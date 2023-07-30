#ifndef CARDLIST_H
#define CARDLIST_H

#include <QObject>
#include <QList>
#include <card.h>

#define CARDLIST_TYPE_COUNT  (8)
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
    void addCard(QList<Card*> cards);
    // 显示牌堆
    void ShowCard();
    // 打印牌堆
    void PrintCard();
    // 获取选中的列表
    QList<Card*> SelectCardList();
    // 删除选中的列表
    void DeleteCardList();
    // 从牌堆选一张牌
    Card* SelectOneCard();
    // 洗牌
    void shuffle();
    // 排序
    void SortCard();

private:
    // 获取牌权重
    int getCardValue(Card*card);
    // 牌类型
    int m_cardListType;
    // 牌堆
    int m_beginX = 0;
    int m_beginY = 0;

public:
    // 管理牌列表
    QList<Card*> m_cardlist;

signals:

};

#endif // CARDLIST_H
