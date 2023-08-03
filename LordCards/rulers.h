#ifndef RULERS_H
#define RULERS_H
#include <cardlist.h>
enum CARD_TYPE{
    CARDTYPE_NONE,//啥也不是
    SINGLE,//单张
    PAIR,//对子
    TRIPLE,//三张
    TRIPLE_WITH_ONE,//三带一
    TRIPLE_WITH_TWO,//三带二
    STRAIGHT,//顺子
    STRAIGHT_PAIR,//连对
    PLANE,//飞机
    PLANE_WITH_WING,//飞机带翅膀
    FOUR_WITH_TWO,//四带两对
    FOUR_WITH_TWO_PAIR,//四带二
    BOMB,//炸弹
    KINGBOMB,//王炸
};
class Rulers
{
public:
    // 获得牌型
    static int get_card_type(QList<Card*> &cards);

    //是不是顺子
    static bool is_straight(QList<Card*> &cards);

    //飞机
    static bool is_plane(QList<Card*> &cards);

    //飞机带翅膀
    static bool is_plane_with_wing(QList<Card*> &cards);

    //四带二
    static bool is_four_with_two(QList<Card*> &cards);

    //四带两对
    static bool is_four_with_two_pair(QList<Card*> &cards);

    //连对
    static bool is_straight_pair(QList<Card*> &cards);

    //比较谁牌组大
    static bool compare_cards(QList<Card*>&cards1, QList<Card*>&cards2);

    //相同类型 比较谁牌组大
    static bool compare_same_type_cards(QList<Card*>&cards1, QList<Card*>&cards2, int type);

    //是否可以管上
    static bool can_beat(QList<Card*> &cardInHand, QList<Card*> &cardLastPlayer);

    //是否能出牌
    static bool can_play_cards(QList<Card*> &cardInHand, QList<Card*> &cardLastPlayer);

    friend class main_dialog;
};
#endif // RULERS_H
