#ifndef JSONWRITE_H
#define JSONWRITE_H

#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <string>

#include "MainWidget.h"
#include "ui_MainWidget.h"

#include "MapForm.h"
#include "ui_MapForm.h"

#include "SettingWidget.h"
#include "ui_SettingWidget.h"


class JsonWrite
{
public:
    JsonWrite(MainWidget *mw, MapForm *mf, SettingWidget * sw);

    //清除jsonObject对象内容
    void clearJsonObject(QJsonObject &object);


private:
    MainWidget *mainWidget;
    MapForm *mapForm;
    SettingWidget *settingWidget;
};

#endif // JSONWRITE_H
