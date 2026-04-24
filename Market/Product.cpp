#include"Product.h"

Product::Product():
    ID(""),
    name(""),
    price(""),
    description(""),
    sellerID(""),
    putOnTime(""),
     status(""){
}

Product::Product(string ID, string name, string price, string description, string sellerID, string putOnTime, string status) :
    ID(ID),
    name(name),
    price(price),
    description(description),
    sellerID(sellerID),
    putOnTime(putOnTime),
    status(status) {
}

string Product::getID() const {
    return ID;
}

string Product::getName() const {
    return name;
}

string Product::getPrice() const {
    return price;
}

string Product::getDescription() const {
    return description;
}

string Product::getSellerID() const {
    return sellerID;
}

string Product::getPutOnTime() const {
    return putOnTime;
}

string Product::getStatus() const {
    return status;
}

void Product::setID(const string& id) {
    ID = id;
}

void Product::setName(const string& newName) {
    name = newName;
}

void Product::setPrice(const string& newPrice) {
    price = newPrice;
}

void Product::setDescription(const string& desc) {
    description = desc;
}

void Product::setSellerID(const string& seller) {
    sellerID = seller;
}

void Product::setPutOnTime(const string& time) {
    putOnTime = time;
}

void Product::setStatus(const string& newStatus) {
    status = newStatus;
}