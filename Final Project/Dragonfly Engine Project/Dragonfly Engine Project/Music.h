#pragma once

#include <string>
#include <SFML/Audio.hpp>

namespace df {
	class Music {
	private:
		Music(Music const&);			// SFML doesn't allow music copy
		void operator=(Music const&);	// SMFL doesn't allow music assignment
		sf::Music m_music;
		std::string m_label;

	public:
		Music();

		int loadMusic(std::string filename);
		sf::Music* getMusic();
		void setLabel(std::string new_label);
		std::string getLabel();

		void play(bool loop = true);	// If loop is true, repeat play when done
		void stop();
		void pause();
	};
}