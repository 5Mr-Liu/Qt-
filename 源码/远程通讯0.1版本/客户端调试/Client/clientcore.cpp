
#include "clientcore.h"

#include <QDebug>
GetUI::GetUI(Ui::Widget *ui_ptr)
{

   cui=ui_ptr;//获取UI界面指针，控制控件

    WORD w_VR = MAKEWORD(2, 2);
    /*设置网络套接字版本。前面是低位字节，后面是高位字节*/
    WSADATA wsadata;
    int error;
    error = WSAStartup(w_VR, &wsadata);
    if (error != 0) {
        //cout << "初始化套接字失败！" << endl;
        cui->textEdit->append("初始化套接字失败！");
    }
    else {
        //cout << "初始化套接字成功！" << endl;
        cui->textEdit->append("初始化套接字成功！");
    }

    if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
        //cout << "套接字版本错误！" << endl;
        cui->textEdit->append("套接字版本错误！");
        WSACleanup();
    }
    else {
        //cout << "套接字版本正确！" << endl;
        cui->textEdit->append("套接字版本正确！");
    }
}

/*-----------------服务器初始化------------*/
SOCKET GetUI::Initserver()
{

    int send_Len = 0;//发送消息的长度
    int recv_Len = 0;//接受消息的长度
    char  Send_buf[1000]={0};//存放发送消息的数组
    char Recv_buf[1000]={0};//存放接受消息的数组

    SOCKET XServer;  /*服务器套接字*/

    SOCKADDR_IN server_addr;/*服务端地址*/

    //Initsock();
    /*------------套接字初始化---------------*/

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.S_un.S_addr = inet_addr("115.29.240.46");//"127.0.0.1"本机的ip
    server_addr.sin_port = htons(9000);
    /*------------套接字创建-----------------*/

    XServer = socket(AF_INET, SOCK_STREAM, 0);/*修改为非阻塞的SOCKET   0*/

    if (::connect(XServer, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        //cout << "服务器连接失败！" << endl;
        cui->textEdit->append("服务器连接失败！");

        WSACleanup();


    }
    else {
        //cout << "服务器连接成功！" << endl;
         cui->textEdit->append("服务器连接成功！");
    }
   return XServer;
}

/*---------------套接字初始化------------------*/
void GetUI::Initsock()//没用到的函数，没删掉
{


}
GetUI::~GetUI()
{

}

