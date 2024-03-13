#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL_mixer.h"
#include <string>
#include <map>
#include <iostream>

class SoundManager {
public:
    static SoundManager* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundManager();
    }

    bool loadSoundEffect(const std::string& id, const std::string& filename);
    bool loadMusic(const std::string& id, const std::string& filename);
    void playSoundEffect(const std::string& id, int loops = 0);
    void playMusic(const std::string& id, int loops = -1);
    void setSoundEffectVolume(const std::string& id, int volume);
    void setMusicVolume(const std::string& id, int volume);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void clean();

private:
    SoundManager() {}
    static SoundManager* s_Instance;
    std::map<std::string, Mix_Chunk*> m_SoundEffects;
    std::map<std::string, Mix_Music*> m_MusicTracks;
};

#endif
