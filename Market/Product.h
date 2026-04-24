#pragma once
#include<string>
using namespace std;
class Product {
public:
	Product();
	Product(string ID, string name, string price, string description, string sellerID, string putOnTime, string status);

    string getID() const;
    string getName() const;
    string getPrice() const;
    string getDescription() const;
    string getSellerID() const;
    string getPutOnTime() const;
    string getStatus() const;

    void setID(const string& id);
    void setName(const string& newName);
    void setPrice(const string& newPrice);
    void setDescription(const string& desc);
    void setSellerID(const string& seller);
    void setPutOnTime(const string& time);
    void setStatus(const string& newStatus);
private:
	string ID, name, price, description, sellerID, putOnTime, status;
};