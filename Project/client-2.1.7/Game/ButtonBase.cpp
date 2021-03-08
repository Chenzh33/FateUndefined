#include "ButtonBase.h"

ButtonBase::ButtonBase(QWidget *parent) : QPushButton(parent)
{
	_ButtonPicture = new QPixmap();
	_PressPicture = new QPixmap();
	_ReleasePicture = new QPixmap();
	this->setFlat(true);
	this->setMouseTracking(true);
}

void ButtonBase::setSizeGeometry(int x, int y, int width, int height)
{
	this->setIconSize(QSize(width, height));
	this->setGeometry(x, y, width, height);
}

void ButtonBase::setButtonPicture(QPixmap pic)
{
	*_ButtonPicture = pic;
	this->setIcon(QIcon(*_ButtonPicture));
	this->setMask(pic.createHeuristicMask());
}

void ButtonBase::setPressPicture(QPixmap pic)
{
	*_PressPicture = pic;
}

void ButtonBase::setReleasePicture(QPixmap pic)
{
	*_ReleasePicture = pic;
}

void ButtonBase::mousePressEvent(QMouseEvent *e)
{
	this->setIcon(QIcon(*_PressPicture));
}

void ButtonBase::mouseMoveEvent(QMouseEvent *e)
{
	//	
}

void ButtonBase::mouseReleaseEvent(QMouseEvent *e)
{
	this->setIcon(QIcon(*_ReleasePicture));
	emit clicked();
}