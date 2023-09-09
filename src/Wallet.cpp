#include "Wallet.h"
#include <iostream>
#include "CSVReader.h"

Wallet::Wallet()
{


}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) 
    {
        balance = 0;
    }
    else { 
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0)
    {
        
        return false;
    }
    else { 
        if (containsCurrency(type, amount))
        {
            
            currencies[type] -= amount;
            return true;
        }
        else 
            return false;
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0) 
        return false;
    else
        return currencies[type] >= amount;

}

std::string Wallet::toString()
{
    std::string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFullFillOrder(OrderBookData order)
{
    std::vector<std::string> currs = CsvReader::tokenise(order.product, '/');
    
    if (order.bid_or_ask == orderType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;

        return containsCurrency(currency, amount);
    }
   
    if (order.bid_or_ask == orderType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }


    return false;
}


void Wallet::processSale(OrderBookData& sale)
{
    std::vector<std::string> currs = CsvReader::tokenise(sale.product, '/');
   
    if (sale.bid_or_ask == orderType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;

    }
   
    if (sale.bid_or_ask == orderType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}
std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
    os << wallet.toString();
    return os;
}

