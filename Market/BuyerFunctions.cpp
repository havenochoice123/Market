#include"BuyerFunctions.h"
#include"ProductManagement.h"
#include"Utilities.h"
#include"UserManagement.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<chrono>
using namespace std;
//用户登录后的买家操作
void buyerMenu(Users& user) {
	while (true) {
		showBuyerMenu();
		int flag;
		cin >> flag;
		// 清理输入缓冲区
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (flag) {
		case 1: { //查看商品列表（仅销售中）
			showSellProduct();
			break;
		}
		case 2: { //购买商品
			buyProduct(user);
			break;
		}
		case 3: { //搜索商品
			searchProduct();
			break;
		}
		case 4: { //查看历史订单
			showAllOrders(user);
			break;
		}
		case 5: { //查看商品详细信息
			showDetailedInformationOfProduct();
			break;
		}
		case 6: { //返回用户主界面
			system("cls");
			cout << "已返回用户主界面！" << endl;
			return;
		}
		default: {
			cout << "输入错误！请重试" << endl;
			break;
		}
		}
	}
}

//显示买家菜单
void showBuyerMenu() {
	cout << "\n\n";
	cout << "\t\t    **************************************************    \n";
	cout << "\t\t    *                                                *    \n";
	cout << "\t\t    *                 ★ 买家中心 ★                   *    \n";
	cout << "\t\t    *                                                *    \n";
	cout << "\t\t    **************************************************    \n";
	cout << "\t\t    *                                                *    \n";
	cout << "\t\t    *        [1] 查看商品列表        [2] 购买商品    *    \n";
	cout << "\t\t    *                                                *    \n";
	cout << "\t\t    *        [3] 搜索商品            [4] 历史订单    *    \n";
	cout << "\t\t    *                                                *    \n";
	cout << "\t\t    *        [5] 商品详细信息        [6] 返回主界面  *    \n";
	cout << "\t\t    *                                                *    \n";
	cout << "\t\t    **************************************************    \n";
	cout << "\t\t    *               服务同学  诚信交易               *    \n";
	cout << "\t\t    **************************************************    \n";
	cout << "\n";
	cout << "\t\t\t\t请选择操作 (1-6): ";
}

//显示正在售出的商品列表
void showSellProduct() {
	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错！" << endl;
		return;
	}
	cout << "*****************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) << "名称" << setw(8) << "价格" << setw(15) << "上架时间" << setw(12) << "卖家ID" << endl;


	string line;
	while (getline(productFile, line)) {
		istringstream ss(line);
		string id, name, price, description, sellerId, putOnTime, status;

		// 读取商品信息
		getline(ss, id, ',');		//读取ID
		getline(ss, name, ',');		//读取名称
		getline(ss, price, ',');	//读取价格
		getline(ss, description, ',');//读取描述
		getline(ss, sellerId, ',');	//读取卖家ID
		getline(ss, putOnTime, ',');//读取上架时间
		getline(ss, status);   //读取状态（注意：最后一个字段不需要逗号分隔符）

		// 检查商品状态是否为 "销售中"
		if (status == "销售中") {
			cout << left << setw(12) << id << setw(12) << name << setw(8) << price << setw(15) << putOnTime << setw(12) << sellerId << endl; // 打印商品信息
		}

	}
	cout << "*****************************************************" << endl;
	productFile.close();

}

//买家购买商品
void buyProduct(Users& user) {
	cout << "请输入商品ID:";
	string buyId; cin >> buyId;

	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错" << endl;
		return;
	}

	string line;
	bool flag = false;//商品ID是否存在标志
	while (getline(productFile, line)) {
		istringstream ss(line);
		string id, name, price, description, sellerId, putOnTime, status;

		// 读取商品信息
		getline(ss, id, ',');		//读取ID
		//逐行匹配商品ID，检查是否存在
		if (id != buyId)continue;
		flag = true;
		//继续读取剩余信息
		getline(ss, name, ',');    //读取名称
		getline(ss, price, ',');   //读取价格
		getline(ss, description, ',');//读取描述
		getline(ss, sellerId, ',');	//读取卖家ID
		getline(ss, putOnTime, ',');//读取上架时间
		getline(ss, status, ',');   //读取状态
		if (status != "销售中") {
			cout << "该商品未在销售中！" << endl;
			productFile.close();
			return;
		}
		//防止购买自己发布的商品
		if (sellerId == user.getId()) {
			cout << "不能购买自己发布的商品！" << endl;
			productFile.close();
			return;
		}
		//确认是否购买
		cout << "确定购买？(y/n)";
		char i; cin >> i;
		cout << endl;
		if (i == 'y'|| i == 'Y') {
			double priceValue = stod(price);
			double balanceValue = stod(user.getBalance());
			if (balanceValue < priceValue) {
				cout << "当前余额不足！" << endl;
				return;
			}
			else {
				//设置新的余额
				double newBalance = balanceValue - priceValue;
				ostringstream balanceStream;
				balanceStream << fixed << setprecision(2) << newBalance;
				user.setBalance(balanceStream.str());
				//更新用户余额
				updateUserToFile(user);
				//打印交易信息
				cout << "*****************************" << endl;
				cout << "交易提醒！" << endl;
				//获取当前时间
				auto now = chrono::system_clock::now();
				time_t now_time = chrono::system_clock::to_time_t(now);
				//格式化时间
				tm* now_tm = localtime(&now_time);
				stringstream timeStream;
				timeStream << put_time(now_tm, "%Y-%m-%d %H:%M:%S");
				string transTime = timeStream.str();
				cout << "交易时间：" << transTime << endl;
				cout << "交易金额：" << priceValue << "元" << endl;
				cout << "交易状态：" << "交易成功" << endl;
				cout << "当前余额：" << newBalance << "元" << endl;
				cout << "*****************************" << endl;
				//存储订单
				string orderId;
				generateID(orderId, 3);//获取订单ID
				//更新商品状态
                updateProductToFile(Product(id, name, price, description, sellerId, putOnTime, "已售出"));
				ofstream orderFile("order.txt", ios::app);
				if (!orderFile) {
					cerr << "打开订单数据文件时出错" << endl;
				}
				else {
					//写入订单信息
					orderFile << orderId << ',' << id << ',' << fixed << setprecision(2) << stod(price) << ',' << transTime << ',' << user.getId() << ',' << sellerId << endl;
					orderFile.close();
				}

			}
		}
		else if (i == 'n' || i == 'N') {
			cout << "已取消购买商品" << endl;
			return;
		}
		else {
			cout << "请输入正确的字母,y表示是，n表示否" << endl;
			return;
		}
	}
	productFile.close();
	if (!flag) {
		cout << "该商品ID不存在！" << endl;
	}
}

//查看历史订单
void showAllOrders(Users& user) {
	ifstream orderFile("order.txt");
	if (!orderFile) {
		cerr << "打开订单数据文件时出错！" << endl;
		return;
	}
	//查看此时订单文件是否为空
	if (orderFile.peek() == EOF) {
		cout << "历史订单为空！" << endl;
		return;
	}
	//不为空，进行打印
	string line;
	bool flag = false;
	while (getline(orderFile, line)) {
		istringstream ss(line);
		string orderID, ID, price, dealTime, buyerID, sellerID;
		getline(ss, orderID, ',');
		getline(ss, ID, ',');
		getline(ss, price, ',');
		getline(ss, dealTime, ',');
		getline(ss, buyerID, ',');
		getline(ss, sellerID, ',');
		if (buyerID == user.getId()) {
            flag = true;
			cout << "*******************************************************************************" << endl;
			cout << left << setw(12) << "ID" << setw(12) << "商品ID" << setw(12) << "交易金额" << setw(25) << "交易时间" << setw(12) << "买家ID" << setw(12) << "卖家ID" << endl;
			cout << left << setw(12) << orderID << setw(12) << ID << setw(12) << price << setw(25) << dealTime << setw(12) << user.getId() << setw(12) << sellerID << endl;
			cout << "*******************************************************************************" << endl;
		}
	}
	if (!flag) {
        cout << "历史订单为空！" << endl;
    }
	orderFile.close();
}