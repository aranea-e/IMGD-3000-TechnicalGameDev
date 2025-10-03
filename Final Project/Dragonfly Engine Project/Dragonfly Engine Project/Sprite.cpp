#include "Sprite.h"

df::Sprite::~Sprite()
{
	if (m_frame != NULL)
	{
		delete[] m_frame;
	}
}

df::Sprite::Sprite(int max_frames)
{
	m_frame_count = 0;
	m_width = 0;
	m_height = 0;
	m_frame = new Frame[max_frames];
	m_max_frame_count = max_frames;
	m_color = COLOR_DEFAULT;
}

void df::Sprite::setWidth(int new_width) {
	m_width = new_width;
}

int df::Sprite::getWidth() const {
	return m_width;
}

void df::Sprite::setHeight(int new_height) {
	m_height = new_height;
}

int df::Sprite::getHeight() const {
	return m_height;
}

void df::Sprite::setColor(Color new_color)
{
	m_color = new_color;
}

df::Color df::Sprite::getColor() const
{
	return m_color;
}

int df::Sprite::getFrameCount() const
{
	return m_frame_count;
}

int df::Sprite::addFrame(Frame new_frame)
{
	if (m_frame_count >= m_max_frame_count)
	{
		return -1;
	}
	m_frame[m_frame_count] = new_frame;
	m_frame_count++;
	return 0;
}

df::Frame df::Sprite::getFrame(int frame_number) const
{
	if ((frame_number < 0) || (frame_number >= m_frame_count)) {
		Frame empty;
		return empty;
	}

	return m_frame[frame_number];
}

void df::Sprite::setLabel(std::string new_label)
{
	m_label = new_label;
}

std::string df::Sprite::getLabel() const
{
	return m_label;
}

void df::Sprite::setSlowdown(int new_sprite_slowdown)
{
	m_slowdown = new_sprite_slowdown;
}

int df::Sprite::getSlowdown() const
{
	return m_slowdown;
}

int df::Sprite::draw(int frame_number, Vector position) const
{
	return m_frame[frame_number].draw(position, m_color);
}

