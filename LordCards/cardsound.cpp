#include "cardsound.h"

CardSound::CardSound()
{

}

void CardSound::palySound(int type)
{
    QString str;
    switch (type) {
    case SOUND_WIN:

        break;
    case SOUND_NOCALL:

        break;
    case SOUND_ROBLORD:

        break;
    case SOUND_PASS:

        break;
    case SOUND_LOSE:

        break;
    case SOUND_JIAODIZHU:

        break;

    case SOUND_XIPAI:

        break;
    }
}

void CardSound::playBGM()
{
    static QSoundEffect sound;
    sound.setSource(QUrl::fromLocalFile(":/sound/bkMusic.wac"));
    sound.setLoopCount(QSoundEffect::Infinite);
    sound.setVolume(0.1);
    sound.play();
}
