#pragma once
#include<string>
using namespace std;
class Users {
public:
	Users();
	Users(string id, string username, string password, string phone, string address, string balance);
    void setId(const string& id);
    void setUsername(const string& username);
    void setPassword(const string& password);
    void setPhone(const string& phone);
    void setAddress(const string& address);
    void setBalance(const string& balance);
    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getPhone() const;
    string getAddress() const;
    string getBalance() const;
private:
	string id,username, password,phone,address,balance;
};