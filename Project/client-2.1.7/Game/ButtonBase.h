#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include <QPushButton>
#include <QMouseEvent>
#include <QBitmap>

class ButtonBase : public QPushButton
{
	Q_OBJECT
public:
	ButtonBase(QWidget *parent);
	void setSizeGeometry(int x, int y, int width, int height);
	void setButtonPicture(QPixmap pic);
	void setPressPicture(QPixmap pic);
	void setReleasePicture(QPixmap pic);
private:
	//event
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	//picture members
	QPixmap *_ButtonPicture;
	QPixmap *_PressPicture;
	QPixmap *_ReleasePicture;

};



















#endif