 #include "Include/recthread.h"
#include <QFile>
#include <QJsonParseError>
#include "string.h"
#include <QDebug>

#define KEY_UP(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

int Pix_ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int Pix_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

RecThread::~RecThread()
{

}

void RecThread::slot_runRecievedMsg()
{
    qDebug()<<"Collecting updates from Server...";

    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
   int rc = zmq_connect(subscriber, "tcp://localhost:5566");
//    int rc = zmq_connect(subscriber, "tcp://192.168.31.252:7788");
//    int rc = zmq_connect(subscriber, "tcp://192.168.0.151:7766");
    qDebug()<< "zmq connect:" << rc;
//    std::cout<<"\n\n\n\n\n adsa \n\n\n\n"<<std::endl;

    //设置订阅条件，为空表示全订阅
    const char *filter = "";
    zmq_setsockopt(subscriber,ZMQ_SUBSCRIBE,filter,strlen(filter));

    //要操作的当前意图控件
    QString curController("");
    curController1 = {
            "csscBasicWidget",
            "csscBasicWidget_2",
            "csscBasicWidget_3",
            "csscBasicWidget_4",
            "csscBasicWidget_5"
    };
    curController2 = {
            "MapForm"
        };
    curController3 = {
            "widget1",
            "widget2",
            "widget3",
            "widget4"
        };
    //要调用的信号索引以及相关参数
    QVector<QString> parameters;
    //要调用的信号索引
    int signalIndex;

    //读json文件,并输出提示信息
    QFile loadFile("D:\\UAVCS-update\\1.json");
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "coundn't open projects json!";
    }
    QByteArray allData = loadFile.readAll();
    loadFile.close();
//    qDebug() <<"recData==="<<allData;
    //报告json解析期间出现的错误
    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "json error!" << jsonError.errorString();
    }

    QJsonObject rootObj = jsonDoc.object();

    //消息循环
    while(true)
    {
        extern int hisVideo;
        char buffer[512];
//        std::cout<<1<<std::endl;
        int size = zmq_recv(subscriber, buffer, 512, 0);
//        std::cout<<2<<std::endl;
//        std::cout<<buffer<<std::endl;
        //避免堵塞
        if(size == -1)
            continue;
        //转成字符串
        buffer[size] = '\0';
        qDebug() << "Received: " << buffer;

        parameters.clear();

        //解析收到的字符串
        QString commandStr = QString::fromStdString(buffer);
        qDebug() << "commandStr" << commandStr;

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(commandStr.toUtf8(), &jsonError));
        qDebug() << "jsonDoc" << jsonDoc;

        if(jsonError.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!" << jsonError.errorString();
        }

        commandJson = jsonDoc.object();
        qDebug() << "commandJson" << commandJson;


        QString index = commandJson.value("id").toString();
        qDebug() << "id" << index;

        QString eye = commandJson.value("command").toString();
        qDebug() << "command" << eye;

        QString physicId = QString("%1%2").arg(QString("physic ")).arg(index);  //显示器物理位置1,2,3
        qDebug() << "physicId" << physicId;
        //根据输入命令中的显示器标号值（物理位置），映射到对应的界面号上（逻辑位置）
        //如果物理位置对应于physicId，则返回对应的logicId(逻辑位置)
        QJsonObject psubObj= rootObj.value("windows").toObject();
        qDebug() << "psubObj" << psubObj;
        QString logicId = psubObj.value(physicId).toString();
        qDebug() << "logicId = " << logicId;

        // 调用命令解析函数
        // 作用：输入收到的命令commandJson,读取配置文件，
        // 先输出意图控制区域 by eyeParse()，再赋值要调用的信号索引以及相关参数QVector by commandParse()

        // 眼动
        if(commandJson.value("command").toString() == "eye")
        {
            qDebug() << "eye";
            int actualX = commandJson.value("actualX").toInt();
            int actualY = commandJson.value("actualY").toInt();

            show(actualX, actualY, logicId);

            POINT temp;
            GetCursorPos(&temp);

            v1.push_back(pair<int, int>(temp.x, temp.y));
            v2.push_back(pair<int, int>(actualX, actualY));

            //G.GetClickAndGaze(click_x,click_y,actualX,actualY,50);
            pair<int, int> P(-1, -1);

            // G.pair<int, int> RetUserPos(int x, int y);
            POINT p1;
            p1.x = click_x;
            p1.y = click_y;
            if(conflict(v1, v2, p1, 10, 3, 50, 30, 50, 50))
            {
                //G.RefreshM();
                G.RefreshP2M(500);
                P = G.RetUserPos(actualX, actualY);
                if(P.first == -1)
                {
                    P.first = actualX;
                    P.second = actualY;
                }
                //输出意图控制区域名称
                curController = eyeParse(P.first, P.second, rootObj, logicId);
                qDebug() << "curController " << curController;

                //移动鼠标
                QCursor::setPos(P.first, P.second);
                qDebug() << "move cursor " << P.first <<", " << P.second;

                if(index == "1")
                {
                //主界面需要高亮
                    commandParse(commandJson, parameters, curController, rootObj, logicId);
                    qDebug() << "end commandParse";
                    signalIndex = parameters[0].toInt();
                    int para1 = parameters[1].toInt();

                    qDebug() << "signalIndex: " << signalIndex;
                    qDebug() << "praa" << para1;

                    emit (this->*signalFun[signalIndex])(para1, 0);
                    qDebug() << "suceesfully emit!";
                }
            }
        }


        //手势
        else if(commandJson.value("command").toString() == "hand"){
            qDebug() << "hand";
            commandParse(commandJson, parameters, curController, rootObj, logicId);
            signalIndex = parameters[0].toInt();

            if (commandJson.contains("offset")){
                //参数从消息中取（地图左移右移的offset）
                // 发出命令对应的信号
                int offset = commandJson.value("offset").toInt();
                emit (this->*signalFun[signalIndex])(offset,0);
            }
            else {
                //参数从配置文件中取
                if(parameters.size() == 2){
                    qDebug() << "size = 2";
                    int para1 = parameters[1].toInt();
                    qDebug() << "parameters[1]" << parameters[1];
                    qDebug() << "signalIndex: " << signalIndex;
                    qDebug() << "para" << para1;
                    emit (this->*signalFun[signalIndex])(para1,0);
                    qDebug() << "suceesfully emit!";
                }
                else if (parameters.size() == 3) {
                    int para1 = parameters[1].toInt();
                    int para2 = parameters[2].toInt();
                    emit (this->*signalFun[signalIndex])(para1, para2);
                }
                else {
                    // 没有参数，只有索引
                    emit (this->*signalFun[signalIndex])(0,0);
                }
            }
        }
        //语音
        else if(commandJson.value("command").toString() == "voice"){
            qDebug() << "voice";
            commandParse(commandJson, parameters, curController, rootObj, logicId);
            signalIndex = parameters[0].toInt();

//            if (commandJson.contains("offset")){
//                //参数从消息中取（地图左移右移的offset）
//                // 发出命令对应的信号
//                int offset = commandJson.value("offset").toInt();
//                emit (this->*signalFun[signalIndex])(offset,0);
//            }
//            else {
                //参数从配置文件中取
                if(parameters.size() == 2){
                    qDebug() << "size = 2";
                    int para1 = parameters[1].toInt();
                    qDebug() << "parameters[1]" << parameters[1];
                    qDebug() << "signalIndex: " << signalIndex;
                    qDebug() << "para" << para1;
                    emit (this->*signalFun[signalIndex])(para1,0);
                    qDebug() << "suceesfully emit!";
              }
                 else if (parameters.size() == 3) {
                    int para1 = parameters[1].toInt();
                    int para2 = parameters[2].toInt();
                    emit (this->*signalFun[signalIndex])(para1, para2);
                }
                else {
                    // 没有参数，只有索引
                    emit (this->*signalFun[signalIndex])(0,0);
                }
            }

    }
}


QString RecThread::eyeParse(int lX, int lY, QJsonObject rootObj, QString logicId)
{
    int curCon_x;
    int curCon_y;

    if(logicId == "1")
    {
//        curCon_x = lX - Pix_ScreenWidth;
        curCon_x = lX;
        curCon_y = lY;

    }
    else if(logicId == "2")
    {
        curCon_x = lX;
        curCon_y = lY;
    }
    else if(logicId == "3")
    {
        curCon_x = Pix_ScreenWidth + lX;
        curCon_y = lY;
    }

    QPoint logicPoint(curCon_x, curCon_y);
    //输出意图控制区域，并移动鼠标
    //利用lX和lY去得到意图区域
    QString curControl = "invalid area";

    //逻辑位置：mainWidget为1, mapWidget为2, settingWidget为3
    //找到了对应的界面
    qDebug() << "logicID" << logicId;
    if(rootObj.contains(logicId))
    {
        QJsonObject subObj = rootObj.value(logicId).toObject();
        QJsonArray controlArray = subObj.value("controls").toArray();

        int i;
        for (i = 0; i < controlArray.size(); i++)
        {
            curControl = controlArray.at(i).toString();
            QJsonObject thirdObj = subObj.value(curControl).toObject();
            QRect controlRect(thirdObj["x"].toInt(), thirdObj["y"].toInt(),
                    thirdObj["width"].toInt(), thirdObj["height"].toInt());

            //找到了对应的控件
            if(controlRect.contains(logicPoint))
            {
                qDebug() << "finded it!!!!!!!!!!!!!!!!!!!!!!!";
                return curControl;
            }
        }
     }
    else {
        qDebug() << "logical index error!";
        return "null control";
    }
}

bool RecThread::commandParse(QJsonObject commandJson, QVector<QString>&para, QString curControl, QJsonObject rootObj, QString logicId)
{
    //手势和语音
    //命令解析函数
    QString commandType = commandJson.value("command").toString();
    QString commandContent = commandJson.value("content").toString();
    qDebug() << "commandJson="<<commandJson<<",curControl="<<curControl<<",rootObj="<<rootObj<<",logicId="<<logicId;

    //找到了对应的界面
    if(rootObj.contains(logicId))
    {
        QJsonObject subObj = rootObj.value(logicId).toObject();
        QJsonArray ctrList = subObj.value("controls").toArray();
        int j;
        for (j = 0; j < ctrList.size(); j++){
            QJsonObject thirdObj = subObj.value(ctrList[j].toString()).toObject();
            QJsonObject keyObj = thirdObj.value(commandType).toObject();
            QStringList keysList = keyObj.keys();
            QString curString;
            int i;
            for (i = 0; i < keysList.size(); i++)
            {
                curString = keysList.at(i);

                //当前命令内容合法
                if(curString == commandContent)
                {
                    //若鼠标在该控件上，则返回命令对应的函数指针数组索引
                    QJsonObject fourthObj  = keyObj.value(curString).toObject();
                    QString signalIndex = fourthObj.value("index").toString();

                    qDebug() << "inner signalIndex" << signalIndex;

                    para.push_back(signalIndex);
                    if(fourthObj.contains("args"))
                    {
                        QJsonArray argsArr = fourthObj.value("args").toArray();
                        qDebug() << "inner args" << argsArr;
                        qDebug() << "inner args.size" << argsArr.size();
                        for (int j = 0; j < argsArr.size(); j++)
                            para.push_back(argsArr.at(j).toString());
                    }
                    qDebug() << "para_content:(inner)" << para;

                    return true;
                }
            }
            if(i == keysList.size()){
                qDebug() << "command content error!";
            }
        }

    }else{
        qDebug() << "logical index error!";
    }
    return true;
}

pair<int, int> avesum(vector<pair<int, int>>x, int n)
{
    pair<int, int> ret(0, 0);
    size_t cnt = x.size() - 1;
    int tot = 0;
    for(int i = max(0, n-10); i <= min(int(cnt), n+10); ++i)
    {
        ret.first += x[i].first;
        ret.second += x[i].second;
        tot++;
    }
    ret.first /= tot;
    ret.second /= tot;
    return ret;
}

bool RecThread::conflict(vector<pair<int, int>>Clicks, vector<pair<int, int>>Gazes, POINT p, int a, int b, int c, int d, int e, int f)
{
    size_t cnt = Clicks.size() - 1;
    pair<int, int> P1, P2;
    //如果鼠标在a内发生移动，则不进行眼动
    if(cnt >= a)
    {
        P1 = avesum(Clicks, cnt);
        P2 = avesum(Clicks, cnt-a);
        if (P1.first != P2.first || P1.second != P2.second)
            return false;
    }
    cnt = Gazes.size() - 1;
    //如果眼在b时间内移动（曼哈顿距离）大于c，则不发生眼动
    if(cnt >= b)
    {
        P1 = avesum(Gazes, cnt);
        P2 = avesum(Gazes, cnt-b);
        if (abs(P1.first - P2.first) + abs(P1.second - P2.second) >= c)
            return false;
    }
    //如果眼在x-b-d到x-b这段时间内时间内移动（曼哈顿距离）小于e，则不发生眼动
    if(cnt >= b+d)
    {
        P1 = avesum(Gazes, cnt-b);
        P2 = avesum(Gazes, cnt-b-d);
        if (abs(P1.first - P2.first) + abs(P1.second - P2.second) <= e)
            return false;
    }
    //如果凝视点和鼠标距离小于f，不进行移动
    P1 = avesum(Gazes, cnt);
    if (abs(P1.first - p.x) + abs(P1.second - p.y) <= f)
        return false;
    return true;
}

bool RecThread::release()
{
    while(1)//循环检测
    {
        if(KEY_UP(VK_LBUTTON))
        {  			//鼠标左键按下
           return true;
        }
    }
}

void RecThread::show(int a_x, int a_y, QString id)
{
    int logicX;
    int logicY;

    if(id == "1")
    {
       // logicX = a_x - Pix_ScreenWidth;
         logicX = a_x;
        logicY = a_y;
    }
    else if(id == "2")
    {
        logicX = a_x;
        logicY = a_y;
    }
    else if(id == "3")
    {
        logicX = Pix_ScreenWidth + a_x;
        logicY = a_y;
    }

    //将QJsonObject的消息传到showtrack中
    QJsonObject qjb;
    qjb.insert("logicX", logicX);
    qjb.insert("logicY", logicY);
    qjb.insert("logicID", id.toInt());
    qDebug() << "********************";
    qDebug() << "qjb" << qjb;
    emit deliverMesssage(qjb);
}

void RecThread::slot_recvPoint(QPoint p){
    click_x = p.x();
    click_y = p.y();
    size_t cnt = v2.size()-1;
    if(v2.size())
    {
        int actualX = v2[cnt].first;
        int actualY = v2[cnt].second;
        //G.GetClickAndGaze(click_x, click_y, actualX, actualY);
        G.GetClickAndGaze(click_x, click_y, actualX, actualY, 50);
    }
}
