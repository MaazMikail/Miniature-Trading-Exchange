# Miniature Trading Exchange

A toy CLI simulation of how a trading exchange works.

## The main components/classes: 

- [OrderBookEntry]
  The OrderBookEntry represents a row in the order book data set (i.e. a single order in the order book). It can be a bid or an ask order.

- [OrderBook]
  The OrderBook class presents a high level interface on all the orders in the order book data set, including query functions to find out which products are in the data set, and to retrieve a subset of the orders using filters. This class also contains the 'Order Matching Engine'

- [Order Matching Engine]
  When a trader submits a buy order (indicating the price they are willing to pay) or a sell order (indicating the price at which they are willing to sell), the order matching engine compares these orders based on their prices and executes trades when compatible orders are found.

- [CrypExchange]
  The CrypExchange class represents the application itself, and it deals with user input and menu printing.

- [Wallet]
  Allows the user to insert & check if the wallet contains a currency in order to fullfil a transaction.

- [CsvReader]
  The CsvReader class allows us to read data from a CSV into an OrderBookEntry object. 


## Features

- Get High & low Ask/Bid prices.
- Insert Currencies into your wallet.
- Make a Bid or Ask.
- Complete a Buy/Sell order and have it reflect on your wallet. 

## Getting Started

The easiest way to run this simulation open it up inside a Visual Studio Project or run it from the command line using this command: 

`g++ --std=c++11 *.cpp` 

