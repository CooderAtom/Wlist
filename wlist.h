#ifndef WLIST_H
#define WLIST_H

#include <QWidget>
#include "listarea.h"

namespace Ui {
class Wlist;
}

class Wlist : public QWidget
{
    Q_OBJECT

public:
    explicit Wlist(QWidget *parent = 0);
    ~Wlist();

    void list_SetList(QString List[],int Num);
    void list_SetFocus(int focus);
    void list_setSize(int width,int height);
protected:
    virtual void timerEvent(QTimerEvent * event);

private slots:
    void slot_SetItem_Proc(unsigned char itemID);
    void slot_SlidePos_Proc(int pos);
    void on_verticalSlider_valueChanged(int pos);

    void on_BtnUp_clicked();

    void on_BtnDown_clicked();

    void on_BtnUp_pressed();

    void on_BtnUp_released();

    void on_BtnDown_pressed();

    void on_BtnDown_released();

signals:
    void sig_SelectItem(int);
    void sig_Slide_Pos(int pos);
private:
    Ui::Wlist *ui;

    listArea *slideArea;

    int timer_Up;
    int timer_Down;
    int posInTimer;
    int m_focus;
};

#endif // WLIST_H
