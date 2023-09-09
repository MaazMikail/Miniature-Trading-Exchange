#pragma once

#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "CsvReader.h"




class OrderBook {

public:

	OrderBook(std::string filename);
	std::vector<std::string> getKnownProducts();
	std::vector<OrderBookData> getOrders(orderType type, std::string product, std::string timestamp);
	std::vector<std::string> getKnowntimestamps();
	static double getHighprice(std::vector<OrderBookData> orders);
	static double getLowprice(std::vector<OrderBookData> orders);
	std::vector<OrderBookData> match(std::string product, std::string timestamp);
	std::string getEarliestTime();
	std::string getNextTime(std::string currentTime);
	void insertOrder(OrderBookData order);
	
	
private:
	std::vector<OrderBookData> orders;


};