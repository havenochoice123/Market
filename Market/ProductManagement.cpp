#include"ProductManagement.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
//更新商品信息到文件
bool updateProductToFile(const Product& product) {
	// 读取所有行
	ifstream inputFile("product.txt");
	if (!inputFile) {
		cerr << "打开商品数据文件时出错！" << endl;
		return false;
	}

	vector<string> lines;
	string line;
	bool productFound = false;

	while (getline(inputFile, line)) {
		istringstream ss(line);
		string id, name, price, description, sellerId, putOnTime, status;
		getline(ss, id, ',');
		getline(ss, name, ',');
		getline(ss, price, ',');
		getline(ss, description, ',');
		getline(ss, sellerId, ',');
		getline(ss, putOnTime, ',');
		getline(ss, status);

		//如果是要更新的商品，替换整行
		if (id == product.getID()) {
			string newProductLine = product.getID() + "," + product.getName() + "," +
				product.getPrice() + "," + product.getDescription() + "," +
				product.getSellerID() + "," + product.getPutOnTime() + "," +
				product.getStatus();
			lines.push_back(newProductLine);
			productFound = true;
		}
		//不是目标商品，保留并写入文件
		else {
			lines.push_back(line);
		}
	}
	inputFile.close();

	if (!productFound) {
		cerr << "未找到要更新的商品！" << endl;
		return false;
	}

	//写回文件
	ofstream outputFile("product.txt");
	if (!outputFile) {
		cerr << "打开商品数据文件时出错！" << endl;
		return false;
	}

	for (const string& fileLine : lines) {
		outputFile << fileLine << endl;
	}
	outputFile.close();
	return true;
}

//查找是否含有商品（贪心算法）
bool ifHaveProduct(const string& searchName, const string& name) {
	int searchIndex = 0;
	int nameIndex = 0;
	vector<int> matchName;
	//遍历原商品列表名称
	while (searchIndex < searchName.length() && nameIndex < name.length()) {
		//如果当前字符匹配，移动查找指针
		if (searchName[searchIndex] == name[nameIndex]) {
			matchName.push_back(nameIndex);
			searchIndex++;
		}
		//无论是否匹配，都移动商品名称指针
		nameIndex++;
	}
	//判断是否找到完整的子序列
	return searchIndex == searchName.length();
}

//搜索商品（用户）
void searchProduct() {
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
		
		//只显示销售中且匹配条件的商品
		if (nameMatch && priceMatch && status == "销售中") {
			counter++;
			flag = true;
			if (counter == 1) { //边框和列表名只打印一次
				cout << "*****************************************************" << endl;
				cout << left << setw(12) << "ID" << setw(12) << "名称" << setw(8) << "价格" << setw(15) << "上架时间" << setw(12) << "卖家ID" << endl;
			}
			cout << left << setw(12) << id << setw(12) << name << setw(8) << price << setw(15) << putOnTime << setw(12) << sellerId << endl;
		}
	}
	if (counter > 0) cout << "*****************************************************" << endl; //打印最后的边框
	if (!flag)cout << "无匹配商品！" << endl;
	productFile.close();
}

//查看商品详细信息
void showDetailedInformationOfProduct() {
	cout << "请输入您想查看的商品ID：";
	string id; cin >> id;
	ifstream productFile("product.txt");
	if (!productFile) {
		cerr << "打开商品数据文件时出错！" << endl;
		return;
	}
	else {
		string line;
		bool flag = false;
		while (getline(productFile, line)) {
			istringstream ss(line);
			string productId, name, price, description, sellerId, putOnTime, status;
			// 读取商品信息
			getline(ss, productId, ',');		//读取ID
			//比较要查找的ID
			if (productId != id)continue;
			flag = true;
			getline(ss, name, ',');		//读取名称
			getline(ss, price, ',');	//读取价格
			getline(ss, description, ',');//读取描述
			getline(ss, sellerId, ',');	//读取卖家ID
			getline(ss, putOnTime, ',');//读取上架时间
			getline(ss, status);   //读取状态
			//打印商品信息
			cout << "*************************" << endl;
			cout << "名称：" << name << endl;
			cout << "描述：" << description << endl;
			cout << "上架时间：" << putOnTime << endl;
			cout << "卖家ID：" << sellerId << endl;
			cout << "商品状态：" << status << endl;
			cout << "*************************" << endl;
		}
		if (!flag) {
			cout << "该商品ID不存在！" << endl;
		}
	}
}