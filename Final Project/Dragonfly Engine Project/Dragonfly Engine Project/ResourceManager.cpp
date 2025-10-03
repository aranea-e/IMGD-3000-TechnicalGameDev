#include <iostream>
#include <fstream>

#include "ResourceManager.h"
#include "LogManager.h"

using std::cout;
using std::endl;

df::ResourceManager::ResourceManager() {
	setType("ResourceManager");
	startUp();
}

df::ResourceManager& df::ResourceManager::getInstance()
{
	static ResourceManager rm;	// Static variable persists after running
	return rm;
}

int df::ResourceManager::startUp() {
	m_sprite_count = 0;
	return Manager::startUp();
}

void df::ResourceManager::shutDown() {
	Manager::shutDown();
}

int df::ResourceManager::loadSprite(std::string filename, std::string label)
{
	if (m_sprite_count == MAX_SPRITES) {
		LM.writeLog("!!Sprite load error: Sprite Limit Reached!!");
		return -1;
	}

	std::string line;
	std::ifstream file(filename);

	if (!file.is_open()) {
		LM.writeLog("!!Sprite load error: File not found!!\nSource: \"%s\"\n", filename.c_str());
		file.close();
		return -1;
	}

	std::getline(file, line);
	int frames;
	try
	{
		frames = stoi(line);
	}
	catch (const std::exception&)
	{
		LM.writeLog("!!Sprite load error: Frames not found!!\nSource: \"%s\"\n", filename.c_str());
		file.close();
		return -1;
	}
	
	std::getline(file, line);
	int width;
	try
	{
		width = stoi(line);
	}
	catch (const std::exception&)
	{
		LM.writeLog("!!Sprite load error: Width not found!!\nSource: \"%s\"\n", filename.c_str());
		file.close();
		return -1;
	}
	
	std::getline(file, line);
	int height;
	try
	{
		height = stoi(line);
	}
	catch (const std::exception&)
	{
		LM.writeLog("!!Sprite load error: Height not found!!\nSource: \"%s\"\n", filename.c_str());
		file.close();
		return -1;
	}

	std::getline(file, line);
	int slowdown;
	try
	{
		slowdown = stoi(line);
	}
	catch (const std::exception&)
	{
		LM.writeLog("!!Sprite load error: Slowdown not found!!\nSource: \"%s\"\n", filename.c_str());
		file.close();
		return -1;
	}

	std::getline(file, line);
	Color color;
	if (line == "black") {
		color = BLACK;
	}
	else if (line == "red") {
		color = RED;
	}
	else if (line == "green") {
		color = GREEN;
	}
	else if (line == "yellow") {
		color = YELLOW;
	}
	else if (line == "blue") {
		color = BLUE;
	}
	else if (line == "magenta") {
		color = MAGENTA;
	}
	else if (line == "cyan") {
		color = CYAN;
	}
	else if (line == "white") {
		color = WHITE;
	}
	else {
		LM.writeLog("!!Sprite load error: Color not found!!\nSource: \"%s\"\n", filename.c_str());
		file.close();
		return -1;
	}

	Sprite* p_sprite = new Sprite(frames);
	p_sprite->setHeight(height);
	p_sprite->setWidth(width);
	p_sprite->setSlowdown(slowdown);
	p_sprite->setColor(color);

	for (int f = 0; f < frames; f++)
	{
		std::string framestr;
		for (int h = 0; h < height; h++)
		{
			std::getline(file, line);
			if (line.length() != width)
			{
				LM.writeLog("!!Sprite load error: Incorrect Width!!\nSource: \"%s\"\nLine: %d\nContents: %s\nExpected v Actual: %d %d\n", 
					filename.c_str(), h + 6, line.c_str(), width, line.length());
				file.close();
				delete p_sprite;
				return -1;
			}
			framestr.append(line);
		}
		Frame frame = Frame(width, height, framestr);
		p_sprite->addFrame(frame);
	}

	file.close();

	p_sprite->setLabel(label);
	m_p_sprite[m_sprite_count] = p_sprite;
	m_sprite_count++;

	return 0;
}

int df::ResourceManager::unloadSprite(std::string label)
{
	for (int i = 0; i < m_sprite_count; i++)
	{
		if (label == m_p_sprite[i]->getLabel()) {
			delete m_p_sprite[i];
			for (int j = i; j < m_sprite_count - 1; j++)
			{
				m_p_sprite[j] = m_p_sprite[j + 1];
			}
			m_sprite_count--;
			return 0;
		}
	}
	return -1;
}

df::Sprite* df::ResourceManager::getSprite(std::string label) const
{
	for (int i = 0; i < m_sprite_count; i++)
	{
		if (label == m_p_sprite[i]->getLabel()) {
			return m_p_sprite[i];
		}
	}
	return NULL;
}

int df::ResourceManager::loadSound(std::string filename, std::string label)
{
	if (m_sound_count == MAX_SOUNDS) {
		LM.writeLog("!!Sound load error: Sound Limit Reached!!\n");
		return -1;
	}

	if (m_sound[m_sound_count].loadSound(filename) == -1) {
		LM.writeLog("!!Sound load error: Sound not found!!\n");
		return -1;
	}
	m_sound[m_sound_count].setLabel(label);
	m_sound_count++;
	return 0;
}

int df::ResourceManager::unloadSound(std::string label)
{
	for (int i = 0; i < m_sound_count; i++)
	{
		if (label == m_sound[i].getLabel()) {
			for (int j = 0; j < m_sound_count - 1; j++)
			{
				m_sound[j] = m_sound[j + 1];
			}
			m_sound_count--;
			return 0;
		}
	}
	return -1;
}

df::Sound* df::ResourceManager::getSound(std::string label)
{
	for (int i = 0; i < m_sound_count; i++)
	{
		if (label == m_sound[i].getLabel())
		{
			return &m_sound[i];
		}
	}
	return NULL;
}

int df::ResourceManager::loadMusic(std::string filename, std::string label)
{
	if (m_music_count == MAX_MUSICS) {
		LM.writeLog("!!Music load error: Music Limit Reached!!\n");
		return -1;
	}

	if (m_music[m_music_count].loadMusic(filename) == -1) {
		LM.writeLog("!!Music load error: Music not found!!\n");
		return -1;
	}
	m_music[m_music_count].setLabel(label);
	m_music_count++;
	return 0;
}

int df::ResourceManager::unloadMusic(std::string label)
{
	for (int i = 0; i < m_music_count; i++)
	{
		if (label == m_sound[i].getLabel()) {
			m_sound[i].setLabel("");
			return 0;
		}
	}
	return -1;
}

df::Music* df::ResourceManager::getMusic(std::string label)
{
	if (label == "")
	{
		return NULL;
	}
	for (int i = 0; i < m_music_count; i++)
	{
		if (label == m_music[i].getLabel())
		{
			return &m_music[i];
		}
	}
	return NULL;
}
