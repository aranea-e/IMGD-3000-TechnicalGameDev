#pragma once

#include <string>

#include "Frame.h"

namespace df {
	class Sprite {
	private:
		int m_width;			// Sprite width
		int m_height;			// Sprite height	
		int m_max_frame_count;	// Max number of frames
		int m_frame_count;		// Actual number of frames
		Color m_color;			// Optional color for sprite
		int m_slowdown;			// Animation slowdown (1=no slowdown, 0=stop)
		Frame* m_frame;			// Array of frames
		std::string m_label;	// Text label to identify sprite
		Sprite();				// Sprite always has frame count arg

	public:
		~Sprite();	// Destroy sprite, delete allocated frames
		Sprite(int max_frames);	// Create sprite with maximum frames

		// Getters and Setters
		void setWidth(int new_width);
		int getWidth() const;
		void setHeight(int new_height);
		int getHeight() const;
		void setColor(Color new_color);
		Color getColor() const;
		int getFrameCount() const;
		int addFrame(Frame new_frame);	// Add frame to sprite. Return -1 if full, else 0
		Frame getFrame(int frame_number) const;	// Return empty frame if out of range [0, m_frame_count - 1]
		void setLabel(std::string new_label);
		std::string getLabel() const;
		void setSlowdown(int new_sprite_slowdown);	// Value in multiples of GameManager frame time
		int getSlowdown() const;

		// Draw frame at position (x, y) with color.
		// Return 0 if ok, else -1
		// Top-left coordinate is (0, 0)
		int draw(int frame_number, Vector position) const;
	};
}