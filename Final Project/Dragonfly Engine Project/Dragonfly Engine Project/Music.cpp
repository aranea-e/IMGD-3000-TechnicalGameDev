#include "Music.h"
#include "LogManager.h"

df::Music::Music()
{
	m_music = sf::Music();
	m_label = "";
}

int df::Music::loadMusic(std::string filename)
{
	if (!m_music.openFromFile(filename)) {
		LM.writeLog("!!Music not loaded!!\nTarget: \"%s\"\n", filename.c_str());
		return -1;
	}
	return 0;
}

sf::Music* df::Music::getMusic()
{
	return &m_music;
}

void df::Music::setLabel(std::string new_label) {
	m_label = new_label;
}

std::string df::Music::getLabel()
{
	return m_label;
}

void df::Music::play(bool loop) {
	m_music.play();
	m_music.setLooping(loop);
}

void df::Music::stop() {
	m_music.stop();
}

void df::Music::pause() {
	m_music.pause();
}