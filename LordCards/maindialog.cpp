#include "maindialog.h"
#include "ui_maindialog.h"
#include "QPalette"
#include "card.h"
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    // 最大与最小化
    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    // 标题
    this->setWindowTitle("斗地主");

    ui->sw_page->setCurrentIndex(0);

    slot_setBackGroud();
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
    int beginx = 150;
    int beginy = 100;

    for(int i = 0; i < 54; ++i)
    {
        //创建牌
        Card *card = new Card(i, this->ui->page_game);

        //设置
        card->setCardPositive(true);
        card->move(beginx + (i) % 13 * CARD_SHOW_WIDTH, beginy + (i) / 13 * Card_Height);

        //显示牌
        card->show();
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


