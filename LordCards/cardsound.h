#ifndef CARDSOUND_H
#define CARDSOUND_H

#include<QSound>
#include<QSoundEffect>

enum SOUNDE_TYPE{
    SOUND_NOCALL,
    SOUND_JIAODIZHU,
    SOUND_LOSE,
    SOUND_PASS,
    SOUND_ROBLORD,
    SOUND_WIN,
    SOUND_XIPAI,
};

class CardSound
{
public:
    CardSound();

    static void palySound(int type);

    static void playBGM();



};

#endif // CARDSOUND_H
