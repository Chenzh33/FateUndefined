#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include <QPaintEvent>
#include <QTimer>
#include <QFont>
#include <QGraphicsEffect>
#include <QPainter>
#include <qlabel.h>
#include "constant.h"


class TextLabel : public QLabel
{
	Q_OBJECT
	Q_PROPERTY(qreal windowOpacity READ windowOpacity WRITE setWindowOpacity)

public:
	TextLabel(QString text, QWidget *parent, int Type);

private:
	void TextLabel::paintEvent(QPaintEvent *event);

};
#endif