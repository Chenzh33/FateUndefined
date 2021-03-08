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

int ElementPool::get_item_index_in_ElementPool(QGraphicsItem *obj){
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

Element* ElementPool::get_Element_with_pos(int x, int y)
{
	for (int i = 0; i != ELEMENTS_NUM * 2; i++)
	if ((m_Elements[i]->_character.get_X() == x) && 
		(m_Elements[i]->_character.get_Y() == y) &&
		(!(m_Elements[i]->_character.Death(m_Elements[i]->_character.get_Round_Death())) ||
		(m_Elements[i]->_character.get_Choose() == 6 && 
		m_Elements[i]->_character.get_Round() - m_Elements[i]->_character.get_Round_Death() < 2)))
		return m_Elements[i];
	return nullptr;
}

void ElementPool::restoreAllEnemyElementColor(bool IsHost)
{
	for (int i = 0; i != ELEMENTS_NUM; i++){
		if (IsHost){
			if (m_Elements[i + 6]->get_note_state())
				m_Elements[i + 6]->restore();
		}
		else{
			if (m_Elements[i]->get_note_state())
				m_Elements[i]->restore();
		}		
	}
}
