#include "rulers.h"
#include <map>

Rulers::Rulers()
{

}

int Rulers::getCardtype(QList<Card *> &cards)
{
    int n = cards.count();
    if(n == 0)return CARDTYPE_NONE;
    if(n == 1)return STRAIGHT;
    else if(n == 2){
        if(cards.at(0)->m_point == cards.at(1)->m_point)
        {
            return PAIR;
        }
        else if(cards.at(0)->m_point == Card_BigKing && Card_SmallKing == cards.at(1)->m_point)
        {
            return KINGBOMB;
        }
    }
    else if(n == 3){
        if(cards.at(0)->m_point ==  cards.at(1)->m_point && cards.at(1)->m_point == cards.at(2)->m_point)
        {
            return TRIPLE;
        }
    }
    else if(n == 4){

        if(cards.at(0)->m_point ==  cards.at(1)->m_point && cards.at(1)->m_point == cards.at(2)->m_point
            && cards.at(2)->m_point == cards.at(3)->m_point)
        {
            return BOMB;
        }
        if((cards.at(0)->m_point !=  cards.at(1)->m_point &&
             cards.at(1)->m_point == cards.at(2)->m_point &&
             cards.at(2)->m_point == cards.at(3)->m_point) ||
            (cards.at(0)->m_point ==  cards.at(1)->m_point && cards.at(1)->m_point == cards.at(2)->m_point && cards.at(2)->m_point != cards.at(3)->m_point))
        {
            return TRIPLE_WITH_ONE;
        }
    }
    else if(n == 5){
        if((cards.at(0)->m_point ==  cards.at(1)->m_point &&
             cards.at(1)->m_point != cards.at(2)->m_point &&
             cards.at(2)->m_point == cards.at(3)->m_point &&
             cards.at(3)->m_point == cards.at(4)->m_point) ||
            (cards.at(0)->m_point ==  cards.at(1)->m_point && cards.at(1)->m_point == cards.at(2)->m_point && cards.at(2)->m_point != cards.at(3)->m_point && cards.at(3)->m_point == cards.at(4)->m_point))
        {
            return TRIPLE_WITH_TWO;
        }
        if(isStraight(cards))return STRAIGHT;
    }
    else if(n == 6){
        if(isStraight(cards))return STRAIGHT;
        if(isStraightPair(cards))return STRAIGHT_PAIR;
        if(isPlane(cards))return PLANE;
        if(isFourWithTwo(cards))return FOUR_WITH_TWO;
    }
    else if(n == 7){
        if(isStraight(cards))return STRAIGHT;
    }
    else if(n == 8){

        if(isStraight(cards))return STRAIGHT;

        if(isStraightPair(cards))return STRAIGHT;

        if(isFourWithTwoPair(cards))return FOUR_WITH_TWO_PAIR;

        if(isPlaneWithWing(cards))return PLANE_WITH_WING;

    }
    else if(n == 9){
        if(isStraight(cards))return STRAIGHT;
        if(isPlane(cards))return PLANE;
    }
    else if(n == 10){
        if(isStraight(cards))return STRAIGHT;
        if(isStraightPair(cards))return STRAIGHT_PAIR;
        if(isPlaneWithWing(cards))return PLANE_WITH_WING;
    }

    else if(n == 11){
        if(isStraight(cards))return STRAIGHT;

    }
    else if(n == 12){
        if(isStraight(cards))return STRAIGHT;
        if(isStraightPair(cards))return STRAIGHT_PAIR;
        if(isPlane(cards))return PLANE;
    }
    else if(n == 13){

    }
    else if(n == 14){
        if(isStraight(cards))return STRAIGHT;
    }
}

bool Rulers::isStraight(QList<Card *> &cards)
{
    // 牌数不足5
    //无2 小王大王
    //牌不能重复
    //第一张与最后一张 n-1
    int n = cards.count();
    if(n < 5)return false;
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    map<int,int>mapPointToCount;
    for(auto card : cards)
    {
        if(mapPointToCount.count(card->m_point)!=0)return false;
        else
            mapPointToCount[card->m_point] = 1;
    }
    if(cards.front()->m_point - cards.back()->m_point == n - 1) return true;
    return false;
}

bool Rulers::isPlane(QList<Card *> &cards)
{
    // 牌数不足6 必须是3倍数
    //无2 小王大王
    //每张牌出现次数为3
    //第一张-最后一张 = n/3 - 1
    int n = cards.count();
    if(n < 6)return false;
    if(n % 3 != 0)return false;
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    map<int,int>mapPointToCount;
    for(auto card : cards)
    {
        if(mapPointToCount.count(card->m_point)!=0)mapPointToCount[card->m_point] += 1;
        else
            mapPointToCount[card->m_point] = 1;
    }
    for(pair<int, int> p:mapPointToCount){
        if(p.second != 3)return false;
    }
    if(cards.front()->m_point - cards.back()->m_point == n/3 - 1) return true;
    return false;
}

bool Rulers::isPlaneWithWing(QList<Card *> &cards)
{
    // 8张10张
    // 统计个数
    // 无2 小王大王
    // 判断3个是否连续
    // 8 单牌带2个 要不相等，要有两个数
    // 10 对子个数为2 要有两个数 不相等
    int n = cards.size();
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    map<int,int>mapPointToCount;
    for(auto card : cards)
    {
        if(mapPointToCount.count(card->m_point)!=0)mapPointToCount[card->m_point] += 1;
        else
            mapPointToCount[card->m_point] = 1;
    }
    if(n == 8)
    {
        int count = 0;
        vector<int> vec;
        // 遍历 map
        for(pair<int, int> p:mapPointToCount){
            if(p.second == 3)
            {
                vec.push_back(p.first);
            }
            if(p.second == 1)
            {
                count++;
            }
        }
        // vector是否有两个元素 插值为1
        if(count != 2)return false;
        if(vec.size() != 2)return false;
        if(vec[0] + 1 != vec[1])return false;
        // 单牌
        return true;
    }
    if(n == 10)
    {
        int count = 0;
        vector<int> vec;
        // 遍历 map
        for(pair<int, int> p:mapPointToCount){
            if(p.second == 3)
            {
                vec.push_back(p.first);
            }
            if(p.second == 1)
            {
                return false;
            }
            if(p.second == 2)
            {
                count++;
            }
        }
        // vector是否有两个元素 插值为1
        if(count != 2)return false;
        if(vec.size() != 2)return false;
        if(vec[0] + 1 != vec[1])return false;
        // 单牌
        return true;
    }
    return false;
}

bool Rulers::isFourWithTwo(QList<Card *> &cards)
{
    // 牌数不足6
    map<int,int>mapPointToCount;
    for(auto card : cards)
    {
        if(mapPointToCount.count(card->m_point)!=0)mapPointToCount[card->m_point] += 1;
        else
            mapPointToCount[card->m_point] = 1;
    }
    int count = 0;
    for(pair<int, int> p:mapPointToCount){
        if(p.second == 4)
        {
            count += 40;
        }
        if(p.second == 1)
        {
            count += 1;
        }
    }
    if(count == 42)return true;
    return false;
}

bool Rulers::isFourWithTwoPair(QList<Card *> &cards)
{
    map<int,int>mapPointToCount;
    for(auto card : cards)
    {
        if(mapPointToCount.count(card->m_point)!=0)mapPointToCount[card->m_point] += 1;
        else
            mapPointToCount[card->m_point] = 1;
    }
    int count = 0;
    for(pair<int, int> p:mapPointToCount){
        if(p.second == 4)
        {
            count += 40;
        }
        if(p.second == 2)
        {
            count += 2;
        }
    }
    if(count == 44)return true;
    return false;
}

bool Rulers::isStraightPair(QList<Card *> &cards)
{
    // 牌数不足6 必须是偶数
    //无2 小王大王
    //每张牌出现次数为2
    //第一张-最后一张 = n/2 - 1
    int n = cards.count();
    if(n < 6)return false;
    if(n % 2 != 0)return false;
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    map<int,int>mapPointToCount;
    for(auto card : cards)
    {
        if(mapPointToCount.count(card->m_point)!=0)mapPointToCount[card->m_point] += 1;
        else
            mapPointToCount[card->m_point] = 1;
    }
    for(pair<int, int> p:mapPointToCount){
        if(p.second != 2)return false;
    }
    if(cards.front()->m_point - cards.back()->m_point == n/2 - 1) return true;
    return false;
}

bool Rulers::compareCards(QList<Card *> &cards1, QList<Card *> &cards2)
{
    int type1 = getCardtype(cards1);
    int type2 = getCardtype(cards2);
    if(type1 == CARDTYPE_NONE)
        return false;
    if(type1 == type2 && cards1.size() == cards2.size())
    {
        return compareSameTypeCards(cards1, cards2,type1);
    }
    if(type1 == KINGBOMB)
        return true;
    if(type1 == BOMB && type2 != KINGBOMB)
        return true;
    return false;
}

bool Rulers::compareSameTypeCards(QList<Card *> &cards1, QList<Card *> &cards2, int type)
{
    int value1 = 0; int value2 = 0;

    switch (type) {
        case FOUR_WITH_TWO:
    {   map<int, int> mapPointToCount1;
        map<int, int> mapPointToCount2;
        for(auto card: cards1)
        {
            mapPointToCount1[card->m_point] += 1;
            if(mapPointToCount1[card->m_point] == 4)
            {
                value1 = card->m_point;
                break;
            }
        }
        for(auto card: cards2)
        {
            mapPointToCount2[card->m_point] += 1;
            if(mapPointToCount2[card->m_point] == 4) value2 = card->m_point;
        }
        return value1 > value2;
    }
                break;
        case CARDTYPE_NONE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case SINGLE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case TRIPLE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case TRIPLE_WITH_ONE:
        {   map<int, int> mapPointToCount1;
            map<int, int> mapPointToCount2;
            for(auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 3) value1 = card->m_point;
            }
            for(auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 3) value2 = card->m_point;
            }
            return value1 > value2;
        }
                break;
        case TRIPLE_WITH_TWO:
        {   map<int, int> mapPointToCount1;
            map<int, int> mapPointToCount2;
            for(auto card: cards1)
            {
            mapPointToCount1[card->m_point] += 1;
            if(mapPointToCount1[card->m_point] == 3) value1 = card->m_point;
            }
            for(auto card: cards2)
            {
            mapPointToCount2[card->m_point] += 1;
            if(mapPointToCount2[card->m_point] == 3) value2 = card->m_point;
            }
            return value1 > value2;
        }
                break;
        case STRAIGHT_PAIR:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case STRAIGHT:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case PAIR:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case BOMB:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case FOUR_WITH_TWO_PAIR:
        {   map<int, int> mapPointToCount1;
            map<int, int> mapPointToCount2;
            for(auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 4) value1 = card->m_point;
            }
            for(auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 4) value2 = card->m_point;
            }
            return value1 > value2;
        }
                break;
        case PLANE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
                break;
        case PLANE_WITH_WING:
        {   map<int, int> mapPointToCount1;
            map<int, int> mapPointToCount2;
            for(auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 3)
                {
                    value1 = card->m_point;
                    break;
                }
            }
            for(auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 3) value2 = card->m_point;
            }
            return value1 > value2;
        }
                break;
        case FOUR_WITH_ONE:
        {   map<int, int> mapPointToCount1;
            map<int, int> mapPointToCount2;
            for(auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 4) value1 = card->m_point;
            }
            for(auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 4) value2 = card->m_point;
            }
            return value1 > value2;
        }
                break;
        default:
            break;
    }

}
//switch (type) {
//case FOUR_WITH_TWO:

//    break;
//case CARDTYPE_NONE:

//    break;
//case SINGLE:

//    break;
//case TRIPLE:

//    break;
//case TRIPLE_WITH_ONE:

//    break;
//case TRIPLE_WITH_TWO:

//    break;
//case STRAIGHT_PAIR:

//    break;
//case STRAIGHT:

//    break;
//case PAIR:

//    break;
//case KINGBOMB:

//    break;
//case BOMB:

//    break;
//case FOUR_WITH_TWO_PAIR:

//    break;
//case PLANE:

//    break;
//case PLANE_WITH_WING:

//    break;
//case FOUR_WITH_ONE:

//    break;
//default:
//    break;
//}
bool Rulers::canBeat(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    return compareCards(cardInHand, cardLastPlayer);
}

bool Rulers::canPlayCards(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    if(cardLastPlayer.size() == 0)
        return CARDTYPE_NONE != getCardtype(cardInHand);

    return canBeat(cardInHand, cardLastPlayer);
}
