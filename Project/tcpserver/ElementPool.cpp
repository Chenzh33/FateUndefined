#include "ElementPool.h"

ElementPool::ElementPool()
{
	this->m_Elements.reserve(ELEMENTS_NUM * 2);

}

ElementPool::~ElementPool()
{

}

int ElementPool::addElement(Element* element)
{
	m_Elements.push_back(element);
	return m_Elements.size() - 1;
}

/*bool ElementPool::CheckIsInMyElementPool(QGraphicsItem *obj, bool IsHost)
{
	for (int i = 0; i != m_Elements.size();i++){
		if (m_Elements[i] == static_cast<Element*>(obj)){
			if (IsHost && i >= 0 && i < ELEMENTS_NUM ||
				!IsHost && i >= ELEMENTS_NUM && i < m_Elements.size())
				return true;
		};
	}
	return false;
}*/

int ElementPool::get_item_index_in_ElementPool(Element *obj){
	for (int i = 0; i != m_Elements.size(); i++){
		if (m_Elements[i] == static_cast<Element*>(obj)){
			if (i >= 0 && i < ELEMENTS_NUM)
				return i + 1;
			else if (i >= ELEMENTS_NUM && i < m_Elements.size())
				return 5 - i;
		}
	}
	return 0;
}

Element* ElementPool::get_Element(int index)
{
	if (index > 0)
		return m_Elements[index - 1];
	else
		return m_Elements[ELEMENTS_NUM - 1 - index];
}

/*void ElementPool::restoreAllEnemyElementColor(bool IsHost)
{
	for (int i = 0; i != ELEMENTS_NUM; i++){
		if (IsHost)
			m_Elements[i + 6]->restore();
		else
			m_Elements[i]->restore();
	}
}*/
