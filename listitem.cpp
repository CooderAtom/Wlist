#include "listitem.h"
#include "ui_listitem.h"

ListItem::ListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItem)
{
    ui->setupUi(this);

    m_MoveState = WLIST_STATE_NOTMOVING;
    ui->pushButton->installEventFilter(this);
}

ListItem::~ListItem()
{
    delete ui;
}

void ListItem::on_pushButton_pressed()
{
    aaa = cursor().pos();
    press_y = aaa.y();
}

void ListItem::on_pushButton_released()
{

}

void ListItem::on_pushButton_clicked()
{
    qDebug("itemID = %d",itemID);
    emit sig_BtnItem_clicked(itemID);
}

void ListItem::SetHighLight()
{

}

void ListItem::CancelHighLight()
{

}

void ListItem::SetItemText(QString text)
{
    ui->ItexText->setText(text);
}

void ListItem::SetItemID(unsigned char num)
{
    itemID = num;
}

bool ListItem::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->pushButton &&
            (e->type() == QEvent::MouseButtonPress ||
             e->type() == QEvent::MouseButtonRelease ||
             e->type() == QEvent::MouseMove))
    {
        if(m_MoveState == WLIST_STATE_NOTMOVING && e->type() == QEvent::MouseMove)
        {
            aaa = cursor().pos();
            minusResult_y = aaa.y() - press_y;
            if(minusResult_y < 5 && minusResult_y > -5)
            {
                return true;
            }
            emit sig_BtnItem_moving();
            on_pushButton_released();
            m_MoveState = WLIST_STATE_MOVING;
            return false;
        }
        else if(m_MoveState == WLIST_STATE_MOVING && e->type() == QEvent::MouseButtonRelease)
        {
            emit sig_BtnItem_released();
            m_MoveState = WLIST_STATE_NOTMOVING;
            return false;
        }
    }
    return QWidget::eventFilter(obj, e);
}
