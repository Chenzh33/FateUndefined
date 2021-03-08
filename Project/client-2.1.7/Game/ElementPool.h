#ifndef ELEMENTPOOL_H
#define ELEMENTPOOL_H

#include "Element.h"

class ElementPool
{
public:
	ElementPool();
	~ElementPool();
	int addElement(Element *);
	//bool CheckIsInMyElementPool(QGraphicsItem *obj,bool IsHost);
	int get_item_index_in_ElementPool(QGraphicsItem *obj);
	Element* get_Element(int n);
	Element* get_Element_with_pos(int x, int y);
	void restoreAllEnemyElementColor(bool IsHost);

private:
	QVector<Element*> m_Elements;

};
#endif