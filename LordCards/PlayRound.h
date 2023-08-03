#ifndef CARDROUND_H
#define CARDROUND_H
#include <QObject>
#include<card.h>
#include<aiplaycard.h>
#include<QTime>
class main_dialog;
class PlayRound : public QObject
{
    Q_OBJECT
public:
    explicit PlayRound(main_dialog *p, QObject *parent);

    void initRound();

    void delay_second(int m_second);

signals:



public:
    // 叫地主
    void decideBeginLord();

    void turnCallLord(int player);

    void callLordGiveUp(int player);

    void slot_midPlayerCallLord();

    void slot_midPlayerNoCall();

    // 电脑叫不叫地主 手牌有炸
    void slot_computerCallLord(int player);

    // 出牌阶段
    void startRound(int player);

    void turnPlayer(int player);

    void slot_midPlayerPlayCards();

    void slot_midPlayerPass();

    void slot_computerRound(int player);

    void slot_computerPlayCards(int player);


    // 结算
    // 出牌
    int biggestPlayer;

    int currentPlayer;

    // 上一个出牌人牌组
    QList<Card*>lastPlayerCards;

    //叫地主
    int beginCallLord;

    bool isEndCall;

    int lordPlayer;

    QTime m_timerArray[3];

private:
    main_dialog* m_mainDialog;

public slots:
    void slot_play_card_time_out();

    void slot_strat_timer(int player);

    void slot_end_timer(int player);

};
#endif // CARDROUND_H
