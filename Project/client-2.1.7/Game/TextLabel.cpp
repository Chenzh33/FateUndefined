#include "TextLabel.h"

TextLabel::TextLabel(QString text, QWidget *parent = 0, int Type = 0) :QLabel(parent)
{
	if (Type == 0)
		setGeometry(VIEW_WIDTH / 2 - 200, VIEW_HEIGHT / 2 - 100, 500, 135);
	if (Type == 1)
		setGeometry(VIEW_WIDTH / 2 - 200, VIEW_HEIGHT / 2 - 250, 500, 135);
	setFont(QFont("Algerian", 150, QFont::Bold));
	setText(text);
	QGraphicsColorizeEffect *_ColorEffect = new QGraphicsColorizeEffect(this);
	_ColorEffect->setColor(QColor(255, 204, 0));
	_ColorEffect->setStrength(1);

	this->setGraphicsEffect(_ColorEffect);
}

void TextLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	QPainter painter(this);
	painter.drawText(QPoint(0, 0), text());
}