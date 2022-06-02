#include "Include/mapwidget.h"
#include<complex>

#define pi 3.14159265


MapWidget::MapWidget(QWidget *parent) : QWidget(parent),
    Alloffset(0,0)
{
    action = MapWidget::None;
    image = QImage(":/Image/map2.png");

    pix = pix.fromImage(image);
    maxRatio = pix.width()/1920 < pix.height()/1050 ? pix.width()/1920 : pix.height()/1050;
    ratio =  (maxRatio + 1.0)/2;
//    maxRatio = 2;
//    ratio = 1.5;
    pressed = false;

    px1 = 0;
    px2 = 0;
    px3 = 0;
    px4 = 0;
    py1 = 0;
    py2 = 0;
    py3 = 0;
    py4 = 0;

    //开启定时器
    startTimer(1000);

  //  qDebug()<<"maxRatio"<<maxRatio<<",ratio"<<ratio;

    //this->setMouseTracking(true);

    for (int i=0;i<length;i++) {
        uav1[i] = QPoint(0,0);
        uav2[i] = QPoint(0,0);
        uav3[i] = QPoint(0,0);
        uav4[i] = QPoint(0,0);
        monitor[i] = QPoint(0,0);
        drone[i] = QPoint(0,0);
    }
}


bool MapWidget::event(QEvent *event)
{
    QPoint preDot;
    if(event->type() == QEvent::MouseButtonPress)
    {
        //强制类型转换dynamic_cast<>
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        pressed = true;
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
        oldMouse.setX(mouseEvent->x());
        oldMouse.setY(mouseEvent->y());

    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        pressed = false;
    }
    if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        offset.setX(mouseEvent->x() - oldMouse.x());
        offset.setY(mouseEvent->y() - oldMouse.y());
        oldMouse.setX(mouseEvent->x());
        oldMouse.setY(mouseEvent->y());
        this->setAction(MapWidget::Move);
        this->update();
    }
    return QWidget::event(event);
}

void MapWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        this->setAction(MapWidget::Amplification);
        this->update();
    }
    else
    {
        this->setAction(MapWidget::Shrink);
        this->update();
    }
    event->accept();
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    static int w = 960;
    static int h = 555;
    int newW = 1920 * ratio;
    int newH = 1050 * ratio;
    if( abs(Alloffset.x())<=((newW - 1920)/2)){
        ofx = Alloffset.x();

    }
    if( abs(Alloffset.y())<=((newH - 1050)/2)){
        ofy = Alloffset.y();
    }
//    if(action == MapWidget::Shrink)
//    {
//        action = MapWidget::all_air;
//        qDebug() << "shrink map!";
//        ratio -= 0.02 * ratio;
//        if(ratio < 1.0)
//        {
//            ratio = 1.0;
//        }

//    }
//    else if(action == MapWidget::Amplification)
//    {
//        action = MapWidget::all_air;
//        qDebug() << "enlarge map!";
//        ratio += 0.02 * ratio;
//        if(ratio > maxRatio)
//        {
//            ratio = maxRatio;
//        }

//    }
//    else if(action == MapWidget::Move)
//    {
//        action = MapWidget::all_air;
//        qDebug() << "move map!";
//        int offsetX = Alloffset.x() + offset.x();
//        Alloffset.setX(offsetX);
//        int offsetY = Alloffset.y() + offset.y();
//        Alloffset.setY(offsetY);

//    }else
    double l = 10.0;                                           //箭头的长度
    double a = 0.5;                                            //箭头与线段角度
    if(action == MapWidget::first_air)
    {
        qDebug() << "first air!";
        //画背景地图       
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);


        //绘制无人机1的飞行轨迹

//        qDebug()<<"name="<<pointList3.at(0).first;
//        qDebug()<<"x="<<pointList3.at(0).second.x();
//        qDebug()<<"y="<<pointList3.at(0).second.y();

//        qDebug()<<"name1="<<pointList4.at(0).first;
//        qDebug()<<"x1="<<pointList4.at(0).second.x();
//        qDebug()<<"y1="<<pointList4.at(0).second.y();



//        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        int temp = 1;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }


//        static int r1 = 100;
//        static int a1 = 300;
//        static int b1 = 300;
//        painter.drawArc(a1,b1,2*r1,2*r1,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px1 = a1 + r1 + r1 * cos(endArc/16*pi/180);
//        py1 = b1 + r1 - r1 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::red, 20, Qt::SolidLine, Qt::RoundCap));
            double x1 = pointList3.at(0).second.x();
            double y1 = pointList3.at(0).second.y();

            px1 = w + ((x1 - w) * ratio) + ofx;
            py1 = h + ((y1 - h) * ratio) + ofy;
//            G_px1 = px1;
//            G_py1 = py1;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::red);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(0).first);
//            pt.end();
//            painter.drawPixmap(px1-75, py1-75, 100, 100, pix1);
            painter.drawPoint(QPointF(px1,py1));
            painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum1 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav1[i].x()!=0||uav1[i].y()!=0)&&(uav1[i+1].x()!=0||uav1[i+1].y()!=0)){
                    double a1 = w + ((uav1[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav1[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav1[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav1[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum1++;
                }
            }
//            qDebug()<<"sum1="<<sum1;

            double chax = pointList4.at(0).second.x()-pointList3.at(0).second.x();
            double chay = pointList4.at(0).second.y()-pointList3.at(0).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
                double x2 = w + ((pointList4.at(0).second.x() - w) * ratio) + ofx;
                double y2 = h + ((pointList4.at(0).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x2,y2));
                    for (int i=0;i<length;i++) {
                        uav1[i] = QPoint(0,0);
                    }
                }else{
                    //绘制箭头
                   double x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - px1)) - a);//计算箭头的终点（x3,y3）
                   double y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - px1)) - a);
                   double x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - py1)) - a);//计算箭头的终点（x4,y4）
                   double y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - py1)) - a);
                   painter.drawLine(x2,y2,x3,y3);    //绘制箭头(x2,y2,x3,y3)
                   painter.drawLine(x2,y2,x4,y4);   //绘制箭头(x2,y2,x4,y4)
                   painter.drawLine(px1,py1,x2,y2);   //绘制主干箭头(begin,end)
                }

            }
        }

    }

    else if(action == MapWidget::second_air)
    {
        qDebug() << "second air!";
        //画背景地图
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);

        //绘制无人机2的飞行轨迹
        //设置线条颜色和样式

        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        int temp = 2;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }

//        static int r = 80;
//        static int a = 800;
//        static int b = 300;
//        painter.drawArc(a,b,2*r,2*r,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px2 = a + r + r * cos(endArc/16*pi/180);
//        py2 = b + r - r * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::yellow, 20, Qt::SolidLine, Qt::RoundCap));

            double x1 = pointList3.at(1).second.x();
            double y1 = pointList3.at(1).second.y();

            px2 = w + ((x1 - w) * ratio) + ofx;
            py2 = h + ((y1 - h) * ratio) + ofy;
//            G_px2 = px2;
//            G_py2 = py2;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::yellow);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(1).first);
//            pt.end();
//            painter.drawPixmap(px2-75, py2-75, 100, 100, pix1);


            painter.drawPoint(QPointF(px2,py2));
            painter.setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap));

            //绘制轨迹
            int sum2 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav2[i].x()!=0||uav2[i].y()!=0)&&(uav2[i+1].x()!=0||uav2[i+1].y()!=0)){
                    double a1 = w + ((uav2[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav2[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav2[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav2[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum2++;
                }
            }
//            qDebug()<<"sum2="<<sum2;
            double chax = pointList4.at(1).second.x()-pointList3.at(1).second.x();
            double chay = pointList4.at(1).second.y()-pointList3.at(1).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::yellow, 10, Qt::SolidLine, Qt::RoundCap));
                double x12 = w + ((pointList4.at(1).second.x() - w) * ratio) + ofx;
                double y12 = h + ((pointList4.at(1).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x12,y12));
                    for (int i=0;i<length;i++) {
                        uav2[i] = QPoint(0,0);
                    }
                }else{
                    double x13 = x12 - l * cos(atan2((y12 - y1) , (x12 - px2)) - a);//计算箭头的终点（x3,y3）
                    double y13 = y12 - l * sin(atan2((y12 - y1) , (x12 - px2)) - a);
                    double x14 = x12 - l * sin(atan2((x12 - x1) , (y12 - py2)) - a);//计算箭头的终点（x4,y4）
                    double y14 = y12 - l * cos(atan2((x12 - x1) , (y12 - py2)) - a);
                    painter.drawLine(x12,y12,x13,y13);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x12,y12,x14,y14);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px2,py2,x12,y12);   //绘制主干箭头(begin,end)
                }
            }
        }
    }

    else if(action == MapWidget::third_air)
    {
        qDebug() << "third air!";
        //画背景地图
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);

        //绘制无人机3的飞行轨迹
        //设置线条颜色和样式

//        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        int temp = 3;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }


//        static int r3 = 75;
//        static int a3 = 1000;
//        static int b3 = 500;
//        painter.drawArc(a3,b3,2*r3,2*r3,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px3 = a3 + r3 + r3 * cos(endArc/16*pi/180);
//        py3 = b3 + r3 - r3 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::blue, 20, Qt::SolidLine, Qt::RoundCap));

            double x1 = pointList3.at(2).second.x();
            double y1 = pointList3.at(2).second.y();

            px3 = w + ((x1 - w) * ratio) + ofx;
            py3 = h + ((y1 - h) * ratio) + ofy;
//            G_px3 = px3;
//            G_py3 = py3;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::blue);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(2).first);
//            pt.end();
//            painter.drawPixmap(px3-75, py3-75, 100, 100, pix1);

            painter.drawPoint(QPointF(px3,py3));
            painter.setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap));

            //绘制轨迹
            int sum3 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav3[i].x()!=0||uav3[i].y()!=0)&&(uav3[i+1].x()!=0||uav3[i+1].y()!=0)){
                    double a1 = w + ((uav3[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav3[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav3[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav3[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum3++;
                }
            }
//            qDebug()<<"sum3="<<sum3;
            double chax = pointList4.at(2).second.x()-pointList3.at(2).second.x();
            double chay = pointList4.at(2).second.y()-pointList3.at(2).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::blue, 10, Qt::SolidLine, Qt::RoundCap));
                double x22 = w + ((pointList4.at(2).second.x() - w) * ratio) + ofx;
                double y22 = h + ((pointList4.at(2).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x22,y22));
                    for (int i=0;i<length;i++) {
                        uav3[i] = QPoint(0,0);
                    }
                }else{
                    double x23 = x22 - l * cos(atan2((y22 - y1) , (x22 - px3)) - a);//计算箭头的终点（x3,y3）
                    double y23 = y22 - l * sin(atan2((y22 - y1) , (x22 - px3)) - a);
                    double x24 = x22 - l * sin(atan2((x22 - x1) , (y22 - py3)) - a);//计算箭头的终点（x4,y4）
                    double y24 = y22 - l * cos(atan2((x22 - x1) , (y22 - py3)) - a);
                    painter.drawLine(x22,y22,x23,y23);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x22,y22,x24,y24);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px3,py3,x22,y22);   //绘制主干箭头(begin,end)
                }

           }
        }
    }

    else if(action == MapWidget::fourth_air)
    {
        qDebug() << "fourth air!";
        //画背景地图
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);

        //绘制无人机4的飞行轨迹
        //设置线条颜色和样式


//        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        int temp = 4;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }


//        static int r4 = 110;
//        static int a4 = 500;
//        static int b4 = 500;
//        painter.drawArc(a4,b4,2*r4,2*r4,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px4 = a4 + r4 + r4 * cos(endArc/16*pi/180);
//        py4 = b4 + r4 - r4 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::green, 20, Qt::SolidLine, Qt::RoundCap));

            double x1 = pointList3.at(3).second.x();
            double y1 = pointList3.at(3).second.y();

            px4 = w + ((x1 - w) * ratio) + ofx;
            py4 = h + ((y1 - h) * ratio) + ofy;
//            G_px4 = px4;
//            G_py4 = py4;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::green);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(3).first);
//            pt.end();
//            painter.drawPixmap(px4-75, py4-75, 100, 100, pix1);

            painter.drawPoint(QPointF(px4,py4));
            painter.setPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum4 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav4[i].x()!=0||uav4[i].y()!=0)&&(uav4[i+1].x()!=0||uav4[i+1].y()!=0)){
                    double a1 = w + ((uav4[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav4[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav4[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav4[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum4++;
                }
            }
//            qDebug()<<"sum4="<<sum4;

            double chax = pointList4.at(3).second.x()-pointList3.at(3).second.x();
            double chay = pointList4.at(3).second.y()-pointList3.at(3).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::green, 10, Qt::SolidLine, Qt::RoundCap));
                double x32 = w + ((pointList4.at(3).second.x() - w) * ratio) + ofx;
                double y32 = h + ((pointList4.at(3).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x32,y32));
                    for (int i=0;i<length;i++) {
                        uav4[i] = QPoint(0,0);
                    }
                }else{
                    double x33 = x32 - l * cos(atan2((y32 - y1) , (x32 - px4)) - a);//计算箭头的终点（x3,y3）
                    double y33 = y32 - l * sin(atan2((y32 - y1) , (x32 - px4)) - a);
                    double x34 = x32 - l * sin(atan2((x32 - x1) , (y32 - py4)) - a);//计算箭头的终点（x4,y4）
                    double y34 = y32 - l * cos(atan2((x32 - x1) , (y32 - py4)) - a);
                    painter.drawLine(x32,y32,x33,y33);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x32,y32,x34,y34);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px4,py4,x32,y32);   //绘制主干箭头(begin,end)
                }
            }
        }
    }

    else if(action == MapWidget::fir_sec_air)
    {
        qDebug() << "fir_sec_air!";
        //画背景地图
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);


//        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        int temp = 2;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }
//        static int r1 = 100;
//        static int a1 = 300;
//        static int b1 = 300;
//        painter.drawArc(a1,b1,2*r1,2*r1,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px1 = a1 + r1 + r1 * cos(endArc/16*pi/180);
//        py1 = b1 + r1 - r1 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            //绘制无人机1的飞行轨迹
            painter.setPen(QPen(Qt::red, 20, Qt::SolidLine, Qt::RoundCap));
            double x1 = pointList3.at(0).second.x();
            double y1 = pointList3.at(0).second.y();

            px1 = w + ((x1 - w) * ratio) + ofx;
            py1 = h + ((y1 - h) * ratio) + ofy;
//            G_px1 = px1;
//            G_py1 = py1;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::red);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(0).first);
//            pt.end();
//            painter.drawPixmap(px1-75, py1-75, 100, 100, pix1);

            painter.drawPoint(QPointF(px1,py1));
            painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum1 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav1[i].x()!=0||uav1[i].y()!=0)&&(uav1[i+1].x()!=0||uav1[i+1].y()!=0)){
                    double a1 = w + ((uav1[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav1[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav1[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav1[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum1++;
                }
            }
//            qDebug()<<"sum1="<<sum1;
//            qDebug()<<"Alloffset="<<Alloffset;
//            qDebug()<<"ratio="<<ratio;
            double chax = pointList4.at(0).second.x()-pointList3.at(0).second.x();
            double chay = pointList4.at(0).second.y()-pointList3.at(0).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
                double x2 = w + ((pointList4.at(0).second.x() - w) * ratio) + ofx;
                double y2 = h + ((pointList4.at(0).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x2,y2));
                }else{
                    //绘制箭头
                   double x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - px1)) - a);//计算箭头的终点（x3,y3）
                   double y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - px1)) - a);
                   double x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - py1)) - a);//计算箭头的终点（x4,y4）
                   double y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - py1)) - a);
                   painter.drawLine(x2,y2,x3,y3);    //绘制箭头(x2,y2,x3,y3)
                   painter.drawLine(x2,y2,x4,y4);   //绘制箭头(x2,y2,x4,y4)
                   painter.drawLine(px1,py1,x2,y2);   //绘制主干箭头(begin,end)
                }

            }
        }
        //绘制无人机2的飞行轨迹
        //设置线条颜色和样式

//        //画弧
//        temp = 2;
//        mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }

//        static int r = 80;
//        static int a = 800;
//        static int b = 300;
//        painter.drawArc(a,b,2*r,2*r,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px2 = a + r + r * cos(endArc/16*pi/180);
//        py2 = b + r - r * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::yellow, 20, Qt::SolidLine, Qt::RoundCap));

            double x11 = pointList3.at(1).second.x();
            double y11 = pointList3.at(1).second.y();

            px2 = w + ((x11 - w) * ratio) + ofx;
            py2 = h + ((y11 - h) * ratio) + ofy;
//            G_px2 = px2;
//            G_py2 = py2;

//            //给实时点上显示小飞机图片
//            QPixmap pix2;
//            pix2.load(":/Image/uav.png");
//            QPainter pt1(&pix2);
//            pt1.begin(&pix2);
//            pt1.setPen(Qt::yellow);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font1 = pt1.font();
//            font1.setPixelSize(100);//改变字体大小
//            font1.setFamily("Microsoft YaHei");
//            font1.setBold(true);
//            pt1.setFont(font1);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt1.drawText(pix2.rect(), Qt::AlignCenter,pointList3.at(1).first);
//            pt1.end();
//            painter.drawPixmap(px2-75, py2-75, 100, 100, pix2);

            painter.drawPoint(QPointF(px2,py2));
            painter.setPen(QPen(Qt::yellow, 5, Qt::SolidLine, Qt::RoundCap));

            //绘制轨迹
            int sum2 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav2[i].x()!=0||uav2[i].y()!=0)&&(uav2[i+1].x()!=0||uav2[i+1].y()!=0)){
                    double a1 = w + ((uav2[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav2[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav2[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav2[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum2++;
                }
            }
//            qDebug()<<"sum2="<<sum2;
            double chax = pointList4.at(1).second.x()-pointList3.at(1).second.x();
            double chay = pointList4.at(1).second.y()-pointList3.at(1).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::yellow, 10, Qt::SolidLine, Qt::RoundCap));
                double x12 = w + ((pointList4.at(1).second.x() - w) * ratio) + ofx;
                double y12 = h + ((pointList4.at(1).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x12,y12));
                }else{
                    double x13 = x12 - l * cos(atan2((y12 - y11) , (x12 - px2)) - a);//计算箭头的终点（x3,y3）
                    double y13 = y12 - l * sin(atan2((y12 - y11) , (x12 - px2)) - a);
                    double x14 = x12 - l * sin(atan2((x12 - x11) , (y12 - py2)) - a);//计算箭头的终点（x4,y4）
                    double y14 = y12 - l * cos(atan2((x12 - x11) , (y12 - py2)) - a);
                    painter.drawLine(x12,y12,x13,y13);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x12,y12,x14,y14);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px2,py2,x12,y12);   //绘制主干箭头(begin,end)
                }
            }
        }
    }

    else if(action == MapWidget::thi_fou_air)
    {
        qDebug() << "thi_fou_air!";
        //画背景地图
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);

        //绘制无人机3的飞行轨迹
        //设置线条颜色和样式

//        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        int temp = 3;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }


//        static int r3 = 75;
//        static int a3 = 1000;
//        static int b3 = 500;
//        painter.drawArc(a3,b3,2*r3,2*r3,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px3 = a3 + r3 + r3 * cos(endArc/16*pi/180);
//        py3 = b3 + r3 - r3 * sin(endArc/16*pi/180);
        double l = 10.0;                                           //箭头的长度
        double a = 0.5;
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::blue, 20, Qt::SolidLine, Qt::RoundCap));
            double x1 = pointList3.at(2).second.x();
            double y1 = pointList3.at(2).second.y();

            px3 = w + ((x1 - w) * ratio) + ofx;
            py3 = h + ((y1 - h) * ratio) + ofy;
//            G_px3 = px3;
//            G_py3 = py3;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::blue);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(2).first);
//            pt.end();
//            painter.drawPixmap(px3-75, py3-75, 100, 100, pix1);

            painter.drawPoint(QPointF(px3,py3));
            painter.setPen(QPen(Qt::blue, 5, Qt::SolidLine, Qt::RoundCap));

            //绘制轨迹
            int sum3 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav3[i].x()!=0||uav3[i].y()!=0)&&(uav3[i+1].x()!=0||uav3[i+1].y()!=0)){
                    double a1 = w + ((uav3[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav3[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav3[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav3[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum3++;
                }
            }
//            qDebug()<<"sum3="<<sum3;
            double chax = pointList4.at(2).second.x()-pointList3.at(2).second.x();
            double chay = pointList4.at(2).second.y()-pointList3.at(2).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::blue, 10, Qt::SolidLine, Qt::RoundCap));
                double x22 = w + ((pointList4.at(2).second.x() - w) * ratio) + ofx;
                double y22 = h + ((pointList4.at(2).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x22,y22));
                }else{
                    double x23 = x22 - l * cos(atan2((y22 - y1) , (x22 - px3)) - a);//计算箭头的终点（x3,y3）
                    double y23 = y22 - l * sin(atan2((y22 - y1) , (x22 - px3)) - a);
                    double x24 = x22 - l * sin(atan2((x22 - x1) , (y22 - py3)) - a);//计算箭头的终点（x4,y4）
                    double y24 = y22 - l * cos(atan2((x22 - x1) , (y22 - py3)) - a);
                    painter.drawLine(x22,y22,x23,y23);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x22,y22,x24,y24);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px3,py3,x22,y22);   //绘制主干箭头(begin,end)
                }

           }
        }                                                             //箭头与线段角度
        //绘制无人机4的飞行轨迹
        //设置线条颜色和样式

//        //画弧
//        temp = 4;
//        mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }


//        static int r4 = 110;
//        static int a4 = 500;
//        static int b4 = 500;
//        painter.drawArc(a4,b4,2*r4,2*r4,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px4 = a4 + r4 + r4 * cos(endArc/16*pi/180);
//        py4 = b4 + r4 - r4 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::green, 20, Qt::SolidLine, Qt::RoundCap));
            double x11 = pointList3.at(3).second.x();
            double y11 = pointList3.at(3).second.y();

            px4 = w + ((x11 - w) * ratio) + ofx;
            py4 = h + ((y11 - h) * ratio) + ofy;
//            G_px4 = px4;
//            G_py4 = py4;

//            //给实时点上显示小飞机图片
//            QPixmap pix2;
//            pix2.load(":/Image/uav.png");
//            QPainter pt1(&pix2);
//            pt1.begin(&pix2);
//            pt1.setPen(Qt::green);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font1 = pt1.font();
//            font1.setPixelSize(100);//改变字体大小
//            font1.setFamily("Microsoft YaHei");
//            font1.setBold(true);
//            pt1.setFont(font1);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt1.drawText(pix2.rect(), Qt::AlignCenter,pointList3.at(3).first);
//            pt1.end();
//            painter.drawPixmap(px4-75, py4-75, 100, 100, pix2);
            painter.drawPoint(QPointF(px4,py4));
            painter.setPen(QPen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum4 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav4[i].x()!=0||uav4[i].y()!=0)&&(uav4[i+1].x()!=0||uav4[i+1].y()!=0)){
                    double a1 = w + ((uav4[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav4[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav4[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav4[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum4++;
                }
            }
//            qDebug()<<"sum4="<<sum4;

            double chax = pointList4.at(3).second.x()-pointList3.at(3).second.x();
            double chay = pointList4.at(3).second.y()-pointList3.at(3).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::green, 10, Qt::SolidLine, Qt::RoundCap));
                double x32 = w + ((pointList4.at(3).second.x() - w) * ratio) + ofx;
                double y32 = h + ((pointList4.at(3).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x32,y32));
                }else{
                    double x33 = x32 - l * cos(atan2((y32 - y11) , (x32 - px4)) - a);//计算箭头的终点（x3,y3）
                    double y33 = y32 - l * sin(atan2((y32 - y11) , (x32 - px4)) - a);
                    double x34 = x32 - l * sin(atan2((x32 - x11) , (y32 - py4)) - a);//计算箭头的终点（x4,y4）
                    double y34 = y32 - l * cos(atan2((x32 - x11) , (y32 - py4)) - a);
                    painter.drawLine(x32,y32,x33,y33);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x32,y32,x34,y34);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px4,py4,x32,y32);   //绘制主干箭头(begin,end)
                }
            }
        }

    }

    else if(action == MapWidget::all_air)
    {
       // qDebug() << "all air!";
        //画背景地图
        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        QPainter painter(this);

        int x = (newW - 1920)/2 - Alloffset.x();
        if(x < 0){
            x = 0;
        }
        if(x > newW - 1920){
            x = newW -  1920;
        }
        int y = (newH - 1050)/2 - Alloffset.y();
        if(y < 0){
            y = 0;
        }
        if(y > newH - 1050){
            y = newH -  1050;
        }        
        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
        QPen pen;
        pen.setWidth(3);
        pen.setColor(QColor(4,176,238));
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0,0,1917,1047);


        //绘制无人机1的飞行轨迹


//        //画弧
//        int endArc = 0;
//        int startArc = 0;
//        //画弧
//        int temp = 1;
//        int mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }

//        static int r1 = 100;
//        static int a1 = 300;
//        static int b1 = 300;
//        painter.drawArc(a1,b1,2*r1,2*r1,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px1 = a1 + r1 + r1 * cos(endArc/16*pi/180);
//        py1 = b1 + r1 - r1 * sin(endArc/16*pi/180);

        if(pointList3.size()>0){
            painter.setPen(QPen(QBrush(QColor(186,73,73)), 20, Qt::SolidLine, Qt::RoundCap));

            double x1 = pointList3.at(0).second.x();
            double y1 = pointList3.at(0).second.y();


            px1 = w + ((x1 - w) * ratio) + ofx;
            py1 = h + ((y1 - h) * ratio) + ofy;
//            px1 = x1;
//            py1 = y1;
//            G_px1 = px1;
//            G_py1 = py1;

//            //给实时点上显示小飞机图片
//            QPixmap pix1;
//            pix1.load(":/Image/uav.png");
//            QPainter pt(&pix1);
//            pt.begin(&pix1);
//            pt.setPen(Qt::red);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font = pt.font();
//            font.setPixelSize(100);//改变字体大小
//            font.setFamily("Microsoft YaHei");
//            font.setBold(true);
//            pt.setFont(font);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt.drawText(pix1.rect(), Qt::AlignCenter,pointList3.at(0).first);
//            pt.end();
//            painter.drawPixmap(px1-75, py1-75, 100, 100, pix1);

            painter.drawPoint(QPointF(px1,py1));
            painter.setPen(QPen(QBrush(QColor(186,73,73)), 3, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum1 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav1[i].x()!=0||uav1[i].y()!=0)&&(uav1[i+1].x()!=0||uav1[i+1].y()!=0)){
                    double a1 = w + ((uav1[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav1[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav1[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav1[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum1++;
                }
            }
//            qDebug()<<"sum1="<<sum1;
//            qDebug()<<"Alloffset="<<Alloffset;
//            qDebug()<<"ratio="<<ratio;
            double chax = pointList4.at(0).second.x()-pointList3.at(0).second.x();
            double chay = pointList4.at(0).second.y()-pointList3.at(0).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(QBrush(QColor(186,73,73)), 5, Qt::SolidLine, Qt::RoundCap));
                double x2 = w + ((pointList4.at(0).second.x() - w) * ratio) + ofx;
                double y2 = h + ((pointList4.at(0).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x2,y2));
                    for (int i = 0;i<length-2;i++) {
                        uav1[i+1] = QPoint(0,0);
                        monitor[i+1] = QPoint(0,0);
                    }
                }else{
                    //绘制箭头
                   double x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - px1)) - a);//计算箭头的终点（x3,y3）
                   double y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - px1)) - a);
                   double x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - py1)) - a);//计算箭头的终点（x4,y4）
                   double y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - py1)) - a);
                   painter.drawLine(x2,y2,x3,y3);    //绘制箭头(x2,y2,x3,y3)
                   painter.drawLine(x2,y2,x4,y4);   //绘制箭头(x2,y2,x4,y4)
                   painter.drawLine(px1,py1,x2,y2);   //绘制主干箭头(begin,end)
                }

            }
        }

        //绘制无人机2的飞行轨迹
        //设置线条颜色和样式

//        //画弧
//        temp = 2;
//        mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }

//        static int r = 80;
//        static int a = 800;
//        static int b = 300;
//        painter.drawArc(a,b,2*r,2*r,startArc,endArc);

//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px2 = a + r + r * cos(endArc/16*pi/180);
//        py2 = b + r - r * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(QBrush(QColor(214,84,84)), 20, Qt::SolidLine, Qt::RoundCap));
            double x11 = pointList3.at(1).second.x();
            double y11 = pointList3.at(1).second.y();

            px2 = w + ((x11 - w) * ratio) + ofx;
            py2 = h + ((y11 - h) * ratio) + ofy;
//            px2 = x11;
//            py2 = y11;
//            G_px2 = px2;
//            G_py2 = py2;

//            //给实时点上显示小飞机图片
//            QPixmap pix2;
//            pix2.load(":/Image/uav.png");
//            QPainter pt2(&pix2);
//            pt2.begin(&pix2);
//            pt2.setPen(Qt::yellow);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font2 = pt2.font();
//            font2.setPixelSize(100);//改变字体大小
//            font2.setFamily("Microsoft YaHei");
//            font2.setBold(true);
//            pt2.setFont(font2);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt2.drawText(pix2.rect(), Qt::AlignCenter,pointList3.at(1).first);
//            pt2.end();
//            painter.drawPixmap(px2-75, py2-75, 100, 100, pix2);

            painter.drawPoint(QPointF(px2,py2));
            painter.setPen(QPen(QBrush(QColor(214,84,84)), 3, Qt::SolidLine, Qt::RoundCap));

            //绘制轨迹
            int sum2 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav2[i].x()!=0||uav2[i].y()!=0)&&(uav2[i+1].x()!=0||uav2[i+1].y()!=0)){
                    double a1 = w + ((uav2[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav2[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav2[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav2[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum2++;
                }
            }
//            qDebug()<<"sum2="<<sum2;
            double chax = pointList4.at(1).second.x()-pointList3.at(1).second.x();
            double chay = pointList4.at(1).second.y()-pointList3.at(1).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(QBrush(QColor(214,84,84)), 5, Qt::SolidLine, Qt::RoundCap));
                double x12 = w + ((pointList4.at(1).second.x() - w) * ratio) + ofx;
                double y12 = h + ((pointList4.at(1).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x12,y12));
                    for (int i = 0;i<length-2;i++) {
                        uav2[i+1] = QPoint(0,0);
                    }
                }else{
                    double x13 = x12 - l * cos(atan2((y12 - y11) , (x12 - px2)) - a);//计算箭头的终点（x3,y3）
                    double y13 = y12 - l * sin(atan2((y12 - y11) , (x12 - px2)) - a);
                    double x14 = x12 - l * sin(atan2((x12 - x11) , (y12 - py2)) - a);//计算箭头的终点（x4,y4）
                    double y14 = y12 - l * cos(atan2((x12 - x11) , (y12 - py2)) - a);
                    painter.drawLine(x12,y12,x13,y13);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x12,y12,x14,y14);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px2,py2,x12,y12);   //绘制主干箭头(begin,end)
                }
            }
        }
        //绘制无人机3的飞行轨迹
        //设置线条颜色和样式
//        temp = 3;
//        mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }

//        static int r3 = 75;
//        static int a3 = 1000;
//        static int b3 = 500;
//        painter.drawArc(a3,b3,2*r3,2*r3,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px3 = a3 + r3 + r3 * cos(endArc/16*pi/180);
//        py3 = b3 + r3 - r3 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(QBrush(QColor(238,93,93)), 20, Qt::SolidLine, Qt::RoundCap));
            double x21 = pointList3.at(2).second.x();
            double y21 = pointList3.at(2).second.y();

            px3 = w + ((x21 - w) * ratio) + ofx;
            py3 = h + ((y21 - h) * ratio) + ofy;
//            px3 = x21;
//            py3 = y21;
//            G_px3 = px3;
//            G_py3 = py3;

//            //给实时点上显示小飞机图片
//            QPixmap pix3;
//            pix3.load(":/Image/uav.png");
//            QPainter pt3(&pix3);
//            pt3.begin(&pix3);
//            pt3.setPen(Qt::blue);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font3 = pt3.font();
//            font3.setPixelSize(100);//改变字体大小
//            font3.setFamily("Microsoft YaHei");
//            font3.setBold(true);
//            pt3.setFont(font3);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt3.drawText(pix3.rect(), Qt::AlignCenter,pointList3.at(2).first);
//            pt3.end();
//            painter.drawPixmap(px3-75, py3-75, 100, 100, pix3);

            painter.drawPoint(QPointF(px3,py3));
            painter.setPen(QPen(QBrush(QColor(238,93,93)), 3, Qt::SolidLine, Qt::RoundCap));

            //绘制轨迹
            int sum3 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav3[i].x()!=0||uav3[i].y()!=0)&&(uav3[i+1].x()!=0||uav3[i+1].y()!=0)){
                    double a1 = w + ((uav3[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav3[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav3[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav3[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum3++;
                }
            }
//            qDebug()<<"sum3="<<sum3;
            double chax = pointList4.at(2).second.x()-pointList3.at(2).second.x();
            double chay = pointList4.at(2).second.y()-pointList3.at(2).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(QBrush(QColor(238,93,93)), 5, Qt::SolidLine, Qt::RoundCap));
                double x22 = w + ((pointList4.at(2).second.x() - w) * ratio) + ofx;
                double y22 = h + ((pointList4.at(2).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x22,y22));
                    for (int i = 0;i<length-2;i++) {
                        uav3[i+1] = QPoint(0,0);
                    }
                }else{
                    double x23 = x22 - l * cos(atan2((y22 - y21) , (x22 - px3)) - a);//计算箭头的终点（x3,y3）
                    double y23 = y22 - l * sin(atan2((y22 - y21) , (x22 - px3)) - a);
                    double x24 = x22 - l * sin(atan2((x22 - x21) , (y22 - py3)) - a);//计算箭头的终点（x4,y4）
                    double y24 = y22 - l * cos(atan2((x22 - x21) , (y22 - py3)) - a);
                    painter.drawLine(x22,y22,x23,y23);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x22,y22,x24,y24);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px3,py3,x22,y22);   //绘制主干箭头(begin,end)
                }

           }
        }
        //绘制无人机4的飞行轨迹
        //设置线条颜色和样式

//        //画弧
//        temp = 4;
//        mol = 360/temp;
//        if((timeCount) <= 40)
//        {
//            startArc = 0;
//            endArc = (timeCount%mol)*16*temp;
//        }
//        else {
//            endArc = 40*16*temp;
//            startArc = (timeCount%mol)*16*temp - endArc;
//        }
//        static int r4 = 110;
//        static int a4 = 500;
//        static int b4 = 500;
//        painter.drawArc(a4,b4,2*r4,2*r4,startArc,endArc);
//        //画实时点
//        endArc = (timeCount%mol)*16*temp;
//        px4 = a4 + r4 + r4 * cos(endArc/16*pi/180);
//        py4 = b4 + r4 - r4 * sin(endArc/16*pi/180);
        if(pointList3.size()>0){
            painter.setPen(QPen(QBrush(QColor(255,100,100)), 20, Qt::SolidLine, Qt::RoundCap));
            double x31 = pointList3.at(3).second.x();
            double y31 = pointList3.at(3).second.y();

            px4 = w + ((x31 - w) * ratio) + ofx;
            py4 = h + ((y31 - h) * ratio) + ofy;

//            px4 = x31;
//            py4 = y31;
//            G_px4 = px4;
//            G_py4 = py4;

//            //给实时点上显示小飞机图片
//            QPixmap pix4;
//            pix4.load(":/Image/uav.png");
//            QPainter pt4(&pix4);
//            pt4.begin(&pix4);
//            pt4.setPen(Qt::green);
//            //设置字体大小.另可以根据画笔改变颜色等属性
//            QFont font4 = pt4.font();
//            font4.setPixelSize(100);//改变字体大小
//            font4.setFamily("Microsoft YaHei");
//            font4.setBold(true);
//            pt4.setFont(font4);
//            //将文字写在图片上，例如是int型的数字123，居中
//            pt4.drawText(pix4.rect(), Qt::AlignCenter,pointList3.at(3).first);
//            pt4.end();
//            painter.drawPixmap(px4-75, py4-75, 100, 100, pix4);

            painter.drawPoint(QPointF(px4,py4));
            painter.setPen(QPen(QBrush(QColor(255,100,100)), 3, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum4 = 0;
            for (int i=0;i<length-1;i++) {
                if((uav4[i].x()!=0||uav4[i].y()!=0)&&(uav4[i+1].x()!=0||uav4[i+1].y()!=0)){
                    double a1 = w + ((uav4[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((uav4[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((uav4[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((uav4[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum4++;
                }
            }
//            qDebug()<<"sum4="<<sum4;

            double chax = pointList4.at(3).second.x()-pointList3.at(3).second.x();
            double chay = pointList4.at(3).second.y()-pointList3.at(3).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(QBrush(QColor(255,100,100)), 5, Qt::SolidLine, Qt::RoundCap));
                double x32 = w + ((pointList4.at(3).second.x() - w) * ratio) + ofx;
                double y32 = h + ((pointList4.at(3).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x32,y32));
                    for (int i = 0;i<length-2;i++) {
                        uav4[i+1] = QPoint(0,0);
                    }
                }else{
                    double x33 = x32 - l * cos(atan2((y32 - y31) , (x32 - px4)) - a);//计算箭头的终点（x3,y3）
                    double y33 = y32 - l * sin(atan2((y32 - y31) , (x32 - px4)) - a);
                    double x34 = x32 - l * sin(atan2((x32 - x31) , (y32 - py4)) - a);//计算箭头的终点（x4,y4）
                    double y34 = y32 - l * cos(atan2((x32 - x31) , (y32 - py4)) - a);
                    painter.drawLine(x32,y32,x33,y33);    //绘制箭头(x2,y2,x3,y3)
                    painter.drawLine(x32,y32,x34,y34);   //绘制箭头(x2,y2,x4,y4)
                    painter.drawLine(px4,py4,x32,y32);   //绘制主干箭头(begin,end)
                }
            }
        }
        //侦察机的轨迹
        if(pointList3.size()>0){
            painter.setPen(QPen(Qt::cyan, 20, Qt::SolidLine, Qt::RoundCap));

            double x1 = pointList3.at(4).second.x();
            double y1 = pointList3.at(4).second.y();
            x1 = w + ((x1 - w) * ratio) + ofx;
            y1 = h + ((y1 - h) * ratio) + ofy;

            painter.drawPoint(QPointF(x1,y1));
            painter.setPen(QPen(Qt::cyan, 5, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum5 = 0;
            for (int i=0;i<length-1;i++) {
                if((monitor[i].x()!=0||monitor[i].y()!=0)&&(monitor[i+1].x()!=0||monitor[i+1].y()!=0)){
                    double a1 = w + ((monitor[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((monitor[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((monitor[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((monitor[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum5++;
                }
            }
//            qDebug()<<"sum5="<<sum5;
            double chax = pointList4.at(4).second.x()-pointList3.at(4).second.x();
            double chay = pointList4.at(4).second.y()-pointList3.at(4).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::cyan, 5, Qt::SolidLine, Qt::RoundCap));
                double x34 = w + ((pointList3.at(4).second.x() - w) * ratio) + ofx;
                double y34 = h + ((pointList3.at(4).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x34,y34));
                    for (int i = 0;i<length-2;i++) {
                        monitor[i+1] = QPoint(0,0);
                    }
                }
            }
          }

        //敌机的轨迹
        if(pointList4.size()>0){
            painter.setPen(QPen(Qt::black, 20, Qt::SolidLine, Qt::RoundCap));

            double x1 = pointList4.at(4).second.x();
            double y1 = pointList4.at(4).second.y();
            x1 = w + ((x1 - w) * ratio) + ofx;
            y1 = h + ((y1 - h) * ratio) + ofy;

            painter.drawPoint(QPointF(x1,y1));
            painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
            //绘制轨迹
            int sum6 = 0;
            for (int i=0;i<length-1;i++) {
                if((drone[i].x()!=0||drone[i].y()!=0)&&(drone[i+1].x()!=0||drone[i+1].y()!=0)){
                    double a1 = w + ((drone[i].x() - w) * ratio) + ofx;
                    double a2 = w + ((drone[i+1].x() - w) * ratio) + ofx;
                    double b1 = h + ((drone[i].y() - h) * ratio) + ofy;
                    double b2 = h + ((drone[i+1].y() - h) * ratio) + ofy;
                    painter.drawLine(QPointF(a1,b1),QPointF(a2,b2));
                    sum6++;
                }
            }
//            qDebug()<<"sum6="<<sum6;
            double chax = pointList4.at(4).second.x()-pointList3.at(4).second.x();
            double chay = pointList4.at(4).second.y()-pointList3.at(4).second.y();
            if(pointList4.size()>0){
                painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
                double x35 = w + ((pointList4.at(4).second.x() - w) * ratio) + ofx;
                double y35 = h + ((pointList4.at(4).second.y() - h) * ratio) + ofy;
                if(abs(chax)<5&&abs(chay)<5){
                    painter.drawPoint(QPointF(x35,y35));
                    for (int i = 0;i<length-2;i++) {
                        drone[i+1] = QPoint(0,0);
                    }
                }
            }
          }
    }

//    if(action == MapWidget::Shrink || action == MapWidget::Amplification ||
//            action == MapWidget::Move || action == MapWidget::None)
//    {
// //        qDebug()<<"进来jiu分支了";
//        //共有部分
//        action = MapWidget::None;
//        int newW = 1920 * ratio;
//        int newH = 1050 * ratio;
//        QPixmap tmpPix = pix.scaled(newW,newH,Qt::IgnoreAspectRatio,Qt::FastTransformation);
//        QPainter painter(this);

//        int x = (newW - 1920)/2 - Alloffset.x();
//        if(x < 0){
//            x = 0;
//        }
//        if(x > newW - 1920){
//            x = newW -  1920;
//        }
//        int y = (newH - 1050)/2 - Alloffset.y();
//        if(y < 0){
//            y = 0;
//        }
//        if(y > newH - 1050){
//            y = newH -  1050;
//        }
//        painter.drawTiledPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix,x,y);
//        QPen pen;
//        pen.setWidth(3);
//        pen.setColor(QColor(4,176,238));
//        pen.setStyle(Qt::SolidLine);
//        painter.setPen(pen);
//        painter.drawRect(0,0,1917,1047);
//    }else

        if(action == MapWidget::Large)
      {
         // qDebug()<<"进来xin分支了,";
          //共有部分
          QPixmap tmpPix = pix.scaled(480,263,Qt::IgnoreAspectRatio,Qt::FastTransformation);
          QPainter painter(this);
          painter.drawPixmap(3,3,tmpPix.width()-6,tmpPix.height()-6,tmpPix);
          QPen pen;
          pen.setWidth(3);
          pen.setColor(QColor(4,176,238));
          pen.setStyle(Qt::SolidLine);
          painter.setPen(pen);
          painter.drawRect(0,0,480,263);
          if(pointList3.size()>0){
              painter.setPen(QPen(Qt::red, 7, Qt::SolidLine, Qt::RoundCap));
              painter.drawPoint(QPointF(pointList3.at(0).second.x()/4,pointList3.at(0).second.y()/4));
              painter.setPen(QPen(Qt::darkRed, 7, Qt::SolidLine, Qt::RoundCap));
              painter.drawPoint(QPointF(pointList3.at(1).second.x()/4,pointList3.at(1).second.y()/4));
              painter.setPen(QPen(Qt::magenta, 7, Qt::SolidLine, Qt::RoundCap));
              painter.drawPoint(QPointF(pointList3.at(2).second.x()/4,pointList3.at(2).second.y()/4));
              painter.setPen(QPen(Qt::darkMagenta, 7, Qt::SolidLine, Qt::RoundCap));
              painter.drawPoint(QPointF(pointList3.at(3).second.x()/4,pointList3.at(3).second.y()/4));
          }
      }
}

void MapWidget::setAction(int value)
{
   // qDebug() << "setAction!";
    this->action = value;
    if(action == MapWidget::Shrink)
    {
     //   qDebug() << "shrink map!";
        ratio -= 0.02 * ratio;
        if(ratio < 1.0)
        {
            ratio = 1.0;
        }
    }
    else if(action == MapWidget::Amplification)
    {
      //  qDebug() << "enlarge map!";
        ratio += 0.02 * ratio;
        if(ratio > maxRatio)
        {
            ratio = maxRatio;
        }
    }
    else if(action == MapWidget::His)
    {
        action = MapWidget::None;
        image = QImage(":/Image/map2.png");

        pix = pix.fromImage(image);
        maxRatio = pix.width()/1920 < pix.height()/1050 ? pix.width()/1920 : pix.height()/1050;
        ratio =  (maxRatio + 1.0)/2;
    //    maxRatio = 2;
    //    ratio = 1.5;
        pressed = false;

        px1 = 0;
        px2 = 0;
        px3 = 0;
        px4 = 0;
        py1 = 0;
        py2 = 0;
        py3 = 0;
        py4 = 0;

        //开启定时器
        startTimer(1000);

      //  qDebug()<<"maxRatio"<<maxRatio<<",ratio"<<ratio;

        //this->setMouseTracking(true);

        for (int i=0;i<length;i++) {
            uav1[i] = QPoint(0,0);
            uav2[i] = QPoint(0,0);
            uav3[i] = QPoint(0,0);
            uav4[i] = QPoint(0,0);
            monitor[i] = QPoint(0,0);
            drone[i] = QPoint(0,0);
        }
    }
    else if(action == MapWidget::Move)
    {
     //   qDebug() << "move map!";
        int offsetX = Alloffset.x() + offset.x();
        Alloffset.setX(offsetX);
        int offsetY = Alloffset.y() + offset.y();
        Alloffset.setY(offsetY);
    }
    if(action == MapWidget::Shrink || action == MapWidget::Amplification ||action == MapWidget::Move || action == MapWidget::None)
    {
        action = MapWidget::all_air;
        this->update();
    }
}

void MapWidget::timerEvent(QTimerEvent *event)
{
    //记录无人机飞行总秒数，根据视频长短设定为不同值进行循环
    timeCount ++;

//    qDebug() << "timeEvent!";
    //动态绘制无人机轨迹，每隔一秒
    if(action == MapWidget::first_air || MapWidget::second_air || MapWidget::third_air || MapWidget::fourth_air
            || MapWidget::fir_sec_air || MapWidget::thi_fou_air || MapWidget::all_air )
        this->update();
}

void MapWidget::setPoint1(QList<QPair<QString,QPoint>> pointList,int find,int first_find)
{
//    qDebug() << "setPoint1!";
    if(pointList.size()>0){
        foreach(auto item,pointList3)
        {
            pointList3.removeOne(item);
        }

        if(first_find == 1){
            for (int i=0;i<length;i++) {
                uav1[i] = QPoint(0,0);
                uav2[i] = QPoint(0,0);
                uav3[i] = QPoint(0,0);
                uav4[i] = QPoint(0,0);
                monitor[i] = QPoint(0,0);
            }
            qDebug() << "找到了!====================================";
        }
        for(int i=0;i<pointList.size();i++){
            QPair<QString,QPoint> p = pointList.at(i);            
            pointList3.append(p);          
            if(i==0&&(p.second.x()!=uav1[0].x()||p.second.y()!=uav1[0].y())){
                for (int i=length-1;i>0;i--) {
                    if(uav1[i-1].x()!=0&&uav1[i-1].y()!=0){
                        uav1[i] = uav1[i-1];
                    }
                }
                uav1[0] = p.second;
            }else if(i==1&&(p.second.x()!=uav2[0].x()||p.second.y()!=uav2[0].y())){
                for (int i=length-1;i>0;i--) {
                    if(uav2[i-1].x()!=0&&uav2[i-1].y()!=0){
                        uav2[i] = uav2[i-1];
                    }
                }
                uav2[0] = p.second;
            }else if(i==2&&(p.second.x()!=uav3[0].x()||p.second.y()!=uav3[0].y())){
                for (int i=length-1;i>0;i--) {
                    if(uav3[i-1].x()!=0&&uav3[i-1].y()!=0){
                        uav3[i] = uav3[i-1];
                    }
                }
                uav3[0] = p.second;
            }else if(i==3&&(p.second.x()!=uav4[0].x()||p.second.y()!=uav4[0].y())){
                for (int i=length-1;i>0;i--) {
                    if(uav4[i-1].x()!=0&&uav4[i-1].y()!=0){
                        uav4[i] = uav4[i-1];
                    }
                }
                uav4[0] = p.second;
            }else if(i==4&&(p.second.x()!=monitor[0].x()||p.second.y()!=monitor[0].y())){
                for (int i=length-1;i>0;i--) {
                    if(monitor[i-1].x()!=0&&monitor[i-1].y()!=0){
                        monitor[i] = monitor[i-1];
                    }
                }
                monitor[0] = p.second;
            }
        }
    }
//    qDebug() << "pointList3="<<pointList3;
//    qDebug() << "uav1=["<<uav1[0]<<","<<uav1[1]<<","<<uav1[2];
//    qDebug() << "uav2=["<<uav2[0]<<","<<uav2[1]<<","<<uav2[2];
//    qDebug() << "uav3=["<<uav3[0]<<","<<uav3[1]<<","<<uav3[2];
//    qDebug() << "uav4=["<<uav4[0]<<","<<uav4[1]<<","<<uav4[2];
}

void MapWidget::setPoint2(QList<QPair<QString,QPoint>> pointList,int find,int uav_state)
{
//    qDebug() << "setPoint2!";

    if(uav_state==1){
        foreach(auto item,pointList4)
        {
            pointList4.removeOne(item);
        }
    }
    if(pointList.size()>0&&find>0){
        foreach(auto item,pointList4)
        {
            pointList4.removeOne(item);
        }
        for(int i=0;i<pointList.size();i++){
            QPair<QString,QPoint> p = pointList.at(i);
            pointList4.append(p);
            if(i==4&&(p.second.x()!=drone[0].x()||p.second.y()!=drone[0].y())){
                for (int i=length-1;i>0;i--) {
                    if(drone[i-1].x()!=0&&drone[i-1].y()!=0){
                        drone[i] = drone[i-1];
                    }
                }
                drone[0] = p.second;
            }
        }
    }
//    qDebug() << "pointList4="<<pointList4;
}
