#ifndef CARDROUND_H
#define CARDROUND_H

#include <QObject>

#include"card.h"
#include"aiplaycard.h"
class MainDialog;
class Cardround : public QObject
{
    Q_OBJECT
public:
    explicit Cardround(MainDialog *p, QObject *parent);
    void initRound();
    void delaySecond(int msec);
signals:

public:
    // 叫地主

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



private:
    MainDialog* m_maindialog;

};

#endif // CARDROUND_H
