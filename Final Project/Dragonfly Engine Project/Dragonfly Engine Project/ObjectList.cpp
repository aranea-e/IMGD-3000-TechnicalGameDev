#include <stdexcept>

#include "ObjectList.h"
#include "LogManager.h"

df::ObjectList::ObjectList()
{
	m_count = 0;
}

int df::ObjectList::insert(Object* p_o)
{
	if (m_count == MAX_OBJECTS) { return -1; }
	m_p_obj[m_count] = p_o;
	m_count++;
	return 0;
}

int df::ObjectList::remove(Object* p_o)
{
	for (int i = 0; i < m_count; i++)
	{
		if (m_p_obj[i] == p_o) {
			m_count--;
			for (int j = i; j < m_count; j++)
			{
				m_p_obj[j] = m_p_obj[j + 1];
			}
			return 0;
		}
	}
	return -1;
}

void df::ObjectList::clear() {
	m_count = 0;
}

int df::ObjectList::getCount() const
{
	return m_count;
}

bool df::ObjectList::isEmpty() const
{
	return m_count == 0;
}

bool df::ObjectList::isFull() const
{
	return m_count == MAX_OBJECTS;
}

df::Object* df::ObjectList::operator[](int index) const
{
	if (index >= m_count || index < 0)
	{
		throw std::out_of_range("Invalid index!");
	}
	return m_p_obj[index];
}
