#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtWidgets/QMainWindow>
//#include "ui_tcpserver.h"
#include"qdialog.h"
#include"qlistwidget.h"
#include"qlabel.h"
#include"qlineedit.h"
#include"qpushbutton.h"
#include"qgridlayout.h"

#include"server.h"

class tcpserver : public QDialog
{
	Q_OBJECT

public:
	tcpserver(QWidget *parent = 0,Qt::WindowFlags f=0);
	~tcpserver();

private:
	//Ui::tcpserverClass ui;
	QListWidget *ContentListWidget;
	QLabel *PortLabel;
	QLineEdit *PortLineEdit;
	QPushButton *CreateBtn;
	QGridLayout *mainLayout;
	int port;
	Server *server;
public slots:
	void slotCreateServer();
	void updateServer(QString);
};

#endif // TCPSERVER_H
