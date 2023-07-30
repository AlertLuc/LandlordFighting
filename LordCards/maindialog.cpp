#include "maindialog.h"
#include "ui_maindialog.h"
#include "QPalette"
#include "cardlist.h"
#include "QDebug"
#include <synchapi.h>
#include "cardsound.h"
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog),m_playround(this, parent)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    this->setWindowTitle("斗地主");

    ui->sw_page->setCurrentIndex(0);

    slot_setBackGroud();

    for(int i = 0; i< CARDLIST_TYPE_COUNT; ++i)
    {
        m_cardList[i].setCardListType(i);
    }

    connect(&m_refreshTime, SIGNAL(timeout()), this, SLOT(slot_refreshAllCardList()));


    CardSound::playBGM();
    m_lbPassArr[CARDLIST_LEFTPLAYER] = ui->lb_leftPess;
    m_lbPassArr[CARDLIST_MIDPLAYER] = ui->lb_midPess;
    m_lbPassArr[CARDLIST_RIGHTPLAYER] = ui->lb_rightPess;
}

MainDialog::~MainDialog()
{
    delete ui;
}

// 点击快速开始
void MainDialog::on_pb_start_clicked()
{
    ui->sw_page->setCurrentIndex(1);

    slot_startOneGamg();
}

// 点击下一局
void MainDialog::on_pb_next_clicked()
{
    ui->sw_page->setCurrentIndex(1);
}

// 回到主页
void MainDialog::on_pb_end_clicked()
{
    ui->sw_page->setCurrentIndex(0);
}

void MainDialog::on_pb_text_clicked()
{
    ui->sw_page->setCurrentIndex(2);
}

void MainDialog::slot_startOneGamg()
{
//    int beginx = 150;
//    int beginy = 100;

//    for(int i = 0; i < 54; ++i)
//    {
//        //创建牌
//        Card *card = new Card(i, this->ui->page_game);

//        //设置
//        card->setCardPositive(true);
//        card->move(beginx + (i) % 13 * CARD_SHOW_WIDTH, beginy + (i) / 13 * Card_Height);

//        //显示牌
//        card->show();
//    }
    slot_hideAllPass();
    // 出牌叫地主隐藏
    slot_showCallLord(false);
    slot_showPlayCards(false);
    for(int i = 0; i < 54; ++i)
    {
        Card* card = new Card(i, this->ui->page_game);
        card->setCardPositive(false);
        m_cardList[CARDLIST_WHOLE].addCard(card);
    }
    // 洗牌
    m_cardList[CARDLIST_WHOLE].shuffle();

    m_refreshTime.start(1000/10);

//    m_cardList[CARDLIST_WHOLE].ShowCard();

    qDebug()<<"总牌数";
    m_cardList[CARDLIST_WHOLE].PrintCard();

    Sleep(1000);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    slot_refreshAllCardList();

    QSound sound(":/sound/xipai.wav");
    sound.play();
    //发牌动画
    for(int i = 0; i < 3; ++i)
    {
        Card* card = m_cardList[CARDLIST_WHOLE].SelectOneCard();
        m_cardList[CARDLIST_LORD].addCard(card);
    }

    Sleep(1000);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    slot_refreshAllCardList();

    m_cardList[CARDLIST_WHOLE].SortCard();

    //玩家手牌顺序
    for(int i = 0; i < 54 - 3; ++i)
    {
        Sleep(50);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        Card* card = m_cardList[CARDLIST_WHOLE].SelectOneCard();
        if(i%3 == 0)
        {
            m_cardList[CARDLIST_LEFTPLAYER].addCard(card);
        }
        else if(i%3 == 1)
        {
            m_cardList[CARDLIST_MIDPLAYER].addCard(card);
        }
        else
        {
            m_cardList[CARDLIST_RIGHTPLAYER].addCard(card);
        }
    }

    qDebug()<<"";
    m_cardList[CARDLIST_LEFTPLAYER].PrintCard();

    qDebug()<<"";
    m_cardList[CARDLIST_MIDPLAYER].PrintCard();

    qDebug()<<"";
    m_cardList[CARDLIST_RIGHTPLAYER].PrintCard();

    sound.stop();
    // 排序
//    m_cardList[CARDLIST_LEFTPLAYER].SortCard();
//    m_cardList[CARDLIST_MIDPLAYER].SortCard();
//    m_cardList[CARDLIST_RIGHTPLAYER].SortCard();
    m_playround.startRound(CARDLIST_LEFTPLAYER);

}

void MainDialog::slot_refreshAllCardList()
{
    for(int i = 0; i < CARDLIST_TYPE_COUNT; ++i)
    {
        m_cardList[i].ShowCard();
    }
}

// 添加背景
void MainDialog::slot_setBackGroud()
{
    // 调色板
    QPalette p = this->palette();

    // 设置画刷 设置图片
    QPixmap pixmap(":/image/bk.png");
    p.setBrush(QPalette::Background, QBrush(pixmap));

    // 设置调色板
    this->setPalette(p);
}



void MainDialog::on_pb_playCard_clicked()
{
    // 选择出牌
    m_playround.slot_midPlayerPlayCards();
    // 清除

    // 判断是否符号规则
//    QList<Card*> lst = m_cardList[CARDLIST_MIDPLAYER].SelectCardList();
//    if(Rulers::canPlayCards(lst, m_playround.lastPlayerCards)){
//        // 获得选中添加玩家外面手牌
//        // 删除选中
//        CardSound::playCardSound(lst);
//        m_cardList[CARDLIST_MIDPLAYER_OUTCARD].addCard(lst);
//        // 玩家手牌外面显示
//        m_cardList[CARDLIST_MIDPLAYER].DeleteCardList();
//    }
}

void MainDialog::slot_delectAllPlayerCards()
{
    for(int i = CARDLIST_LEFTPLAYER; i < 3; i++)
    {
        while(m_cardList[i+CARDLIST_LEFTPLAYER_OUTCARD].m_cardlist.size() != 0)
        {
            Card* card = m_cardList[i+CARDLIST_LEFTPLAYER_OUTCARD].SelectOneCard();
            card->hide();
        }
    }
}

void MainDialog::slot_delectPlayerOutCard(int player)
{
    int playerOutCard = player + CARDLIST_LEFTPLAYER_OUTCARD;
    while(m_cardList[playerOutCard].m_cardlist.size() != 0)
    {
        Card* card = m_cardList[playerOutCard].SelectOneCard();
        card->hide();
    }
}

void MainDialog::slot_showPlayCards(bool flag)
{
    if(flag)
    {
        ui->wdg_palyCards->show();

    }
    else{
        ui->wdg_palyCards->hide();
    }
}

void MainDialog::slot_showCallLord(bool flag)
{
    if(flag)
    {
        ui->wdg_callLord->show();

    }
    else{
        ui->wdg_callLord->hide();
    }
}


void MainDialog::on_pb_pass_clicked()
{
    m_playround.slot_midPlayerPass();
}

void MainDialog::slot_hideAllPass()
{
    for(QLabel* lb : m_lbPassArr)
    {
        lb->hide();
    }
}

