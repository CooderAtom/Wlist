#include "wlist.h"
#include "ui_wlist.h"

#define SLIDE_ONCE 2

Wlist::Wlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wlist)
{
    ui->setupUi(this);

    slideArea = new listArea(this);
    slideArea->setGeometry(76,0,slideArea->width(),slideArea->width());

    connect(slideArea,SIGNAL(sig_areaSlide_Pos(int)),this,SLOT(slot_SlidePos_Proc(int)));
    connect(slideArea,SIGNAL(sig_areaBtn_clicked(unsigned char)),this,SLOT(slot_SetItem_Proc(unsigned char)));
    connect(this,SIGNAL(sig_Slide_Pos(int)),slideArea,SLOT(slot_areaSlide_Pos(int)));

    QString List[70] = {"abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC",
                       "abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC"
                        "abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC"
                        "abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC"
                        "abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC"
                        "abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC"
                        "abc","bcd","def","asdc","xcvzc","werfg","dfhvc","asetwet","zxcvsd","ARWEXC"
                       };
    this->list_SetList(List,13);
    ui->verticalSlider->setValue(0);
}

Wlist::~Wlist()
{
    delete ui;
}

void Wlist::list_SetList(QString List[], int Num)
{
    slideArea->list_SetList(List,Num);
    if(Num < 6)
    {
        ui->verticalSlider->hide();
        ui->BtnDown->hide();
        ui->BtnUp->hide();
    }
}

void Wlist::list_setSize(int width, int height)
{
    resize(width,height);
}

void Wlist::list_SetFocus(int focus)
{
    m_focus = focus;
    //add code
}

void Wlist::slot_SetItem_Proc(unsigned char itemID)
{
    emit sig_SelectItem(itemID);
}

void Wlist::slot_SlidePos_Proc(int pos)
{
    ui->verticalSlider->setValue(pos);
}

void Wlist::on_verticalSlider_valueChanged(int pos)
{
    emit sig_Slide_Pos(pos);
    qDebug("%d",pos);
    return;
}

void Wlist::on_BtnUp_clicked()
{
    int pos = ui->verticalSlider->value();
    pos -= SLIDE_ONCE;
    ui->verticalSlider->setValue(pos);
}

void Wlist::on_BtnDown_clicked()
{
    int pos = ui->verticalSlider->value();
    pos += SLIDE_ONCE;
    ui->verticalSlider->setValue(pos);
}

void Wlist::on_BtnUp_pressed()
{
    timer_Up = startTimer(10);
}

void Wlist::on_BtnUp_released()
{
    killTimer(timer_Up);
    timer_Up = 0;
}


void Wlist::on_BtnDown_pressed()
{
     timer_Down = startTimer(10);
}

void Wlist::on_BtnDown_released()
{
    killTimer(timer_Down);
    timer_Down = 0;
}

void Wlist::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timer_Up)
    {
        posInTimer = ui->verticalSlider->value();
        posInTimer -= 1;
        ui->verticalSlider->setValue(posInTimer);
    }
    else if(event->timerId() == timer_Down)
    {
        posInTimer = ui->verticalSlider->value();
        posInTimer += 1;
        ui->verticalSlider->setValue(posInTimer);
    }
}



