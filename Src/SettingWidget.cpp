#include "Include/SettingWidget.h"
#include "ui_SettingWidget.h"



SettingWidget::SettingWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
//    this->showMaximized();


//    QPalette pal(this->palette());
//    pal.setColor(QPalette::Background, QColor(199,199,199,255));
//    ui->centralWidget->setAutoFillBackground(true);
//    ui->centralWidget->setPalette(pal);
//    ui->centralWidget->setAttribute(Qt::WA_TranslucentBackground, true);

    //启动定时器,间隔为1s
    startTimer(1000);

    //捕获键盘事件
    this->grabKeyboard();

    ui->jia1->setToolTip("放大");
    ui->all1->setToolTip("全屏");
    ui->jia2->setToolTip("放大");
    ui->all2->setToolTip("全屏");
    ui->jia3->setToolTip("放大");
    ui->all3->setToolTip("全屏");
    ui->jia4->setToolTip("放大");
    ui->all4->setToolTip("全屏");

    ui->UAV1->setVisible(false);
    ui->UAV2->setVisible(false);
    ui->UAV3->setVisible(false);
    ui->UAV4->setVisible(false);


    ui->widget_1->raise();
    ui->widget_2->raise();
    ui->widget_3->raise();
    ui->widget_4->raise();
   // setVideo();
    setImage();
//    connect(this, SIGNAL(setFour()), this, SLOT(recoverFour()));
    //this->setMouseTracking(true);
//    qDebug()<<"setting thread="<<QThread::currentThreadId();

}

void SettingWidget::mousePressEvent(QMouseEvent *event)
{
    QApplication::setOverrideCursor(Qt::OpenHandCursor);
}
void SettingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void SettingWidget::recoverFour()
{
    //复原四窗格
    ui->widget1->setGeometry(0,0,959,539);
    ui->widget2->setGeometry(960,0,959,539);
    ui->widget3->setGeometry(0,540,959,511);
    ui->widget4->setGeometry(960,540,959,511);

    ui->widget_1->setGeometry(120,410,611,61);
    ui->widget_2->setGeometry(120,410,611,61);
    ui->widget_3->setGeometry(120,390,611,61);
    ui->widget_4->setGeometry(120,390,611,61);


    ui->csscBasicWidget->setGeometry(10,50,941,479);
    ui->csscBasicWidget_2->setGeometry(10,50,941,479);
    ui->csscBasicWidget_3->setGeometry(10,50,941,451);
    ui->csscBasicWidget_4->setGeometry(10,50,941,451);

    ui->csscLabel->setGeometry(0,0,941,479);
    ui->csscLabel_2->setGeometry(0,0,941,479);
    ui->csscLabel_3->setGeometry(0,0,941,451);
    ui->csscLabel_4->setGeometry(0,0,941,451);

    ui->csscComboBox->setGeometry(10,10,150,32);
    ui->csscComboBox_2->setGeometry(10,10,150,32);
    ui->csscComboBox_3->setGeometry(10,10,150,32);
    ui->csscComboBox_4->setGeometry(10,10,150,32);

    ui->csscComboBox->setVisible(true);
    ui->csscComboBox_2->setVisible(true);
    ui->csscComboBox_3->setVisible(true);
    ui->csscComboBox_4->setVisible(true);


    ui->jia1->setToolTip("放大");
    ui->all1->setToolTip("全屏");
    ui->jia2->setToolTip("放大");
    ui->all2->setToolTip("全屏");
    ui->jia3->setToolTip("放大");
    ui->all3->setToolTip("全屏");
    ui->jia4->setToolTip("放大");
    ui->all4->setToolTip("全屏");

    ui->jia1->setVisible(true);

    ui->all1->setVisible(true);
    ui->jia2->setVisible(true);

    ui->jia3->setVisible(true);
    ui->all3->setVisible(true);
    ui->all2->setVisible(true);
    ui->jia4->setVisible(true);
    ui->all4->setVisible(true);

    ui->jian1->setEnabled(false);
    ui->jian2->setEnabled(false);
    ui->jian3->setEnabled(false);
    ui->jian4->setEnabled(false);

    ui->jian1->setGeometry(750, 10,40,36);
    ui->jian2->setGeometry(750, 10,40,36);
    ui->jian3->setGeometry(750, 10,40,36);
    ui->jian4->setGeometry(750, 10,40,36);

    ui->jia1->setGeometry(820, 10,40,36);
    ui->all1->setGeometry(890, 10,40,36);
    ui->jia2->setGeometry(820, 10,40,36);
    ui->all2->setGeometry(890, 10,40,36);

    ui->jia3->setGeometry(820, 10,40,36);
    ui->all3->setGeometry(890, 10,40,36);
    ui->jia4->setGeometry(820, 10,40,36);
    ui->all4->setGeometry(890, 10,40,36);

    ui->widget_1->setVisible(true);
    ui->widget_2->setVisible(true);
    ui->widget_3->setVisible(true);
    ui->widget_4->setVisible(true);

    ui->csscGaugeMini_6->setVisible(true);
    ui->csscGaugeMini_7->setVisible(true);
    ui->csscGaugeMini_8->setVisible(true);
    ui->csscGaugeMini_9->setVisible(true);

    ui->weizhi1->setVisible(true);
    ui->weizhi_x->setVisible(true);
    ui->weizhi_y->setVisible(true);
    ui->weizhi_z->setVisible(true);
    ui->sudu1->setVisible(true);
    ui->sudu_x->setVisible(true);
    ui->sudu_y->setVisible(true);
    ui->sudu_z->setVisible(true);

    ui->weizhi2->setVisible(true);
    ui->weizhi_x2->setVisible(true);
    ui->weizhi_y2->setVisible(true);
    ui->weizhi_z2->setVisible(true);
    ui->sudu2->setVisible(true);
    ui->sudu_x2->setVisible(true);
    ui->sudu_y2->setVisible(true);
    ui->sudu_z2->setVisible(true);

    ui->weizhi3->setVisible(true);
    ui->weizhi_x3->setVisible(true);
    ui->weizhi_y3->setVisible(true);
    ui->weizhi_z3->setVisible(true);
    ui->sudu3->setVisible(true);
    ui->sudu_x3->setVisible(true);
    ui->sudu_y3->setVisible(true);
    ui->sudu_z3->setVisible(true);

    ui->weizhi4->setVisible(true);
    ui->weizhi_x4->setVisible(true);
    ui->weizhi_y4->setVisible(true);
    ui->weizhi_z4->setVisible(true);
    ui->sudu4->setVisible(true);
    ui->sudu_x4->setVisible(true);
    ui->sudu_y4->setVisible(true);
    ui->sudu_z4->setVisible(true);

    ui->weizhi1->setGeometry(80,15,71,31);
    ui->weizhi_x->setGeometry(150,15,71,31);
    ui->weizhi_y->setGeometry(210,15,71,31);
    ui->weizhi_z->setGeometry(270,15,71,31);
    ui->sudu1->setGeometry(350,15,71,31);
    ui->sudu_x->setGeometry(420,15,71,31);
    ui->sudu_y->setGeometry(480,15,71,31);
    ui->sudu_z->setGeometry(540,15,71,31);

    ui->weizhi2->setGeometry(80,15,71,31);
    ui->weizhi_x2->setGeometry(150,15,71,31);
    ui->weizhi_y2->setGeometry(210,15,71,31);
    ui->weizhi_z2->setGeometry(270,15,71,31);
    ui->sudu2->setGeometry(350,15,71,31);
    ui->sudu_x2->setGeometry(420,15,71,31);
    ui->sudu_y2->setGeometry(480,15,71,31);
    ui->sudu_z2->setGeometry(540,15,71,31);

    ui->weizhi3->setGeometry(80,15,71,31);
    ui->weizhi_x3->setGeometry(150,15,71,31);
    ui->weizhi_y3->setGeometry(210,15,71,31);
    ui->weizhi_z3->setGeometry(270,15,71,31);
    ui->sudu3->setGeometry(350,15,71,31);
    ui->sudu_x3->setGeometry(420,15,71,31);
    ui->sudu_y3->setGeometry(480,15,71,31);
    ui->sudu_z3->setGeometry(540,15,71,31);

    ui->weizhi4->setGeometry(80,15,71,31);
    ui->weizhi_x4->setGeometry(150,15,71,31);
    ui->weizhi_y4->setGeometry(210,15,71,31);
    ui->weizhi_z4->setGeometry(270,15,71,31);
    ui->sudu4->setGeometry(350,15,71,31);
    ui->sudu_x4->setGeometry(420,15,71,31);
    ui->sudu_y4->setGeometry(480,15,71,31);
    ui->sudu_z4->setGeometry(540,15,71,31);

    ui->UAV1->setVisible(false);
    ui->UAV2->setVisible(false);
    ui->UAV3->setVisible(false);
    ui->UAV4->setVisible(false);


}

void SettingWidget::keyPressEvent(QKeyEvent *keyset)
{
    //当按下Esc时，退出全屏或放大屏状态
    if(keyset->key() == Qt::Key_Escape)
    {
        recoverFour();
    }
}

//判断无人机视频放大还是全屏（因为对应相同的手势）
void SettingWidget::enlargeOrFull(int airID)
{
    if(airID == 1)
    {
        if(ui->widget1->width() == 959){
            on_jia1_clicked();
        }
        else {
            on_all1_clicked();
        }
    }
    else if (airID == 2) {
        if(ui->widget2->width() == 959){
            on_jia2_clicked();
        }
        else {
            on_all2_clicked();
        }
    }
    else if (airID == 3) {
        if(ui->widget3->width() == 959){
            on_jia3_clicked();
        }
        else {
            on_all3_clicked();
        }
    }
    else {
        if(ui->widget4->width() == 959){
            on_jia4_clicked();
        }
        else {
            on_all4_clicked();
        }
    }
}

void SettingWidget::recoverFour1(int airID){
    if(airID == 1)
    {
//        qDebug()<<"ui->widget1->width()="<<ui->widget1->width();
//        qDebug()<<"this->frameGeometry().width()="<<this->frameGeometry().width();
        if(ui->widget1->width() == this->frameGeometry().width()){
            on_jia1_clicked();
        }
        else {
            recoverFour();
        }
    }
    else if (airID == 2) {
        if(ui->widget2->width() == this->frameGeometry().width()){
            on_jia2_clicked();
        }
        else {
            recoverFour();
        }
    }
    else if (airID == 3) {
        if(ui->widget3->width() == this->frameGeometry().width()){
            on_jia3_clicked();
        }
        else {
            recoverFour();
        }
    }
    else {
        if(ui->widget4->width() == this->frameGeometry().width()){
            on_jia4_clicked();
        }
        else {
            recoverFour();
        }
    }
}


//void SettingWidget::setVideo()
//{
//    //设置视频
//    player1 = new QMediaPlayer();
//    videoWidget1 = new QVideoWidget(this);
//    videoWidget1->setAspectRatioMode(Qt::IgnoreAspectRatio);

//    QVBoxLayout *hlay = new QVBoxLayout(this);
//    hlay->addWidget(videoWidget1);
//    ui->csscBasicWidget->setLayout(hlay);

//    mediaList1 = new QMediaPlaylist;

//    //第一个视频
//    //mediaList1->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\one.mp4"));
//    mediaList1->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\Image\\1.jpg"));
//    //mediaList1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    mediaList1->setCurrentIndex(0);
//    player1->setPlaylist(mediaList1);

//    player1->setVideoOutput(videoWidget1);
//    videoWidget1->show();


//    //第二个视频
//    player2 = new QMediaPlayer;
//    videoWidget2 = new QVideoWidget;
//    mediaList2 = new QMediaPlaylist;

// //    player2->setMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\second.mp4"));
//   // mediaList2->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\two.mp4"));
//    mediaList2->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\Image\\2.jpg"));
//    //mediaList2->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    mediaList2->setCurrentIndex(0);
//    player2->setPlaylist(mediaList2);

//    player2->setVideoOutput(videoWidget2);
//    videoWidget2->setAspectRatioMode(Qt::IgnoreAspectRatio);

//    QHBoxLayout *hlay2 = new QHBoxLayout(this);
//    hlay2->addWidget(videoWidget2);
//    ui->csscBasicWidget_2->setLayout(hlay2);
//    videoWidget2->show();

//    //第三个视频
//    player3 = new QMediaPlayer;
//    videoWidget3 = new QVideoWidget;
//    mediaList3 = new QMediaPlaylist;

// //    player3->setMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\third.mp4"));
//    //mediaList3->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\three.mp4"));
//    mediaList3->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\Image\\3.png"));
//   // mediaList3->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    mediaList3->setCurrentIndex(0);
//    player3->setPlaylist(mediaList3);

//    player3->setVideoOutput(videoWidget3);
//    videoWidget3->setAspectRatioMode(Qt::IgnoreAspectRatio);

//    QHBoxLayout *hlay3 = new QHBoxLayout(this);
//    hlay3->addWidget(videoWidget3);
//    ui->csscBasicWidget_3->setLayout(hlay3);

//    videoWidget3->show();

//    //第四个视频
//    player4 = new QMediaPlayer;
//    videoWidget4 = new QVideoWidget;
//    mediaList4 = new QMediaPlaylist;

// //    player4->setMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\fourth.mp4"));
//    //mediaList4->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\video\\four.mp4"));
//    mediaList4->addMedia(QUrl::fromLocalFile("D:\\UAVCS-update\\Image\\4.jpg"));
//    //mediaList4->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    mediaList4->setCurrentIndex(0);
//    player4->setPlaylist(mediaList4);

//    player4->setVideoOutput(videoWidget4);
//    videoWidget4->setAspectRatioMode(Qt::IgnoreAspectRatio);

//    QHBoxLayout *hlay4 = new QHBoxLayout(this);
//    hlay4->addWidget(videoWidget4);
//    ui->csscBasicWidget_4->setLayout(hlay4);

//    videoWidget4->show();

//    player1->play();
//    player2->play();
//    player3->play();
//    player4->play();

//    QSize size = ui->csscBasicWidget->size();
//    qDebug() <<"size="<< size.isEmpty()<<size.isNull();
//    QImage uavImg = QImage(":/Image/1.jpg");
//    qDebug() <<"uavImg.width()="<< uavImg.width();
//    QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
//    qDebug() <<"uavPixmap.width()="<< uavPixmap.width();

//    QSize size2 = ui->csscBasicWidget_2->size();
//    QImage uavImg2 = QImage(":/Image/2.jpg");
//    QPixmap uavPixmap2 = QPixmap::fromImage(uavImg.scaled(size2,Qt::IgnoreAspectRatio));
//    ui->csscBasicWidget_2->setBgPixmap(uavPixmap2);

//    QSize size3 = ui->csscBasicWidget_3->size();
//    QImage uavImg3 = QImage(":/Image/3.png");
//    QPixmap uavPixmap3 = QPixmap::fromImage(uavImg.scaled(size3,Qt::IgnoreAspectRatio));
//    ui->csscBasicWidget_3->setBgPixmap(uavPixmap3);

//    QSize size4 = ui->csscBasicWidget_4->size();
//    QImage uavImg4 = QImage(":/Image/4.jpg");
//    QPixmap uavPixmap4 = QPixmap::fromImage(uavImg.scaled(size4,Qt::IgnoreAspectRatio));
//    ui->csscBasicWidget_4->setBgPixmap(uavPixmap4);


//    emit zmq_deliver(2,0);
//    emit zmq_deliver(2,1);
//    emit zmq_deliver(2,2);
//    emit zmq_deliver(2,3);
//}

//void SettingWidget::setImage(QPixmap pixmap,int index){

//}
void SettingWidget::setImage(){

        QSize size = ui->csscBasicWidget->size();
        QImage uavImg = QImage(":/Image/1.jpg");
        QPixmap uavPixmap = QPixmap::fromImage(uavImg.scaled(size,Qt::IgnoreAspectRatio));
        ui->csscLabel->setPixmap(uavPixmap);

        QSize size2 = ui->csscBasicWidget_2->size();
        QImage uavImg2 = QImage(":/Image/2.jpg");
        QPixmap uavPixmap2 = QPixmap::fromImage(uavImg2.scaled(size2,Qt::IgnoreAspectRatio));
        ui->csscLabel_2->setPixmap(uavPixmap2);

        QSize size3 = ui->csscBasicWidget_3->size();
        QImage uavImg3 = QImage(":/Image/3.png");
        QPixmap uavPixmap3 = QPixmap::fromImage(uavImg3.scaled(size3,Qt::IgnoreAspectRatio));
        ui->csscLabel_3->setPixmap(uavPixmap3);

        QSize size4 = ui->csscBasicWidget_4->size();
        QImage uavImg4 = QImage(":/Image/4.jpg");
        QPixmap uavPixmap4 = QPixmap::fromImage(uavImg4.scaled(size4,Qt::IgnoreAspectRatio));
        ui->csscLabel_4->setPixmap(uavPixmap4);

}
SettingWidget::~SettingWidget()
{
    delete ui;
}


//重写定时器事件
void SettingWidget::timerEvent(QTimerEvent *)
{
    //定义静态局部对象time，定义一次，多次调用
//    static double circle_2[15] = {10.00,15.14,20.38,25.34,0.00,0.00,40.25,45.68,50.96,
//                                   0.00,0.00,43.37,32.89,23.54,14.35};
//    static int num = -1;
//    static int lastSudu = 0;
//    static int sudu[15] = {10,15,20,25,30,30,40,45,50,55,50,45,35,25,15};
//    static int haiba[15] = {10,15,15,25,30,35,35,35,32,27,24,26,28,23,15};
//    //最大变化幅度：两分钟0.01值变
//    static double jingdu[15] = {124.471670, 124.471970,124.472670,124.473670,124.474670,124.474970, 124.475670,
//                               124.475980,124.476670,124.476970,124.477670,124.477970,124.478670,124.478970, 124.479670};
//    static double weidu[15] = {23.261940,23.262340,23.262740,23.263540,23.264940,23.265340,23.265740,
//                              23.265940,23.266540,23.267440,23.267940,23.268340,23.268740,23.269040, 23.269940};

//    num++;

//    //其余部件值随着时间波动
//        if(G_add2 == true)
//        {
//            player1->setPlaybackRate(1.5);
//            lastSudu = lastSudu + 1;
//            ui->sudu->setText(QString::number(lastSudu));
//        }
//        else if (G_jian2 == true)
//        {
//            player1->setPlaybackRate(0.5);
//            lastSudu = lastSudu - 1;
//            ui->sudu->setText(QString::number(lastSudu));
//        }

//        else
//        {
//            自由飞行模式
//            player1->setPlaybackRate(1.0);
//            lastSudu = sudu[num%15];
//            ui->sudu->setText(QString::number(lastSudu));
//        }

//    ui->sudu_x->setText(QString::number(haiba[num%15]));
//    ui->sudu_y->setText(QString::number(haiba[num%15]));
//    ui->sudu_z->setText(QString::number(haiba[num%15]));

//    ui->weizhi_x->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_y->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_z->setText(QString::number(jingdu[num%15]));

//    ui->angle_x->setText(QString::number(weidu[num%15])) ;
//    ui->angle_y->setText(QString::number(weidu[num%15])) ;
//    ui->angle_z->setText(QString::number(weidu[num%15])) ;

//    //无人机2
//    ui->sudu_x2->setText(QString::number(haiba[num%15])+3);
//    ui->sudu_y2->setText(QString::number(haiba[num%15])+1.8);
//    ui->sudu_z2->setText(QString::number(haiba[num%15])+1.2);

//    ui->weizhi_x2->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_y2->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_z2->setText(QString::number(jingdu[num%15])+0.1);

//    ui->angle_x2->setText(QString::number(weidu[num%15])+1) ;
//    ui->angle_y2->setText(QString::number(weidu[num%15])+2) ;
//    ui->angle_z2->setText(QString::number(weidu[num%15])+3) ;
//   // ui->gaodu2->setText(QString::number(haiba[num%15]+3));
// //    ui->sudu2->setText(QString::number(sudu[num%15]-2));
// //    ui->jingdu2->setText(QString::number(jingdu[num%15]+1.2));
// //    ui->weidu2->setText(QString::number(weidu[num%15]-2.3)) ;

//    //无人机3
//    ui->sudu_x3->setText(QString::number(haiba[num%15])+9);
//    ui->sudu_y3->setText(QString::number(haiba[num%15])+1.2);
//    ui->sudu_z3->setText(QString::number(haiba[num%15])+1.4);

//    ui->weizhi_x3->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_y3->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_z3->setText(QString::number(jingdu[num%15])+0.7);

//    ui->angle_x3->setText(QString::number(weidu[num%15])+8) ;
//    ui->angle_y3->setText(QString::number(weidu[num%15])+7) ;
//    ui->angle_z3->setText(QString::number(weidu[num%15])+6) ;
//    //ui->gaodu3->setText(QString::number(haiba[num%15]+2));
// //    ui->sudu3->setText(QString::number(sudu[num%15]+5));
// //    ui->jingdu3->setText(QString::number(jingdu[num%15]-2.1));
// //    ui->weidu3->setText(QString::number(weidu[num%15]+1.4)) ;

//    //无人机4
//    ui->sudu_x4->setText(QString::number(haiba[num%15])+3.3);
//    ui->sudu_y4->setText(QString::number(haiba[num%15])+1.2);
//    ui->sudu_z4->setText(QString::number(haiba[num%15])+1.1);

//    ui->weizhi_x4->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_y4->setText(QString::number(jingdu[num%15]));
//    ui->weizhi_z4->setText(QString::number(jingdu[num%15])+0.7);

//    ui->angle_x4->setText(QString::number(weidu[num%15])+4) ;
//    ui->angle_y4->setText(QString::number(weidu[num%15])+3) ;
//    ui->angle_z4->setText(QString::number(weidu[num%15])+2) ;
//   // ui->gaodu4->setText(QString::number(haiba[num%15]-6));
// //    ui->sudu4->setText(QString::number(sudu[num%15]-6));
// //    ui->jingdu4->setText(QString::number(jingdu[num%15]+1.6));
// //    ui->weidu4->setText(QString::number(weidu[num%15]-1.2)) ;
}

void SettingWidget::show_all(int index){
    switch (index)
    {
        case 1:
            on_all1_clicked();
            break;
        case 2:
            on_all2_clicked();
            break;
        case 3:
            on_all3_clicked();
            break;
        case 4:
            on_all4_clicked();
            break;
        case 5:
            recoverFour();
            break;
        case 6:
            recoverFour();
            break;
        case 7:
            recoverFour();
            break;
        }
}

void SettingWidget::on_all1_clicked()
{
    //实现第一个无人机视频全屏功能
    ui->widget1->setGeometry(this->frameGeometry().x(), this->frameGeometry().y(),
                             this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscLabel->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscBasicWidget->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
    //ui->widget_1->setGeometry(610, 950, 681, 61);
    ui->widget_1->setGeometry(520,950,900,61);
    ui->csscGaugeMini_6->setVisible(true);
    ui->weizhi1->setGeometry(80,15,71,31);
    ui->weizhi_x->setGeometry(180,15,71,31);
    ui->weizhi_y->setGeometry(280,15,71,31);
    ui->weizhi_z->setGeometry(380,15,71,31);
    ui->sudu1->setGeometry(500,15,71,31);
    ui->sudu_x->setGeometry(600,15,71,31);
    ui->sudu_y->setGeometry(700,15,71,31);
    ui->sudu_z->setGeometry(800,15,71,31);
    ui->widget1->raise();

//    QPixmap pixmap = ui->csscLabel->pixmap();
//    QSize size = ui->csscBasicWidget->size();
//    QPixmap uavPixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio);
//    ui->csscLabel->setPixmap(uavPixmap);

    ui->jia1->setVisible(true);
    ui->jia1->setGeometry(1770,10,40,36);
    ui->jian1->setVisible(true);
    ui->jian1->setEnabled(true);
    ui->jian1->setGeometry(1840,10,40,36);
    ui->all1->setVisible(false);



    ui->widget_2->setVisible(false);
    ui->widget_3->setVisible(false);
    ui->widget_4->setVisible(false);
//    ui->weizhi2->setVisible(false);
//    ui->weizhi_x2->setVisible(false);
//    ui->weizhi_y2->setVisible(false);
//    ui->weizhi_z2->setVisible(false);
//    ui->sudu2->setVisible(false);
//    ui->sudu_x2->setVisible(false);
//    ui->sudu_y2->setVisible(false);
//    ui->sudu_z2->setVisible(false);

//    ui->weizhi3->setVisible(false);
//    ui->weizhi_x3->setVisible(false);
//    ui->weizhi_y3->setVisible(false);
//    ui->weizhi_z3->setVisible(false);
//    ui->sudu3->setVisible(false);
//    ui->sudu_x3->setVisible(false);
//    ui->sudu_y3->setVisible(false);
//    ui->sudu_z3->setVisible(false);

//    ui->weizhi4->setVisible(false);
//    ui->weizhi_x4->setVisible(false);
//    ui->weizhi_y4->setVisible(false);
//    ui->weizhi_z4->setVisible(false);
//    ui->sudu4->setVisible(false);
//    ui->sudu_x4->setVisible(false);
//    ui->sudu_y4->setVisible(false);
//    ui->sudu_z4->setVisible(false);

    ui->jian1->setToolTip("四窗格");
    ui->jia1->setToolTip("退出全屏");
    ui->jian2->setToolTip("四窗格");
    ui->jia2->setToolTip("退出全屏");
    ui->jian3->setToolTip("四窗格");
    ui->jia3->setToolTip("退出全屏");
    ui->jian4->setToolTip("四窗格");
    ui->jia4->setToolTip("退出全屏");

    ui->UAV1->setGeometry(820,30,280,60);
    ui->UAV1->setVisible(true);
    ui->UAV2->setVisible(false);
    ui->UAV3->setVisible(false);
    ui->UAV4->setVisible(false);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

}

void SettingWidget::on_all2_clicked()
{
    //实现第2个无人机视频全屏功能
    ui->widget2->setGeometry(this->frameGeometry().x(), this->frameGeometry().y(),
                             this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscLabel_2->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscBasicWidget_2->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
   // ui->widget_2->setGeometry(610, 950, 681, 61);
    ui->widget2->raise();

    ui->jia2->setVisible(true);
    ui->jia2->setGeometry(1770,10,40,36);
    ui->jian2->setVisible(true);
    ui->jian2->setEnabled(true);
    ui->jian2->setGeometry(1840,10,40,36);
    ui->all2->setVisible(false);

//    ui->weizhi1->setVisible(false);
//    ui->weizhi_x->setVisible(false);
//    ui->weizhi_y->setVisible(false);
//    ui->weizhi_z->setVisible(false);
//    ui->sudu1->setVisible(false);
//    ui->sudu_x->setVisible(false);
//    ui->sudu_y->setVisible(false);
//    ui->sudu_z->setVisible(false);
    ui->widget_2->setVisible(true);
    ui->csscGaugeMini_7->setVisible(true);
    ui->widget_2->setGeometry(520,950,900,61);
    ui->weizhi2->setGeometry(80,15,71,31);
    ui->weizhi_x2->setGeometry(180,15,71,31);
    ui->weizhi_y2->setGeometry(280,15,71,31);
    ui->weizhi_z2->setGeometry(380,15,71,31);
    ui->sudu2->setGeometry(500,15,71,31);
    ui->sudu_x2->setGeometry(600,15,71,31);
    ui->sudu_y2->setGeometry(700,15,71,31);
    ui->sudu_z2->setGeometry(800,15,71,31);

    ui->widget_1->setVisible(false);
    ui->widget_3->setVisible(false);
    ui->widget_4->setVisible(false);

//    ui->weizhi3->setVisible(false);
//    ui->weizhi_x3->setVisible(false);
//    ui->weizhi_y3->setVisible(false);
//    ui->weizhi_z3->setVisible(false);
//    ui->sudu3->setVisible(false);
//    ui->sudu_x3->setVisible(false);
//    ui->sudu_y3->setVisible(false);
//    ui->sudu_z3->setVisible(false);

//    ui->weizhi4->setVisible(false);
//    ui->weizhi_x4->setVisible(false);
//    ui->weizhi_y4->setVisible(false);
//    ui->weizhi_z4->setVisible(false);
//    ui->sudu4->setVisible(false);
//    ui->sudu_x4->setVisible(false);
//    ui->sudu_y4->setVisible(false);
//    ui->sudu_z4->setVisible(false);

    ui->jian1->setToolTip("四窗格");
    ui->jia1->setToolTip("退出全屏");
    ui->jian2->setToolTip("四窗格");
    ui->jia2->setToolTip("退出全屏");
    ui->jian3->setToolTip("四窗格");
    ui->jia3->setToolTip("退出全屏");
    ui->jian4->setToolTip("四窗格");
    ui->jia4->setToolTip("退出全屏");

    ui->UAV2->setGeometry(820,30,280,60);
    ui->UAV2->setVisible(true);
    ui->UAV1->setVisible(false);
    ui->UAV3->setVisible(false);
    ui->UAV4->setVisible(false);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

}

void SettingWidget::on_all3_clicked()
{
     //实现第3个无人机视频全屏功能
    ui->widget3->setGeometry(this->frameGeometry().x(), this->frameGeometry().y(),
                             this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscLabel_3->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscBasicWidget_3->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
   // ui->widget_3->setGeometry(610, 950, 681, 61);
    ui->widget3->raise();

    ui->jia3->setVisible(true);
    ui->jia3->setGeometry(1770,10,40,36);
    ui->jian3->setVisible(true);
    ui->jian3->setEnabled(true);
    ui->jian3->setGeometry(1840,10,40,36);
    ui->all3->setVisible(false);

//    ui->weizhi1->setVisible(false);
//    ui->weizhi_x->setVisible(false);
//    ui->weizhi_y->setVisible(false);
//    ui->weizhi_z->setVisible(false);
//    ui->sudu1->setVisible(false);
//    ui->sudu_x->setVisible(false);
//    ui->sudu_y->setVisible(false);
//    ui->sudu_z->setVisible(false);

//    ui->weizhi2->setVisible(false);
//    ui->weizhi_x2->setVisible(false);
//    ui->weizhi_y2->setVisible(false);
//    ui->weizhi_z2->setVisible(false);
//    ui->sudu2->setVisible(false);
//    ui->sudu_x2->setVisible(false);
//    ui->sudu_y2->setVisible(false);
//    ui->sudu_z2->setVisible(false);

    ui->widget_3->setVisible(true);
    ui->csscGaugeMini_8->setVisible(true);
    ui->widget_3->setGeometry(520,950,900,61);
    ui->weizhi3->setGeometry(80,15,71,31);
    ui->weizhi_x3->setGeometry(180,15,71,31);
    ui->weizhi_y3->setGeometry(280,15,71,31);
    ui->weizhi_z3->setGeometry(380,15,71,31);
    ui->sudu3->setGeometry(500,15,71,31);
    ui->sudu_x3->setGeometry(600,15,71,31);
    ui->sudu_y3->setGeometry(700,15,71,31);
    ui->sudu_z3->setGeometry(800,15,71,31);

    ui->widget_1->setVisible(false);
    ui->widget_2->setVisible(false);
    ui->widget_4->setVisible(false);


//    ui->weizhi4->setVisible(false);
//    ui->weizhi_x4->setVisible(false);
//    ui->weizhi_y4->setVisible(false);
//    ui->weizhi_z4->setVisible(false);
//    ui->sudu4->setVisible(false);
//    ui->sudu_x4->setVisible(false);
//    ui->sudu_y4->setVisible(false);
//    ui->sudu_z4->setVisible(false);

    ui->jian1->setToolTip("四窗格");
    ui->jia1->setToolTip("退出全屏");
    ui->jian2->setToolTip("四窗格");
    ui->jia2->setToolTip("退出全屏");
    ui->jian3->setToolTip("四窗格");
    ui->jia3->setToolTip("退出全屏");
    ui->jian4->setToolTip("四窗格");
    ui->jia4->setToolTip("退出全屏");

    ui->UAV3->setGeometry(820,30,280,60);
    ui->UAV3->setVisible(true);
    ui->UAV1->setVisible(false);
    ui->UAV2->setVisible(false);
    ui->UAV4->setVisible(false);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

}

void SettingWidget::on_all4_clicked()
{
     //实现第4个无人机视频全屏功能
    ui->widget4->setGeometry(this->frameGeometry().x(), this->frameGeometry().y(),
                             this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscLabel_4->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
    ui->csscBasicWidget_4->setGeometry(0, 0, this->frameGeometry().width(), this->frameGeometry().height());
   // ui->widget_4->setGeometry(610, 950, 681, 61);
    ui->widget4->raise();

    ui->jia4->setVisible(true);
    ui->jia4->setGeometry(1770,10,40,36);
    ui->jian4->setVisible(true);
    ui->jian4->setEnabled(true);
    ui->jian4->setGeometry(1840,10,40,36);
    ui->all4->setVisible(false);

//    ui->weizhi1->setVisible(false);
//    ui->weizhi_x->setVisible(false);
//    ui->weizhi_y->setVisible(false);
//    ui->weizhi_z->setVisible(false);
//    ui->sudu1->setVisible(false);
//    ui->sudu_x->setVisible(false);
//    ui->sudu_y->setVisible(false);
//    ui->sudu_z->setVisible(false);

//    ui->weizhi2->setVisible(false);
//    ui->weizhi_x2->setVisible(false);
//    ui->weizhi_y2->setVisible(false);
//    ui->weizhi_z2->setVisible(false);
//    ui->sudu2->setVisible(false);
//    ui->sudu_x2->setVisible(false);
//    ui->sudu_y2->setVisible(false);
//    ui->sudu_z2->setVisible(false);

//    ui->weizhi3->setVisible(false);
//    ui->weizhi_x3->setVisible(false);
//    ui->weizhi_y3->setVisible(false);
//    ui->weizhi_z3->setVisible(false);
//    ui->sudu3->setVisible(false);
//    ui->sudu_x3->setVisible(false);
//    ui->sudu_y3->setVisible(false);
//    ui->sudu_z3->setVisible(false);

    ui->widget_1->setVisible(false);
    ui->widget_2->setVisible(false);
    ui->widget_3->setVisible(false);

    ui->widget_4->setVisible(true);
    ui->csscGaugeMini_9->setVisible(true);
    ui->widget_4->setGeometry(520,950,900,61);
    ui->weizhi4->setGeometry(80,15,71,31);
    ui->weizhi_x4->setGeometry(180,15,71,31);
    ui->weizhi_y4->setGeometry(280,15,71,31);
    ui->weizhi_z4->setGeometry(380,15,71,31);
    ui->sudu4->setGeometry(500,15,71,31);
    ui->sudu_x4->setGeometry(600,15,71,31);
    ui->sudu_y4->setGeometry(700,15,71,31);
    ui->sudu_z4->setGeometry(800,15,71,31);

    ui->jian1->setToolTip("四窗格");
    ui->jia1->setToolTip("退出全屏");
    ui->jian2->setToolTip("四窗格");
    ui->jia2->setToolTip("退出全屏");
    ui->jian3->setToolTip("四窗格");
    ui->jia3->setToolTip("退出全屏");
    ui->jian4->setToolTip("四窗格");
    ui->jia4->setToolTip("退出全屏");

    ui->UAV4->setGeometry(820,30,280,60);
    ui->UAV4->setVisible(true);
    ui->UAV1->setVisible(false);
    ui->UAV2->setVisible(false);
    ui->UAV3->setVisible(false);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

}


void SettingWidget::on_jia1_clicked()
{
    //放大无人机1视频监控窗格
    ui->widget1->setGeometry(0, 0, 1300, 1050);
    ui->csscBasicWidget->setGeometry(5, 5, 1287, 1037);
    ui->csscLabel->setGeometry(5, 5, 1287, 1037);

    ui->widget2->setGeometry(1300, 3, 620, 348);
    ui->widget3->setGeometry(1300, 351, 620, 348);
    ui->widget4->setGeometry(1300, 699, 620, 348);

    ui->csscBasicWidget_2->setGeometry(5,5,608,333);
    ui->csscBasicWidget_3->setGeometry(5,5,608,333);
    ui->csscBasicWidget_4->setGeometry(5,5,608,333);

    ui->csscLabel_2->setGeometry(5, 5, 608,333);
    ui->csscLabel_3->setGeometry(5, 5, 608,333);
    ui->csscLabel_4->setGeometry(5, 5, 608,333);

    ui->jia1->setVisible(false);
    ui->jian1->setEnabled(true);
    ui->jian1->setGeometry(1130,10,40,36);
    ui->all1->setVisible(true);
    ui->all1->setGeometry(1200,10,40,36);

    ui->jia2->setVisible(false);
    ui->jian2->setEnabled(true);
    ui->jian2->setGeometry(515,10,40,36);
    ui->all2->setVisible(true);
    ui->all2->setGeometry(565,10,40,36);

    ui->jia3->setVisible(false);
    ui->jian3->setEnabled(true);
    ui->jian3->setGeometry(515,10,40,36);
    ui->all3->setVisible(true);
    ui->all3->setGeometry(565,10,40,36);

    ui->jia4->setVisible(false);
    ui->jian4->setEnabled(true);
    ui->jian4->setGeometry(515,10,40,36);
    ui->all4->setVisible(true);
    ui->all4->setGeometry(565,10,40,36);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

//        ui->csscComboBox->setGeometry(10,20,150,32);
//        ui->csscComboBox_2->setGeometry(10,20,150,32);
//        ui->csscComboBox_3->setGeometry(10,20,150,32);
//        ui->csscComboBox_4->setGeometry(10,20,150,32);

    ui->widget_1->setGeometry(320,970,721,61);
    ui->widget_1->setVisible(true);
    ui->csscGaugeMini_6->setVisible(true);
    ui->weizhi1->setGeometry(80,15,71,31);
    ui->weizhi_x->setGeometry(160,15,71,31);
    ui->weizhi_y->setGeometry(240,15,71,31);
    ui->weizhi_z->setGeometry(320,15,71,31);
    ui->sudu1->setGeometry(410,15,71,31);
    ui->sudu_x->setGeometry(490,15,71,31);
    ui->sudu_y->setGeometry(570,15,71,31);
    ui->sudu_z->setGeometry(650,15,71,31);

    ui->widget_2->setVisible(true);
    ui->widget_2->setGeometry(50,280,511,61);
    ui->csscGaugeMini_7->setVisible(false);
    ui->weizhi2->setGeometry(10,15,71,31);
    ui->weizhi_x2->setGeometry(70,15,71,31);
    ui->weizhi_y2->setGeometry(130,15,71,31);
    ui->weizhi_z2->setGeometry(190,15,71,31);
    ui->sudu2->setGeometry(260,15,71,31);
    ui->sudu_x2->setGeometry(320,15,71,31);
    ui->sudu_y2->setGeometry(380,15,71,31);
    ui->sudu_z2->setGeometry(440,15,71,31);

    ui->widget_3->setVisible(true);
    ui->widget_3->setGeometry(50,280,511,61);
    ui->csscGaugeMini_8->setVisible(false);
    ui->weizhi3->setGeometry(10,15,71,31);
    ui->weizhi_x3->setGeometry(70,15,71,31);
    ui->weizhi_y3->setGeometry(130,15,71,31);
    ui->weizhi_z3->setGeometry(190,15,71,31);
    ui->sudu3->setGeometry(260,15,71,31);
    ui->sudu_x3->setGeometry(320,15,71,31);
    ui->sudu_y3->setGeometry(380,15,71,31);
    ui->sudu_z3->setGeometry(440,15,71,31);

    ui->widget_4->setVisible(true);
    ui->widget_4->setGeometry(50,280,511,61);
    ui->csscGaugeMini_9->setVisible(false);
    ui->weizhi4->setGeometry(10,15,71,31);
    ui->weizhi_x4->setGeometry(70,15,71,31);
    ui->weizhi_y4->setGeometry(130,15,71,31);
    ui->weizhi_z4->setGeometry(190,15,71,31);
    ui->sudu4->setGeometry(260,15,71,31);
    ui->sudu_x4->setGeometry(320,15,71,31);
    ui->sudu_y4->setGeometry(380,15,71,31);
    ui->sudu_z4->setGeometry(440,15,71,31);

    ui->jian1->setToolTip("四窗格");
    ui->all1->setToolTip("全屏");
    ui->jian2->setToolTip("四窗格");
    ui->all2->setToolTip("全屏");
    ui->jian3->setToolTip("四窗格");
    ui->all3->setToolTip("全屏");
    ui->jian4->setToolTip("四窗格");
    ui->all4->setToolTip("全屏");

    ui->UAV1->setGeometry(510,30,280,60);
    ui->UAV2->setGeometry(165,30,280,60);
    ui->UAV3->setGeometry(165,30,280,60);
    ui->UAV4->setGeometry(165,30,280,60);

    ui->UAV1->setVisible(true);
    ui->UAV2->setVisible(true);
    ui->UAV3->setVisible(true);
    ui->UAV4->setVisible(true);

}

void SettingWidget::on_jia2_clicked()
{
    //放大无人机2视频监控窗格
    ui->widget2->setGeometry(0, 0, 1300, 1050);
    ui->csscBasicWidget_2->setGeometry(5, 5,1287, 1037);
    ui->csscLabel_2->setGeometry(5, 5, 1287, 1037);
  //  ui->widget_2->setGeometry(250, 900, 681, 61);

    ui->widget1->setGeometry(1300, 3, 620, 348);
    ui->widget3->setGeometry(1300, 351, 620, 348);
    ui->widget4->setGeometry(1300, 699, 620, 348);

    ui->csscBasicWidget->setGeometry(5,5,608,333);
    ui->csscBasicWidget_3->setGeometry(5,5,608,333);
    ui->csscBasicWidget_4->setGeometry(5,5,608,333);

    ui->csscLabel->setGeometry(5,5,608,333);
    ui->csscLabel_3->setGeometry(5,5,608,333);
    ui->csscLabel_4->setGeometry(5,5,608,333);

    ui->jia2->setVisible(false);
    ui->jian2->setEnabled(true);
    ui->jian2->setGeometry(1130,10,40,36);
    ui->all2->setVisible(true);
    ui->all2->setGeometry(1200,10,40,36);

    ui->jia1->setVisible(false);
    ui->jian1->setEnabled(true);
    ui->jian1->setGeometry(515,10,40,36);
    ui->all1->setVisible(true);
    ui->all1->setGeometry(565,10,40,36);

    ui->jia3->setVisible(false);
    ui->jian3->setEnabled(true);
    ui->jian3->setGeometry(515,10,40,36);
    ui->all3->setVisible(true);
    ui->all3->setGeometry(565,10,40,36);

    ui->jia4->setVisible(false);
    ui->jian4->setEnabled(true);
    ui->jian4->setGeometry(515,10,40,36);
    ui->all4->setVisible(true);
    ui->all4->setGeometry(565,10,40,36);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

//    ui->csscComboBox->setGeometry(10,20,150,32);
//    ui->csscComboBox_2->setGeometry(10,20,150,32);
//    ui->csscComboBox_3->setGeometry(10,20,150,32);
//    ui->csscComboBox_4->setGeometry(10,20,150,32);


    ui->widget_2->setVisible(true);
    ui->widget_2->setGeometry(320,970,721,61);
    ui->csscGaugeMini_7->setVisible(true);
    ui->weizhi2->setGeometry(80,15,71,31);
    ui->weizhi_x2->setGeometry(160,15,71,31);
    ui->weizhi_y2->setGeometry(240,15,71,31);
    ui->weizhi_z2->setGeometry(320,15,71,31);
    ui->sudu2->setGeometry(410,15,71,31);
    ui->sudu_x2->setGeometry(490,15,71,31);
    ui->sudu_y2->setGeometry(570,15,71,31);
    ui->sudu_z2->setGeometry(650,15,71,31);

    ui->widget_1->setVisible(true);
    ui->widget_1->setGeometry(50,280,511,61);
    ui->csscGaugeMini_6->setVisible(false);
    ui->weizhi1->setGeometry(10,15,71,31);
    ui->weizhi_x->setGeometry(70,15,71,31);
    ui->weizhi_y->setGeometry(130,15,71,31);
    ui->weizhi_z->setGeometry(190,15,71,31);
    ui->sudu1->setGeometry(260,15,71,31);
    ui->sudu_x->setGeometry(320,15,71,31);
    ui->sudu_y->setGeometry(380,15,71,31);
    ui->sudu_z->setGeometry(440,15,71,31);

    ui->widget_3->setVisible(true);
    ui->widget_3->setGeometry(50,280,511,61);
    ui->csscGaugeMini_8->setVisible(false);
    ui->weizhi3->setGeometry(10,15,71,31);
    ui->weizhi_x3->setGeometry(70,15,71,31);
    ui->weizhi_y3->setGeometry(130,15,71,31);
    ui->weizhi_z3->setGeometry(190,15,71,31);
    ui->sudu3->setGeometry(260,15,71,31);
    ui->sudu_x3->setGeometry(320,15,71,31);
    ui->sudu_y3->setGeometry(380,15,71,31);
    ui->sudu_z3->setGeometry(440,15,71,31);

    ui->widget_4->setVisible(true);
    ui->widget_4->setGeometry(50,280,511,61);
    ui->csscGaugeMini_9->setVisible(false);
    ui->weizhi4->setGeometry(10,15,71,31);
    ui->weizhi_x4->setGeometry(70,15,71,31);
    ui->weizhi_y4->setGeometry(130,15,71,31);
    ui->weizhi_z4->setGeometry(190,15,71,31);
    ui->sudu4->setGeometry(260,15,71,31);
    ui->sudu_x4->setGeometry(320,15,71,31);
    ui->sudu_y4->setGeometry(380,15,71,31);
    ui->sudu_z4->setGeometry(440,15,71,31);

    ui->jian1->setToolTip("四窗格");
    ui->all1->setToolTip("全屏");
    ui->jian2->setToolTip("四窗格");
    ui->all2->setToolTip("全屏");
    ui->jian3->setToolTip("四窗格");
    ui->all3->setToolTip("全屏");
    ui->jian4->setToolTip("四窗格");
    ui->all4->setToolTip("全屏");

    ui->UAV2->setGeometry(510,30,280,60);
    ui->UAV1->setGeometry(165,30,280,60);
    ui->UAV3->setGeometry(165,30,280,60);
    ui->UAV4->setGeometry(165,30,280,60);

    ui->UAV1->setVisible(true);
    ui->UAV2->setVisible(true);
    ui->UAV3->setVisible(true);
    ui->UAV4->setVisible(true);

}

void SettingWidget::on_jia3_clicked()
{
    //放大无人机3视频监控窗格
    ui->widget3->setGeometry(0, 0, 1300, 1044);
    ui->csscBasicWidget_3->setGeometry(5, 5, 1287, 1037);
    ui->csscLabel_3->setGeometry(5, 5, 1287, 1037);
   // ui->widget_3->setGeometry(250, 900, 681, 61);

    ui->widget1->setGeometry(1300, 3, 620, 348);
    ui->widget2->setGeometry(1300, 351, 620, 348);
    ui->widget4->setGeometry(1300, 699, 620, 348);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

//    ui->csscComboBox->setGeometry(10,20,150,32);
//    ui->csscComboBox_2->setGeometry(10,20,150,32);
//    ui->csscComboBox_3->setGeometry(10,20,150,32);
//    ui->csscComboBox_4->setGeometry(10,20,150,32);

    ui->csscBasicWidget->setGeometry(5,5,608,333);
    ui->csscBasicWidget_2->setGeometry(5,5,608,333);
    ui->csscBasicWidget_4->setGeometry(5,5,608,333);

    ui->csscLabel->setGeometry(5,5,608,333);
    ui->csscLabel_2->setGeometry(5,5,608,333);
    ui->csscLabel_4->setGeometry(5,5,608,333);

    ui->jia3->setVisible(false);
    ui->jian3->setEnabled(true);
    ui->jian3->setGeometry(1130,10,40,36);
    ui->all3->setVisible(true);
    ui->all3->setGeometry(1200,10,40,36);

    ui->jia2->setVisible(false);
    ui->jian2->setEnabled(true);
    ui->jian2->setGeometry(515,10,40,36);
    ui->all2->setVisible(true);
    ui->all2->setGeometry(565,10,40,36);

    ui->jia1->setVisible(false);
    ui->jian1->setEnabled(true);
    ui->jian1->setGeometry(515,10,40,36);
    ui->all1->setVisible(true);
    ui->all1->setGeometry(565,10,40,36);

    ui->jia4->setVisible(false);
    ui->jian4->setEnabled(true);
    ui->jian4->setGeometry(515,10,40,36);
    ui->all4->setVisible(true);
    ui->all4->setGeometry(565,10,40,36);

    ui->widget_3->setVisible(true);
    ui->widget_3->setGeometry(320,970,721,61);
    ui->csscGaugeMini_8->setVisible(true);
    ui->weizhi3->setGeometry(80,15,71,31);
    ui->weizhi_x3->setGeometry(160,15,71,31);
    ui->weizhi_y3->setGeometry(240,15,71,31);
    ui->weizhi_z3->setGeometry(320,15,71,31);
    ui->sudu3->setGeometry(410,15,71,31);
    ui->sudu_x3->setGeometry(490,15,71,31);
    ui->sudu_y3->setGeometry(570,15,71,31);
    ui->sudu_z3->setGeometry(650,15,71,31);

    ui->widget_2->setVisible(true);
    ui->widget_2->setGeometry(50,280,511,61);
    ui->csscGaugeMini_7->setVisible(false);
    ui->weizhi2->setGeometry(10,15,71,31);
    ui->weizhi_x2->setGeometry(70,15,71,31);
    ui->weizhi_y2->setGeometry(130,15,71,31);
    ui->weizhi_z2->setGeometry(190,15,71,31);
    ui->sudu2->setGeometry(260,15,71,31);
    ui->sudu_x2->setGeometry(320,15,71,31);
    ui->sudu_y2->setGeometry(380,15,71,31);
    ui->sudu_z2->setGeometry(440,15,71,31);

    ui->widget_1->setVisible(true);
    ui->widget_1->setGeometry(50,280,511,61);
    ui->csscGaugeMini_6->setVisible(false);
    ui->weizhi1->setGeometry(10,15,71,31);
    ui->weizhi_x->setGeometry(70,15,71,31);
    ui->weizhi_y->setGeometry(130,15,71,31);
    ui->weizhi_z->setGeometry(190,15,71,31);
    ui->sudu1->setGeometry(260,15,71,31);
    ui->sudu_x->setGeometry(320,15,71,31);
    ui->sudu_y->setGeometry(380,15,71,31);
    ui->sudu_z->setGeometry(440,15,71,31);

    ui->widget_4->setVisible(true);
    ui->widget_4->setGeometry(50,280,511,61);
    ui->csscGaugeMini_9->setVisible(false);
    ui->weizhi4->setGeometry(10,15,71,31);
    ui->weizhi_x4->setGeometry(70,15,71,31);
    ui->weizhi_y4->setGeometry(130,15,71,31);
    ui->weizhi_z4->setGeometry(190,15,71,31);
    ui->sudu4->setGeometry(260,15,71,31);
    ui->sudu_x4->setGeometry(320,15,71,31);
    ui->sudu_y4->setGeometry(380,15,71,31);
    ui->sudu_z4->setGeometry(440,15,71,31);


    ui->jian1->setToolTip("四窗格");
    ui->all1->setToolTip("全屏");
    ui->jian2->setToolTip("四窗格");
    ui->all2->setToolTip("全屏");
    ui->jian3->setToolTip("四窗格");
    ui->all3->setToolTip("全屏");
    ui->jian4->setToolTip("四窗格");
    ui->all4->setToolTip("全屏");

    ui->UAV3->setGeometry(510,30,280,60);
    ui->UAV1->setGeometry(165,30,280,60);
    ui->UAV2->setGeometry(165,30,280,60);
    ui->UAV4->setGeometry(165,30,280,60);

    ui->UAV1->setVisible(true);
    ui->UAV2->setVisible(true);
    ui->UAV3->setVisible(true);
    ui->UAV4->setVisible(true);
}

void SettingWidget::on_jia4_clicked()
{
    //放大无人机4视频监控窗格
    ui->widget4->setGeometry(0, 0,1300, 1050);
    ui->csscBasicWidget_4->setGeometry(5, 5, 1287, 1037);
    ui->csscLabel_4->setGeometry(5, 5, 1287, 1037);
  //  ui->widget_4->setGeometry(250, 900, 681, 61);

    ui->widget1->setGeometry(1300, 3, 620, 348);
    ui->widget2->setGeometry(1300, 351, 620, 348);
    ui->widget3->setGeometry(1300, 699, 620, 348);


    ui->csscBasicWidget_2->setGeometry(5,5,608,333);
    ui->csscBasicWidget_3->setGeometry(5,5,608,333);
    ui->csscBasicWidget->setGeometry(5,5,608,333);

    ui->csscLabel_2->setGeometry(5,5,608,333);
    ui->csscLabel_3->setGeometry(5,5,608,333);
    ui->csscLabel->setGeometry(5,5,608,333);

    ui->jia4->setVisible(false);
    ui->jian4->setEnabled(true);
    ui->jian4->setGeometry(1130,10,40,36);
    ui->all4->setVisible(true);
    ui->all4->setGeometry(1200,10,40,36);

    ui->jia2->setVisible(false);
    ui->jian2->setEnabled(true);
    ui->jian2->setGeometry(515,10,40,36);
    ui->all2->setVisible(true);
    ui->all2->setGeometry(565,10,40,36);

    ui->jia3->setVisible(false);
    ui->jian3->setEnabled(true);
    ui->jian3->setGeometry(515,10,40,36);
    ui->all3->setVisible(true);
    ui->all3->setGeometry(565,10,40,36);

    ui->jia1->setVisible(false);
    ui->jian1->setEnabled(true);
    ui->jian1->setGeometry(515,10,40,36);
    ui->all1->setVisible(true);
    ui->all1->setGeometry(565,10,40,36);

    ui->csscComboBox->setVisible(false);
    ui->csscComboBox_2->setVisible(false);
    ui->csscComboBox_3->setVisible(false);
    ui->csscComboBox_4->setVisible(false);

//    ui->csscComboBox->setGeometry(10,20,150,32);
//    ui->csscComboBox_2->setGeometry(10,20,150,32);
//    ui->csscComboBox_3->setGeometry(10,20,150,32);
//    ui->csscComboBox_4->setGeometry(10,20,150,32);

    ui->widget_4->setVisible(true);
    ui->widget_4->setGeometry(320,970,721,61);
    ui->csscGaugeMini_9->setVisible(true);
    ui->weizhi4->setGeometry(80,15,71,31);
    ui->weizhi_x4->setGeometry(160,15,71,31);
    ui->weizhi_y4->setGeometry(240,15,71,31);
    ui->weizhi_z4->setGeometry(320,15,71,31);
    ui->sudu4->setGeometry(410,15,71,31);
    ui->sudu_x4->setGeometry(490,15,71,31);
    ui->sudu_y4->setGeometry(570,15,71,31);
    ui->sudu_z4->setGeometry(650,15,71,31);

    ui->widget_2->setVisible(true);
    ui->widget_2->setGeometry(50,280,511,61);
    ui->csscGaugeMini_7->setVisible(false);
    ui->weizhi2->setGeometry(10,15,71,31);
    ui->weizhi_x2->setGeometry(70,15,71,31);
    ui->weizhi_y2->setGeometry(130,15,71,31);
    ui->weizhi_z2->setGeometry(190,15,71,31);
    ui->sudu2->setGeometry(260,15,71,31);
    ui->sudu_x2->setGeometry(320,15,71,31);
    ui->sudu_y2->setGeometry(380,15,71,31);
    ui->sudu_z2->setGeometry(440,15,71,31);

    ui->widget_3->setVisible(true);
    ui->widget_3->setGeometry(50,280,511,61);
    ui->csscGaugeMini_8->setVisible(false);
    ui->weizhi3->setGeometry(10,15,71,31);
    ui->weizhi_x3->setGeometry(70,15,71,31);
    ui->weizhi_y3->setGeometry(130,15,71,31);
    ui->weizhi_z3->setGeometry(190,15,71,31);
    ui->sudu3->setGeometry(260,15,71,31);
    ui->sudu_x3->setGeometry(320,15,71,31);
    ui->sudu_y3->setGeometry(380,15,71,31);
    ui->sudu_z3->setGeometry(440,15,71,31);
\
    ui->widget_1->setVisible(true);
    ui->widget_1->setGeometry(50,280,511,61);
    ui->csscGaugeMini_6->setVisible(false);
    ui->weizhi1->setGeometry(10,15,71,31);
    ui->weizhi_x->setGeometry(70,15,71,31);
    ui->weizhi_y->setGeometry(130,15,71,31);
    ui->weizhi_z->setGeometry(190,15,71,31);
    ui->sudu1->setGeometry(260,15,71,31);
    ui->sudu_x->setGeometry(320,15,71,31);
    ui->sudu_y->setGeometry(380,15,71,31);
    ui->sudu_z->setGeometry(440,15,71,31);


    ui->jian1->setToolTip("四窗格");
    ui->all1->setToolTip("全屏");
    ui->jian2->setToolTip("四窗格");
    ui->all2->setToolTip("全屏");
    ui->jian3->setToolTip("四窗格");
    ui->all3->setToolTip("全屏");
    ui->jian4->setToolTip("四窗格");
    ui->all4->setToolTip("全屏");

    ui->UAV4->setGeometry(510,30,280,60);
    ui->UAV1->setGeometry(165,30,280,60);
    ui->UAV2->setGeometry(165,30,280,60);
    ui->UAV3->setGeometry(165,30,280,60);

    ui->UAV1->setVisible(true);
    ui->UAV2->setVisible(true);
    ui->UAV3->setVisible(true);
    ui->UAV4->setVisible(true);
}

//void SettingWidget::backPlay(int index)
//{
//    //回放30s
//    switch (index)
//    {
//    case 1:
//        on_csscRadioButton_clicked();
//        break;
//    case 2:
//        on_csscToolButton_clicked();
//        break;
//    case 3:
//        on_csscToolButton_2_clicked();
//        break;
//    case 4:
//        on_csscToolButton_3_clicked();
//        break;
//    }
//}

//void SettingWidget::recoverPlay(int index)
//{
//    //恢复实时播放
//    switch (index)
//    {
//    case 1:
//        on_csscRadioButton_2_clicked();
//        break;
//    case 2:
//        on_csscToolButton_5_clicked();
//        break;
//    case 3:
//        on_csscToolButton_4_clicked();
//        break;
//    case 4:
//        on_csscToolButton_6_clicked();
//        break;
//    }
//}

//无人机1
//void SettingWidget::on_csscRadioButton_clicked()
//{
//    //回放到30s处
//    curTime = player1->position();
//    player1->setPosition(30000);

//}

//void SettingWidget::on_csscRadioButton_2_clicked()
//{
//    //恢复实时播放
//    player1->setPosition(curTime);
//}


//无人机2
//void SettingWidget::on_csscToolButton_clicked()
//{
//    //回放到30s处
//    curTime = player2->position();
//    player2->setPosition(30000);
//}


//void SettingWidget::on_csscToolButton_5_clicked()
//{
//    //恢复实时播放
//    player2->setPosition(curTime);
//}


//无人机3
//void SettingWidget::on_csscToolButton_2_clicked()
//{
//    //回放到30s处
//    curTime = player3->position();
//    player3->setPosition(30000);
//}

//void SettingWidget::on_csscToolButton_4_clicked()
//{
//    //恢复实时播放
//    player3->setPosition(curTime);
//}

//无人机4
//void SettingWidget::on_csscToolButton_3_clicked()
//{
//    //回放到30s处
//    curTime = player4->position();
//    player4->setPosition(30000);
//}

//void SettingWidget::on_csscToolButton_6_clicked()
//{
//    //恢复实时播放
//    player4->setPosition(curTime);
//}

void SettingWidget::setData(QJsonObject uav){

//    qDebug()<<"setting设置数据。。。。"<<uav;
    //根据index的数值来确定应该给哪个控件设置数值

        switch (uav.value("index").toInt())
       {
        case 0:

            //ui->csscComboBox->setEditText(uav.value("uav_name").toString());
            ui->weizhi_x->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
            ui->weizhi_y->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
            ui->weizhi_z->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
            ui->sudu_x->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
            ui->sudu_y->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
            ui->sudu_z->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
            ui->UAV1->setShowText(uav.value("uav_name").toString());
    //        ui->angle_x->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
    //        ui->angle_y->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
    //        ui->angle_z->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
            break;
        case 1:
            //ui->csscComboBox_2->setEditText(uav.value("uav_name").toString());
            ui->weizhi_x2->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
            ui->weizhi_y2->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
            ui->weizhi_z2->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
            ui->sudu_x2->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
            ui->sudu_y2->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
            ui->sudu_z2->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
            ui->UAV2->setShowText(uav.value("uav_name").toString());
    //        ui->angle_x2->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
    //        ui->angle_y2->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
    //        ui->angle_z2->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
            break;
        case 2:
            //ui->csscComboBox_3->setEditText(uav.value("uav_name").toString());
            ui->weizhi_x3->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
            ui->weizhi_y3->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
            ui->weizhi_z3->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
            ui->sudu_x3->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
            ui->sudu_y3->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
            ui->sudu_z3->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
            ui->UAV3->setShowText(uav.value("uav_name").toString());
    //        ui->angle_x3->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
    //        ui->angle_y3->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
    //        ui->angle_z3->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
            break;
        case 3:
            //ui->csscComboBox_4->setEditText(uav.value("uav_name").toString());
            ui->weizhi_x4->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
            ui->weizhi_y4->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
            ui->weizhi_z4->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
            ui->sudu_x4->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
            ui->sudu_y4->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
            ui->sudu_z4->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
            ui->UAV4->setShowText(uav.value("uav_name").toString());
    //        ui->angle_x4->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
    //        ui->angle_y4->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
    //        ui->angle_z4->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
            break;
       }

}
void SettingWidget::setData1(QJsonObject uav){
   // qDebug()<<"设置数据。。。。"<<uav;
    //根据index的数值来确定应该给哪个控件设置数值
        //ui->csscComboBox_2->setEditText(uav.value("uav_name").toString());

        ui->weizhi_x2->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
        ui->weizhi_y2->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
        ui->weizhi_z2->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
        ui->sudu_x2->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
        ui->sudu_y2->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
        ui->sudu_z2->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
        ui->UAV2->setShowText(uav.value("uav_name").toString());

//    ui->angle_x2->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
//    ui->angle_y2->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
//    ui->angle_z2->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
}
void SettingWidget::setData2(QJsonObject uav){
    //ui->csscComboBox_3->setEditText(uav.value("uav_name").toString());
        ui->weizhi_x3->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
        ui->weizhi_y3->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
        ui->weizhi_z3->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
        ui->sudu_x3->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
        ui->sudu_y3->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
        ui->sudu_z3->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
        ui->UAV3->setShowText(uav.value("uav_name").toString());
    //    ui->angle_x3->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
    //    ui->angle_y3->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
    //    ui->angle_z3->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
//     }
}
void SettingWidget::setData3(QJsonObject uav){
        //ui->csscComboBox_4->setEditText(uav.value("uav_name").toString());
        ui->weizhi_x4->setText(QString::number(uav.value("locate_x").toDouble(), 10, 1));
        ui->weizhi_y4->setText(QString::number(uav.value("locate_y").toDouble(), 10, 1));
        ui->weizhi_z4->setText(QString::number(uav.value("locate_z").toDouble(), 10, 1));
        ui->sudu_x4->setText(QString::number(uav.value("sudu_x").toDouble(), 10, 1));
        ui->sudu_y4->setText(QString::number(uav.value("sudu_y").toDouble(), 10, 1));
        ui->sudu_z4->setText(QString::number(uav.value("sudu_z").toDouble(), 10, 1));
        ui->UAV4->setShowText(uav.value("uav_name").toString());
    //    ui->angle_x4->setText(QString::number(uav.value("angle_x").toDouble(), 10, 4));
    //    ui->angle_y4->setText(QString::number(uav.value("angle_y").toDouble(), 10, 4));
    //    ui->angle_z4->setText(QString::number(uav.value("angle_z").toDouble(), 10, 4));
}
void SettingWidget::setImage(QPixmap pixmap,QString uav_name,int index)
{
//    qDebug()<<"setting uavname="<<uav_name<<",index="<<index;
    //根据index的数值来确定应该给哪个控件设置图片
    QSize size = ui->csscBasicWidget->size();
    pixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio);
    ui->csscLabel->setScaledContents(true);
    ui->csscLabel_2->setScaledContents(true);
    ui->csscLabel_3->setScaledContents(true);
    ui->csscLabel_4->setScaledContents(true);
        switch (index)
       {
            case 0:
                ui->csscLabel->setPixmap(pixmap);
               // ui->csscComboBox->setEditText(uav_name);
                break;
            case 1:
                ui->csscLabel_2->setPixmap(pixmap);
               // ui->csscComboBox_2->setEditText(uav_name);
                break;
            case 2:
                ui->csscLabel_3->setPixmap(pixmap);
                //ui->csscComboBox_3->setEditText(uav_name);
                break;
            case 3:
                ui->csscLabel_4->setPixmap(pixmap);
                //ui->csscComboBox_4->setEditText(uav_name);
            break;
       }
}
void SettingWidget::setImage1(QPixmap pixmap,QString uav_name,int index)
{
    //根据index的数值来确定应该给哪个控件设置图片
    QSize size = ui->csscBasicWidget->size();
    pixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio);
    ui->csscLabel->setScaledContents(true);
    ui->csscLabel_2->setScaledContents(true);
    ui->csscLabel_3->setScaledContents(true);
    ui->csscLabel_4->setScaledContents(true);
    switch (index)
   {
        case 0:
            ui->csscLabel->setPixmap(pixmap);
            //ui->csscComboBox->setEditText(uav_name);
            break;
        case 1:
            ui->csscLabel_2->setPixmap(pixmap);
          //  ui->csscComboBox_2->setEditText(uav_name);
            break;
        case 2:
            ui->csscLabel_3->setPixmap(pixmap);
//            ui->csscComboBox_3->setEditText(uav_name);
            break;
        case 3:
            ui->csscLabel_4->setPixmap(pixmap);
           // ui->csscComboBox_4->setEditText(uav_name);
        break;
   }

}
void SettingWidget::setImage2(QPixmap pixmap,QString uav_name,int index)
{
    //根据index的数值来确定应该给哪个控件设置图片
    QSize size = ui->csscBasicWidget->size();
    pixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio);
    ui->csscLabel->setScaledContents(true);
    ui->csscLabel_2->setScaledContents(true);
    ui->csscLabel_3->setScaledContents(true);
    ui->csscLabel_4->setScaledContents(true);
    switch (index)
   {
        case 0:
            ui->csscLabel->setPixmap(pixmap);
            //ui->csscComboBox->setEditText(uav_name);
            break;
        case 1:
            ui->csscLabel_2->setPixmap(pixmap);
           // ui->csscComboBox_2->setEditText(uav_name);
            break;
        case 2:
            ui->csscLabel_3->setPixmap(pixmap);
            //ui->csscComboBox_3->setEditText(uav_name);
            break;
        case 3:
            ui->csscLabel_4->setPixmap(pixmap);
            //ui->csscComboBox_4->setEditText(uav_name);
        break;
   }

}
void SettingWidget::setImage3(QPixmap pixmap,QString uav_name,int index)
{
    //根据index的数值来确定应该给哪个控件设置图片
    QSize size = ui->csscBasicWidget->size();
    pixmap = pixmap.scaled(size,Qt::IgnoreAspectRatio);
    ui->csscLabel->setScaledContents(true);
    ui->csscLabel_2->setScaledContents(true);
    ui->csscLabel_3->setScaledContents(true);
    ui->csscLabel_4->setScaledContents(true);
    switch (index)
   {
        case 0:
            ui->csscLabel->setPixmap(pixmap);
            //ui->csscComboBox->setEditText(uav_name);
            break;
        case 1:
            ui->csscLabel_2->setPixmap(pixmap);
            //ui->csscComboBox_2->setEditText(uav_name);
            break;
        case 2:
            ui->csscLabel_3->setPixmap(pixmap);
            //ui->csscComboBox_3->setEditText(uav_name);
            break;
        case 3:
            ui->csscLabel_4->setPixmap(pixmap);
            //ui->csscComboBox_4->setEditText(uav_name);
        break;
   }

}
void SettingWidget::setUAVName(QStringList list)
{
    //给所有的下拉框设置无人机的名字
    if(list.size()>0){
        ui->csscComboBox->clear();
        ui->csscComboBox_2->clear();
        ui->csscComboBox_3->clear();
        ui->csscComboBox_4->clear();
        for(int i = 0; i< list.size();++i)
        {
            if(i<4){
                QString uav = list.at(i);
                ui->csscComboBox->addItem(uav);
                ui->csscComboBox_2->addItem(uav);
                ui->csscComboBox_3->addItem(uav);
                ui->csscComboBox_4->addItem(uav);
                if(i==0){
                   ui->csscComboBox->setCurrentIndex(i);
                }else if (i==1) {
                   ui->csscComboBox_2->setCurrentIndex(i);
                }else if (i==2) {
                    ui->csscComboBox_3->setCurrentIndex(i);
                 }else if (i==3) {
                    ui->csscComboBox_4->setCurrentIndex(i);
                 }
            }

        }
    }
}


void SettingWidget::RefreshWindow(int index){

    if(index >= 0 && index <= 3) {

        switch (index){

            case 0:
                    on_jia1_clicked();
                    break;
            case 1:
                    on_jia2_clicked();
                    break;
            case 2:
                    on_jia3_clicked();
                    break;
            case 3:
                    on_jia4_clicked();
                    break;
        }
    }
}



void SettingWidget::on_jian1_clicked()
{
    recoverFour();
}

void SettingWidget::on_jian2_clicked()
{
    recoverFour();
}

void SettingWidget::on_jian3_clicked()
{
    recoverFour();
}

void SettingWidget::on_jian4_clicked()
{
    recoverFour();
}
