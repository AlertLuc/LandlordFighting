#ifndef CARDLIST_H
#define CARDLIST_H

#include <QObject>
#include <QList>
#include <card.h>

enum CARDLIST_TYPE{
    CARDLIST_LEFTPLAYER,
    CARDLIST_MIDPLAYER,
    CARDLIST_RIGHTPLAYER,
    CARDLIST_LORD,// 地主牌
    CARDLIST_WHOLE,// 牌堆
    CARDLIST_LEFTPLAYER_OUTCARD,
    CARDLIST_MIDPLAYER_OUTCARD,
    CARDLIST_RIGHTPLAYER_OUTCARD

};


class CardList : public QObject
{
    Q_OBJECT
public:
    explicit CardList(QObject *parent = nullptr);

    // 赋值类型
    void setCardListType(int type);

    // 添加牌
    void addCard(Card* card);

    // 以列表形式添加牌
    void addCard(QList<Card*> card);

private:
    int m_cardListType;
    // 牌堆
    int m_beginX = 0;
    int m_beginY = 0;
public:
    QList<Card*> m_cardlist;


signals:

};

#endif // CARDLIST_H
