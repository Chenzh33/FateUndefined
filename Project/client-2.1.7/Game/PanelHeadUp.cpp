#include "PanelHeadUp.h"

PanelHeadUp::PanelHeadUp(QWidget *parent) : QFrame(parent)
{
	this->setGeometry(QRect(-20, 0, 1320, 90));
	this->setStyleSheet(QLatin1String("image: url(:/IconSrc/Panel_headup);"""));
	_btMainMenu = new ButtonBase(this);
	_btMainMenu->setSizeGeometry(50, -30, 80, 80);
	_btMainMenu->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_headup)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_headup_2)}");
	QObject::connect(_btMainMenu, &ButtonBase::clicked, this, &PanelHeadUp::EmitShowMenuSignal);

	_btPanelBattleInfo = new ButtonBase(this);
	_btPanelBattleInfo->setSizeGeometry(615, -10, 100, 100);
	_btPanelBattleInfo->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_BattleInfo)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_BattleInfo_2)}");
	QObject::connect(_btPanelBattleInfo, &ButtonBase::clicked, this, &PanelHeadUp::EmitShowBattleInfoSignal);

	QVector<QString> Class;

	Class.push_back("Saber");
	Class.push_back("Archer");
	Class.push_back("Rider");
	Class.push_back("Assassin");
	Class.push_back("Caster");
	Class.push_back("Berserker");
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 6; j++)
	{
		QPushButton *temp;
		QIcon tempicon;
		temp = new QPushButton(this);
		temp->setGeometry(QRect(150 + 68.5 * j + 626.4 * i, 0, 66, 36));
		QString tempString = { ":/IconSrc/" + Class[j] + "_headup" };
		tempicon.addFile(tempString, QSize(), QIcon::Normal, QIcon::Off);
		temp->setIcon(tempicon);
		temp->setIconSize(QSize(66, 36));
		temp->setMask(QPixmap(tempString).createHeuristicMask());
		GraphicsItem.push_back(temp);

		QPushButton *healthtemp;
		QIcon healthtempicon;
		healthtemp = new QPushButton(this);
		healthtemp->setGeometry(QRect(150 + 68.5 * j + 626.4 * i, 37.5, 66, 4));
		
		healthtempicon.addFile(QStringLiteral(":/IconSrc/health_basic"), QSize(), QIcon::Normal, QIcon::Off);
		healthtemp->setIcon(healthtempicon);
		healthtemp->setIconSize(QSize(66, 4));
		healthtemp->setMask(QPixmap(":/IconSrc/health_basic").createHeuristicMask());

		QGraphicsColorizeEffect* ColorEffect = new QGraphicsColorizeEffect();
		ColorEffect->setColor(QColor(0, 255, 0));
		healthtemp->setGraphicsEffect(ColorEffect);
		HealthItem.push_back(healthtemp);
	}

	this->show();
}

PanelHeadUp::~PanelHeadUp()
{

}


void PanelHeadUp::EmitShowMenuSignal()
{
	emit ShowMenu_HeadUpToView_Signal();
}

void PanelHeadUp::EmitShowBattleInfoSignal()
{
	emit ShowPanelBattleInfo_Signal();
}

void PanelHeadUp::set_health(int _Index, int HP, int max_HP, bool Death, bool Death_to_Alive)
{
	int idx_temp = _Index > 0 ? _Index - 1 : 5 - _Index;
	if (HP <= 0) HP = 1;

	double deltaX = HealthItem[idx_temp]->geometry().width() - 66.0 * static_cast<double>(HP) / static_cast<double>(max_HP);
	deltaX = abs(deltaX);
	double delta = static_cast<double>(HP) / max_HP;
	int new_Green = (delta * 510) > 255 ? 255 : (delta * 510);
	int new_Red = (510 - (delta * 510)) > 255 ? 255 : (510 - (delta * 510));

	double old_delta = static_cast<double>(HealthItem[idx_temp]->geometry().width()) / 66;
	int old_Green = (old_delta * 510) > 255 ? 255 : (old_delta * 510);
	int old_Red = (510 - (old_delta * 510)) > 255 ? 255 : (510 - (old_delta * 510));

	if ((old_delta - delta < 0.00001) && (Death))
	{
		HealthItem[idx_temp]->hide();
		QGraphicsColorizeEffect *Effect = new QGraphicsColorizeEffect();
		Effect->setColor(QColor(0, 0, 0));
		GraphicsItem[idx_temp]->setGraphicsEffect(Effect);
		return;
	}

	
	QPropertyAnimation* MoveAnime = new QPropertyAnimation(HealthItem[idx_temp], "geometry");
	MoveAnime->setDuration(deltaX * 50);
	MoveAnime->setStartValue(HealthItem[idx_temp]->geometry());
	MoveAnime->setEndValue(QRect(150 + 68.5 * (idx_temp - idx_temp / 6 * 6) + 626.4 * (idx_temp / 6), 37.5, 66.0 * static_cast<double>(HP) / static_cast<double>(max_HP), 4));
	MoveAnime->start();
	
	
	for (int i = 0; i < static_cast<int>(deltaX); i++)
	{
		msec_50[idx_temp][i] = new QTimer(this);
		msec_50[idx_temp][i]->setSingleShot(true);
		
		double now_delta = (delta - old_delta)*i / deltaX + old_delta;
		int now_Green = (now_delta * 510) > 255 ? 255 : (now_delta * 510);
		int now_Red = (510 - (now_delta * 510)) > 255 ? 255 : (510 - (now_delta * 510));

		SHAnime_color[idx_temp][i] = new Set_Health_Animation(idx_temp, QColor(now_Red, now_Green, 0));
		QObject::connect(msec_50[idx_temp][i], &QTimer::timeout, SHAnime_color[idx_temp][i], &Set_Health_Animation::emit_set_health_color_signal);
		QObject::connect(SHAnime_color[idx_temp][i], &Set_Health_Animation::set_health_color_signal, this, &PanelHeadUp::set_health_color);

		msec_50[idx_temp][i]->start(i * 50);
	}

	SHAnime[idx_temp] = new Set_Health_Animation(idx_temp, HP, max_HP);

	QObject::connect(MoveAnime, &QPropertyAnimation::finished, SHAnime[idx_temp], &Set_Health_Animation::emit_set_health_end_signal);
	QObject::connect(SHAnime[idx_temp], &Set_Health_Animation::set_health_end_signal, this, &PanelHeadUp::set_health_end);

	if (Death)
	{
		SHAnime_death[idx_temp] = new Set_Health_Animation(idx_temp);
		QObject::connect(MoveAnime, &QPropertyAnimation::finished, SHAnime_death[idx_temp], &Set_Health_Animation::emit_set_death_signal);
		QObject::connect(SHAnime_death[idx_temp], &Set_Health_Animation::set_death_signal, this, &PanelHeadUp::set_Death);
	}

	if (Death_to_Alive)
	{
		HealthItem[idx_temp]->show();
		QGraphicsColorizeEffect* Effect = new QGraphicsColorizeEffect();
		Effect->setColor(QColor(204, 0, 0));
		Effect->setStrength(0.4);
		GraphicsItem[idx_temp]->setGraphicsEffect(Effect);
	}
}

void PanelHeadUp::set_health_end(int idx_temp, int HP, int max_HP)
{
	HealthItem[idx_temp]->setGeometry(QRect(150 + 68.5 * (idx_temp - idx_temp / 6 * 6) + 626.4 * (idx_temp / 6), 37.5, 66.0 * static_cast<double>(HP) / static_cast<double>(max_HP), 4));
}

void PanelHeadUp::set_health_color(int idx_temp, QColor color)
{
	QGraphicsColorizeEffect* ColorEffect = new QGraphicsColorizeEffect();
	int red = color.red();
	int green = color.green();
	ColorEffect->setColor(color);
	HealthItem[idx_temp]->setGraphicsEffect(ColorEffect);

}

void PanelHeadUp::set_Death(int idx_temp)
{
	HealthItem[idx_temp]->hide();
	QGraphicsColorizeEffect* Effect = new QGraphicsColorizeEffect();
	Effect->setColor(QColor(0, 0, 0));
	GraphicsItem[idx_temp]->setGraphicsEffect(Effect);	
}

void Set_Health_Animation::emit_set_health_end_signal()
{
	emit set_health_end_signal(_idx_temp, _HP, _max_HP);
}

void Set_Health_Animation::emit_set_health_color_signal()
{
	emit set_health_color_signal(_idx_temp, _Color);
}

void Set_Health_Animation::emit_set_death_signal()
{
	emit set_death_signal(_idx_temp);
}

Set_Health_Animation::Set_Health_Animation(int idx_temp, int HP, int max_HP)
{
	_idx_temp = idx_temp;
	_HP = HP;
	_max_HP = max_HP;
}

Set_Health_Animation::Set_Health_Animation(int idx_temp, QColor color)
{
	_idx_temp = idx_temp;
	_Color = color;
}

Set_Health_Animation::Set_Health_Animation(int idx_temp)
{
	_idx_temp = idx_temp;
}