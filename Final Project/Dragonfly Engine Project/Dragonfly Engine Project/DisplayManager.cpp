#include "DisplayManager.h"
#include "LogManager.h"

df::DisplayManager::DisplayManager() {
	setType("DisplayManager");
	startUp();
}

df::DisplayManager& df::DisplayManager::getInstance()
{
	static DisplayManager dm;	// Static variable persists after running
	return dm;
}

int df::DisplayManager::startUp() {

	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;


	if (m_p_window != NULL) {
		return 0;
	}
	m_p_window = 
		new sf::RenderWindow(
					sf::VideoMode({ (unsigned int)m_window_horizontal_pixels, (unsigned int)m_window_vertical_pixels }), 
					WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);


	if (!m_p_window) {
		LM.writeLog("!!Window not allocated!!");
		return -1;
	}

	m_p_window->setMouseCursorVisible(false);
	m_p_window->setVerticalSyncEnabled(true);

	if (m_font.openFromFile("df-font.ttf") == false) {
		LM.writeLog("!!Font not loaded!!");
		return -1;
	}

	Manager::startUp();

	return 0;
}

void df::DisplayManager::shutDown() {
	m_p_window->close();
}

int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const
{
	if (m_p_window == NULL)
	{
		return -1;
	}

	Vector pixel_pos = spacesToPixels(world_pos);
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition({ pixel_pos.getX() - charWidth() / 10,
						   pixel_pos.getY() + charHeight() / 5 });
	m_p_window->draw(rectangle);

	static sf::Text text(m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);

	if (charWidth() < charHeight()) { text.setCharacterSize((unsigned int)(charWidth() * 1.5)); }
	else { text.setCharacterSize((unsigned int)(charHeight() * 1.5)); }

	switch (color) {
	case BLACK:
		text.setFillColor(sf::Color::Black);
		break;
	case RED:
		text.setFillColor(sf::Color::Red);
		break;
	case GREEN:
		text.setFillColor(sf::Color::Green);
		break;
	case YELLOW:
		text.setFillColor(sf::Color::Yellow);
			break;
	case BLUE:
		text.setFillColor(sf::Color::Blue);
		break;
	case MAGENTA:
		text.setFillColor(sf::Color::Magenta);
		break;
	case CYAN:
		text.setFillColor(sf::Color::Cyan);
		break;
	case WHITE:
		text.setFillColor(sf::Color::White);
		break;
	case UNDEFINED_COLOR:
	default:
			return -1;
	}

	text.setPosition({ pixel_pos.getX(), pixel_pos.getY() });

	m_p_window->draw(text);

	return 0;
}

int df::DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const
{
	Vector starting_pos = pos;
	switch (just) {
	case CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size() / 2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
	default:
		break;
	}

	for (int i = 0; i < str.size(); i++)
	{
		Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}
	return 0;
}

int df::DisplayManager::getHorizontal() const
{
	return m_window_horizontal_chars;
}

int df::DisplayManager::getVertical() const
{
	return m_window_vertical_chars;
}

int df::DisplayManager::getHorizontalPixels() const
{
	return m_window_horizontal_pixels;
}

int df::DisplayManager::getVerticalPixels() const
{
	return m_window_vertical_pixels;
}

int df::DisplayManager::swapBuffers()
{
	if (m_p_window == NULL) {
		return -1;
	}

	m_p_window->display();
	m_p_window->clear();
	return 0;
}

sf::RenderWindow* df::DisplayManager::getWindow() const
{
	return m_p_window;
}

float df::charHeight(void)
{
	return (float)DM.getVerticalPixels() / DM.getVertical();
}

float df::charWidth(void)
{
	return (float)DM.getHorizontalPixels() / DM.getHorizontal();
}

df::Vector df::spacesToPixels(Vector spaces)
{
	return Vector(spaces.getX() * charWidth(), spaces.getY() * charHeight());
}

df::Vector df::pixelsToSpaces(Vector pixels)
{
	return Vector(pixels.getX() / charWidth(), pixels.getY() / charHeight());
}
