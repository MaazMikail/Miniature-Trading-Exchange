
#include "OrderBook.h"
#include <map>
#include <iostream>
#include <algorithm>
#include "OrderBookEntry.h"


OrderBook::OrderBook(std::string filename) {

	orders = CsvReader::readCSV(filename);

}

std::vector<std::string> OrderBook::getKnownProducts() {


	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;

	for (const OrderBookData& e : orders) {

		prodMap[e.product] = true;

	}

	for (auto const& o : prodMap) {

		products.push_back(o.first);
	}

	return products;


}

std::vector<OrderBookData> OrderBook::getOrders(orderType type, std::string product, std::string timestamp) {

	std::vector<OrderBookData> all_orders;


	for (OrderBookData& e : orders) {

		if (e.bid_or_ask == type &&
			e.product == product &&
			e.timestamp == timestamp)

		{
			all_orders.push_back(e);
			
		}
		
	}

	return all_orders;
}

double OrderBook::getHighprice(std::vector<OrderBookData> orders) {

	double max_order = 0;

	for (OrderBookData& e : orders) {

		if (e.price > max_order) max_order = e.price;
	}

	return max_order;

}

double OrderBook::getLowprice(std::vector<OrderBookData> orders) {

	double min_order = orders[0].price;

	for (OrderBookData& e : orders) {

		if (e.price < min_order) min_order = e.price;
	}

	return min_order;

}

std::string OrderBook::getEarliestTime() {

	return orders[0].timestamp;


}

std::string OrderBook::getNextTime(std::string currentTime)
{

	std::string next_timestamp = "";

	for (OrderBookData& e : orders) {

		if (e.timestamp > next_timestamp) {

			next_timestamp = e.timestamp;
		}

	}

	if (next_timestamp == "") {

		next_timestamp = orders[0].timestamp;
	}

	return next_timestamp;

}



std::vector<std::string> OrderBook::getKnowntimestamps() {


	std::vector<std::string> timestamps;
	std::map<std::string, bool> timeMap;

	for (const OrderBookData& e : orders) {

		timeMap[e.timestamp] = true;

	}

	for (auto const& o : timeMap) {

		timestamps.push_back(o.first);
	}

	return timestamps;


}

void OrderBook::insertOrder(OrderBookData order) {

	orders.push_back(order);

	std::sort(orders.begin(), orders.end(), OrderBookData::comparebyTime);

}



std::vector<OrderBookData>  OrderBook::match(std::string product, std::string timestamp) {

	// asks
	
	vector<OrderBookData> asks = OrderBook::getOrders(orderType::ask, product, timestamp);

	// bids

	vector<OrderBookData> bids = OrderBook::getOrders(orderType::bid, product, timestamp);


	// sales 

	vector<OrderBookData> sales;

	std::sort(asks.begin(), asks.end(), OrderBookData::comparebyPriceAsc);
	std::sort(bids.begin(), bids.end(), OrderBookData::comparebyPriceDesc);

    for (OrderBookData& ask : asks)
    {
        //     for bid in bids:
        for (OrderBookData& bid : bids)
        {
            //         if bid.price >= ask.price # we have a match
            if (bid.price >= ask.price)
            {
                //             sale = new order()
                //             sale.price = ask.price
                OrderBookData sale{ ask.price, 0, timestamp,
                    product,
                    orderType::asksale };

                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.bid_or_ask = orderType::bidsale;
                }
                if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.bid_or_ask = orderType::asksale;
                }

                //             # now work out how much was sold and 
                //             # create new bids and asks covering 
                //             # anything that was not sold
                //             if bid.amount == ask.amount: # bid completely clears ask
                if (bid.amount == ask.amount)
                {
                    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
                    //                 # can do no more with this ask
                    //                 # go onto the next ask
                    //                 break
                    break;
                }
                //           if bid.amount > ask.amount:  # ask is completely gone slice the bid
                if (bid.amount > ask.amount)
                {
                    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # we adjust the bid in place
                    //                 # so it can be used to process the next ask
                    //                 bid.amount = bid.amount - ask.amount
                    bid.amount = bid.amount - ask.amount;
                    //                 # ask is completely gone, so go to next ask                
                    //                 break
                    break;
                }


                //             if bid.amount < ask.amount # bid is completely gone, slice the ask
                if (bid.amount < ask.amount &&
                    bid.amount > 0)
                {
                    //                 sale.amount = bid.amount
                    sale.amount = bid.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # update the ask
                    //                 # and allow further bids to process the remaining amount
                    //                 ask.amount = ask.amount - bid.amount
                    ask.amount = ask.amount - bid.amount;
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
                    //                 # some ask remains so go to the next bid
                    //                 continue
                    continue;
                }
            }
        }
    }
    return sales;

}

