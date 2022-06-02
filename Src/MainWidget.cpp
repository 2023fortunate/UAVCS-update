#include "Include/MainWidget.h"
#include "ui_MainWidget.h"
#include<QDebug>
#include<QPainter>

QList<QPointF> MainWidget::m_points;
MainWidget::MainWidget(QWidget *parent) :
    CSSCWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    add2 = false;
    jian2 = false;
    inited = false;

    this->setWindowMovable(false);
    QSize size = ui->label_5->size();
    QImage uavImg = QImage(":/Image/uav.png");
    QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
    ui->label_5->setPixmap(uavPixmap);

    //启动定时器,间隔为2s
    //startTimer(1000);

    ui->zhiNanZhen->setAnimation(true);

    ui->Radar->installEventFilter(this);

    ui->image_1->installEventFilter(this);

    ui->image_2->installEventFilter(this);

    ui->image_3->installEventFilter(this);

    ui->image_4->installEventFilter(this);

    ui->image_1->setMouseTracking(true);
    ui->image_2->setMouseTracking(true);
    ui->image_3->setMouseTracking(true);
    ui->image_4->setMouseTracking(true);

    ui->csscTextMoveWidget->setVisible(true);


    ui->csscBasicWidget_6->setVisible(false);

    ratio1 = 1;
    ratio2 = 1;

    strArray = {
        ":/Image/1.jpg",
        ":/Image/2.jpg",
        ":/Image/3.png",
        ":/Image/4.jpg"
    };

//    poUAV={
//        "",
//        "",
//        "",
//        ""
//    };

    imgNum = 0;

    videoWidget1 = new QVideoWidget(this);
    player1 = new QMediaPlayer();
    timer = new QTimer();
    timer->setInterval(100);//如果想看起来流畅些，可以把时间间隔调小，如100ms
    blureffect1 = new QGraphicsBlurEffect;
    blureffect2 = new QGraphicsBlurEffect;
    blureffect3 = new QGraphicsBlurEffect;
    blureffect4 = new QGraphicsBlurEffect;
    blureffect5 = new QGraphicsBlurEffect;

//    ui->csscToolButton_5->setVisible(false);

    //this->setTracking(true);
//    connect(player1,SIGNAL(durationChanged(qint64)),this,SLOT(getduration(qint64)));
//    qDebug()<<"main thread="<<QThread::currentThreadId();
}


MainWidget::~MainWidget()
{
    delete ui;
}


//void MainWidget::PressEvent(QEvent *event)
//{
//    QApplication::setOverrideCursor(Qt::OpenHandCursor);
//}
//void MainWidget::ReleaseEvent(QEvent *event)
//{
//    QApplication::setOverrideCursor(Qt::ArrowCursor);
//}


  //事件过滤器
bool MainWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->Radar && event->type() == QEvent::Paint)
    {
        //响应函数
        showPaint(MainWidget::m_points);
    }

    if((obj == ui->image_1 || obj == ui->image_2 || obj == ui->image_3 || obj == ui->image_4)
            && event->type() == QEvent::MouseButtonPress)
    {
        if(obj == ui->image_1){
            imgNum = 0;
        }else if(obj == ui->image_2){
            imgNum = 1;
        }else if(obj == ui->image_3){
            imgNum = 2;
        }else if(obj == ui->image_4){
            imgNum = 3;
        }
        QSize size = ui->image->size();
        QImage uavImg = QImage(strArray[imgNum]);
        int w1 = uavImg.width();
        int h1 = uavImg.height();
        QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
        ui->image->setPixmap(uavPixmap);

        imgPath = strArray[imgNum];

        ratio1 = (ui->image->width()*1.0)/(w1*1.0);
        ratio2 = (ui->image->height()*1.0)/(h1*1.0);

        ui->answer->setShowText(QString("第 %1 张/共 %2 张"). arg(imgNum+1).arg(strArray.size()));
    }

    if(event->type() == QEvent::MouseMove){
        ui->image_1->setStyleSheet("border-width: 0px;");
        ui->image_2->setStyleSheet("border-width: 0px;");
        ui->image_3->setStyleSheet("border-width: 0px;");
        ui->image_4->setStyleSheet("border-width: 0px;");
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        qDebug()<<"shub进来了,x="<<mouseEvent->x()<<",y="<<mouseEvent->y();
        if(obj == ui->image_1)
        {
//            if(mouseEvent->x()>10 && mouseEvent->x()<220 && mouseEvent->x()>1 && mouseEvent->y()<141){
                ui->image_1->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(21, 197, 212);");
//            }
        }
        if(obj == ui->image_2)
        {
            ui->image_2->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(21, 197, 212);");
        }
        if(obj == ui->image_3)
        {
            ui->image_3->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(21, 197, 212);");
        }

        if(obj == ui->image_4)
        {
            ui->image_4->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(21, 197, 212);");
        }
    }
    return QWidget::eventFilter(obj, event);
}

void MainWidget::showPaint(QList<QPointF> points)
{
    //qDebug()<<"传入m_points="<<points;
    int index = ui->uav_name->currentIndex();
    double x[4] = {0,0,0,0};
//    double x2 = 0;
//    double x3 = 0;
//    double x4 = 0;
    double y[4] = {0,0,0,0};
//    double y2 = 0;
//    double y3 = 0;
//    double y4 = 0;
    double a = 185.5;
    double b = 165.5;
//    points.append(QPoint(0,0));
//    points.append(QPoint(521,334));
//    points.append(QPoint(344,-521));
//    points.append(QPoint(-543,-2500));
    if(points.size()>0){
        if(index==0){
            if(points.size()>3){
                x[3] = static_cast<int>(points.at(3).x()-points.at(0).x()) + a;
                y[3] = static_cast<int>(points.at(0).y()-points.at(3).y()) + b;
            }
            if(points.size()>2){
                x[2] = static_cast<int>(points.at(2).x()-points.at(0).x()) + a;
                y[2] = static_cast<int>(points.at(0).y()-points.at(2).y()) + b;
            }
            if(points.size()>1){
                x[1] = static_cast<int>(points.at(1).x()-points.at(0).x()) + a;
                y[1] = static_cast<int>(points.at(0).y()-points.at(1).y()) + b;
            }
            if(points.size()>0){
                 x[0] = a; y[0] = b;
            }
        }else if(index==1){
            if(points.size()>3){
                x[3] = static_cast<int>(points.at(3).x()-points.at(1).x()) + a;
                y[3] = static_cast<int>(points.at(1).y()-points.at(3).y()) + b;
            }
            if(points.size()>2){
                x[2] = static_cast<int>(points.at(2).x()-points.at(1).x()) + a;
                y[2] = static_cast<int>(points.at(1).y()-points.at(2).y()) + b;
            }
            if(points.size()>1){
                x[0] = static_cast<int>(points.at(0).x()-points.at(1).x()) + a;
                y[0] = static_cast<int>(points.at(1).y()-points.at(0).y()) + b;
                x[1] = a; y[1] = b;
            }
        }else if(index==2){
            if(points.size()>3){
                x[3] = static_cast<int>(points.at(3).x()-points.at(2).x()) + a;
                y[3] = static_cast<int>(points.at(2).y()-points.at(3).y()) + b;
            }
            if(points.size()>2){
               x[2] = a; y[2] = b;
               x[0] = static_cast<int>(points.at(0).x()-points.at(2).x()) + a;
               y[0] = static_cast<int>(points.at(2).y()-points.at(0).y()) + b;
               x[1] = static_cast<int>(points.at(1).x()-points.at(2).x()) + a;
               y[1] = static_cast<int>(points.at(2).y()-points.at(1).y()) + b;
            }
        }else if(index==3){
            if(points.size()>3){
                x[3] = a; y[3] = b;
                x[0] = static_cast<int>(points.at(0).x()-points.at(3).x()) + a;
                y[0] = static_cast<int>(points.at(3).y()-points.at(0).y()) + b;
                x[1] = static_cast<int>(points.at(1).x()-points.at(3).x()) + a;
                y[1] = static_cast<int>(points.at(3).y()-points.at(1).y()) + b;
                x[2] = static_cast<int>(points.at(2).x()-points.at(3).x()) + a;
                y[2] = static_cast<int>(points.at(3).y()-points.at(2).y()) + b;
            }
        }
    }

    double maxlengthx = 0.0;
    for (int i=0;i<4;i++) {
        double lengthx;
        if(x[i]<=a){
            lengthx = a - x[i];
        }else{
            lengthx = x[i] - a;
        }
        if(lengthx>maxlengthx){
            maxlengthx = lengthx;
        }
    }
    double scale_x = ceil(maxlengthx/a);
    for (int i=0;i<4;i++) {
        if(x[i]>a){
            x[i] = x[i] / scale_x;            
        }else if(x[i]<a){
            x[i] = a - ((a - x[i]) / scale_x);
        }
    }


    double maxlengthy = 0.0;
    for (int i=0;i<4;i++) {
        double lengthy;
        if(y[i]<=b){
            lengthy = b - y[i];
        }else{
            lengthy = y[i] - b;
        }
        if(lengthy>maxlengthy){
            maxlengthy = lengthy;
        }
    }
    double scale_y = ceil(maxlengthy/b);
    for (int i=0;i<4;i++) {
        if(y[i]>b){
            y[i] = y[i] / scale_y;
        }else if(y[i]<b){
            y[i] = b - ((b - y[i]) / scale_y);
        }
    }
//    qDebug()<<"hhh,x1="<<x[0]<<",y1="<<y[0]<<",x2="<<x[1]<<",y2="<<y[1]<<",x3="<<x[2]<<",y3="<<y[2]<<",x4="<<x[3]<<",y4="<<y[3];
//    x[0]= 185.5 ;y[0]= 165.5 ;x[1]= 184.5 ;y[1]= 156.5 ;x[2]= 176.5 ;y[2]= 157.5 ;x[3]= 177.5 ;y[3]= 163.5;
    for (int i=0;i<4;i++) {
        if(((x[i]-a >0) && (x[i]-a <3) )|| ((y[i]-b >0) && (y[i]-b <3))){
//            qDebug()<<"进来了，i="<<i;
            if((x[i] !=a) && (y[i]!=b)){
//                qDebug()<<"i="<<i;
                if(i==0){
                    x[i] = x[i] - a/3;
                    y[i] = y[i] - b/3;
                }else if(i==1){
                    x[i] = x[i] + a/3;
                    y[i] = y[i] - b/3;
                }else if(i==2){
                    x[i] = x[i] - a/3;
                    y[i] = y[i] + b/3;
                }else if(i==3){
                    x[i] = x[i] + a/3;
                    y[i] = y[i] + b/3;
                }
            }
        }else{
            if(x[i] > 2*a/3 && x[i] < a){
                x[i] = x[i] - a/3;
            }else if(x[i] > a && x[i] < 4*a/3){
                x[i] = x[i] + a/3;
            }

            if(y[i] > 2*b/3 && y[i] < b){
                y[i] = y[i] - b/3;
            }else if(y[i] > b && y[i] < 4*b/3){
                y[i] = y[i] + b/3;
            }
        }

    }
// qDebug()<<"hhh,x1="<<x[0]<<",y1="<<y[0]<<",x2="<<x[1]<<",y2="<<y[1]<<",x3="<<x[2]<<",y3="<<y[2]<<",x4="<<x[3]<<",y4="<<y[3];
    QPainter painter(ui->Radar);    
    if(x[0]!=0.0&&y[0]!=0.0){
        painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF(x[0], y[0]));
        painter.drawPoint(QPointF(x[0]+2, y[0]+2));
        painter.drawPoint(QPointF(x[0]+2, y[0]));
        painter.drawPoint(QPointF(x[0], y[0]+2));
    }
    if(x[1]!=0.0&&y[1]!=0.0){
        painter.setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF(x[1], y[1]));
        painter.drawPoint(QPointF(x[1]+2, y[1]+2));
        painter.drawPoint(QPointF(x[1]+2, y[1]));
        painter.drawPoint(QPointF(x[1], y[1]+2));
    }
    if(x[2]!=0.0&&y[2]!=0.0){
        painter.setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF(x[2], y[2]));
        painter.drawPoint(QPointF(x[2]+2, y[2]+2));
        painter.drawPoint(QPointF(x[2]+2, y[2]));
        painter.drawPoint(QPointF(x[2], y[2]+2));
    }
    if(x[3]!=0.0&&y[3]!=0.0){
        painter.setPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap));
        painter.drawPoint(QPointF(x[3], y[3]));
        painter.drawPoint(QPointF(x[3]+2, y[3]+2));
        painter.drawPoint(QPointF(x[3]+2, y[3]));
        painter.drawPoint(QPointF(x[3], y[3]+2));
    }
}

//   //重写定时器事件
//void MainWidget::timerEvent(QTimerEvent *)
//{
//    this->update();

//    //定义静态局部对象time，定义一次，多次调用
//    static QTime time(0,0);
//    static int num = -1;
//    static int yiBiao_1[10] = {40,41,42,43,45,46,43,44,42,44};
//    static int yiBiao_2[10] = {41,41,42,44,44,43,43,45,44,43};
//    static int yiBiao_3[10] = {41,41,42,44,44,43,43,45,44,43};
//    static int yiBiao_4[10] = {42,41,42,45,45,46,43,46,46,43};
//    static int haiba[10] = {25,30,35,35,35,32,27,24,26,28};
//    static int wendu[10] = {33,34,33,35,34,36,34,36,33,34};
//    static int dianliang_1 = 500;
//    static int dianliang_2 = 500;
//    static int youliang = 500;
//    static double circle_1[10] = {37.04,35.20,37.67,38.25,40.00,38.00,39.37,39.89,38.23,36.35};
//    static double circle_2[10] = {34.14,37.14,35.38,35.19,37.00,35.00,33.37,32.89,34.54,35.35};
//    static double circle_3[10] = {5.30,5.14,4.38,0.00,6.40,5.67,0.00,6.37,6.89,4.85};
//    //最大变化幅度：两分钟0.01值变
//    static double jingdu[15] = {124.471670, 124.471970,124.472670,124.473670,124.474670,124.474970, 124.475670,
//                               124.475980,124.476670,124.476970,124.477670,124.477970,124.478670,124.478970, 124.479670};
//    static double weidu[15] = {23.261940,23.262340,23.262740,23.263540,23.264940,23.265340,23.265740,
//                              23.265940,23.266540,23.267440,23.267940,23.268340,23.268740,23.269040, 23.269940};

//    //姿态仪
//    static int deg[30] = {3,2,3,3,3,3,2,1,0,-1,-1,-1,-3,-3,-3,-3,-2,-2,-1,1,2,2,2,3,3,3,4,4,5,4};


//    //飞行时间的定时器
//    time = time.addSecs(1);
//    num++;
//    QString timeAfterStr = time.toString("hh:mm:ss");
//    ui->csscLabel_49->setText(timeAfterStr);

//    //其余部件值随着时间波动
//    if(add2 == true)
//    {
//        //如果主页面按了加速按钮
//        ui->yibiao_1->setValue(ui->yibiao_1->getValue() + 1);
//        ui->yibiao_2->setValue(ui->yibiao_2->getValue() + 1);
//        ui->yibiao_3->setValue(ui->yibiao_3->getValue() + 1);
//        ui->yibiao_4->setValue(ui->yibiao_4->getValue() + 1);
//        ui->kedu_1->setValue(ui->kedu_1->getValue() + 1);

//        double c1 = ui->circle_1->getValue();
//        if(c1 == 0)
//            ui->circle_1->setValue(0);
//        else
//            ui->circle_1->setValue(c1 + 1);

//        double c2 = ui->circle_2->getValue();
//        if(c2 == 0)
//            ui->circle_2->setValue(0);
//        else
//            ui->circle_2->setValue(c2 + 1);

//        double c3 = ui->circle_1->getValue();
//        if(c3 == 0)
//            ui->circle_3->setValue(0);
//        else
//            ui->circle_3->setValue(c3 + 1);
//    }
//    else if (jian2 == true) {
//        //如果主页面按了减速按钮
//        ui->yibiao_1->setValue(ui->yibiao_1->getValue() - 1);
//        ui->yibiao_2->setValue(ui->yibiao_2->getValue() - 1);
//        ui->yibiao_3->setValue(ui->yibiao_3->getValue() - 1);
//        ui->yibiao_4->setValue(ui->yibiao_4->getValue() - 1);
//        ui->kedu_1->setValue(ui->kedu_1->getValue() - 1);

//        double c1 = ui->circle_1->getValue();
//        if(c1 == 0)
//            ui->circle_1->setValue(0);
//        else
//            ui->circle_1->setValue(c1 - 1);

//        double c2 = ui->circle_2->getValue();
//        if(c2 == 0)
//            ui->circle_2->setValue(0);
//        else
//            ui->circle_2->setValue(c2 - 1);

//        double c3 = ui->circle_1->getValue();
//        if(c3 == 0)
//            ui->circle_3->setValue(0);
//        else
//            ui->circle_3->setValue(c3 - 1);
//    }
//    else
//    {
//        //自由飞行模式
//        if(inited == false)
//        {
//  //            qDebug() << "-------------------------------------------";
//  //            qDebug() << "rate value1" << ui->yibiao_1->getValue();
//  //            qDebug() << "rate value2" << ui->yibiao_2->getValue();
//  //            qDebug() << "rate value3" << ui->yibiao_3->getValue();
//  //            qDebug() << "rate value4" << ui->yibiao_4->getValue();
//            ui->yibiao_1->setValue(yiBiao_1[num%10]);
//            ui->yibiao_2->setValue(yiBiao_2[num%10]);
//            ui->yibiao_3->setValue(yiBiao_3[num%10]);
//            ui->yibiao_4->setValue(yiBiao_4[num%10]);
//            ui->kedu_1->setValue(yiBiao_1[num%10]);
//            ui->circle_1->setValue(circle_1[num%10]);
//            ui->circle_2->setValue(circle_2[num%10]);
//            ui->circle_3->setValue(circle_3[num%10]);
//            inited = true;
//  //            qDebug() << "rate value1" << ui->yibiao_1->getValue();
//  //            qDebug() << "rate value2" << ui->yibiao_2->getValue();
//  //            qDebug() << "rate value3" << ui->yibiao_3->getValue();
//  //            qDebug() << "rate value4" << ui->yibiao_4->getValue();
//        }
//        else
//        {
//            ui->yibiao_1->setValue(ui->yibiao_1->getValue() + yiBiao_1[num%10] - 43);
//            ui->yibiao_2->setValue(ui->yibiao_2->getValue() + yiBiao_2[num%10] - 43);
//            ui->yibiao_3->setValue(ui->yibiao_3->getValue() + yiBiao_3[num%10] - 43);
//            ui->yibiao_4->setValue(ui->yibiao_4->getValue() + yiBiao_4[num%10] - 44);
//            ui->kedu_1->setValue(ui->kedu_1->getValue() + yiBiao_1[num%10]- 43);
//            ui->circle_1->setValue(ui->circle_1->getValue() + circle_1[num%10] - 38);
//            ui->circle_2->setValue(ui->circle_2->getValue() + circle_2[num%10] - 35);
//            ui->circle_3->setValue(ui->circle_3->getValue() + circle_3[num%10] - 4.50);
//  //            qDebug() <<"++++++++++++++++++++++++++++++++++++++++++++";
//  //            qDebug() << "rate value1" << ui->yibiao_1->getValue();
//  //            qDebug() << "rate value2" << ui->yibiao_2->getValue();
//  //            qDebug() << "rate value3" << ui->yibiao_3->getValue();
//  //            qDebug() << "rate value4" << ui->yibiao_4->getValue();

//        }

//    }

//    ui->kedu_2->setValue(haiba[num%10]);

//    if(dianliang_1 > 10)
//    {
//        dianliang_1 = dianliang_1 - 1;
//        ui->dianchi_5->setValue(dianliang_1);
//    }
//    else
//       ui->dianchi_5->setValue(10);


//    if(dianliang_2 > 10)
//    {
//        dianliang_2 = dianliang_2 - 1;
//        ui->dianchi_6->setValue(dianliang_2);
//    }
//    else
//        ui->dianchi_6->setValue(10);

//    if(youliang > 5)
//    {
//        youliang = youliang - 1;
//        ui->youliang_4->setValue(youliang);
//    }
//    else
//       ui->youliang_4->setValue(5);


//    ui->wendu_3->setValue(wendu[num%10]);

//    ui->csscGaugeCompass->setValue(num);

//    //姿态仪
//    ui->csscGaugePlane->setDegValue(deg[num%30]);
//    ui->csscGaugePlane->setRollValue(deg[num%30]);
//}


void MainWidget::on_MainWidget_sigMinButtonClicked()
{
    this->showMinimized();
}


void MainWidget::acclerate_v()
{
    // 无人机1加速2
//    add2 = true;
//    G_add2 = true;

    on_up_vx_clicked();
    on_up_vy_clicked();
    on_up_vz_clicked();

}

void MainWidget::decelerate_v()
{
    //无人机1减速2
//    jian2 = true;
//    G_jian2 = true;

    on_down_vx_clicked();
    on_down_vy_clicked();
    on_down_vz_clicked();
}

//void MainWidget::on_csscPushButton_13_clicked()
//{
//    G_jian2 = false;
//    G_add2 = false;
//    jian2 = false;
//    add2 = false;
//}

void MainWidget::on_csscToolButton_clicked()
{
    //第一个区域红色高亮
    QColor colorRed(255,0,0);
    QColor colorGray(100,100,100);
    ui->csscBasicWidget->setBorderColor(colorRed);
    ui->csscBasicWidget_2->setBorderColor(colorGray);
    ui->csscBasicWidget_3->setBorderColor(colorGray);
    ui->csscBasicWidget_4->setBorderColor(colorGray);
    ui->csscBasicWidget_5->setBorderColor(colorGray);

}

void MainWidget::on_csscToolButton_4_clicked()
{
    QColor colorRed(255,0,0);
    QColor colorGray(100,100,100);
    ui->csscBasicWidget_2->setBorderColor(colorRed);
    ui->csscBasicWidget->setBorderColor(colorGray);
    ui->csscBasicWidget_3->setBorderColor(colorGray);
    ui->csscBasicWidget_4->setBorderColor(colorGray);
    ui->csscBasicWidget_5->setBorderColor(colorGray);
}

void MainWidget::on_csscToolButton_5_clicked()
{
    QColor colorRed(255,0,0);
    QColor colorGray(100,100,100);
    ui->csscBasicWidget_5->setBorderColor(colorRed);
    ui->csscBasicWidget->setBorderColor(colorGray);
    ui->csscBasicWidget_3->setBorderColor(colorGray);
    ui->csscBasicWidget_4->setBorderColor(colorGray);
    ui->csscBasicWidget_2->setBorderColor(colorGray);
}


void MainWidget::on_csscToolButton_3_clicked()
{
    QColor colorRed(255,0,0);
    QColor colorGray(100,100,100);
    ui->csscBasicWidget_3->setBorderColor(colorRed);
    ui->csscBasicWidget->setBorderColor(colorGray);
    ui->csscBasicWidget_2->setBorderColor(colorGray);
    ui->csscBasicWidget_4->setBorderColor(colorGray);
    ui->csscBasicWidget_5->setBorderColor(colorGray);
}

void MainWidget::on_csscToolButton_2_clicked()
{
    QColor colorRed(255,0,0);
    QColor colorGray(100,100,100);
    ui->csscBasicWidget_4->setBorderColor(colorRed);
    ui->csscBasicWidget->setBorderColor(colorGray);
    ui->csscBasicWidget_3->setBorderColor(colorGray);
    ui->csscBasicWidget_2->setBorderColor(colorGray);
    ui->csscBasicWidget_5->setBorderColor(colorGray);
}


void MainWidget::highShow(int index)
{
    qDebug() << "slot function";
    switch (index)
    {
    case 1:
        on_csscToolButton_clicked();
        break;
    case 2:
        on_csscToolButton_4_clicked();
        break;
    case 3:
        on_csscToolButton_5_clicked();
        break;
    case 4:
        on_csscToolButton_3_clicked();
        break;
    case 5:
        on_csscToolButton_2_clicked();
        break;
    }
}
void MainWidget::showState1(int airID)
{
    airID = airID-1;
    if(airID==4||airID==6){
        airID=0;
    }
    if(airID==5){
        airID=2;
    }

    showState(airID);
}

   //显示不同无人机状态（修改无人机编号、台位名称、操作员ID）
void MainWidget::showState(int airID)
{
    //qDebug()<<"进来了,airID="<<airID<<",videoID="<<videoID;
    ui->uav_name->setCurrentIndex(airID);
    qDebug()<<" uav_index="<<uav_index;
    ui->uav_name->setNormalBorderColor(Qt::red);

    QTimer * timer1 = new QTimer();
    timer1->setInterval(100);//100ms
    timer1->start();
    connect(timer1, SIGNAL(timeout()), this, SLOT(onTimerOut1()));
    QTimer * timer2 = new QTimer();
    timer2->setInterval(10000);//100ms
    timer2->start();
    connect(timer2, &QTimer::timeout, this, [=] {
        timer1->stop();
        timer2->stop();
        delete timer1;
        delete timer2;
        QColor border1 = ui->work_camera->getNormalBorderColor();
        ui->uav_name->setNormalBorderColor(border1);
    });

//    ui->csscComboBox_2->setCurrentIndex(airID);
//    ui->csscComboBox_4->setCurrentIndex(airID);
//    ui->csscComboBox_5->setCurrentIndex(videoID);
    //on_uav_name_currentIndexChanged(airID);

//    int x = (1920-ui->csscBasicWidget_2->width())/2;
//    int y = (1000-ui->csscBasicWidget_2->height())/2;
//    ui->csscBasicWidget->setVisible(false);
//    ui->csscBasicWidget_2->setVisible(true);
//    ui->csscBasicWidget_2->setGeometry(x,y,ui->csscBasicWidget_2->width(),ui->csscBasicWidget_2->height());
//    ui->csscBasicWidget_3->setVisible(false);
//    ui->csscBasicWidget_4->setVisible(false);
//    ui->csscBasicWidget_5->setVisible(false);
//    ui->csscBasicWidget_6->setVisible(false);
}
void MainWidget::onTimerOut1(){
    int blur = blureffect1->blurRadius();
    if(blur>0){
        MainWidget::windowRecover();
    }
    QColor border = ui->uav_name->getNormalBorderColor();
    QColor border1 = ui->work_camera->getNormalBorderColor();
    if(border == Qt::red){
        ui->uav_name->setNormalBorderColor(border1);
    }else if(border == border1){
        ui->uav_name->setNormalBorderColor(Qt::red);
    }
}
//   //修改无人机的工作模式
//void MainWidget::workPattern(int patternID)
//{
//    ui->csscComboBox_3->setCurrentIndex(patternID);
//}

//   //语音传过来无人机ID和模式ID之后，对参数进行配置
//void MainWidget::modeChange(int airID,int modeID)
//{
//    qDebug() << "airID="<<airID;
//    qDebug() << "modeID="<<modeID;
//    ui->csscComboBox_2->setCurrentIndex(airID);
//    this->on_mode_currentIndexChanged(modeID);
//}

//   //修改无人机的配置方式
//void MainWidget::on_mode_currentIndexChanged(int modeID)
//{
//    qDebug() << "modeID="<<modeID;
//    ui->mode->setCurrentIndex(modeID);
//    if(modeID==0){
//        ui->csscComboBox_3->setCurrentIndex(0);
//        ui->csscComboBox_4->setCurrentIndex(0);
//        ui->csscComboBox_5->setCurrentIndex(0);
//    }else if(modeID==1){
//        ui->csscComboBox_3->setCurrentIndex(1);
//        ui->csscComboBox_4->setCurrentIndex(1);
//        ui->csscComboBox_5->setCurrentIndex(1);
//    }else if(modeID==2){
//        ui->csscComboBox_3->setCurrentIndex(2);
//        ui->csscComboBox_4->setCurrentIndex(2);
//        ui->csscComboBox_5->setCurrentIndex(0);
//    }else if(modeID==3){
//        ui->csscComboBox_3->setCurrentIndex(0);
//        ui->csscComboBox_4->setCurrentIndex(3);
//        ui->csscComboBox_5->setCurrentIndex(1);
//    }
//}


void MainWidget::setUAVMainData(QJsonObject uavJson){
//    qDebug()<<"mainwidget进了了-====uavJson="<<uavJson.value("1").toObject();
    if(uavJson.isEmpty()){
//       qDebug()<<"收到的uav为空";

    }else {
        //环境信息
        QJsonObject evalue = uavJson.value("EnvironmentState").toObject();
        ui->wendu->setValue(evalue.value("temperature").toDouble());
        ui->midu_qiya->setValue(evalue.value("air_density").toDouble());
        ui->midu_qiya->setValueRight(evalue.value("air_pressure").toDouble()/10000);

//        QJsonObject geo_point = evalue.value("geo_point").toObject();
//        ui->haiBa->setValue(geo_point.value("altitude").toDouble());
//        ui->jing_weidu->setValue(geo_point.value("longitude").toDouble());
//        ui->jing_weidu->setValueRight(geo_point.value("latitude").toDouble());

        //无人机的信息
        QJsonArray array = uavJson.value("UAV").toArray();

        //填充uav名称的下拉框
//        ui->uav_name->clear();
        for(int i=0;i<array.size();i++){
            if(i<4){
                QString name = array[i].toObject().value("name").toString();
                ui->uav_name->setItemText(i,name);
                QJsonObject obj = array[i].toObject().value("kinematics_estimated").toObject();
                QJsonObject linear_velocity = obj.value("linear_velocity").toObject();
                double vx = linear_velocity.value("x_val").toDouble();
                double vy = linear_velocity.value("y_val").toDouble();
                double vz = linear_velocity.value("z_val").toDouble();
//                poUAV[i] = QString(" %1号无人机位置\n x=%2 \n y=%3 \n z=%4").arg(QString::number(i)).arg(QString::number(vx, 'f', 2)).arg(QString::number(vy, 'f', 2)).arg(QString::number(vz, 'f', 2));
            }
        }
//        ui->uav_name->setCurrentIndex(uav_index);

        //磁力信息
        QJsonObject Magnetometer = array[uav_index].toObject().value("Magnetometer").toObject();
        double cili_x = Magnetometer.value("x_val").toDouble();
        double cili_y = Magnetometer.value("y_val").toDouble();
        double cili_z = Magnetometer.value("z_val").toDouble();

        ui->cili_x->setMaxValue(Convert(static_cast<int>(cili_x)));
        ui->cili_x->setLongStep(Convert(static_cast<int>(cili_x))/10);
        ui->cili_x->setShortStep(shortNum(Convert(static_cast<int>(cili_x))/10,10));
        ui->cili_y->setMaxValue(Convert(static_cast<int>(cili_y)));
        ui->cili_y->setLongStep(Convert(static_cast<int>(cili_y))/10);
        ui->cili_y->setShortStep(shortNum(Convert(static_cast<int>(cili_y))/10,10));
        ui->cili_z->setMaxValue(Convert(static_cast<int>(cili_z)));
        ui->cili_z->setLongStep(Convert(static_cast<int>(cili_z))/10);
        ui->cili_z->setShortStep(shortNum(Convert(static_cast<int>(cili_z))/10,10));

        ui->cili_x->setValue(cili_x);
        ui->cili_y->setValue(cili_y);
        ui->cili_z->setValue(cili_z);


        //QString cur_name = ui->uav_name->currentText();

        QString uav_name = array[uav_index].toObject().value("name").toString();
        int uav_state = array[uav_index].toObject().value("landed_state").toInt();
        QString uav_renwu = array[uav_index].toObject().value("task").toString(); //任务模式
        QString uav_shijiao = array[uav_index].toObject().value("ViewMode").toString(); //视角模式
        QString uav_camera = array[uav_index].toObject().value("camera").toString();//工作相机
        QString uav_image = array[uav_index].toObject().value("PhotoTpye").toString(); //图像格式

        QString state;//无人机状态
        QString renwu;//任务模式
        QString sj;//视角
        QString camera;//工作相机
        QString image;//图像格式
        if(uav_state==0){
            state = "着陆";
        }else if (uav_state==1) {
            state = "起飞";
        }else if (uav_state==2) {
            state = "飞行";
        }else if (uav_state==3) {
            state = "悬停";
        }else if (uav_state==4) {
            state = "碰撞";
        }

        if(uav_renwu=="search"||uav_renwu=="0"){
            renwu = "搜索";
        }else if(uav_renwu=="formation"||uav_renwu=="1"){
            renwu = "编队";
        }else if(uav_renwu=="following"||uav_renwu=="2"){
            renwu = "跟随";
        }

        if(uav_shijiao=="pickaback"||uav_shijiao=="0"){
            sj = "机载F";
        }else if(uav_shijiao=="Following"||uav_shijiao=="1"){
            sj = "跟随B";
        }else if(uav_shijiao=="manual"||uav_shijiao=="2"){
            sj = "手动M";
        }

        camera = uav_camera;
//             if(uav_camera==0){
//                 camera = "front_center";
//             }else if(uav_camera==1){
//                 camera = "front_right";
//             }else if(uav_camera==2){
//                 camera = "front_left";
//             }else if(uav_camera==3){
//                 camera = "bottom_center";
//             }else if(uav_camera==4){
//                 camera = "back_center";
//             }

         if(uav_camera=="front_center"){
             camera = "正前方";
         }else if(uav_camera=="front_right"){
             camera = "右方";
         }else if(uav_camera=="front_left"){
             camera = "左方";
         }else if(uav_camera=="bottom_center"){
             camera = "下方";
         }else if(uav_camera=="back_center"){
             camera = "后方";
         }

        image = uav_image;
//             if(uav_image==0){
//                 image = "Scene";
//             }else if(uav_image==1){
//                 image = "DepthPlanar";
//             }else if(uav_image==2){
//                 image = "DepthPerspective";
//             }else if(uav_image==3){
//                 image = "DepthVis";
//             }else if(uav_image==4){
//                 image = "DisparityNormalized";
//             }else if(uav_image==5){
//                 image = "Segmentation";
//             }else if(uav_image==6){
//                 image = "SurfaceNormals";
//             }else if(uav_image==7){
//                 image = "Infrared";
//             }

        QJsonObject obj = array[uav_index].toObject().value("kinematics_estimated").toObject();
        QJsonObject linear_velocity = obj.value("linear_velocity").toObject();
        double vx = linear_velocity.value("x_val").toDouble();
        double vy = linear_velocity.value("y_val").toDouble();
        double vz = linear_velocity.value("z_val").toDouble();
//             double v = sqrt(qPow(vx,2)+qPow(vy,2)+qPow(vz,2));
//           qDebug()<<"vx="<<vx<<",vy="<<vy<<",vz="<<vz;

        QJsonObject linear_acceleration = obj.value("linear_acceleration").toObject();
        double jvx = linear_acceleration.value("x_val").toDouble();
        double jvy = linear_acceleration.value("y_val").toDouble();
        double jvz = linear_acceleration.value("z_val").toDouble();
        double jv = sqrt(qPow(jvx,2)+qPow(jvy,2)+qPow(jvz,2));
//           qDebug()<<"jvx="<<jvx<<",vy="<<jvy<<",jvz="<<jvz<<",jv="<<jv;

        QJsonObject angular_velocity = obj.value("angular_velocity").toObject();
        double avx = angular_velocity.value("x_val").toDouble();
        double avy = angular_velocity.value("y_val").toDouble();
        double avz = angular_velocity.value("z_val").toDouble();
//             double av = sqrt(qPow(avx,2)+qPow(avy,2)+qPow(avz,2));
         //  qDebug()<<"avx="<<avx<<",avy="<<avy<<",avz="<<avz<<",av="<<av;

        QJsonObject angular_acceleration = obj.value("angular_acceleration").toObject();
        double javx = angular_acceleration.value("x_val").toDouble();
        double javy = angular_acceleration.value("y_val").toDouble();
        double javz = angular_acceleration.value("z_val").toDouble();
        double jav = sqrt(qPow(javx,2)+qPow(javy,2)+qPow(javz,2));
        // qDebug()<<"javx="<<javx<<",javy="<<javy<<",javz="<<javz<<",jav="<<jav;


        ui->kedu_1->setMaxValue(Convert(static_cast<int>(abs(vx))));
        ui->kedu_1->setMaxValueRight(Convert(static_cast<int>(abs(vy))));
        ui->kedu_1->setLongStep(Convert(static_cast<int>(abs(vx)))/10);
        ui->kedu_1->setLongStepRight(Convert(static_cast<int>(abs(vy)))/10);
        ui->kedu_1->setShortStep(shortNum(Convert(static_cast<int>(abs(vx)))/10,5));
        ui->kedu_1->setShortStepRight(shortNum(Convert(static_cast<int>(abs(vy)))/10,5));
        ui->kedu_1->setValue(abs(vx));
        ui->kedu_1->setValueRight(abs(vy));
        ui->vz->setValue(abs(vz));
        ui->vx->setShowText(QString::number(abs(vx), 'f', 2));
        ui->vy->setShowText(QString::number(abs(vy), 'f', 2));

        //第一个界面的四旋翼的速度
//        qDebug()<<"array="<<array;
        QJsonArray rotors = array[uav_index].toObject().value("rotorstates").toObject().value("rotors").toArray();
//qDebug()<<"rotors="<<rotors;
        ui->yibiao_1->setMaxValue(Convert(rotors[0].toObject().value("speed").toInt()));
        ui->yibiao_1->setValue(rotors[0].toObject().value("speed").toDouble());
//qDebug()<<"1="<<rotors[0].toObject().value("speed").toDouble();
        ui->yibiao_2->setMaxValue(Convert(rotors[1].toObject().value("speed").toInt()));
        ui->yibiao_2->setValue(rotors[1].toObject().value("speed").toDouble());
//qDebug()<<"2="<<rotors[1].toObject().value("speed").toDouble();
        ui->yibiao_3->setMaxValue(Convert(rotors[2].toObject().value("speed").toInt()));
        ui->yibiao_3->setValue(rotors[2].toObject().value("speed").toDouble());
//qDebug()<<"3="<<rotors[2].toObject().value("speed").toDouble();
        ui->yibiao_4->setMaxValue(Convert(rotors[3].toObject().value("speed").toInt()));
        ui->yibiao_4->setValue(rotors[3].toObject().value("speed").toDouble());
//qDebug()<<"4="<<rotors[3].toObject().value("speed").toDouble();
//                 ui->yibiao_1->
//                 ui->yibiao_2->setShowOverlay(false);
//                 ui->yibiao_3->setShowOverlay(false);
//                 ui->yibiao_4->setShowOverlay(false);

        //第一个小界面的右边部分
//                 if(abs(avx)<=25.0){
//                     ui->ruler_avx->setMaxValue(25);
//                 }else if(25.0<abs(avx)<=50.0){
//                     ui->ruler_avx->setMaxValue(50);
//                 }else if(50.0<abs(avx)<=100.0){
//                     ui->ruler_avx->setMaxValue(100);
//                 }else if(abs(avx)>100.0){
//                     ui->ruler_avx->setMaxValue(200);
//                 }
//                 if(abs(avy)<=25.0){
//                     ui->ruler_avy->setMaxValue(25);
//                 }else if(25.0<abs(avy)<=50.0){
//                     ui->ruler_avy->setMaxValue(50);
//                 }else if(50.0<abs(avy)<=100.0){
//                     ui->ruler_avy->setMaxValue(100);
//                 }else if(abs(avy)>100.0){
//                     ui->ruler_avy->setMaxValue(200);
//                 }
//                 if(abs(avz)<=25.0){
//                     ui->ruler_avz->setMaxValue(25);
//                 }else if(25.0<abs(avz)<=50.0){
//                     ui->ruler_avz->setMaxValue(50);
//                 }else if(50.0<abs(avz)<=100.0){
//                     ui->ruler_avz->setMaxValue(100);
//                 }else if(abs(avz)>100.0){
//                     ui->ruler_avz->setMaxValue(200);
//                 }

        ui->kedu_2->setMaxValue(Convert(static_cast<int>(abs(avx))));
        ui->kedu_2->setMaxValueRight(Convert(static_cast<int>(abs(avy))));
        ui->kedu_2->setLongStep(Convert(static_cast<int>(abs(avx)))/10);
        ui->kedu_2->setLongStepRight(Convert(static_cast<int>(abs(avy)))/10);
        ui->kedu_2->setShortStep(shortNum(Convert(static_cast<int>(abs(avx)))/10,5));
        ui->kedu_2->setShortStepRight(shortNum(Convert(static_cast<int>(abs(avy)))/10,5));
        ui->kedu_2->setValue(abs(avx));
        ui->kedu_2->setValueRight(abs(avy));
        ui->avz->setValue(abs(avz));
        ui->avx->setShowText(QString::number(abs(avx), 'f', 2));
        ui->avy->setShowText(QString::number(abs(avy), 'f', 2));
        ui->jv->setValue(jv);
        ui->jav->setValue(jav);

        //第二个界面的水平姿态仪
        QJsonObject yawangle =  array[uav_index].toObject().value("yawangle").toObject();
        int pitch = static_cast<int>(ceil(yawangle.value("pitch").toDouble()));
        int roll = static_cast<int>(ceil(yawangle.value("roll").toDouble()));
        ui->shuiPingYi->setDegValue(abs(pitch)); //设置旋转角度值pitch
        ui->shuiPingYi->setRollValue(abs(roll)); //设置前进旋转值roll

        //第二个界面的指南针
        double yaw = yawangle.value("yaw").toDouble();
        ui->zhiNanZhen->setValue(abs(yaw)); //yaw

        //第三个界面的下拉框填充
        ui->uav_state->setCurrentIndex(uav_state);//飞行状态  //暂传定值
        ui->renwu_model->setCurrentText(renwu);//任务模式 //暂传定值
        ui->shijiao->setCurrentText(sj);//视角 //暂传定值
        ui->work_camera->setCurrentText(camera);//工作相机 //暂传定值
        ui->image_format->setCurrentText(image);//图像格式 //暂传定值
        //第四个界面的遥控数据
        ui->number_vx->setShowText(QString::number(abs(vx), 'f', 2));
        ui->number_vy->setShowText(QString::number(abs(vy), 'f', 2));
        ui->number_vz->setShowText(QString::number(abs(vz), 'f', 2));
        ui->number_pitch->setShowText(QString::number(abs(yawangle.value("pitch").toDouble()), 'f', 2));
        ui->number_roll->setShowText(QString::number(abs(yawangle.value("roll").toDouble()), 'f', 2));
        ui->number_yaw->setShowText(QString::number(abs(yaw), 'f', 2));

        if(array.size()>0){
            MainWidget::m_points.clear();
        }
         for(int i=0;i<array.size();i++){

             QJsonObject position = array[i].toObject().value("kinematics_estimated").toObject().value("position").toObject();

             if(i==0){
                 double x1 = ceil(position.value("x_val").toDouble());
                 double y1 = ceil(position.value("y_val").toDouble());
//                 qDebug()<<"x1="<<x1<<",y1="<<y1;
                 MainWidget::m_points.append(QPointF(x1,y1));
             }else if(i==1){
                 double x2 = ceil(position.value("x_val").toDouble());
                 double y2 = ceil(position.value("y_val").toDouble());
//                 qDebug()<<"x2="<<x2<<",y2="<<y2;
                 MainWidget::m_points.append(QPointF(x2,y2));
             }else if(i==2){
                 double x3 = ceil(position.value("x_val").toDouble());
                 double y3 = ceil(position.value("y_val").toDouble());
//                 qDebug()<<"x3="<<x3<<",y3="<<y3;
                 MainWidget::m_points.append(QPointF(x3,y3));
             }else if(i==3){
                 double x4 = ceil(position.value("x_val").toDouble());
                 double y4 = ceil(position.value("y_val").toDouble());
//                 qDebug()<<"x4="<<x4<<",y4="<<y4;
                 MainWidget::m_points.append(QPointF(x4,y4));
             }
            // qDebug()<<"m_points="<<MainWidget::m_points;
            this->update();

//             if(uav_name.compare(cur_name)==0){

                 //第一个小界面的左边部分
//                 if(abs(vx)<=25.0){
//                     ui->ruler_vx->setMaxValue(25);
//                 }else if(25.0<abs(vx)<=50.0){
//                     ui->ruler_vx->setMaxValue(50);
//                 }else if(50.0<abs(vx)<=100.0){
//                     ui->ruler_vx->setMaxValue(100);
//                 }else if(abs(vx)>100.0){
//                     ui->ruler_vx->setMaxValue(200);
//                 }
//                 if(abs(vy)<=25.0){
//                     ui->ruler_vy->setMaxValue(25);
//                 }else if(25.0<abs(vy)<=50.0){
//                     ui->ruler_vy->setMaxValue(50);
//                 }else if(50.0<abs(vy)<=100.0){
//                     ui->ruler_vy->setMaxValue(100);
//                 }else if(abs(vy)>100.0){
//                     ui->ruler_vy->setMaxValue(200);
//                 }
//                 if(abs(vz)<=25.0){
//                     ui->ruler_vz->setMaxValue(25);
//                 }else if(25.0<abs(vz)<=50.0){
//                     ui->ruler_vz->setMaxValue(50);
//                 }else if(50.0<abs(vz)<=100.0){
//                     ui->ruler_vz->setMaxValue(100);
//                 }else if(abs(vz)>100.0){
//                     ui->ruler_vz->setMaxValue(200);
//                 }

//             }

//             //第四个界面的表格填充
//             ui->csscTableWidget->setItem(i,0,new QTableWidgetItem(uav_name));
//             ui->csscTableWidget->setItem(i,1,new QTableWidgetItem(camera));
//             ui->csscTableWidget->setItem(i,2,new QTableWidgetItem(renwu));
//             ui->csscTableWidget->setItem(i,3,new QTableWidgetItem(sj));
//             ui->csscTableWidget->setItem(i,4,new QTableWidgetItem(state));

         }
//         MainWidget::m_points.clear();
//         ui->csscTableWidget->setRowCount(array.size());
    }

}

void MainWidget::on_uav_name_currentIndexChanged(int index)
{
    if(index>=0){
        uav_index = index;//赋值给全局变量
         qDebug()<<"进来了，index="<<index<<",uav_index="<<uav_index;
    }

}
void MainWidget::changeIndex(int index){
    if(index>=0){
        qDebug()<<"成功进来了，index="<<index<<",uav_index="<<uav_index;
        ui->uav_name->setCurrentIndex(index);
        uav_index = index;//赋值给全局变量
    }
}
//void MainWidget::on_uav_name_currentTextChanged(const QString &name)
//{
//    qDebug()<<"change MainWidget uav name ...";
//    QString ip = "192.168.1.103";
//    //消息循环
//    GD d;//初始化，连接服务器
//    d.initA(ip.toStdString());
//    while(true)
//    {
//       QString AllData =  QString::fromStdString(d.AGet());//得到无人机名字和对应数据
//       QJsonDocument jsonDocument = QJsonDocument::fromJson(AllData.toLocal8Bit().data());
//        if( jsonDocument.isNull() ){
//            qDebug()<< "===> please check the string "<< AllData.toLocal8Bit().data();
//        }
//        QJsonObject jsonObject = jsonDocument.object();
//        //无人机的信息
//        QJsonArray array = jsonObject.value("UAV").toArray();
//        for(int i=0;i<array.size();i++){

//           QString  uav_name = array[i].toObject().value("name").toString();
//           if(uav_name.compare(name)==0){
//               QJsonObject obj = array[i].toObject().value("kinematics_estimated").toObject();
//               QJsonObject linear_velocity = obj.value("linear_velocity").toObject();
//               double vx = linear_velocity.value("x_val").toDouble();
//               double vy = linear_velocity.value("y_val").toDouble();
//               double vz = linear_velocity.value("z_val").toDouble();
//               double v = sqrt(qPow(vx,2)+qPow(vy,2)+qPow(vz,2));
//               //   qDebug()<<"vx="<<vx<<",vy="<<vy<<",vz="<<vz<<",v="<<v;

//               QJsonObject linear_acceleration = obj.value("linear_acceleration").toObject();
//               double jvx = linear_acceleration.value("x_val").toDouble();
//               double jvy = linear_acceleration.value("y_val").toDouble();
//               double jvz = linear_acceleration.value("z_val").toDouble();
//               double jv = sqrt(qPow(jvx,2)+qPow(jvy,2)+qPow(jvz,2));
//               //   qDebug()<<"jvx="<<jvx<<",vy="<<jvy<<",jvz="<<jvz<<",jv="<<jv;

//               QJsonObject angular_velocity = obj.value("angular_velocity").toObject();
//               double avx = angular_velocity.value("x_val").toDouble();
//               double avy = angular_velocity.value("y_val").toDouble();
//               double avz = angular_velocity.value("z_val").toDouble();
//               double av = sqrt(qPow(vx,2)+qPow(vy,2)+qPow(vz,2));
//               //   qDebug()<<"avx="<<avx<<",avy="<<avy<<",avz="<<avz<<",av="<<av;

//               QJsonObject angular_acceleration = obj.value("angular_acceleration").toObject();
//               double javx = angular_acceleration.value("x_val").toDouble();
//               double javy = angular_acceleration.value("y_val").toDouble();
//               double javz = angular_acceleration.value("z_val").toDouble();
//               double jav = sqrt(qPow(jvx,2)+qPow(jvy,2)+qPow(jvz,2));
//            //    qDebug()<<"javx="<<javx<<",javy="<<javy<<",javz="<<javz<<",jav="<<jav;

//               ui->uav_state->setCurrentIndex(array[i].toObject().value("landed_state").toInt());
//               ui->yibiao_vx->setValue(vx);
//               ui->yibiao_vy->setValue(vy);
//               ui->yibiao_vz->setValue(vz);
//               ui->csscLabel_v->setText(QString::number(v, 10, 2)+"m/s");
//               ui->uav_sudu->setText(QString::number(v, 10, 2)+"m/s");

//               ui->yibiao_jvx->setValue(jvx);
//               ui->yibiao_jvy->setValue(jvy);
//               ui->yibiao_jvz->setValue(jvz);
//               ui->csscLabel_jv->setText(QString::number(jv, 10, 2)+"m/s²");
//               ui->uav_jia_v->setText(QString::number(jv, 10, 2)+"m/s²");

//               ui->kedu_1->setValue(v);
//               ui->kedu_1->setValueRight(jv);

//               ui->yibiao_avx->setValue(avx);
//               ui->yibiao_avy->setValue(avy);
//               ui->yibiao_avz->setValue(avz);
//               ui->csscLabel_av->setText(QString::number(av, 10, 2)+"rad/s");
//               ui->uav_jiao_v->setText(QString::number(av, 10, 2)+"rad/s");

//               ui->yibiao_javx->setValue(javx);
//               ui->yibiao_javy->setValue(javy);
//               ui->yibiao_javz->setValue(javz);
//               ui->csscLabel_jav->setText(QString::number(jav, 10, 2)+"rad/s²");

//               ui->kedu_2->setValue(av);
//               ui->kedu_2->setValueRight(jav);

//           }
//        }
//    }
//}

void MainWidget::on_up_vx_clicked()
{
    QString vx = ui->number_vx->getShowText();
    double vx1 = vx.toDouble();
    ui->number_vx->setShowText(QString::number(vx1+1, 'f', 2));
}

void MainWidget::on_up_vy_clicked()
{
    QString vy = ui->number_vy->getShowText();
    double vy1 = vy.toDouble();
    ui->number_vy->setShowText(QString::number(vy1+1, 'f', 2));
}

void MainWidget::on_up_vz_clicked()
{
    QString vz = ui->number_vz->getShowText();
    double vz1 = vz.toDouble();
    ui->number_vz->setShowText(QString::number(vz1+1, 'f', 2));
}

void MainWidget::on_down_vx_clicked()
{
    QString vx = ui->number_vx->getShowText();
    double vx1 = vx.toDouble();
    if(vx1-1<0){
        vx1 = 1.0;
    }
    ui->number_vx->setShowText(QString::number(vx1-1, 'f', 2));
}

void MainWidget::on_down_vy_clicked()
{
    QString vy = ui->number_vy->getShowText();
    double vy1 = vy.toDouble();
    if(vy1-1<0){
        vy1 = 1.0;
    }
    ui->number_vy->setShowText(QString::number(vy1-1, 'f', 2));
}

void MainWidget::on_down_vz_clicked()
{
    QString vz = ui->number_vz->getShowText();
    double vz1 = vz.toDouble();
    if(vz1-1<0){
        vz1 = 1.0;
    }
    ui->number_vz->setShowText(QString::number(vz1-1, 'f', 2));
}

void MainWidget::on_up_pitch_clicked()
{
    QString pitch = ui->number_pitch->getShowText();
    double pitch1 = pitch.toDouble();
    ui->number_pitch->setShowText(QString::number(pitch1+1, 'f', 2));
}

void MainWidget::on_up_roll_clicked()
{
    QString roll = ui->number_roll->getShowText();
    double roll1 = roll.toDouble();
    ui->number_roll->setShowText(QString::number(roll1+1, 'f', 2));
}

void MainWidget::on_up_yaw_clicked()
{
    QString yaw = ui->number_yaw->getShowText();
    double yaw1 = yaw.toDouble();
    ui->number_yaw->setShowText(QString::number(yaw1+1, 'f', 2));
}

void MainWidget::on_down_pitch_clicked()
{
    QString pitch = ui->number_pitch->getShowText();
    double pitch1 = pitch.toDouble();
    if(pitch1-1<0){
        pitch1 = 1.0;
    }
    ui->number_pitch->setShowText(QString::number(pitch1-1, 'f', 2));
}

void MainWidget::on_down_roll_clicked()
{
    QString roll = ui->number_roll->getShowText();
    double roll1 = roll.toDouble();
    if(roll1-1<0){
        roll1 = 1.0;
    }
    ui->number_roll->setShowText(QString::number(roll1-1, 'f', 2));
}

void MainWidget::on_down_yaw_clicked()
{
    QString yaw = ui->number_yaw->getShowText();
    double yaw1 = yaw.toDouble();
    if(yaw1-1<0){
        yaw1 = 1.0;
    }
    ui->number_yaw->setShowText(QString::number(yaw1-1, 'f', 2));
}

int MainWidget::Convert(int num){
    int num1 = 0; //处理完毕的数字
    if(num>0){
        if(num<10){
            num1 = 10;
        }else if(num<50){
            num1 = 50;
        }else if(num<100){
            num1 = 100;
        }else if(num<1000){
            if(num/10%10<5){
                num1 = (num/100%10)*100+50;
            }else{
                num1 = (num/100%10+1)*100;
            }
        }else{
            int sum = 0;
            int num3 = num;
            while(num3){
                sum++;
                num3/=10;
            }
            int num2 = static_cast<int>(qPow(10,sum-1));
            num1 = ((num/num2)%10+1)*num2;
        }
    }
    return num1;
}

int MainWidget::shortNum(int num,int step){
    int num1 = num/step; //处理完毕的数字
    if(num1<1){
        num1 = 1;
    }
    return num1;
}

//弹框
void MainWidget::popWindow(int index1, int index2){
//    QPixmap pixmap(":/Image/bg.png");
    ui->csscBasicWidget_6->setVisible(true);
//    ui->csscBasicDialog->setVisible(false);
    ui->csscBasicWidget_6->raise();
    ui->title->setVisible(true);
    ui->csscTextEdit->setVisible(false);
    ui->image->setVisible(false);
    ui->image_1->setVisible(false);
    ui->image_2->setVisible(false);
    ui->image_3->setVisible(false);
    ui->image_4->setVisible(false);
    ui->big->setVisible(false);
    ui->small->setVisible(false);
    ui->all->setVisible(false);
    ui->left->setVisible(false);
    ui->right->setVisible(false);
    ui->answer->setVisible(false);
    videoWidget1->setVisible(false);
    ui->csscMediaControl->setVisible(false);
    ui->csscSliderTip->setVisible(false);
    player1->stop();

    ui->csscTextEdit->setWindowFlags(Qt::FramelessWindowHint | ui->csscTextEdit->windowFlags());
    ui->csscTextEdit->setAttribute(Qt::WA_TranslucentBackground);
    QWidget *v = ui->csscTextEdit->viewport();
    v->setWindowFlags(Qt::FramelessWindowHint | v->windowFlags());
    v->setAttribute(Qt::WA_TranslucentBackground);
    ui->title->setGeometry(200,8,500,40);


    blureffect1->setBlurRadius(10);	//数值越大，越模糊
    ui->csscBasicWidget->setGraphicsEffect(blureffect1);//设置模糊特效

    blureffect2->setBlurRadius(10);	//数值越大，越模糊
    ui->csscBasicWidget_2->setGraphicsEffect(blureffect2);//设置模糊特效

    blureffect3->setBlurRadius(10);	//数值越大，越模糊
    ui->csscBasicWidget_3->setGraphicsEffect(blureffect3);//设置模糊特效

    blureffect4->setBlurRadius(10);	//数值越大，越模糊
    ui->csscBasicWidget_4->setGraphicsEffect(blureffect4);//设置模糊特效

    blureffect5->setBlurRadius(10);	//数值越大，越模糊
    ui->csscBasicWidget_5->setGraphicsEffect(blureffect5);//设置模糊特效
    if(index1==1 && index2==1){
        QString dlgTitle="无人机有哪些分类？";
        QString strInfo="无人机可按：飞行平台、用途、尺度、任务高度、活动半径，划分为多种类型。";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==2){
        QString dlgTitle="无人机有哪些用途";
//        QString strInfo="      无人驾驶飞机简称“无人机”，英文缩写为“UAV”，是利用无线电遥控设备和自备的程序控制装置操纵的不载人飞机，或者由车载计算机完全地或间歇地自主地操作。与有人驾驶飞机相比，无人机往往更适合那些太“愚钝，肮脏或危险”的任务。\n      无人机按应用领域，可分为军用与民用。军用方面，无人机分为侦察机和靶机。民用方面，无人机+行业应用，是无人机真正的刚需；在航拍、农业、植保、微型自拍、快递运输、灾难救援、观察野生动物、监控传染病、测绘、新闻报道、电力巡检、救灾、影视拍摄、制造浪漫等等领域的应用，大大的拓展了无人机本身的用途，发达国家也在积极扩展行业应用与发展无人机技术。\n      2018年9月份，世界海关组织协调制度委员会（HSC）第62次会议决定，将无人机归类为“会飞的照相机”。";
//        MainWidget::longWords(dlgTitle,strInfo);
        QString strInfo1="主要划分为军用、民用。军用包括：侦察、诱饵、电子对抗、通讯中继和靶机等；民用包括：巡查/监视、农用、气象、勘探、测绘等。";
        QVector<QString> imgs = {
                ":/Image/21.png",
                ":/Image/22.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==3){
        QString dlgTitle="无人机有哪些尺度（尺寸）";
        QString strInfo1="微型无人机≤7g、7g<轻型无人机≤116kg，116kg<小型无人机≤5700kg、大型无人机>5700kg";
        QVector<QString> imgs = {
                ":/Image/31.png",
                ":/Image/32.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==4){
        QString dlgTitle="无人机有哪些任务高度";
        QString strInfo1="超低空无人机：高度≤100m\n低空无人机：100m<高度≤1000m\n中空无人机：1000m<高度≤7000m\n高空无人机：7000m高度≤18000m\n超高空无人机：高度>18000m";
        QVector<QString> imgs = {
                ":/Image/41.png",
                ":/Image/42.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==5){
        QString dlgTitle="无人机有哪些用途";
        QString strInfo="超近程无人机：半径≤15km \n近程无人机：15km<半径≤50km \n短程无人机：50km<半径≤200km \n中程无人机：200km<半径≤800km \n远程无人机：半径>800km";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==6){
        QString dlgTitle="无人机有哪些飞行平台";
        QString strInfo1="按照飞行平构型，无人机可分为：固定翼无人机、旋翼无人机、无人飞艇、扑翼无人机等";
        QVector<QString> imgs = {
                ":/Image/61.png",
                ":/Image/62.png",
                ":/Image/63.png",
                ":/Image/64.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==7){
        QString dlgTitle="什么是旋翼无人机";
        QString strInfo1="是一种具有三个及以上旋翼轴的特殊的无人驾驶直升机。其通过每个轴上的电动机转动，带动旋翼，从而产生升推力。旋翼的总距固定，而不像一般直升机那样可变。通过改变不同旋翼之间的相对转速，可以改变单轴推进力的大小，从而控制飞行器的运行轨迹。";
        QVector<QString> imgs = {
                ":/Image/71.jpg"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==8){
        QString dlgTitle="常见军用无人机";
        QString strInfo1="RQ-4A全球鹰无人机、复仇者-ER无人机、彩虹七型无人机、神雕无人机、X-47B无人机、MQ-9无人机、翔龙无人机、暗剑无人机";
        QVector<QString> imgs = {
                ":/Image/81.png",
                ":/Image/82.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==9){
        QString dlgTitle="（民用）无人机有哪些品牌 ";
        QString strInfo1="DJI大疆创新、3D Robotics、 Parrot（派诺特）、极飞、AscTec 、Microdrones 、亿航EHANG、零度、AEE一电、PowerVision等";
        QVector<QString> imgs = {
                ":/Image/91.png",
                ":/Image/92.png",
                ":/Image/93.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==10){
        QString dlgTitle="大疆无人机有哪些系列";
        QString strInfo="晓Spark系列、御Mavic系列、精灵Phantom系列、悟Inspire系列";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==11){
        QString dlgTitle="晓系列参数";
        QString strInfo=":/Image/101.png";
        MainWidget::img(dlgTitle,strInfo);

    }else if(index1==1 && index2==12){
        QString dlgTitle="无人机关键技术有哪些";
        QString strInfo="视觉技术\n定点悬停技术\n跟踪拍摄技术\n自主避障技术\n无人机图像传输技术\n电子稳像技术\n云台技术";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==13){
        QString dlgTitle="无人机图像传输技术有哪些";
        QString strInfo=" OFDM技术 \n COFDM技术 \n WIFI技术 \n Lightbridge高清远距离数字图传技术 \n 模拟图传技术";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==14){
        QString dlgTitle="无人机集群是什么";
        QString strInfo1="无人机集群是指由一定数量的同类或异类无人机组成，利用信息交互与反馈、激励与响应，实现相互间行为协同，适应动态环境，共同完成特定任务的自主式空中智能系统。";
        QVector<QString> imgs = {
                ":/Image/141.gif",
                ":/Image/142.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==15){
        QString dlgTitle="无人机集群关键技术";
        QString strInfo=" 无人机集群的体系结构 \n 任务分配 \n 集群控制 \n 集群导航 \n 集群组网";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==16){
        QString dlgTitle="无人机集群体系结构有哪些";
        QString strInfo1="目前主流的无人机集群体系结构保所分层式和分布式两种：";
        QVector<QString> imgs = {
                ":/Image/161.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);
    }else if(index1==1 && index2==17){
        QString dlgTitle="无人机集群如何任务分配";
        QString strInfo1="";
        QVector<QString> imgs = {
                ":/Image/171.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==18){
        QString dlgTitle="什么是无人机编队技术";
        QString strInfo="多无人机协同编队飞行，简称 CFF（Coordinated Formation Flight），就是将具有自主控制能力的多架无人机按照指定的三维队形和结构进行排列，并通过设计编队控制器使得所有的无人机在飞行过程中不仅能够保持队形的稳定，协同完成各项任务，而且可以进行队形的实时调整。";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==19){
        QString dlgTitle="无人机编队如何实现";
        QString strInfo1="";
        QVector<QString> imgs = {
                ":/Image/191.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }else if(index1==1 && index2==20){
        QString dlgTitle="无人机编队控制算法";
        QString strInfo=" 基于行为法 \n 人工势场法 \n 长机-僚机法 \n 图论法 \n 虚拟结构法";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==21){
        QString dlgTitle="什么是基于行为法（或其他算法）";
        QString strInfo="基于行为法的关键在于感知周围环境并作出相应判断。在无人机编队飞行过程中，机载传感器感知周围飞行环境，处理器和控制器做出不同响应。该方法将无人机编队的响应类型分为四种：避免碰撞、避开障碍物、获取目标和保持队形，每架无人机上控制器输出是这些基本行为的控制作用的加权平均值。基于行为法稳定性较好、灵活性强，但是队形保持难以做到十分精确。";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==22){
        QString dlgTitle="什么是人工势场法";
        QString strInfo="人工势场法通过构建人工势能场的方式来达到无人机编队飞行的效果。构建人工势能场需要建立人工势场函数，即各无人机之间具有相互吸引和相互排斥的作用力：当无人机之间的距离小于安全距离时，无人机之间的作用力为“斥力”，当无人机之间的距离大于编队距离时，无人机之间的作用力为“引力”。无人机加载多种传感器，可对周边环境进行三维建模，当检测到飞行轨迹上的存在障碍物且与障碍物的距离小于安全距离时，无人机与障碍物产生“斥力”，反之亦然。人工势场法原理简单，思路明确，但是构建人工势场函数以及周边环境的三维模型建立，对处理器的要求较高。";
        MainWidget::longWords(dlgTitle,strInfo);

    }else if(index1==1 && index2==23){
        QString dlgTitle="无人机编队应用";
        QString strInfo1="无人机编队主要的应用领域可分为军用和民用。在军用方面，无人机编队相较于单架无人机有诸多优势：无人机编队协同作业，可提升执行任务的成功率。在侦查军事目标、斩首行动、建立战场通讯、电子对抗和干扰等任务中，无人机编队可弥补单架无人机载重有限、视域不足的缺点，在瞬息万变的战场上很可能成为制胜关键。在民用领域，无人机编队最主要的应用场景为无人机编队表演，从春晚上数百架无人机美轮美奂的编队飞行，到婚礼、庆典中小型无人机编队助兴，无人机编队表演已经成为一种新颖时尚的表演形式。";
        QVector<QString> imgs = {
                ":/Image/231.gif",
                ":/Image/232.gif",
                ":/Image/233.png",
                ":/Image/234.png"
        };
        MainWidget::wordImg(dlgTitle,strInfo1,imgs);

    }
//    else if(index1==2 && index2==1){
//        QString dlgTitle="当前地图";
//        QString strInfo=":/Image/map.jpg";
//        MainWidget::img(dlgTitle,strInfo);

//    }
//    else if(index1==2 && index2==2){
//        QString dlgTitle="无人机图片";
//        MainWidget::imgs(dlgTitle,strArray);

//    }
//    else if(index1==3 && index2==1){
//        QString dlgTitle="无人机飞行动图";
//        QString strInfo = ":/Image/2.gif";
//        MainWidget::moveImg(dlgTitle,strInfo);


//    }
//    else if(index1==3 && index2==0){
//        QString dlgTitle="回放围捕过程";
//        QString strInfo = "D:\\movie\\uav0.mp4";
//        MainWidget::video(dlgTitle,strInfo);

//    }else if(index1==3 && index2==1){
//        QString dlgTitle="回放1号无人机围捕过程";
//        QString strInfo = "D:\\movie\\uav1.mp4";
//        MainWidget::video(dlgTitle,strInfo);

//    }else if(index1==3 && index2==2){
//        QString dlgTitle="回放2号无人机围捕过程";
//        QString strInfo = "D:\\movie\\uav2.mp4";
//        MainWidget::video(dlgTitle,strInfo);

//    }else if(index1==3 && index2==3){
//        QString dlgTitle="回放3号无人机围捕过程";
//        QString strInfo = "D:\\movie\\uav3.mp4";
//        MainWidget::video(dlgTitle,strInfo);

//    }else if(index1==3 && index2==4){
//        QString dlgTitle="回放4号无人机围捕过程";
//        QString strInfo = "D:\\movie\\uav4.mp4";
//        MainWidget::video(dlgTitle,strInfo);

//    }else if(index1==1 && index2==24){
//        QString dlgTitle="谁先发现了目标机？";
//        QString strInfo="uav"+QString::number(uav_index+1);
//        MainWidget::shortWords(dlgTitle,strInfo);
//    }else if(index1==1 && index2==25){
//        QString dlgTitle="1号无人机的位置分布";
//        QString strInfo=poUAV[0];
//        MainWidget::longWords(dlgTitle,strInfo);
//    }else if(index1==1 && index2==26){
//        QString dlgTitle="2号无人机的位置分布";
//        QString strInfo=poUAV[1];
//        MainWidget::longWords(dlgTitle,strInfo);
//    }else if(index1==1 && index2==27){
//        QString dlgTitle="3号无人机的位置分布";
//        QString strInfo=poUAV[2];
//        MainWidget::longWords(dlgTitle,strInfo);
//    }else if(index1==1 && index2==28){
//        QString dlgTitle="4号无人机的位置分布";
//        QString strInfo=poUAV[3];
//        MainWidget::longWords(dlgTitle,strInfo);
//    }

}

void MainWidget::shortWords(QString dlgTitle,QString strInfo){
    QPixmap bgPixmap = QPixmap(":/Image/bg6.png");
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);

//        QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
//        ui->csscBasicWidget_6->setGeometry(593,260,891,661);
//        ui->answer->setGeometry(60,84,781,521);
    ui->csscBasicWidget_6->setGeometry(593,260,891,552);
    ui->answer->setGeometry(0,0,891,552);


//        ui->title->setVisible(false);
//        ui->answer->setVisible(false);

    ui->title->setShowText(dlgTitle);
    ui->answer->setVisible(true);
    ui->answer->setShowText(strInfo);
}
void MainWidget::longWords(QString dlgTitle,QString strInfo){
    QPixmap bgPixmap = QPixmap(":/Image/bg6.png");
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);

//        QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);

    ui->csscBasicWidget_6->setGeometry(593,260,891,552);
    ui->csscTextEdit->setGeometry(57,56,778,448);


    ui->title->setShowText(dlgTitle);
    ui->csscTextEdit->setVisible(true);
    ui->csscTextEdit->setText(strInfo);

//        ui->answer->setGeometry(10,10,800,600);
//        ui->answer->setVisible(true);
//        ui->answer->setShowText(strInfo);
}
void MainWidget::wordImg(QString dlgTitle,QString strInfo1,QVector<QString> imgs){
    QPixmap bgPixmap = QPixmap(":/Image/bg6.png");
    ui->title->setShowText(dlgTitle);
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);
//        ui->csscBasicWidget_6->setGeometry(593,260,891,661);
//        ui->csscTextEdit->setGeometry(56,60,780,550);
    ui->csscBasicWidget_6->setGeometry(593,260,891,552);
    ui->csscTextEdit->setGeometry(56,60,780,488);
    ui->csscTextEdit->setVisible(true);
    ui->csscTextEdit->setText(strInfo1);

//        ui->image->setGeometry(406,320,410,263);
    ui->image->setVisible(true);
    if(imgs.size()==1){
         if(imgs[0].contains("191") | imgs[0].contains("171")| imgs[0].contains("161")){
             ui->image->setGeometry(58,52,775,449);
         }else{
             ui->image->setGeometry(58,255,775,246);
         }

         QSize size = ui->image->size();
         QImage uavImg = QImage(imgs[0]);
         QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
         ui->image->setPixmap(uavPixmap);
         ui->image->raise();
    }else if(imgs.size()==2){
        ui->image->setGeometry(58,255,387,246);
        if(imgs[0].contains("gif")){
            ui->image->setScaledContents(true);
            QMovie *movie = new QMovie(imgs[0]);
            ui->image->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start();         // 2. 启动动画
            ui->image->show();
        }else{
            QSize size = ui->image->size();
            QImage uavImg = QImage(imgs[0]);
            QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
            ui->image->setPixmap(uavPixmap);
            ui->image->raise();
        }
        ui->image_1->setVisible(true);
        ui->image_1->setGeometry(445,255,387,246);
        QSize size = ui->image_1->size();
        QImage uavImg = QImage(imgs[1]);
        QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
        ui->image_1->setPixmap(uavPixmap);
        ui->image_1->raise();
   }else if(imgs.size()==3){
        ui->image->setGeometry(58,255,258,246);
        QSize size1 = ui->image->size();
        QImage uavImg = QImage(imgs[0]);
        QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size1,Qt::IgnoreAspectRatio));
        ui->image->setPixmap(uavPixmap);
        ui->image->raise();

        ui->image_1->setVisible(true);
        ui->image_1->setGeometry(316,255,258,246);
        QSize size2 = ui->image_1->size();
        QImage uavImg2 = QImage(imgs[1]);
        QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
        ui->image_1->setPixmap(uavPixmap2);

        ui->image_2->raise();
        ui->image_2->setVisible(true);
        ui->image_2->setGeometry(574,255,258,246);
        QSize size3 = ui->image_2->size();
        QImage uavImg3 = QImage(imgs[2]);
        QPixmap uavPixmap3 = QPixmap::fromImage(uavImg3.scaled(size3,Qt::IgnoreAspectRatio));
        ui->image_2->setPixmap(uavPixmap3);
        ui->image_2->raise();
   }else if(imgs.size()==4){
        ui->image->setGeometry(58,255,193,246);
        if(imgs[0].contains("gif")){
            ui->image->setScaledContents(true);
            QMovie *movie = new QMovie(imgs[0]);
            ui->image->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start();         // 2. 启动动画
            ui->image->show();
        }else{
            QSize size = ui->image->size();
            QImage uavImg = QImage(imgs[0]);
            QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
            ui->image->setPixmap(uavPixmap);
            ui->image->raise();
        }
        ui->image_1->setVisible(true);
        ui->image_1->setGeometry(251,255,193,246);
        if(imgs[1].contains("gif")){
            ui->image_1->setScaledContents(true);
            QMovie *movie = new QMovie(imgs[1]);
            ui->image_1->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start();         // 2. 启动动画
            ui->image_1->show();
        }else{
            QSize size = ui->image_1->size();
            QImage uavImg = QImage(imgs[1]);
            QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
            ui->image_1->setPixmap(uavPixmap);
            ui->image_1->raise();
        }

        ui->image_2->raise();
        ui->image_2->setVisible(true);
        ui->image_2->setGeometry(444,255,193,246);
        QSize size3 = ui->image_2->size();
        QImage uavImg3 = QImage(imgs[2]);
        QPixmap uavPixmap3 = QPixmap::fromImage(uavImg3.scaled(size3,Qt::IgnoreAspectRatio));
        ui->image_2->setPixmap(uavPixmap3);
        ui->image_2->raise();

        ui->image_3->setVisible(true);
        ui->image_3->setGeometry(637,255,193,246);
        QSize size4 = ui->image_3->size();
        QImage uavImg4 = QImage(imgs[3]);
        QPixmap uavPixmap4 = QPixmap::fromImage(uavImg4.scaled(size4,Qt::IgnoreAspectRatio));
        ui->image_3->setPixmap(uavPixmap4);
        ui->image_3->raise();
   }

}
void MainWidget::img(QString dlgTitle,QString strInfo){
    ui->big->setVisible(true);
    ui->small->setVisible(true);
    ui->all->setVisible(true);

    QPixmap bgPixmap = QPixmap(":/Image/bg6.png");
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);
//        ui->csscBasicWidget_6->setGeometry(593,260,891,661);
//        ui->image->setGeometry(56,60,780,550);
    ui->csscBasicWidget_6->setGeometry(593,260,891,552);
    ui->image->setGeometry(58,52,774,448);
    ui->big->setGeometry(716,50,40,36);
    ui->small->setGeometry(754,50,40,36);
    ui->all->setGeometry(792,50,40,36);
    ui->image->setVisible(true);

    ui->title->setShowText(dlgTitle);
    QPixmap uavPixmap = QPixmap(strInfo);
    ui->image->setPixmap(uavPixmap);
    imgPath = strInfo;
    action = 1;
}
void MainWidget::imgs(QString dlgTitle,QVector<QString> strArray){
    ui->big->setVisible(true);
    ui->small->setVisible(true);
    ui->all->setVisible(true);
    ui->left->setVisible(true);
    ui->right->setVisible(true);
//        ui->left->setGeometry(150,200,71,41);
//        ui->right->setGeometry(691,200,71,41);
//        ui->big->setGeometry(644,5,40,36);
//        ui->small->setGeometry(682,5,40,36);
//        ui->all->setGeometry(720,5,40,36);
    ui->left->setGeometry(58,250,71,41);
    ui->right->setGeometry(760,250,71,41);
    ui->big->setGeometry(716,65,40,36);
    ui->small->setGeometry(754,65,40,36);
    ui->all->setGeometry(792,65,40,36);
    QPixmap bgPixmap = QPixmap(":/Image/bg9.png");
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);
    ui->csscBasicWidget_6->setGeometry(593,260,891,552);
//        ui->csscBasicWidget_6->setGeometry(593,260,891,761);
//        ui->csscImageView->setVisible(true);
//        ui->csscImageView->setGeometry(66,204,761,345);
//        ui->csscImageView->setFileDir("D:/UAVCS-update1/Image/duo");
//        ui->csscImageView->setFill(true);
//        ui->csscBasicWidget_6->setGeometry(573,260,912,425);

    ui->title->setShowText(dlgTitle);

    QSize size = ui->image->size();
    QImage uavImg = QImage(strArray[imgNum]);
    int w1 = uavImg.width();
    int h1 = uavImg.height();
    QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
    ui->image->setPixmap(uavPixmap);
    ui->image->setVisible(true);
    ui->image->setGeometry(58,67,774,433);
//        ui->image->setGeometry(66,204,761,345);
//        ui->image->setGeometry(152,5,610,415);
    imgPath = strArray[imgNum];

    ratio1 = (ui->image->width()*1.0)/(w1*1.0);
    ratio2 = (ui->image->height()*1.0)/(h1*1.0);

    ui->answer->setShowText(QString("第 %1 张/共 %2 张"). arg(imgNum+1).arg(strArray.size()));
//        ui->answer->setGeometry(210,500,461,71);
    ui->answer->setGeometry(215,429,461,71);
    ui->answer->setVisible(true);
//        ui->image_1->setGeometry(0,148,150,152);
//        ui->image_2->setGeometry(762,148,150,152);

//        ui->image_1->setGeometry(10,620,210,140);
//        ui->image_2->setGeometry(230,620,210,140);
//        ui->image_3->setGeometry(450,620,210,140);
//        ui->image_4->setGeometry(670,620,210,140);
//        ui->image_1->setVisible(true);
//        ui->image_2->setVisible(true);
//        ui->image_3->setVisible(true);
//        ui->image_4->setVisible(true);

//        int imgNum1 = imgNum-1;
//        QSize size1 = ui->image_1->size();
//        if(imgNum1>=0){
//            QImage uavImg1 = QImage(strArray[imgNum1]);
//            QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//            ui->image_1->setPixmap(uavPixmap1);
//            QGraphicsBlurEffect *blureffect11 = new QGraphicsBlurEffect;
//            blureffect11->setBlurRadius(10);	//数值越大，越模糊
//            ui->image_1->setGraphicsEffect(blureffect11);//设置模糊特效
//        }else{
//            QImage uavImg1 = QImage(":/Image/mask.png");
//            QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//            ui->image_1->setPixmap(uavPixmap1);
//        }


//        int imgNum2 = imgNum+1;
//        QSize size2 = ui->image_2->size();
//        if(imgNum2<strArray.size()){
//            QImage uavImg2 = QImage(strArray[imgNum2]);
//            QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//            ui->image_2->setPixmap(uavPixmap2);
//            QGraphicsBlurEffect *blureffect12 = new QGraphicsBlurEffect;
//            blureffect12->setBlurRadius(10);	//数值越大，越模糊
//            ui->image_2->setGraphicsEffect(blureffect12);//设置模糊特效
//        }else{
//            QImage uavImg2 = QImage(":/Image/mask.png");
//            QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//            ui->image_2->setPixmap(uavPixmap2);
//        }


//        QSize size3 = ui->image_3->size();
//        QImage uavImg3 = QImage(":/Image/3.png");
//        QPixmap uavPixmap3 = QPixmap::fromImage(uavImg3.scaled(size3,Qt::IgnoreAspectRatio));
//        ui->image_3->setPixmap(uavPixmap3);

//        QSize size4 = ui->image_4->size();
//        QImage uavImg4 = QImage(":/Image/4.jpg");
//        QPixmap uavPixmap4 = QPixmap::fromImage(uavImg4.scaled(size4,Qt::IgnoreAspectRatio));
//        ui->image_4->setPixmap(uavPixmap4);
    action = 2;
}
void MainWidget::moveImg(QString dlgTitle,QString strInfo){
    QPixmap bgPixmap = QPixmap(":/Image/bg6.png");
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);
    ui->csscBasicWidget_6->setGeometry(593,260,891,552);
    ui->image->setGeometry(58,52,774,448);
//        ui->csscBasicWidget_6->setGeometry(593,260,891,661);
//        ui->csscAnimationPlayer->setGeometry(30,30,737,490);
//        ui->csscAnimationPlayer->setDirPath("D://UAVCS-update//Image");
//        ui->csscAnimationPlayer->show();

    ui->title->setShowText(dlgTitle);
//        ui->image->setGeometry(56,60,780,550);
    ui->image->setVisible(true);
    ui->image->setScaledContents(true);
    QMovie *movie = new QMovie(strInfo);
    ui->image->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start();         // 2. 启动动画
    ui->image->show();
}
void MainWidget::video(QString dlgTitle,QString strInfo){
    ui->csscMediaControl->setVisible(true);
    ui->csscSliderTip->setVisible(true);
    ui->csscMediaControl->raise();
    ui->csscSliderTip->raise();
    QPixmap bgPixmap = QPixmap(":/Image/bg6.png");
    ui->csscBasicWidget_6->setBgPixmap(bgPixmap);
    ui->csscBasicWidget_6->setIsShowBgPixmap(true);
//        ui->csscBasicWidget_6->setGeometry(593,260,891,761);
    ui->csscBasicWidget_6->setGeometry(593,260,891,552);

    ui->csscSliderTip->setShowLabel(true);
    ui->csscSliderTip->setShowTime(true);
    ui->csscSliderTip->setRange(0,maxValue);
    videoWidget1->setVisible(true);

//        ui->csscMediaControl->setGeometry(0,660,881,47);
//        ui->csscSliderTip->setGeometry(60,710,771,22);
    ui->csscMediaControl->setGeometry(58,454,775,47);
    ui->csscSliderTip->setGeometry(58,432,775,22);



    ui->title->setShowText(dlgTitle);
    ui->csscMediaControl->setMediaStyle();

    //设置视频
    mediaList1 = new QMediaPlaylist(this);
    mediaList1->clear();
    videoWidget1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    QVBoxLayout *hlay = new QVBoxLayout(this);
    hlay->addWidget(videoWidget1);
    ui->csscBasicWidget_6->setLayout(hlay);

    videoWidget1->setParent(ui->csscBasicWidget_6);
//        videoWidget1->setGeometry(66,204,761,345);
    videoWidget1->setGeometry(58,52,774,448);
//        player1->setMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\one.mp4"));
    mediaList1->addMedia(QUrl::fromLocalFile(strInfo));
    mediaList1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaList1->setCurrentIndex(0);
    player1->setPlaylist(mediaList1);
    player1->setVideoOutput(videoWidget1);
    player1->setVolume(20);
//        ui->csscSliderTip->setRange(0,static_cast<int>(player1->duration()));

    videoWidget1->show();

    player1->play();

    timer->start();
    //将timer连接至onTimerOut槽函数
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}
void MainWidget::onTimerOut(){
    if(player1->duration()!=0){
        ui->csscSliderTip->setValue(player1->position()*maxValue/player1->duration());
    }

}
void MainWidget::getduration(qint64 playtime){
      playtime = player1->duration();
}
QString MainWidget::settime(qint64 playtime)
{
    qDebug()<<"playtime="<<playtime;
    int h,m,s;
    QString h1,m1,s1;
    playtime /= 1000;  //获得的时间是以毫秒为单位的
    h = playtime/3600;
    m = (playtime-h*3600)/60;
    s = playtime-h*3600-m*60;
    if(h<10){
        h1 = "0"+ QString::number(h);
    }else{
        h1 = QString::number(h);
    }
    if(m<10){
        m1 = "0"+ QString::number(m);
    }else{
        m1 = QString::number(m);
    }
    if(s<10){
        s1 = "0"+ QString::number(s);
    }else{
        s1 = QString::number(s);
    }

    QString time ;
    if(h!=0){
         time = QString("%1:%2:%3").arg(h1).arg(m1).arg(s1);  //把int型转化为string类型后再设置为label的text
    }else {
         time = QString("%1:%2").arg(m1).arg(s1);  //把int型转化为string类型后再设置为label的text
    }

//    qDebug()<<"h1="<<h1<<",m1="<<m1<<",s1="<<s1<<",time="<<time;
    return time;
}
//图片放大
void MainWidget::imageEnlarge(){
      ratio1 += 0.02 * ratio1;
      ratio2 += 0.02 * ratio2;
      QImage uavImg = QImage(imgPath);
      int w = uavImg.width();
      int h = uavImg.height();
      QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(ratio1*w,ratio2*h,Qt::IgnoreAspectRatio));
      ui->image->setPixmap(uavPixmap);
}

//图片缩小
void MainWidget::imageDecrease(){
    ratio1 -= 0.02 * ratio1;
    ratio2 -= 0.02 * ratio2;
    QImage uavImg = QImage(imgPath);
    int w = uavImg.width();
    int h = uavImg.height();
    QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(ratio1*w,ratio2*h,Qt::IgnoreAspectRatio));
    ui->image->setPixmap(uavPixmap);
}

//图片全屏
void MainWidget::imageFull(){
    if(ui->csscBasicWidget_6->width()==this->frameGeometry().width()){       

        ui->big->setVisible(true);
        ui->small->setVisible(true);
        ui->all->setVisible(true);
        ui->csscBasicWidget_6->raise();
        ui->title->setVisible(true);
//        ui->answer->setGeometry(210,500,461,71);
        ui->answer->setGeometry(230,350,461,71);
        if(action==1){
            ui->big->setGeometry(716,50,40,36);
            ui->small->setGeometry(754,50,40,36);
            ui->all->setGeometry(792,50,40,36);
            ui->csscBasicWidget_6->setGeometry(593,260,891,552);
            ui->image->setGeometry(58,52,774,448);

            QPixmap uavPixmap = QPixmap(imgPath);
            ui->image->setPixmap(uavPixmap);
            ui->left->setVisible(false);
            ui->right->setVisible(false);
        }else if(action==2){
//            ui->csscBasicWidget_6->setGeometry(593,260,891,761);
//            ui->csscBasicWidget_6->setGeometry(573,260,912,425);
//            ui->answer->setGeometry(230,350,461,71);
            ui->csscBasicWidget_6->setGeometry(593,260,891,552);
            ui->answer->setGeometry(215,429,461,71);
            ui->image->setVisible(true);
//            ui->image->setGeometry(66,204,761,345);
//            ui->image->setGeometry(152,5,610,415);
            ui->image->setGeometry(58,67,774,433);
            QSize size = ui->image->size();
            QImage uavImg = QImage(imgPath);
            int w1 = uavImg.width();
            int h1 = uavImg.height();
            QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
            ui->image->setPixmap(uavPixmap);
            ratio1 = (ui->image->width()*1.0)/(w1*1.0);
            ratio2 = (ui->image->height()*1.0)/(h1*1.0);

//            ui->left->setGeometry(80,350,71,41);
//            ui->right->setGeometry(750,350,71,41);
//            ui->left->setGeometry(150,200,71,41);
//            ui->right->setGeometry(691,200,71,41);
//            ui->big->setGeometry(644,5,40,36);
//            ui->small->setGeometry(682,5,40,36);
//            ui->all->setGeometry(720,5,40,36);

            ui->left->setGeometry(58,250,71,41);
            ui->right->setGeometry(760,250,71,41);
            ui->big->setGeometry(716,65,40,36);
            ui->small->setGeometry(754,65,40,36);
            ui->all->setGeometry(792,65,40,36);

            ui->left->setVisible(true);
            ui->right->setVisible(true);
//            ui->image_1->setVisible(true);
//            ui->image_2->setVisible(true);
//            ui->image_3->setVisible(true);
//            ui->image_4->setVisible(true);
        }



    }else {
        ui->csscBasicWidget_6->setGeometry(this->frameGeometry().x(), this->frameGeometry().y(),
                                           this->frameGeometry().width(), this->frameGeometry().height());
        ui->image->setGeometry(0, 0,this->frameGeometry().width(), this->frameGeometry().height());
        ui->csscBasicWidget_6->raise();
        ui->title->setVisible(false);
        ui->image_1->setVisible(false);
        ui->image_2->setVisible(false);
        ui->image_3->setVisible(false);
        ui->image_4->setVisible(false);


        QSize size = ui->image->size();
        QImage uavImg = QImage(imgPath);
        int w1 = uavImg.width();
        int h1 = uavImg.height();
        QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
        ui->image->setPixmap(uavPixmap);
        ui->image->setVisible(true);
        ratio1 = (ui->image->width()*1.0)/(w1*1.0);
        ratio2 = (ui->image->height()*1.0)/(h1*1.0);

        ui->big->setGeometry(1780,0,40,36);
        ui->small->setGeometry(1830,0,40,36);
        ui->all->setGeometry(1880,0,40,36);
        if(action==2){
            ui->left->setGeometry(0,540,71,41);
            ui->right->setGeometry(1849,540,71,41);
            ui->left->setVisible(true);
            ui->right->setVisible(true);
            ui->answer->setGeometry(730,990,461,71);
            ui->answer->setVisible(true);
        }

        ui->big->setVisible(true);
        ui->small->setVisible(true);
        ui->all->setVisible(true);

    }

}

//图片左移
void MainWidget::imageLeft(){
    ++imgNum;
    if(imgNum==4){
        imgNum = 0;
    }

    QSize size = ui->image->size();
    QImage uavImg = QImage(strArray[imgNum]);
    int w1 = uavImg.width();
    int h1 = uavImg.height();
    QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
    ui->image->setPixmap(uavPixmap);

    imgPath = strArray[imgNum];

    ratio1 = (ui->image->width()*1.0)/(w1*1.0);
    ratio2 = (ui->image->height()*1.0)/(h1*1.0);

    ui->answer->setShowText(QString("第 %1 张/共 %2 张"). arg(imgNum+1).arg(strArray.size()));

//    int imgNum1 = imgNum-1;
//    QSize size1 = ui->image_1->size();
//    if(imgNum1>=0){
//        QImage uavImg1 = QImage(strArray[imgNum1]);
//        QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//        ui->image_1->setPixmap(uavPixmap1);
//        QGraphicsBlurEffect *blureffect11 = new QGraphicsBlurEffect;
//        blureffect11->setBlurRadius(10);	//数值越大，越模糊
//        ui->image_1->setGraphicsEffect(blureffect11);//设置模糊特效
//    }else{
//        QImage uavImg1 = QImage(":/Image/mask.png");
//        QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//        ui->image_1->setPixmap(uavPixmap1);
//    }


//    int imgNum2 = imgNum+1;
//    QSize size2 = ui->image_2->size();
//    if(imgNum2<strArray.size()){
//        QImage uavImg2 = QImage(strArray[imgNum2]);
//        QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//        ui->image_2->setPixmap(uavPixmap2);
//        QGraphicsBlurEffect *blureffect12 = new QGraphicsBlurEffect;
//        blureffect12->setBlurRadius(10);	//数值越大，越模糊
//        ui->image_2->setGraphicsEffect(blureffect12);//设置模糊特效
//    }else{
//        QImage uavImg2 = QImage(":/Image/mask.png");
//        QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//        ui->image_2->setPixmap(uavPixmap2);
//    }
//    ++pictureNum1;
//    if(pictureNum1==4){
//        pictureNum1 = 0;
//    }
//    QSize size1 = ui->image->size();
//    QImage uavImg1 = QImage(strArray[pictureNum1]);
//    QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//    ui->image->setPixmap(uavPixmap1);

//    ++pictureNum2;
//    if(pictureNum2==4){
//        pictureNum2 = 0;
//    }
//    QSize size2 = ui->image_2->size();
//    QImage uavImg2 = QImage(strArray[pictureNum2]);
//    QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//    ui->image_2->setPixmap(uavPixmap2);

//    ++pictureNum3;
//    if(pictureNum3==4){
//        pictureNum3 = 0;
//    }
//    QSize size3 = ui->image_3->size();
//    QImage uavImg3 = QImage(strArray[pictureNum3]);
//    QPixmap uavPixmap3 = QPixmap::fromImage(uavImg3.scaled(size3,Qt::IgnoreAspectRatio));
//    ui->image_3->setPixmap(uavPixmap3);
}

//图片右移
void MainWidget::imageRight(){
    --imgNum;
    if(imgNum==-1){
        imgNum = 3;
    }

    QSize size = ui->image->size();
    QImage uavImg = QImage(strArray[imgNum]);
    int w1 = uavImg.width();
    int h1 = uavImg.height();
    QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
    ui->image->setPixmap(uavPixmap);

    imgPath = strArray[imgNum];
    ratio1 = (ui->image->width()*1.0)/(w1*1.0);
    ratio2 = (ui->image->height()*1.0)/(h1*1.0);

    ui->answer->setShowText(QString("第 %1 张/共 %2 张"). arg(imgNum+1).arg(strArray.size()));

//    int imgNum1 = imgNum-1;
//    QSize size1 = ui->image_1->size();
//    if(imgNum1>=0){
//        QImage uavImg1 = QImage(strArray[imgNum1]);
//        QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//        ui->image_1->setPixmap(uavPixmap1);
//        QGraphicsBlurEffect *blureffect11 = new QGraphicsBlurEffect;
//        blureffect11->setBlurRadius(10);	//数值越大，越模糊
//        ui->image_1->setGraphicsEffect(blureffect11);//设置模糊特效
//    }else{
//        QImage uavImg1 = QImage(":/Image/mask.png");
//        QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//        ui->image_1->setPixmap(uavPixmap1);
//    }


//    int imgNum2 = imgNum+1;
//    QSize size2 = ui->image_2->size();
//    if(imgNum2<strArray.size()){
//        QImage uavImg2 = QImage(strArray[imgNum2]);
//        QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//        ui->image_2->setPixmap(uavPixmap2);
//        QGraphicsBlurEffect *blureffect12 = new QGraphicsBlurEffect;
//        blureffect12->setBlurRadius(10);	//数值越大，越模糊
//        ui->image_2->setGraphicsEffect(blureffect12);//设置模糊特效
//    }else{
//        QImage uavImg2 = QImage(":/Image/mask.png");
//        QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//        ui->image_2->setPixmap(uavPixmap2);
//    }
//    --pictureNum1;
//    if(pictureNum1==-1){
//        pictureNum1 = 3;
//    }
//    QSize size1 = ui->image->size();
//    QImage uavImg1 = QImage(strArray[pictureNum1]);
//    QPixmap uavPixmap1 = QPixmap::fromImage(uavImg1.scaled(size1,Qt::IgnoreAspectRatio));
//    ui->image->setPixmap(uavPixmap1);

//    --pictureNum2;
//    if(pictureNum2==-1){
//        pictureNum2 = 3;
//    }
//    QSize size2 = ui->image_2->size();
//    QImage uavImg2 = QImage(strArray[pictureNum2]);
//    QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
//    ui->image_2->setPixmap(uavPixmap2);

//    --pictureNum3;
//    if(pictureNum3==-1){
//        pictureNum3 = 3;
//    }
//    QSize size3 = ui->image_3->size();
//    QImage uavImg3 = QImage(strArray[pictureNum3]);
//    QPixmap uavPixmap3 = QPixmap::fromImage(uavImg3.scaled(size3,Qt::IgnoreAspectRatio));
//    ui->image_3->setPixmap(uavPixmap3);
}
void MainWidget::windowRecover(){
    qDebug()<<"进来了xssw=================";
    ui->csscBasicWidget_6->setVisible(false);
//    ui->title->setVisible(false);
//    ui->csscTextEdit->setVisible(false);
//    ui->image->setVisible(false);
//    ui->image_1->setVisible(false);
//    ui->image_2->setVisible(false);
//    ui->image_3->setVisible(false);
//    ui->image_4->setVisible(false);
//    ui->big->setVisible(false);
//    ui->small->setVisible(false);
//    ui->all->setVisible(false);
//    ui->left->setVisible(false);
//    ui->right->setVisible(false);
//    ui->answer->setVisible(false);
//    videoWidget1->setVisible(false);
//    ui->csscMediaControl->setVisible(false);
//    ui->csscSliderTip->setVisible(false);
    player1->stop();

    blureffect1->setBlurRadius(0);	//数值越大，越模糊
    ui->csscBasicWidget->setGraphicsEffect(blureffect1);//设置模糊特效

    blureffect2->setBlurRadius(0);	//数值越大，越模糊
    ui->csscBasicWidget_2->setGraphicsEffect(blureffect2);//设置模糊特效

    blureffect3->setBlurRadius(0);	//数值越大，越模糊
    ui->csscBasicWidget_3->setGraphicsEffect(blureffect3);//设置模糊特效

    blureffect4->setBlurRadius(0);	//数值越大，越模糊
    ui->csscBasicWidget_4->setGraphicsEffect(blureffect4);//设置模糊特效

    blureffect5->setBlurRadius(0);	//数值越大，越模糊
    ui->csscBasicWidget_5->setGraphicsEffect(blureffect5);//设置模糊特效
}

void MainWidget::on_csscMediaControl_sigPlay()
{
   qDebug()<<"sigplay进来了";
   int state = player1->state(); // 获取播放的状态
   switch (state) {
       case QMediaPlayer::StoppedState:
            /* 媒体播放 */
            player1->play();
            break;
       case QMediaPlayer::PlayingState:
            /* 媒体暂停 */
            player1->pause();
            break;
       case QMediaPlayer::PausedState:
            player1->play();
            break;
   }
}
void MainWidget::on_csscMediaControl_sigStop()
{
    qDebug()<<"sigstop进来了";
    player1->pause();
}
void MainWidget::on_csscMediaControl_sigAddRate()
{
    qDebug()<<"AddRate进来了"<<player1->playbackRate();
    player1->setPlaybackRate(player1->playbackRate()+0.5);
}

void MainWidget::on_csscMediaControl_sigSubRate()
{
    qDebug()<<"SubRate进来了"<<player1->playbackRate();
    if(player1->playbackRate()<0.7){
         player1->setPlaybackRate(0.5);
    }
    player1->setPlaybackRate(player1->playbackRate()-0.2);
}

void MainWidget::on_csscSliderTip_valueChanged(int value)
{
    qDebug()<<"valueChanged进来了"<<value;
    qDebug()<<"duration="<<player1->duration();
    player1->setPosition(player1->duration()*value/100);
    QString time = MainWidget::settime(player1->duration());
    ui->csscMediaControl->setDurationInfo(time);
//    time = MainWidget::settime(player1->position());
//    ui->csscMediaControl->setPositionInfo(time);
}

void MainWidget::on_csscMediaControl_sigReplay()
{
    player1->setPosition(0);
}

void MainWidget::on_csscMediaControl_sigFullScreen()
{
    ui->csscMediaControl->setVisible(true);
    ui->csscSliderTip->setVisible(true);
    ui->csscMediaControl->raise();
    ui->csscSliderTip->raise();
    if(ui->csscBasicWidget_6->width()==this->frameGeometry().width()+350){
//        ui->csscBasicWidget_6->setGeometry(593,260,891,761);
//        videoWidget1->setGeometry(66,204,761,345);
//        ui->csscMediaControl->setGeometry(0,660,881,47);
// //        ui->csscSliderTip->setGeometry(650,670,171,22);
//        ui->csscSliderTip->setGeometry(60,710,771,22);
        ui->csscBasicWidget_6->setGeometry(593,260,891,552);
        videoWidget1->setGeometry(58,52,774,448);
        ui->csscMediaControl->setGeometry(58,454,775,47);
        ui->csscSliderTip->setGeometry(58,432,775,22);
    }else{
        ui->csscBasicWidget_6->setGeometry(this->frameGeometry().x()-200, this->frameGeometry().y()-52,
                                           this->frameGeometry().width()+350, this->frameGeometry().height()+350);
        videoWidget1->setGeometry(200,52,this->frameGeometry().width(), this->frameGeometry().height());
        ui->csscMediaControl->setGeometry(200,1087,1920,47);
//        ui->csscSliderTip->setGeometry(1400,1040,200,22);
        ui->csscSliderTip->setGeometry(200,1067,1920,22);
//        ui->csscMediaControl->setAutoFillBackground(true);
//        ui->csscSliderTip->setBackground(Qt::black);
    }
}

void MainWidget::on_big_clicked()
{
    MainWidget::imageEnlarge();
}

void MainWidget::on_small_clicked()
{
    MainWidget::imageDecrease();
}

void MainWidget::on_all_clicked()
{
    MainWidget::imageFull();
}

void MainWidget::on_left_clicked()
{
    MainWidget::imageRight();
}

void MainWidget::on_right_clicked()
{
    MainWidget::imageLeft();
}




void MainWidget::on_csscSliderTip_clicked()
{

}

void MainWidget::on_csscSliderTip_sliderMoved(int position)
{

}

void MainWidget::on_csscSliderTip_sliderReleased()
{

}
