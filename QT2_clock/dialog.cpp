#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include<QTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    state = 0;
    nMSCnt = 0;
    idx = 0;
    sTime = QTime::currentTime();

    QTimer *timer = new QTimer(this);
    connect(timer , SIGNAL(timeout()), this, SLOT(mytimer()));
    timer->start(10);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::mytimer()
{
    if(state == 1){
        update();
    }
}


void Dialog::paintEvent(QPaintEvent *)
{
    QRect rc = rect();
    int size = rc.width() > rc.height() ? rc.height() : rc.width();

    QPainter qp(this);
    qp.setFont(QFont("Arial", size / 6));
    qp.setPen(Qt::black);

    QString str;
    int nms;
    if(state > 0){
        if(state == 1)
            nms = (sTime.msecsTo(QTime::currentTime()) + nMSCnt) / 10;
        else
            nms = nMSCnt / 10;
        str.sprintf("%02d:%02d.%02d", nms / 6000, (nms / 100) % 60, nms %100);
    }
    else{
        str = "00:00:00";
    }
    if (lstCnt.empty())
    qp.drawText(rect(), Qt::AlignCenter, str);
    else
    {
        qp.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, str);
        qp.setPen(Qt::gray);
        qp.setFont(QFont("Arial", size / 10));
        QRect t = rect();
        t.translate(0, size / 6 + size / 20);
        nms -= lstCnt.last() / 10;
         str.sprintf("%02d:%02d.%02d", nms / 6000, (nms / 100) % 60, nms %100);
         qp.drawText(t, Qt::AlignTop | Qt::AlignHCenter, str);

         qp.setFont(QFont("Arial", size / 15));
         qp.setPen(Qt::darkBlue);
         t.translate(0, size / 6);
         int i = idx, j;
         if( i>= lstCnt.size())
             i = lstCnt.size() - 1;
         j = i-4;

         for(; i>=0 && i>j; --i){
             nms = lstCnt[i] / 10;
             int nnms;
             if(i>0)
                 nnms = (lstCnt[i] - lstCnt[i - 1]) / 10;
             str.sprintf("%02d           %02d:%02d.%02d       %02d:%02d.%02d",
                         i + 1, nms / 6000, (nms / 100) % 60, nms % 100,
                         nnms / 6000, (nnms/100) %60, nnms % 100);
             qp.drawText(t, Qt::AlignTop | Qt::AlignHCenter , str);
             t.translate(0, size / 10);
         }
    }

    qp.setFont(QFont("Arial", size / 15));
    qp.setPen(Qt::red);
    int hh = size / 10;
    rcLeft = QRect(rc.left(), rc.bottom() - hh * 2, rc.width() / 2, hh);
    rcRight = QRect(rc.width() / 2, rc.bottom() - hh * 2, rc.width() / 2, hh);
    rcBottom = QRect(rc.left(), rc.bottom() - hh * 2, rc.width(), hh);

    switch (state){
    default:
        qp.drawText(rcBottom, Qt::AlignCenter, "开始");
        break;
    case 1:
         qp.drawText(rcLeft, Qt::AlignCenter, "暂停");
         qp.setPen(Qt::blue);
         qp.drawText(rcRight, Qt::AlignCenter, "计次");
        break;
    case 2:
        qp.drawText(rcLeft, Qt::AlignCenter, "继续");
        qp.setPen(Qt::blue);
        qp.drawText(rcRight, Qt::AlignCenter, "重置");
        break;
    }
}

void Dialog::mousePressEvent(QMouseEvent *e)
{
    if(Qt::LeftButton == e->button()) {
        switch (state){
        default:
            if( rcBottom.contains(e->pos())) {
                nMSCnt = 0;
                sTime = QTime::currentTime();
                state = 1;
            }
            break;
        case 1 :
            if(rcLeft.contains(e->pos())){
                state = 2;
                nMSCnt += sTime.msecsTo(QTime::currentTime());
                update();
            }
            else  if(rcRight.contains(e->pos())){
                lstCnt.append(nMSCnt + sTime.msecsTo(QTime::currentTime()));
                idx = lstCnt.size() - 1;
                update();

            }
            break;
        case 2:
            if (rcLeft.contains(e->pos())){
                state = 1;
                sTime = QTime::currentTime();
            }
            else if(rcRight.contains(e->pos())){
                state = 0;
                nMSCnt = 0;
                lstCnt.clear();
                update();
            }
            break;
        }
    }
}


void Dialog::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0) {
        if(idx < lstCnt.size() - 1){
            ++idx;
            update();
        }
       }
        else {
            if(idx > 0){
                --idx;
                update();
            }
        }

}
