#include "AudioManager.h"

AudioManager::AudioManager() {
	m_allowMusic = true;
	m_allowSound = true;

	m_scrollBuffer.loadFromFile("assets/Scroll.ogg");
	m_scrollSound.setBuffer(m_scrollBuffer);
	m_scrollSound.setVolume(50.0f);

	m_selectBuffer.loadFromFile("assets/Select.ogg");
	m_selectSound.setBuffer(m_selectBuffer);
	m_selectSound.setVolume(50.0f);

	m_returnBuffer.loadFromFile("assets/Return.ogg");
	m_returnSound.setBuffer(m_returnBuffer);
	m_returnSound.setVolume(50.0f);

	m_jumpBuffer.loadFromFile("assets/Jump.ogg");
	m_jumpSound.setBuffer(m_jumpBuffer);
	m_jumpSound.setVolume(50.0f);

	m_punchBuffer.loadFromFile("assets/Punch.ogg");
	m_punchSound.setBuffer(m_punchBuffer);
	m_punchSound.setVolume(50.0f);

	m_menu.openFromFile("assets/Menu.ogg");
	m_menu.setVolume(50.0f);
	m_menu.setLoop(true);

	m_level.openFromFile("assets/Level.ogg");
	m_level.setVolume(50.0f);
	m_level.setLoop(true);

	playMusic(CurrentMusic::MENU);
}

void AudioManager::playSound(SoundType theSound) {
	// checks if sound is toggled on
	if (m_allowSound == true) {
		// checks which sound is to be played
		if (theSound == SELECT) {
			m_selectSound.play();
		}
		if (theSound == SCROLL) {
			m_scrollSound.play();
		}
		if (theSound == RETURN) {
			m_returnSound.play();
		}
		if (theSound == JUMP) {
			m_jumpSound.play();
		}
		if (theSound == PUNCH) {
			m_punchSound.play();
		}
	}
}

void AudioManager::toggleSound() {
	// if sound is on, turn off
	if (m_allowSound == true) {
		m_allowSound = false;
	}
	// if sound is off, turn on
	else {
		m_allowSound = true;
	}
}

bool AudioManager::getSoundToggle() {
	return m_allowSound;
}

void AudioManager::changeSoundVolume(float value) {
	if (value < 0) {
		if (m_selectSound.getVolume() > 5.0f) {
			m_selectSound.setVolume(m_selectSound.getVolume() + value);
		}

		if (m_scrollSound.getVolume() > 5.0f) {
			m_scrollSound.setVolume(m_scrollSound.getVolume() + value);
		}
		if (m_returnSound.getVolume() > 5.0f) {
			m_returnSound.setVolume(m_returnSound.getVolume() + value);
		}
		if (m_jumpSound.getVolume() > 5.0f) {
			m_jumpSound.setVolume(m_jumpSound.getVolume() + value);
		}

		if (m_punchSound.getVolume() > 5.0f) {
			m_punchSound.setVolume(m_punchSound.getVolume() + value);
		}
	}

	if (value > 0) {
		if (m_selectSound.getVolume() <= 95.0f) {
			m_selectSound.setVolume(m_selectSound.getVolume() + value);
		}

		if (m_scrollSound.getVolume() <= 95.0f) {
			m_scrollSound.setVolume(m_scrollSound.getVolume() + value);
		}
		if (m_returnSound.getVolume() <= 95.0f) {
			m_returnSound.setVolume(m_returnSound.getVolume() + value);
		}
		if (m_jumpSound.getVolume() <= 95.0f) {
			m_jumpSound.setVolume(m_jumpSound.getVolume() + value);
		}
		if (m_punchSound.getVolume() <= 95.0f) {
			m_punchSound.setVolume(m_punchSound.getVolume() + value);
		}
	}
}

string AudioManager::showSoundVolume() {
	return "Sound Volume: " + to_string((int)m_jumpSound.getVolume());
}

void AudioManager::playMusic(CurrentMusic music) {
	m_currentMusic = music;

	// checks if music is toggled on
	if (m_allowMusic == true) {
		// checks which menu music is to be played
		if (m_currentMusic == MENU) {
			// checks if any other music is being played
			if (m_level.getStatus() == sf::Music::Playing) {
				m_level.stop();
			}
			m_menu.play();
		}

		// level music is to be played
		else {
			// checks if any other music is being played
			if (m_menu.getStatus() == sf::Music::Playing) {
				m_menu.stop();
			}
			m_level.play();
		}
	}
}

void AudioManager::toggleMusic() {
	// if music is on, turn off
	if (m_allowMusic == true) {
		m_allowMusic = false;
		// checks which menu music is to be played
		if (m_currentMusic == MENU) {
			m_menu.stop();
		}

		// level music is to be played
		else {
			m_level.stop();
		}
	}
	// if music is off, turn on
	else {
		m_allowMusic = true;

		// checks which menu music is to be played
		if (m_currentMusic == MENU) {
			m_menu.play();
		}

		// level music is to be played
		else {
			m_level.play();
		}
	}
}

bool AudioManager::getMusicToggle() {
	return m_allowMusic;
}

void AudioManager::changeMusicVolume(float value) {
	if (value < 0) {
		if (m_menu.getVolume() > 5.0f) {
			m_menu.setVolume(m_menu.getVolume() + value);
		}
		if (m_level.getVolume() > 5.0f) {
			m_level.setVolume(m_level.getVolume() + value);
		}
	}

	if (value > 0) {
		if (m_menu.getVolume() <= 95.0f) {
			m_menu.setVolume(m_menu.getVolume() + value);
		}
		if (m_level.getVolume() <= 95.0f) {
			m_level.setVolume(m_level.getVolume() + value);
		}
	}
}

string AudioManager::showMusicVolume() {
	return "Music Volume: " + to_string((int)m_menu.getVolume());
}
