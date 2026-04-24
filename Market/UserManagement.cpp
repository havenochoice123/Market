#include"UserManagement.h"
#include"BuyerFunctions.h"
#include"SellerFunctions.h"
#include"Utilities.h"
#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<iomanip>
// 显示主菜单
void showmenu() {
    cout << "\n\n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *            ★ 山西大学校园交易平台 ★            *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [1] 用户登录            [2] 用户注册    *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [3] 管理员登录          [4] 退出系统    *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *               服务同学  诚信交易               *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\n";
    cout << "\t\t\t\t请选择操作 (1-4): ";
}
//用户注册菜单
void clientRegister() {
	cout << "请输入用户名：";
	string username; cin >> username;
	ifstream in("user.txt");
	string data;
	if (!ifUnique(in, username, data)) {
		cout << "该用户名已存在！" << endl;
		return;
	}
	cout << "请输入密码：";
	string password; cin >> password;
	string temp = password;
	cout << "请再次输入密码：";
	cin >> password;
	if (temp != password) {
		cout << "两次输入的密码不一致！" << endl;
		return;
	}
	cout << "请输入电话：";
	string phone; 
	cin >> phone;
	//验证电话号码格式
	if (!isValidPhone(phone)) {
		cout << "电话号码格式错误！请输入11位数字的手机号码。" << endl;
		return;
	}
	cout << "请输入地址:";
	string address; cin >> address;
	string id; generateID(id, 1); //生成唯一ID
	string balance = "0.00"; //初始余额
	//写入文件
	ofstream outputFile("user.txt", ios::app); //追加写入
	if (!outputFile) {
		cerr << "打开用户数据文件时出错！" << endl;
		return;
	}
	// 写入新用户信息
	outputFile << id << "," << username << "," << password << "," << phone << "," << address << "," << balance << endl;
	outputFile.close();
	cout << "注册成功！" << endl;
}

//检测注册时用户名是否重复
//ifstream 对象不能直接按值传递，应该按引用传递
bool ifUnique(ifstream& in, string username, string& data) {
	if (!in.is_open()) {
		cout << "文件打开失败！" << endl; // 提示用户文件打开失败
		return false;
	}
	while (getline(in, data)) {
		size_t pos = data.find(','); // 找到用户名的位置
		if (pos != string::npos) {
			string storedUser = data.substr(pos + 1, data.find(',', pos + 1) - pos - 1); // 提取用户名
			if (username == storedUser) return false;
		}
	}
	in.close();
	return true;
}

//用户登录菜单
void clientLogin() {
	string username, password;
	cout << "------------------用户登录----------------------" << endl;
	cout << "================================================" << endl;
	cout << "请输入用户名:";
	cin >> username;
	cout << "请输入密码:";
	cin >> password;
	Users user;

	if (validateUser(username, password, user)) {
		system("cls");
		cout << "****** 登录成功！******" << endl;
		while (true) {
			personalMenu();
			cout << "请输入操作：";
			int flag;
			cin >> flag;
			// 清理输入缓冲区
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (flag)
			{
			case 1: { //注销登录
				system("cls");
				cout << "注销登录成功！" << endl;
				return;
			}
			case 2: { //买家菜单
				system("cls");
				buyerMenu(user);
				break;
			}
			case 3: { //卖家菜单
				system("cls");
				sellerMenu(user);
				break;
			}
			case 4: { //个人信息管理
				system("cls");
				personalInfomanagement(user);
				break;
			}
			default: {
				system("cls");
				cout << "输入错误！请重试" << endl;
				break;
			}
			}
		}
	}
	else {
		cout << "******用户名或密码错误，即将返回主菜单...******" << endl;
		return;
	}
}

//检测登录时用户名和密码是否正确
bool validateUser(const string& _username, const string& _password, Users& user) {
	ifstream userFile("user.txt");
	if (!userFile) {
		cerr << "错误，无法打开用户数据文件！" << endl;
		return false;
	}
	string line;
	while (getline(userFile, line)) {
		//分割行中的各个部分
		istringstream ss(line);
		string id, username, password, phone, address, balance;
		//读取文件中每一行的信息
		getline(ss, id, ',');          //读取id
		getline(ss, username, ',');    //读取用户名
		getline(ss, password, ',');    //读取密码
		getline(ss, phone, ',');       //读取电话号码
		getline(ss, address, ',');     //读取地址
		getline(ss, balance, ',');     //读取余额
		if (_username == username && _password == password) {
			//用户验证成功，同时加载用户数据
			user.setId(id);
			user.setUsername(username);
			user.setPassword(password);
			user.setPhone(phone);
			user.setAddress(address);
			user.setBalance(balance);
			userFile.close();
			return true;
		}

	}
	userFile.close();
	return false;
}

//建立用户登陆成功后的主菜单，以便进行下一步操作
void personalMenu() {
    cout << "\n\n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *                  ★ 用户中心 ★                  *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [1] 注销登录            [2] 我是买家    *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [3] 我是卖家            [4] 信息管理    *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *               服务同学  诚信交易               *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\n";
    cout << "\t\t\t\t请选择操作 (1-4): ";
}

//用户登录后，用于个人信息的查看和修改
void personalInfomanagement(Users& user) {
	while (true) {
		personalInformationMenu();
		int flag; cin >> flag;
		// 清理输入缓冲区
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (flag) {
		case 1: {
			system("cls");
			cout << "已返回用户主界面！" << endl;
			return;
		}
		case 2: {
			changeInformation(user);
			break;
		}
		case 3: {
			showInformation(user);
			break;
		}
		case 4: {
			recharge(user);
			break;
		}
		default: {
			cout << "输入错误！请重试" << endl;
			break;
		}
		}
	}
}

// 显示个人信息菜单
void personalInformationMenu() {
    cout << "\n\n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *               ★ 个人信息中心 ★                 *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [1] 返回用户主界面      [2] 修改信息    *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    *        [3] 查看信息            [4] 充值        *    \n";
    cout << "\t\t    *                                                *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\t\t    *               服务同学  诚信交易               *    \n";
    cout << "\t\t    **************************************************    \n";
    cout << "\n";
    cout << "\t\t\t\t请选择操作 (1-4): ";
}

//修改个人信息
void changeInformation(Users& user) {
	cout << "请选择修改的属性（1.用户名 2.电话 3.地址）：";
	int flag; cin >> flag;
	switch (flag) {
	case 1: {
		cout << "请输入修改后的用户名：";
		string username; cin >> username;
		ifstream in("user.txt");
		string data;
		if (!ifUnique(in, username, data)) {
			cout << "该用户名已存在！" << endl;
			in.close();
			return;
		}
		in.close();
		user.setUsername(username);
		if (updateUserToFile(user)) cout << "用户信息更新成功！" << endl; // 立即保存到文件
		break;
	}
	case 2: {
		cout << "请输入修改后的电话：";
		string phone; cin >> phone;
		user.setPhone(phone);
		if(updateUserToFile(user)) cout << "用户信息更新成功！" << endl;; // 立即保存到文件
		break;
	}
	case 3: {
		cout << "请输入修改后的地址：";
		string address; cin >> address;
		user.setAddress(address);
		if(updateUserToFile(user)) cout << "用户信息更新成功！" << endl;; // 立即保存到文件
		break;
	}
	default: {
		cout << "输入错误！请重试" << endl;
		break;
	}
	}
}

//更新用户信息到文件
bool updateUserToFile(const Users& user) {
	// 读取所有行
	ifstream inputFile("user.txt");
	if (!inputFile) {
		cerr << "打开用户数据文件时出错！" << endl;
		return false;
	}

	vector<string> lines;
	string line;
	bool userFound = false;

	while (getline(inputFile, line)) {
		istringstream ss(line);
		string id, username, password, phone, address, balance;
		getline(ss, id, ',');
		getline(ss, username, ',');
		getline(ss, password, ',');
		getline(ss, phone, ',');
		getline(ss, address, ',');
		getline(ss, balance);

		//如果是要更新的用户，替换整行
		if (id == user.getId()) {
			string newUserLine = user.getId() + "," + user.getUsername() + "," +
				user.getPassword() + "," + user.getPhone() + "," +
				user.getAddress() + "," + user.getBalance();
			lines.push_back(newUserLine);
			userFound = true;
		}
		//不是目标用户，保留并写入文件
		else {
			lines.push_back(line);
		}
	}
	inputFile.close();

	if (!userFound) {
		cerr << "未找到要更新的用户！" << endl;
		return false;
	}

	//写回文件
	ofstream outputFile("user.txt");
	if (!outputFile) {
		cerr << "打开用户数据文件时出错！" << endl;
		return false;
	}

	for (const string& fileLine : lines) {
		outputFile << fileLine << endl;
	}
	outputFile.close();

	return true;
}

//查看个人信息
void showInformation(Users& user) {
	cout << "*********************************************" << endl;
	cout << "用户名：" << user.getUsername() << endl;
	cout << "电话：" << user.getPhone() << endl;
	cout << "地址：" << user.getAddress() << endl;
	cout << "余额：" << fixed << setprecision(2) << stod(user.getBalance()) << "元" << endl;
	cout << "*********************************************" << endl;
}

//充值
void recharge(Users& user) {
	cout << "请输入充值数目：";
	double money; cin >> money;
	//如果输入的不是数字
	if (cin.fail()) {
		/*
		* 获取failbit的值，在输入的时候，如果是整形变量int，输入char类型的字符，failbit的值会由0变为1，
		* 输入的字符会卡在输入缓冲区导致后面无法进行输入操作。
		* 此时我们使用cin.clear()可以
		*/
		cin.clear();
		/*
		* 使failbit重新变为0，但此时我们还是无法进行输入的操作,
		* 因为此时缓冲区中有残留数据，cin对象会直接取得这些残留数据而不会请求键盘输入
		*/
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		/*
		* 忽略输入流中的所有字符，直到遇到换行符（或达到指定的最大字符数）
		* 将输入缓冲区的字符取出来，这样就能进行后续的输入了
		*/
		cout << "输入无效，请输入有效的数字金额。" << endl;
		return;
	}
	//如果输入了负数或零
	if (money <= 0) {
		cout << "充值金额必须为正数！" << endl;
		return;
	}
	//计算新余额
	double currentBalance = stod(user.getBalance());
	double newBalance = currentBalance + money;
	//格式化新余额
	ostringstream ss;
	ss << fixed << setprecision(2) << newBalance;
	string formattedBalance = ss.str();
	user.setBalance(formattedBalance);
	//重新写入文件
	updateUserToFile(user);
	cout <<  "*********************************************" << endl;
	cout <<  "充值成功！" << endl;
	cout <<  "当前余额：" << formattedBalance << "元" << endl;
}

//退出
void systemExit() {
	cout << "已成功退出！" << endl;
	exit(0);
}

//验证电话号码格式
bool isValidPhone(const string& phone) {
	//检查长度是否为11位
	if (phone.length() != 11) {
		return false;
	}
	//检查是否以1开头
	if (phone[0] != '1') {
		return false;
	}
	//检查是否全为数字
	for (char c : phone) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}