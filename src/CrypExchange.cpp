#include "CrypExchange.h"
#include <iostream>
#include "OrderBookEntry.h"
#include "CsvReader.h"

using namespace std;


CrypExchange::CrypExchange() {
    

}

void CrypExchange::init() {


    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10.0);

    while (true) {

        printMenu();
        processUserOption();

    }


}


int CrypExchange::GetNumber()
{
    int n;
    cin >> n;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Not a valid number. Please reenter: ";
        cin >> n;
    }
    return n;
}


void CrypExchange::printMenu() {

    cout << "====== Crypto Trade ======" << endl;
    cout << "1. Print Help." << endl;
    cout << "2. Print Exchange Statistics." << endl;
    cout << "3. Make an Offer." << endl;
    cout << "4. Make a Bid.." << endl;
    cout << "5. View Wallet." << endl;
    cout << "6. Continue." << endl;
    cout << "==================" << endl;

    cout << "Current Time is: " << currentTime << endl;
}


int CrypExchange::getUserInput() {

    int i;

    cout << "Select an Option from 1 to 6" << endl;
    i = GetNumber();
    return i;
}


void CrypExchange::PrintHelp()
{

    cout << "Help: This application allows you to trade Cryptocurrencies." << endl;
}

void CrypExchange::ExchangeInfo()
{   
    cout << "Products: " << endl;
    for (const std::string prod : orderBook.getKnownProducts()) {

        cout << prod << endl;
        std::vector<OrderBookData> entries = orderBook.getOrders(orderType::ask, prod, currentTime);
        cout << entries.size() << endl;

        if (entries.size() == 0) continue;

        std::cout << "Max Ask: " << orderBook.getHighprice(entries) << std::endl;
        std::cout << "Min Ask: " << orderBook.getLowprice(entries) << std::endl;
        

    }
 }

void CrypExchange::MakeAsk()
{

    cout << "Nake an Offer Product, Price, Amount. E.g., ETH/BTC, 100, 0.5" << endl;
    std::string input;

    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(cin, input);
    std::cout << "You typed: " <<  input << endl;

    std::vector<std::string> tokens = CsvReader::tokenise(input, ',');

    if (tokens.size() != 3) {

        std::cout << "Bad Input " << input << std::endl;
    }
    else {
        try {
            OrderBookData obe = CsvReader::strings_to_order(tokens[0], tokens[1], tokens[2], currentTime, orderType::ask);
            obe.username = "simuser";
            if (wallet.canFullFillOrder(obe)) {
                orderBook.insertOrder(obe);
                cout << "Wallet Looks Good" << endl;

            }
            else {
                cout << "Insufficient Funds" << endl;
            }
        }
        catch (const std::exception& e) {

            std::cout << "Bad input: Please enter Valid input, " << input << endl;
        }
    }
  
}

void CrypExchange::MakeBid()
{

    cout << "Nake a Bid, Product, Price, Amount. E.g., ETH/BTC, 100, 0.5" << endl;
    std::string input;


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(cin, input);
    std::cout << "You typed: " << input << endl;

    std::vector<std::string> tokens = CsvReader::tokenise(input, ',');

    if (tokens.size() != 3) {

        std::cout << "Bad Input " << input << std::endl;
    }
    else {
        try {
            OrderBookData obe = CsvReader::strings_to_order(tokens[0], tokens[1], tokens[2], currentTime, orderType::bid);
            obe.username = "simuser";
            if (wallet.canFullFillOrder(obe)) {
                orderBook.insertOrder(obe);
                cout << "Wallet Looks Good" << endl;

            }
            else {
                cout << "Insufficient Funds" << endl;
            }
        }
        catch (const std::exception& e) {

            std::cout << "Bad input: Please enter Valid input, " << input << endl;
        }
    }
}

void CrypExchange::ViewWallet()
{

    cout << "view Wallet." << endl;
    std::cout << wallet.toString() << endl; 
}

void CrypExchange::GotoNextTimeFrame()
{

    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookData> sales = orderBook.match(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookData& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }

    }

    currentTime = orderBook.getNextTime(currentTime);

}

/*
void CrypExchange::AssignToMenu()
{

    CrypExchange::menu[1] = PrintHelp;
    CrypExchange::menu[2] = ExchangeInfo;
    CrypExchange::menu[3] = MakeOffer;
    CrypExchange::menu[4] = MakeBid;
    CrypExchange::menu[5] = ViewWallet;
    CrypExchange::menu[6] = GotoNextTimeFrame;
}
*/
void CrypExchange::processUserOption()
{
    int user_input;
    user_input = getUserInput();

    switch (user_input)
    {
    case 1:
        PrintHelp();
        cout << "==================" << endl;
        break;
    case 2:
        ExchangeInfo();
        cout << "==================" << endl;
        break;
    case 3:
        MakeAsk();
        cout << "==================" << endl;
        break;
    case 4:
        MakeBid();
        cout << "==================" << endl;
        break;
    case 5:
        ViewWallet();
        cout << "==================" << endl;
        break;
    case 6:
        GotoNextTimeFrame();
        cout << "==================" << endl;
        break;
    default:
        cout << "Please enter something between 1-6." << endl;
        cout << "==================" << endl;
        break;

    }
}