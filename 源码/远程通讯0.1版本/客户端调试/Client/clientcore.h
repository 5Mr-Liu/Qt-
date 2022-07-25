#ifndef CLIENTCORE_H
#define CLIENTCORE_H
#pragma once

#include <iostream>
#include <string>
using namespace std;
#include <winsock.h>
#include <stdio.h>
#include "widget.h"
#include "ui_widget.h"
#pragma comment(lib,"ws2_32.lib")





class GetUI//定义的一个类，用以封装socket源码
{
public:
    Ui::Widget *cui;//自己定义的UI指针，控制界面控件用的
    GetUI(Ui::Widget *ui_ptr);//构造函数，可以获取ui界面的指针，便于操作控件
    void Initsock();//初始化套接字
    SOCKET Initserver();//服务器初始化
    ~GetUI();

};




#endif // CLIENTCORE_H
