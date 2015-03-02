#include "listarea.h"
#include "ui_listarea.h"
#define SLIDE_SEC 40
#define SLIDE_PARA  0.2
listArea::listArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listArea)
{
    ui->setupUi(this);
}

listArea::~listArea()
{
    delete ui;
}

void listArea::slot_Btn_clicked(unsigned char num)
{
    emit sig_areaBtn_clicked(num);
}
void listArea::slot_Btn_released()
{
    if(item[0]->y() > 0)
    {
        slide_span = item[0]->y();
        slide_span = (int)((float) SLIDE_PARA * (float)slide_span);
        timer_returnStartUp = startTimer(SLIDE_SEC);
    }
    else if(num_All > 6 && (item[num_All - 1]->y() < MAX_HEIGHT - ITEM_HEIGHT))
    {
        slide_span = (MAX_HEIGHT - ITEM_HEIGHT) - (item[num_All - 1]->y());
        slide_span = (int)((float) SLIDE_PARA * (float)slide_span);
        timer_ReturnEndDown = startTimer(SLIDE_SEC);
    }
    else if(num_All <= 6 && item[0]->y() < 0)
    {
        slide_span = -item[0]->y();
        slide_span = (int)((float) SLIDE_PARA * (float)slide_span);
        timer_ReturnStartDown = startTimer(SLIDE_SEC);
    }
    killTimer(timer_Slide);
    timer_Slide = 0;
}

void listArea::slot_Btn_moving()
{
    QPoint aaa = cursor().pos();
    last_y = aaa.y();
    timer_Slide = startTimer(SLIDE_SEC);
}

void listArea::slot_areaSlide_Pos(int pos)
{
    int index;
    int startY = (int)(((float)pos / 100.0) * slide_height);
    startY = -startY;
    for(index = 0; index < num_All; index++)
    {
        item[index]->setGeometry(0,startY,item[index]->width(),item[index]->height());
        startY += 56;
    }
}

void listArea::list_SetList(QString List[], int Num)
{
    int index;
    height_all = 0;
    num_All = Num;
    for(index = 0; index < num_All; index++)
    {
        item[index] = new ListItem(this);
        item[index]->SetItemID((unsigned char)index);
        item[index]->setGeometry(0,height_all,item[index]->width(),item[index]->height());
        item[index]->SetItemText(List[index]);
        height_all += 56;
        connect(item[index],SIGNAL(sig_BtnItem_clicked(unsigned char)),this,SLOT(slot_Btn_clicked(unsigned char)));
        connect(item[index],SIGNAL(sig_BtnItem_moving()),this,SLOT(slot_Btn_moving()));
        connect(item[index],SIGNAL(sig_BtnItem_released()),this,SLOT(slot_Btn_released()));

    }
    slide_height = height_all - 336;
}

void listArea::list_SetFoucs(int foucs)
{
    m_foucs = foucs;
    item[m_foucs]->SetHighLight();
}

void listArea::timerEvent(QTimerEvent * event)
{
    QPoint aaa;
    int x,y,index;
    if(event->timerId() == timer_Slide)
    {
        aaa = cursor().pos();
        y = aaa.y() - last_y;
        last_y = aaa.y();
        for(index = 0; index < num_All; index++)
        {
            item[index]->setGeometry(item[index]->x(),item[index]->y() + y,item[index]->width(),item[index]->height());
        }
        slide_cury = -item[0]->y();
        if(slide_cury < 0)
        {
            slide_cury = 0;
        }
        x = (int)(((float)slide_cury / (float)slide_height) * 100);
        emit sig_areaSlide_Pos(x);
    }
    else if(event->timerId() == timer_returnStartUp)
    {
        if(item[0]->y() > 0)
        {
            if(item[0]->y() - slide_span < 0)
            {
                slide_span = item[0]->y();
            }
            for(index = 0; index < num_All; index++)
            {
                item[index]->setGeometry(item[index]->x(),item[index]->y() - slide_span,item[index]->width(),item[index]->height());
            }
        }
        else
        {
            killTimer(timer_returnStartUp);
            timer_returnStartUp = 0;
        }
    }
    else if(event->timerId() == timer_ReturnEndDown)
    {
        if(item[num_All - 1]->y() < MAX_HEIGHT - ITEM_HEIGHT)
        {
            if(item[num_All - 1]->y() + slide_span > (MAX_HEIGHT - ITEM_HEIGHT))
            {
                slide_span = (MAX_HEIGHT - ITEM_HEIGHT) - item[num_All - 1]->y();
            }
            for(index = 0; index < num_All; index++)
            {
                item[index]->setGeometry(item[index]->x(),item[index]->y() + slide_span,item[index]->width(),item[index]->height());
            }
        }
        else
        {
            killTimer(timer_ReturnEndDown);
            timer_ReturnEndDown = 0;
        }
    }
    else if(event->timerId() == timer_ReturnStartDown)
    {
        if(num_All <= 6 && item[0]->y() < 0)
        {
            if(item[0]->y() + slide_span > 0)
            {
                slide_span = -item[0]->y();
            }
            for(index = 0; index < num_All; index++)
            {
                item[index]->setGeometry(item[index]->x(),item[index]->y() + slide_span,item[index]->width(),item[index]->height());
            }
        }
        else
        {
            killTimer(timer_ReturnStartDown);
            timer_ReturnStartDown = 0;
        }
    }
}
