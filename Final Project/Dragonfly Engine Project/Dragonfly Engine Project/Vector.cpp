#include <cmath>

#include "Vector.h"

df::Vector::Vector()
{
	m_x = 0;
	m_y = 0;
}

df::Vector::Vector(float init_x, float init_y)
{
	m_x = init_x;
	m_y = init_y;
}

// Getters and Setters
#pragma region GetSet
void df::Vector::setX(float new_x)
{
	m_x = new_x;
}

float df::Vector::getX() const
{
	return m_x;
}

void df::Vector::setY(float new_y)
{
	m_y = new_y;
}

float df::Vector::getY() const
{
	return m_y;
}

void df::Vector::setXY(float new_x, float new_y)
{
	setX(new_x);
	setY(new_y);
}
#pragma endregion GetSet

// Returns sqrt(x^2 + y^2)
float df::Vector::getMagnitude() const
{
	return std::sqrt(getX() * getX() + getY() * getY());
}

// Finds magnitude, then scales vector by (1 / magnitude) to set magnitude to 1
void df::Vector::normalize()
{
	if (getMagnitude() > 0) scale(1 / getMagnitude());
}

// Multiplies components by scale
void df::Vector::scale(float s)
{
	m_x *= s;
	m_y *= s;
}

// Basic operators
#pragma region Operators
df::Vector df::Vector::operator+(const Vector& other) const // Add
{
	return Vector((getX() + other.getX()), (getY() + other.getY()));
}

df::Vector df::Vector::operator-(const Vector& other) const // Subtract
{
	return Vector((getX() - other.getX()), (getY() - other.getY()));
}

df::Vector df::Vector::operator*(const Vector& other) const // Multiply
{
	return Vector((getX() * other.getX()), (getY() * other.getY()));
}

df::Vector df::Vector::operator/(const Vector& other) const // Divide
{
	return Vector((getX() / other.getX()), (getY() / other.getY()));
}

bool df::Vector::operator==(const Vector& other) const // Equality
{
	return ((getX() == other.getX()) && (getY() == other.getY()));
}

bool df::Vector::operator!=(const Vector& other) const // Inequality
{
	return !(this == &other);
}
#pragma endregion Operators