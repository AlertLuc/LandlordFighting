#include "aiplaycard.h"
#include <rulers.h>
int AIPlayCard::findSmallestCards(QList<Card *> &cards)
{
    for(Card* card: cards)
    {
        card->setUnSelected();
    }
    int selected = 0;
    selected = findStraight(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findStraightPair(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findPlaneWithPair(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findPlaneWithOne(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findPlane(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findTripleWithPair(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findTripleWithOne(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findTriple(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findTripleWithPair(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findPair(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findSingle(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findBomb(cards, -1);
    if(selected != 0)
    {
        return selected;
    }
    selected = findKingBomb(cards);
    if(selected != 0)
    {
        return selected;
    }
    selected = findSmallestSingle(cards);
    if(selected != 0)
    {
        return selected;
    }
}

int AIPlayCard::findStraight(QList<Card *> &cards)
{
    std::map<int, Card*>mapPointCard;
    for(Card* card: cards)
    {
        if(card->m_point == Card_2 || card->m_point == Card_SmallKing
            || card->m_point == Card_BigKing) continue;
        mapPointCard[card->m_point] = card;
    }
    std::vector<int> vec;
    for(std::pair<int, Card*>p : mapPointCard)
    {
        vec.push_back(p.first);
    }
    int n = vec.size();
    if(n < 5)return 0;
    int maxLen = 0;
    int count = 1;
    int begin = vec[0];

    std::vector<int> vecBeginToEnd(2, 0);
    for(int i = 0; i< n- 1; ++i)
    {
        if(vec[i] + 1 == vec[i+1])
        {
            count++;
        }
        else{
            if(count >= 5 && count >maxLen)
            {
                maxLen = count;
                vecBeginToEnd = std::vector<int>{begin, vec[i]};

            }
            begin = vec[i+1];
            count = 1;
        }
    }
    if(count >= 5 && count > maxLen)
    {
        maxLen = count;
        vecBeginToEnd = std::vector<int>{begin, vec[n-1]};
    }
    if(maxLen!= 0)
    {
        for(int i = vecBeginToEnd[0]; i<=vecBeginToEnd[1];++i)
        {
            Card* card = mapPointCard[i];
            card->setSelected();
        }
    }
    return maxLen;
}

int AIPlayCard::findStraightPair(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2)continue;
        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second >= 2)
        {
            vec.push_back(p.first);
        }
    }
    if(vec.size() < 3)return 0;
    int n = vec.size();
    int count = 1;
    int begin = vec[0];
    std::vector<int>vecBeginToEnd(2,0);
    int maxLen = 0;
    for(int i = 0;i < n-1;++i)
    {
        if(vec[i]+1 == vec[i+1])count++;
        else
        {
            if(count >= 3 && count > maxLen)
            {
                maxLen = count;
                vecBeginToEnd = std::vector<int>{begin, vec[i]};

            }
            begin = vec[i+1];
            count = 1;
        }
    }
    if(count >= 3 && count > maxLen)
    {
        maxLen = count;
        vecBeginToEnd = std::vector<int>{begin,vec[n-1]};
    }
    int twocount = 0;
    int pos = vecBeginToEnd[1];
    if(maxLen != 0)
    {
        for(Card* card: cards)
        {
            if(card->m_point >= vecBeginToEnd[0] && card->m_point <= vecBeginToEnd[1])
            {
                if(card->m_point == pos)
                {
                    twocount++;
                }
                else
                {
                    pos--;
                    twocount = 1;
                }
                if(twocount <= 2)
                {
                    card->setSelected();
                }
            }
        }
    }
    return maxLen*2;
}

int AIPlayCard::findPlaneWithOne(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2 || card->m_point == Card_SmallKing || card->m_point == Card_BigKing)continue;
        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    std::vector<int>vecSingle;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3)
        {
            vec.push_back(p.first);
        }
        if(p.second == 1)
        {
            vecSingle.push_back(p.first);
        }
    }
    if(vec.size() < 2||vecSingle.size()<2)return 0;
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i]+1 == vec[i+1])
        {
            for(Card* card:cards)
            {
                if(card->m_point == vec[i]||card->m_point == vec[i+1]||
                    card->m_point == vecSingle[0]||card->m_point == vecSingle[1])
                {
                    card->setSelected();
                }
            }
            return 8;
        }
    }
    return 0;
}

int AIPlayCard::findPlaneWithPair(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2||card->m_point == Card_SmallKing||card->m_point == Card_BigKing)continue;
        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    std::vector<int>vecPair;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3)
        {
            vec.push_back(p.first);
        }
        if(p.second == 1)
        {
            vecPair.push_back(p.first);
        }
    }
    if(vec.size() < 2||vecPair.size()<2)return 0;
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i]+1 == vec[i+1])
        {
            for(Card* card:cards)
            {
                if(card->m_point == vec[i]||card->m_point == vec[i+1]||
                    card->m_point == vecPair[0]||card->m_point == vecPair[1])
                {
                    card->setSelected();
                }
            }
            return 10;
        }
    }
    return 0;
}

int AIPlayCard::findPlane(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2)continue;
        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3)
        {
            vec.push_back(p.first);
        }
    }
    int n  = vec.size();
    if(n < 2)return 0;
    for(int i = 0; i<n-1;++i)
    {
        if(vec[i]+1 == vec[i+1])
        {
            for(Card* card:cards)
            {
                if(card->m_point == vec[i]||card->m_point == vec[i+1])
                {
                    card->setSelected();
                }
            }
            return 6;
        }
    }
    return 0;
}

int AIPlayCard::findTripleWithOne(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(cards.size() > 6 && card->m_point == Card_2)continue;
        mapPointCount[card->m_point] += 1;
    }
    int triple = -1;
    int one = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && triple == -1)
        {
            triple = p.first;
        }
        if(p.second == 1 && one == -1)
        {
            one = p.first;
        }
        if(triple != -1 && one != -1)break;
    }
    if(triple == -1)return 0;
    if(one == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == triple || card->m_point == one)
        {
            card->setSelected();
        }
    }
    return 4;
}

int AIPlayCard::findTripleWithPair(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(cards.size() > 6 && card->m_point == Card_2)continue;
        mapPointCount[card->m_point] += 1;
    }
    int triple = -1;
    int two = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && triple == -1)
        {
            triple = p.first;
        }
        if(p.second == 1 && two == -1)
        {
            two = p.first;
        }
        if(triple != -1 && two != -1)break;
    }
    if(triple == -1)return 0;
    if(two == -1)return 0;

    for(Card* card:cards)
    {
        if(card->m_point == triple || card->m_point == two)
        {
            card->setSelected();
        }
    }
    return 5;
}

int AIPlayCard::findTriple(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(cards.size() > 6 && card->m_point == Card_2)continue;
        mapPointCount[card->m_point] += 1;
    }
    int triple = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && triple == -1)
        {
            triple = p.first;
        }
        if(triple != -1)break;
    }
    if(triple == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == triple)
        {
            card->setSelected();
        }
    }
    return 3;
}

int AIPlayCard::findPair(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2)continue;
        mapPointCount[card->m_point] += 1;
    }
    int two = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 2 && two == -1)
        {
            two = p.first;
        }
        if(two != -1)break;
    }
    if(two == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == two)
        {
            card->setSelected();
        }
    }
    return 2;
}

int AIPlayCard::findSingle(QList<Card *> &cards)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_SmallKing|| card->m_point == Card_BigKing)continue;
        mapPointCount[card->m_point] += 1;
    }
    int single = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 1 && single == -1)
        {
            single = p.first;
        }
        if(single != -1)break;
    }
    if(single == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == single)
        {
            card->setSelected();
        }
    }
    return 1;
}

int AIPlayCard::findBomb(QList<Card *> &cards, int value)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        mapPointCount[card->m_point] += 1;
    }
    int bomb = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 4 && bomb == -1)
        {
            bomb = p.first;
        }
        if(bomb != -1)break;
    }
    if(bomb == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == bomb)
        {
            card->setSelected();
        }
    }
    return 4;
}

int AIPlayCard::findKingBomb(QList<Card *> &cards)
{
    if(cards.size()<2)return 0;
    if(cards.at(0)->m_point == Card_BigKing && cards.at(1)->m_point == Card_SmallKing)
    {
        cards.at(0)->setSelected();
        cards.at(1)->setSelected();
        return 2;
    }
    return 0;
}

int AIPlayCard::findSmallestSingle(QList<Card *> &cards)
{
    if(cards.size()==0)return 0;
    cards.back()->setSelected();
    return 1;
}

QList<Card *> AIPlayCard::BeatCards(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    QList<Card*>cards;
    int selected = 0;
    for(Card* card:cardInHand)
    {
        card->setUnSelected();
    }
    if(cardLastPlayer.size() == 0)
    {
        findSmallestCards(cardInHand);
    }
    else
    {
        if(KINGBOMB == Rulers::getCardtype(cardLastPlayer))
            return cards;
        selected = findBeatBySameType(cardInHand, cardLastPlayer);
        if(selected ==0)
        {
            if(BOMB==Rulers::getCardtype(cardLastPlayer))
            {
                selected = findBomb(cardInHand, cardLastPlayer.back()->m_point);
            }
            else{
                selected = findBomb(cardInHand, -1);
            }
            if(selected ==0)
            {
                selected = findKingBomb(cardInHand);
                if(selected == 0)
                {
                    return cards;
                }

            }
        }
    }
    for(Card* card : cardInHand)
    {
        if(card->m_isClicked)
            cards.append(card);
    }
}

int AIPlayCard::findBeatBySameType(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    int type = Rulers::getCardtype(cardLastPlayer);
    int selected = 0;
    switch (type) {
    case CARDTYPE_NONE:
        selected = 0;
        break;
    case FOUR_WITH_TWO:
        break;
    case SINGLE:
        selected = findSingle(cardInHand, cardLastPlayer.back()->m_point);
        break;
    case TRIPLE:
        selected = findTriple(cardInHand, cardLastPlayer.back()->m_point);
        break;
    case TRIPLE_WITH_ONE:
    {
        int point = 0;
        std::map<int, int>mapPointCount;
        for(Card* card: cardLastPlayer){
            mapPointCount[card->m_point] += 1;
        }
        for(std::pair<int, int> p : mapPointCount)
        {
            if(p.second == 3)
            {
                point = p.first;
                break;
            }
        }
        selected = findTriple(cardInHand, point);
    }
    break;
    case TRIPLE_WITH_TWO:
    {
        int point = 0;
        std::map<int, int>mapPointCount;
        for(Card* card: cardLastPlayer){
            mapPointCount[card->m_point] += 1;
        }
        for(std::pair<int, int> p : mapPointCount)
        {
            if(p.second == 3)
            {
                point = p.first;
                break;
            }
        }
        selected = findTripleWithPair(cardInHand, point);
    }
    break;
    case STRAIGHT_PAIR:
        selected = findStraightPair(cardInHand, cardLastPlayer.back()->m_point, cardLastPlayer.size()/2);
        break;
    case STRAIGHT:
        selected = findStraight(cardInHand, cardLastPlayer.back()->m_point, cardLastPlayer.size());
        break;
    case PAIR:
        selected = findPair(cardInHand, cardLastPlayer.back()->m_point);
        break;
    case FOUR_WITH_TWO_PAIR:
        break;
    case PLANE:
        selected = findPlane(cardInHand, cardLastPlayer.back()->m_point);
        break;
    case PLANE_WITH_WING:
    {
        int point = 0;
        std::map<int, int>mapPointCount;
        for(Card* card: cardLastPlayer){
            mapPointCount[card->m_point] += 1;
        }
        std::vector<int> vec;
        std::vector<int> vecSingle;
        std::vector<int> vecTwo;
        for(std::pair<int, int> p : mapPointCount)
        {
            if(p.second == 3)
            {
                vec.push_back(p.first);
            }
            if(p.second == 2)
            {
                vecTwo.push_back(p.first);
            }
            if(p.second == 1)
            {
                vecSingle.push_back(p.first);
            }
        }
        if(vecTwo.size()==0)
        {
            selected = findPlaneWithOne(cardInHand, vec.front());
        }
        else
        {
            selected = findPlaneWithPair(cardInHand, vec.front());
        }

    }
        break;
    case BOMB:
        selected = 0;
        break;
    case KINGBOMB:
        selected = 0;
        break;
    }
}

int AIPlayCard::findStraight(QList<Card *> &cards, int point, int len)
{
    std::map<int, Card*>mapPointCard;
    for(Card* card: cards)
    {
        if(card->m_point == Card_2 || card->m_point == Card_SmallKing
            || card->m_point == Card_BigKing) continue;
        if(card->m_point>point)
        mapPointCard[card->m_point] = card;
    }
    std::vector<int> vec;
    for(std::pair<int, Card*>p : mapPointCard)
    {
        vec.push_back(p.first);
    }
    int n = vec.size();
    if(n < len)return 0;
    int count = 1;
    int begin = vec[0];

    std::vector<int> vecBeginToEnd(2, 0);
    for(int i = 0; i< n- 1; ++i)
    {
        if(vec[i] + 1 == vec[i+1])
        {
            count++;
            if(count == len)
            {
                vecBeginToEnd = std::vector<int>{begin,begin+len-1};
                for(int i = vecBeginToEnd[0]; i <= vecBeginToEnd[1]; ++i)
                {
                    Card* card = mapPointCard[i];
                    card->setSelected();
                }
                return len;
            }
        }
        else{

            begin = vec[i+1];
            count = 1;
        }
    }
    return 0;
}

int AIPlayCard::findStraightPair(QList<Card *> &cards, int point, int len)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2)continue;
        if(card->m_point > point);
        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second >= 2)
        {
            vec.push_back(p.first);
        }
    }
    if(vec.size() < len)return 0;
    int n = vec.size();
    int count = 1;
    int begin = vec[0];
    std::vector<int>vecBeginToEnd(2,0);
    for(int i = 0;i < n-1;++i)
    {

        if(vec[i]+1 == vec[i+1])
        {

            count++;
            if(count == len)
            {
                vecBeginToEnd = std::vector<int>{begin,begin+len-1};
                int twocount = 0;
                int pos = vecBeginToEnd[1];
                for(Card* card: cards)
                {
                    if(card->m_point >= vecBeginToEnd[0] && card->m_point <= vecBeginToEnd[1])
                    {
                        if(card->m_point == pos)
                        {
                            twocount++;
                        }
                        else
                        {
                            pos--;
                            twocount = 1;
                        }
                        if(twocount <= 2)
                        {
                            card->setSelected();
                        }
                    }
                }
                return len;
            }
        }
        else
        {
            begin = vec[i+1];
            count = 1;
        }
    }
    return 0;
}

int AIPlayCard::findPlaneWithOne(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    if(cards.size() < 8) return 0;
    for(Card* card: cards){
        if(cards.at(0)->m_point==Card_BigKing && cards.at(1)->m_point == Card_SmallKing)
        {
            if(card->m_point ==Card_SmallKing||card->m_point == Card_BigKing)continue;
        }

        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    std::vector<int>vecSingle;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && p.first > point)
        {
            vec.push_back(p.first);
        }
        if(p.second == 1)
        {
            vecSingle.push_back(p.first);
        }
    }
    if(vec.size() < 2||vecSingle.size()<2)return 0;
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i]+1 == vec[i+1])
        {
            for(Card* card:cards)
            {
                if(card->m_point == vec[i]||card->m_point == vec[i+1]||
                    card->m_point == vecSingle[0]||card->m_point == vecSingle[1])
                {
                    card->setSelected();
                }
            }
            return 8;
        }
    }
    return 0;
}

int AIPlayCard::findPlaneWithPair(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    if(cards.size() < 10) return 0;
    for(Card* card: cards){
        if(card->m_point==Card_BigKing && card->m_point == Card_SmallKing)
        {
            if(card->m_point ==Card_SmallKing||card->m_point == Card_BigKing)continue;
        }

        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    std::vector<int>vecTwo;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && p.first > point)
        {
            vec.push_back(p.first);
        }
        if(p.second == 2)
        {
            vecTwo.push_back(p.first);
        }
    }
    if(vec.size() < 2||vecTwo.size()<2)return 0;
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i]+1 == vec[i+1])
        {
            for(Card* card:cards)
            {
                if(card->m_point == vec[i]||card->m_point == vec[i+1]||
                    card->m_point == vecTwo[0]||card->m_point == vecTwo[1])
                {
                    card->setSelected();
                }
            }
            return 10;
        }
    }
    return 0;
}

int AIPlayCard::findPlane(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point == Card_2)continue;
        if(card->m_point > point)
        mapPointCount[card->m_point] += 1;
    }
    std::vector<int>vec;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3)
        {
            vec.push_back(p.first);
        }
    }
    int n  = vec.size();
    if(n < 2)return 0;
    for(int i = 0; i<n-1;++i)
    {
        if(vec[i]+1 == vec[i+1])
        {
            for(Card* card:cards)
            {
                if(card->m_point == vec[i]||card->m_point == vec[i+1])
                {
                    card->setSelected();
                }
            }
            return 6;
        }
    }
    return 0;
}

int AIPlayCard::findTripleWithOne(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){

        mapPointCount[card->m_point] += 1;
    }
    int triple = -1;
    int one = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && triple == -1 && p.first>point)
        {
            triple = p.first;
        }
        if(p.second == 1 && one == -1)
        {
            one = p.first;
        }
        if(triple != -1 && one != -1)break;
    }
    if(triple == -1)return 0;
    if(one == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == triple || card->m_point == one)
        {
            card->setSelected();
        }
    }
    return 4;
}

int AIPlayCard::findTripleWithPair(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        mapPointCount[card->m_point] += 1;
    }
    int triple = -1;
    int two = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && triple == -1 && p.first > point)
        {
            triple = p.first;
        }
        if(p.second == 2 && two == -1)
        {
            two = p.first;
        }
        if(triple != -1 && two != -1)break;
    }
    if(triple == -1)return 0;
    if(two == -1)return 0;

    for(Card* card:cards)
    {
        if(card->m_point == triple || card->m_point == two)
        {
            card->setSelected();
        }
    }
    return 5;
}

int AIPlayCard::findTriple(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point > point)
        mapPointCount[card->m_point] += 1;
    }
    int triple = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 3 && triple == -1)
        {
            triple = p.first;
        }
        if(triple != -1)break;
    }
    if(triple == -1)return 0;
    for(Card* card:cards)
    {
        if(card->m_point == triple)
        {
            card->setSelected();
        }
    }
    return 3;
}

int AIPlayCard::findPair(QList<Card *> &cards, int point)
{
    std::map<int, int>mapPointCount;
    for(Card* card: cards){
        if(card->m_point>point)
        mapPointCount[card->m_point] += 1;
    }
    int two = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 2 && two == -1)
        {
            two = p.first;
        }
        if(two != -1)break;
    }

    if(two == -1){
        if(point<Card_2 && (mapPointCount.count(Card_2)==3||mapPointCount.count(Card_2)==4))
        {
            int _count =0;
            for(Card* card:cards)
            {
                if(card->m_point == Card_2)
                {
                    card->setSelected();
                    _count++;
                }
                if(_count>=2)
                {
                    return 2;
                }
            }
        }
        return 0;
    }
    for(Card* card:cards)
    {
        if(card->m_point == two)
        {
            card->setSelected();
        }
    }
    return 2;
}

int AIPlayCard::findSingle(QList<Card *> &cards, int point)
{
    QList<Card*> newCards = cards;
    if(cards.size()>=5)
    {
        while(removeStraitht(newCards));
    }
    std::map<int, int>mapPointCount;
    for(Card* card: newCards){
        if(card->m_point > point)
        mapPointCount[card->m_point] += 1;
    }
    int single = -1;
    for(std::pair<int, int> p : mapPointCount)
    {
        if(p.second == 1 && single == -1)
        {
            single = p.first;
        }
        if(single != -1)break;
    }
    if(single == -1){
        if(point < Card_2)
        {
            for(Card*card: newCards)
            {
                if(card->m_point == Card_2)

                    card->setSelected();
                    return 1;
            }
        }
        return 0;
    }
    for(Card* card:newCards)
    {
        if(card->m_point == single)
        {
            card->setSelected();
        }
    }
    return 1;
}

bool AIPlayCard::removeStraitht(QList<Card *> &cards)
{
    //

    std::map<int, Card*>mapPointCard;
    for(Card* card: cards)
    {
        if(card->m_point == Card_2 || card->m_point == Card_SmallKing
            || card->m_point == Card_BigKing) continue;
        mapPointCard[card->m_point] = card;
    }
    std::vector<int> vec;
    for(std::pair<int, Card*>p : mapPointCard)
    {
        vec.push_back(p.first);
    }
    int n = vec.size();
    if(n < 5)return false;
    int count = 1;
    int begin = vec[0];

    std::vector<int> vecBeginToEnd(2, 0);
    for(int i = 0; i< n- 1; ++i)
    {
        if(vec[i] + 1 == vec[i+1])
        {
            count++;
        }
        else{
            if(count >= 5 )
            {
                vecBeginToEnd = std::vector<int>{begin, vec[i]};
                for(int j = vecBeginToEnd[1]; j >= vecBeginToEnd[0]; --j)
                {
                    Card* card = mapPointCard[j];
                    for(auto ite = cards.begin();ite != cards.end(); )
                    {
                        if(card == *ite)
                        {
                            ite = cards.erase(ite);
                            break;
                        }
                        else
                        {
                            ++ite;
                        }
                    }
                }
                    return true;
            }
            begin = vec[i+1];
            count = 1;
        }
    }
    if(count >= 5)
    {
        vecBeginToEnd = std::vector<int>{begin, vec[n-1]};
        for(int j = vecBeginToEnd[1]; j >= vecBeginToEnd[0]; --j)
        {
            Card* card = mapPointCard[j];
            for(auto ite = cards.begin();ite != cards.end(); )
            {
                    if(card == *ite)
                    {
                    ite = cards.erase(ite);
                    break;
                    }
                    else
                    {
                    ++ite;
                    }
            }
        }
        return true;
    }
    return false;
}
