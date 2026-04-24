#include"AdminManagement.h"
#include"ProductManagement.h"
#include"Product.h"
#include"Utilities.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include<vector>
using namespace std;

//管理员登录
void adminLogin() {
	string name, code, admininformation;
	cout << "------------------管理员登录----------------------" << endl;
	cout << "================================================" << endl;
	cout << "请输入管理员姓名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> code;
	string information, dh = ",";
	information = name + dh + code;
	ifstream ifs("admin.txt");
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	int n = 1;
	while (getline(ifs, admininformation))
	{
		if (admininformation == information)
		{
			n = 2;
			break;
		}
	}
	ifs.close();
	if (n == 2)
	{
		system("cls");
		cout << "******登录成功******" << endl;
		admin_menu();
	}
	else
	{
		system("cls");
		cout << "******登录失败！即将返回主菜单...******" << endl;
		return;
	}
}

//管理员菜单
void showAdmin_menu() {
    cout << "\n\n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *               ★ 管理员中心 ★                   *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *    [1] 查看所有商品    [2] 搜索商品            *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *    [3] 查看订单        [4] 查看所有用户        *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *    [5] 删除用户        [6] 下架商品            *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *    [7] 登出系统                                *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *               服务同学  诚信交易               *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\n";
    cout << "\t\t\t\t请选择操作 (1-7): ";
}
void admin_menu()
{
	while (true)
	{
		showAdmin_menu();
		cout << "请输入操作：";
		int flag;
		cin >> flag;
		// 清理输入缓冲区
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (flag)
		{
		case 1: { //查看所有商品
			admin_ViewProduct();
			break;
		}
		case 2: { //搜索商品
			admin_SearchProducts();
			break;
		}
		case 3: { //查看所有订单
			admin_ViewOrder();
			break;
		}
		case 4: { //查看所有用户
			admin_ViewUser();
			break;
		}
		case 5: { //删除用户
			admin_DeleteUser();
			break;
		}
		case 6: { //下架商品
			admin_Soldout();
			break;
		}
		case 7: { //登出
			system("cls");
			cout << "登出成功！" << endl;
			return;
		}
		default: {
			cout << "输入错误！请重试" << endl;
			break;
		}
		}
	}
}

//管理员查看商品
void admin_ViewProduct()
{
	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错" << endl;
		return;
	}
	cout << "*******************************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) << "名称" << setw(8) << "价格" << setw(15) << "上架时间" << setw(12) << "卖家ID" << setw(12) << "商品状态" << endl;
	cout << "*******************************************************************" << endl;

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

		// 打印所有商品信息
		cout << left << setw(12) << id << setw(12) << name << setw(8) << price << setw(15) << putOnTime << setw(12) << sellerId << setw(12) << status << endl;
	}
	productFile.close();
	cout << "*******************************************************************" << endl;
}

//管理员查看订单
void admin_ViewOrder()
{
	ifstream orderFile("order.txt");
	if (!orderFile) {
		cerr << "打开订单数据文件时出错！" << endl;
		return;
	}
	//查看此时订单文件是否为空
	if (orderFile.peek() == EOF) {
		cout << "现在无商品正在销售！" << endl;
		return;
	}
	//不为空，进行打印
	cout << "*******************************************************************************" << endl;
	cout << left << setw(12) << "ID" << setw(12) << "商品ID" << setw(12) << "交易金额" << setw(25) << "交易时间" << setw(12) << "买家ID" << setw(12) << "卖家ID" << endl;
	string line;
	while (getline(orderFile, line)) {
		istringstream ss(line);
		string orderID, ID, price, dealTime, buyerID, sellerID;
		getline(ss, orderID, ',');
		getline(ss, ID, ',');
		getline(ss, price, ',');
		getline(ss, dealTime, ',');
		getline(ss, buyerID, ',');
		getline(ss, sellerID, ',');
		cout << left << setw(12) << orderID << setw(12) << ID << setw(12) << price << setw(25) << dealTime << setw(12) << buyerID << setw(12) << sellerID << endl;
	}
	orderFile.close();
	cout << "*******************************************************************************" << endl;
}

//管理员搜索商品
void admin_SearchProducts()
{
	cout << "请选择搜索方式：" << endl;
	cout << "[1] 按名称搜索  [2] 按价格范围搜索  [3] 综合搜索" << endl;
	int searchType;
	cin >> searchType;
	
	// 检测输入错误
	if (cin.fail() || searchType < 1 || searchType > 3) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "输入错误！请输入1-3之间的数字。" << endl;
		return;
	}
	
	string productName = "";
	double minPrice = 0, maxPrice = 999999;
	
	if (searchType == 1 || searchType == 3) {
		cout << "请输入商品名称：";
		cin >> productName;
	}
	
	if (searchType == 2 || searchType == 3) {
		cout << "请输入最低价格：";
		cin >> minPrice;
		if (cin.fail() || minPrice < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "价格输入无效！" << endl;
			return;
		}
		cout << "请输入最高价格：";
		cin >> maxPrice;
		if (cin.fail() || maxPrice < minPrice) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "价格输入无效！" << endl;
			return;
		}
	}
	
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
	bool flag = false;//标志是否存在匹配的商品名称
	int counter = 0;//避免星号边框重复打印
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
		getline(ss, status);   //读取状态

		double productPrice = stod(price);
		bool nameMatch = true, priceMatch = true;
		
		//检查名称匹配
		if (searchType == 1 || searchType == 3) {
			nameMatch = ifHaveProduct(productName, name);
		}
		
		//检查价格匹配
		if (searchType == 2 || searchType == 3) {
			priceMatch = (productPrice >= minPrice && productPrice <= maxPrice);
		}
		
		//显示匹配条件的商品（管理员可查看所有状态商品）
		if (nameMatch && priceMatch) {
			counter++;
			flag = true;
			if (counter == 1) { //边框和列表名只打印一次
				cout << "****************************************************************" << endl;
				cout << left << setw(12) << "ID" << setw(12) << "名称" << setw(8) << "价格" << setw(15) << "上架时间" << setw(12) << "卖家ID" << setw(12) << "状态" << endl;
			}
			cout << left << setw(12) << id << setw(12) << name << setw(8) << price << setw(15) << putOnTime << setw(12) << sellerId << setw(12) << status << endl;
		}
	}
	if (counter > 0) cout << "****************************************************************" << endl; //打印最后的边框
	if (!flag) cout << "无匹配商品！" << endl;
	productFile.close();
}

//管理员查看用户
void admin_ViewUser(){
	ifstream userFile("user.txt");
	if (!userFile) {
		cerr << "打开商品数据文件时出错" << endl;
		return;
	}
	cout << "************************************************************************************" << endl;
	cout << left << setw(12) << "用户ID" << setw(12) << "用户名" << setw(15) << "电话" << setw(20) << "地址" << setw(12) << "钱包余额" << endl;
	string line;
	while (getline(userFile, line)) {
		istringstream ss(line);
		string id, username, password, phone, address, balance;

		// 读取用户信息
		getline(ss, id, ',');		//读取ID
		getline(ss, username, ',');		//读取用户名
		getline(ss, password, ',');	//读取密码
		getline(ss, phone, ',');//读取电话
		getline(ss, address, ',');	//读取地址
		getline(ss, balance, ',');//读取余额

		// 打印所有用户信息
		cout << left << setw(12) << id << setw(12) << username << setw(15) << phone << setw(20) << address << setw(12) << balance << endl;
	}
	userFile.close();
	cout << "************************************************************************************" << endl;
}

//管理员删除用户
void admin_DeleteUser()
{
	string deleteID;
	cout << "请输入您要删除的用户ID:";
	cin >> deleteID;

	ifstream inuserFile("user.txt");
	if (!inuserFile) {
		cout << "打开用户数据文件时出错！" << endl;
		return;
	}

	vector<string> validLines; // 存储需要保留的整行
	bool found = false;

	string line;
	while (getline(inuserFile, line)) {
		// 提取第一列（ID）进行比较
		istringstream ss(line);
		string id;
		getline(ss, id, ','); // 用逗号分割，获取ID

		if (id == deleteID) {
			found = true; // 标记已找到
		}
		else {
			validLines.push_back(line); // 保留有效行
		}
	}
	inuserFile.close();

	// 未找到用户
	if (!found) {
		cout << "未找到用户ID: " << deleteID << endl;
		return;
	}

	// 用覆盖模式打开文件（清空原内容）
	ofstream outuserFile("user.txt", ios::trunc);
	if (!outuserFile) {
		cerr << "无法覆盖写入用户文件！" << endl;
		return;
	}

	// 写入有效行
	for (const string& l : validLines) {
		outuserFile << l << endl;
	}
	outuserFile.close();

	cout << "用户ID " << deleteID << " 已成功删除！" << endl;
}

//管理员下架商品
void admin_Soldout() {
	cout << "请输入下架商品ID：" ;
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

		if (id == ID) {
			if (status == "已下架") {
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
						cout << "商品下架成功！" << endl;
					}
					else {
						cout << "商品下架失败！" << endl;
					}
					break;
				}
				else if (confirm == 'N' || confirm == 'n') {
					cout << "已取消下架操作！" << endl;
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
		cout << "该商品ID不存在!" << endl;
		return;
	}
}
