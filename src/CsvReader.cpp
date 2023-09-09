#include "CsvReader.h"
#include <fstream>


CsvReader::CsvReader() {}


vector<OrderBookData> CsvReader::readCSV(string csvFilename) {

    ifstream csvFile{csvFilename};
	vector<OrderBookData> data;
    string line;

    if (csvFile.is_open()) {

        while (getline(csvFile, line)) {


            try {
                OrderBookData obe = strings_to_order(tokenise(line, ','));
                data.push_back(obe);
            }
            catch (const exception& e) {
                cout << "bad data" << endl;
            }
        }


    }

    cout << "readCSV:  " << data.size() << endl;

	return data;
}


vector<string> CsvReader::tokenise(string csvLine, char separator) {


	vector<string> entries;

    signed int start = csvLine.find_first_not_of(separator, 0);
    signed int end;
    string token;

    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
        break;
        if (end >= 0) {
            token = csvLine.substr(start, end - start);
        }
        else {
            token = csvLine.substr(start, csvLine.length() - start);
        }
        entries.push_back(token);
        start = end + 1;
    } while (end > 0);

   


	return entries;
}

OrderBookData CsvReader::strings_to_order(vector<string> tokens) {

    double price, amount;
    string timestamp, product, type;


    if (tokens.size() < 5)
        throw exception{};

   try {
       timestamp = tokens[0];
       product = tokens[1];
       type = tokens[2];
       price = stod(tokens[3]);
       amount = stod(tokens[4]);
            
        }
        catch (const exception& e) {
            throw;
        }

	OrderBookData obe{price,amount,timestamp,product,OrderBookData::string_to_ob_type(type)};

	return obe;

}

OrderBookData CsvReader::strings_to_order(std::string _product,
    std::string _price,
    std::string _amount,
    std::string _timestamp,
    orderType _type) {

    double price, amount;
    string timestamp, product, type;


    try {
        price = std::stod(_price);
        amount = std::stod(_amount);
        
    }
    catch (const exception& e) {
        throw;
    }

    OrderBookData obe{ price,amount,_timestamp,_product,_type };

    return obe;



}