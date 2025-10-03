#pragma once

namespace df {
	class Vector {
	private:
		// Components (x, y)
		float m_x;
		float m_y;

	public:
		Vector(); // Default constructor: (0, 0)
		Vector(float init_x, float init_y); // Constructor (x, y)

		// Getters and setters for components
		void setX(float new_x);
		float getX() const;
		void setY(float new_y);
		float getY() const;
		void setXY(float new_x, float new_y);

		// Return magnitute ( sqrt[x^2 + y^2] )
		float getMagnitude() const;

		// Normalize ( set magnitude to 1, becomes a unit vector )
		void normalize();

		// Scale vector
		void scale(float s);

		// Basic Operators
		Vector operator+(const Vector& other) const;
		Vector operator-(const Vector& other) const;
		Vector operator*(const Vector& other) const;
		Vector operator/(const Vector& other) const;
		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;
	};
}