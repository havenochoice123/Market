#pragma once
#include <string>
#include "Product.h"
using namespace std;
bool updateProductToFile(const Product& product);
bool ifHaveProduct(const string& searchName, const string& name);
void searchProduct();
void showDetailedInformationOfProduct();
