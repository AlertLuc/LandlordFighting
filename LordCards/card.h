#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

namespace Ui {
class Card;
}
#define CardPoint_Begin Card_3

// 牌点数枚举
enum CardPoint
{
    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,
    Card_SmallKing,
    Card_BigKing,
    CardPoint_End

};

// 花色枚举
#define CardSuit_Begin Diamond
enum CardSuit
{
    Diamond,///♦
    Club,///♣
    Heart,/// ♥
    Spade,///♠
    Suit_SamllKing,
    Suit_BigKing,
    CardSuit_End
};

// 画图尺寸
#define Card_Width (80)
#define Card_Height (105)

// 点击上移
#define CARD_UP_DISTANCE (20)

// 牌的时隔举例
#define CARD_SHOW_WIDTH (25)

class Card : public QWidget
{
    Q_OBJECT

public:
    explicit Card(int point, int suit,QWidget *parent = nullptr);

    // 数字初始化牌
    // 按照3-k A 2 花色*4
    explicit Card(int number, QWidget *parent = nullptr);

    ~Card();

    // 设置是否选择
    void setSelected();
    void setUnSelected();

    // 设置鼠标点击
    void mousePressEvent(QMouseEvent *event);

    // 设置正反面
    void setCardPositive(bool flag);

    // 牌上移
    void slot_moveUp();

private:
    Ui::Card *ui;
    void init(int point, int suit);

    // 用来存总图片， 不用每次都绘制加载
    static QImage m_img;

    // 绘制 重绘事件
    void paintEvent(QPaintEvent *event);

public:
    // 是否点击
    bool m_isClicked = false;

    // 正反面
    bool m_isPositive = false;

    // 花色
    int m_suit;

    // 点数
    int m_point;
};

#endif // CARD_H
