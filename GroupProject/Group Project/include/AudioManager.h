#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "stdafx.h"

class AudioManager {
public:
	AudioManager();

	enum SoundType { SELECT, RETURN, SCROLL, JUMP, PUNCH };
	enum CurrentMusic { MENU, LEVEL };

	void playSound(SoundType sound);

	void toggleSound();

	bool getSoundToggle();

	void changeSoundVolume(float value);

	string showSoundVolume();

	void playMusic(CurrentMusic music);

	void toggleMusic();

	bool getMusicToggle();

	//void changeMusic();

	void changeMusicVolume(float value);

	string showMusicVolume();

private:
	// booleans for toggling sound and music
	bool m_allowMusic;
	bool m_allowSound;

	// sound buffers
	sf::SoundBuffer m_scrollBuffer;
	sf::SoundBuffer m_returnBuffer;
	sf::SoundBuffer m_selectBuffer;
	sf::SoundBuffer m_jumpBuffer;
	sf::SoundBuffer m_punchBuffer;

	// sounds to be player
	sf::Sound m_scrollSound;
	sf::Sound m_returnSound;
	sf::Sound m_selectSound;
	sf::Sound m_jumpSound;
	sf::Sound m_punchSound;

	// music
	sf::Music m_menu;
	sf::Music m_level;

	CurrentMusic m_currentMusic;
};

#endif
