#include "GameMainMenu.h"

GameMainMenu::GameMainMenu(GameContent *content, QWidget *parent = 0) : QFrame(parent)
{
	_Content = content;

	this->setObjectName("GameMainMenu");
	this->setStyleSheet("QFrame#GameMainMenu{background-image:url(:/IconSrc/GameMainMenu)}");
	this->setGeometry(VIEW_WIDTH / 2 - 200, VIEW_HEIGHT / 2 - 150, 400, 300);
	this->setFixedSize(400, 300);
	this->setWindowFlags(Qt::FramelessWindowHint);

	QLabel* text_BGM_volume = new QLabel("Background VOL", this);
	text_BGM_volume->setGeometry(50, 80, 240, 20);
	text_BGM_volume->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_BGM = new QGraphicsColorizeEffect(text_BGM_volume);
	ColorEffect_BGM->setColor(QColor(255, 204, 0));
	text_BGM_volume->setGraphicsEffect(ColorEffect_BGM);

	_slBackgroundMusicVolume = new QSlider(Qt::Horizontal, this);
	_slBackgroundMusicVolume->setGeometry(50, 110, 300, 20);
	_slBackgroundMusicVolume->setRange(0, 100);
	_slBackgroundMusicVolume->setValue(_Content->Settings()->BackgroundMusicVolume);

	QLabel* text_Effect_volume = new QLabel("Effect VOL", this);
	text_Effect_volume->setGeometry(50, 140, 180, 20);
	text_Effect_volume->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Effect = new QGraphicsColorizeEffect(text_Effect_volume);
	ColorEffect_Effect->setColor(QColor(255, 204, 0));
	text_Effect_volume->setGraphicsEffect(ColorEffect_Effect);

	_slEffectVolume = new QSlider(Qt::Horizontal, this);
	_slEffectVolume->setGeometry(50, 170, 300, 20);
	_slEffectVolume->setRange(0, 100);
	_slEffectVolume->setValue(_Content->Settings()->EffectVolume);

	_btResume = new ButtonBase(this);
	_btResume->setSizeGeometry(130, 200, 140, 40);
	_btResume->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Resume)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Resume_2)}");

	_btQuit = new ButtonBase(this);
	_btQuit->setSizeGeometry(130, 240, 140, 40);
	_btQuit->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Quit)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Quit_2)}");

	QObject::connect(_slBackgroundMusicVolume, &QSlider::valueChanged, _Content, &GameContent::ChangeBackgroundMusicVolume);
	QObject::connect(_slEffectVolume, &QSlider::valueChanged, _Content, &GameContent::ChangeEffectVolume);

	QObject::connect(_btQuit, &QPushButton::clicked, this, &GameMainMenu::Quit_Signal);
	QObject::connect(_btResume, &QPushButton::clicked, this, &GameMainMenu::EmitResumeSignal);


	this->show();

}

GameMainMenu::~GameMainMenu()
{

}

void GameMainMenu::EmitResumeSignal()
{
	emit Resume_Signal();
}

void GameMainMenu::EmitQuitSignal()
{
	emit Quit_Signal();
}