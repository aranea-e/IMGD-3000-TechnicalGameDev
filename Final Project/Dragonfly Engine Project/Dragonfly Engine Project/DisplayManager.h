#pragma once

// System includes
#include <SFML/Graphics.hpp>

// Engine includes
#include "Manager.h"
#include "Color.h"
#include "Vector.h"

#define DM df::DisplayManager::getInstance()

namespace df {

	// String justifications.
	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	// Defaults for SFML window.
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	// Compute character height, based on window size and font.
	float charHeight(void);

	// Compute character width, based on window size and font.
	float charWidth(void);

	// Convert ASCII spaces (x,y) to window pixels (x,y).
	Vector spacesToPixels(Vector spaces);

	// Convert window pixels (x,y) to ASCII spaces (x,y).
	Vector pixelsToSpaces(Vector pixels);

	class DisplayManager : public Manager {
	private:
		DisplayManager();						// Private (singleton)
		DisplayManager(DisplayManager const&);		// Don't allow copy
		void operator=(DisplayManager const&);	// Don't allow assignment

		sf::Font m_font;		  // Font used for ASCII graphics.
		sf::RenderWindow* m_p_window;	  // Pointer to SFML window.
		int m_window_horizontal_pixels; // Horizontal pixels in window.
		int m_window_vertical_pixels;   // Vertical pixels in window.
		int m_window_horizontal_chars;  // Horizontal ASCII spaces in window.
		int m_window_vertical_chars;    // Vertical ASCII spaces in window.

	public:
		static DisplayManager& getInstance(); // Get only instance 

		int startUp();		// Start up the DisplayManager, open window. Return 0 if ok, else -1
		void shutDown();	// Shut down the DisplayManager, close window

		// Draw at location (x,y) with color. Return 0 if ok, else -1
		int drawCh(Vector world_pos, char ch, Color color) const;	// Draw char
		int drawString(Vector pos, std::string str, Justification just, Color color) const;	// Draw string

		int getHorizontal() const;			// Return window's horizontal maximum (characters)
		int getVertical() const;			// Return window's vertical maximum (characters)
		int getHorizontalPixels() const;	// Return window's horizontal maximum (pixels)
		int getVerticalPixels() const;		// Return window's vertical maximum (pixels)

		int swapBuffers();	// Render current window buffer. Return 0 if okay, else -1.

		sf::RenderWindow* getWindow() const;	// Return pointer to SFML graphics window
	};
}
