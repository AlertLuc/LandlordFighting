#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include <QDialog>
#include "cardlist.h"
#include "QTimer"
#include"cardround.h"
#include<QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT
public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();
private slots:
    void on_pb_start_clicked();
    void on_pb_next_clicked();
    void on_pb_end_clicked();

    // 设置背景
    void slot_setBackGroud();
    void on_pb_text_clicked();
    void slot_startOneGamg();
    void slot_refreshAllCardList();
    void on_pb_playCard_clicked();
    void slot_delectAllPlayerCards();
    void slot_delectPlayerOutCard(int player);
    void slot_showPlayCards(bool flag);
    void slot_showCallLord(bool flag);
    void on_pb_pass_clicked();

    void slot_hideAllPass();

    void on_pb_callLord_clicked();

    void on_pb_noCall_clicked();

    void slot_lordAddLordCards(int player);

private:
    Ui::MainDialog *ui;
    CardList m_cardList[CARDLIST_TYPE_COUNT];
    //QList<Card*> m_cardLastPlayer;回合管理
    Cardround m_playround;
    QTimer m_refreshTime;
    friend class Cardround;

    QLabel* m_lbPassArr[3];
};
#endif // MAINDIALOG_H
