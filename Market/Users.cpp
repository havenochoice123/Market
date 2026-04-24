#include"Users.h"
Users::Users(string id, string username, string password, string phone, string address, string balance)
{
	this->id = id;
	this->username = username;
	this->password = password;
	this->phone = phone;
	this->address = address;
	this->balance = balance;
}
Users::Users() :username("name"), password("123") {
}
void Users::setId(const string& id) {
	this->id = id;
}

void Users::setUsername(const string& username) {
	this->username = username;
}

void Users::setPassword(const string& password) {
	this->password = password;
}

void Users::setPhone(const string& phone) {
	this->phone = phone;
}

void Users::setAddress(const string& address) {
	this->address = address;
}

void Users::setBalance(const string& balance) {
	this->balance = balance;
}
string Users::getId() const {
	return id;
}

string Users::getUsername() const {
	return username;
}

string Users::getPassword() const {
	return password;
}

string Users::getPhone() const {
	return phone;
}

string Users::getAddress() const {
	return address;
}

string Users::getBalance() const {
	return balance;
}