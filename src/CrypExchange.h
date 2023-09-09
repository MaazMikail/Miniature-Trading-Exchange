#pragma once
#include <map>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"


class CrypExchange {


public: 

	CrypExchange();
    void init();


private:
    vector<OrderBookData> orders;
    int GetNumber();
    void printMenu();
    int getUserInput();
    void PrintHelp();
    void ExchangeInfo();
    void MakeAsk();
    void MakeBid();
    void ViewWallet();
    void GotoNextTimeFrame();
    void processUserOption();

    std::string currentTime;

    OrderBook orderBook{ "20200317.csv" };


    Wallet wallet{};

};