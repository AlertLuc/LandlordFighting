#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include <QDialog>
#include "cardlist.h"
#include "QTimer"
#include"PlayRound.h"
#include<QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class main_dialog : public QDialog
{
    Q_OBJECT
public:
    main_dialog(QWidget *parent = nullptr);

    ~main_dialog();
private slots:
    void on_pb_start_clicked();

    void on_pb_next_clicked() const;

    void on_pb_end_clicked() const;

    void on_pb_helpPlayCard_clicked();

    // 设置背景
    void slot_set_back_ground();

    void on_pb_text_clicked() const;

    void slot_start_one_game();

    void slot_refreshAllCardList();

    void on_pb_playCard_clicked();

    void slot_delete_all_player_cards();

    void slot_delete_player_out_card(int player);

    void slot_show_play_cards(bool flag) const;

    void slot_showCallLord(bool flag) const;

    void on_pb_pass_clicked();

    void slot_hideAllPass();

    void slot_hide_all_call_lord();

    void slot_hide_all_no_call();

    void slot_hide_all_clock();

    void slot_show_all_cards_count();

    void slot_hide_all_card_count();

    void on_pb_callLord_clicked();

    void on_pb_noCall_clicked();

    void slot_lordAddLordCards(int player);

private:
    Ui::MainDialog *ui;
    CardList m_cardList[CARDLIST_TYPE_COUNT];
    //QList<Card*> m_cardLastPlayer;回合管理

    QLabel* m_lbIconArray[3];

    QLabel* m_lbCallLordArray[3];

    QLabel* m_lbNoCallArray[3];

    QLabel* m_lbClockArray[3];

    QLabel* m_lbTimerArray[3];

    QLabel* m_lbCardCountArray[3];


    PlayRound m_playround_;

    QTimer m_refreshTime;

    friend class PlayRound;

    QLabel* m_lbPassArr[3]{};
};
#endif // MAINDIALOG_H
