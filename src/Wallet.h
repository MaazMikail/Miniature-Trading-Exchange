#pragma once
#include <string>
#include <map>
#include "OrderBookEntry.h"
#include <vector>
#include "CsvReader.h"


class Wallet {


public:
	Wallet();
	void insertCurrency(std::string type, double amount);
	bool containsCurrency(std::string type, double amount);
	bool removeCurrency(std::string type, double amount);
	std::string toString();
	bool canFullFillOrder(OrderBookData order);
	void processSale(OrderBookData& sale);

private:
	std::map<std::string, double> currencies;
	

};