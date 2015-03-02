#ifndef LISTAREA_H
#define LISTAREA_H

#include <QWidget>
#include <QPoint>
#include <QList>
#include "listitem.h"
#include <QMouseEvent>

#define MAX_HEIGHT 350
#define ITEM_HEIGHT 56
namespace Ui {
class listArea;
}

class listArea : public QWidget
{
    Q_OBJECT

public:
    explicit listArea(QWidget *parent = 0);
    ~listArea();

    void list_SetList(QString List[], int Num);
    void list_SetFoucs(int foucs);

public slots:
    void slot_areaSlide_Pos(int pos);

protected:
    virtual void timerEvent(QTimerEvent * event);

private slots:
    void slot_Btn_clicked(unsigned char num);
    void slot_Btn_moving();
    void slot_Btn_released();
    //void slide_ReturnUp();
    //void slide_returnDown();

signals:
    void sig_areaBtn_clicked(unsigned char);
    void sig_areaSlide_Pos(int pos);

private:
    Ui::listArea *ui;

    QList<QWidget *> lineEdit;
    ListItem *item[256];

    int timer_Slide;
    int timer_returnStartUp;
    int timer_ReturnEndDown;
    int timer_ReturnStartDown;

    int num_All;
    int last_y;
    int height_all;
    int slide_height;
    int slide_cury;
    int slide_span;

    int m_foucs;
};

#endif // LISTAREA_H
