#include "Sound.h"
#include "LogManager.h"

df::Sound::Sound()
{
	m_p_sound = NULL;
	m_sound_buffer = sf::SoundBuffer();
	m_label = "";
}

df::Sound::~Sound()
{
	if (m_p_sound != NULL)
	{
		delete m_p_sound;
		m_p_sound = NULL;
	}
}

int df::Sound::loadSound(std::string filename)
{
	if (!m_sound_buffer.loadFromFile(filename))
	{
		LM.writeLog("!!Sound not loaded!!\nTarget: \"%s\"\n", filename.c_str());
		return -1;
	}
	m_p_sound = new sf::Sound(m_sound_buffer);
	return 0;
}

sf::Sound df::Sound::getSound() const
{
	return *m_p_sound;
}

void df::Sound::setLabel(std::string new_label)
{
	m_label = new_label;
}

std::string df::Sound::getLabel() const
{
	return m_label;
}

void df::Sound::play(bool loop)
{
	m_p_sound->play();
	m_p_sound->setLooping(loop);
}

void df::Sound::stop()
{
	m_p_sound->stop();
}

void df::Sound::pause()
{
	m_p_sound->pause();
}
