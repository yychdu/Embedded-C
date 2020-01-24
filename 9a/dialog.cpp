#include "dialog.h"
#include "ui_dialog.h"
#include<qpainter.h>
#include<qtimer.h>
#include<QMouseEvent>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    fa = 0.0; // 初始角度为0
    sp=0.0;
    zuo=0;
    you=0;
    QTimer *timer = new QTimer(this); // 声明一个定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(mytimer()));// 定时器超时信号连接到槽函数
 timer->start(10); // 启动定时器，定时周期10ms

}
Dialog::~Dialog()
{delete ui;}


void Dialog::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    painter.fillRect(rect(),Qt::blue);
//    painter.setPen(Qt::white);
//    painter.setFont(QFont("Arial",60));
//    painter.drawText(rect(),Qt::AlignCenter,"Qt 你好");


    QPainter qp(this); QRect rc(0, 0, rect().width(), 30);
    qp.fillRect(rc, Qt::blue); // 填充蓝色矩形
    qp.setPen(Qt::yellow); qp.setFont(QFont("Arial", 28));
    qp.drawText(rc, Qt::AlignCenter, "Hello QT"); //显示标题文字
    for (int i = 0; i < rect().width(); i += 20)
        qp.drawPoint(i, 20); // 连续打点
    QPen pen(Qt::red); qp.setPen(pen);
    rc.setRect(5, 40, rect().width() - 10, rect().height() - 45);
    qp.drawRect(rc); // 画矩形框
    pen.setWidth(3); qp.setPen(pen);
    qp.drawLine(5, 35, rect().width() - 10, 35); // 画粗线
    QBrush brush(Qt::cyan); qp.setBrush(brush);
    qp.setPen(Qt::NoPen); // 关闭画笔，不画边框
    qp.drawEllipse(rc); // 画青色椭圆

    int r = rc.width()>rc.height() ? rc.height()/2 : rc.width()/2;//圆半径
      rc.setRect(rc.center().rx() - r, rc.center().ry() - r, 2 * r, 2 * r);
      qp.setRenderHint(QPainter::Antialiasing); // 反锯齿平滑
      QConicalGradient cg(0, 0, fa); // 声明色轮渐变对象
      cg.setColorAt(0, Qt::red); // 设置0度角红色
      cg.setColorAt(60.0 / 360.0, Qt::yellow); // 设置60度角黄色
      cg.setColorAt(120.0 / 360.0, Qt::green); // 设置120度角绿色
      cg.setColorAt(180.0 / 360.0, Qt::cyan); // 设置180度角青色
      cg.setColorAt(240.0 / 360.0, Qt::blue); // 设置240度角蓝色
      cg.setColorAt(300.0 / 360.0, Qt::magenta); // 设置300度角紫色
      cg.setColorAt(1, Qt::red); // 设置360度角红色
      qp.translate(rc.center()); // 坐标原点移到矩形中心
      QBrush tbr(cg); qp.setBrush(tbr); // 声明渐变画刷
      qp.drawEllipse(QPoint(0, 0), r, r); // 绘制彩色色轮


}

void Dialog::mytimer()
{
fa += sp;
if (fa >= 360)
    fa = 0;
if(fa<0)
    fa=360;
update();
}


void Dialog::on_pushButton_clicked()
{
    if(sp<10)
        sp+=1.0;
}

void Dialog::on_pushButton_2_clicked()
{
    if(sp>-10)
        sp-=1.0;
}


void Dialog::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton){
        zuo=1;
        if(you==1)
        {
            sp=0;
        }
       else if(sp < 0){
            sp = 1.0;
        }
      else  if(sp < 100){
            sp+= 1.0;
        }
    }
    // 如果是鼠标右键按下
    else if(event->button() == Qt::RightButton){
        you=1;
        if(zuo==1)
        {sp=0;}
        else if(sp > 0){
            sp = -1.0;
        }
       else  if(sp> -10){
            sp -= 1.0;
        }
    }
}



//void Dialog::mouseReleaseEvent(QMouseEvent *)
//{
//    if (event->button () == Qt::LeftButton) {
//            zuo=0;
//        }
// else if(event->button()==Qt::RightButton)
//        {
//            you=0;
//        }

//}

//A 编写一个 Qt 程序，在窗口正中央绘制一个正方形，当用户鼠标点住该方块时，
//方块开始旋转，放开鼠标时方块停止旋转。左键点住顺时针旋转，右键点住逆时
//针旋转，左右键同时点住则不旋转。
