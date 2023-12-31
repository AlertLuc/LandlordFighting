#include "cardlist.h"
#include "card.h"
#include "QDebug"
#include "QString"
#include <random>
#include "QDateTime"
CardList::CardList(QObject *parent)
    : QObject{parent}{}
// 赋值类型
void CardList::setCardListType(int type)
{
    m_cardListType = type;
}

// 添加牌
void CardList::addCard(Card *card)
{
    if(m_cardListType == CARDLIST_MIDPLAYER)
    {
        card->setCardPositive(true);
    }
    if( m_cardListType == CARDLIST_LEFTPLAYER_OUTCARD||
        m_cardListType == CARDLIST_MIDPLAYER_OUTCARD ||
        m_cardListType == CARDLIST_RIGHTPLAYER_OUTCARD)
    {
        card->setCardPositive(true);
    }
    m_cardList.append(card);
}
// 以列表形式添加牌
void CardList::addCard(QList<Card *> cards)
{
    for(auto card : cards)
    {
        addCard(card);
    }
}
// 显示牌堆
void CardList::ShowCard()
{
    int count = 0;
    switch (m_cardListType) {
        case CARDLIST_LEFTPLAYER:
            m_beginX = 70;
            m_beginY = 170;
            for(auto card : m_cardList)
            {
                card->setCardPositive(false);
                card->move(m_beginX, m_beginY+(count++)*10);
                card->raise();
                card->show();
            }
            break;
        case CARDLIST_MIDPLAYER:
            m_beginX = 1000/2 - (Card_Width + (m_cardList.size()-1)*CARD_SHOW_WIDTH)/2;
            m_beginY = 650 - 150;
            for(auto card : m_cardList)
            {
                card->setCardPositive(true);
                card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);

                if(card->m_isClicked)
                {
                    card->slot_moveUp();
                }
                card->raise();
                card->show();
            }
            break;
        case CARDLIST_RIGHTPLAYER:
            m_beginX = 850;
            m_beginY = 170;
            for(auto card : m_cardList)
            {
                card->setCardPositive(false);
                card->move(m_beginX, m_beginY+(count++)*10);
                card->raise();
                card->show();
            }
            break;
        case CARDLIST_LORD:
            m_beginX = 1000/2 - (Card_Width*3 + 20*2)/2;
            m_beginY = 50;
            for(const auto card : m_cardList)
            {
                card->move(m_beginX+(count++)*(Card_Width +20),m_beginY);
                card->raise();
                card->show();
            }
            break;
        case CARDLIST_WHOLE:
            m_beginX = 1000/2 - (Card_Width + (m_cardList.size()-1)*5)/2;
            m_beginY = 650/2 - Card_Height/2;
            for(auto card : m_cardList)
            {
                card->setCardPositive(false);
                card->move(m_beginX+(count++)*5,m_beginY);
                card->raise();
                card->show();
            }
            break;
        case CARDLIST_LEFTPLAYER_OUTCARD:
            m_beginX = 70+80+50;
            m_beginY = 170+10;
            for(auto card : m_cardList)
            {
                card->setCardPositive(true);
                card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);
                card->raise();
                card->show();
            }
            break;
        case CARDLIST_MIDPLAYER_OUTCARD:
            m_beginX = 1000/2 - (Card_Width + (m_cardList.size()-1)*CARD_SHOW_WIDTH)/2;
            m_beginY = 415 - 105;
            for(auto card : m_cardList)
            {
                card->setCardPositive(true);
                card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);

                if(card->m_isClicked)
                {
                    card->slot_moveUp();
                }
                card->raise();
                card->show();
            }
            break;
            break;
        case CARDLIST_RIGHTPLAYER_OUTCARD:
            m_beginX = 800-(Card_Width+(m_cardList.size()-1)*CARD_SHOW_WIDTH);
            m_beginY = 170+10;
            for(auto card : m_cardList)
            {
                card->setCardPositive(true);
                card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);
                card->raise();
                card->show();
            }
            break;
    }
}
// 打印牌堆
void CardList::PrintCard()
{
    QString str;

    for(auto card : m_cardList)
    {
        if(card->m_point == Suit_SamllKing)
        {
            str += "小王 ";
            continue;
        }
        if(card->m_point == Suit_BigKing)
        {
            str += "大王 ";
            continue;
        }
        switch (card->m_suit) {
        case Diamond:
            str += "方块";
            break;
        case Club:
            str += "梅花";
            break;

        case Heart:
            str += "红桃";
            break;

        case Spade:
            str += "黑桃";
            break;

        default:
            break;
        }
        if(card->m_point == Card_A)
        {
            str += "A ";
        }
        else if(card->m_point == Card_2)
        {
            str += "2 ";
        }
        else
        {
            str += QString::number(card->m_point + 3);
            str += " ";
        }
    }
    qDebug()<<str;
}
// 获取选中的列表
QList<Card *> CardList::SelectCardList()
{
    QList<Card*> lst;
    for(auto card : m_cardList)
    {
        if(card->m_isClicked)
        {
            lst.append(card);
        }
    }
    return lst;
}
// 删除选中的列表
void CardList::DeleteCardList()
{
    // 移除列表节点
    for(auto ite = m_cardList.begin(); ite != m_cardList.end(); )
    {
        Card* card =*ite;
        if(card->m_isClicked)
        {
            ite = m_cardList.erase(ite);
        }
        else
        {
            ++ite;
        }
    }
}
// 从牌堆选一张牌
Card *CardList::SelectOneCard()
{
    if(!m_cardList.isEmpty())
    {
        return m_cardList.takeFirst();
    }
    return nullptr;
}

void CardList::setAllCardsPositive(bool flag)
{
    for(auto card: m_cardList)
    {
        qDebug()<<" "<<flag;
        card->setCardPositive(flag);
    }
}
// 洗牌
void CardList::shuffle()
{
	qint64 seed = QDateTime::currentSecsSinceEpoch();
    std::shuffle(m_cardList.begin(), m_cardList.end(), std::default_random_engine(seed));
}
// 排序
void CardList::SortCard()
{
    std::sort(m_cardList.begin(), m_cardList.end(),[this](Card* &a, Card* &b)
    {
        return getCardValue(a) > getCardValue(b);
    });
}
// 获取牌权重
int CardList::getCardValue(Card *card)
{
    if(card->m_point == Card_BigKing)return 888;
    if(card->m_point == Card_SmallKing)return 666;
    return card->m_point*10 +(4-card->m_suit);
}



