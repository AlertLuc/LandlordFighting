#include "maindialog.h"
#include "ui_maindialog.h"
#include "QPalette"
#include "cardlist.h"
#include "QDebug"
#include <synchapi.h>
#include "cardsound.h"
#include<QDateTime>
main_dialog::main_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog),m_playround_(this, parent)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    this->setWindowTitle("斗地主");

    ui->sw_page->setCurrentIndex(0);

    slot_set_back_ground();

    // 随机种子
    qsrand(QDateTime::currentSecsSinceEpoch());  // NOLINT(clang-diagnostic-shorten-64-to-32)

    for(int i = 0; i< CARDLIST_TYPE_COUNT; ++i)
    {
        m_cardList[i].setCardListType(i);
    }

    connect(&m_refreshTime, SIGNAL(timeout()), this, SLOT(slot_refreshAllCardList()));


    CardSound::playBGM();
    m_lbPassArr[CARDLIST_LEFTPLAYER] = ui->lb_leftPess;
    m_lbPassArr[CARDLIST_MIDPLAYER] = ui->lb_midPess;
    m_lbPassArr[CARDLIST_RIGHTPLAYER] = ui->lb_rightPess;

    m_lbIconArray[CARDLIST_LEFTPLAYER] = ui->lb_leftplayericon;
    m_lbIconArray[CARDLIST_MIDPLAYER] = ui->lb_midplayericon;
    m_lbIconArray[CARDLIST_RIGHTPLAYER] = ui->lb_rightplayericon;

    m_lbCallLordArray[CARDLIST_LEFTPLAYER] = ui->lb_leftCallLord;
    m_lbCallLordArray[CARDLIST_MIDPLAYER] = ui->lb_midCallLord;
    m_lbCallLordArray[CARDLIST_RIGHTPLAYER] = ui->lb_rightCallLord;

    m_lbNoCallArray[CARDLIST_LEFTPLAYER] = ui->lb_leftNoCall;
    m_lbNoCallArray[CARDLIST_MIDPLAYER] = ui->lb_midNoCall;
    m_lbNoCallArray[CARDLIST_RIGHTPLAYER] = ui->lb_rightNoCall;

	m_lbCardCountArray[CARDLIST_LEFTPLAYER] = ui->lb_leftCardCount;
	m_lbCardCountArray[CARDLIST_MIDPLAYER] = ui->lb_midCardCount;
	m_lbCardCountArray[CARDLIST_RIGHTPLAYER] = ui->lb_rightCardCount;

	m_lbClockArray[CARDLIST_LEFTPLAYER] = ui->lb_leftClock;
    m_lbClockArray[CARDLIST_MIDPLAYER] = ui->lb_midClock;
    m_lbClockArray[CARDLIST_RIGHTPLAYER] = ui->lb_rightClock;

    m_lbTimerArray[CARDLIST_LEFTPLAYER] = ui->lb_leftTimer;
    m_lbTimerArray[CARDLIST_MIDPLAYER] = ui->lb_midTimer;
    m_lbTimerArray[CARDLIST_RIGHTPLAYER] = ui->lb_rightTimer;
    
}

main_dialog::~main_dialog()
{
    delete ui;
}

// 点击快速开始
void main_dialog::on_pb_start_clicked()
{
    ui->sw_page->setCurrentIndex(1);

    slot_start_one_game();
}

// 点击下一局
void main_dialog::on_pb_next_clicked() 
{
    on_pb_start_clicked();
}

// 回到主页
void main_dialog::on_pb_end_clicked() 
{
    ui->sw_page->setCurrentIndex(0);
}

void main_dialog::on_pb_text_clicked() 
{
    m_playround_.m_isStop = true;
    m_playround_.slot_close_all_timer();
    ui->sw_page->setCurrentIndex(0);
}

void main_dialog::slot_start_one_game()
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
    m_refreshTime.stop();
    m_playround_.initRound();

    slot_clear_cards();

    slot_hideAllPass();

    // 出牌叫地主隐藏
    slot_hide_all_call_lord();

    slot_hide_all_no_call();
    
    slot_hide_all_clock();

    slot_showCallLord(false);

    slot_show_play_cards(false);

    for(int i = 0; i < 54; ++i)
    {
        Card* card = new Card(i, this->ui->page_game);
        card->setCardPositive(false);
        m_cardList[CARDLIST_WHOLE].addCard(card);

        m_card_total.append(card);
    }

    // 洗牌
    m_cardList[CARDLIST_WHOLE].shuffle();
    m_refreshTime.start(1000/10);
	QSound sound(":/sound/xipai.wav");
    sound.play();
    qDebug()<<"总牌数";
    m_cardList[CARDLIST_WHOLE].PrintCard();

    if (m_playround_.m_isStop)return;
    Sleep(1000);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    slot_refreshAllCardList();

    //发牌动画
    for(int i = 0; i < 3; ++i)
    {
        Card* card = m_cardList[CARDLIST_WHOLE].SelectOneCard();
        card->setCardPositive(false);
        m_cardList[CARDLIST_LORD].addCard(card);
    }

    //玩家手牌顺序
    for (int i = 0; i < 54 - 3; ++i)
    {
        if (m_playround_.m_isStop)return;

        Sleep(50);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        Card* card = m_cardList[CARDLIST_WHOLE].SelectOneCard();
        if (i % 3 == 0)
        {
            m_cardList[CARDLIST_LEFTPLAYER].addCard(card);
        }
        else if (i % 3 == 1)
        {
            m_cardList[CARDLIST_MIDPLAYER].addCard(card);
        }
        else
        {
            m_cardList[CARDLIST_RIGHTPLAYER].addCard(card);
        }
    }

    if (m_playround_.m_isStop)return;
    Sleep(1000);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    slot_refreshAllCardList();

    m_cardList[CARDLIST_WHOLE].SortCard();

    m_playround_.decideBeginLord();
}

void main_dialog::slot_refreshAllCardList()
{
    for (int i = 0; i < CARDLIST_TYPE_COUNT; ++i )
    {
        m_cardList[i].ShowCard();
    }

    for(int i = 0; i < 3; ++i)
    {
        QString txt = QString::number(m_cardList[i].m_cardList.size());
        m_lbCardCountArray[i]->setText(txt);
    }
}

// 添加背景
void main_dialog::slot_set_back_ground()
{
    // 调色板
    QPalette p = this->palette();

    // 设置画刷 设置图片
    const QPixmap pixmap(":/image/bk.png");
    // ReSharper disable once CppDeprecatedEntity
    p.setBrush(QPalette::Background, QBrush(pixmap));

    // 设置调色板
    this->setPalette(p);
}

void main_dialog::on_pb_playCard_clicked()
{
    // 选择出牌
    m_playround_.slot_midPlayerPlayCards();
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

void main_dialog::slot_delete_all_player_cards()
{
    for(int i = CARDLIST_LEFTPLAYER; i < 3; i++)
    {
        while(!m_cardList[i + CARDLIST_LEFTPLAYER_OUTCARD].m_cardList.empty())
        {
            Card* card = m_cardList[i+CARDLIST_LEFTPLAYER_OUTCARD].SelectOneCard();
            card->hide();
        }
    }
}

void main_dialog::slot_delete_player_out_card(int player)
{
	const int playerOutCard = player + CARDLIST_LEFTPLAYER_OUTCARD;
    while(!m_cardList[playerOutCard].m_cardList.empty())
    {
        Card* card = m_cardList[playerOutCard].SelectOneCard();
        card->hide();
    }
}

void main_dialog::slot_show_play_cards(bool flag) 
{
    if(flag)
    {
        ui->wdg_palyCards->show();
    }
    else{
        ui->wdg_palyCards->hide();
    }
}

void main_dialog::slot_showCallLord(bool flag) 
{
    if(flag)
    {
        ui->wdg_callLord->show();
    }
    else{
        ui->wdg_callLord->hide();
    }
}

void main_dialog::on_pb_pass_clicked()
{
    m_playround_.slot_midPlayerPass();
}

void main_dialog::slot_hideAllPass()
{
    for(QLabel* lb : m_lbPassArr)
    {
        lb->hide();
    }
}

void main_dialog::slot_hide_all_call_lord()
{
    for (QLabel* lb : m_lbCallLordArray)
    {
        lb->hide();
    }
}

void main_dialog::slot_hide_all_no_call()
{
    for (QLabel* lb : m_lbNoCallArray)
    {
        lb->hide();
    }
}

void main_dialog::slot_hide_all_clock()
{
    for (QLabel* lb : m_lbClockArray)
    {
        lb->hide();
    }
    for (QLabel* lb : m_lbTimerArray)
    {
        lb->hide();
    }
}

void main_dialog::slot_show_all_cards_count()
{
    for (QLabel* lb : m_lbClockArray)
    {
        lb->show();
    }
}

void main_dialog::slot_hide_all_card_count()
{
    for (QLabel* lb : m_lbCardCountArray)
    {
        lb->hide();
    }
}

void main_dialog::on_pb_callLord_clicked()
{
    m_playround_.slot_midPlayerCallLord();
}

void main_dialog::on_pb_noCall_clicked()
{
    m_playround_.slot_midPlayerNoCall();
}

void main_dialog::on_pb_helpPlayCard_clicked()
{
    m_playround_.slot_computer_help();
}

void main_dialog::slot_lordAddLordCards(int player)
{
    for(const Card* card : m_cardList[CARDLIST_LORD].m_cardList)
    {
        Card* newCard = new Card(card->m_point,card->m_suit,this->ui->page_game);
        m_cardList[player].addCard(newCard);
        m_card_total.append(newCard);
    }
    m_cardList[player].SortCard();
    for(Card* card : m_cardList[CARDLIST_LORD].m_cardList)
    {
        card->setCardPositive(true);
    }
}

void main_dialog::slot_show_win_page()
{
    ui->sw_page->setCurrentIndex(2);
}

void main_dialog::slot_show_result(bool flag)
{
    if(flag)
    {
        ui->label->setText("恭喜！\n你赢了");
    }
    else
    {
        ui->label->setText("你输了");
    }
}

void main_dialog::slot_clear_cards()
{
    for(int i = 0 ; i < CARDLIST_TYPE_COUNT; ++i)
    {
        m_cardList[i].m_cardList.clear();
    }
    for(Card* card:m_card_total)
    {
        card->hide();
        card->deleteLater();
    }
    m_card_total.clear();
}

