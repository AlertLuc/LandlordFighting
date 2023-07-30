#include "aiplaycard.h"
#include "map"
AIPlayCard::AIPlayCard()
{

}

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
            if(count >=3 && count >maxLen)
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
        if(card->m_point == Card_2||card->m_point ==Card_SmallKing||card->m_point == Card_BigKing)continue;
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
        if(card->m_point == Card_2||card->m_point ==Card_SmallKing||card->m_point == Card_BigKing)continue;
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
        if(card->m_point == Card_2)continue;
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
