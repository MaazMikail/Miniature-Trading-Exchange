#include "OrderBookEntry.h"



    OrderBookData::OrderBookData(double _price,
        double _amount,
        string _timestamp,
        string _product,
        orderType _bid_or_ask,
        string _username )
    : price(_price),
        amount(_amount),
        timestamp(_timestamp),
        product(_product),
        bid_or_ask(_bid_or_ask),
        username(_username) {}


    orderType OrderBookData::string_to_ob_type(string ordertype) {

        if (ordertype == "ask") return orderType::ask;
        else if (ordertype == "bid") return orderType::bid;
        else return orderType::unknown;

    }

   

