#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>

namespace Ui {
class ListItem;
}

typedef enum tabMoveStateEnum
{
    WLIST_STATE_MOVING = 0,
    WLIST_STATE_NOTMOVING,
}MoveStateEnum;

class ListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ListItem(QWidget *parent = 0);
    ~ListItem();

    void SetHighLight();
    void CancelHighLight();
    void SetItemText(QString text);
    void SetItemID(unsigned char num);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void sig_BtnItem_clicked(unsigned char num);
    void sig_BtnItem_moving();
    void sig_BtnItem_released();

private slots:
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_pushButton_clicked();

private:
    Ui::ListItem *ui;

    unsigned char itemID;
    MoveStateEnum m_MoveState;

    QPoint aaa;
    int press_y;
    int minusResult_y;
};

#endif // LISTITEM_H
