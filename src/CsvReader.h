#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>


class CsvReader {

public:
	CsvReader();
	static vector<OrderBookData> readCSV(string csvFile);
	static vector<string> tokenise(string csvLine, char separator);
	static OrderBookData strings_to_order(std::string product,
										  std::string price,
										  std::string amount,	
										  std::string timestamp,
										  orderType type);

private:
	
	static OrderBookData strings_to_order(vector<string> tokens);


};