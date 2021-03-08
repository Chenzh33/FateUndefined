#include "PlayerViewController.h"

PlayerViewController::PlayerViewController(QGraphicsScene* scene, GameContent* content, TcpClient*tcpclient, QWidget *parent, bool IsHost) : QGraphicsView(parent)
{
	tcpPoint = tcpclient;
	gamestart = false;
	connect(tcpPoint, &TcpClient::gameOver, this, &PlayerViewController::gameOver);
	connect(tcpPoint, &TcpClient::battleData, this, &PlayerViewController::battleData);
	QVariantMap answer;
	answer.insert("state", "battle");
	answer.insert("action", "start");
	answer.insert("from", tcpPoint->userName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());

	_Content = content;
	_Operate = nullptr;
	_Scene = scene;
	_timer = nullptr;

	//以下三句是弹道初始化，Element初始化第三项_Index=0时读入弹道图片，请到Element构造函数里修改
	_BulletPicture_Archer = new Element(0, 0, 13);
	_Scene->addItem(_BulletPicture_Archer);
	_BulletPicture_Archer->hide();

	_BulletPicture_Caster = new Element(0, 0, 14);
	_Scene->addItem(_BulletPicture_Caster);
	_BulletPicture_Caster->hide();

	_BulletPicture_Saber = new Element(0, 0, 15);
	_Scene->addItem(_BulletPicture_Saber);
	_BulletPicture_Saber->hide();

	this->setDragMode(QGraphicsView::ScrollHandDrag);
	this->setFocus();
	this->setScene(scene);

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//之后应该放在initState()中
	_State.IsHost = IsHost;
	_State.IsChoosingAttackTarget = false;
	_State.IsChoosingMoveTarget = false;
	_State.HasAttacked = false;
	_State.HasMoved = false;
	_State.HasUltimateSkilled = false;
	_State.WhileUltimateSkilling = 0;

	_State.Round = 0;
	this->centerOn(_Content->Elements()->get_Element(1));
	//初始化抬头面板
	initBattleInfo();
	initHeadUp();

}

PlayerViewController::~PlayerViewController()
{

}


/**** init ****/
void PlayerViewController::initHeadUp()
{
	_HeadUp = new PanelHeadUp(this);
	QObject::connect(_HeadUp, &PanelHeadUp::ShowMenu_HeadUpToView_Signal, this, &PlayerViewController::ShowMenu);
	QObject::connect(_HeadUp, &PanelHeadUp::ShowPanelBattleInfo_Signal, this, &PlayerViewController::TogglePanelBattleInfo);

}

void PlayerViewController::initBattleInfo()
{
	_BattleInfo = new PanelBattleInfo(_Content, &_State, this);
	_BattleInfo->hide();
}


/**** game control ****/
void PlayerViewController::newRound(QVariantList list)
{
	_State.AttackSequence.clear();
	for (auto i : list){
		_State.AttackSequence.push_back(i.toInt());
	}
	Element* element = _Content->Elements()->get_Element(6);
	element->_character.Death(_State.Round);
	if ((element->_character.get_Whether_Strokes() == 1) &&
		(element->_character.get_Round_Death() == _State.Round - 2))
	{
		_HeadUp->set_health(element->Index(), element->_character.get_HP(), element->_character.get_Max_HP(), element->_character.Death(_State.Round), true);
		element->alive_note();
	}

	Element* element1 = _Content->Elements()->get_Element(-6);
	element1->_character.Death(_State.Round);
	if ((element1->_character.get_Whether_Strokes() == 1) &&
		(element1->_character.get_Round_Death() == _State.Round - 2))
	{
		_HeadUp->set_health(element1->Index(), element1->_character.get_HP(), element1->_character.get_Max_HP(), element1->_character.Death(_State.Round), true);
		element1->alive_note();
	}

	QTimer::singleShot(1500, _BattleInfo, &PanelBattleInfo::RefreshNewRoundInfo);
}

void PlayerViewController::Next()//先攻队列出列，得到下一个待操作的element
{
	_Content->Elements()->get_Element(ActionPiece)->restore();

	/*
	//新增，用于判断剩余队列中是否存在在本轮死亡的Element，如果有，将其pop掉
	do{
	_State.AttackSequence.pop_front();
	if (_State.AttackSequence.empty()){
	initNewRound();
	return;
	}
	} while (_Content->Elements()->get_Element(_State.AttackSequence.front())->_character.Death(_State.Round));
	}*/
	//以上部分已经加入服务器中
	_State.HasMoved = false;
	_State.HasAttacked = false;
	_State.HasUltimateSkilled = false;

	QVariantMap answer;
	answer.insert("state", "battle");
	answer.insert("action", "cancel");
	answer.insert("from", tcpPoint->userName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}


/**** animation and move ****/
void PlayerViewController::attackAnimation(Element*enemy, Element*element, int Damage, bool death,int AC_value)
{

	int piece = element->_character.get_Choose();
	if (piece < 0)piece = -piece;
	if (piece != 2){
		_Content->playlist_battle->setCurrentIndex(piece - 1);
		_Content->player_battle->play();
	}
	if (element->_character.get_Choose() == 2 && element->_character.get_Speed() == 8)
	{
		_Content->playlist_battle->setCurrentIndex(17);
		_Content->player_battle->play();
	}
	if (element->_character.get_Choose() == 2 && element->_character.get_Speed() == 6)
	{
		_Content->playlist_battle->setCurrentIndex(1);
		_Content->player_battle->play();
	}
	//以下开始攻击动画
	QParallelAnimationGroup* ParallelPartofAttackAnimation = new QParallelAnimationGroup;
	QSequentialAnimationGroup* AllAttackAnimation = new QSequentialAnimationGroup;

	//这是冲向element的动画
	QParallelAnimationGroup* AttackTowardEnemyGroup = new QParallelAnimationGroup;
	QPropertyAnimation *AttackForward = new QPropertyAnimation(element, "pos");
	AttackForward->setDuration(100);
	AttackForward->setStartValue(element->pos());
	AttackForward->setEndValue(enemy->pos());

	//这里是弹道动画改动  改图片改下面这个if就行   Archer跟Caster的弹道不同可以分开成两个if
	if (element->_character.get_Choose() == 2 && element->_character.get_Speed() == 6)
	{
		_BulletPicture_Archer->setPos(element->pos());
		qreal rad = qAtan2(enemy->pos().y() - element->pos().y(), enemy->pos().x() - element->pos().x());
		qreal offsetX = cos(PI / 4 - rad / 2)*cos((PI - rad) / 2)*sqrt(2)*CELL_SIZE;
		qreal offsetY = -1 * sin(PI / 4 - rad / 2)*cos((PI - rad) / 2)*sqrt(2)*CELL_SIZE;
		_BulletPicture_Archer->setRotation(rad * 180 / PI);

		AttackForward = new QPropertyAnimation(_BulletPicture_Archer, "pos");
		int dis = element->_character.get_Distance(enemy->_character);
		AttackForward->setDuration(700 + dis * 20);
		AttackForward->setStartValue(QPointF{ _BulletPicture_Archer->pos().x() + offsetX + 30 * cos(rad), _BulletPicture_Archer->pos().y() + offsetY + 30 * sin(rad) });
		AttackForward->setKeyValueAt(qreal(700) / qreal(700 + dis * 20), QPointF{ _BulletPicture_Archer->pos().x() + offsetX, _BulletPicture_Archer->pos().y() + offsetY });
		AttackForward->setEndValue(QPointF{ enemy->pos().x() + offsetX, enemy->pos().y() + offsetY });

		QPropertyAnimation* FadeIn = new QPropertyAnimation(_BulletPicture_Archer, "opacity");
		FadeIn->setDuration(700);
		FadeIn->setStartValue(0);
		FadeIn->setEndValue(1);
		AttackTowardEnemyGroup->addAnimation(FadeIn);

		_BulletPicture_Archer->show();
		_EAnime = new M_Element_Animation(_BulletPicture_Archer);
		QObject::connect(AttackTowardEnemyGroup, &QParallelAnimationGroup::finished, _EAnime, &M_Element_Animation::Emit_Hide_Signal);
	}

	//这里是弹道动画改动  改图片改下面这个if就行   Archer跟Caster的弹道不同可以分开成两个if
	if (element->_character.get_Choose() == 5)
	{
		_BulletPicture_Caster->setPos(element->pos());
		qreal rad = qAtan2(enemy->pos().y() - element->pos().y(), enemy->pos().x() - element->pos().x());

		AttackForward = new QPropertyAnimation(_BulletPicture_Caster, "pos");
		int dis = element->_character.get_Distance(enemy->_character);
		AttackForward->setDuration(350 + dis * 40);
		AttackForward->setStartValue(QPointF{ _BulletPicture_Caster->pos().x() + 30 * cos(rad), _BulletPicture_Caster->pos().y() + 30 * sin(rad) });
		AttackForward->setKeyValueAt(qreal(350) / qreal(350 + dis * 40), QPointF{ _BulletPicture_Caster->pos().x() + 30 * cos(rad), _BulletPicture_Caster->pos().y() + 30 * sin(rad) });
		AttackForward->setEndValue(enemy->pos());

		QPropertyAnimation* FadeIn = new QPropertyAnimation(_BulletPicture_Caster, "opacity");
		FadeIn->setDuration(350);
		FadeIn->setStartValue(0);
		FadeIn->setEndValue(1);
		AttackTowardEnemyGroup->addAnimation(FadeIn);

		_BulletPicture_Caster->show();
		_EAnime = new M_Element_Animation(_BulletPicture_Caster);
		QObject::connect(AttackTowardEnemyGroup, &QParallelAnimationGroup::finished, _EAnime, &M_Element_Animation::Emit_Hide_Signal);
	}

	AttackTowardEnemyGroup->addAnimation(AttackForward);


	//这是从element缩回来的动画，如果是弹道自然没有这条，下面判断了
	QPropertyAnimation* AttackTowardEnemy_Back = new QPropertyAnimation(element, "pos");
	AttackTowardEnemy_Back->setDuration(100);
	AttackTowardEnemy_Back->setStartValue(enemy->pos());
	AttackTowardEnemy_Back->setEndValue(element->pos());

	//下面是enemy的迷♂之♂抖♂动动画组
	int deltaX[9] = { 0, 1, 4, -1, -5, 9, 2, -6, 0 };
	int deltaY[9] = { 0, 3, -5, 8, -9, 7, 9, -3, 0 };
	QSequentialAnimationGroup* BeAttacked = new QSequentialAnimationGroup;
	for (int i = 0; i < 8; i++)
	{
		//生成向某一个方向抖♂动的动画
		QPropertyAnimation* temp_BeAttacked = new QPropertyAnimation(enemy, "pos");
		temp_BeAttacked->setDuration(40);
		temp_BeAttacked->setStartValue(QPointF(enemy->x() + deltaX[i], enemy->y() + deltaY[i]));
		temp_BeAttacked->setEndValue(QPointF(enemy->x() + deltaX[i + 1], enemy->y() + deltaY[i + 1]));
		//把这一次迷♂之♂抖♂动加入动画组
		BeAttacked->addAnimation(temp_BeAttacked);
	}

	//如果是弹道动画（远程），那么就没有缩回来这个动作了
	if ((element->_character.get_Choose() != 5) && !((element->_character.get_Choose() == 2) && (element->_character.get_Speed() == 6)))
		ParallelPartofAttackAnimation->addAnimation(AttackTowardEnemy_Back);
	//迷之抖动和element从enemy处缩回是同时的，所以用Parallel动画组的ParallelPartofAttackAnimation


	//*****此处需将assassin闪避动画加入*****//
	if (AC_value == 30 && element->_character.get_Choose() != 5){
		connect(AttackTowardEnemyGroup, &QParallelAnimationGroup::finished, this, &PlayerViewController::UltimateSkill_Assassin_Sound_Effect);
		QParallelAnimationGroup* Assassin_Dodge_Anime = new QParallelAnimationGroup;
		qreal rad = qAtan2(enemy->pos().y() - element->pos().y(), enemy->pos().x() - element->pos().x());

		QPropertyAnimation *Assassin_Opac = new QPropertyAnimation(enemy, "opacity");
		Assassin_Opac->setDuration(400);
		Assassin_Opac->setStartValue(0);
		Assassin_Opac->setKeyValueAt(0.5, 0);
		Assassin_Opac->setEndValue(1);
		Assassin_Dodge_Anime->addAnimation(Assassin_Opac);

		Element* Effect_Dodge_1 = new Element(enemy->pos().x() - sin(rad) * 80, enemy->pos().y() + cos(rad) * 80, 18);
		_Scene->addItem(Effect_Dodge_1);
		QPropertyAnimation *Assassin_Dodge_Move_1 = new QPropertyAnimation(Effect_Dodge_1, "pos");
		Assassin_Dodge_Move_1->setDuration(200);
		Assassin_Dodge_Move_1->setStartValue(QPointF{ enemy->pos().x() - sin(rad) * 80, enemy->pos().y() + cos(rad) * 80 });
		Assassin_Dodge_Move_1->setEndValue(enemy->pos());
		Assassin_Dodge_Anime->addAnimation(Assassin_Dodge_Move_1);

		Element* Effect_Dodge_2 = new Element(enemy->pos().x() + sin(rad) * 80, enemy->pos().y() + cos(rad) * 80, 18);
		_Scene->addItem(Effect_Dodge_2);
		QPropertyAnimation *Assassin_Dodge_Move_2 = new QPropertyAnimation(Effect_Dodge_2, "pos");
		Assassin_Dodge_Move_2->setDuration(200);
		Assassin_Dodge_Move_2->setStartValue(QPointF{ enemy->pos().x() + sin(rad) * 80, enemy->pos().y() - cos(rad) * 80 });
		Assassin_Dodge_Move_2->setEndValue(enemy->pos());
		Assassin_Dodge_Anime->addAnimation(Assassin_Dodge_Move_2);

		QPropertyAnimation *Assassin_Dodge_Opac_1 = new QPropertyAnimation(Effect_Dodge_1, "opacity");
		Assassin_Dodge_Opac_1->setDuration(200);
		Assassin_Dodge_Opac_1->setStartValue(0);
		Assassin_Dodge_Opac_1->setEndValue(1);
		Assassin_Dodge_Anime->addAnimation(Assassin_Dodge_Opac_1);

		QPropertyAnimation *Assassin_Dodge_Opac_2 = new QPropertyAnimation(Effect_Dodge_2, "opacity");
		Assassin_Dodge_Opac_2->setDuration(200);
		Assassin_Dodge_Opac_2->setStartValue(0);
		Assassin_Dodge_Opac_2->setEndValue(1);
		Assassin_Dodge_Anime->addAnimation(Assassin_Dodge_Opac_2);

		ParallelPartofAttackAnimation->addAnimation(Assassin_Dodge_Anime);
		connect(Assassin_Dodge_Anime, &QParallelAnimationGroup::finished, Effect_Dodge_1, &Element::deleteLater);
		connect(Assassin_Dodge_Anime, &QParallelAnimationGroup::finished, Effect_Dodge_2, &Element::deleteLater);

	}
	else{
		ParallelPartofAttackAnimation->addAnimation(BeAttacked);
	}

	//*****结束*****//

	//先是element冲向enemy，然后才是迷之抖动和缩回来，所以用Sequential动画组的AllAttackAnimation
	//如果是远程，就是先弹道打出来，然后是迷之抖动
	AllAttackAnimation->addAnimation(AttackTowardEnemyGroup);
	AllAttackAnimation->addAnimation(ParallelPartofAttackAnimation);
	//以上为攻击动画

	//弹道打到身上才出现伤害，因为connect函数比较逗比的原因一定要用这种奇怪的方式链接
	_EAnime = new M_Element_Animation(enemy, Damage);
	QObject::connect(AttackTowardEnemyGroup, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Damage_Signal);
	QObject::connect(_EAnime, &M_Element_Animation::Damage_signal, this, &PlayerViewController::show_damage);

	enemy->_character.Input_Damage(Damage);
	//掉血动画在攻击动画后面运行
	_HealthAnime = new M_Element_Animation(enemy, _State.Round, _HeadUp);
	if (Damage>0)
		QObject::connect(AttackTowardEnemyGroup, &QPropertyAnimation::finished, _HealthAnime, &M_Element_Animation::Emit_Set_Health_Signal);


	//判断死亡，死亡动画也在攻击动画后面调用
	if (enemy->_character.Death(_State.Round))
	{
		if ((enemy->_character.get_Choose() == 6) && (enemy->_character.get_Whether_Strokes() == 0))
		{
			//判定B叔用过大招了
			enemy->_character.set_Whether_Strokes(1);
			QObject::connect(AllAttackAnimation, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Tomb_Note_Signal);
		}
		else
		{
			//这是一个渐隐
			QPropertyAnimation *DeathAnime = new QPropertyAnimation(enemy, "opacity");
			DeathAnime->setDuration(1200);
			DeathAnime->setStartValue(1);
			DeathAnime->setEndValue(0);
			//死亡动画在迷♂之♂抖♂动结束后再开始
			AllAttackAnimation->addAnimation(DeathAnime);
			//在死亡动画结束后hide这个element
			QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Hide_Signal);
		}

	}

	//这里执行所有的动画组
	AllAttackAnimation->start();
}

void PlayerViewController::saberAnimation(Element*enemy, Element*element, int Damage, bool death)
{
	QParallelAnimationGroup* ParallelPartofAttackAnimation = new QParallelAnimationGroup;
	QParallelAnimationGroup* EffectAnimation = new QParallelAnimationGroup;
	QSequentialAnimationGroup* AllAttackAnimation = new QSequentialAnimationGroup;
	QSequentialAnimationGroup* AllAttackForwardAnime = new QSequentialAnimationGroup;

	//快速阶段
	QPropertyAnimation* AttackTowardEnemy_1 = new QPropertyAnimation(_BulletPicture_Saber, "pos");
	_BulletPicture_Saber->setPos(element->pos().x() - CELL_SIZE / 2, element->pos().y() - CELL_SIZE / 2);

	qreal rad = qAtan2(enemy->pos().y() - element->pos().y(), enemy->pos().x() - element->pos().x());
	qreal offsetX = cos(PI / 4 - rad / 2)*cos((PI - rad) / 2)*sqrt(2) * 2 * CELL_SIZE;
	qreal offsetY = -1 * sin(PI / 4 - rad / 2)*cos((PI - rad) / 2)*sqrt(2) * 2 * CELL_SIZE;
	_BulletPicture_Saber->setRotation(rad * 180 / PI);

	AttackTowardEnemy_1 = new QPropertyAnimation(_BulletPicture_Saber, "pos");
	int dis = element->_character.get_Distance(enemy->_character);
	AttackTowardEnemy_1->setDuration(dis * 30);
	AttackTowardEnemy_1->setStartValue(QPointF{ _BulletPicture_Saber->pos().x() - CELL_SIZE / 2 + offsetX, _BulletPicture_Saber->pos().y() - CELL_SIZE / 2 + offsetY });
	AttackTowardEnemy_1->setEndValue(QPointF{ enemy->pos().x() - CELL_SIZE / 2 + offsetX - 40 * cos(rad), enemy->pos().y() - CELL_SIZE / 2 + offsetY - 40 * sin(rad) });
	AllAttackForwardAnime->addAnimation(AttackTowardEnemy_1);


	//慢速阶段
	QPropertyAnimation* AttackTowardEnemy_2 = new QPropertyAnimation(_BulletPicture_Saber, "pos");
	AttackTowardEnemy_2 = new QPropertyAnimation(_BulletPicture_Saber, "pos");
	AttackTowardEnemy_2->setDuration(1000);
	AttackTowardEnemy_2->setStartValue(QPointF{ enemy->pos().x() - CELL_SIZE / 2 + offsetX - 40 * cos(rad), enemy->pos().y() - CELL_SIZE / 2 + offsetY - 40 * sin(rad) });
	AttackTowardEnemy_2->setEndValue(QPointF{ enemy->pos().x() - CELL_SIZE / 2 + offsetX, enemy->pos().y() - CELL_SIZE / 2 + offsetY });

	AllAttackForwardAnime->addAnimation(AttackTowardEnemy_2);

	_BulletPicture_Saber->show();
	_EAnime = new M_Element_Animation(_BulletPicture_Saber);
	QObject::connect(AllAttackForwardAnime, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Hide_Signal);

	//下为特效动画（并行）
	QPropertyAnimation* OpacityChange = new QPropertyAnimation(_BulletPicture_Saber, "opacity");
	OpacityChange->setDuration(dis * 30 + 1000);
	OpacityChange->setStartValue(0.3);
	OpacityChange->setEndValue(1);

	EffectAnimation->addAnimation(AllAttackForwardAnime);
	EffectAnimation->addAnimation(OpacityChange);

	QTimer *EffectTimer_1 = new QTimer;
	QTimer *EffectTimer_2 = new QTimer;
	EffectTimer_1->start(10);
	connect(AttackTowardEnemy_1, &QPropertyAnimation::finished, EffectTimer_1, &QTimer::stop);
	connect(AttackTowardEnemy_1, &QPropertyAnimation::finished, EffectTimer_1, &QTimer::deleteLater);
	connect(AttackTowardEnemy_1, &QPropertyAnimation::finished, this, &PlayerViewController::UltimateSkill_Saber_Sound_Effect);
	connect(EffectTimer_1, &QTimer::timeout, this, &PlayerViewController::UltimateSkill_Saber_Effect_Fast);
	QObject::connect(AttackTowardEnemy_1, SIGNAL(finished(void)),
		EffectTimer_2, SLOT(start(void)));

	EffectTimer_2->setInterval(10);
	connect(AttackTowardEnemy_2, &QPropertyAnimation::finished, EffectTimer_2, &QTimer::stop);
	connect(AttackTowardEnemy_2, &QPropertyAnimation::finished, EffectTimer_2, &QTimer::deleteLater);
	connect(EffectTimer_2, &QTimer::timeout, this, &PlayerViewController::UltimateSkill_Saber_Effect_Slow);

	//下面是enemy的迷♂之♂抖♂动动画组
	int deltaX[9] = { 0, 1, 4, -1, -5, 9, 2, -6, 0 };
	int deltaY[9] = { 0, 3, -5, 8, -9, 7, 9, -3, 0 };
	QSequentialAnimationGroup* BeAttacked = new QSequentialAnimationGroup;
	for (int i = 0; i < 8; i++)
	{
		//生成向某一个方向抖♂动的动画
		QPropertyAnimation* temp_BeAttacked = new QPropertyAnimation(enemy, "pos");
		temp_BeAttacked->setDuration(40);
		temp_BeAttacked->setStartValue(QPointF(enemy->x() + deltaX[i], enemy->y() + deltaY[i]));
		temp_BeAttacked->setEndValue(QPointF(enemy->x() + deltaX[i + 1], enemy->y() + deltaY[i + 1]));
		//把这一次迷♂之♂抖♂动加入动画组
		BeAttacked->addAnimation(temp_BeAttacked);
	}

	//迷之抖动和element从enemy处缩回是同时的，所以用Parallel动画组的ParallelPartofAttackAnimation
	ParallelPartofAttackAnimation->addAnimation(BeAttacked);

	//先是element冲向enemy，然后才是迷之抖动和缩回来，所以用Sequential动画组的AllAttackAnimation
	//如果是远程，就是先弹道打出来，然后是迷之抖动
	AllAttackAnimation->addAnimation(EffectAnimation);
	AllAttackAnimation->addAnimation(ParallelPartofAttackAnimation);
	//以上为攻击动画

	//弹道打到身上才出现伤害，因为connect函数比较逗比的原因一定要用这种奇怪的方式链接
	//改动：伤害固定为25
	_EAnime = new M_Element_Animation(enemy, Damage);
	QObject::connect(AllAttackForwardAnime, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Damage_Signal);
	QObject::connect(_EAnime, &M_Element_Animation::Damage_signal, this, &PlayerViewController::show_damage);

	enemy->_character.Input_Damage(Damage);
	//掉血动画
	_HealthAnime = new M_Element_Animation(enemy, _State.Round, _HeadUp);
	if (Damage > 0)
		QObject::connect(AllAttackForwardAnime, &QPropertyAnimation::finished, _HealthAnime, &M_Element_Animation::Emit_Set_Health_Signal);

	//判断死亡
	if (enemy->_character.Death(_State.Round))
	{
		if ((enemy->_character.get_Choose() == 6) && (enemy->_character.get_Whether_Strokes() == 0))
		{
			//判定B叔用过大招了
			enemy->_character.set_Whether_Strokes(1);
			QObject::connect(AllAttackAnimation, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Tomb_Note_Signal);
		}
		else
		{
			//这是一个渐隐
			QPropertyAnimation *DeathAnime = new QPropertyAnimation(enemy, "opacity");
			DeathAnime->setDuration(1200);
			DeathAnime->setStartValue(1);
			DeathAnime->setEndValue(0);
			//死亡动画在迷♂之♂抖♂动结束后再开始
			AllAttackAnimation->addAnimation(DeathAnime);
			//在死亡动画结束后hide这个element
			QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Hide_Signal);
		}
	}
	//这里执行所有的动画组
	AllAttackAnimation->start();

}

//待修改
void PlayerViewController::archerAnimation(bool melee)
{
	/*QSequentialAnimationGroup* Multi_AllAttackAnimation = new QSequentialAnimationGroup;

	//以下是Attack那边copy过来的   改动会写出
	do
	{
		QParallelAnimationGroup* ParallelPartofAttackAnimation = new QParallelAnimationGroup;
		QSequentialAnimationGroup* AllAttackAnimation = new QSequentialAnimationGroup;

		//这是冲向element的动画
		QPropertyAnimation* AttackTowardEnemy = new QPropertyAnimation(element, "pos");
		AttackTowardEnemy->setDuration(100);
		AttackTowardEnemy->setStartValue(element->pos());
		AttackTowardEnemy->setEndValue(enemy->pos());

		//改动：删除弹道部分
		//这是从element缩回来的动画，如果是弹道自然没有这条，下面判断了
		QPropertyAnimation* AttackTowardEnemy_Back = new QPropertyAnimation(element, "pos");
		AttackTowardEnemy_Back->setDuration(100);
		AttackTowardEnemy_Back->setStartValue(enemy->pos());
		AttackTowardEnemy_Back->setEndValue(element->pos());

		//下面是enemy的迷♂之♂抖♂动动画组
		int deltaX[9] = { 0, 1, 4, -1, -5, 9, 2, -6, 0 };
		int deltaY[9] = { 0, 3, -5, 8, -9, 7, 9, -3, 0 };
		QSequentialAnimationGroup* BeAttacked = new QSequentialAnimationGroup;
		for (int i = 0; i < 8; i++)
		{
			//生成向某一个方向抖♂动的动画
			QPropertyAnimation* temp_BeAttacked = new QPropertyAnimation(enemy, "pos");
			temp_BeAttacked->setDuration(40);
			temp_BeAttacked->setStartValue(QPointF(enemy->x() + deltaX[i], enemy->y() + deltaY[i]));
			temp_BeAttacked->setEndValue(QPointF(enemy->x() + deltaX[i + 1], enemy->y() + deltaY[i + 1]));
			//把这一次迷♂之♂抖♂动加入动画组
			BeAttacked->addAnimation(temp_BeAttacked);
		}

		ParallelPartofAttackAnimation->addAnimation(AttackTowardEnemy_Back);
		//迷之抖动和element从enemy处缩回是同时的，所以用Parallel动画组的ParallelPartofAttackAnimation
		ParallelPartofAttackAnimation->addAnimation(BeAttacked);

		//先是element冲向enemy，然后才是迷之抖动和缩回来，所以用Sequential动画组的AllAttackAnimation
		AllAttackAnimation->addAnimation(AttackTowardEnemy);
		AllAttackAnimation->addAnimation(ParallelPartofAttackAnimation);
		//以上为攻击动画

		//改动：这里暂时不用考虑show_Damage和掉血动画
		//改动：伤害和判定死亡放到后面
		//改动：将这段加入总动画组
		Multi_AllAttackAnimation->addAnimation(AllAttackAnimation);

		attack_num--;

	} while (attack_num > 0);

	enemy->_character.Input_Damage(Damage);

	_EAnime = new M_Element_Animation(enemy, Damage);
	QObject::connect(Multi_AllAttackAnimation, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Damage_Signal);
	QObject::connect(_EAnime, &M_Element_Animation::Damage_signal, this, &PlayerViewController::show_damage);

	_HeadUp->set_health(enemy->Index(), enemy->_character.get_HP(), enemy->_character.get_Max_HP(), enemy->_character.Death(_State.Round));

	//判断死亡
	if (enemy->_character.Death(_State.Round))
	{
		if ((enemy->_character.get_Choose() == 6) && (enemy->_character.get_Whether_Strokes() == 0))
		{
			//判定B叔用过大招了
			enemy->_character.set_Whether_Strokes(1);
			QObject::connect(Multi_AllAttackAnimation, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Tomb_Note_Signal);
		}
		else
		{
			//这是一个渐隐
			QPropertyAnimation *DeathAnime = new QPropertyAnimation(enemy, "opacity");
			DeathAnime->setDuration(1200);
			DeathAnime->setStartValue(1);
			DeathAnime->setEndValue(0);
			//死亡动画在迷♂之♂抖♂动结束后再开始
			Multi_AllAttackAnimation->addAnimation(DeathAnime);
			//在死亡动画结束后hide这个element
			QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime, &M_Element_Animation::Emit_Hide_Signal);
		}
	}

	Multi_AllAttackAnimation->start();*/
	int temp_piece = ActionPiece;
	//以下为单纯地播放音效
	Element*element = _Content->Elements()->get_Element(ActionPiece);
	if (element->_character.get_AB() != 8){
		_Content->playlist_battle->setCurrentIndex(18);
		_Content->player_battle->play();
	}
	else{
		_Content->playlist_battle->setCurrentIndex(14);
		_Content->player_battle->play();
	}
	if (temp_piece > 0){
		temp_piece = temp_piece - 1;
	}
	else{
		temp_piece = -temp_piece + 5;
	}
	QIcon tempicon;
	QString tempString = { ":/IconSrc/Archer_headup" };
	if (melee){
		tempString.push_back('2');
		if (_State.AttackSequence.front() > 0){
			element->surface_index = 19;
		}
		else{
			element->surface_index = 20;
		}
	}
	else{
		element->surface_index = _State.AttackSequence.front();
	}
	element->update();
	tempicon.addFile(tempString, QSize(), QIcon::Normal, QIcon::Off);
	_HeadUp->GraphicsItem[temp_piece]->setIcon(tempicon);
}

void PlayerViewController::riderAnimation(QVariantList list, QVariantList death_list)
{
	_Content->playlist_battle->setCurrentIndex(15);
	_Content->player_battle->play();
	//次数-1
	auto element = _Content->Elements()->get_Element(ActionPiece);
	element->_character.change_Num_Strokes();
	int calc = -1;
	for (auto temp_element_num : list)
	{
		Element* temp_element = _Content->Elements()->get_Element(temp_element_num.toInt());
		calc++;

		int deltaX[9] = { 0, 1, 4, -1, -5, 9, 2, -6, 0 };
		int deltaY[9] = { 0, 3, -5, 8, -9, 7, 9, -3, 0 };
		QSequentialAnimationGroup* BeAttacked = new QSequentialAnimationGroup;
		for (int i = 0; i < 8; i++)
		{
			//生成向某一个方向抖♂动的动画
			QPropertyAnimation* temp_BeAttacked = new QPropertyAnimation(temp_element, "pos");
			temp_BeAttacked->setDuration(40);
			temp_BeAttacked->setStartValue(QPointF(temp_element->x() + deltaX[i], temp_element->y() + deltaY[i]));
			temp_BeAttacked->setEndValue(QPointF(temp_element->x() + deltaX[i + 1], temp_element->y() + deltaY[i + 1]));
			//把这一次迷♂之♂抖♂动加入动画组
			BeAttacked->addAnimation(temp_BeAttacked);
		}
		if (death_list.count(temp_element_num))
		{
			int Damage = temp_element->_character.get_HP() + 2;
			temp_element->_character.Input_Damage(Damage);
			//掉血动画
			_HeadUp->set_health(temp_element->Index(), temp_element->_character.get_HP(), temp_element->_character.get_Max_HP(), true);
			if (temp_element->_character.Death(_State.Round))
			{
				if ((temp_element->_character.get_Choose() == 6) && (temp_element->_character.get_Whether_Strokes() == 0))
				{
					//判定B叔用过大招了
					temp_element->_character.set_Whether_Strokes(1);
					temp_element->tomb_note();
				}
				else
				{
					//这是一个渐隐
					QPropertyAnimation *DeathAnime = new QPropertyAnimation(temp_element, "opacity");
					DeathAnime->setDuration(1200);
					DeathAnime->setStartValue(1);
					DeathAnime->setEndValue(0);
					BeAttacked->addAnimation(DeathAnime);
					//DeathAnime->start();

					//在死亡动画结束后hide这个element
					_EAnime_Rider[calc] = new M_Element_Animation(temp_element);
					QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime_Rider[calc], &M_Element_Animation::Emit_Hide_Signal);
				}
			}

		}
		else QObject::connect(BeAttacked, &QPropertyAnimation::finished, temp_element, &Element::alive_note);
		BeAttacked->start();
	}
}

void PlayerViewController::casterAnimation(Element* element, int x, int y)
{
	element->_character.change_Num_Strokes();
	element->Move(x, y);

	_Content->playlist_battle->setCurrentIndex(16);
	_Content->player_battle->play();

	QSequentialAnimationGroup *AnimeGroup = new QSequentialAnimationGroup;

	QPropertyAnimation *OpacityAnime = new QPropertyAnimation(element, "opacity");
	OpacityAnime->setDuration(600);
	OpacityAnime->setStartValue(1);
	OpacityAnime->setEndValue(0);
	AnimeGroup->addAnimation(OpacityAnime);

	QPropertyAnimation *MoveAnime = new QPropertyAnimation(element, "pos");
	MoveAnime->setDuration(1);
	MoveAnime->setStartValue(element->pos());
	MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(x, y, 0, 0);
	MoveAnime->setEndValue(temp_MapUnit->pos());
	AnimeGroup->addAnimation(MoveAnime);

	QPropertyAnimation *OpacityAnime_2 = new QPropertyAnimation(element, "opacity");
	OpacityAnime_2->setDuration(600);
	OpacityAnime_2->setStartValue(0);
	OpacityAnime_2->setEndValue(1);
	AnimeGroup->addAnimation(OpacityAnime_2);

	//消失->移动->出现
	AnimeGroup->start();
}

void PlayerViewController::MoveElement(int piece,int x, int y)
{
	Element*element = _Content->Elements()->get_Element(piece);
	MoveAnimate(element, x, y);
	element->Move(x, y);
}

void PlayerViewController::MoveAnimate(Element* element, int x, int y)
{
	//播放音效
	int piece = element->_character.get_Choose();
	if (piece < 0)piece = -piece;
	_Content->playlist_battle->setCurrentIndex(piece +5);
	_Content->player_battle->play();

	int temp_x = element->_character.get_X();
	int temp_y = element->_character.get_Y();
	int temp_speed = element->_character.get_Speed() * 2 + 1;

	QVector<int> List_X;
	QVector<int> List_Y;
	QVector<int> List_Pace;
	//List_MapUnit[i]代表第i个元素从初始位置到现在的路径，存在一个QVector里
	QVector<QVector<MapUnit*>> List_MapUnit;
	List_X.push_back(temp_x);
	List_Y.push_back(temp_y);
	List_Pace.push_back(0);
	//这是准备存到List_MapUnit中的一个临时变量
	QVector<MapUnit*> tempMapUnitRoute;
	tempMapUnitRoute.push_back(_Content->Map()->get_MapUnit_around(temp_x, temp_y, 0, 0));
	List_MapUnit.push_back(tempMapUnitRoute);

	int nowX = x;
	int nowY = y;


	int head = -1;
	int tail = 0;
	int temp_pace = 0;
	int deltaX[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };
	int deltaY[8] = { 1, 0, -1, 0, -1, 1, -1, 1 };
	bool MultiIgnore[40][40] = { { false } };
	MultiIgnore[temp_x][temp_y] = true;
	while (head < tail)
	{
		head++;
		temp_x = List_X[head];
		temp_y = List_Y[head];
		temp_pace = List_Pace[head];
		if (temp_pace + 2> temp_speed) continue;
		for (int i = 0; i < 4; i++)
		{
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], deltaY[i]);
			if (temp_MapUnit == nullptr) continue;
			Element* itemBlocking = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit->Xcell(), temp_MapUnit->Ycell());
			if ((itemBlocking != nullptr) && (!(itemBlocking->_character.Death(_State.Round)))) continue;
			if ((itemBlocking != nullptr) && (itemBlocking->_character.get_Choose() == 6) &&
				(itemBlocking->_character.get_Round() - itemBlocking->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit->CanPass()) continue;
			if (MultiIgnore[temp_x + deltaX[i]][temp_y + deltaY[i]]) continue;
			List_X.push_back(temp_x + deltaX[i]);
			List_Y.push_back(temp_y + deltaY[i]);
			//下面3句是传递路径，下同
			tempMapUnitRoute = List_MapUnit[head];
			tempMapUnitRoute.push_back(temp_MapUnit);
			List_MapUnit.push_back(tempMapUnitRoute);

			List_Pace.push_back(temp_pace + 2);
			tail++;
			MultiIgnore[List_X[tail]][List_Y[tail]] = true;
		}
		if (temp_pace + 3> temp_speed) continue;
		for (int i = 4; i < 8; i++)
		{
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], deltaY[i]);
			if (temp_MapUnit == nullptr) continue;
			Element* itemBlocking = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit->Xcell(), temp_MapUnit->Ycell());
			if ((itemBlocking != nullptr) && (!(itemBlocking->_character.Death(_State.Round)))) continue;
			if ((itemBlocking != nullptr) && (itemBlocking->_character.get_Choose() == 6) &&
				(itemBlocking->_character.get_Round() - itemBlocking->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit->CanPass()) continue;
			if (MultiIgnore[temp_x + deltaX[i]][temp_y + deltaY[i]]) continue;

			MapUnit* temp_MapUnit_noX = _Content->Map()->get_MapUnit_around(temp_x, temp_y, 0, deltaY[i]);
			if (temp_MapUnit_noX == nullptr) continue;
			Element* itemBlocking_noX = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit_noX->Xcell(), temp_MapUnit_noX->Ycell());
			if ((itemBlocking_noX != nullptr) && (!(itemBlocking_noX->_character.Death(_State.Round)))) continue;
			if ((itemBlocking_noX != nullptr) && (itemBlocking_noX->_character.get_Choose() == 6) &&
				(itemBlocking_noX->_character.get_Round() - itemBlocking_noX->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit_noX->CanPass()) continue;

			MapUnit* temp_MapUnit_noY = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], 0);
			if (temp_MapUnit_noY == nullptr) continue;
			Element* itemBlocking_noY = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit_noY->Xcell(), temp_MapUnit_noY->Ycell());
			if ((itemBlocking_noY != nullptr) && (!(itemBlocking_noY->_character.Death(_State.Round)))) continue;
			if ((itemBlocking_noY != nullptr) && (itemBlocking_noY->_character.get_Choose() == 6) &&
				(itemBlocking_noY->_character.get_Round() - itemBlocking_noY->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit_noY->CanPass()) continue;

			List_X.push_back(temp_x + deltaX[i]);
			List_Y.push_back(temp_y + deltaY[i]);

			tempMapUnitRoute = List_MapUnit[head];
			tempMapUnitRoute.push_back(temp_MapUnit);
			List_MapUnit.push_back(tempMapUnitRoute);

			List_Pace.push_back(temp_pace + 3);
			tail++;
			MultiIgnore[List_X[tail]][List_Y[tail]] = true;
		}
	}

	//下为移动动画
	QSequentialAnimationGroup *AnimeGroup = new QSequentialAnimationGroup;

	for (int k = 0; k <= tail; k++)
	if ((List_X[k] == nowX) && (List_Y[k] == nowY))
	for (int i = 0; i < List_MapUnit[k].size() - 1; i++)
	{
		QPropertyAnimation *MoveAnime = new QPropertyAnimation(element, "pos");
		MoveAnime->setDuration(80);//速度已降低
		if ((List_MapUnit[k][i]->Xcell() != List_MapUnit[k][i + 1]->Xcell()) &&
			(List_MapUnit[k][i]->Xcell() != List_MapUnit[k][i + 1]->Xcell()))
			MoveAnime->setDuration(113);//
		MoveAnime->setStartValue(List_MapUnit[k][i]->pos());
		MoveAnime->setEndValue(List_MapUnit[k][i + 1]->pos());
		AnimeGroup->addAnimation(MoveAnime);//构建每一格到下一格的动画，并逐个加入动画组
	}
	AnimeGroup->start();//动画组播放，播放结束后，element的【真实位置】已发生改变，但由于未改变坐标值，故需有下一句：
}

void PlayerViewController::newRoundAnimation(){
	QString text{ std::to_string(_State.Round).c_str() };
	text = "ROUND " + text;
	QLabel* textNewRound = new QLabel(text, this);
	textNewRound->setGeometry(VIEW_WIDTH / 2 - 1400, VIEW_HEIGHT / 2 - 100, 1000, 100);
	textNewRound->setFont(QFont("Algerian", 100, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Round = new QGraphicsColorizeEffect(textNewRound);
	ColorEffect_Round->setColor(QColor(255, 255, 65));
	textNewRound->setGraphicsEffect(ColorEffect_Round);
	textNewRound->show();

	QSequentialAnimationGroup *SlideAnimeGroup = new QSequentialAnimationGroup;
	QPropertyAnimation* Slide_Anime_1 = new QPropertyAnimation(textNewRound, "geometry");
	Slide_Anime_1->setDuration(200);
	Slide_Anime_1->setStartValue(textNewRound->geometry());
	Slide_Anime_1->setEndValue(QRect(textNewRound->geometry().left() + 1000, textNewRound->geometry().top(), textNewRound->geometry().width(), textNewRound->geometry().height()));

	QPropertyAnimation* Slide_Anime_2 = new QPropertyAnimation(textNewRound, "geometry");
	Slide_Anime_2->setDuration(800);
	Slide_Anime_2->setStartValue(QRect(textNewRound->geometry().left() + 1000, textNewRound->geometry().top(), textNewRound->geometry().width(), textNewRound->geometry().height()));
	Slide_Anime_2->setEndValue(QRect(textNewRound->geometry().left() + 1200, textNewRound->geometry().top(), textNewRound->geometry().width(), textNewRound->geometry().height()));

	QPropertyAnimation* Slide_Anime_3 = new QPropertyAnimation(textNewRound, "geometry");
	Slide_Anime_3->setDuration(500);
	Slide_Anime_3->setStartValue(QRect(textNewRound->geometry().left() + 1200, textNewRound->geometry().top(), textNewRound->geometry().width(), textNewRound->geometry().height()));
	Slide_Anime_3->setEndValue(QRect(textNewRound->geometry().left() + 2200, textNewRound->geometry().top(), textNewRound->geometry().width(), textNewRound->geometry().height()));

	SlideAnimeGroup->addAnimation(Slide_Anime_1);
	SlideAnimeGroup->addAnimation(Slide_Anime_2);
	SlideAnimeGroup->addAnimation(Slide_Anime_3);

	SlideAnimeGroup->start();
}

/**** assistant ****/
void PlayerViewController::resetOperate()//删除operate
{
	if (_Operate != nullptr){
		delete(_Operate);
		_Operate = nullptr;
	}
	this->setFocus();
}

void PlayerViewController::show_damage(int damage)
{
	QString text{ std::to_string(damage).c_str() };
	if (damage == 0) text = "MISS";
	QLabel* DamageText = new QLabel(this);
	DamageText->setGeometry(VIEW_WIDTH / 2 - 200, VIEW_HEIGHT / 2 - 100, 500, 135);
	DamageText->setFont(QFont("Algerian", 150, QFont::Bold));
	DamageText->setText(text);
	QGraphicsColorizeEffect *_ColorEffect = new QGraphicsColorizeEffect(DamageText);
	_ColorEffect->setColor(QColor(255, 204, 0));
	_ColorEffect->setStrength(1);
	DamageText->setGraphicsEffect(_ColorEffect);

	QTimer::singleShot(3000, DamageText, &QLabel::deleteLater);
	DamageText->show();
	QPropertyAnimation* Upward_Anime = new QPropertyAnimation(DamageText, "geometry");
	Upward_Anime->setDuration(1000);
	Upward_Anime->setStartValue(DamageText->geometry());
	Upward_Anime->setEndValue(QRect(DamageText->geometry().left(), DamageText->geometry().top() - DamageText->geometry().height() * 1 / 2, DamageText->geometry().width(), DamageText->geometry().height()));
	Upward_Anime->start();
}

void PlayerViewController::Melee_Archer()
{
	Element* element = _Content->Elements()->get_Element(ActionPiece);

	element->_character.set_AB(8);
	element->_character.set_AC(13);
	element->_character.set_Ability_Bonus(0);
	element->_character.set_Range_Inc(1);
	element->_character.set_Dice_Num(3);
	element->_character.set_Dice_Type(4);
	element->_character.set_Critical_Hit_Range(2);
	element->_character.set_Critical_Hit_Bonus(2);
	element->_character.set_Speed(8);
}

void PlayerViewController::Remote_Archer()
{
	Element* element = _Content->Elements()->get_Element(ActionPiece);

	element->_character.set_AB(6);
	element->_character.set_AC(13);
	element->_character.set_Ability_Bonus(0);
	element->_character.set_Range_Inc(10);
	element->_character.set_Dice_Num(1);
	element->_character.set_Dice_Type(8);
	element->_character.set_Critical_Hit_Range(1);
	element->_character.set_Critical_Hit_Bonus(3);
	element->_character.set_Speed(6);
}

void PlayerViewController::UltimateSkill_Saber_Effect_Fast()
{
	std::random_device rd;
	qreal angle = _BulletPicture_Saber->rotation() + (rd() % 90) - 45;
	Element* Effect = new Element(_BulletPicture_Saber->pos().x(), _BulletPicture_Saber->pos().y(), 16);
	_Scene->addItem(Effect);

	qreal rad = angle / 180 * PI;

	Effect->setRotation(angle);

	QParallelAnimationGroup* AllAnime = new QParallelAnimationGroup;

	QPropertyAnimation* Move_Anime = new QPropertyAnimation(Effect, "pos");
	Move_Anime->setDuration(700);
	Move_Anime->setStartValue(_BulletPicture_Saber->pos());
	Move_Anime->setEndValue(QPointF{ _BulletPicture_Saber->pos().x() + cos(rad) * 60, _BulletPicture_Saber->pos().y() + sin(rad) * 60 });

	QPropertyAnimation* Opacity_Anime = new QPropertyAnimation(Effect, "opacity");
	Opacity_Anime->setDuration(700);
	Opacity_Anime->setStartValue(0.4);
	Opacity_Anime->setEndValue(0);

	AllAnime->addAnimation(Move_Anime);
	AllAnime->addAnimation(Opacity_Anime);

	AllAnime->start();
	connect(AllAnime, &QParallelAnimationGroup::finished, Effect, &Element::deleteLater);
}

void PlayerViewController::UltimateSkill_Saber_Effect_Slow()
{
	std::random_device rd;
	for (int i = 0; i != 3; i++){
		qreal angle = _BulletPicture_Saber->rotation() + (rd() % 180) - 90;
		qreal rad = angle / 180 * PI;
		qreal rad0 = _BulletPicture_Saber->rotation() / 180 * PI;
		qreal rad_delta = rad - rad0;
		qreal offsetX = cos(PI / 4 - rad_delta / 2 - rad0)*cos((PI - rad_delta) / 2)*sqrt(2) * 2 * CELL_SIZE;
		qreal offsetY = -1 * sin(PI / 4 - rad_delta / 2 - rad0)*cos((PI - rad_delta) / 2)*sqrt(2) * 2 * CELL_SIZE;

		Element* Effect = new Element(_BulletPicture_Saber->pos().x() + offsetX, _BulletPicture_Saber->pos().y() + offsetY, 17);
		_Scene->addItem(Effect);
		Effect->setRotation(angle);


		QGraphicsColorizeEffect *Color_Effect = new QGraphicsColorizeEffect(Effect);
		Color_Effect->setColor(QColor(255, 255, 255 - (rd() % 200)));
		//Color_Effect->setStrength(qreal(rd() % 100) / qreal(100));
		Effect->setGraphicsEffect(Color_Effect);

		QParallelAnimationGroup* AllAnime = new QParallelAnimationGroup;

		QPropertyAnimation* Move_Anime = new QPropertyAnimation(Effect, "pos");
		Move_Anime->setDuration(200);
		Move_Anime->setStartValue(QPointF{ _BulletPicture_Saber->pos().x() + offsetX, _BulletPicture_Saber->pos().y() + offsetY });
		qreal dis = (qreal(rd() % 200) + 20);
		Move_Anime->setEndValue(QPointF{ _BulletPicture_Saber->pos().x() + cos(rad) * dis + offsetX, _BulletPicture_Saber->pos().y() + sin(rad) * dis + offsetY });

		QPropertyAnimation* Opacity_Anime = new QPropertyAnimation(Effect, "opacity");
		Opacity_Anime->setDuration(200);
		Opacity_Anime->setStartValue(0.7);
		Opacity_Anime->setEndValue(0);

		AllAnime->addAnimation(Move_Anime);
		AllAnime->addAnimation(Opacity_Anime);

		AllAnime->start();
		connect(AllAnime, &QParallelAnimationGroup::finished, Effect, &Element::deleteLater);
	}
}

void PlayerViewController::UltimateSkill_Saber_Sound_Effect()
{
	_Content->playlist_battle->setCurrentIndex(13);
	_Content->player_battle->play();
}

void PlayerViewController::UltimateSkill_Assassin_Sound_Effect()
{
	_Content->playlist_battle->setCurrentIndex(19);
	_Content->player_battle->play();
}


/**** note ****/
void PlayerViewController::notePossibleMoveTargetMapUnit()//高亮先攻队列front的element其所有移动范围内的mapUnit
{
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	int temp_x = element->_character.get_X();
	int temp_y = element->_character.get_Y();
	//注意！这里修改了步数计算方法
	int temp_speed = element->_character.get_Speed() * 2 + 1;

	////////////////////////////////////////////////////////////////////////////////////
	//BFS部分的变量定义如下：
	//队列首尾分别为head、tail
	//队伍中某个元素i包括以下部分：
	//List_X[i],List_Y[i]:当前元素的X、Y
	//List_Pace[i]：当前元素已经走了多少步，横着算两步，斜着算3步，所以上面speed改成了乘二加一
	//MultiIgnore[x][y]:之前是否来过，判重用的数组
	//deltaX、deltaY：八个方向，0-3是上下左右，4-8是4个对角线 
	////////////////////////////////////////////////////////////////////////////////////
	QVector<int> List_X;
	QVector<int> List_Y;
	QVector<int> List_Pace;
	List_X.push_back(temp_x);
	List_Y.push_back(temp_y);
	List_Pace.push_back(0);
	int head = -1;
	int tail = 0;
	int temp_pace = 0;
	int deltaX[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };
	int deltaY[8] = { 1, 0, -1, 0, -1, 1, -1, 1 };
	bool MultiIgnore[40][40] = { { false } };
	MultiIgnore[temp_x][temp_y] = true;
	//以下为BFS部分
	while (head < tail)
	{
		head++;
		//取出head元素的X、Y、已经走的步数
		temp_x = List_X[head];
		temp_y = List_Y[head];
		temp_pace = List_Pace[head];
		//如果不能再走了就返回
		if (temp_pace + 2> temp_speed) continue;
		//以下是上下左右方向的判断
		for (int i = 0; i < 4; i++)
		{
			//temp_MapUnit是试探的周边MapUnit
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], deltaY[i]);
			//如果超过边界就返回
			if (temp_MapUnit == nullptr) continue;
			//itemBlocking判断这个MapUnit上有没有Element
			Element* itemBlocking = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit->Xcell(), temp_MapUnit->Ycell());
			//如果itemBlocking上有一个Element并且Element还活着/B叔复活中，就把这个视为障碍
			if ((itemBlocking != nullptr) && (!(itemBlocking->_character.Death(_State.Round)))) continue;
			if ((itemBlocking != nullptr) && (itemBlocking->_character.get_Choose() == 6) &&
				(itemBlocking->_character.get_Round() - itemBlocking->_character.get_Round_Death() < 2)) continue;
			//这格是障碍
			if (!temp_MapUnit->CanPass()) continue;
			//已经高亮（之前来过）了
			if (MultiIgnore[temp_x + deltaX[i]][temp_y + deltaY[i]]) continue;

			//下面是往tail加这格的信息
			List_X.push_back(temp_x + deltaX[i]);
			List_Y.push_back(temp_y + deltaY[i]);
			List_Pace.push_back(temp_pace + 2);
			tail++;
			MultiIgnore[List_X[tail]][List_Y[tail]] = true;
			temp_MapUnit->note();
		}
		//如果不能斜着走了就返回
		if (temp_pace + 3> temp_speed) continue;
		//以下是对角线4方向的判断
		for (int i = 4; i < 8; i++)
		{
			//以下参考上面上下左右那段
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], deltaY[i]);
			if (temp_MapUnit == nullptr) continue;
			Element* itemBlocking = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit->Xcell(), temp_MapUnit->Ycell());
			if ((itemBlocking != nullptr) && (!(itemBlocking->_character.Death(_State.Round)))) continue;
			if ((itemBlocking != nullptr) && (itemBlocking->_character.get_Choose() == 6) &&
				(itemBlocking->_character.get_Round() - itemBlocking->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit->CanPass()) continue;
			if (MultiIgnore[temp_x + deltaX[i]][temp_y + deltaY[i]]) continue;

			//下面两段判断能不能直接走过去，如（0，0）->（1，1），判断（1，0）和（0，1）是不是障碍
			//这两段只比上面少了一句，不需要判断是否走过（1，0）和（0，1）【也就是不用判断高亮MultiIgnore】
			MapUnit* temp_MapUnit_noX = _Content->Map()->get_MapUnit_around(temp_x, temp_y, 0, deltaY[i]);
			if (temp_MapUnit_noX == nullptr) continue;
			Element* itemBlocking_noX = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit_noX->Xcell(), temp_MapUnit_noX->Ycell());
			if ((itemBlocking_noX != nullptr) && (!(itemBlocking_noX->_character.Death(_State.Round)))) continue;
			if ((itemBlocking_noX != nullptr) && (itemBlocking_noX->_character.get_Choose() == 6) &&
				(itemBlocking_noX->_character.get_Round() - itemBlocking_noX->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit_noX->CanPass()) continue;

			MapUnit* temp_MapUnit_noY = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], 0);
			if (temp_MapUnit_noY == nullptr) continue;
			Element* itemBlocking_noY = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit_noY->Xcell(), temp_MapUnit_noY->Ycell());
			if ((itemBlocking_noY != nullptr) && (!(itemBlocking_noY->_character.Death(_State.Round)))) continue;
			if ((itemBlocking_noY != nullptr) && (itemBlocking_noY->_character.get_Choose() == 6) &&
				(itemBlocking_noY->_character.get_Round() - itemBlocking_noY->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit_noY->CanPass()) continue;

			List_X.push_back(temp_x + deltaX[i]);
			List_Y.push_back(temp_y + deltaY[i]);
			List_Pace.push_back(temp_pace + 3);
			tail++;
			MultiIgnore[List_X[tail]][List_Y[tail]] = true;
			temp_MapUnit->note();
		}
	}
}

bool PlayerViewController::notePossibleAttackTargetElement()
{
	bool AttackEnemy{ false };
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	for (int i = 1; i != ELEMENTS_NUM + 1; i++){
		Element* enemy;
		if (_State.IsHost)
			enemy = _Content->Elements()->get_Element(-i);
		else
			enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= element->_character.get_Range_Inc()) &&
			(!enemy->_character.Death(_State.Round)))
		{
			enemy->attack_note();
			AttackEnemy = true;
		}
	}
	return AttackEnemy;
}

bool PlayerViewController::noteUltimateSkillTarget_Saber()
{
	bool AttackEnemy{ false };
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy;
		if (_State.IsHost)
			enemy = _Content->Elements()->get_Element(-i);
		else
			enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 10) &&
			(!enemy->_character.Death(_State.Round)))
		{
			enemy->attack_note();
			AttackEnemy = true;
		}
	}
	return AttackEnemy;
}

bool PlayerViewController::noteUltimateSkillTarget_Archer()
{
	bool AttackEnemy{ false };
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy;
		if (_State.IsHost)
			enemy = _Content->Elements()->get_Element(-i);
		else
			enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 2) &&
			(!enemy->_character.Death(_State.Round)))
		{
			enemy->attack_note();
			AttackEnemy = true;
		}
	}
	return AttackEnemy;

}

void PlayerViewController::noteUltimateSkillTarget_Caster()
{
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	int temp_x = element->_character.get_X();
	int temp_y = element->_character.get_Y();
	//注意！这里修改了步数计算方法
	int temp_speed = 31;

	////////////////////////////////////////////////////////////////////////////////////
	//BFS部分的变量定义如下：
	//队列首尾分别为head、tail
	//队伍中某个元素i包括以下部分：
	//List_X[i],List_Y[i]:当前元素的X、Y
	//List_Pace[i]：当前元素已经走了多少步，横着算两步，斜着算3步，所以上面speed改成了乘二加一
	//MultiIgnore[x][y]:之前是否来过，判重用的数组
	//deltaX、deltaY：八个方向，0-3是上下左右，4-8是4个对角线 
	////////////////////////////////////////////////////////////////////////////////////
	QVector<int> List_X;
	QVector<int> List_Y;
	QVector<int> List_Pace;
	List_X.push_back(temp_x);
	List_Y.push_back(temp_y);
	List_Pace.push_back(0);
	int head = -1;
	int tail = 0;
	int temp_pace = 0;
	int deltaX[8] = { 0, 1, 0, -1, -1, -1, 1, 1 };
	int deltaY[8] = { 1, 0, -1, 0, -1, 1, -1, 1 };
	bool MultiIgnore[40][40] = { { false } };
	MultiIgnore[temp_x][temp_y] = true;
	//以下为BFS部分
	while (head < tail)
	{
		head++;
		//取出head元素的X、Y、已经走的步数
		temp_x = List_X[head];
		temp_y = List_Y[head];
		temp_pace = List_Pace[head];
		//如果不能再走了就返回
		if (temp_pace + 2> temp_speed) continue;
		//以下是上下左右方向的判断
		for (int i = 0; i < 4; i++)
		{
			//temp_MapUnit是试探的周边MapUnit
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], deltaY[i]);
			//如果超过边界就返回
			if (temp_MapUnit == nullptr) continue;
			//itemBlocking判断这个MapUnit上有没有Element
			Element* itemBlocking = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit->Xcell(), temp_MapUnit->Ycell());
			//如果itemBlocking上有一个Element并且Element还活着/B叔复活中，就把这个视为障碍
			if ((itemBlocking != nullptr) && (!(itemBlocking->_character.Death(_State.Round)))) continue;
			if ((itemBlocking != nullptr) && (itemBlocking->_character.get_Choose() == 6) &&
				(itemBlocking->_character.get_Round() - itemBlocking->_character.get_Round_Death() < 2)) continue;
			//这格是障碍
			if (!temp_MapUnit->CanPass()) continue;
			//已经高亮（之前来过）了
			if (MultiIgnore[temp_x + deltaX[i]][temp_y + deltaY[i]]) continue;

			//下面是往tail加这格的信息
			List_X.push_back(temp_x + deltaX[i]);
			List_Y.push_back(temp_y + deltaY[i]);
			List_Pace.push_back(temp_pace + 2);
			tail++;
			MultiIgnore[List_X[tail]][List_Y[tail]] = true;
			temp_MapUnit->note();
		}
		//如果不能斜着走了就返回
		if (temp_pace + 3> temp_speed) continue;
		//以下是对角线4方向的判断
		for (int i = 4; i < 8; i++)
		{
			//以下参考上面上下左右那段
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], deltaY[i]);
			if (temp_MapUnit == nullptr) continue;
			Element* itemBlocking = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit->Xcell(), temp_MapUnit->Ycell());
			if ((itemBlocking != nullptr) && (!(itemBlocking->_character.Death(_State.Round)))) continue;
			if ((itemBlocking != nullptr) && (itemBlocking->_character.get_Choose() == 6) &&
				(itemBlocking->_character.get_Round() - itemBlocking->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit->CanPass()) continue;
			if (MultiIgnore[temp_x + deltaX[i]][temp_y + deltaY[i]]) continue;

			//下面两段判断能不能直接走过去，如（0，0）->（1，1），判断（1，0）和（0，1）是不是障碍
			//这两段只比上面少了一句，不需要判断是否走过（1，0）和（0，1）【也就是不用判断高亮MultiIgnore】
			MapUnit* temp_MapUnit_noX = _Content->Map()->get_MapUnit_around(temp_x, temp_y, 0, deltaY[i]);
			if (temp_MapUnit_noX == nullptr) continue;
			Element* itemBlocking_noX = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit_noX->Xcell(), temp_MapUnit_noX->Ycell());
			if ((itemBlocking_noX != nullptr) && (!(itemBlocking_noX->_character.Death(_State.Round)))) continue;
			if ((itemBlocking_noX != nullptr) && (itemBlocking_noX->_character.get_Choose() == 6) &&
				(itemBlocking_noX->_character.get_Round() - itemBlocking_noX->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit_noX->CanPass()) continue;

			MapUnit* temp_MapUnit_noY = _Content->Map()->get_MapUnit_around(temp_x, temp_y, deltaX[i], 0);
			if (temp_MapUnit_noY == nullptr) continue;
			Element* itemBlocking_noY = this->_Content->Elements()->get_Element_with_pos(temp_MapUnit_noY->Xcell(), temp_MapUnit_noY->Ycell());
			if ((itemBlocking_noY != nullptr) && (!(itemBlocking_noY->_character.Death(_State.Round)))) continue;
			if ((itemBlocking_noY != nullptr) && (itemBlocking_noY->_character.get_Choose() == 6) &&
				(itemBlocking_noY->_character.get_Round() - itemBlocking_noY->_character.get_Round_Death() < 2)) continue;
			if (!temp_MapUnit_noY->CanPass()) continue;

			List_X.push_back(temp_x + deltaX[i]);
			List_Y.push_back(temp_y + deltaY[i]);
			List_Pace.push_back(temp_pace + 3);
			tail++;
			MultiIgnore[List_X[tail]][List_Y[tail]] = true;
			temp_MapUnit->note();
		}
	}
}


/**** operate ****/
void PlayerViewController::undo()//右键undo，即取消IsChoosingMoveTarget/IsChoosingAttackTarget的状态
{
	resetOperate();
	if (_State.IsChoosingMoveTarget){
		_State.IsChoosingMoveTarget = false;
		_Content->Map()->restoreAllMapUnitColor();
	}
	if (_State.IsChoosingAttackTarget){
		_State.IsChoosingAttackTarget = false;
		_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
	}
	if (_State.WhileUltimateSkilling != 0){
		_State.WhileUltimateSkilling = 0;
		_Content->Map()->restoreAllMapUnitColor();
		_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
	}
}

void PlayerViewController::Move(MapUnit* target)//移动先攻队列front的element到指定target
{
	if (target->get_note_state())
	{
		resetOperate();

		_State.IsChoosingMoveTarget = false;
		_Content->Map()->restoreAllMapUnitColor();
		_State.HasMoved = true;

		QVariantMap answer;
		answer.insert("state", "battle");
		answer.insert("action", "move");
		answer.insert("piece", ActionPiece);
		answer.insert("x", target->Xcell());
		answer.insert("y", target->Ycell());
		answer.insert("from", tcpPoint->userName);
		answer.insert("to", tcpPoint->enemyName);
		QString json = QJsonDocument::fromVariant(answer).toJson();
		tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
	}
}

void PlayerViewController::Attack(int index)
{
	Element* enemy = _Content->Elements()->get_Element(index);
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	if (enemy->get_note_state()){
		resetOperate();
		_State.IsChoosingAttackTarget = false;
		//attack animation//

		QVariantMap answer;
		answer.insert("state", "battle");
		answer.insert("action", "attack");
		answer.insert("self", ActionPiece);
		answer.insert("enemy", index);
		answer.insert("from", tcpPoint->userName);
		answer.insert("to", tcpPoint->enemyName);
		QString json = QJsonDocument::fromVariant(answer).toJson();
		tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());

		_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
		_State.HasAttacked = true;
	}
}

void PlayerViewController::UltimateSkill_Saber(int index)
{
	Element* enemy = _Content->Elements()->get_Element(index);
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	if (enemy->get_note_state()){
		resetOperate();
		_State.WhileUltimateSkilling = 0;
		_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
		_State.HasUltimateSkilled = true;
		//attack animation//
		element->_character.change_Num_Strokes();
		QVariantMap answer;
		answer.insert("state", "battle");
		answer.insert("action", "ult");
		answer.insert("self", ActionPiece);
		answer.insert("enemy", index);
		answer.insert("from", tcpPoint->userName);
		answer.insert("to", tcpPoint->enemyName);
		QString json = QJsonDocument::fromVariant(answer).toJson();
		tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());

		_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
	}
}

void PlayerViewController::UltimateSkill_Archer()
{
	resetOperate();
	_State.HasUltimateSkilled = true;
	QVariantMap answer;
	answer.insert("state", "battle");
	answer.insert("action", "ult");
	answer.insert("piece", ActionPiece);
	answer.insert("from", tcpPoint->userName);
	answer.insert("to", tcpPoint->enemyName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());

		//_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
}

void PlayerViewController::UltimateSkill_Rider(){
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	QVariantList element_in_range;
	QVector<Element*> element_vector;
	_State.HasAttacked = true;
	//要特技可以加在这里

	//找到距离内可用的东西
	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 3) && (!enemy->_character.Death(_State.Round)))
		if (enemy != element)
		{
			element_in_range.append(i);
			element_vector.push_back(enemy);
			enemy->tomb_note();
		}
	}

	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy = _Content->Elements()->get_Element(-i);
		if ((element->_character.get_Distance(enemy->_character) <= 3) && (!enemy->_character.Death(_State.Round)))
		if (enemy != element)
		{
			element_in_range.append(-i);
			element_vector.push_back(enemy);
			enemy->tomb_note();
		}
	}

	QVariantMap answer;
	answer.insert("state", "battle");
	answer.insert("action", "ult");
	answer.insert("piece", ActionPiece);
	answer.insert("list", element_in_range);
	answer.insert("from", tcpPoint->userName);
	answer.insert("to", tcpPoint->enemyName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void PlayerViewController::UltimateSkill_Caster(MapUnit*target){
	if (target->get_note_state())
	{
		Element* element = _Content->Elements()->get_Element(ActionPiece);
		resetOperate();

		_State.WhileUltimateSkilling = 0;
		_Content->Map()->restoreAllMapUnitColor();
		_State.HasUltimateSkilled = true;

		QVariantMap answer;
		answer.insert("state", "battle");
		answer.insert("action", "ult");
		answer.insert("piece", ActionPiece);
		answer.insert("x", target->Xcell());
		answer.insert("y", target->Ycell());
		answer.insert("from", tcpPoint->userName);
		answer.insert("to", tcpPoint->enemyName);
		QString json = QJsonDocument::fromVariant(answer).toJson();
		tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());


	}
}

void PlayerViewController::Cancel()
{
	Next();//无条件直接next
}


/**** slot ****/
void PlayerViewController::battleData(QVariantMap result)
{
	QString action = result["action"].toString();
	if (action == "move" ||
		(result["action"].toString() == "ult" &&
		(result["piece"].toInt() == 5 || result["piece"].toInt()==-5))){
		if (action == "move"){
			MoveElement(result["piece"].toInt(),result["x"].toInt(), result["y"].toInt());
		}
		else{
			casterAnimation(_Content->Elements()->get_Element(result["piece"].toInt()), result["x"].toInt(), result["y"].toInt());
		}
	}
	else if (action == "attack" || (result["action"].toString() == "ult" && (result["self"].toInt() == 1 || result["self"].toInt() == -1))){
		//伤害不在本地存储，只是显示出来，不过本地还是要存储生命值
		int shouPiece = result["enemy"].toInt();
		int gongPiece = result["self"].toInt();
		//如果是Saber或Archer则把是否能大招发过来
		if (gongPiece == 1 || gongPiece == -1){
			Element *element = _Content->Elements()->get_Element(gongPiece);
			element->_character.set_Num_Strokes(result["stroke1"].toInt());
		}
		//saber的大招和attack除了动画不同其他的都相似
		if (result["action"].toString() == "attack"){
			attackAnimation(_Content->Elements()->get_Element(shouPiece), _Content->Elements()->get_Element(gongPiece), result["damage"].toInt(), result["death"].toBool(),result["AC"].toInt());
		}
		else if (gongPiece == 1 || gongPiece == -1){
			saberAnimation(_Content->Elements()->get_Element(shouPiece), _Content->Elements()->get_Element(gongPiece), result["damage"].toInt(), result["death"].toBool());
		}
		if (result["victory"].toBool()){
			gameOver(result["result"].toInt());
		}
	}
	else if (action == "next"){
		if (result["host"].toBool()){
			_State.IsHost = result["ishost"].toBool();
			if (!_State.IsHost){
				this->centerOn(_Content->Elements()->get_Element(-1));
			}
		}
		if (result["newround"].toBool()){
			_State.Round = result["round"].toInt();
			if (_State.Round != 1){
				newRoundAnimation();
			}
			else{
				QTimer::singleShot(3000, this,&PlayerViewController::newRoundAnimation);
			}
			newRound(result["newlist"].toList());
		}
		else{
			_State.AttackSequence.clear();
			for (auto i : result["newlist"].toList()){
				_State.AttackSequence.push_back(i.toInt());
			}
			QTimer::singleShot(500, _BattleInfo, &PanelBattleInfo::RefreshAllBattleInfo);
		}
		ActionPiece = _State.AttackSequence.front();
		if (result["my"].toBool()){
			if (gamestart){
				_Content->Elements()->get_Element(ActionPiece)->restore();
			}
			if (result["newround"].toBool()){
				QTimer::singleShot(1500, _Content->Elements()->get_Element(ActionPiece), &Element::move_note);
			}
			else{
				_Content->Elements()->get_Element(ActionPiece)->move_note();
			}
		}
	}
	else if (action == "ult"){
		if (result["piece"].toInt() == 3){
			riderAnimation(result["list"].toList(), result["death_list"].toList());
		}
		else if (result["piece"].toInt() == 2 || result["piece"].toInt() == -2){
			Element* element = _Content->Elements()->get_Element(result["piece"].toInt());
			if (element->_character.get_AB() == 8) Remote_Archer(); else Melee_Archer();
			archerAnimation(element->_character.get_AB() == 8);
		}
	}
}

void  PlayerViewController::gameOver(int over)
{
	QString text;
	if (over == 1){
		text = "WIN";
	}
	else{
		text = "LOSE";
	}
	QLabel* DamageText = new QLabel(this);
	DamageText->setGeometry(VIEW_WIDTH / 2 - 200, VIEW_HEIGHT / 2 - 250, 500, 135);
	DamageText->setFont(QFont("Algerian", 150, QFont::Bold));
	DamageText->setText(text);
	QGraphicsColorizeEffect *_ColorEffect = new QGraphicsColorizeEffect(DamageText);
	_ColorEffect->setColor(QColor(255, 204, 0));
	_ColorEffect->setStrength(1);
	DamageText->setGraphicsEffect(_ColorEffect);
	QTimer::singleShot(2000, DamageText, &QLabel::show);
	QTimer::singleShot(5000, DamageText, &QLabel::deleteLater);


	QTimer *count_down = new QTimer(this);
	count_down->start(5000);
	connect(count_down, &QTimer::timeout, this, &PlayerViewController::QuitGame_Signal);
	disconnect(tcpPoint, 0, 0, 0);
}

void PlayerViewController::ShowMenu()
{
	emit ShowMenu_ViewToMainWindow_Signal();
	resetOperate();
}

void PlayerViewController::TogglePanelBattleInfo()
{
	if (_BattleInfo->isHidden()){
		_BattleInfo->show();
		resetOperate();
	}
	else if (!_BattleInfo->isHidden()){
		_BattleInfo->hide();
		resetOperate();
	}
}


void PlayerViewController::btMovePressed()//slot
{
	_State.IsChoosingMoveTarget = true;
	resetOperate();
	notePossibleMoveTargetMapUnit();//变色，加MapUnit鼠标指针变换
}

void PlayerViewController::btAttackPressed()//slot
{

	_State.IsChoosingAttackTarget = true;
	resetOperate();
	if (!notePossibleAttackTargetElement()){
		undo();
	}

}

void PlayerViewController::btCancelPressed()//slot
{
	resetOperate();
	Cancel();
}

void PlayerViewController::btUltimateSkillPressed()//slot
{
	Element* element = _Content->Elements()->get_Element(ActionPiece);
	if (!element->_character.if_Strokes()) return;


	switch (element->_character.get_Choose())
	{
	case 1:
	{
			  _State.WhileUltimateSkilling = 1;
			  if (!noteUltimateSkillTarget_Saber())  undo();
			  //写大招
			  break;
	}
	case 2:
	{
			  //切换形态
			  UltimateSkill_Archer();
			  break;
	}
	case 3:
	{
			  UltimateSkill_Rider();
			  break;
	}
	case 5:
	{
			  //任意门
			  _State.WhileUltimateSkilling = 5;
			  noteUltimateSkillTarget_Caster();
			  break;
	}
	}
	resetOperate();

}

void PlayerViewController::lose(){
	disconnect(tcpPoint, 0, 0, 0);
	QVariantMap answer;
	answer.insert("state", "lose");
	answer.insert("from", tcpPoint->userName);
	answer.insert("to", tcpPoint->enemyName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}


/**** event ****/
void PlayerViewController::wheelEvent(QWheelEvent* e)
{
	//if (this->isInteractive()){
	//	resetOperate();
	//	QGraphicsView::wheelEvent(e);//此句不能少，否则会由于重载后不再运行原本view的wheelevent，进而无法滑动
	//}
}

void PlayerViewController::mousePressEvent(QMouseEvent *e)//此处mousePressEvent只重点处理operate的创建，其余内容放在Move和Attack等函数中
{
	if (this->isInteractive()){

		QGraphicsItem *itemSelected = this->itemAt(e->x(), e->y());
		int index = _Content->Elements()->get_item_index_in_ElementPool(itemSelected);

		if (e->button() == Qt::LeftButton)
		{ //点击的是左键
			if (!_State.IsChoosingMoveTarget && !_State.IsChoosingAttackTarget && (_State.WhileUltimateSkilling == 0))
			{//处于最基本的状态，没有点击过任何operate的按钮
				if (itemSelected != NULL && index != 0 &&
					(((index > 0 && _State.IsHost) || (index < 0 && !_State.IsHost)))
					&& (index==ActionPiece))
				{
					resetOperate();
					//新增
					Element* element = _Content->Elements()->get_Element(ActionPiece);
					bool EX_state = true;
					if (abs(index) == 1 || abs(index) == 3 || abs(index) == 5)
						EX_state = element->_character.get_Num_Strokes() != 0 ? true : false;//
					if (abs(index) == 6)
						EX_state = element->_character.get_Whether_Strokes() == 0 ? true : false;//

					QPointF pos_operate = this->mapFromScene(QPointF(itemSelected->pos()));
					if (pos_operate.x() + 45 > VIEW_WIDTH - 126 && pos_operate.y() + 45 > VIEW_HEIGHT - 126){
						_Operate = new PanelOperate(pos_operate.x() - 121, pos_operate.y() - 121, this->_State, Operate_type::Left_Top, EX_state, this);
					}
					if (pos_operate.x() + 45 <= VIEW_WIDTH - 126 && pos_operate.y() + 45 > VIEW_HEIGHT - 126){
						_Operate = new PanelOperate(pos_operate.x() + 45, pos_operate.y() - 121, this->_State, Operate_type::Right_Top, EX_state, this);
					}
					if (pos_operate.x() + 45 > VIEW_WIDTH - 126 && pos_operate.y() + 45 <= VIEW_HEIGHT - 126){
						_Operate = new PanelOperate(pos_operate.x() - 121, pos_operate.y() + 45, this->_State, Operate_type::Left_Bottom, EX_state, this);
					}
					if (pos_operate.x() + 45 <= VIEW_WIDTH - 126 && pos_operate.y() + 45 <= VIEW_HEIGHT - 126){
						_Operate = new PanelOperate(pos_operate.x() + 45, pos_operate.y() + 45, this->_State, Operate_type::Right_Bottom, EX_state, this);
					}
					connect(_Operate, &PanelOperate::btMovePressed_Signal, this, &PlayerViewController::btMovePressed);
					connect(_Operate, &PanelOperate::btAttackPressed_Signal, this, &PlayerViewController::btAttackPressed);
					connect(_Operate, &PanelOperate::btUltimateSkillPressed_Signal, this, &PlayerViewController::btUltimateSkillPressed);
					connect(_Operate, &PanelOperate::btCancelPressed_Signal, this, &PlayerViewController::btCancelPressed);

				}
				else
					resetOperate();
			}
			else if (_State.IsChoosingMoveTarget)
			{
				MapUnit* unit = _Content->Map()->get_MapUnit_in_MapInfo(itemSelected);
				if (unit != nullptr)//任意一块MapUnit
					Move(unit);
			}
			else if (_State.IsChoosingAttackTarget)
			{
				if ((index < 0 && _State.IsHost) || (index > 0 && !_State.IsHost))//任意敌人element
					Attack(index);

			}
			else if (_State.WhileUltimateSkilling != 0)
			{
				switch (_State.WhileUltimateSkilling)
				{
				case 1:
				{
						  if ((index < 0 && _State.IsHost) || (index > 0 && !_State.IsHost))//任意敌人element
							  UltimateSkill_Saber(index);
						  break;
				}
				case 5:
				{
						  MapUnit* unit = _Content->Map()->get_MapUnit_in_MapInfo(itemSelected);
						  if (unit != nullptr)//任意一块MapUnit
							  UltimateSkill_Caster(unit);
						  break;
				}
				}

			}

		}
		else if (e->button() == Qt::RightButton)//点击右键，undo
			undo();

		QGraphicsView::mousePressEvent(e);
	}
}

void PlayerViewController::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A)
	{
		viewMoveTimer(1);
	}
	if (event->key() == Qt::Key_D)
	{
		viewMoveTimer(2);
	}
	if (event->key() == Qt::Key_W)
	{
		viewMoveTimer(3);
	}
	if (event->key() == Qt::Key_S)
	{
		viewMoveTimer(4);
	}
	resetOperate();
}

void PlayerViewController::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A || event->key() == Qt::Key_D || event->key() == Qt::Key_W || event->key() == Qt::Key_S){
		viewMoveTimer(0);
		this->setFocus();
	}
}

void PlayerViewController::viewMoveTimer(int type)
{
	if (_timer == nullptr){
		_timer = new QTimer;
		switch (type)
		{
		case 1:
			connect(_timer, &QTimer::timeout, this, &PlayerViewController::moveView_Left); break;
		case 2:
			connect(_timer, &QTimer::timeout, this, &PlayerViewController::moveView_Right); break;
		case 3:
			connect(_timer, &QTimer::timeout, this, &PlayerViewController::moveView_Up); break;
		case 4:
			connect(_timer, &QTimer::timeout, this, &PlayerViewController::moveView_Down); break;
		default:
			break;
		}
		_timer->start(16);
	}
	else if (_timer != nullptr && type == 0){
		_timer->stop();
		_timer->deleteLater();
		_timer = nullptr;
	}
}

void PlayerViewController::moveView_Left()
{
	centerOn(mapToScene(rect().center().x() - 20, rect().center().y()));
}

void PlayerViewController::moveView_Right()
{
	centerOn(mapToScene(rect().center().x() + 20, rect().center().y()));
}

void PlayerViewController::moveView_Up()
{
	centerOn(mapToScene(rect().center().x(), rect().center().y() - 20));
}

void PlayerViewController::moveView_Down()
{
	centerOn(mapToScene(rect().center().x(), rect().center().y() + 20));

}


/**** M_Element_Animation ****/
M_Element_Animation::M_Element_Animation(Element* ActionElement)
{
	_ActionElement = ActionElement;
}

M_Element_Animation::M_Element_Animation(Element* ActionElement, int Damage)
{
	_ActionElement = ActionElement;
	_Damage = Damage;
}

M_Element_Animation::M_Element_Animation(Element* ActionElement, int Round, PanelHeadUp* HeadUp)
{
	_ActionElement = ActionElement;
	_Round = Round;
	_HeadUp = HeadUp;
}

void M_Element_Animation::Emit_Hide_Signal()
{
	_ActionElement->hide();
}

void M_Element_Animation::Emit_Damage_Signal()
{
	emit Damage_signal(_Damage);
}

void M_Element_Animation::Emit_Set_Health_Signal()
{
	_HeadUp->set_health(_ActionElement->Index(), _ActionElement->_character.get_HP(), _ActionElement->_character.get_Max_HP(), _ActionElement->_character.Death(_Round));
}

void M_Element_Animation::Emit_Tomb_Note_Signal()
{
	_ActionElement->tomb_note();
}