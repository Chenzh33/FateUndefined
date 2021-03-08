#include "SinglePlayerController.h"

SinglePlayerController::SinglePlayerController(QGraphicsScene* scene, GameContent* content, int ailevel, QWidget *parent, bool IsHost) : QGraphicsView(parent)
{
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
	srand(time(nullptr));
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
	_State.AILevel = ailevel;
	_State.Round = 0;

	//设置视角
	if (IsHost)
		this->centerOn(_Content->Elements()->get_Element(1));
	else
		this->centerOn(_Content->Elements()->get_Element(-1));

	//初始化抬头面板
	initBattleInfo();
	initHeadUp();


	QTimer::singleShot(5500, this, &SinglePlayerController::initNewRound);
}

SinglePlayerController::~SinglePlayerController()
{

}


/**** init ****/
void SinglePlayerController::initHeadUp()
{
	_HeadUp = new PanelHeadUp(this);
	QObject::connect(_HeadUp, &PanelHeadUp::ShowMenu_HeadUpToView_Signal, this, &SinglePlayerController::ShowMenu);
	QObject::connect(_HeadUp, &PanelHeadUp::ShowPanelBattleInfo_Signal, this, &SinglePlayerController::TogglePanelBattleInfo);
}

void SinglePlayerController::initBattleInfo()
{
	_BattleInfo = new PanelBattleInfo(_Content, &_State, this);
	_BattleInfo->hide();
}

void SinglePlayerController::initQueue()
{
	QVector<int> ChooseSide;
	ChooseSide.push_back(rand() % 2);
	ChooseSide.push_back(1 - ChooseSide[0]);
	QVector<int> Miku, Rin;

	for (int i = 0; i < ELEMENTS_NUM; i++)
	{
		Miku.push_back((rand() % 20 + Initiative[i]) * 100 + Initiative[i] * 10 + ChooseSide[0]);
		Rin.push_back((rand() % 20 + Initiative[i]) * 100 + Initiative[i] * 10 + ChooseSide[1]);
	}
	for (int i = 0; i < ELEMENTS_NUM * 2; i++)
	{
		int Miku_max{ 0 }, Rin_max{ 0 };
		for (int j = 0; j < ELEMENTS_NUM; j++)
		{
			if (Miku[j] > Miku[Miku_max]) Miku_max = j;
			if (Rin[j] > Rin[Rin_max]) Rin_max = j;
		}
		int Max{ Miku[Miku_max] > Rin[Rin_max] ? Miku_max + 1 : (-1 - Rin_max) };
		if (!_Content->Elements()->get_Element(Max)->_character.Death(_State.Round))
			_State.AttackSequence.push_back(Max);
		if (Max > 0) Miku[Max - 1] = -1;
		else Rin[-Max - 1] = -1;

		Element* element = _Content->Elements()->get_Element(Max);
		element->_character.set_Round(_State.Round);
		if ((_Content->Elements()->get_Element(Max)->_character.get_Choose() == 6) &&
			(_Content->Elements()->get_Element(Max)->_character.get_Whether_Strokes() == 1) &&
			(_Content->Elements()->get_Element(Max)->_character.get_Round_Death() == _State.Round - 2))
		{
			_HeadUp->set_health(element->Index(), element->_character.get_HP(), element->_character.get_Max_HP(), element->_character.Death(_State.Round), true);
			element->alive_note();
		}
	}

}

void SinglePlayerController::initNewRound()
{
	_State.Round++;
	initQueue();
	_State.HasMoved = false;
	_State.HasAttacked = false;
	_State.HasUltimateSkilled = false;

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



	QTimer::singleShot(1500, _Content->Elements()->get_Element(_State.AttackSequence.front()), &Element::move_note);
	QTimer::singleShot(1500, _BattleInfo, &PanelBattleInfo::RefreshNewRoundInfo);
	QTimer::singleShot(2500, this, &SinglePlayerController::SinglePlayerAI);
	
}


/**** game control ****/
bool SinglePlayerController::CheckIsNextAttacker(int index)//检查当前index的element是否是先攻队列的front
{
	if (_State.AttackSequence.front() == index)
		return true;
	else
		return false;
}

void SinglePlayerController::Next()//先攻队列出列，得到下一个待操作的element
{
	//新增，用于判断剩余队列中是否存在在本轮死亡的Element，如果有，将其pop掉

	_Content->Elements()->get_Element(_State.AttackSequence.front())->restore();
	do{
		_State.AttackSequence.pop_front();
		if (_State.AttackSequence.empty()){
			initNewRound();
			return;
		}
	} while (_Content->Elements()->get_Element(_State.AttackSequence.front())->_character.Death(_State.Round));

	_State.HasMoved = false;
	_State.HasAttacked = false;
	_State.HasUltimateSkilled = false;

	QTimer::singleShot(500, _Content->Elements()->get_Element(_State.AttackSequence.front()), &Element::move_note);
	QTimer::singleShot(500, _BattleInfo, &PanelBattleInfo::RefreshAllBattleInfo);
	QTimer::singleShot(500, this, &SinglePlayerController::SinglePlayerAI);

}

void SinglePlayerController::CheckVictory()
{
	bool flag_Miku = true, flag_Rin = true;
	for (int i = 0; i != ELEMENTS_NUM; i++)
	if (!_Content->Elements()->get_Element(i + 1)->_character.Death(_State.Round)) flag_Miku = false;
	if ((_Content->Elements()->get_Element(6)->_character.get_Whether_Strokes() == 1) &&
		(_Content->Elements()->get_Element(6)->_character.get_Round() - _Content->Elements()->get_Element(6)->_character.get_Round_Death() < 2))
		flag_Miku = false;
	for (int i = 0; i != ELEMENTS_NUM; i++)
	if (!_Content->Elements()->get_Element(-(i + 1))->_character.Death(_State.Round)) flag_Rin = false;
	if ((_Content->Elements()->get_Element(-6)->_character.get_Whether_Strokes() == 1) &&
		(_Content->Elements()->get_Element(-6)->_character.get_Round() - _Content->Elements()->get_Element(-6)->_character.get_Round_Death() < 2))
		flag_Rin = false;
	QString text;
	if (flag_Miku){
		text = "BLUE WIN";
	}
	else if (flag_Rin){
		text = "YELLOW WIN";
	}

	if (flag_Miku || flag_Rin){
		QLabel* DamageText = new QLabel(this);
		DamageText->setGeometry(VIEW_WIDTH / 2 - 325, VIEW_HEIGHT / 2 - 250, 650, 135);
		DamageText->setFont(QFont("Algerian", 80, QFont::Bold));
		DamageText->setText(text);
		QGraphicsColorizeEffect *_ColorEffect = new QGraphicsColorizeEffect(DamageText);
		_ColorEffect->setColor(QColor(255, 204, 0));
		_ColorEffect->setStrength(1);
		DamageText->setGraphicsEffect(_ColorEffect);
		QTimer::singleShot(3000, DamageText, &QLabel::deleteLater);
		DamageText->show();

		QTimer *count_down = new QTimer(this);
		count_down->start(5000);
		connect(count_down, &QTimer::timeout, this, &SinglePlayerController::QuitGame_Signal);
	}
}


/**** note ****/
void SinglePlayerController::notePossibleMoveTargetMapUnit()//高亮先攻队列front的element其所有移动范围内的mapUnit
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
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

bool SinglePlayerController::notePossibleAttackTargetElement()
{
	bool AttackEnemy{ false };
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	for (int i = 1; i != ELEMENTS_NUM + 1; i++){

		Element* enemy = _Content->Elements()->get_Element(-i);
		if (enemy->Index()*element->Index() > 0) enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= element->_character.get_Range_Inc()) &&
			(!enemy->_character.Death(_State.Round)))
		{
			enemy->attack_note();
			AttackEnemy = true;
		}
	}
	return AttackEnemy;
}

bool SinglePlayerController::noteUltimateSkillTarget_Saber()
{
	bool AttackEnemy{ false };
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy;
		if (element->Index() > 0)
			enemy = _Content->Elements()->get_Element(-i);
		else
			enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 10) && //changed
			(!enemy->_character.Death(_State.Round)))
		{
			enemy->attack_note();
			AttackEnemy = true;
		}
	}
	return AttackEnemy;
}

void SinglePlayerController::noteUltimateSkillTarget_Caster()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
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


/**** assistant ****/
void SinglePlayerController::resetOperate()//删除operate
{
	if (_Operate != nullptr){
		_Operate->deleteLater();
		_Operate = nullptr;
	}
	this->setFocus();
}

void SinglePlayerController::show_damage(int damage)
{
	QString text{ std::to_string(damage).c_str() };
	if (text == "0") text = "MISS";
	QLabel* DamageText = new QLabel(this);
	DamageText->setGeometry(VIEW_WIDTH / 2 - 200, VIEW_HEIGHT / 2 - 100, 500, 135);
	DamageText->setFont(QFont("Algerian", 150, QFont::Bold));
	DamageText->setText(text);
	QGraphicsColorizeEffect *_ColorEffect = new QGraphicsColorizeEffect(DamageText);
	_ColorEffect->setColor(QColor(255, 204, 0));
	_ColorEffect->setStrength(1);
	DamageText->setGraphicsEffect(_ColorEffect);

	QTimer::singleShot(1000, DamageText, &QLabel::deleteLater);
	DamageText->show();
	QPropertyAnimation* Upward_Anime = new QPropertyAnimation(DamageText, "geometry");
	Upward_Anime->setDuration(1000);
	Upward_Anime->setStartValue(DamageText->geometry());
	Upward_Anime->setEndValue(QRect(DamageText->geometry().left(), DamageText->geometry().top() - DamageText->geometry().height() * 1 / 2, DamageText->geometry().width(), DamageText->geometry().height()));
	Upward_Anime->start();
}

void SinglePlayerController::Melee_Archer()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

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

void SinglePlayerController::Remote_Archer()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

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

void SinglePlayerController::UltimateSkill_Saber_Effect_Fast()
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

void SinglePlayerController::UltimateSkill_Saber_Effect_Slow()
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

void SinglePlayerController::UltimateSkill_Saber_Sound_Effect()
{
	_Content->playlist_battle->setCurrentIndex(13);
	_Content->player_battle->play();
}

void SinglePlayerController::UltimateSkill_Assassin_Sound_Effect()
{
	_Content->playlist_battle->setCurrentIndex(19);
	_Content->player_battle->play();
}


/**** operate ****/
void SinglePlayerController::undo()//右键undo，即取消IsChoosingMoveTarget/IsChoosingAttackTarget的状态
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

void SinglePlayerController::Move(MapUnit* target)//移动先攻队列front的element到指定target
{
	if (target->get_note_state())
	{
		int ActionPiece{ _State.AttackSequence.front() };
		if (ActionPiece < 0) ActionPiece = -ActionPiece;
		_Content->playlist_battle->setCurrentIndex(ActionPiece + 5);
		_Content->player_battle->play();
		
		resetOperate();

		//以下BFS部分请参照notePossibleMoveTargetMapUnit中相似段
		Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
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

		int nowX = target->Xcell();
		int nowY = target->Ycell();


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
		element->Move(target->Xcell(),target->Ycell());//only change the Xcell and Ycell of Element

		_State.IsChoosingMoveTarget = false;
		_Content->Map()->restoreAllMapUnitColor();
		_State.HasMoved = true;
	}
}

void SinglePlayerController::Attack(Element* enemy)
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	if (enemy->get_note_state())
	{
		int ActionPiece{ _State.AttackSequence.front() };
		if (ActionPiece < 0) ActionPiece = -ActionPiece;
		if (ActionPiece != 2){
			_Content->playlist_battle->setCurrentIndex(ActionPiece - 1);
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
		resetOperate();

		_State.IsChoosingAttackTarget = false;
		//以下开始攻击动画
		QParallelAnimationGroup* ParallelPartofAttackAnimation = new QParallelAnimationGroup;
		QSequentialAnimationGroup* AllAttackAnimation = new QSequentialAnimationGroup;

		//这是冲向element的动画
		QParallelAnimationGroup* AttackTowardEnemyGroup = new QParallelAnimationGroup;
		QPropertyAnimation *AttackForward = new QPropertyAnimation(element, "pos");
	//	QPropertyAnimation *FadeIn = new QPropertyAnimation(this, "opacity");
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
			_EAnime = new Element_Animation(_BulletPicture_Archer);
			QObject::connect(AttackTowardEnemyGroup, &QParallelAnimationGroup::finished, _EAnime, &Element_Animation::Emit_Hide_Signal);
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
			_EAnime = new Element_Animation(_BulletPicture_Caster);
			QObject::connect(AttackTowardEnemyGroup, &QParallelAnimationGroup::finished, _EAnime, &Element_Animation::Emit_Hide_Signal);
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


		//*****下面为assassin闪避动画*****//
		int AC_value = enemy->_character.get_AC();
		if (AC_value == 30 && element->_character.get_Choose() != 5){
			connect(AttackTowardEnemyGroup,&QParallelAnimationGroup::finished,this,&SinglePlayerController::UltimateSkill_Assassin_Sound_Effect);
			QParallelAnimationGroup* Assassin_Dodge_Anime = new QParallelAnimationGroup;
			qreal rad = qAtan2(enemy->pos().y() - element->pos().y(), enemy->pos().x() - element->pos().x());

			QPropertyAnimation *Assassin_Opac = new QPropertyAnimation(enemy, "opacity");
			Assassin_Opac->setDuration(400);
			Assassin_Opac->setStartValue(0);
			Assassin_Opac->setKeyValueAt(0.5,0);
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

		int Damage = element->_character.Output_Damage(AC_value);
		_EAnime = new Element_Animation(enemy, Damage);
		QObject::connect(AttackTowardEnemyGroup, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Damage_Signal);
		QObject::connect(_EAnime,&Element_Animation::Damage_signal,this,&SinglePlayerController::show_damage);

		enemy->_character.Input_Damage(Damage);
		//掉血动画
		_HealthAnime = new Element_Animation(enemy, _State.Round, _HeadUp);
		if (Damage>0)
			QObject::connect(AttackTowardEnemyGroup, &QPropertyAnimation::finished, _HealthAnime, &Element_Animation::Emit_Set_Health_Signal);


		//判断死亡
		if (enemy->_character.Death(_State.Round))
		{
			if ((enemy->_character.get_Choose() == 6) && (enemy->_character.get_Whether_Strokes() == 0))
			{
				//判定B叔用过大招了
				enemy->_character.set_Whether_Strokes(1);
				QObject::connect(AllAttackAnimation, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Tomb_Note_Signal);
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
				QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Hide_Signal);
			}

			CheckVictory();
		}
		
		//这里执行所有的动画组
		AllAttackAnimation->start();

		if (element->Index()>0)
			_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
		else
			_Content->Elements()->restoreAllEnemyElementColor(!_State.IsHost);
		_State.HasAttacked = true;

		QTimer::singleShot(500, _BattleInfo, &PanelBattleInfo::RefreshAllBattleInfo);//new added
	}
}

void SinglePlayerController::UltimateSkill_Saber(Element* enemy)
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	if (enemy->get_note_state())
	{
		resetOperate();
		_State.WhileUltimateSkilling = 0;
		_Content->Elements()->restoreAllEnemyElementColor(_State.IsHost);
		_Content->playlist_battle->setCurrentIndex(12);
		_Content->player_battle->play();
		_State.HasUltimateSkilled = true;
		//次数-1
		element->_character.change_Num_Strokes();
		//要加特效

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
		_EAnime = new Element_Animation(_BulletPicture_Saber);
		QObject::connect(AllAttackForwardAnime, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Hide_Signal);

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
		connect(AttackTowardEnemy_1, &QPropertyAnimation::finished, this, &SinglePlayerController::UltimateSkill_Saber_Sound_Effect);
		connect(EffectTimer_1, &QTimer::timeout, this, &SinglePlayerController::UltimateSkill_Saber_Effect_Fast);
		QObject::connect(AttackTowardEnemy_1, SIGNAL(finished(void)),
			EffectTimer_2, SLOT(start(void)));

		EffectTimer_2->setInterval(10);
		connect(AttackTowardEnemy_2, &QPropertyAnimation::finished, EffectTimer_2, &QTimer::stop);
		connect(AttackTowardEnemy_2, &QPropertyAnimation::finished, EffectTimer_2, &QTimer::deleteLater);
		connect(EffectTimer_2, &QTimer::timeout, this, &SinglePlayerController::UltimateSkill_Saber_Effect_Slow);


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
		int Damage{ 25 };
		_EAnime = new Element_Animation(enemy, Damage);
		QObject::connect(AllAttackForwardAnime, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Damage_Signal);
		QObject::connect(_EAnime, &Element_Animation::Damage_signal, this, &SinglePlayerController::show_damage);

		enemy->_character.Input_Damage(Damage);
		//掉血动画
		_HealthAnime = new Element_Animation(enemy, _State.Round, _HeadUp);
		if (Damage > 0)
			QObject::connect(AllAttackForwardAnime, &QPropertyAnimation::finished, _HealthAnime, &Element_Animation::Emit_Set_Health_Signal);


		//判断死亡
		if (enemy->_character.Death(_State.Round))
		{
			if ((enemy->_character.get_Choose() == 6) && (enemy->_character.get_Whether_Strokes() == 0))
			{
				//判定B叔用过大招了
				enemy->_character.set_Whether_Strokes(1);
				QObject::connect(AllAttackAnimation, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Tomb_Note_Signal);
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
				QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime, &Element_Animation::Emit_Hide_Signal);
			}
			CheckVictory();
		}
		//这里执行所有的动画组
		AllAttackAnimation->start();
		_Content->Elements()->restoreAllEnemyElementColor((element->Index() > 0));
		QTimer::singleShot(500, _BattleInfo, &PanelBattleInfo::RefreshAllBattleInfo);//new added
	}

}

void SinglePlayerController::UltimateSkill_Archer()
{
	bool melee = false;
	int temp_piece = _State.AttackSequence.front();
	Element* element = _Content->Elements()->get_Element(temp_piece);
	_State.HasUltimateSkilled = true;
	resetOperate();
	if (element->_character.get_AB() == 8){
		Remote_Archer();
		_Content->playlist_battle->setCurrentIndex(18);
		_Content->player_battle->play();
	}
	else{
		melee = true;
		Melee_Archer();
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

void SinglePlayerController::UltimateSkill_Rider()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	QVector<Element*> element_vector;
	_Content->playlist_battle->setCurrentIndex(15);
	_Content->player_battle->play();
	_State.HasUltimateSkilled = true;
	//_State.HasAttacked = true;

	//次数-1
	element->_character.change_Num_Strokes();
	//要特技可以加在这里


	//找到距离内可用的东西
	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 3) && (!enemy->_character.Death(_State.Round)))
		if (enemy != element)
		{
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
			element_vector.push_back(enemy);
			enemy->tomb_note();
		}
	}

	srand(time(nullptr));
	int calc = -1;
	for (Element* temp_element : element_vector)
	{
		calc++;
		int Init = temp_element->_character.get_Initiative();
		int rand_Init = Init + rand() % 20 + 1;

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

		if (rand_Init < 15)
		{

			int Damage = temp_element->_character.get_HP();
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
					_EAnime_Rider[calc] = new Element_Animation(temp_element);
					QObject::connect(DeathAnime, &QPropertyAnimation::finished, _EAnime_Rider[calc], &Element_Animation::Emit_Hide_Signal);
				}
				CheckVictory();
			}
			
		}
		else QObject::connect(BeAttacked, &QPropertyAnimation::finished, temp_element, &Element::alive_note);
		BeAttacked->start();

		QTimer::singleShot(1000, _BattleInfo, &PanelBattleInfo::RefreshAllBattleInfo);//new added
	}
}

void SinglePlayerController::UltimateSkill_Caster(MapUnit* target)
{
	if (target->get_note_state())
	{
		Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
		resetOperate();
		//次数-1
		element->_character.change_Num_Strokes();
		_Content->playlist_battle->setCurrentIndex(16);
		_Content->player_battle->play();
		//下为移动动画
		QSequentialAnimationGroup *AnimeGroup = new QSequentialAnimationGroup;

		QPropertyAnimation *OpacityAnime = new QPropertyAnimation(element, "opacity");
		OpacityAnime->setDuration(600);
		OpacityAnime->setStartValue(1);
		OpacityAnime->setEndValue(0);
		AnimeGroup->addAnimation(OpacityAnime);

		QPropertyAnimation *MoveAnime = new QPropertyAnimation(element, "pos");
		MoveAnime->setDuration(1);
		MoveAnime->setStartValue(element->pos());
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(target->Xcell(), target->Ycell(), 0, 0);
		MoveAnime->setEndValue(temp_MapUnit->pos());
		AnimeGroup->addAnimation(MoveAnime);

		QPropertyAnimation *OpacityAnime_2 = new QPropertyAnimation(element, "opacity");
		OpacityAnime_2->setDuration(600);
		OpacityAnime_2->setStartValue(0);
		OpacityAnime_2->setEndValue(1);
		AnimeGroup->addAnimation(OpacityAnime_2);

		//消失->移动->出现
		AnimeGroup->start();
		element->Move(target->Xcell(), target->Ycell());

		_State.WhileUltimateSkilling = 0;
		_Content->Map()->restoreAllMapUnitColor();
		_State.HasUltimateSkilled = true;
	}
}

void SinglePlayerController::Cancel()
{
	Next();//无条件直接next
}


/**** slot ****/
void SinglePlayerController::ShowMenu()
{
	emit ShowMenu_ViewToMainWindow_Signal();
	resetOperate();
}

void SinglePlayerController::TogglePanelBattleInfo()
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

void SinglePlayerController::btMovePressed()//slot
{
	_State.IsChoosingMoveTarget = true;
	resetOperate();
	notePossibleMoveTargetMapUnit();//变色，加MapUnit鼠标指针变换
}

void SinglePlayerController::btAttackPressed()//slot
{

	_State.IsChoosingAttackTarget = true;
	resetOperate();
	if (!notePossibleAttackTargetElement()){
		undo();
	}
}

void SinglePlayerController::btUltimateSkillPressed()//slot
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	if (!element->_character.if_Strokes()) return;

	//对于不同的Element有不同的大招能否释放的条件，现已加入operate判断
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

void SinglePlayerController::btCancelPressed()//slot
{
	resetOperate();
	Cancel();

}


/**** event ****/
void SinglePlayerController::wheelEvent(QWheelEvent* e)
{
	//暂时禁掉了鼠标滚轮的作用
	/*if (this->isInteractive()){
		resetOperate();
		QGraphicsView::wheelEvent(e);//此句不能少，否则会由于重载后不再运行原本view的wheelevent，进而无法滑动
	}*/
}

void SinglePlayerController::mousePressEvent(QMouseEvent *e)//此处mousePressEvent只重点处理operate的创建，其余内容放在Move和Attack等函数中
{
	if (this->isInteractive()){

		QGraphicsItem *itemSelected = this->itemAt(e->x(), e->y());
		int index = _Content->Elements()->get_item_index_in_ElementPool(itemSelected);

		if (e->button() == Qt::LeftButton)
		{ //点击的是左键
			if (!_State.IsChoosingMoveTarget && !_State.IsChoosingAttackTarget && (_State.WhileUltimateSkilling == 0))
			{//处于最基本的状态，没有点击过任何operate的按钮
				if (itemSelected != NULL && index != 0 &&
					(((index > 0 && _State.IsHost) || (index < 0 && !_State.IsHost) || (_State.AILevel == -1)))//_State.IsSinglePlayer ||新增了单机模式的判断
					&& CheckIsNextAttacker(index))	//点到了【先攻队列的front】，且是【自己的】【Element】的【item】
				{
					resetOperate();

					//新增
					Element* element = _Content->Elements()->get_Element(index);
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
					connect(_Operate, &PanelOperate::btMovePressed_Signal, this, &SinglePlayerController::btMovePressed);
					connect(_Operate, &PanelOperate::btAttackPressed_Signal, this, &SinglePlayerController::btAttackPressed);
					connect(_Operate, &PanelOperate::btUltimateSkillPressed_Signal, this, &SinglePlayerController::btUltimateSkillPressed);
					connect(_Operate, &PanelOperate::btCancelPressed_Signal, this, &SinglePlayerController::btCancelPressed);
					
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
				if ((index < 0 && _State.IsHost) || (index > 0 && !_State.IsHost) || (_State.AILevel == -1))//任意敌人element
					Attack(_Content->Elements()->get_Element(index));

			}
			else if (_State.WhileUltimateSkilling != 0)
			{
				switch (_State.WhileUltimateSkilling)
				{
				case 1:
				{
						  if ((index < 0 && _State.IsHost) || (index > 0 && !_State.IsHost) || (_State.AILevel == -1))//任意敌人element
							  UltimateSkill_Saber(_Content->Elements()->get_Element(index));
						  break;
				}
/*				
				case 2:
				{
						  if ((index < 0 && _State.IsHost) || (index > 0 && !_State.IsHost))//任意敌人element
							  UltimateSkill_Archer(_Content->Elements()->get_Element(index));
						  break;
				}
*/
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

void SinglePlayerController::keyPressEvent(QKeyEvent *event)
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

void SinglePlayerController::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_A || event->key() == Qt::Key_D || event->key() == Qt::Key_W || event->key() == Qt::Key_S){
		viewMoveTimer(0);
		this->setFocus();
	}
}

void SinglePlayerController::viewMoveTimer(int type)
{
	if (_timer == nullptr){
		_timer = new QTimer;
		switch (type)
		{
		case 1:
			connect(_timer, &QTimer::timeout, this, &SinglePlayerController::moveView_Left); break;
		case 2:
			connect(_timer, &QTimer::timeout, this, &SinglePlayerController::moveView_Right); break;
		case 3:
			connect(_timer, &QTimer::timeout, this, &SinglePlayerController::moveView_Up); break;
		case 4:
			connect(_timer, &QTimer::timeout, this, &SinglePlayerController::moveView_Down); break;
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

void SinglePlayerController::moveView_Left()
{
	centerOn(mapToScene(rect().center().x() - 20, rect().center().y()));
}

void SinglePlayerController::moveView_Right()
{
	centerOn(mapToScene(rect().center().x() + 20, rect().center().y()));
}

void SinglePlayerController::moveView_Up()
{
	centerOn(mapToScene(rect().center().x(), rect().center().y() - 20));
}

void SinglePlayerController::moveView_Down()
{
	centerOn(mapToScene(rect().center().x(), rect().center().y() + 20));
}


/**** AI ****/
void SinglePlayerController::SinglePlayerAI()
{
	if (_State.AILevel == -1)
		return;
	//判断先攻队列中下一个为敌人
	if ((_State.AttackSequence.front() < 0 && _State.IsHost) || (_State.AttackSequence.front() > 0 && !_State.IsHost))
	{
		QTimer::singleShot(1000, this, &SinglePlayerController::notePossibleMoveTargetMapUnit);
		switch (_State.AILevel){
		case 0:
			QTimer::singleShot(1500, this, &SinglePlayerController::AI_Action_TutorialMode);break;
		case 1:
			QTimer::singleShot(1500, this, &SinglePlayerController::AI_Action_EasyMode); break;
		case 2:
			QTimer::singleShot(1500, this, &SinglePlayerController::AI_Action_NormalMode); break;
		case 3:
			QTimer::singleShot(1500, this, &SinglePlayerController::AI_Action_HardMode); break;
		case 4:
			QTimer::singleShot(1500, this, &SinglePlayerController::AI_Action_LunaticMode); break;
		}
	}
}

void SinglePlayerController::AI_Action_TutorialMode()
{
	_Content->Map()->restoreAllMapUnitColor();
	QTimer::singleShot(1000, this, &SinglePlayerController::Cancel);
}

void SinglePlayerController::AI_Action_EasyMode()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	QVector<Element*> Alive_Element_Vector;
	//这是玩家操控的Element的判定(对于AI的敌人)
	int num_sig = -1;
	if (_State.IsHost) num_sig = 1;

	//把活着的AI敌人加入Vector
	for (int i = 1; i <= 6; i++)
	{
		Element* temp_Element = _Content->Elements()->get_Element(num_sig*i);
		if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector.push_back(temp_Element);
	}
	if (Alive_Element_Vector.size() == 0) {
		_Content->Map()->restoreAllMapUnitColor();
		QTimer::singleShot(1000, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
		return;
	}
	
	//排序：血多的放前面
	for (int i = 0; i < Alive_Element_Vector.size() - 1; i++)
	for (int j = i + 1; j < Alive_Element_Vector.size(); j++)
	if (Alive_Element_Vector[i]->_character.get_HP()<Alive_Element_Vector[j]->_character.get_HP())
	{
		Element* temp{ Alive_Element_Vector[i] };
		Alive_Element_Vector[i] = Alive_Element_Vector[j];
		Alive_Element_Vector[j] = temp;
	}

	//选取地点
	int temp_step = element->_character.get_Speed();
	MapUnit* target_MapUnit = nullptr;
	int target_Element = -1;
	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;
		if (temp_MapUnit->get_note_state())
		{
			for (int i = target_Element + 1; i < Alive_Element_Vector.size(); i++)
			{
				int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);

				if (Dis <= element->_character.get_Range_Inc())
				{
					target_Element = i;
					target_MapUnit = temp_MapUnit;
				}
			}
		}
	}

	//判断站着能不能打人
	for (int i = target_Element + 1; i < Alive_Element_Vector.size(); i++)
	if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= element->_character.get_Range_Inc())
	{
		target_Element = i;
		target_MapUnit = nullptr;
	}

	//如果这轮打不到人就瞎走
	if (target_Element == -1)
	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;

		if (temp_MapUnit->get_note_state())
		//随便写个random条件
		if (rand() % 20 == 1)	target_MapUnit = temp_MapUnit;
	}

	//时间延迟
	int Action_Num = 3;
	int Dis_Delay = 0;

	//是否移动
	if (target_MapUnit != nullptr)
	{
		AI_Anime_Move = new AI_Animation(target_MapUnit);
		QTimer* temp_time = new QTimer(this);
		temp_time->setSingleShot(true);
		temp_time->start(Action_Num * 500);
		QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Move, &AI_Animation::Emit_Move_Signal);
		QObject::connect(AI_Anime_Move, &AI_Animation::Move_Signal, this, &SinglePlayerController::Move);
		Action_Num++;
	}
	else
		_Content->Map()->restoreAllMapUnitColor();

	//是否攻击
	if (target_Element != -1)
	{
		QTimer::singleShot(Action_Num * 500, this, &SinglePlayerController::notePossibleAttackTargetElement);
		Action_Num++;

		AI_Anime_Attack = new AI_Animation(Alive_Element_Vector[target_Element]);
		QTimer* temp_time = new QTimer(this);
		temp_time->setSingleShot(true);
		temp_time->start(Action_Num * 500);
		QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Attack, &AI_Animation::Emit_Attack_Signal);
		QObject::connect(AI_Anime_Attack, &AI_Animation::Attack_Signal, this, &SinglePlayerController::Attack);
		Action_Num++;
		Dis_Delay += element->_character.get_Distance(Alive_Element_Vector[target_Element]->_character) * 50;
	}
	//QTimer::singleShot(Action_Num * 500, this, &SinglePlayerController::undo);
	QTimer::singleShot(Action_Num * 500 + 500 + Dis_Delay, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
}

void SinglePlayerController::AI_Action_NormalMode()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	QVector<Element*> Alive_Element_Vector;
	//这是玩家操控的Element的判定(对于AI的敌人)
	int num_sig = -1;
	if (_State.IsHost) num_sig = 1;

	//把活着的AI敌人加入Vector
	for (int i = 1; i <= 6; i++)
	{
		Element* temp_Element = _Content->Elements()->get_Element(num_sig*i);
		if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector.push_back(temp_Element);
	}
	if (Alive_Element_Vector.size() == 0) {
		_Content->Map()->restoreAllMapUnitColor();
		QTimer::singleShot(1000, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
		return;
	}
	//排序：加权，血多的放前面
	for (int i = 0; i < Alive_Element_Vector.size() - 1; i++)
	for (int j = i + 1; j < Alive_Element_Vector.size(); j++)
	{
		int i_HP = Alive_Element_Vector[i]->_character.get_HP();
		int j_HP = Alive_Element_Vector[j]->_character.get_HP();
		int i_AC = Alive_Element_Vector[i]->_character.get_AC_basic();
		int j_AC = Alive_Element_Vector[j]->_character.get_AC_basic();
		int i_Ran = 20 - Alive_Element_Vector[i]->_character.get_AC() + element->_character.get_AB();
		int j_Ran = 20 - Alive_Element_Vector[j]->_character.get_AC() + element->_character.get_AB();
		if (Alive_Element_Vector[i]->_character.get_Choose() == 5) i_Ran /= 2;
		if (Alive_Element_Vector[j]->_character.get_Choose() == 5) j_Ran /= 2;

		if ((i_HP*i_Ran) < (j_HP*j_Ran))
		{
			Element* temp{ Alive_Element_Vector[i] };
			Alive_Element_Vector[i] = Alive_Element_Vector[j];
			Alive_Element_Vector[j] = temp;
		}
	}
	//选取地点
	int temp_step = element->_character.get_Speed();
	MapUnit* target_MapUnit = nullptr;
	int target_Element = 0;
	bool whether_target = false;
	int min_Dis = 1024;
	int max_Dis = -1;

	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;
		if (temp_MapUnit->get_note_state())
		{
			for (int i = target_Element; i < Alive_Element_Vector.size(); i++)
			{
				int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);

				if (Dis <= element->_character.get_Range_Inc())
				{
					int element_character = element->_character.get_Choose();
					bool whether_remote = false;
					if ((element_character == 2) || (element_character == 5)) whether_remote = true;
					if ((whether_remote) && (Dis > max_Dis))
					{
						max_Dis = Dis;
						whether_target = true;
						target_Element = i;
						target_MapUnit = temp_MapUnit;
					}
					if ((!whether_remote) && (Dis < min_Dis))
					{
						min_Dis = Dis;
						whether_target = true;
						target_Element = i;
						target_MapUnit = temp_MapUnit;
					}
				}
			}
		}
	}

	//判断站着能不能打人
	for (int i = target_Element; i < Alive_Element_Vector.size(); i++)
	if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= element->_character.get_Range_Inc())
	{
		whether_target = true;
		target_Element = i;
		target_MapUnit = nullptr;
	}

	//如果这轮打不到人就往血最少的家伙走！
	min_Dis = 1024;
	if (!whether_target)
	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;

		if (temp_MapUnit->get_note_state())
		{
			int i = Alive_Element_Vector.size() - 1;
			int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
			int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
			int small;
			int large;
			if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
			large = X_diff + Y_diff - small;
			int Dis = large + static_cast<int>(0.5*small);

			int element_character = element->_character.get_Choose();
			if (Dis < min_Dis)
			{
				min_Dis = Dis;
				whether_target = true;
				target_Element = i;
				target_MapUnit = temp_MapUnit;
			}
		}
	}

	//时间延迟
	int Action_Num = 1;
	int Dis_Delay = 0;
	//是否移动
	if (target_MapUnit != nullptr)
	{
		AI_Anime_Move = new AI_Animation(target_MapUnit);
		QTimer* temp_time = new QTimer(this);
		temp_time->setSingleShot(true);
		temp_time->start(Action_Num * 500);
		QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Move, &AI_Animation::Emit_Move_Signal);
		QObject::connect(AI_Anime_Move, &AI_Animation::Move_Signal, this, &SinglePlayerController::Move);
		Action_Num++;
	}
	else
		_Content->Map()->restoreAllMapUnitColor();

	//是否攻击
	if (target_Element != -1)
	{
		QTimer::singleShot(Action_Num * 500 + 500, this, &SinglePlayerController::notePossibleAttackTargetElement);
		Action_Num++;

		AI_Anime_Attack = new AI_Animation(Alive_Element_Vector[target_Element]);
		QTimer* temp_time = new QTimer(this);
		temp_time->setSingleShot(true);
		temp_time->start(Action_Num * 500 + 500);
		QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Attack, &AI_Animation::Emit_Attack_Signal);
		QObject::connect(AI_Anime_Attack, &AI_Animation::Attack_Signal, this, &SinglePlayerController::Attack);
		Action_Num++;
		Dis_Delay += element->_character.get_Distance(Alive_Element_Vector[target_Element]->_character) * 50;
	}
	QTimer::singleShot(Action_Num * 500 + 500 + Dis_Delay, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
}

void SinglePlayerController::AI_Action_HardMode()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	QVector<Element*> Alive_Element_Vector;
	//这是玩家操控的Element的判定(对于AI的敌人)
	int num_sig = -1;
	if (_State.IsHost) num_sig = 1;

	//把活着的AI敌人加入Vector
	for (int i = 1; i <= 6; i++)
	{
		Element* temp_Element = _Content->Elements()->get_Element(num_sig*i);
		if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector.push_back(temp_Element);
	}
	if (Alive_Element_Vector.size() == 0) {
		_Content->Map()->restoreAllMapUnitColor();
		QTimer::singleShot(1000, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
		return;
	}
	//排序：加权，血多的放前面
	for (int i = 0; i < Alive_Element_Vector.size() - 1; i++)
	for (int j = i + 1; j < Alive_Element_Vector.size(); j++)
	{
		int i_HP = Alive_Element_Vector[i]->_character.get_HP();
		int j_HP = Alive_Element_Vector[j]->_character.get_HP();
		int i_AC = Alive_Element_Vector[i]->_character.get_AC_basic();
		int j_AC = Alive_Element_Vector[j]->_character.get_AC_basic();
		int i_Ran = 20 - Alive_Element_Vector[i]->_character.get_AC() + element->_character.get_AB();
		int j_Ran = 20 - Alive_Element_Vector[j]->_character.get_AC() + element->_character.get_AB();
		if (Alive_Element_Vector[i]->_character.get_Choose() == 5) i_Ran /= 2;
		if (Alive_Element_Vector[j]->_character.get_Choose() == 5) j_Ran /= 2;

		if ((i_HP*i_Ran) < (j_HP*j_Ran))
		{
			Element* temp{ Alive_Element_Vector[i] };
			Alive_Element_Vector[i] = Alive_Element_Vector[j];
			Alive_Element_Vector[j] = temp;
		}
	}

	//Hard Mode专供：大招（好难写的(╯‵□′)╯︵┻━┻）
	if (element->_character.if_Strokes())
	{
		switch (element->_character.get_Choose())
		{
		case 1:
		{
				  bool AttackEnemy = false;
				  QVector<Element*> Alive_Element_Vector_Saber;
				  for (int i = 1; i != ELEMENTS_NUM + 1; i++)
				  {
					  Element* enemy;
					  if (element->Index() > 0)
						  enemy = _Content->Elements()->get_Element(-i);
					  else
						  enemy = _Content->Elements()->get_Element(i);
					  if ((element->_character.get_Distance(enemy->_character) <= 10) &&
						  (!enemy->_character.Death(_State.Round)))
					  {
						  Alive_Element_Vector_Saber.push_back(enemy);
						  AttackEnemy = true;
					  }
				  }
				  if (AttackEnemy)
				  {
					  _Content->Map()->restoreAllMapUnitColor();
					  QTimer::singleShot(500, this, &SinglePlayerController::noteUltimateSkillTarget_Saber);
					  QTimer::singleShot(1000, this, &SinglePlayerController::AI_Action_HardMode_UltimateSkill_Saber);
					  return;
				  }
				  break;
		}
		case 2:
		{
				  if (element->_character.get_AB() == 8)
				  {
					  _Content->Map()->restoreAllMapUnitColor();
					  UltimateSkill_Archer();
					  notePossibleMoveTargetMapUnit();
				  }
				  break;
		}
		case 3:
		{
				  QVector<Element*> Alive_Element_Vector_Rider;
				  for (int i = 1; i <= 6; i++)
				  {
					  Element* temp_Element = _Content->Elements()->get_Element(i);
					  if (temp_Element == element) continue;
					  if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector_Rider.push_back(temp_Element);
					  temp_Element = _Content->Elements()->get_Element(-i);
					  if (temp_Element == element) continue;
					  if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector_Rider.push_back(temp_Element);
				  }
				  int calc_probable_damage = 0;
				  for (Element* alive_element : Alive_Element_Vector_Rider)
				  {
					  if (alive_element->Index()*element->Index() > 0) calc_probable_damage += alive_element->_character.get_HP();
					  else  calc_probable_damage -= alive_element->_character.get_HP();
				  }
				  if (calc_probable_damage >= 5)
				  {
					  _Content->Map()->restoreAllMapUnitColor();
					  QTimer::singleShot(500, this, &SinglePlayerController::UltimateSkill_Rider);
					  QTimer::singleShot(2000, this, &SinglePlayerController::Cancel);
					  return;
				  }
				  break;
		}
		case 5:
		{
				  int calc_probable_damage = 0;
				  for (Element* enemy : Alive_Element_Vector)
				  {
					  int temp_speed = enemy->_character.get_Speed();
					  if (element->_character.get_Distance(enemy->_character) <= temp_speed)
					  {
						  int temp_Damage = (20 + enemy->_character.get_AB() - element->_character.get_AC())*
							  (enemy->_character.get_Dice_Num()*(enemy->_character.get_Dice_Type() + 1) / 2 + enemy->_character.get_Ability_Bonus());
						  calc_probable_damage += temp_Damage;
					  }
				  }
				  if (calc_probable_damage > (element->_character.get_HP() * 2 / 3))
				  {
					  _Content->Map()->restoreAllMapUnitColor();
					  QTimer::singleShot(500, this, &SinglePlayerController::noteUltimateSkillTarget_Caster);
					  QTimer::singleShot(1000, this, &SinglePlayerController::AI_Action_HardMode_UltimateSkill_Caster);
					  QTimer::singleShot(2000, this, &SinglePlayerController::Cancel);
					  return;
				  }
				  break;
		}
			//switch完结
		}
	}


	//选取地点
	int temp_step = element->_character.get_Speed();
	MapUnit* target_MapUnit = nullptr;
	int target_Element = 0;
	bool whether_target = false;
	int min_Dis = 1024;
	int max_Dis = -1;

	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;
		if (temp_MapUnit->get_note_state())
		{
			for (int i = target_Element; i < Alive_Element_Vector.size(); i++)
			{
				int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);

				if (Dis <= element->_character.get_Range_Inc())
				{
					int element_character = element->_character.get_Choose();
					bool whether_remote = false;
					if ((element_character == 2) || (element_character == 5)) whether_remote = true;
					if ((whether_remote) && (Dis > max_Dis))
					{
						max_Dis = Dis;
						whether_target = true;
						target_Element = i;
						target_MapUnit = temp_MapUnit;
					}
					if ((!whether_remote) && (Dis < min_Dis))
					{
						min_Dis = Dis;
						whether_target = true;
						target_Element = i;
						target_MapUnit = temp_MapUnit;
					}
				}
			}
		}
	}

	//判断站着能不能打人
	for (int i = target_Element; i < Alive_Element_Vector.size(); i++)
	if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= element->_character.get_Range_Inc())
	{
		whether_target = true;
		target_Element = i;
		target_MapUnit = nullptr;
	}

	//如果这轮打不到人就往血最少的家伙走！
	min_Dis = 1024;
	if (!whether_target)
	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;

		if (temp_MapUnit->get_note_state())
		{
			int i = Alive_Element_Vector.size() - 1;
			int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
			int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
			int small;
			int large;
			if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
			large = X_diff + Y_diff - small;
			int Dis = large + static_cast<int>(0.5*small);

			int element_character = element->_character.get_Choose();
			if (Dis < min_Dis)
			{
				min_Dis = Dis;
				whether_target = true;
				target_Element = i;
				target_MapUnit = temp_MapUnit;
			}
		}
	}

	//时间延迟
	int Action_Num = 1;
	int Dis_Delay = 0;
	//是否移动
	if (target_MapUnit != nullptr)
	{
		AI_Anime_Move = new AI_Animation(target_MapUnit);
		QTimer* temp_time = new QTimer(this);
		temp_time->setSingleShot(true);
		temp_time->start(Action_Num * 500);
		QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Move, &AI_Animation::Emit_Move_Signal);
		QObject::connect(AI_Anime_Move, &AI_Animation::Move_Signal, this, &SinglePlayerController::Move);
		Action_Num++;
	}
	else
		_Content->Map()->restoreAllMapUnitColor();

	//是否攻击
	if (target_Element != -1)
	{
		QTimer::singleShot(Action_Num * 500 + 500, this, &SinglePlayerController::notePossibleAttackTargetElement);
		Action_Num++;

		AI_Anime_Attack = new AI_Animation(Alive_Element_Vector[target_Element]);
		QTimer* temp_time = new QTimer(this);
		temp_time->setSingleShot(true);
		temp_time->start(Action_Num * 500 + 500);
		QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Attack, &AI_Animation::Emit_Attack_Signal);
		QObject::connect(AI_Anime_Attack, &AI_Animation::Attack_Signal, this, &SinglePlayerController::Attack);
		Action_Num++;
		Dis_Delay += element->_character.get_Distance(Alive_Element_Vector[target_Element]->_character) * 50;

	}
	QTimer::singleShot(Action_Num * 500 + 500 + Dis_Delay, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
}

void SinglePlayerController::AI_Action_LunaticMode()
{
	Element *element = _Content->Elements()->get_Element(_State.AttackSequence.front());
	QVector<Element*> Alive_Element_Vector;
	int num_sig = -1;
	if (_State.IsHost) num_sig = 1;

	for (int i = 1; i <= 6; i++)
	{
		Element* temp_Element = _Content->Elements()->get_Element(num_sig*i);
		if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector.push_back(temp_Element);
	}
	if (Alive_Element_Vector.size() == 0) {
		_Content->Map()->restoreAllMapUnitColor();
		QTimer::singleShot(1000, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
		return;
	}

	//排序：加权方式改变，血多的放前面
	for (int i = 0; i < Alive_Element_Vector.size() - 1; i++)
	for (int j = i + 1; j < Alive_Element_Vector.size(); j++)
	{
		double self_AC = element->_character.get_AC();
		double self_AB = element->_character.get_AB();
		double self_Dice_Num = element->_character.get_Dice_Num();
		double self_Dive_Type = element->_character.get_Dice_Type();
		double self_Ability = element->_character.get_Ability_Bonus();
		double i_HP = Alive_Element_Vector[i]->_character.get_HP();
		double j_HP = Alive_Element_Vector[j]->_character.get_HP();
		double i_AB = Alive_Element_Vector[i]->_character.get_AB();
		double j_AB = Alive_Element_Vector[j]->_character.get_AB();
		double i_AC = Alive_Element_Vector[i]->_character.get_AC_basic();
		double j_AC = Alive_Element_Vector[j]->_character.get_AC_basic();
		double i_Whether_Strokes = Alive_Element_Vector[i]->_character.get_Whether_Strokes();
		double j_Whether_Strokes = Alive_Element_Vector[j]->_character.get_Whether_Strokes();
		double i_Dice_Num = Alive_Element_Vector[i]->_character.get_Dice_Num();
		double j_Dice_Num = Alive_Element_Vector[j]->_character.get_Dice_Num();
		double i_Dice_Type = Alive_Element_Vector[i]->_character.get_Dice_Type();
		double j_Dice_Type = Alive_Element_Vector[j]->_character.get_Dice_Type();
		double i_Ability = Alive_Element_Vector[i]->_character.get_Ability_Bonus();
		double j_Ability = Alive_Element_Vector[j]->_character.get_Ability_Bonus();
		double i_Choose = Alive_Element_Vector[i]->_character.get_Choose();
		double j_Choose = Alive_Element_Vector[j]->_character.get_Choose();
		double i_Attack_Sequen;
		double j_Attack_Sequen;
		for (int AttackSequence_Num = 0; AttackSequence_Num < _State.AttackSequence.size(); AttackSequence_Num++)
		{
			if (_State.AttackSequence[AttackSequence_Num] == num_sig*i_Choose)
				i_Attack_Sequen = AttackSequence_Num;
			if (_State.AttackSequence[AttackSequence_Num] == num_sig*j_Choose)
				j_Attack_Sequen = AttackSequence_Num;
		}
		double i_Equal_HP, j_Equal_HP;
		switch (Alive_Element_Vector[i]->_character.get_Choose())
		{
		case 1: case 2: i_Equal_HP = 2 * i_HP - 5 * i_Whether_Strokes -
			(i_AC - self_AB) / 20 * (i_Dice_Num*i_Dice_Type + i_Ability) / 2; break;
		case 3:i_Equal_HP = 2 * i_HP - 5 * Alive_Element_Vector[i]->_character.if_Strokes() -
			(i_AC - self_AB) / 20 * (i_Dice_Num*i_Dice_Type + i_Ability) / 2; break;
		case 4: case 5: case 6: i_Equal_HP = 2 * i_HP -
			(i_AC - self_AB) / 20 * (i_Dice_Num*i_Dice_Type + i_Ability) / 2; break;
		default:
			break;
		}
		switch (Alive_Element_Vector[j]->_character.get_Choose())
		{
		case 1: case 2: j_Equal_HP = 2 * j_HP - 5 * j_Whether_Strokes -
			(j_AC - self_AB) / 20 * (j_Dice_Num*j_Dice_Type + j_Ability) / 2; break;
		case 3:j_Equal_HP = 2 * j_HP - 5 * Alive_Element_Vector[i]->_character.if_Strokes() -
			(j_AC - self_AB) / 20 * (j_Dice_Num*j_Dice_Type + j_Ability) / 2; break;
		case 4: case 5: case 6:j_Equal_HP = 2 * j_HP -
			(j_AC - self_AB) / 20 * (j_Dice_Num*j_Dice_Type + j_Ability) / 2; break;
		default:
			break;
		}
		i_Equal_HP -= i_Attack_Sequen;
		j_Equal_HP -= j_Attack_Sequen;
		if (i_Equal_HP<j_Equal_HP)
		{
			Element* temp{ Alive_Element_Vector[i] };
			Alive_Element_Vector[i] = Alive_Element_Vector[j];
			Alive_Element_Vector[j] = temp;
		}

	}

	//大招
	bool UltimateSkill_and_Move = false;
	bool is_Archer = (element->_character.get_Choose()==2);

	if (element->_character.if_Strokes())
	{
		switch (element->_character.get_Choose())
		{
		case 1:
		{
				  bool AttackEnemy = false;
				  for (int i = 1; i != ELEMENTS_NUM + 1; i++)
				  {
					  Element *enemy;
					  if (element->Index() > 0)
						  enemy = _Content->Elements()->get_Element(-i);
					  else
						  enemy = _Content->Elements()->get_Element(i);
					  if ((element->_character.get_Distance(enemy->_character) <= 10)
						  && (!enemy->_character.Death(_State.Round)))
						  AttackEnemy = true;
				  }
				  if (AttackEnemy)
				  {
					  _Content->Map()->restoreAllMapUnitColor();
					  QTimer::singleShot(500, this, &SinglePlayerController::noteUltimateSkillTarget_Saber);
					  QTimer::singleShot(1000, this, &SinglePlayerController::AI_Action_LunaticMode_UltimateSkill_Saber);
					  return;
				  }
				  break;
		}
		case 3:
		{
				  QVector<Element*> Alive_Element_Vector_Rider;
				  for (int i = 1; i <= 6; i++)
				  {
					  Element* temp_Element = _Content->Elements()->get_Element(i);
					  if (temp_Element == element) continue;
					  if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector_Rider.push_back(temp_Element);
					  temp_Element = _Content->Elements()->get_Element(-i);
					  if (temp_Element == element) continue;
					  if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector_Rider.push_back(temp_Element);
				  }
				  int calc_probable_damage = 0;
				  for (Element* alive_element : Alive_Element_Vector_Rider)
				  {
					  if (alive_element->Index()*element->Index() > 0) calc_probable_damage += alive_element->_character.get_HP();
					  else  calc_probable_damage -= alive_element->_character.get_HP();
				  }
				  if (calc_probable_damage >= 5)
				  {
					  UltimateSkill_and_Move = true;
					  _Content->Map()->restoreAllMapUnitColor();
					  QTimer::singleShot(500, this, &SinglePlayerController::UltimateSkill_Rider);
					  QTimer::singleShot(2000, this, &SinglePlayerController::Cancel);
				  }
				  break;
		}
		case 5:
		{
				  int calc_probable_damage = 0;
				  for (Element* enemy : Alive_Element_Vector)
				  {
					  int temp_speed = enemy->_character.get_Speed();
					  if (element->_character.get_Distance(enemy->_character) <= temp_speed)
					  {
						  int temp_Damage = (20 + enemy->_character.get_AB() - element->_character.get_AC())*
							  (enemy->_character.get_Dice_Num()*(enemy->_character.get_Dice_Type() + 1) / 2 + enemy->_character.get_Ability_Bonus());
						  calc_probable_damage += temp_Damage;
					  }
				  }
				  if (calc_probable_damage > (element->_character.get_HP() * 2 / 3))
				  {
					  _Content->Map()->restoreAllMapUnitColor();
					  QTimer::singleShot(500, this, &SinglePlayerController::noteUltimateSkillTarget_Caster);
					  QTimer::singleShot(1000, this, &SinglePlayerController::AI_Action_LunaticMode_UltimateSkill_Caster);
					  QTimer::singleShot(2000, this, &SinglePlayerController::Cancel);
					  return;
				  }
				  break;
		}
		default:
			break;
		}
	}

	//进行先攻击在移动还是先移动在攻击的判定
	int temp_step = element->_character.get_Speed();
	MapUnit* target_MapUnit = nullptr;
	int target_Element = -1;
	bool whether_target = false;
	int min_Dis = 1024;
	int max_Dis = -1;
	bool attack_enemy_notmove = false;
	bool move_after_attack = false;

	//判断站着不动能不能打人
	//如果不是Archer，直接判定
	if (!is_Archer)
	{
		for (int i = 0; i < Alive_Element_Vector.size(); i++)
		if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= element->_character.get_Range_Inc())
		{
			target_Element = i;
			move_after_attack = true;
			whether_target = true;
		}
	}
	//如果是Archer，进行是否变身的判定
	else
	{
		if (element->_character.get_Range_Inc() == 10)
		{
			int temp_target_Element=-1;
			for (int i = 0; i < Alive_Element_Vector.size(); i++)
			if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= element->_character.get_Range_Inc())
			{
				if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) == 1)
				{
					temp_target_Element = i;
					move_after_attack = true;
					whether_target = true;
				}
				target_Element = i;
				move_after_attack = true;
				whether_target = true;
			}
			if (temp_target_Element != -1)
			{
				target_Element = temp_target_Element;
				_Content->Map()->restoreAllMapUnitColor();
				UltimateSkill_Archer();
				notePossibleMoveTargetMapUnit();
			}
		}
		else
		{
			bool remote = true;
			int temp_target_Element = -1;
			for (int i = 0; i < Alive_Element_Vector.size(); i++)
			{
				if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= 10 * element->_character.get_Range_Inc())
				{
					if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) == 1)
					{
						remote = false;
						temp_target_Element = i;
					}
					target_Element = i;
					move_after_attack = true;
					whether_target = true;
				}
			}

			if (temp_target_Element != -1)
				target_Element = temp_target_Element;

			if (remote && whether_target)
			{
				_Content->Map()->restoreAllMapUnitColor();
				UltimateSkill_Archer();
				notePossibleMoveTargetMapUnit();
			}
		}
	}

	//时间延迟
	int Action_Num = 1;
	int Dis_Delay = 0;

	//如果可以不动打到目标的话，就攻击目标之后，在选择移动位置，否则，就执行先移动在攻击的动作
	if (move_after_attack)
	{
		//攻击动作
		if ((target_Element != -1) && (!UltimateSkill_and_Move))
		{
			QTimer::singleShot(Action_Num * 500, this, &SinglePlayerController::notePossibleAttackTargetElement);
			Action_Num++;

			AI_Anime_Attack = new AI_Animation(Alive_Element_Vector[target_Element]);
			QTimer* temp_time = new QTimer(this);
			temp_time->setSingleShot(true);
			temp_time->start(Action_Num * 500);
			QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Attack, &AI_Animation::Emit_Attack_Signal);
			QObject::connect(AI_Anime_Attack, &AI_Animation::Attack_Signal, this, &SinglePlayerController::Attack);
			Action_Num++;

		}
		//进行选择位置,选择离对方位置最远的地方进行躲避
		int longest_Dis = 0;
		for (int i = -temp_step; i < temp_step; i++)
		for (int j = -temp_step; j < temp_step; j++)
		{
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
			if (temp_MapUnit == nullptr) continue;
			if (temp_MapUnit->get_note_state())
			{
				int X_diff = abs(Alive_Element_Vector[target_Element]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[target_Element]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);
				if (Dis > longest_Dis)
				{
					longest_Dis = Dis;
					target_MapUnit = temp_MapUnit;
					whether_target = true;
				}
			}
		}
		//进行移动

		if (target_MapUnit != nullptr)
		{
			AI_Anime_Move = new AI_Animation(target_MapUnit);
			QTimer* temp_time = new QTimer(this);
			temp_time->setSingleShot(true);
			temp_time->start(Action_Num * 500 + 500);
			QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Move, &AI_Animation::Emit_Move_Signal);
			QObject::connect(AI_Anime_Move, &AI_Animation::Move_Signal, this, &SinglePlayerController::Move);
			Action_Num++;
		}
		else
			_Content->Map()->restoreAllMapUnitColor();
		QTimer::singleShot(Action_Num * 500 + 1000, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
	}

	//要先移动才能达到目标的话，就按照下面来执行
	if (!move_after_attack)
	{
		//选择位置
		for (int i = -temp_step; i < temp_step; i++)
		for (int j = -temp_step; j < temp_step; j++)
		{
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
			if (temp_MapUnit == nullptr) continue;
			if (temp_MapUnit->get_note_state())
			{
				for (int i = 0; i < Alive_Element_Vector.size(); i++)
				{
					int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
					int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
					int small;
					int large;
					if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
					large = X_diff + Y_diff - small;
					int Dis = large + static_cast<int>(0.5*small);

					if (Dis <= element->_character.get_Range_Inc())
					{
						int element_character = element->_character.get_Choose();
						bool whether_remote = false;
						if ((element_character == 2) || (element_character == 5)) whether_remote = true;
						if ((whether_remote) && (Dis > max_Dis))
						{
							max_Dis = Dis;
							whether_target = true;
							target_Element = i;
							target_MapUnit = temp_MapUnit;
						}
						if ((!whether_remote) && (Dis < min_Dis))
						{
							min_Dis = Dis;
							whether_target = true;
							target_Element = i;
							target_MapUnit = temp_MapUnit;
						}
					}
				}
			}
		}

		//如果这轮打不到人就往血最少的家伙走！
		min_Dis = 1024;
		if (!whether_target)
		for (int i = -temp_step; i < temp_step; i++)
		for (int j = -temp_step; j < temp_step; j++)
		{
			MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
			if (temp_MapUnit == nullptr) continue;

			if (temp_MapUnit->get_note_state())
			{
				int i = Alive_Element_Vector.size() - 1;
				int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);

				int element_character = element->_character.get_Choose();
				if (Dis < min_Dis)
				{
					min_Dis = Dis;
					whether_target = true;
					target_Element = i;
					target_MapUnit = temp_MapUnit;
				}
			}
		}


		//是否移动
		if (target_MapUnit != nullptr)
		{
			AI_Anime_Move = new AI_Animation(target_MapUnit);
			QTimer* temp_time = new QTimer(this);
			temp_time->setSingleShot(true);
			temp_time->start(Action_Num * 500);
			QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Move, &AI_Animation::Emit_Move_Signal);
			QObject::connect(AI_Anime_Move, &AI_Animation::Move_Signal, this, &SinglePlayerController::Move);
			Action_Num++;
		}
		else
			_Content->Map()->restoreAllMapUnitColor();

		//判定是否攻击
		if ((target_Element != -1)&&(!UltimateSkill_and_Move))
		{
			QTimer::singleShot(Action_Num * 500 + 500, this, &SinglePlayerController::notePossibleAttackTargetElement);
			Action_Num++;

			AI_Anime_Attack = new AI_Animation(Alive_Element_Vector[target_Element]);
			QTimer* temp_time = new QTimer(this);
			temp_time->setSingleShot(true);
			temp_time->start(Action_Num * 500 + 500);
			QObject::connect(temp_time, &QTimer::timeout, AI_Anime_Attack, &AI_Animation::Emit_Attack_Signal);
			QObject::connect(AI_Anime_Attack, &AI_Animation::Attack_Signal, this, &SinglePlayerController::Attack);
			Action_Num++;
			Dis_Delay += element->_character.get_Distance(Alive_Element_Vector[target_Element]->_character) * 50;

		}
		QTimer::singleShot(Action_Num * 500 + 500 + Dis_Delay, this, &SinglePlayerController::Cancel);//修改：500 -> 1000
	}
}

void SinglePlayerController::AI_Action_HardMode_UltimateSkill_Saber()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	Element* target_enemy = nullptr;

	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy;
		if (element->Index() > 0)
			enemy = _Content->Elements()->get_Element(-i);
		else
			enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 100) && //changed
			(!enemy->_character.Death(_State.Round)))
		{
			if (target_enemy == nullptr) target_enemy = enemy;
			if (enemy->_character.get_HP() > target_enemy->_character.get_HP())
				target_enemy = enemy;
		}
	}
	UltimateSkill_Saber(target_enemy);

	int Dis_Ex_Delay = element->_character.get_Distance(target_enemy->_character) * 30 + 1500;
	QTimer::singleShot(Dis_Ex_Delay, this, &SinglePlayerController::Cancel);

}

void SinglePlayerController::AI_Action_LunaticMode_UltimateSkill_Saber(){
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	Element* target_enemy = nullptr;

	for (int i = 1; i != ELEMENTS_NUM + 1; i++)
	{
		Element* enemy;
		if (element->Index() > 0)
			enemy = _Content->Elements()->get_Element(-i);
		else
			enemy = _Content->Elements()->get_Element(i);
		if ((element->_character.get_Distance(enemy->_character) <= 10) &&
			(!enemy->_character.Death(_State.Round)))
		{
			if (target_enemy == nullptr) target_enemy = enemy;
			if ((25 - enemy->_character.get_HP()) > (25 - target_enemy->_character.get_HP()))
				target_enemy = enemy;
		}
	}
	UltimateSkill_Saber(target_enemy);

	int Dis_Ex_Delay = element->_character.get_Distance(target_enemy->_character) * 30 + 1500;
	QTimer::singleShot(Dis_Ex_Delay, this, &SinglePlayerController::Cancel);
}

void SinglePlayerController::AI_Action_HardMode_UltimateSkill_Caster()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	QVector<Element*> Alive_Element_Vector;
	//这是玩家操控的Element的判定(对于AI的敌人)
	int num_sig = -1;
	if (_State.IsHost) num_sig = 1;

	//把活着的AI敌人加入Vector
	for (int i = 1; i <= 6; i++)
	{
		Element* temp_Element = _Content->Elements()->get_Element(num_sig*i);
		if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector.push_back(temp_Element);
	}
	if (Alive_Element_Vector.size() == 0) return;

	int temp_step = 15;

	int target_MapUnit_Distance = 0;
	MapUnit* target_MapUnit = nullptr;
	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;
		if (temp_MapUnit->get_note_state())
		{
			int tot_Distance = 0;
			for (int i = 0; i < Alive_Element_Vector.size(); i++)
			if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= Alive_Element_Vector[i]->_character.get_Speed())
			{
				int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);
				tot_Distance += Dis;
			}
			if (tot_Distance > target_MapUnit_Distance)
			{
				target_MapUnit = temp_MapUnit;
				target_MapUnit_Distance = tot_Distance;
			}
		}
	}
	UltimateSkill_Caster(target_MapUnit);
}

void SinglePlayerController::AI_Action_LunaticMode_UltimateSkill_Caster()
{
	Element* element = _Content->Elements()->get_Element(_State.AttackSequence.front());

	QVector<Element*> Alive_Element_Vector;
	//这是玩家操控的Element的判定(对于AI的敌人)
	int num_sig = -1;
	if (_State.IsHost) num_sig = 1;

	//把活着的AI敌人加入Vector
	for (int i = 1; i <= 6; i++)
	{
		Element* temp_Element = _Content->Elements()->get_Element(num_sig*i);
		if (!(temp_Element->_character.Death(_State.Round))) Alive_Element_Vector.push_back(temp_Element);
	}
	if (Alive_Element_Vector.size() == 0) return;

	int temp_step = 15;

	int target_MapUnit_Distance = 0;
	MapUnit* target_MapUnit = nullptr;
	for (int i = -temp_step; i < temp_step; i++)
	for (int j = -temp_step; j < temp_step; j++)
	{
		MapUnit* temp_MapUnit = _Content->Map()->get_MapUnit_around(element->_character.get_X(), element->_character.get_Y(), i, j);
		if (temp_MapUnit == nullptr) continue;
		if (temp_MapUnit->get_note_state())
		{
			int tot_Distance = 0;
			for (int i = 0; i < Alive_Element_Vector.size(); i++)
			if (element->_character.get_Distance(Alive_Element_Vector[i]->_character) <= Alive_Element_Vector[i]->_character.get_Speed())
			{
				int X_diff = abs(Alive_Element_Vector[i]->_character.get_X() - temp_MapUnit->Xcell());
				int Y_diff = abs(Alive_Element_Vector[i]->_character.get_Y() - temp_MapUnit->Ycell());
				int small;
				int large;
				if (X_diff>Y_diff) small = Y_diff; else small = X_diff;
				large = X_diff + Y_diff - small;
				int Dis = large + static_cast<int>(0.5*small);
				tot_Distance += Dis;
			}
			if (tot_Distance > target_MapUnit_Distance)
			{
				target_MapUnit = temp_MapUnit;
				target_MapUnit_Distance = tot_Distance;
			}
		}
	}
	UltimateSkill_Caster(target_MapUnit);
}


/**** Element_Animation ****/
Element_Animation::Element_Animation(Element* ActionElement)
{
	_ActionElement = ActionElement;
}

Element_Animation::Element_Animation(Element* ActionElement, int Damage)
{
	_ActionElement = ActionElement;
	_Damage = Damage;
}

Element_Animation::Element_Animation(Element* ActionElement, int Round, PanelHeadUp* HeadUp)
{
	_ActionElement = ActionElement;
	_Round = Round;
	_HeadUp = HeadUp;
}

void Element_Animation::Emit_Hide_Signal()
{
	_ActionElement->hide();
}

void Element_Animation::Emit_Damage_Signal()
{
	emit Damage_signal(_Damage);
}

void Element_Animation::Emit_Set_Health_Signal()
{
	_HeadUp->set_health(_ActionElement->Index(), _ActionElement->_character.get_HP(), _ActionElement->_character.get_Max_HP(), _ActionElement->_character.Death(_Round));
}

void Element_Animation::Emit_Tomb_Note_Signal()
{
	_ActionElement->tomb_note();
}


/**** AI_Animation ****/
AI_Animation::AI_Animation(MapUnit* target)
{
	_target = target;
}

AI_Animation::AI_Animation(Element* enemy)
{
	_enemy = enemy;
}

void AI_Animation::Emit_Move_Signal()
{
	emit Move_Signal(_target);
}

void AI_Animation::Emit_Attack_Signal()
{
	emit Attack_Signal(_enemy);
}

