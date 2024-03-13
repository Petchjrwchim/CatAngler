#include "SoundManager.h"

SoundManager* SoundManager::s_Instance = nullptr;

bool SoundManager::loadSoundEffect(const std::string& id, const std::string& filename) {
    Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());
    if (!chunk) {
        std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
        return false;
    }
    m_SoundEffects[id] = chunk;
    return true;
}

bool SoundManager::loadMusic(const std::string& id, const std::string& filename) {
    Mix_Music* music = Mix_LoadMUS(filename.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    m_MusicTracks[id] = music;
    return true;
}

void SoundManager::playSoundEffect(const std::string& id, int loops) {
    Mix_PlayChannel(-1, m_SoundEffects[id], loops);
}

void SoundManager::playMusic(const std::string& id, int loops) {
    Mix_PlayMusic(m_MusicTracks[id], loops);
}

void SoundManager::stopMusic() {
    Mix_HaltMusic();
}

void SoundManager::pauseMusic() {
    Mix_PauseMusic();
}

void SoundManager::resumeMusic() {
    Mix_ResumeMusic();
}

void SoundManager::clean() {
    for (auto& sound : m_SoundEffects) {
        Mix_FreeChunk(sound.second);
    }
    for (auto& music : m_MusicTracks) {
        Mix_FreeMusic(music.second);
    }
    m_SoundEffects.clear();
    m_MusicTracks.clear();
    Mix_Quit();
}

void SoundManager::setSoundEffectVolume(const std::string& id, int volume) {

    volume = std::max(0, std::min(volume, MIX_MAX_VOLUME));


    if (m_SoundEffects.find(id) != m_SoundEffects.end()) {
        Mix_VolumeChunk(m_SoundEffects[id], volume);
    }
    else {
        std::cerr << "Sound effect with ID '" << id << "' not found." << std::endl;
    }
}

void SoundManager::setMusicVolume(const std::string& id, int volume) {

    volume = std::max(0, std::min(volume, MIX_MAX_VOLUME));

    if (m_MusicTracks.find(id) != m_MusicTracks.end()) {
        Mix_VolumeMusic(volume);
    }
    else {
        std::cerr << "Music track with ID '" << id << "' not found." << std::endl;
    }
}
