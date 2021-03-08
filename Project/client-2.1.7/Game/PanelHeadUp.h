#ifndef PANELHEADUP_H
#define PANELHEADUP_H

#include <QFrame>
#include <QPainter>
#include <QBitmap>
#include "constant.h"
#include "ButtonBase.h"
#include <QGraphicsView>
#include <QGraphicsColorizeEffect>
#include <qvector.h>
#include <qstring.h>
#include <qpropertyanimation.h>
#include <qtimer.h>

class Set_Health_Animation;

class PanelHeadUp : public QFrame
{
	Q_OBJECT

public:
	PanelHeadUp(QWidget *parent = 0);
	~PanelHeadUp();
	void EmitShowMenuSignal();
	void EmitShowBattleInfoSignal();
	void set_health(int _Index, int HP, int max_HP, bool Death, bool Death_to_Alive = false);
	void set_health_end(int idx_temp, int HP, int max_HP);
	void set_health_color(int idx_temp, QColor color);
	void set_Death(int idx_temp);
	QVector<QPushButton*> GraphicsItem;
signals:
	void ShowMenu_HeadUpToView_Signal();
	void ShowPanelBattleInfo_Signal();
private:
	QFrame *_MainMenu;
	ButtonBase *_btMainMenu;
	ButtonBase *_btPanelBattleInfo;
	
	QVector<QWidget*> HealthItem;
	//Ϊ������ֵ�����ı���
	Set_Health_Animation* SHAnime[12];
	//Ϊ��ˢ��Ѫ����ɫ�Ĵ��ݱ���
	Set_Health_Animation* SHAnime_color[12][100];
	//Ϊ��ˢ��Ѫ����ɫ��timer�ļ�����
	QTimer* msec_50[12][100];
	//��������
	Set_Health_Animation* SHAnime_death[12];
};

//����һ��Ϊ�˶������� ��ܾͺ�
class Set_Health_Animation :public QObject
{
	Q_OBJECT
public:
	Set_Health_Animation(int idx_temp, int HP, int max_HP);
	Set_Health_Animation(int idx_temp, QColor color);
	Set_Health_Animation(int idx_temp);
	void emit_set_health_end_signal();
	void emit_set_health_color_signal();
	void emit_set_death_signal();
signals:
	void set_health_end_signal(int idx_temp,  int HP, int max_HP);
	void set_health_color_signal(int idx_temp, QColor color);
	void set_death_signal(int idx_temp);
private:
	int _idx_temp;
	int _HP;
	int _max_HP;
	QColor _Color;
};
#endif