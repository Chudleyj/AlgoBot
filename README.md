# AlgoBot
A C++ stock market algorithmic trading bot


This is a rework of https://github.com/Chudleyj/Binance-Trading-Bot/

This takes advantage of https://github.com/Chudleyj/IEX_CPP_API

Calculates Technical indicators from stock market, will eventually make automatic buy/sell/hold decisions.

You will need:

Libcurl: https://curl.haxx.se/docs/install.html

Jsoncpp: https://github.com/open-source-parsers/jsoncpp

To run this on your machine.

You'll also need to at least have some C++ knowledge to edit the code for your needs.

To compile and run:

Put all the files from this repo into one folder, and have the above mentioned dependencies installed.

Next, run this in your terminal:

g++ *.cpp -std=c++11 -ljsoncpp -lcurl -o exa.out && ./exa.out
