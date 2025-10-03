#pragma once

#include <string>

#include "Manager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

#define RM df::ResourceManager::getInstance()

namespace df {
	const int MAX_SPRITES = 500;
	const int MAX_SOUNDS = 50;
	const int MAX_MUSICS = 50;

	class ResourceManager : public Manager {
	private:
		ResourceManager();						// Private (singleton)
		ResourceManager(ResourceManager const&);// Don't allow copy
		void operator=(ResourceManager const&);	// Don't allow assignment

		int m_sprite_count;					// Count of number of loaded sprites
		Sprite* m_p_sprite[MAX_SPRITES];	// Array of sprites

		int m_sound_count;					// Count of number of loaded sounds
		Sound m_sound[MAX_SOUNDS];			// Array of sounds
		int m_music_count;					// Count of number of loaded musics
		Music m_music[MAX_MUSICS];			// Array of music

	public:
		static ResourceManager& getInstance(); // Get only instance 

		int startUp();		// Start up the ResourceManager
		void shutDown();	// Shut down the ResourceManager, free allocated sprites

		// Load sprite, assign label. Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);
		// Unload sprite with label. Return 0 if ok, else -1.
		int unloadSprite(std::string label);
		// Find sprite with label. Return pointer if found, else NULL.
		Sprite* getSprite(std::string label) const;
		// Load sound, assign label. Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);
		// Unload sound with label. Return 0 if ok, else -1.
		int unloadSound(std::string label);
		// Find sound with label. Return pointer if found, else NULL.
		Sound* getSound(std::string label);
		// Load music, assign label. Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);
		// Unload music with label. Return 0 if ok, else -1.
		int unloadMusic(std::string label);
		// Find music with label. Return pointer if found, else NULL.
		Music* getMusic(std::string label);
	};
}