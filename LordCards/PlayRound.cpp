#include "PlayRound.h"
#include"maindialog.h"
#include"cardsound.h"
#include"QCoreApplication"
#include "rulers.h"
#include "QLabel"
#include <QObject>
#include <QTimer>

PlayRound::PlayRound(main_dialog *p,QObject *parent) : QObject(parent),m_mainDialog(p)
{
	connect(&m_timerArray[CARDLIST_LEFTPLAYER], &QTimer::timeout, this, &PlayRound::slot_play_card_time_out);
    connect(&m_timerArray[CARDLIST_MIDPLAYER], &QTimer::timeout, this, &PlayRound::slot_play_card_time_out);
    connect(&m_timerArray[CARDLIST_RIGHTPLAYER], &QTimer::timeout, this, &PlayRound::slot_play_card_time_out);

}

void PlayRound::initRound()
{
    // 叫地主
    beginCallLord = CARDLIST_LORD;
    isEndCall = false;
    lordPlayer = CARDLIST_LORD;

    //出牌
    biggestPlayer = CARDLIST_LORD;
    currentPlayer = CARDLIST_LORD;
    lastPlayerCards.clear();


    m_isStop = false;
}

void PlayRound::delay_second(int msec)
{
    do{
        _sleep(10);
        QCoreApplication::processEvents(QEventLoop::AllEvents,10);
        msec -= 20;
    }while(msec >= 0);
}

void PlayRound::decideBeginLord()
{

    // 随机
    beginCallLord = qrand() % 3;
    callLordGiveUp(beginCallLord);
}

void PlayRound::turnCallLord(int player)
{
    if (m_isStop)return;
    // 当前玩家
    currentPlayer = player;

    if(player == (beginCallLord + 1) % 3)
    {
        if(isEndCall)
        {
            //都不叫
            if(biggestPlayer == CARDLIST_LORD)
            {
                delay_second(1000);
                if (m_isStop)return;
                m_mainDialog->on_pb_start_clicked();
                return;
            }

            m_mainDialog->slot_hide_all_call_lord();
            m_mainDialog->slot_hide_all_no_call();

            lordPlayer = biggestPlayer;

            m_mainDialog->m_lbIconArray[lordPlayer]->setPixmap(QPixmap(":/image/lord_head.png"));

            // 加三张牌
            m_mainDialog->slot_lordAddLordCards(lordPlayer);


            delay_second(1000);
            if (m_isStop)return;

			m_mainDialog->slot_show_all_cards_count();

            startRound(biggestPlayer);


            return;
        }

    }
    isEndCall = true;
    // 判断是否结束
    if(biggestPlayer == player)
    {
        turnCallLord((player+1) % 3);
        return;
    }

    callLordGiveUp(player);
}

void PlayRound::callLordGiveUp(int player)
{
    if (m_isStop)return;
    currentPlayer = player;

    slot_strat_timer(player);

    if(player == CARDLIST_MIDPLAYER)
    {
        m_mainDialog->slot_showCallLord(true);

    }
    else{
        delay_second(100);
        if (m_isStop)return;
        slot_computerCallLord(player);
    }
}

void PlayRound::slot_midPlayerCallLord()
{
    if (m_isStop)return;
    // 叫地主
    if(biggestPlayer == CARDLIST_LORD)
    {
        CardSound::play_sound(SOUND_JIAODIZHU);
    }
    else{
        CardSound::play_sound(SOUND_ROBLORD);
    }

    biggestPlayer = CARDLIST_MIDPLAYER;

    m_mainDialog->slot_showCallLord(false);

    // 叫地主显示
    m_mainDialog->m_lbNoCallArray[CARDLIST_MIDPLAYER]->hide();
    m_mainDialog->m_lbCallLordArray[CARDLIST_MIDPLAYER]->show();

    slot_end_timer(CARDLIST_MIDPLAYER);

    // 切换到其他玩家
    turnCallLord(CARDLIST_MIDPLAYER + 1);
}

void PlayRound::slot_midPlayerNoCall()
{
    if (m_isStop)return;
    // 播放声音
    CardSound::play_sound(SOUND_NOCALL);

    m_mainDialog->slot_showCallLord(false);

	m_mainDialog->m_lbCallLordArray[CARDLIST_MIDPLAYER]->hide();
    m_mainDialog->m_lbNoCallArray[CARDLIST_MIDPLAYER]->show();
    

    slot_end_timer(CARDLIST_MIDPLAYER);
    turnCallLord(CARDLIST_MIDPLAYER + 1);
}

void PlayRound::slot_computerCallLord(int player)
{
    if (m_isStop)return;
    // 电脑叫地主
    bool res = AIPlayCard::isCallLord(m_mainDialog->m_cardList[player].m_cardList);
    if(res){
        if(biggestPlayer == CARDLIST_LORD)
        {
            CardSound::play_sound(SOUND_JIAODIZHU);
        }
        else
        {
             CardSound::play_sound(SOUND_ROBLORD);
        }
        biggestPlayer = player;

		m_mainDialog->m_lbNoCallArray[player]->hide();
	    m_mainDialog->m_lbCallLordArray[player]->show();
    }
    else
    {
        CardSound::play_sound(SOUND_NOCALL);
        
        m_mainDialog->m_lbCallLordArray[player]->hide();
		m_mainDialog->m_lbNoCallArray[player]->show();
    }

    slot_end_timer(player);


    turnCallLord((player + 1)%3);
}

void PlayRound::startRound(int player)
{
    if (m_isStop) return;
    m_mainDialog->slot_hideAllPass();
    currentPlayer = player;

    slot_strat_timer(player);

    // 清除所有玩家外面手牌
    m_mainDialog->slot_delete_player_out_card(player);

    // 上一个玩家牌组
    lastPlayerCards.clear();

    // 当前玩家赋值
    if(currentPlayer == CARDLIST_MIDPLAYER)
    {
        m_mainDialog->slot_show_play_cards(true);
    }
    else
    {
        slot_computerRound(player);
    }
}

void PlayRound::turnPlayer(int player)
{
    if (m_isStop)return;
    currentPlayer = player;
    
    if(biggestPlayer == player)
    {
        delay_second(1000);
        if (m_isStop)return;
        startRound(player);

        return;
    }

    slot_strat_timer(player);

    m_mainDialog->m_lbPassArr[currentPlayer]->hide();

    m_mainDialog->slot_delete_player_out_card(player);

    if(player == CARDLIST_MIDPLAYER)
    {
        m_mainDialog->slot_show_play_cards(true);
    }
    else
    {
        delay_second(2000);
        if (m_isStop)return;
        slot_computerRound(player);
    }
}

void PlayRound::slot_midPlayerPlayCards()
{
    if (m_isStop) return;
    QList<Card*> lst = m_mainDialog->m_cardList[CARDLIST_MIDPLAYER].SelectCardList();
    if(lst.size() == 0)return;
    if(Rulers::can_play_cards(lst, lastPlayerCards)){
        // 获得选中添加玩家外面手牌
        // 删除选中
        CardSound::playCardSound(lst);
        m_mainDialog->m_cardList[CARDLIST_MIDPLAYER_OUTCARD].addCard(lst);
        // 玩家手牌外面显示
        m_mainDialog->m_cardList[CARDLIST_MIDPLAYER].DeleteCardList();

        biggestPlayer = CARDLIST_MIDPLAYER;
        lastPlayerCards = lst;

        m_mainDialog->slot_show_play_cards(false);

        slot_end_timer(CARDLIST_MIDPLAYER);

        if (slot_isEnd(CARDLIST_MIDPLAYER))
        {
            return;
        }

        turnPlayer(CARDLIST_MIDPLAYER+1);
    }
}
void PlayRound::slot_midPlayerPass()
{
    if (m_isStop) return;
    if(biggestPlayer == CARDLIST_MIDPLAYER)
    {
        return;
    }
    m_mainDialog->slot_show_play_cards(false);
    CardSound::play_sound(SOUND_PASS);
    m_mainDialog->m_lbPassArr[CARDLIST_MIDPLAYER]->show();

    slot_end_timer(CARDLIST_MIDPLAYER);
    turnPlayer(CARDLIST_MIDPLAYER+1);
}

void PlayRound::slot_computerRound(int player)
{
    // 电脑出牌
    slot_computerPlayCards(player);

    if(slot_isEnd(player))
    {
        return;
    }

    // 切换下一个玩家
    turnPlayer((player+1)%3);
}
void PlayRound::slot_computerPlayCards(int player)
{
    if (m_isStop) return;
    QList<Card*> cards;
    if(lordPlayer == player || biggestPlayer == lordPlayer || player == biggestPlayer)
    {
        cards = AIPlayCard::BeatCards(m_mainDialog->m_cardList[player].m_cardList, lastPlayerCards);
    }
    else
    {
	    if(biggestPlayer != lordPlayer)
	    {
            cards = AIPlayCard::BeatCards(m_mainDialog->m_cardList[player].m_cardList, lastPlayerCards);
            if(cards.size() != m_mainDialog->m_cardList[player].m_cardList.size())
            {
	            for(Card* card:cards)
	            {
                    card->setUnSelected();
	            }
                cards.clear();

                int type = Rulers::get_card_type(lastPlayerCards);
                if(type == SINGLE || type == PAIR)
                {
                    cards = AIPlayCard::BeatCards(m_mainDialog->m_cardList[player].m_cardList, lastPlayerCards);
                }
            }
	    }
    }

    cards = AIPlayCard::BeatCards(m_mainDialog->m_cardList[player].m_cardList,lastPlayerCards);
    if(cards.empty())
    {
        CardSound::play_sound(SOUND_PASS);
        m_mainDialog->m_lbPassArr[player]->show();
    }
	else
    {
//        delaySecond(2000);
        CardSound::playCardSound(cards);
        m_mainDialog->m_cardList[player+CARDLIST_LEFTPLAYER_OUTCARD].addCard(cards);
        m_mainDialog->m_cardList[player].DeleteCardList();
        biggestPlayer = player;
        lastPlayerCards = cards;
    }

    slot_end_timer(player);
}

void PlayRound::slot_computer_help()
{
    AIPlayCard::BeatCards(m_mainDialog->m_cardList[CARDLIST_MIDPLAYER].m_cardList, lastPlayerCards);
}

bool PlayRound::slot_isEnd(int player)
{
    bool isWin = false;
    bool isEnd = false;

    if(player != CARDLIST_MIDPLAYER)
    {
	    if(m_mainDialog->m_cardList[player].m_cardList.count()==0)
	    {
            if (lordPlayer == CARDLIST_MIDPLAYER)
            {
                isWin = false;
                    
            }
            else if(player == CARDLIST_MIDPLAYER)
            {
                isWin = false;
            }
            else
            {
                isWin = true;
            }
            isEnd = true;
	    }
    }
    else
    {
        if (m_mainDialog->m_cardList[player].m_cardList.count() == 0)
        {
            isWin = true;
            isEnd = true;
        }
    }
    if(isEnd)
    {
	    if(isWin)
	    {
            CardSound::play_sound(SOUND_WIN);
	    }
        else
        {
            CardSound::play_sound(SOUND_LOSE);
        }

        m_mainDialog->slot_hideAllPass();

        int nextPlayer = (player + 1) % 3;

        for (int i = 0; i < 2;++i)
        {
	        while(!m_mainDialog->m_cardList[nextPlayer + CARDLIST_LEFTPLAYER_OUTCARD].m_cardList.empty())
	        {
                Card* card = m_mainDialog->m_cardList[nextPlayer + CARDLIST_LEFTPLAYER_OUTCARD].SelectOneCard();
                card->hide();
	        }
            nextPlayer = (player + 1) % 3;
        }
        slot_close_all_timer();

        for(int i = 0; i < 3; ++i)
        {
            while(m_mainDialog->m_cardList[i+CARDLIST_LEFTPLAYER].m_cardList.size()!=0)
            {
	            Card* card = m_mainDialog->m_cardList[i + CARDLIST_LEFTPLAYER].SelectOneCard();
				m_mainDialog->m_cardList[i + CARDLIST_LEFTPLAYER_OUTCARD].addCard(card);
            }
            
        }
        
        delay_second(5000);
        m_mainDialog->slot_show_result(isWin);
        m_mainDialog->slot_show_win_page();
    }
    return isEnd;
}

void PlayRound::slot_close_all_timer()
{
    for(QTimer& timer : m_timerArray)
    {
        timer.stop();
    }
}

void PlayRound::slot_play_card_time_out()
{
    if (m_isStop) return;
	QLabel* label = m_mainDialog->m_lbTimerArray[currentPlayer];
    int num = label->text().toInt();
    num--;
    label->setText(QString::number(num));
    if(num < 1)
    {
	    if(lordPlayer == CARDLIST_LORD)
	    {
		    if(currentPlayer == CARDLIST_MIDPLAYER)
		    {

                slot_midPlayerNoCall();
		    }

            slot_end_timer(currentPlayer);
	    }
        else
        {
            slot_computerPlayCards(currentPlayer);

            m_mainDialog->slot_show_play_cards(false);
        }
    }

}

void PlayRound::slot_strat_timer(int player)
{
    m_timerArray[player].start(1000);
    m_mainDialog->m_lbTimerArray[player]->setText("30");
    m_mainDialog->m_lbClockArray[player]->show();
    m_mainDialog->m_lbTimerArray[player]->show();
}

void PlayRound::slot_end_timer(int player)
{
	m_timerArray[player].stop();
    m_mainDialog->m_lbClockArray[player]->hide();
    m_mainDialog->m_lbTimerArray[player]->hide();
}
