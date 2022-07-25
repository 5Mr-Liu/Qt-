#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <exception>
#pragma execution_character_set("utf-8");
//这个程序我是先在VS2022上先写完通讯的基本源码，在到这里补上界面的

SOCKET XS;//保存服务端的套接字

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QKeyEvent *ev;
    //ui->textEdit->setText("nihao");
    setWindowTitle("远程聊天0.9版---湖科刘群杰开发");
    this->resize(800,500);

    GetUI Start(ui);//创建一个对象，并把全局的UI指针传入，达到可以在另外的C++文件中控制界面的控件
    SOCKET xServer=Start.Initserver();//获取服务端的套接字

    ui->textEdit->document()->setMaximumBlockCount(10);//设置聊天框的最大长度
    ui->textEdit->setReadOnly(true);//设置TextEdit为只读

     connect(ui->Btn,&QPushButton::clicked,this,[=](){clickSend(xServer);});//绑定发送消息事件的按钮
     //connect(ui->Btn_2,&QPushButton::clicked,this,[=](){onTimeOut(xServer);});//绑定接受消息事件的按钮，之所以接收消息的函数名叫做onTimeOut,是因为一开始我是用定时器的，//时间到了就调用，后来没改，定时器的代码我注释掉了


     XS=xServer;

    tim=new QTimer();//定时器的源码
    tim->setInterval(500);
    connect(tim,&QTimer::timeout,this,[=](){onTimeOut(xServer);});
    tim->start();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::onTimeOut(SOCKET xServer)//接收消息的函数
{
    int recv_Len=0;
    char recv_Buf[100]={0};
    int flag=0;
    u_long arg=1;
    flag=ioctlsocket(xServer,FIONBIO,&arg);
    qDebug()<<"flag="<<flag;
    if (flag != NO_ERROR){
      qDebug()<<"ioctlsocket failed with error: "<< flag;
      int now;
      now=WSAGetLastError();
      qDebug()<<"now="<<now;
    }

    recv_Len=recv(xServer,recv_Buf,29,0);

         if(recv_Len==SOCKET_ERROR)
    {

            /*sprintf(recv_Buf,"对方未发来消息");
            QString strError(recv_Buf);
            ui->textEdit->append(strError);*/
            return;
    }
    // recv_Len=recv(xServer,recv_Buf,29,0);//读取服务器发来的消息，使用的是winsocket.h中的recv()API函数

    if(recv_Len<0)
    {
        ui->textEdit->append("接受信息失败！");
    }
    else{
        QString temp(recv_Buf);
        if(NULL==temp)
        {
            return;
        }else{
        QString strdd="对方发来消息:"+temp;
        ui->textEdit->append(strdd);}
    }
    free(recv_Buf);
}



void Widget::clickSend(SOCKET XServer)//发送消息的函数
{
    int send_Len=0;
    char send_Buf[100]={0};
    QString str;
    str=ui->lineEdit->text();
    QByteArray ba=str.toUtf8();
    char *tempStr=ba.data();
    strncpy(send_Buf,tempStr,strlen(tempStr)+1);


    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(NULL,"提示框","发送消息不可为空,请填写内容",MB_OK);
    }
    else{
        if(strlen(send_Buf)>30)
        {
            QMessageBox::information(NULL,"提示框","发送的字符不可超过30个字符",MB_OK);
        }
        else{
        send_Len=send(XServer,send_Buf,29,0);
        if(send_Len<0)
        {
            ui->textEdit->append("发送失败");
            QMessageBox::information(NULL,"提示框","由于使用的外接的服务器，可能会造成发送失败的情况，请重新启动程序即可！",MB_OK);
            this->close();
        }
        else{
            QString strmm="你发的消息："+str;
            ui->textEdit->append(strmm);
            ui->lineEdit->clear();
        }
        }
    }
}
 void Widget::keyPressEvent(QKeyEvent *ev)//监视键盘按键按下，执行某些操作
     {
         switch (ev->key()) {
         case Qt::Key_Enter://数字键盘的Enter键
         case Qt::Key_Return://Enter键
             clickSend(XS);//按下回车发送消息
             break;
         default:
             break;
         }
     }

void Widget::keyReleaseEvent(QKeyEvent *ev)//监视键盘按键释放，执行某些操作
{
    switch (ev->key()) {
    case Qt::Key_Enter:
        Sleep(1);
        break;
    default:
        break;
    }
}
