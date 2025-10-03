#include "Object.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

df::Object::Object()
{
	static int nextid;
	setId(nextid);
	nextid++;

	setType("Object");
	Vector pos;
	setPosition(pos);
	setAltitude(MAX_ALTITUDE / 2);

	setVelocity(Vector(0, 0));
	setSolidness(HARD);

	setAnimation(Animation());

	setBox(Box(pos, 1, 1));

	WM.insertObject(this);
}

df::Object::~Object()
{
	WM.removeObject(this);
}

// Getters and Setters
#pragma region GetSet
void df::Object::setId(int new_id)
{
	m_id = new_id;
}

int df::Object::getId() const
{
	return m_id;
}

void df::Object::setType(std::string new_type) {
	m_type = new_type;
}

std::string df::Object::getType() const {
	return m_type;
}

void df::Object::setPosition(Vector new_pos)
{
	m_position = new_pos;
}

df::Vector df::Object::getPosition() const
{
	return m_position;
}

int df::Object::setAltitude(int newAltitude)
{
	if (newAltitude < 0 || newAltitude > MAX_ALTITUDE)
	{
		return -1;
	}
	m_altitude = newAltitude;
	return 0;
}

int df::Object::getAltitude() const
{
	return m_altitude;
}

void df::Object::setSpeed(float speed) {
	m_speed = speed;
}
float df::Object::getSpeed() const {
	return m_speed;
}
void df::Object::setDirection(Vector new_direction) {
	m_direction = new_direction;
}
df::Vector df::Object::getDirection() const {
	return m_direction;
}
void df::Object::setVelocity(Vector new_velocity) {
	m_speed = new_velocity.getMagnitude();
	new_velocity.normalize();
	m_direction = new_velocity;
}
df::Vector df::Object::getVelocity() const {
	Vector out = m_direction;
	out.scale(m_speed);
	return out;
}
df::Vector df::Object::predictPosition() {
	Vector new_pos = m_position + getVelocity();
	return new_pos;
}

int df::Object::setSolidness(Solidness new_solidness)
{
	if (new_solidness == m_solidness)
	{
		return -1;
	}
	m_solidness = new_solidness;
	return 0;
}

df::Solidness df::Object::getSolidness() const
{
	return m_solidness;
}

bool df::Object::isSolid() const
{
	return (m_solidness == HARD || m_solidness == SOFT);
}

int df::Object::setSprite(std::string sprite_label)
{
	Sprite* s = RM.getSprite(sprite_label);
	if (s == NULL)
	{
		return -1;
	}
	m_animation.setSprite(s);
	setBox(m_animation.getBox());
	return 0;
}

void df::Object::setAnimation(Animation newAnimation)
{
	m_animation = newAnimation;
	setBox(m_animation.getBox());
}

df::Animation df::Object::getAnimation() const
{
	return m_animation;
}

void df::Object::setBox(Box new_box)
{
	m_box = new_box;
}

df::Box df::Object::getBox() const
{
	return m_box;
}

#pragma endregion GetSet

int df::Object::eventHandler(const Event* p_e)
{
	return 0;
}

int df::Object::draw() {
	m_animation.draw(getPosition());
	return 0;
}