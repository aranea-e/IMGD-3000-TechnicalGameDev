#include "Animation.h"

df::Animation::Animation()
{
	m_p_sprite = NULL;
	m_name = "";
	m_index = 0;
	m_slowdown_count = 0;
}

void df::Animation::setSprite(Sprite* p_new_sprite)
{
	m_p_sprite = p_new_sprite;
	m_index = 0;
	m_slowdown_count = 0;
}

df::Sprite* df::Animation::getSprite() const
{
	return m_p_sprite;
}

void df::Animation::setName(std::string new_name)
{
	m_name = new_name;
}

std::string df::Animation::getName() const
{
	return m_name;
}

void df::Animation::setIndex(int new_index)
{
	m_index = new_index;
}

int df::Animation::getIndex() const
{
	return m_index;
}

void df::Animation::setSlowdownCount(int new_slowdown_count)
{
	m_slowdown_count = new_slowdown_count;
}

int df::Animation::getSlowdownCount() const
{
	return m_slowdown_count;
}

df::Box df::Animation::getBox() const{
	if (m_p_sprite == NULL)
	{
		return Box(Vector(-0.5, -0.5), 0.99, 0.99);
	}
	Vector corner(-1 * m_p_sprite->getWidth() / 2.0,
		-1 * m_p_sprite->getHeight() / 2.0);
	Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());
	return box;
}

int df::Animation::draw(Vector position)
{
	Sprite* p_sprite = getSprite();
	if (p_sprite == NULL)
	{
		return -1;
	}

	int index = getIndex();
	p_sprite->draw(index, position);
	if (getSlowdownCount() == -1) {
		return 0;
	}
	int count = getSlowdownCount();
	count++;
	if (count > p_sprite->getSlowdown()) {
		count = 0;
		index++;
		if (index >= p_sprite->getFrameCount())
		{
			index = 0;
		}
		setIndex(index);
	}
	setSlowdownCount(count);
	return 0;
}
