#pragma once
#include <string>
#include "Users.h"
using namespace std;
void showmenu();
void clientRegister();
bool ifUnique(ifstream& in, string username, string& data);
void clientLogin();
bool validateUser(const string& _username, const string& _password, Users& user);
void personalMenu();
void personalInfomanagement(Users& user);
void personalInformationMenu();
void changeInformation(Users& user);
bool updateUserToFile(const Users& user);
void showInformation(Users& user);
void recharge(Users& user);
void systemExit();
bool isValidPhone(const string& phone);
