#include"Utilities.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
//生成唯一的用户/商品/订单ID
void generateID(string& id, int flag) {
	if (flag == 1) {
		string defaultID = "U00000"; //默认起始ID
		ifstream userFile("user.txt");
		if (!userFile) {
			cerr << "打开用户数据文件时出错！" << endl;
			return;
		}
		string line;
		while (getline(userFile, line)) {
			//查看此时用户文件是否为空
			if (!line.empty()) {
				istringstream ss(line);
				getline(ss, defaultID, ',');
			}
		}
		userFile.close();
		//提取ID中的数字部分
		string pre = defaultID.substr(0, 1); //'U'
		string numPart = defaultID.substr(1); //'0000X'
		//将数字转换为整数并自增
		int num = stod(numPart);
		num++;
		//格式化新ID,不足的前面补0
		ostringstream userID;
		userID << pre << setw(5) << setfill('0') << num;
		id = userID.str();
	}
	else if (flag == 2) {
		string defaultID = "M00000"; //默认起始ID
		ifstream orderFile("product.txt");
		if (!orderFile) {
			cerr << "打开商品数据文件时出错！" << endl;
			return;
		}
		string line;
		while (getline(orderFile, line)) {
			//查看此时商品文件是否为空
			if (!line.empty()) {
				istringstream ss(line);
				getline(ss, defaultID, ',');
			}
		}
		orderFile.close();
		//提取ID中的数字部分
		string pre = defaultID.substr(0, 1); //'M'
		string numPart = defaultID.substr(1); //'0000X'
		//将数字转换为整数并自增
		int num = stod(numPart);
		num++;
		//格式化新ID,不足的前面补0
		ostringstream orderID;
		orderID << pre << setw(5) << setfill('0') << num;
		id = orderID.str();
	}
	else {
		string defaultID = "T00000"; //默认起始ID
		ifstream orderFile("order.txt");
		if (!orderFile) {
			cerr << "打开订单数据文件时出错！" << endl;
			return;
		}
		string line;
		while (getline(orderFile, line)) {
			//查看此时订单文件是否为空
			if (!line.empty()) {
				istringstream ss(line);
				getline(ss, defaultID, ',');
			}
		}
		orderFile.close();
		//提取ID中的数字部分
		string pre = defaultID.substr(0, 1); //'T'
		string numPart = defaultID.substr(1); //'0000X'
		//将数字转换为整数并自增
		int num = stod(numPart);
		num++;
		//格式化新ID,不足的前面补0
		ostringstream orderID;
		orderID << pre << setw(5) << setfill('0') << num;
		id = orderID.str();
	}
}

