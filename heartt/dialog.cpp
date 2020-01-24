#include "dialog.h"
#include "ui_dialog.h"
#include "QPainter"
#include "math.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter qp(this);

    qp.setPen(Qt::red);
    qp.translate(rect().width()/2,rect().height()/2);

    double x;
    int r=(rect().width()>rect().height()?rect().height():rect().width())/3;

    for(x=-1.0;x<=1.0;x+=0.001)
    {
        double y1,y2;
        y1=pow(x*x,1.0/3)+pow(1-x*x,0.5);
         y2=pow(x*x,1.0/3)-pow(1-x*x,0.5);

         qp.drawLine(x*r,-y1*r,x*r,-y2*r);

    }
}
