#include "rulers.h"
#include <map>

int Rulers::get_card_type(QList<Card *> &cards)
{
	const int n = cards.count();
    if(n == 0)return CARDTYPE_NONE;
    if(n == 1)return SINGLE;
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
        if(cards.at(0)->m_point == cards.at(1)->m_point && cards.at(1)->m_point == cards.at(2)->m_point)
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
        if(is_straight(cards))return STRAIGHT;
    }
    else if(n == 6){
        if(is_straight(cards))return STRAIGHT;
        if(is_straight_pair(cards))return STRAIGHT_PAIR;
        if(is_plane(cards))return PLANE;
        if(is_four_with_two(cards))return FOUR_WITH_TWO;
    }
    else if(n == 7){
        if(is_straight(cards))return STRAIGHT;
    }
    else if(n == 8){

        if(is_straight(cards))return STRAIGHT;
        if(is_straight_pair(cards))return STRAIGHT;
        if(is_four_with_two_pair(cards))return FOUR_WITH_TWO_PAIR;
        if(is_plane_with_wing(cards))return PLANE_WITH_WING;

    }
    else if(n == 9){
        if(is_straight(cards))return STRAIGHT;
        if(is_plane(cards))return PLANE;
    }
    else if(n == 10){
        if(is_straight(cards))return STRAIGHT;
        if(is_straight_pair(cards))return STRAIGHT_PAIR;
        if(is_plane_with_wing(cards))return PLANE_WITH_WING;
    }

    else if(n == 11){
        if(is_straight(cards))return STRAIGHT;

    }
    else if(n == 12){
        if(is_straight(cards))return STRAIGHT;
        if(is_straight_pair(cards))return STRAIGHT_PAIR;
        if(is_plane(cards))return PLANE;
    }
    else if(n == 13){

    }
    else if(n == 14){
        if(is_straight(cards))return STRAIGHT;
    }
    return 0;
}

bool Rulers::is_straight(QList<Card *> &cards)
{
    // 牌数不足5
    //无2 小王大王
    //牌不能重复
    //第一张与最后一张 n-1
    const int n = cards.count();
    if(n < 5)return false;
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    std::map<int,int>map_point_to_count;
    for(const auto card : cards)
    {
        if(map_point_to_count.count(card->m_point)!=0)return false;
        else
            map_point_to_count[card->m_point] = 1;
    }
    if(cards.front()->m_point - cards.back()->m_point == n - 1) return true;
    return false;
}

bool Rulers::is_plane(QList<Card *> &cards)
{
    // 牌数不足6 必须是3倍数
    //无2 小王大王
    //每张牌出现次数为3
    //第一张-最后一张 = n/3 - 1
    const int n = cards.count();
    if(n < 6)return false;
    if(n % 3 != 0)return false;
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    std::map<int,int>map_point_to_count;
    for(const auto card : cards)
    {
        if(map_point_to_count.count(card->m_point)!=0)map_point_to_count[card->m_point] += 1;
        else
            map_point_to_count[card->m_point] = 1;
    }
    for(const std::pair<int, int> p:map_point_to_count){
        if(p.second != 3)return false;
    }
    if(cards.front()->m_point - cards.back()->m_point == n/3 - 1) return true;
    return false;
}

bool Rulers::is_plane_with_wing(QList<Card *> &cards)
{
    // 8张10张
    // 统计个数
    // 无2 小王大王
    // 判断3个是否连续
    // 8 单牌带2个 要不相等，要有两个数
    // 10 对子个数为2 要有两个数 不相等
    const int n = cards.size();
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    std::map<int,int>map_point_to_count;
    for(const auto card : cards)
    {
        if(map_point_to_count.count(card->m_point)!=0)map_point_to_count[card->m_point] += 1;
        else
            map_point_to_count[card->m_point] = 1;
    }
    if(n == 8)
    {
        int count = 0;
        std::vector<int> vec;
        // 遍历 map
        for(std::pair<int, int> p:map_point_to_count){
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
        std::vector<int> vec;
        // 遍历 map
        for(std::pair<int, int> p:map_point_to_count){
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

bool Rulers::is_four_with_two(QList<Card *> &cards)
{
    // 牌数不足6
    std::map<int,int>map_point_to_count;
    for(const auto card : cards)
    {
        if(map_point_to_count.count(card->m_point)!=0)map_point_to_count[card->m_point] += 1;
        else
            map_point_to_count[card->m_point] = 1;
    }
    int count = 0;
    for(const std::pair<int, int> p:map_point_to_count){
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

bool Rulers::is_four_with_two_pair(QList<Card *> &cards)
{
    std::map<int,int>map_point_to_count;
    for(const auto card : cards)
    {
        if(map_point_to_count.count(card->m_point)!=0)map_point_to_count[card->m_point] += 1;
        else
            map_point_to_count[card->m_point] = 1;
    }
    int count = 0;
    for(const std::pair<int, int> p:map_point_to_count){
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

bool Rulers::is_straight_pair(QList<Card *> &cards)
{
    // 牌数不足6 必须是偶数
    //无2 小王大王
    //每张牌出现次数为2
    //第一张-最后一张 = n/2 - 1
    const int n = cards.count();
    if(n < 6)return false;
    if(n % 2 != 0)return false;
    if(cards.at(0)->m_point == Card_2 || cards.at(0)->m_point == Card_SmallKing || cards.at(0)->m_point == Card_BigKing)
    {
        return false;
    }
    std::map<int,int>map_point_to_count;
    for(const auto card : cards)
    {
        if(map_point_to_count.count(card->m_point)!=0)map_point_to_count[card->m_point] += 1;
        else
            map_point_to_count[card->m_point] = 1;
    }
    for(const std::pair<int, int> p:map_point_to_count){
        if(p.second != 2)return false;
    }
    if(cards.front()->m_point - cards.back()->m_point == n/2 - 1) return true;
    return false;
}

bool Rulers::compare_cards(QList<Card *> &cards1, QList<Card *> &cards2)
{
	const int type1 = get_card_type(cards1);
	const int type2 = get_card_type(cards2);
    if(type1 == CARDTYPE_NONE)
        return false;
    if(type1 == type2 && cards1.size() == cards2.size())
    {
        return compare_same_type_cards(cards1, cards2,type1);
    }
    if(type1 == KINGBOMB)
        return true;
    if(type1 == BOMB && type2 != KINGBOMB)
        return true;
    return false;
}

bool Rulers::compare_same_type_cards(QList<Card *> &cards1, QList<Card *> &cards2, int type)
{
    int value1 = 0; int value2 = 0;
    switch (type) {
        case FOUR_WITH_TWO:
    {
        std::map<int, int> mapPointToCount1;
		std::map<int, int> mapPointToCount2;
        for(const auto card: cards1)
        {
            mapPointToCount1[card->m_point] += 1;
            if(mapPointToCount1[card->m_point] == 4)
            {
                value1 = card->m_point;
                break;
            }
        }
        for(const auto card: cards2)
        {
            mapPointToCount2[card->m_point] += 1;
            if(mapPointToCount2[card->m_point] == 4) value2 = card->m_point;
        }
        return value1 > value2;
    }
        case CARDTYPE_NONE:  // NOLINT(bug prone-branch-clone, bug prone-branch-clone)
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case SINGLE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case TRIPLE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
            case TRIPLE_WITH_ONE:
        {   std::map<int, int> mapPointToCount1;
        std::map<int, int> mapPointToCount2;
            for(const auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 3) value1 = card->m_point;
            }
            for(const auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 3) value2 = card->m_point;
            }
            return value1 > value2;
        }
        case TRIPLE_WITH_TWO:
        {   std::map<int, int> mapPointToCount1;
			std::map<int, int> mapPointToCount2;
            for(const auto card: cards1)
            {
            mapPointToCount1[card->m_point] += 1;
            if(mapPointToCount1[card->m_point] == 3) value1 = card->m_point;
            }
            for(const auto card: cards2)
            {
            mapPointToCount2[card->m_point] += 1;
            if(mapPointToCount2[card->m_point] == 3) value2 = card->m_point;
            }
            return value1 > value2;
        }
        case STRAIGHT_PAIR:  // NOLINT(bug prone-branch-clone)
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case STRAIGHT:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case PAIR:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case BOMB:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case FOUR_WITH_TWO_PAIR:
        {   std::map<int, int> mapPointToCount1;
			std::map<int, int> mapPointToCount2;
            for(const auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 4) value1 = card->m_point;
            }
            for(const auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 4) value2 = card->m_point;
            }
            return value1 > value2;
        }
        case PLANE:
            return cards1.at(0)->m_point > cards2.at(0)->m_point;
        case PLANE_WITH_WING:
        {   std::map<int, int> mapPointToCount1;
			std::map<int, int> mapPointToCount2;
            for(const auto card: cards1)
            {
                mapPointToCount1[card->m_point] += 1;
                if(mapPointToCount1[card->m_point] == 3)
                {
                    value1 = card->m_point;
                    break;
                }
            }
            for(const auto card: cards2)
            {
                mapPointToCount2[card->m_point] += 1;
                if(mapPointToCount2[card->m_point] == 3) value2 = card->m_point;
            }
            return value1 > value2;
        }
		default: ;
    }
    return false;
}

bool Rulers::can_beat(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    return compare_cards(cardInHand, cardLastPlayer);
}

bool Rulers::can_play_cards(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    if(cardLastPlayer.empty())
        return CARDTYPE_NONE != get_card_type(cardInHand);

    return can_beat(cardInHand, cardLastPlayer);
}
