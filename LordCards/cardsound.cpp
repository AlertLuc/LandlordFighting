#include "cardsound.h"
#include "QString"
#include <QTimer>
CardSound::CardSound()
{

}

void CardSound::palySound(int type)
{
    QString str;
    switch (type) {
    case SOUND_WIN:
        str = "win";
        break;
    case SOUND_NOCALL:
        str = "bujiao";
        break;
    case SOUND_ROBLORD:
        str = "qiangdizhu";
        break;
    case SOUND_PASS:
        str = "passMusic";
        break;

    case SOUND_LOSE:
        str = "loseMusic";
        break;

    case SOUND_JIAODIZHU:
        str = "jiaodizhu";
        break;

    case SOUND_XIPAI:
        str = "xipai";
        break;
    }
    str = QString(":/sound/%1.wav").arg(str);
    QSound::play(str);
}

void CardSound::playBGM()
{
    static QSoundEffect sound;
    sound.setSource(QUrl::fromLocalFile(":/sound/bkMusic.wac"));
    sound.setLoopCount(QSoundEffect::Infinite);
    sound.setVolume(0.1);
    sound.play();
}

void CardSound::playCardSound(QList<Card *> cards)
{

    QString str;
    int cardtype = Rulers::getCardtype(cards);
    if(cardtype == TRIPLE)
    {
        QString path = QString(":/sound/sange.wav");
        QSound::play(path);

        str = QString::number(cards.front()->m_point +3);
        str = QString(":/sound/%1.wav").arg(str);
        QTimer::singleShot(333,[str](){QSound::play(str);});
        return;
    }
    switch (cardtype) {
    case SINGLE:
        str = QString::number(cards.front()->m_point +3);
        break;
    case PAIR:
        str = "dui";
        str += QString::number(cards.front()->m_point +3);
        break;
    case TRIPLE_WITH_ONE:
        str = "sandaiyi";
        break;
    case TRIPLE_WITH_TWO:
        str = "sandaiyidui";
        break;
    case STRAIGHT:
        str = "shunzi";
        break;
    case STRAIGHT_PAIR:
        str = "";
        break;
    case PLANE:
        str = "";
        break;
    case PLANE_WITH_WING:
        str = "feijidaichibang";
        break;
    case FOUR_WITH_TWO:
        str = "sidaier";
        break;
    case FOUR_WITH_TWO_PAIR:
        str = "sidailiangdui";
        break;
    case BOMB:
        str = "zhadan";
        break;
    case KINGBOMB:
        str = "wangzha";
        break;
    }
    str = QString(":/sound/%1.wav").arg(str);
    QSound::play(str);
}
