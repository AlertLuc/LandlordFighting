#include "cardround.h"
#include"maindialog.h"
#include"cardsound.h"
#include"QCoreApplication"
Cardround::Cardround(MainDialog *p,QObject *parent)
    : QObject(parent),m_maindialog(p)
{

}

void Cardround::initRound()
{
    biggestPlayer = CARDLIST_LORD;
    currentPlayer = CARDLIST_LORD;
    lastPlayerCards.clear();
}

void Cardround::delaySecond(int msec)
{
    do{_sleep(10);
    QCoreApplication::processEvents(QEventLoop::AllEvents,10);
        msec -= 20;}while(msec >= 0);
}

void Cardround::startRound(int player)
{
    currentPlayer = player;
    // 清除所有玩家外面手牌
    m_maindialog->slot_delectPlayerOutCard(player);
    // 上一个玩家牌组

    lastPlayerCards.clear();

    // 当前玩家赋值


    if(currentPlayer == CARDLIST_MIDPLAYER)
    {
        m_maindialog->slot_showPlayCards(true);
    }
    else
    {
        slot_computerRound(player);
    }
}

void Cardround::turnPlayer(int player)
{
    currentPlayer = player;
    if(biggestPlayer == player)
    {
        startRound(player);
        return;
    }

    m_maindialog->slot_delectPlayerOutCard(player);

    if(currentPlayer == CARDLIST_MIDPLAYER)
    {
        m_maindialog->slot_showPlayCards(true);
    }
    else
    {
        delaySecond(2000);
        slot_computerRound(player);
    }
}

void Cardround::slot_midPlayerPlayCards()
{

    QList<Card*> lst = m_maindialog->m_cardList[CARDLIST_MIDPLAYER].SelectCardList();
    if(lst.size() == 0)return;
    if(Rulers::canPlayCards(lst, lastPlayerCards)){
        // 获得选中添加玩家外面手牌
        // 删除选中
        CardSound::playCardSound(lst);
        m_maindialog->m_cardList[CARDLIST_MIDPLAYER_OUTCARD].addCard(lst);
        // 玩家手牌外面显示
        m_maindialog->m_cardList[CARDLIST_MIDPLAYER].DeleteCardList();

        biggestPlayer = CARDLIST_MIDPLAYER;
        lastPlayerCards = lst;

        m_maindialog->slot_showPlayCards(false);
        turnPlayer(CARDLIST_MIDPLAYER+1);
    }
}

void Cardround::slot_midPlayerPass()
{

}

void Cardround::slot_computerRound(int player)
{
    // 电脑出牌
    slot_computerPlayCards(player);
    // 切换下一个玩家
    turnPlayer((player+1)%3);
}

void Cardround::slot_computerPlayCards(int player)
{
    QList<Card*> cards;

    if(cards.size() == 0)
    {
        CardSound::palySound(SOUND_PASS);
    }else
    {
        delaySecond(2000);
        biggestPlayer = player;
    }
}
