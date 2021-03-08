#include "tcpserver.h"

tcpserver::tcpserver(QWidget *parent, Qt::WindowFlags f)
: QDialog(parent, f)
{
	setWindowTitle(tr("TCP Server"));

	ContentListWidget = new QListWidget(this);

	PortLabel = new QLabel(QStringLiteral("端口："));
	PortLineEdit = new QLineEdit;

	CreateBtn = new QPushButton(QStringLiteral("创建服务器"));

	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(ContentListWidget, 0, 0, 1, 2);
	mainLayout->addWidget(PortLabel, 1, 0);
	mainLayout->addWidget(PortLineEdit, 1, 1);
	mainLayout->addWidget(CreateBtn, 2, 0, 1, 2);

	port = 8010;
	PortLineEdit->setText(QString::number(port));

	connect(CreateBtn, SIGNAL(clicked()), this, SLOT(slotCreateServer()));
}

tcpserver::~tcpserver()
{

}

void tcpserver::slotCreateServer()
{
	server = new Server(this, port);
	connect(server, SIGNAL(updateServer(QString)), this, SLOT(updateServer(QString)));

	CreateBtn->setEnabled(false);
}

void tcpserver::updateServer(QString msg)
{
	ContentListWidget->addItem(msg.left(msg.length()));
}

