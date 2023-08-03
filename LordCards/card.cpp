#include "card.h"
#include "ui_card.h"
#include "QPainter"

QImage Card::m_img = QImage("./image/card.png");

Card::Card(int point, int suit, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
    init(point, suit);
}


Card::Card(int number, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);

    if(number == 52)
    {
        init(Card_SmallKing, Suit_SamllKing);
    }
    else if(number== 53)
    {
        init(Card_BigKing, Suit_BigKing);
    }
    else
    {
        init(number % 13, number / 13);
    }
}

Card::~Card()
{
    delete ui;
}

void Card::setSelected()
{
    m_isClicked = true;
}

void Card::setUnSelected()
{
    m_isClicked = false;
}

void Card::mousePressEvent(QMouseEvent *event)
{
    m_isClicked = !m_isClicked;
}

void Card::setCardPositive(bool flag)
{
    m_isPositive = flag;
}

void Card::slot_moveUp()
{
    QRect rect = this->geometry();
    int x = rect.x();
    int y = rect.y() - CARD_UP_DISTANCE;
    this->move(x,y);
}

// 初始化
void Card::init(int point, int suit)
{
    m_point = point;
    m_suit = suit;
    m_isPositive = false;
    m_isClicked = false;
}

// 绘图事件
void Card::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    int x = 0;
    int y = 0;
    if(m_isPositive)
    {
        if(m_point == Card_SmallKing)
        {
            x = 0; y = 4;
        }
        else if(m_point == Card_BigKing)
        {
            x = 1; y = 4;
        }
        else
        {
            x = m_point;y = m_suit;
        }
    }
    else
    {
        x = 2;
        y = 4;
    }
    paint.drawImage(0, 0, m_img, x*Card_Width, y*Card_Height, Card_Width, Card_Height);
    paint.end();
}
