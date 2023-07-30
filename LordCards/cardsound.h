#ifndef CARDSOUND_H
#define CARDSOUND_H
#include<QSound>
#include<QSoundEffect>
#include<card.h>
#include<rulers.h>

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
    static void palySound(int type);
    static void playBGM();
    static void playCardSound(QList<Card*> cards);
};
#endif // CARDSOUND_H
