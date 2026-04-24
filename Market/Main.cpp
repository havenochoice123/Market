#include"UserManagement.h"
#include"AdminManagement.h"
#include<iostream>
using namespace std;
int main() {
	while (true) {
		showmenu();
		int flag;
		cin >> flag;
		// 清理输入缓冲区
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (flag)
		{
		case 1: {
			system("cls");//清屏
			clientLogin();//用户登录
			break;
		}
		case 2: {
			system("cls");
			clientRegister();//用户注册
			break;
		}
		case 3: {
			system("cls");
			adminLogin();//管理员登录
			break;
		}
		case 4: {
			system("cls");
			systemExit();//退出程序
			break;
		}
		default: {
			cout << "输入错误！请重试" << endl;
			break;
		}
		}
	}
	return 0;
}