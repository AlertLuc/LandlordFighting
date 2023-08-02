#include "cardround.h"
#include"maindialog.h"
#include"cardsound.h"
#include"QCoreApplication"
Cardround::Cardround(MainDialog *p,QObject *parent)
    : QObject(parent),m_maindialog(p){}

void Cardround::initRound()
{

    // 叫地主
    beginCallLord = CARDLIST_LORD;
    isEndCall = false;
    lordPlayer = CARDLIST_LORD;

    //出牌
    biggestPlayer = CARDLIST_LORD;
    currentPlayer = CARDLIST_LORD;
    lastPlayerCards.clear();

}

void Cardround::delaySecond(int msec)
{
    do{
        _sleep(10);
        QCoreApplication::processEvents(QEventLoop::AllEvents,10);
        msec -= 20;
    }while(msec >= 0);
}

void Cardround::decideBeginLord()
{
    // 随机
    beginCallLord = qrand()%3;

    callLordGiveUp(beginCallLord);

}

void Cardround::turnCallLord(int player)
{
    // 当前玩家
    currentPlayer = player;

    if(player == (beginCallLord +1)%3)
    {
        if(isEndCall)
        {
            //都不叫

            if(biggestPlayer == CARDLIST_LORD)
            {
                delaySecond(1000);
                m_maindialog->on_pb_start_clicked();
                return;
            }
            lordPlayer = biggestPlayer;
            // 加三张牌
            m_maindialog->slot_lordAddLordCards(lordPlayer);
            startRound(biggestPlayer);
            return;
        }

    }

    // 判断是否结束
    if(biggestPlayer == player)
    {
        turnCallLord((player+1) % 3);
        return;
    }

    callLordGiveUp(player);
}

void Cardround::callLordGiveUp(int player)
{
    currentPlayer = player;

    if(player == CARDLIST_MIDPLAYER)
    {
        m_maindialog->slot_showCallLord(true);

    }
    else{
        delaySecond(2000);
        slot_computerCallLord(player);
    }
}

void Cardround::slot_midPlayerCallLord()
{
    // 叫地主
    if(biggestPlayer)
    {
        CardSound::palySound(SOUND_JIAODIZHU);
    }
    else{
        CardSound::palySound(SOUND_ROBLORD);
    }

    biggestPlayer = CARDLIST_MIDPLAYER;

    m_maindialog->slot_showCallLord(false);

    // 叫地主显示


    // 切换到其他玩家
    turnCallLord(CARDLIST_MIDPLAYER + 1);
}

void Cardround::slot_midPlayerNoCall()
{
    // 播放声音
    CardSound::palySound(SOUND_NOCALL);

    m_maindialog->slot_showCallLord(false);

    turnCallLord(CARDLIST_MIDPLAYER + 1);
}

void Cardround::slot_computerCallLord(int player)
{
    // 电脑叫地主
    bool res = AIPlayCard::isCallLord(m_maindialog->m_cardList[player].m_cardlist);
    if(res){
        if(biggestPlayer == CARDLIST_LORD)
        {
            CardSound::palySound(SOUND_JIAODIZHU);
        }
        else
        {
             CardSound::palySound(SOUND_ROBLORD);
        }
        biggestPlayer = player;
    }
    else
    {
        CardSound::palySound(SOUND_NOCALL);
    }

    turnCallLord((player + 1)%3);
}

void Cardround::startRound(int player)
{
    m_maindialog->slot_hideAllPass();
//    currentPlayer = player;
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
    m_maindialog->m_lbPassArr[currentPlayer]->hide();
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
    if(biggestPlayer == CARDLIST_MIDPLAYER)
    {
        return;
    }
    m_maindialog->slot_showPlayCards(false);
    CardSound::palySound(SOUND_PASS);
    m_maindialog->m_lbPassArr[CARDLIST_MIDPLAYER]->show();
    turnPlayer(CARDLIST_MIDPLAYER+1);
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
//    if(AIPlayCard::findSmallestCards(m_maindialog->m_cardList[player].m_cardlist) != 0){
//        cards = m_maindialog->m_cardList[player].SelectCardList();
//    }
    cards = AIPlayCard::BeatCards(m_maindialog->m_cardList[player].m_cardlist,
                                  lastPlayerCards);
    if(cards.size() == 0)
    {
        CardSound::palySound(SOUND_PASS);
        m_maindialog->m_lbPassArr[player]->show();
    }else
    {
//        delaySecond(2000);
        CardSound::playCardSound(cards);
        m_maindialog->m_cardList[player+CARDLIST_LEFTPLAYER_OUTCARD].addCard(cards);
        m_maindialog->m_cardList[player].DeleteCardList();
        biggestPlayer = player;
        lastPlayerCards = cards;
    }
}
