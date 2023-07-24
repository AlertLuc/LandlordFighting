#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "cardlist.h"
#include "QTimer"

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

private:
    Ui::MainDialog *ui;

    CardList m_cardList[CARDLIST_TYPE_COUNT];

    QList<Card*> m_cardLastPlayer;

    QTimer m_refreshTime;
};
#endif // MAINDIALOG_H
