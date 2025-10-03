#pragma once

#include <string>

#include "Vector.h"
#include "Color.h"

namespace df {
	class Frame {
	private:
		int m_width;	// Frame width
		int m_height;	// Frame height
		std::string m_frame_str;	// All chars in frame

	public:
		Frame();	// Empty frame
		Frame(int new_width, int new_height, std::string frame_str); // Frame with indicated width, height, and string

		void setWidth(int new_width);
		int getWidth() const;
		void setHeight(int new_height);
		int getHeight() const;
		void setString(std::string new_frame_str);
		std::string getString() const;

		// Draw self at position (x, y) with color.
		// Return 0 if ok, else -1
		// Top-left coordinate is (0, 0)
		int draw(Vector position, Color color) const;
	};
}