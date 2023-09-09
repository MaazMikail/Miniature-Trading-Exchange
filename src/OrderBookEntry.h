#pragma once
#include <iostream>
using namespace std;


enum class orderType { bid, ask, unknown, asksale, bidsale};


class OrderBookData {

public:
    double price;
    double amount;
    string timestamp;
    string product;
    orderType bid_or_ask;
    string username ="dataset";

    OrderBookData(double _price,
        double _amount,
        string _timestamp,
        string _product,
        orderType _bid_or_ask,
        string username = "dataset");

    static orderType string_to_ob_type(string ordertype);
    static bool comparebyTime(OrderBookData e1, OrderBookData e2) {


        return e1.timestamp < e2.timestamp;
    }

    static bool comparebyPriceAsc(OrderBookData e1, OrderBookData e2) {


        return e1.price < e2.price;
    }


    static bool comparebyPriceDesc(OrderBookData e1, OrderBookData e2) {


        return e1.price > e2.price;
    }

};