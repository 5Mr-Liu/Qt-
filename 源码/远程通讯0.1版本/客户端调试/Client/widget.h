#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "clientcore.h"
#include <QKeyEvent>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
     void onTimeOut(SOCKET xServer);//接受服务端消息
     void clickSend(SOCKET XServer);//发送消息

     void keyPressEvent(QKeyEvent *ev);//监视键盘按键按下，执行某些操作
     void keyReleaseEvent(QKeyEvent *ev);//监视键盘按键释放，执行某些操作
private:
    Ui::Widget *ui;
    QTimer *tim;



};

#endif // WIDGET_H
