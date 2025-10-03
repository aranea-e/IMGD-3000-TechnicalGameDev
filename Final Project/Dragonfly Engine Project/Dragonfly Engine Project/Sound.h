#pragma once

#include <string>
#include <SFML/Audio.hpp>

namespace df {
	class Sound {	
	private:
		sf::Sound* m_p_sound;			// SFML Sound
		sf::SoundBuffer m_sound_buffer;	// SFML Sound Buffer
		std::string m_label;			// Text label

	public:
		Sound();
		~Sound();

		int loadSound(std::string filename);			// Load sound buffer from file. Return 0 if ok, else -1
		sf::Sound getSound() const;	
		void setLabel(std::string new_label);
		std::string getLabel() const;

		void play(bool loop = false);	// Play sound. If loop is true, repeat when done.
		void stop();
		void pause();	
	};
}