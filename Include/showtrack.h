#ifndef SHOWTRACK_H
#define SHOWTRACK_H

#include "MainWidget.h"
#include "SettingWidget.h"
#include "MapForm.h"

extern int pointX;
extern int pointY;
extern QString uiID;
extern QString commandType;


class ShowTrack : public QWidget
{
    Q_OBJECT

public:

    ShowTrack(MainWidget *mw, MapForm *mf, SettingWidget *sw);
    ~ShowTrack();

    MainWidget *mainWidget;
    MapForm *mapForm;
    SettingWidget *settingWidget;

    int count;
    QWidget *w1, *w2, *w3, *w4;
    QTimer *timer;
    QList<QPoint> pos_list_w2;
    QList<QPoint> pos_list_w3;
    QList<QPoint> pos_list_w4;
    QPoint point;
    int pointX, pointY;
    int uiID;
    int lastID;

    void setMyStyle(QWidget *wid, int w, int h);
    void deleteList(QList<QPoint> point);

public slots:
    void updatePos(QJsonObject jb);

};

#endif // SHOWTRACK_H
