#include "Include/jsonwrite.h"

JsonWrite::JsonWrite(MainWidget *mw, MapForm *mf, SettingWidget *sw)
{
    // 实例化ui对象
    this->mainWidget = mw;
    this->mapForm = mf;
    this->settingWidget = sw;

    // 以读写方式打开主目录下的1.json文件，若该文件不存在则会自动创建
    QString strs = QString::fromStdString("D:/UAVCS-update/1.json");
    QFile file(strs);
    qDebug() << strs;
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        qDebug() <<"File open!";

    }

    // 清空文件中的原有内容
    file.resize(0);

    // 使用obj作为一级标题，mainWidget，mapWidget，settingWidget
    QJsonObject obj;
    QJsonObject obj1;
    QJsonObject obj2;
    QJsonArray arr1;

    //___________________________________________________________________________
    //mainWidget

    // 使用jsonFinalObject添加值，并写入文件
    QJsonObject jsonObject;
    QJsonObject jsonFinalObject;


    obj1.insert("physic 1", "1");
    obj1.insert("physic 2", "2");
    obj1.insert("physic 3", "3");
    obj.insert("windows", obj1);
    clearJsonObject(obj1);

    arr1 = {1, 2, 3, 4, 5, 6};
    obj.insert("hand", arr1);

    arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
    obj.insert("voice", arr1);

    arr1 = {1};
    obj.insert("eye", arr1);

    arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    obj.insert("signals", arr1);


    //mainWidget
    arr1 = {1980,1020};
    jsonFinalObject.insert("size", arr1);

    arr1 = {0,0};
    jsonFinalObject.insert("offset", arr1);

    arr1 = {1,1};
    jsonFinalObject.insert("scales", arr1);

    arr1 = {"csscBasicWidget", "csscBasicWidget_2", "csscBasicWidget_3", "csscBasicWidget_4", "csscBasicWidget_5"};
    jsonFinalObject.insert("controls", arr1);

    jsonObject.insert("x", mainWidget->ui->csscBasicWidget->x());
    jsonObject.insert("y", mainWidget->ui->csscBasicWidget->y());
    jsonObject.insert("width", mainWidget->ui->csscBasicWidget->width());
    jsonObject.insert("height", mainWidget->ui->csscBasicWidget->height());
    jsonObject.insert("parent", "MainWidget");

    arr1 = {"1"};
    obj1.insert("index", "2");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("eye", obj2);
    clearJsonObject(obj2);

    //结束
    arr1 = {"1","0"};
    obj1.insert("index", "24");
    obj1.insert("args", arr1);
    obj2.insert("0", obj1);
    clearJsonObject(obj1);

    //短文字
    arr1 = {"1","1"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("13", obj1);
    clearJsonObject(obj1);

    //2图片加文字
    arr1 = {"1","2"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("14", obj1);
    clearJsonObject(obj1);

    //2图片加文字
    arr1 = {"1","3"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("15", obj1);
    clearJsonObject(obj1);

    //2图片加文字
    arr1 = {"1","4"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("16", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","5"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("17", obj1);
    clearJsonObject(obj1);

    //4图片加文字
    arr1 = {"1","6"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("18", obj1);
    clearJsonObject(obj1);

    //1图片加文字
    arr1 = {"1","7"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("19", obj1);
    clearJsonObject(obj1);

    //2图片加文字
    arr1 = {"1","8"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("20", obj1);
    clearJsonObject(obj1);

    //3图片加文字
    arr1 = {"1","9"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("21", obj1);
    clearJsonObject(obj1);

    //短文字
    arr1 = {"1","10"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("22", obj1);
    clearJsonObject(obj1);

    //图片
    arr1 = {"1","11"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("23", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","12"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("24", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","13"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("25", obj1);
    clearJsonObject(obj1);

    //2图片加文字(no1=gif)
    arr1 = {"1","14"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("26", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","15"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("27", obj1);
    clearJsonObject(obj1);

    //1图片加文字
    arr1 = {"1","16"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("28", obj1);
    clearJsonObject(obj1);

    //图片
    arr1 = {"1","17"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("29", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","18"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("30", obj1);
    clearJsonObject(obj1);

    //图片
    arr1 = {"1","19"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("31", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","20"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("32", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","21"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("33", obj1);
    clearJsonObject(obj1);

    //长文字
    arr1 = {"1","22"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("34", obj1);
    clearJsonObject(obj1);

    //4图片加文字(no1=gif,no2=gif)
    arr1 = {"1","23"};
    obj1.insert("index", "19");
    obj1.insert("args", arr1);
    obj2.insert("35", obj1);
    clearJsonObject(obj1);


    //回放所有
    arr1 = {"7","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("36", obj1);
    clearJsonObject(obj1);

    //回放1号无人机
    arr1 = {"1","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("37", obj1);
    clearJsonObject(obj1);

    //回放2号无人机
    arr1 = {"2","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("38", obj1);
    clearJsonObject(obj1);

    //回放3号无人机
    arr1 = {"3","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("39", obj1);
    clearJsonObject(obj1);

    //回放4号无人机
    arr1 = {"4","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("40", obj1);
    clearJsonObject(obj1);

    //回放1号和2号无人机
    arr1 = {"5","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("41", obj1);
    clearJsonObject(obj1);

    //回放3号和4号无人机
    arr1 = {"6","1"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("42", obj1);
    clearJsonObject(obj1);

    //回放围捕开始的视频
    arr1 = {"7","2"};
    obj1.insert("index", "25");
    obj1.insert("args", arr1);
    obj2.insert("43", obj1);
    clearJsonObject(obj1);

    //加速回放
    arr1 = {"1","0"};
    obj1.insert("index", "28");
    obj1.insert("args", arr1);
    obj2.insert("44", obj1);
    clearJsonObject(obj1);

    //减速回放
    arr1 = {"2","0"};
    obj1.insert("index", "28");
    obj1.insert("args", arr1);
    obj2.insert("45", obj1);
    clearJsonObject(obj1);

    //回放结束
    arr1 = {"0","0"};
    obj1.insert("index", "29");
    obj1.insert("args", arr1);
    obj2.insert("46", obj1);
    clearJsonObject(obj1);

    //时移30秒
    arr1 = {"1","0"};
    obj1.insert("index", "30");
    obj1.insert("args", arr1);
    obj2.insert("47", obj1);
    clearJsonObject(obj1);

    //时移60秒
    arr1 = {"2","0"};
    obj1.insert("index", "30");
    obj1.insert("args", arr1);
    obj2.insert("48", obj1);
    clearJsonObject(obj1);

    //时移一半进度
    arr1 = {"3","0"};
    obj1.insert("index", "30");
    obj1.insert("args", arr1);
    obj2.insert("49", obj1);
    clearJsonObject(obj1);



//    //无人机1
//    arr1 = {"3","1"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("37", obj1);
//    clearJsonObject(obj1);

//    //无人机2
//    arr1 = {"3","2"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("38", obj1);
//    clearJsonObject(obj1);

//    //无人机3
//    arr1 = {"3","3"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("39", obj1);
//    clearJsonObject(obj1);

//    //无人机4
//    arr1 = {"3","4"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("40", obj1);
//    clearJsonObject(obj1);

//    //短文字：谁先发现了目标机
//    arr1 = {"1","24"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("41", obj1);
//    clearJsonObject(obj1);

//    //长文字：1号无人机的位置分布
//    arr1 = {"1","25"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("42", obj1);
//    clearJsonObject(obj1);

//    //长文字：2号无人机的位置分布
//    arr1 = {"1","26"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("43", obj1);
//    clearJsonObject(obj1);

//    //长文字：3号无人机的位置分布
//    arr1 = {"1","27"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("44", obj1);
//    clearJsonObject(obj1);

//    //长文字：4号无人机的位置分布
//    arr1 = {"1","28"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("45", obj1);
//    clearJsonObject(obj1);




    //单图片
//    arr1 = {"2","1"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("15", obj1);
//    clearJsonObject(obj1);

    //多图片
//    arr1 = {"2","2"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("16", obj1);
//    clearJsonObject(obj1);

    //gif图片
//    arr1 = {"3","1"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("23", obj1);
//    clearJsonObject(obj1);

    //视频
//    arr1 = {"3","0"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("17", obj1);
//    clearJsonObject(obj1);

    //设置1
//    arr1 = {"4","1"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("18", obj1);
//    clearJsonObject(obj1);

    //设置2
//    arr1 = {"4","2"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("19", obj1);
//    clearJsonObject(obj1);

    //设置3
//    arr1 = {"4","3"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("20", obj1);
//    clearJsonObject(obj1);

    //设置4
//    arr1 = {"4","4"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("21", obj1);
//    clearJsonObject(obj1);

    //设置5
//    arr1 = {"4","5"};
//    obj1.insert("index", "19");
//    obj1.insert("args", arr1);
//    obj2.insert("22", obj1);
//    clearJsonObject(obj1);

    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    //手势
    //放大
    obj1.insert("index", "20");
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    //缩小
    obj1.insert("index", "21");
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    //左移
    obj1.insert("index", "22");
    obj2.insert("3", obj1);
    clearJsonObject(obj1);

    //右移
    obj1.insert("index", "23");
    obj2.insert("4", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("hand", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("csscBasicWidget", jsonObject);


    clearJsonObject(jsonObject);
    jsonObject.insert("x", mainWidget->ui->csscBasicWidget_2->x());
    jsonObject.insert("y", mainWidget->ui->csscBasicWidget_2->y());
    jsonObject.insert("width", mainWidget->ui->csscBasicWidget_2->width());
    jsonObject.insert("height", mainWidget->ui->csscBasicWidget_2->height());
    jsonObject.insert("parent", "MainWidget");

    arr1 = {"0"};
    obj1.insert("index", "1");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    arr1 = {"1"};
    obj1.insert("index", "1");
    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    arr1 = {"2"};
    obj1.insert("index", "1");
    obj1.insert("args", arr1);
    obj2.insert("3", obj1);
    clearJsonObject(obj1);

    arr1 = {"3"};
    obj1.insert("index", "1");
    obj1.insert("args", arr1);
    obj2.insert("4", obj1);
    clearJsonObject(obj1);

//    arr1 = {"0"};
//    obj1.insert("index","2");
//    obj1.insert("args", arr1);
//    obj2.insert("5", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"1"};
//    obj1.insert("index", "2");
//    obj1.insert("args", arr1);
//    obj2.insert("6", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"2"};
//    obj1.insert("index", "2");
//    obj1.insert("args", arr1);
//    obj2.insert("7", obj1);
//    clearJsonObject(obj1);


    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    arr1 = {"2"};
    obj1.insert("index", "2");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("eye", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("csscBasicWidget_2", jsonObject);


    clearJsonObject(jsonObject);
    jsonObject.insert("x", mainWidget->ui->csscBasicWidget_3->x());
    jsonObject.insert("y", mainWidget->ui->csscBasicWidget_3->y());
    jsonObject.insert("width", mainWidget->ui->csscBasicWidget_3->width());
    jsonObject.insert("height", mainWidget->ui->csscBasicWidget_3->height());
    jsonObject.insert("parent", "MainWidget");

    obj1.insert("index", "3");
    obj2.insert("5", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "4");
    obj2.insert("6", obj1);
    clearJsonObject(obj1);

//    obj1.insert("index", "6");
//    obj2.insert("10", obj1);
//    clearJsonObject(obj1);

    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    arr1 = {"4"};
    obj1.insert("index", "2");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("eye", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("csscBasicWidget_3", jsonObject);


    clearJsonObject(jsonObject);
    jsonObject.insert("x", mainWidget->ui->csscBasicWidget_4->x());
    jsonObject.insert("y", mainWidget->ui->csscBasicWidget_4->y());
    jsonObject.insert("width", mainWidget->ui->csscBasicWidget_4->width());
    jsonObject.insert("height", mainWidget->ui->csscBasicWidget_4->height());
    jsonObject.insert("parent", "MainWidget");

    arr1 = {"5"};
    obj1.insert("index", "2");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("eye", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("csscBasicWidget_4", jsonObject);

    clearJsonObject(jsonObject);
    jsonObject.insert("x", mainWidget->ui->csscBasicWidget_5->x());
    jsonObject.insert("y", mainWidget->ui->csscBasicWidget_5->y());
    jsonObject.insert("width", mainWidget->ui->csscBasicWidget_5->width());
    jsonObject.insert("height", mainWidget->ui->csscBasicWidget_5->height());
    jsonObject.insert("parent", "MainWidget");

    arr1 = {"3"};
    obj1.insert("index", "2");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);

    clearJsonObject(obj1);

    jsonObject.insert("eye", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("csscBasicWidget_5", jsonObject);


    obj.insert("1", jsonFinalObject);

    //______________________________________________________________________________________
    // mapWidget
    clearJsonObject(jsonFinalObject);
    clearJsonObject(jsonObject);

    arr1 = {1920,1080};
    jsonFinalObject.insert("size", arr1);

    arr1 = {0,0};
    jsonFinalObject.insert("offset", arr1);

    arr1 = {1,1};
    jsonFinalObject.insert("scales", arr1);

    arr1 = {"MapForm"};
    jsonFinalObject.insert("controls", arr1);

    jsonObject.insert("x", 0);
    jsonObject.insert("y", 0);
    jsonObject.insert("width", 1920);
    jsonObject.insert("height", 1080);

    arr1 = {"1"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    arr1 = {"2"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    arr1 = {"3"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("3", obj1);
    clearJsonObject(obj1);

    arr1 = {"4"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("4", obj1);
    clearJsonObject(obj1);

    arr1 = {"5"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("5", obj1);
    clearJsonObject(obj1);

    arr1 = {"6"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("6", obj1);
    clearJsonObject(obj1);

    arr1 = {"7"};
    obj1.insert("index", "26");
    obj1.insert("args", arr1);
    obj2.insert("7", obj1);
    clearJsonObject(obj1);

    arr1 = {"1"};
    obj1.insert("index", "7");
    obj1.insert("args", arr1);
    obj2.insert("8", obj1);
    clearJsonObject(obj1);

    arr1 = {"2"};
    obj1.insert("index", "8");
    obj1.insert("args", arr1);
    obj2.insert("9", obj1);
    clearJsonObject(obj1);

    arr1 = {"3"};
    obj1.insert("index", "9");
    obj1.insert("args", arr1);
    obj2.insert("10", obj1);
    clearJsonObject(obj1);

    arr1 = {"4"};
    obj1.insert("index", "10");
    obj1.insert("args", arr1);
    obj2.insert("11", obj1);
    clearJsonObject(obj1);

//    arr1 = {"5"};
//    obj1.insert("index", "7");
//    obj1.insert("args", arr1);
//    obj2.insert("11", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"6"};
//    obj1.insert("index", "7");
//    obj1.insert("args", arr1);
//    obj2.insert("12", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"7"};
//    obj1.insert("index", "7");
//    obj1.insert("args", arr1);
//    obj2.insert("13", obj1);
//    clearJsonObject(obj1);


    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    //手势
    obj1.insert("index", "5");
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "6");
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "11");
    obj2.insert("3", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "12");
    obj2.insert("4", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "13");
    obj2.insert("5", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "14");
    obj2.insert("6", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("hand", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("MapForm", jsonObject);

    obj.insert("2", jsonFinalObject);

    //_______________________________________________________________________________________
    // settingWidget
    clearJsonObject(jsonFinalObject);
    clearJsonObject(jsonObject);

    arr1 = {1920,1080};
    jsonFinalObject.insert("size", arr1);

    arr1 = {0,0};
    jsonFinalObject.insert("offset", arr1);

    arr1 = {1,1};
    jsonFinalObject.insert("scales", arr1);

    arr1 = {"widget1", "widget2", "widget3", "widget4"};
    jsonFinalObject.insert("controls", arr1);

    jsonObject.insert("x", settingWidget->ui->widget1->x());
    jsonObject.insert("y", settingWidget->ui->widget1->y());
    jsonObject.insert("width", settingWidget->ui->widget1->width());
    jsonObject.insert("height", settingWidget->ui->widget1->height());
    jsonObject.insert("parent", "centralWidget");


    //手势
//    arr1 = {"1"};
//    obj1.insert("index", "14");
//    obj1.insert("args", arr1);
//    obj2.insert("3", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"1"};
//    obj1.insert("index", "15");
//    obj1.insert("args", arr1);
//    obj2.insert("4", obj1);
//    clearJsonObject(obj1);

    arr1 = {"1"};
    obj1.insert("index", "15");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "16");
//    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("hand", obj2);
    clearJsonObject(obj2);

    arr1 = {"1"};
    obj1.insert("index", "17");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "18");
//    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    arr1 = {"1"};
    obj1.insert("index", "27");
    obj1.insert("args", arr1);
    obj2.insert("3", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("widget1", jsonObject);


    clearJsonObject(jsonObject);
    jsonObject.insert("name", "widget2");
    jsonObject.insert("x", settingWidget->ui->widget2->x());
    jsonObject.insert("y", settingWidget->ui->widget2->y());
    jsonObject.insert("width", settingWidget->ui->widget2->width());
    jsonObject.insert("height", settingWidget->ui->widget2->height());
    jsonObject.insert("parent", "centralWidget");

    //手势
//    arr1 = {"2"};
//    obj1.insert("index", "14");
//    obj1.insert("args", arr1);
//    obj2.insert("3", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"2"};
//    obj1.insert("index", "15");
//    obj1.insert("args", arr1);
//    obj2.insert("4", obj1);
//    clearJsonObject(obj1);

    arr1 = {"2"};
    obj1.insert("index", "15");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "16");
//    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("hand", obj2);
    clearJsonObject(obj2);

    arr1 = {"2"};
    obj1.insert("index", "17");
    obj1.insert("args", arr1);
    obj2.insert("4", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "18");
//    obj1.insert("args", arr1);
    obj2.insert("5", obj1);
    clearJsonObject(obj1);

    arr1 = {"2"};
    obj1.insert("index", "27");
    obj1.insert("args", arr1);
    obj2.insert("6", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("widget2", jsonObject);


    clearJsonObject(jsonObject);
    jsonObject.insert("x", settingWidget->ui->widget3->x());
    jsonObject.insert("y", settingWidget->ui->widget3->y());
    jsonObject.insert("width", settingWidget->ui->widget3->width());
    jsonObject.insert("height", settingWidget->ui->widget3->height());
    jsonObject.insert("parent", "centralWidget");

    //手势
//    arr1 = {"3"};
//    obj1.insert("index", "14");
//    obj1.insert("args", arr1);
//    obj2.insert("3", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"3"};
//    obj1.insert("index", "15");
//    obj1.insert("args", arr1);
//    obj2.insert("4", obj1);
//    clearJsonObject(obj1);

    arr1 = {"3"};
    obj1.insert("index", "15");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "16");
//    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("hand", obj2);
    clearJsonObject(obj2);

    arr1 = {"3"};
    obj1.insert("index", "17");
    obj1.insert("args", arr1);
    obj2.insert("7", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "18");
//    obj1.insert("args", arr1);
    obj2.insert("8", obj1);
    clearJsonObject(obj1);

    arr1 = {"3"};
    obj1.insert("index", "27");
    obj1.insert("args", arr1);
    obj2.insert("9", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("widget3", jsonObject);


    clearJsonObject(jsonObject);
    jsonObject.insert("name", "widget4");
    jsonObject.insert("x", settingWidget->ui->widget4->x());
    jsonObject.insert("y", settingWidget->ui->widget4->y());
    jsonObject.insert("width", settingWidget->ui->widget4->width());
    jsonObject.insert("height", settingWidget->ui->widget4->height());
    jsonObject.insert("parent", "centralWidget");

    //手势
//    arr1 = {"4"};
//    obj1.insert("index", "14");
//    obj1.insert("args", arr1);
//    obj2.insert("3", obj1);
//    clearJsonObject(obj1);

//    arr1 = {"4"};
//    obj1.insert("index", "15");
//    obj1.insert("args", arr1);
//    obj2.insert("4", obj1);
//    clearJsonObject(obj1);

    arr1 = {"4"};
    obj1.insert("index", "15");
    obj1.insert("args", arr1);
    obj2.insert("1", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "16");
//    obj1.insert("args", arr1);
    obj2.insert("2", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("hand", obj2);
    clearJsonObject(obj2);

    arr1 = {"4"};
    obj1.insert("index", "17");
    obj1.insert("args", arr1);
    obj2.insert("10", obj1);
    clearJsonObject(obj1);

    obj1.insert("index", "18");
//    obj1.insert("args", arr1);
    obj2.insert("11", obj1);
    clearJsonObject(obj1);

    arr1 = {"4"};
    obj1.insert("index", "27");
    obj1.insert("args", arr1);
    obj2.insert("12", obj1);
    clearJsonObject(obj1);

    jsonObject.insert("voice", obj2);
    clearJsonObject(obj2);

    jsonFinalObject.insert("widget4", jsonObject);

    obj.insert("3", jsonFinalObject);


    //将obj转化为QDocument，写入到file中
    QJsonDocument document;
    document.setObject(obj);
    qDebug() << "write_before";
    file.write(document.toJson());
    file.close();

    qDebug() << "Write to file!";
}

void JsonWrite::clearJsonObject(QJsonObject &object)
{
    QStringList strList = object.keys();

    for(int i = 0; i < strList.size(); ++i)
        object.remove(strList.at(i));
}
