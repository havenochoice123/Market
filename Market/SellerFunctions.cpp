#include"SellerFunctions.h"
#include"Utilities.h"
#include"Product.h"
#include"ProductManagement.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<chrono>
//用户登录后的卖家操作
void sellerMenu(Users& user) {
	while (true) {
		showSellerMenu();
		int flag;
		cin >> flag;
		// 清理输入缓冲区
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (flag)
		{
		case 1: { //发布商品
			sellerDistributeproduct(user);
			break;
		}
		case 2: { //查看发布商品
			sellershowproduct(user);
			break;
		}
		case 3: { //修改商品信息
			sellerReviseproduct(user);
			break;
		}
		case 4: { //下架商品
			sellerRemoveproduct(user);
			break;
		}
		case 5: { //查看历史订单
			sellerShowPreviousOrders(user);
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

// 显示卖家菜单
void showSellerMenu() {
    cout << "\n\n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *                 ★ 卖家中心 ★                   *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [1] 发布商品            [2] 查看发布商品*    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [3] 修改商品信息        [4] 下架商品    *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [5] 查看历史订单        [6] 返回主界面  *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *               服务同学  诚信交易               *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\n";
    cout << "\t\t\t\t请选择操作 (1-6): ";
}

//发布商品
void sellerDistributeproduct(Users& user) {
	string productID, productPrice, productName, productDescribe, putOnTime;
	double price;
	char flag;
	cout << "请输入商品名称："; cin >> productName;
	//验证商品名称不能为空
	if (productName.empty() || productName.find_first_not_of(' ') == string::npos) {
		cout << "商品名称不能为空！" << endl;
		return;
	}
	cout << "请输入商品金额："; cin >> price;
	// 验证价格输入
	if (cin.fail() || price <= 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "无效的价格输入，请输入正数。" << endl;
		return;
	}
	// 格式化价格为两位小数
	ostringstream ss;
	ss << fixed << setprecision(2) << price;
	productPrice = ss.str();
	//获取当前时间
	auto now = chrono::system_clock::now();
	time_t now_time = chrono::system_clock::to_time_t(now);
	//格式化时间
	tm* now_tm = localtime(&now_time);
	stringstream timeStream;
	timeStream << put_time(now_tm, "%Y-%m-%d");//%H:%M:%S
	putOnTime = timeStream.str();
	cout << "请输入商品描述：" << endl;
	cin.ignore(); // 清除输入缓冲区
	getline(cin, productDescribe); // 使用getline读取完整描述
	// 将英文逗号替换为中文逗号
	string temp = "";
	for (char c : productDescribe) {
		if (c == ',') {
			temp += "，"; // 中文逗号
		} else {
			temp += c;
		}
	}
	productDescribe = temp;
	//生成商品ID
	generateID(productID, 2);

	cout << "请确认商品的信息无误!" << endl;
	cout << "==============================" << endl;
	cout << "商品名称：" << productName << endl;
	cout << "商品金额：" << productPrice << endl;
	cout << "商品上架时间：" << putOnTime << endl;
	cout << "商品描述：" << productDescribe << endl;
	cout << "==============================" << endl;
	cout << "您确定要发布商品吗？（y/n）" << endl;
	cin >> flag;

	if (flag == 'y' || flag == 'Y') {
		//写回文件
		ofstream outputFile("product.txt", ios::app);
		if (!outputFile) {
			cerr << "打开商品数据文件时出错！" << endl;
			return;
		}
		outputFile << productID << "," << productName << "," << productPrice << "," << productDescribe << "," << user.getId() << ","
			<< putOnTime << "," << "销售中" << endl;
		outputFile.close();
		cout << "发布商品成功！" << endl;
	}
	else if (flag == 'n' || flag == 'N') {
		cout << "已取消发布商品" << endl;
	}
	else {
		cout << "请输入正确的字母，y表示是，n表示否" << endl;
	}
}

//查看发布商品（只能看到自己售卖的商品）
void sellershowproduct(Users& user) {
	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错！" << endl;
		return;
	}
	cout << "**************************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) << "名称" << setw(8) << "价格" << setw(12) << "上架时间" << setw(12) << "卖家ID" << setw(12) << "状态" << endl;

	string line;
	bool hasProducts = false;
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

		// 检查卖家ID是否为一致
		if (user.getId() == sellerId) {
			hasProducts = true;
			cout << left << setw(12) << id << setw(12) << name << setw(8) << price << setw(12) << putOnTime << setw(12) << sellerId << setw(12) << status << endl; // 打印商品信息
		}

	}
	if (!hasProducts) {
		cout << "您还没有发布任何商品。" << endl;
	}
	cout << "**************************************************************" << endl;
	productFile.close();
}

//修改商品信息
void sellerReviseproduct(Users& user) {
	cout << "************************************" << endl;
	cout << "请输入修改商品ID：" << endl;
	string ID; cin >> ID;
	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错！" << endl;
		return;
	}
	//检查文件是否为空
	if (productFile.peek() == EOF) {
		cout << "现在无商品正在销售！" << endl;
		return;
	}
	//文件不为空，进行搜索
	string line;
	bool flag = false; //商品ID存在标志
	Product product; // 创建商品对象用于存储和修改

	while (getline(productFile, line)) {
		istringstream ss(line);
		string id, name, price, description, sellerId, putOnTime, status;

		// 读取商品信息
		getline(ss, id, ',');       //读取ID
		getline(ss, name, ',');     //读取名称
		getline(ss, price, ',');    //读取价格
		getline(ss, description, ',');//读取描述
		getline(ss, sellerId, ','); //读取卖家ID
		getline(ss, putOnTime, ',');//读取上架时间
		getline(ss, status);   //读取状态

		if (id == ID && sellerId == user.getId()) {
			flag = true;
			// 将找到的商品信息存入商品对象
			product.setID(id);
			product.setName(name);
			product.setPrice(price);
			product.setDescription(description);
			product.setSellerID(sellerId);
			product.setPutOnTime(putOnTime);
			product.setStatus(status);

			cout << "请输入修改商品属性（1.价格 2.描述）" << endl;
			int newProperty; cin >> newProperty;
			// 清理输入缓冲区
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (newProperty) {
			case 1: {
				double price;
				cout << "请输入修改后的价格：" << endl;
                cin >> price;
				// 验证价格输入
				if (cin.fail() || price <= 0) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "无效的价格输入，请输入正数。" << endl;
					return;
				}
				// 格式化价格为两位小数
				ostringstream ss;
				ss << fixed << setprecision(2) << price;
				string newPrice; newPrice = ss.str();
				product.setPrice(newPrice); // 更新商品价格
				break;
			}
			case 2: {
				cout << "请输入修改后的商品描述：" << endl;
				string newDescription;
				cin.ignore(); // 忽略之前输入中的换行符
				getline(cin, newDescription); // 使用getline读取可能包含空格的描述
				// 将英文逗号替换为中文逗号
				string temp = "";
				for (char c : newDescription) {
					if (c == ',') {
						temp += "，"; // 中文逗号
					} else {
						temp += c;
					}
				}
				newDescription = temp;
				product.setDescription(newDescription); // 更新商品描述
				break;
			}
			default: {
				cout << "输入错误！请重试" << endl;
				productFile.close();
				return;
			}
			}
			break; // 找到并修改后跳出循环
		}
	}
	productFile.close(); // 关闭文件

	if (!flag) {
		cout << "该商品ID不存在或卖家ID不一致！" << endl;
		return;
	}

	// 显示修改后的商品信息
	cout << "请确认修改后的商品信息！" << endl;
	cout << "*************************" << endl;
	cout << "商品ID: " << product.getID() << endl;
	cout << "商品名称: " << product.getName() << endl;
	cout << "商品价格: " << product.getPrice() << endl;
	cout << "商品描述: " << product.getDescription() << endl;
	cout << "*************************" << endl;
	cout << "是否确认修改？(y/n)" << endl;
	char confirm;
	cin >> confirm;

	if (confirm == 'Y' || confirm == 'y') {
		// 调用更新商品信息函数
		if (updateProductToFile(product)) {
			cout << "商品信息修改成功！" << endl;
		}
		else {
			cout << "商品信息修改失败！" << endl;
		}
	}
	else {
		cout << "已取消修改！" << endl;
	}
	cout << "************************************" << endl;
}

//下架商品
void sellerRemoveproduct(Users& user) {
	cout << "请输入下架商品ID：" << endl;
	string ID; cin >> ID;
	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错" << endl;
		return;
	}
	//检查文件是否为空
	if (productFile.peek() == EOF) {
		cout << "现在无商品正在销售！" << endl;
		return;
	}
	//文件不为空，进行搜索
	string line;
	bool flag = false; //商品ID存在标志
	Product product; // 创建商品对象用于存储和修改

	while (getline(productFile, line)) {
		istringstream ss(line);
		string id, name, price, description, sellerId, putOnTime, status;

		// 读取商品信息
		getline(ss, id, ',');       //读取ID
		getline(ss, name, ',');     //读取名称
		getline(ss, price, ',');    //读取价格
		getline(ss, description, ',');//读取描述
		getline(ss, sellerId, ','); //读取卖家ID
		getline(ss, putOnTime, ',');//读取上架时间
		getline(ss, status);   //读取状态

		if (id == ID && sellerId == user.getId()) {
			if(status == "已下架") {
				cout << "该商品已下架！" << endl;
				return;
			}
			flag = true;
			Product product;
			// 将找到的商品信息存入商品对象
			product.setID(id);
			product.setName(name);
			product.setPrice(price);
			product.setDescription(description);
			product.setSellerID(sellerId);
			product.setPutOnTime(putOnTime);

			cout << "您确定要下架该商品吗？" << endl;
			cout << "*************************" << endl;
			cout << "商品ID：" << id << endl;
			cout << "商品名称：" << name << endl;
			cout << "商品金额：" << price << endl;
			cout << "商品描述：" << description << endl;
			cout << "*************************" << endl;
			while (true) {
				cout << "请选择(y/n)" << endl;
				char confirm; cin >> confirm;
				if (confirm == 'Y' || confirm == 'y') {
					// 调用更新商品信息函数
					product.setStatus("已下架");
					if (updateProductToFile(product)) {
						cout << "商品信息修改成功！" << endl;
					}
					else {
						cout << "商品信息修改失败！" << endl;
					}
					break;
				}
				else if (confirm == 'N' || confirm == 'n') {
					cout << "已取消修改！" << endl;
					break;
				}
				else {
					cout << "输入错误，请重试！" << endl;
				}
			}
			break; // 找到后跳出循环
		}
	}
	productFile.close(); // 关闭文件

	if (!flag) {
		cout << "该商品ID不存在或卖家ID不一致！" << endl;
		return;
	}
}

//查看历史订单
void sellerShowPreviousOrders(Users& user) {
	ifstream orderFile("order.txt");
	if (!orderFile) {
		cerr << "打开订单数据文件时出错！" << endl;
		return;
	}
	//检查文件是否为空
	if (orderFile.peek() == EOF) {
		cout << "无历史订单！" << endl;
		return;
	}
	//文件不为空，进行搜索
	string line;
	bool flag = false; //是否存在历史订单标志
	while (getline(orderFile, line)) {
		//查看此时订单文件是否为空，
		istringstream ss(line);
		string orderID, ID, price, dealTime, sellerID, buyerID;
		getline(ss, orderID, ',');
		getline(ss, ID, ',');
		getline(ss, price, ',');
		getline(ss, dealTime, ',');
		getline(ss, sellerID, ',');
		getline(ss, buyerID, ',');
		if (sellerID == user.getId()) {
			flag = true;
			cout << "*******************************************************************************" << endl;
			cout << left << setw(12) << "ID" << setw(12) << "商品ID" << setw(12) << "交易金额" << setw(25) << "交易时间" << setw(12) << "买家ID" << setw(12) << "卖家ID" << endl;
			cout << left << setw(12) << orderID << setw(12) << ID << setw(12) << price << setw(25) << dealTime << setw(12) << buyerID << setw(12) << sellerID << endl;
			cout << "*******************************************************************************" << endl;
		}
	}
	orderFile.close();
	
	if (!flag) {
		cout << "历史订单为空！" << endl;
	}
}

//返回用户主界面
void sellerlogout() {
	cout << "卖家登出成功" << endl;
	return;
}