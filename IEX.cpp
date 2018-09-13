/* UNOFFICIAL IEX TRADING API for C++
   BY: Justin Chudley
   https://github.com/Chudleyj/
   OFFICIAL API: https://iextrading.com/developer/docs/
   Refer to the official docs to understand the return of each function.
   GET examples and JSON examples commented above each function are from the offical API.
   ALL credit for those examples belongs to IEX.
   “Data provided for free by IEX (https://iextrading.com/developer/).
   View IEX’s Terms of Use (https://iextrading.com/api-exhibit-a/).”
 */
//TODO CHECK ALL SYMBOLS FOR VALID SYMBOL
#include "IEX.h"

//Callback function used by sendGetRequest to get the result from curl.
std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out)
{
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
}

//Use LIBCURL to send the GET requests
void IEX::sendGetRequest(Json::Value &jsonData, const std::string url)
{
        CURL* curl = curl_easy_init();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        long int httpCode(0); //Having this as a normal int will cause a segmentation fault for some requests being too large.
        std::unique_ptr<std::string> httpData(new std::string());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        Json::Reader jsonReader;
        jsonReader.parse(*httpData, jsonData); //TODO error handle
}
/*
   // .../market
   {
   "AAPL" : {
    "quote": {...},
    "news": [...],
    "chart": [...]
   },
   "FB" : {
    "quote": {...},
    "news": [...],
    "chart": [...]
   },
   }
 */
Json::Value IEX::stocks::batch(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url+="/stock/"+symbol+"/batch";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/* GET /stock/{symbol}/book
   {
   "quote": {...},
   "bids": [...],
   "asks": [...],
   "trades": [...],
   "systemEvent": {...},
   }
 */
Json::Value IEX::stocks::book(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url+="/stock/"+symbol+"/book";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/chart/{range}
   // .../1d
   [
    {
        "date": "20171215"
        "minute": "09:30",
        "label": "09:30 AM",
        "high": 143.98,
        "low": 143.775,
        "average": 143.889,
        "volume": 3070,
        "notional": 441740.275,
        "numberOfTrades": 20,
        "marktHigh": 143.98,
        "marketLow": 143.775,
        "marketAverage": 143.889,
        "marketVolume": 3070,
        "marketNotional": 441740.275,
        "marketNumberOfTrades": 20,
        "open": 143.98,
        "close": 143.775,
        "marktOpen": 143.98,
        "marketClose": 143.775,
        "changeOverTime": -0.0039,
        "marketChangeOverTime": -0.004
    } // , { ... }
   ]
 */
Json::Value IEX::stocks::chart(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url+="/stock/"+symbol+"/chart";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

//Same as chart function, except it takes a range in.
//Range must be: 5y, 2y, 1y, ytd, 6m, 3m, 1m, 1d
Json::Value IEX::stocks::chartRange(const std::string &symbol, const std::string &range)
{
        Json::Value jsonData;
        if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m" || range == "1d") {
                std::string url(IEX_ENDPOINT);
                url+="/stock/"+symbol+"/chart/"+range;
                IEX::sendGetRequest(jsonData, url);
        }
        else{
                std::cout << std::endl << "Incorrect 'range' input in function chartRange. Exiting." << std::endl;
                exit(1);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

//Specific date entry for chart, YYYYMMDD format, 30 trailing calander days
Json::Value IEX::stocks::chartDate(const std::string &symbol, const std::string &date)
{
        Json::Value jsonData;
        if(date.size() == 8) {
                std::string url(IEX_ENDPOINT);
                url+="/stock/"+symbol+"/chart/date/"+date;
                IEX::sendGetRequest(jsonData, url);

        }
        else{
                std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                exit(1);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

//Dynamic chart. See offical API docs.
Json::Value IEX::stocks::chartDynamic(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/chart/dynamic";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/company
   {
   "symbol": "AAPL",
   "companyName": "Apple Inc.",
   "exchange": "Nasdaq Global Select",
   "industry": "Computer Hardware",
   "website": "http://www.apple.com",
   "description": "Apple Inc is an American multinational technology company. It designs, manufactures, and markets mobile communication and media devices, personal computers, and portable digital music players.",
   "CEO": "Timothy D. Cook",
   "issueType": "cs",
   "sector": "Technology",
   }*/
Json::Value IEX::stocks::company(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/company";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/delayed-quote
   {
   "symbol": "AAPL",
   "delayedPrice": 143.08,
   "delayedSize": 200,
   "delayedPriceTime": 1498762739791,
   "processedTime": 1498763640156
   }*/
Json::Value IEX::stocks::delayedQuote(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/delayed-quote";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/dividends/{range}
   [
    {
        "exDate": "2017-08-10",
        "paymentDate": "2017-08-17",
        "recordDate": "2017-08-14",
        "declaredDate": "2017-08-01",
        "amount": 0.63,
        "type": "Dividend income",
        "qualified": "Q"
    } // , { ... }
   ]
   REQUIRES a range: 5y,2y,1y,ytd,6m,3m,1m */
Json::Value IEX::stocks::dividends(const std::string &symbol, const std::string &range)
{
        Json::Value jsonData;
        if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m") {
                std::string url(IEX_ENDPOINT);
                url+="/stock/"+symbol+"/dividends/"+range;
                IEX::sendGetRequest(jsonData, url);
        }
        else{
                std::cout << std::endl << "Incorrect 'range' input in function dividends. Exiting." << std::endl;
                exit(1);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/earnings
   {
   "symbol": "AAPL",
   "earnings": [
    {
      "actualEPS": 2.1,
      "consensusEPS": 2.02,
      "estimatedEPS": 2.02,
      "announceTime": "AMC",
      "numberOfEstimates": 14,
      "EPSSurpriseDollar": 0.08,
      "EPSReportDate": "2017-05-02",
      "fiscalPeriod": "Q2 2017",
      "fiscalEndDate": "2017-03-31",
      "yearAgo": 1.67,
      "yearAgoChangePercent": .30,
      "estimatedChangePercent": .28,
      "symbolId": 11
    },
    {
      "actualEPS": 3.36,
      "consensusEPS": 3.22,
      "estimatedEPS": 3.22,
      "announceTime": "AMC",
      "numberOfEstimates": 15,
      "EPSSurpriseDollar": 0.14,
      "EPSReportDate": "2017-01-31",
      "fiscalPeriod": "Q1 2017",
      "fiscalEndDate": "2016-12-31",
      "yearAgo": 1.67,
      "yearAgoChangePercent": .30,
      "estimatedChangePercent": .28,
      "symbolId": 11
    },
   ]
   }*/
Json::Value IEX::stocks::earnings(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/earnings";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/effective-spread
   [
   {
    "volume": 4899,
    "venue": "XCHI",
    "venueName": "CHX",
    "effectiveSpread": 0.02253725,
    "effectiveQuoted": 0.9539362,
    "priceImprovement": 0.0008471116999999999
   },
   {
    "volume": 9806133,
    "venue": "XBOS",
    "venueName": "NASDAQ BX",
    "effectiveSpread": 0.0127343,
    "effectiveQuoted": 0.9313967,
    "priceImprovement": 0.0007373158
   },
   {
    "volume": 6102991,
    "venue": "IEXG",
    "venueName": "IEX",
    "effectiveSpread": 0.005881705,
    "effectiveQuoted": 0.4532043,
    "priceImprovement": 0.003949427
   }
   ]*/
Json::Value IEX::stocks::effectiveSpread(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/effective-spread";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/financials
   The above example will return JSON with the following keys
   {
   "symbol": "AAPL",
   "financials": [
    {
      "reportDate": "2017-03-31",
      "grossProfit": 20591000000,
      "costOfRevenue": 32305000000,
      "operatingRevenue": 52896000000,
      "totalRevenue": 52896000000,
      "operatingIncome": 14097000000,
      "netIncome": 11029000000,
      "researchAndDevelopment": 2776000000,
      "operatingExpense": 6494000000,
      "currentAssets": 101990000000,
      "totalAssets": 334532000000,
      "totalLiabilities": 200450000000,
      "currentCash": 15157000000,
      "currentDebt": 13991000000,
      "totalCash": 67101000000,
      "totalDebt": 98522000000,
      "shareholderEquity": 134082000000,
      "cashChange": -1214000000,
      "cashFlow": 12523000000,
      "operatingGainsLosses": null
    } // , { ... }
   ]
   }*/
Json::Value IEX::stocks::financials(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/financials";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/stats
   {
   "companyName": "Apple Inc.",
   "marketcap": 760334287200,
   "beta": 1.295227,
   "week52high": 156.65,
   "week52low": 93.63,
   "week52change": 58.801903,
   "shortInterest": 55544287,
   "shortDate": "2017-06-15",
   "dividendRate": 2.52,
   "dividendYield": 1.7280395,
   "exDividendDate": "2017-05-11 00:00:00.0",
   "latestEPS": 8.29,
   "latestEPSDate": "2016-09-30",
   "sharesOutstanding": 5213840000,
   "float": 5203997571,
   "returnOnEquity": 0.08772939519857577,
   "consensusEPS": 3.22,
   "numberOfEstimates": 15,
   "symbol": "AAPL",
   "EBITDA": 73828000000,
   "revenue": 220457000000,
   "grossProfit": 84686000000,
   "cash": 256464000000,
   "debt": 358038000000,
   "ttmEPS": 8.55,
   "revenuePerShare": 42.2830389885382,
   "revenuePerEmployee": 1900491.3793103448,
   "peRatioHigh": 25.5,
   "peRatioLow": 8.7,
   "EPSSurpriseDollar": null,
   "EPSSurprisePercent": 3.9604,
   "returnOnAssets": 14.15,
   "returnOnCapital": null,
   "profitMargin": 20.73,
   "priceToSales": 3.6668503,
   "priceToBook": 6.19,
   "day200MovingAvg": 140.60541,
   "day50MovingAvg": 156.49678,
   "institutionPercent": 32.1,
   "insiderPercent": null,
   "shortRatio": 1.6915414,
   "year5ChangePercent": 0.5902546932200027,
   "year2ChangePercent": 0.3777449874142869,
   "year1ChangePercent": 0.39751716851558366,
   "ytdChangePercent": 0.36659492036160124,
   "month6ChangePercent": 0.12208398133748043,
   "month3ChangePercent": 0.08466584665846649,
   "month1ChangePercent": 0.009668596145283263,
   "day5ChangePercent": -0.005762605699968781
   }*/
Json::Value IEX::stocks::stats(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/stats";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/largest-trades
   [
   {
    "price": 186.39,
    "size": 10000,
    "time": 1527090690175,
    "timeLabel": "11:51:30",
    "venue": "EDGX",
    "venueName": "Cboe EDGX"
   },
   ...
   ] */
Json::Value IEX::stocks::largestTrades(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/largest-trades";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/market/list
   [
   {
      "symbol": "AAPL",
      "companyName": "Apple Inc.",
      "primaryExchange": "Nasdaq Global Select",
      "sector": "Technology",
      "calculationPrice": "tops",
      "latestPrice": 158.73,
      "latestSource": "Previous close",
      "latestTime": "September 19, 2017",
      "latestUpdate": 1505779200000,
      "latestVolume": 20567140,
      "iexRealtimePrice": 158.71,
      "iexRealtimeSize": 100,
      "iexLastUpdated": 1505851198059,
      "delayedPrice": 158.71,
      "delayedPriceTime": 1505854782437,
      "previousClose": 158.73,
      "change": -1.67,
      "changePercent": -0.01158,
      "iexMarketPercent": 0.00948,
      "iexVolume": 82451,
      "avgTotalVolume": 29623234,
      "iexBidPrice": 153.01,
      "iexBidSize": 100,
      "iexAskPrice": 158.66,
      "iexAskSize": 100,
      "marketCap": 751627174400,
      "peRatio": 16.86,
      "week52High": 159.65,
      "week52Low": 93.63,
      "ytdChange": 0.3665,
   } // , { ... }
   ]
   LISTTYPE REQUIRED: mostactive, gainers, losers, iexvolume, or iexmarketpercent*/
Json::Value IEX::stocks::list(const std::string &listType)
{
        Json::Value jsonData;
        if(listType == "mostactive" || listType == "gainers" || listType == "losers" || listType == "iexvolume" || listType == "iexmarketpercent") {
                std::string url(IEX_ENDPOINT);
                url+="/stock/market/list/"+listType;
                IEX::sendGetRequest(jsonData, url);
        }
        else{
                std::cout << std::endl << "Incorrect 'listType' input in function list. Exiting." << std::endl;
                exit(1);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/logo
   {
   "url": "https://storage.googleapis.com/iex/api/logos/AAPL.png"
   }*/
Json::Value IEX::stocks::logo(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/logo";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/news/last/{last}
   [
   {
   "datetime": "2017-06-29T13:14:22-04:00",
   "headline": "Voice Search Technology Creates A New Paradigm For Marketers",
   "source": "Benzinga via QuoteMedia",
   "url": "https://api.iextrading.com/1.0/stock/aapl/article/8348646549980454",
   "summary": "<p>Voice search is likely to grow by leap and bounds, with technological advancements leading to better adoption and fueling the growth cycle, according to Lindsay Boyajian, <a href=\"http://loupventures.com/how-the-future-of-voice-search-affects-marketers-today/\">a guest contributor at Loup Ventu...",
   "related": "AAPL,AMZN,GOOG,GOOGL,MSFT",
   "image": "https://api.iextrading.com/1.0/stock/aapl/news-image/7594023985414148"
   }
   ]
   EITHER PASS A SYMBOL OR A SYMOL AND A NUMBER FOR LAST X ARTICLES (SEE OFFICAL DOCS)
   OR PASS MARKET AS SYMBOL FOR MARKETWIDE NEWS*/
Json::Value IEX::stocks::news(const std::string &symbol, int last)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        last == 0 ? url += "/stock/"+symbol+"/news" : url += "/stock/"+symbol+"/news/last/"+std::to_string(last);
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*GET /stock/{symbol}/ohlc
   {
   "open": {
    "price": 154,
    "time": 1506605400394
   },
   "close": {
    "price": 153.28,
    "time": 1506605400394
   },
   "high": 154.80,
   "low": 153.25
   }
   Can take in a specific symbol OR market as symbol */
Json::Value IEX::stocks::OHLC(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/ohlc";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/peers
   [
    "MSFT",
    "NOK",
    "IBM",
    "BBRY",
    "HPQ",
    "GOOGL",
    "XLK"
   ] */
Json::Value IEX::stocks::peers(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/peers";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/previous
   {
   "symbol": "AAPL",
   "date": "2017-09-19",
   "open": 159.51,
   "high": 159.77,
   "low": 158.44,
   "close": 158.73,
   "volume": 20810632,
   "unadjustedVolume": 20810632,
   "change": 0.06,
   "changePercent": 0.038,
   "vwap": 158.9944
   }
   Takes symbol or market as symbol */
Json::Value IEX::stocks::previous(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/previous";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

// GET /stock/{symbol}/price
Json::Value IEX::stocks::price(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/price";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/quote
   {
   "symbol": "AAPL",
   "companyName": "Apple Inc.",
   "primaryExchange": "Nasdaq Global Select",
   "sector": "Technology",
   "calculationPrice": "tops",
   "open": 154,
   "openTime": 1506605400394,
   "close": 153.28,
   "closeTime": 1506605400394,
   "high": 154.80,
   "low": 153.25,
   "latestPrice": 158.73,
   "latestSource": "Previous close",
   "latestTime": "September 19, 2017",
   "latestUpdate": 1505779200000,
   "latestVolume": 20567140,
   "iexRealtimePrice": 158.71,
   "iexRealtimeSize": 100,
   "iexLastUpdated": 1505851198059,
   "delayedPrice": 158.71,
   "delayedPriceTime": 1505854782437,
   "extendedPrice": 159.21,
   "extendedChange": -1.68,
   "extendedChangePercent": -0.0125,
   "extendedPriceTime": 1527082200361,
   "previousClose": 158.73,
   "change": -1.67,
   "changePercent": -0.01158,
   "iexMarketPercent": 0.00948,
   "iexVolume": 82451,
   "avgTotalVolume": 29623234,
   "iexBidPrice": 153.01,
   "iexBidSize": 100,
   "iexAskPrice": 158.66,
   "iexAskSize": 100,
   "marketCap": 751627174400,
   "peRatio": 16.86,
   "week52High": 159.65,
   "week52Low": 93.63,
   "ytdChange": 0.3665,
   }
   OPTIONAL VALUE TO DISPLAY PERCENT, SEE OFFICAL API */
Json::Value IEX::stocks::quote(const std::string &symbol, bool displayPercent)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        displayPercent ? url += "/stock/"+symbol+"/quote?displayPercent=true" : url += "/stock/"+symbol+"/quote";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/relevant
   {
   "peers": true,
   "symbols": [
      "MSFT",
      "NOK",
      "IBM",
      "BBRY",
      "HPQ",
      "GOOGL",
      "XLK"
   ]
   }*/
Json::Value IEX::stocks::relevant(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/relevant";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/market/sector-performance
   [
   {
    "type": "sector",
    "name": "Industrials",
    "performance": 0.00711,
    "lastUpdated": 1533672000437
   },
   ...
   ]*/
Json::Value IEX::stocks::sectorPerformance()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/market/sector-performance";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/splits/{range}
   [
    {
        "exDate": "2017-08-10",
        "declaredDate": "2017-08-01",
        "recordDate": "2017-08-14",
        "paymentDate": "2017-08-17",
        "ratio": 0.142857,
        "toFactor": 7,
        "forFactor": 1
    } // , { ... }
   ]*/
Json::Value IEX::stocks::splits(const std::string &symbol, const std::string &range)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);

        if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m" || range == "1d") {
                url += "/stock/"+symbol+"/splits/"+range;
                IEX::sendGetRequest(jsonData, url);
        }
        else{
                std::cout << std::endl << "Incorrect 'range' input in function chartRange. Exiting." << std::endl;
                exit(1);
        }

        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

//GET /stock/{symbol}/time-series
Json::Value IEX::stocks::timeSeries(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/time-series";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/{symbol}/delayed-quote
   [
   {
    "volume": 0,
    "venue": "XNYS",
    "venueName": "NYSE",
    "marketPercent": 0,
    "avgMarketPercent": 0,
    "date": "N/A"
   },
   {
    "volume": 21655,
    "venue": "XASE",
    "venueName": "NYSE American",
    "date": "2017-09-19",
    "marketPercent": 0.0010540470343969304,
    "avgMarketPercent": 0.0021596513337820305
   },
   {
    "volume": 164676,
    "venue": "EDGA",
    "venueName": "EDGA",
    "date": "2017-09-19",
    "marketPercent": 0.008015527565751508,
    "avgMarketPercent": 0.007070162857518009
   },
   {
    "volume": 253600,
    "venue": "XCHI",
    "venueName": "CHX",
    "date": "2017-09-19",
    "marketPercent": 0.01234386182974193,
    "avgMarketPercent": 0.019123040706393757
   },
   {
    "volume": 289791,
    "venue": "IEXG",
    "venueName": "IEX",
    "date": "2017-09-19",
    "marketPercent": 0.014105441890783691,
    "avgMarketPercent": 0.01080806673166022
   },
   {
    "volume": 311580,
    "venue": "XPHL",
    "venueName": "NASDAQ PSX",
    "date": "2017-09-19",
    "marketPercent": 0.0151660113127405,
    "avgMarketPercent": 0.010991446666811688
   },
   {
    "volume": 479457,
    "venue": "XBOS",
    "venueName": "NASDAQ BX",
    "date": "2017-09-19",
    "marketPercent": 0.02333734606191868,
    "avgMarketPercent": 0.016846380315025656
   },
   {
    "volume": 501842,
    "venue": "BATY",
    "venueName": "BATS BYX",
    "date": "2017-09-19",
    "marketPercent": 0.024426925506156744,
    "avgMarketPercent": 0.020187355701732888
   },
   {
    "volume": 1242757,
    "venue": "BATS",
    "venueName": "BATS BZX",
    "date": "2017-09-19",
    "marketPercent": 0.06049061788621685,
    "avgMarketPercent": 0.060993172098918684
   },
   {
    "volume": 1865376,
    "venue": "ARCX",
    "venueName": "NYSE Arca",
    "date": "2017-09-19",
    "marketPercent": 0.09079630758878819,
    "avgMarketPercent": 0.07692002795005641
   },
   {
    "volume": 1951116,
    "venue": "EDGX",
    "venueName": "EDGX",
    "date": "2017-09-19",
    "marketPercent": 0.09496966213643043,
    "avgMarketPercent": 0.09297590135910822
   },
   {
    "volume": 5882545,
    "venue": "XNGS",
    "venueName": "NASDAQ",
    "date": "2017-09-19",
    "marketPercent": 0.2863301367793346,
    "avgMarketPercent": 0.27436519408402665
   },
   {
    "volume": 7580229,
    "venue": "TRF",
    "venueName": "Off Exchange",
    "date": "2017-09-19",
    "marketPercent": 0.36896411440773996,
    "avgMarketPercent": 0.40847022134435956
   }
   ]*/
Json::Value IEX::stocks::VolumeByVenue(const std::string &symbol)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/"+symbol+"/volume-by-venue";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /ref-data/daily-list/symbol-directory
   [
   {
    "RecordID": " CA20171108153808144",
    "DailyListTimestamp": "2017-11-08T17:00:00",
    "EffectiveDate": "2017-11-10",
    "IssueEvent": "AA",
    "CurrentSymbolinINETSymbology": "ZEXIT-",
    "CurrentSymbolinCQSSymbology": "ZEXITp",
    "CurrentSymbolinCMSSymbology": "ZEXIT PR",
    "NewSymbolinINETSymbology": "",
    "NewSymbolinCQSSymbology": "",
    "NewSymbolinCMSSymbology": "",
    "CurrentSecurityName": "ZEXIT Preffered Stock",
    "NewSecurityName": "",
    "CurrentCompanyName": "ZEXIT Test Company",
    "NewCompanyName": "",
    "CurrentListingCenter": "",
    "NewListingCenter": "V",
    "DelistingReason": "",
    "CurrentRoundLotSize": "100",
    "NewRoundLotSize": "",
    "CurrentLULDTierIndicator": "0",
    "NewLULDTierIndicator": "",
    "ExpirationDate": "0",
    "SeparationDate": "0",
    "SettlementDate": "0",
    "MaturityDate": "0",
    "RedemptionDate": "0",
    "CurrentFinancialStatus": "0",
    "NewFinancialStatus": "",
    "WhenIssuedFlag": "N",
    "WhenDistributedFlag": "N",
    "IPOFlag": "N",
    "NotesforEachEntry": "New preferred ZIEXT security",
    "RecordUpdateTime": "2017-11-08T16:34:43"
   },
   {...}
   ]*/
Json::Value IEX::refData::symbols()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/ref-data/symbols";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /ref-data/daily-list/symbol-directory
   [
   {
    "RecordID": " CA20171108153808144",
    "DailyListTimestamp": "2017-11-08T17:00:00",
    "EffectiveDate": "2017-11-10",
    "IssueEvent": "AA",
    "CurrentSymbolinINETSymbology": "ZEXIT-",
    "CurrentSymbolinCQSSymbology": "ZEXITp",
    "CurrentSymbolinCMSSymbology": "ZEXIT PR",
    "NewSymbolinINETSymbology": "",
    "NewSymbolinCQSSymbology": "",
    "NewSymbolinCMSSymbology": "",
    "CurrentSecurityName": "ZEXIT Preffered Stock",
    "NewSecurityName": "",
    "CurrentCompanyName": "ZEXIT Test Company",
    "NewCompanyName": "",
    "CurrentListingCenter": "",
    "NewListingCenter": "V",
    "DelistingReason": "",
    "CurrentRoundLotSize": "100",
    "NewRoundLotSize": "",
    "CurrentLULDTierIndicator": "0",
    "NewLULDTierIndicator": "",
    "ExpirationDate": "0",
    "SeparationDate": "0",
    "SettlementDate": "0",
    "MaturityDate": "0",
    "RedemptionDate": "0",
    "CurrentFinancialStatus": "0",
    "NewFinancialStatus": "",
    "WhenIssuedFlag": "N",
    "WhenDistributedFlag": "N",
    "IPOFlag": "N",
    "NotesforEachEntry": "New preferred ZIEXT security",
    "RecordUpdateTime": "2017-11-08T16:34:43"
   },
   {...}
   ]*/
Json::Value IEX::refData::corporateActions(std::string date)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);

        if(!date.empty()) {
                if(date.size() == 8) {
                        url += "/ref-data/daily-list/corporate-actions/"+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else{
                        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                        exit(1);
                }
        }

        else{
                url += "/ref-data/daily-list/corporate-actions";
                IEX::sendGetRequest(jsonData, url);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /ref-data/daily-list/dividends
   [
   {
    "RecordID": " DV20171108154436478",
    "DailyListTimestamp": "2017-11-08T17:00:00",
    "EventType": "CHANGE",
    "SymbolinINETSymbology": "ZEXIT",
    "SymbolinCQSSymbology": "ZEXIT",
    "SymbolinCMSSymbology": "ZEXIT",
    "SecurityName": "ZEXIT Common Stock",
    "CompanyName": "ZEXIT Test Company",
    "DeclarationDate": "2017-11-01",
    "AmountDescription": "fnl",
    "PaymentFrequency": "O",
    "ExDate": "2017-11-09",
    "RecordDate": "2017-11-13",
    "PaymentDate": "2017-11-17",
    "DividendTypeID": "XS",
    "StockAdjustmentFactor": "1.1",
    "StockAmount": ".1",
    "CashAmount": "0",
    "PostSplitShares": "0",
    "PreSplitShares": "0",
    "QualifiedDividend": "Y",
    "ExercisePriceAmount": "0",
    "ElectionorExpirationDate": "0",
    "GrossAmount": "0",
    "NetAmount": "0",
    "BasisNotes": "",
    "NotesforEachEntry": "ZEXIT is paying a 10% stock dividend",
    "RecordUpdateTime": "2017-11-08T16:48:47"
   },
   {...}
   ]*/
Json::Value IEX::refData::dividends(std::string date)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        if(!date.empty()) {
                if(date.size() == 8) {
                        url += "/ref-data/daily-list/dividends/"+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else{
                        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                        exit(1);
                }
        }

        else{
                url += "/ref-data/daily-list/dividends";
                IEX::sendGetRequest(jsonData, url);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /ref-data/daily-list/next-day-ex-date
   [
   {
    "RecordID": " DV20171108154436478",
    "DailyListTimestamp": "2017-11-08T17:00:00",
    "ExDate": "2017-11-09",
    "SymbolinINETSymbology": "ZEXIT",
    "SymbolinCQSSymbology": "ZEXIT",
    "SymbolinCMSSymbology": "ZEXIT",
    "SecurityName": "ZEXIT Common Stock",
    "CompanyName": "ZEXIT Test Company",
    "DividendTypeID": "XS",
    "AmountDescription": "fnl",
    "PaymentFrequency": "O",
    "StockAdjustmentFactor": "1.1",
    "StockAmount": ".1",
    "CashAmount": "0",
    "PostSplitShares": "0",
    "PreSplitShares": "0",
    "QualifiedDividend": "Y",
    "ExercisePriceAmount": "0",
    "ElectionorExpirationDate": "0",
    "GrossAmount": "0",
    "NetAmount": "0",
    "BasisNotes": "",
    "NotesforEachEntry": "ZEXIT is paying a 10% stock dividend",
    "RecordUpdateTime": "2017-11-08T16:48:47"
   },
   {...}
   ]*/
Json::Value IEX::refData::nextDayExDate(std::string date)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        if(!date.empty()) {
                if(date.size() == 8) {
                        url += "/ref-data/daily-list/next-day-ex-date/"+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else{
                        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                        exit(1);
                }
        }

        else{
                url += "/ref-data/daily-list/next-day-ex-date";
                IEX::sendGetRequest(jsonData, url);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /ref-data/daily-list/symbol-directory
   [
   {
    "RecordID": "SD20171020161150890",
    "DailyListTimestamp": "2017-12-18T09:00:00",
    "SymbolinINETSymbology": "ZEXIT",
    "SymbolinCQSSymbology": "ZEXIT",
    "SymbolinCMSSymbology": "ZEXIT",
    "SecurityName": "ZEXIT Common Stock",
    "CompanyName": "ZEXIT Test Company",
    "TestIssue": "Y",
    "IssueDescription": "Common Stock",
    "IssueType": "C",
    "IssueSubType": "C",
    "SICCode": "5678",
    "TransferAgent": "American Stock Transfer",
    "FinancialStatus": "0",
    "RoundLotSize": "100",
    "PreviousOfficialClosingPrice": "10.00",
    "AdjustedPreviousOfficialClosingPrice": "10.00",
    "WhenIssuedFlag": "N",
    "WhenDistributedFlag": "N",
    "IPOFlag": "N",
    "FirstDateListed": "2017-09-15",
    "LULDTierIndicator": "1",
    "CountryofIncorporation": "USA",
    "LeveragedETPFlag": "N",
    "LeveragedETPRatio": "0",
    "InverseETPFlag": "N",
    "RecordUpdateTime": "2017-11-10T16:28:56"
   },
   {...}
   ]*/
Json::Value IEX::refData::symbolDirectory(std::string date)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        if(!date.empty()) {
                if(date.size() == 8) {
                        url += "/ref-data/daily-list/symbol-directory/"+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else{
                        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                        exit(1);
                }
        }

        else{
                url += "/ref-data/daily-list/symbol-directory";
                IEX::sendGetRequest(jsonData, url);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stats/intraday
   {
   "volume": {
    "value": 26908038,
    "lastUpdated": 1480433817323
   },
   "symbolsTraded": {
    "value": 4089,
    "lastUpdated": 1480433817323
   },
   "routedVolume": {
    "value": 10879651,
    "lastUpdated": 1480433816891
   },
   "notional": {
    "value": 1090683735,
    "lastUpdated": 1480433817323
   },
   "marketShare": {
    "value": 0.01691,
    "lastUpdated": 1480433817336
   }
   }*/
Json::Value IEX::stats::intraday()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stats/intraday";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stats/recent
   [
   {
    "date": "2017-01-11",
    "volume": 128048723,
    "routedVolume": 38314207,
    "marketShare": 0.01769,
    "isHalfday": false,
    "litVolume": 30520534
   },
   {
    "date": "2017-01-10",
    "volume": 135116521,
    "routedVolume": 39329019,
    "marketShare": 0.01999,
    "isHalfday": false,
    "litVolume": 29721789
   },
   {
    "date": "2017-01-09",
    "volume": 109850518,
    "routedVolume": 31283422,
    "marketShare": 0.01704,
    "isHalfday": false,
    "litVolume": 27699365
   },
   {
    "date": "2017-01-06",
    "volume": 116680433,
    "routedVolume": 29528471,
    "marketShare": 0.01805,
    "isHalfday": false,
    "litVolume": 29357729
   },
   {
    "date": "2017-01-05",
    "volume": 130389657,
    "routedVolume": 40977180,
    "marketShare": 0.01792,
    "isHalfday": false,
    "litVolume": 33169236
   },
   {
    "date": "2017-01-04",
    "volume": 124428433,
    "routedVolume": 38859989,
    "marketShare": 0.01741,
    "isHalfday": false,
    "litVolume": 31563256
   },
   {
    "date": "2017-01-03",
    "volume": 130195733,
    "routedVolume": 34990159,
    "marketShare": 0.01733,
    "isHalfday": false,
    "litVolume": 34150804
   }
   ]*/
Json::Value IEX::stats::recent()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stats/recent";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stats/records
   {
   "volume": {
    "recordValue": 233000477,
    "recordDate": "2016-01-20",
    "previousDayValue": 99594714,
    "avg30Value": 138634204.5
   },
   "symbolsTraded": {
    "recordValue": 6046,
    "recordDate": "2016-11-10",
    "previousDayValue": 5500,
    "avg30Value": 5617
   },
   "routedVolume": {
    "recordValue": 74855222,
    "recordDate": "2016-11-10",
    "previousDayValue": 29746476,
    "avg30Value": 44520084
   },
   "notional": {
    "recordValue": 9887832327.8355,
    "recordDate": "2016-11-10",
    "previousDayValue": 4175710684.3897,
    "avg30Value": 5771412969.2662
   }
   }*/
Json::Value IEX::stats::records()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stats/records";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stats/historical?date=201605
   [
   {
    "averageDailyVolume": 112247378.5,
    "averageDailyRoutedVolume": 34282226.24,
    "averageMarketShare": 0,
    "averageOrderSize": 493,
    "averageFillSize": 287,
    "bin100Percent": 0.61559,
    "bin101Percent": 0.61559,
    "bin200Percent": 0.61559,
    "bin300Percent": 0.61559,
    "bin400Percent": 0.61559,
    "bin500Percent": 0.61559,
    "bin1000Percent": 0.61559,
    "bin5000Percent": 0.61559,
    "bin10000Percent": 0.61559,
    "bin10000Trades": 4666,
    "bin20000Trades": 1568,
    "bin50000Trades": 231,
    "uniqueSymbolsTraded": 7419,
    "blockPercent": 0.08159,
    "selfCrossPercent": 0.02993,
    "etfPercent": 0.12646,
    "largeCapPercent": 0.40685,
    "midCapPercent": 0.2806,
    "smallCapPercent": 0.18609,
    "venueARCXFirstWaveWeight": 0.22063,
    "venueBATSFirstWaveWeight": 0.06249,
    "venueBATYFirstWaveWeight": 0.07361,
    "venueEDGAFirstWaveWeight": 0.01083,
    "venueEDGXFirstWaveWeight": 0.0869,
    "venueOverallFirstWaveWeight": 1,
    "venueXASEFirstWaveWeight": 0.00321,
    "venueXBOSFirstWaveWeight": 0.02935,
    "venueXCHIFirstWaveWeight": 0.00108,
    "venueXCISFirstWaveWeight": 0.00008,
    "venueXNGSFirstWaveWeight": 0.20358,
    "venueXNYSFirstWaveWeight": 0.29313,
    "venueXPHLFirstWaveWeight": 0.01511,
    "venueARCXFirstWaveRate": 0.97737,
    "venueBATSFirstWaveRate": 0.99357,
    "venueBATYFirstWaveRate": 0.99189,
    "venueEDGAFirstWaveRate": 0.98314,
    "venueEDGXFirstWaveRate": 0.99334,
    "venueOverallFirstWaveRate": 0.98171,
    "venueXASEFirstWaveRate": 0.94479,
    "venueXBOSFirstWaveRate": 0.97829,
    "venueXCHIFirstWaveRate": 0.65811,
    "venueXCISFirstWaveRate": 0.9468,
    "venueXNGSFirstWaveRate": 0.98174,
    "venueXNYSFirstWaveRate": 0.98068,
    "venueXPHLFirstWaveRate": 0.93629
   }
   ]*/
Json::Value IEX::stats::historical(std::string date)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        if(!date.empty()) {
                if(date.size() == 8) {
                        url += "/stats/historical/"+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else{
                        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                        exit(1);
                }
        }

        else{
                url += "/stats/historical/";
                IEX::sendGetRequest(jsonData, url);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stats/historical/daily?last=5
   [
   {
    "date": "2017-05-09",
    "volume": 152907569,
    "routedVolume": 46943802,
    "marketShare": 0.02246,
    "isHalfday": 0,
    "litVolume": 35426666
   },
   {
    "date": "2017-05-08",
    "volume": 142923030,
    "routedVolume": 39507295,
    "marketShare": 0.02254,
    "isHalfday": 0,
    "litVolume": 32404585
   },
   {
    "date": "2017-05-05",
    "volume": 155118117,
    "routedVolume": 39974788,
    "marketShare": 0.02358,
    "isHalfday": 0,
    "litVolume": 35124994
   },
   {
    "date": "2017-05-04",
    "volume": 185715463,
    "routedVolume": 56264408,
    "marketShare": 0.02352,
    "isHalfday": 0,
    "litVolume": 40634976
   },
   {
    "date": "2017-05-03",
    "volume": 183103198,
    "routedVolume": 50953175,
    "marketShare": 0.025009999999999998,
    "isHalfday": 0,
    "litVolume": 40296158
   }
   ]
   EITHER TAKES JUST A SYMBOL, OR SYMBOL AND DATE, OR SYMBOL AND LAST X (UP TO 90)*/
Json::Value IEX::stats::historicalDaily(std::string date)
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        std::locale loc; //For isdigit
        if(!date.empty()) {
                if(date.size() == 8) {
                        url += "/stats/historical/daily?date="+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else if(isdigit(date[0],loc)) {
                        url += "/stats/historical/daily?last="+date;
                        IEX::sendGetRequest(jsonData, url);
                }
                else{
                        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
                        exit(1);
                }
        }

        else{
                url += "/stats/historical/daily";
                IEX::sendGetRequest(jsonData, url);
        }
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /market
   [
   {
    "mic": "TRF",
    "tapeId": "-",
    "venueName": "TRF Volume",
    "volume": 589171705,
    "tapeA": 305187928,
    "tapeB": 119650027,
    "tapeC": 164333750,
    "marketPercent": 0.37027,
    "lastUpdated": 1480433817317
   },
   {
    "mic": "XNGS",
    "tapeId": "Q",
    "venueName": "NASDAQ",
    "volume": 213908393,
    "tapeA": 90791123,
    "tapeB": 30731818,
    "tapeC": 92385452,
    "marketPercent": 0.13443,
    "lastUpdated": 1480433817311
   },
   {
    "mic": "XNYS",
    "tapeId": "N",
    "venueName": "NYSE",
    "volume": 204280163,
    "tapeA": 204280163,
    "tapeB": 0,
    "tapeC": 0,
    "marketPercent": 0.12838,
    "lastUpdated": 1480433817336
   },
   {
    "mic": "ARCX",
    "tapeId": "P",
    "venueName": "NYSE Arca",
    "volume": 180301371,
    "tapeA": 64642458,
    "tapeB": 78727208,
    "tapeC": 36931705,
    "marketPercent": 0.11331,
    "lastUpdated": 1480433817305
   },
   {
    "mic": "EDGX",
    "tapeId": "K",
    "venueName": "EDGX",
    "volume": 137022822,
    "tapeA": 58735505,
    "tapeB": 32753903,
    "tapeC": 45533414,
    "marketPercent": 0.08611,
    "lastUpdated": 1480433817310
   },
   {
    "mic": "BATS",
    "tapeId": "Z",
    "venueName": "BATS BZX",
    "volume": 100403461,
    "tapeA": 52509859,
    "tapeB": 25798360,
    "tapeC": 22095242,
    "marketPercent": 0.0631,
    "lastUpdated": 1480433817311
   },
   {
    "mic": "BATY",
    "tapeId": "Y",
    "venueName": "BATS BYX",
    "volume": 54413196,
    "tapeA": 28539960,
    "tapeB": 13638779,
    "tapeC": 12234457,
    "marketPercent": 0.03419,
    "lastUpdated": 1480433817310
   },
   {
    "mic": "XBOS",
    "tapeId": "B",
    "venueName": "NASDAQ BX",
    "volume": 31417461,
    "tapeA": 16673166,
    "tapeB": 5875538,
    "tapeC": 8868757,
    "marketPercent": 0.01974,
    "lastUpdated": 1480433817311
   },
   {
    "mic": "EDGA",
    "tapeId": "J",
    "venueName": "EDGA",
    "volume": 30670687,
    "tapeA": 15223428,
    "tapeB": 8276375,
    "tapeC": 7170884,
    "marketPercent": 0.01927,
    "lastUpdated": 1480433817311
   },
   {
    "mic": "IEXG",
    "tapeId": "V",
    "venueName": "IEX",
    "volume": 26907838,
    "tapeA": 16578501,
    "tapeB": 3889245,
    "tapeC": 6440092,
    "marketPercent": 0.01691,
    "lastUpdated": 1480433817235
   },
   {
    "mic": "XPHL",
    "tapeId": "X",
    "venueName": "NASDAQ PSX",
    "volume": 13334403,
    "tapeA": 5802294,
    "tapeB": 4239741,
    "tapeC": 3292368,
    "marketPercent": 0.00838,
    "lastUpdated": 1480433817071
   },
   {
    "mic": "XCHI",
    "tapeId": "M",
    "venueName": "CHX",
    "volume": 4719854,
    "tapeA": 834762,
    "tapeB": 3168434,
    "tapeC": 716658,
    "marketPercent": 0.00296,
    "lastUpdated": 1480433814711
   },
   {
    "mic": "XASE",
    "tapeId": "A",
    "venueName": "NYSE MKT",
    "volume": 4419196,
    "tapeA": 0,
    "tapeB": 4419196,
    "tapeC": 0,
    "marketPercent": 0.00277,
    "lastUpdated": 1480433816276
   },
   {
    "mic": "XCIS",
    "tapeId": "C",
    "venueName": "NSX",
    "volume": 187785,
    "tapeA": 39923,
    "tapeB": 62191,
    "tapeC": 85671,
    "marketPercent": 0.00011,
    "lastUpdated": 1480433816141
   }
   ]*/
Json::Value IEX::markets::market()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/market";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

//GET /stock/market/crypto
Json::Value IEX::stocks::crypto()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/market/crypto";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/market/today-earnings
   {
   "bto": [
    {
      "actualEPS": 2.1,
      "consensusEPS": 2.02,
      "estimatedEPS": 2.02,
      "announceTime": "BTO",
      "numberOfEstimates": 14,
      "EPSSurpriseDollar": 0.08,
      "EPSReportDate": "2017-05-02",
      "fiscalPeriod": "Q2 2017",
      "fiscalEndDate": "2017-03-31",
      "yearAgo": 1.67,
      "yearAgoChangePercent": .30,
      "estimatedChangePercent": .28,
      "symbolId": 11,
      "symbol": "AAPL",
      "quote": {
          ...
      },
      "headline": ""
    },
    ...
   ],
   "amc": [
    {
      "actualEPS": 3.36,
      "consensusEPS": 3.22,
      "estimatedEPS": 3.22,
      "announceTime": "AMC",
      "numberOfEstimates": 15,
      "EPSSurpriseDollar": 0.14,
      "EPSReportDate": "2017-05-02",
      "fiscalPeriod": "Q2 2017",
      "fiscalEndDate": "2017-03-31",
      "yearAgo": 1.67,
      "yearAgoChangePercent": .30,
      "estimatedChangePercent": .28,
      "symbolId": 1,
      "symbol": "A",
      "quote": {
          ...
      },
      "headline": ""
    },
    ...
   ]
   }*/
Json::Value IEX::stocks::earningsToday()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/market/today-earnings";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}

/*
   GET /stock/market/upcoming-ipos
   The above example will return JSON with the following keys
   {
    "rawData": [
        {
            "symbol": "VCNX",
            "companyName": "VACCINEX, INC.",
            "expectedDate": "2018-08-09",
            "leadUnderwriters": [
                "BTIG, LLC",
                "Oppenheimer & Co. Inc."
            ],
            "underwriters": [
                "Ladenburg Thalmann & Co. Inc."
            ],
            "companyCounsel": [
                "Hogan Lovells US LLP and Harter Secrest & Emery LLP"
            ],
            "underwriterCounsel": [
                "Mintz, Levin, Cohn, Ferris, Glovsky and Popeo, P.C."
            ],
            "auditor": "Computershare Trust Company, N.A",
            "market": "NASDAQ Global",
            "cik": "0001205922",
            "address": "1895 MOUNT HOPE AVE",
            "city": "ROCHESTER",
            "state": "NY",
            "zip": "14620",
            "phone": "585-271-2700",
            "ceo": "Maurice Zauderer",
            "employees": 44,
            "url": "www.vaccinex.com",
            "status": "Filed",
            "sharesOffered": 3333000,
            "priceLow": 12,
            "priceHigh": 15,
            "offerAmount": null,
            "totalExpenses": 2400000,
            "sharesOverAlloted": 499950,
            "shareholderShares": null,
            "sharesOutstanding": 11474715,
            "lockupPeriodExpiration": "",
            "quietPeriodExpiration": "",
            "revenue": 206000,
            "netIncome": -7862000,
            "totalAssets": 4946000,
            "totalLiabilities": 6544000,
            "stockholderEquity": -133279000,
            "companyDescription": "",
            "businessDescription": "",
            "useOfProceeds": "",
            "competition": "",
            "amount": 44995500,
            "percentOffered": "29.05"
        },
        ...
    ],
    "viewData": [
        {
            "Company": "VACCINEX, INC.",
            "Symbol": "VCNX",
            "Price": "$12.00 - 15.00",
            "Shares": "3,333,000",
            "Amount": "44,995,500",
            "Float": "11,474,715",
            "Percent": "29.05%",
            "Market": "NASDAQ Global",
            "Expected": "2018-08-09"
        },
        ...
    ]
   }*/
Json::Value IEX::stocks::upcomingIPOS()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/market/upcoming-ipos";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}


/*
   GET /stock/market/today-ipos
   The above example will return JSON with the following keys
   {
    "rawData": [
        {
            "symbol": "VCNX",
            "companyName": "VACCINEX, INC.",
            "expectedDate": "2018-08-09",
            "leadUnderwriters": [
                "BTIG, LLC",
                "Oppenheimer & Co. Inc."
            ],
            "underwriters": [
                "Ladenburg Thalmann & Co. Inc."
            ],
            "companyCounsel": [
                "Hogan Lovells US LLP and Harter Secrest & Emery LLP"
            ],
            "underwriterCounsel": [
                "Mintz, Levin, Cohn, Ferris, Glovsky and Popeo, P.C."
            ],
            "auditor": "Computershare Trust Company, N.A",
            "market": "NASDAQ Global",
            "cik": "0001205922",
            "address": "1895 MOUNT HOPE AVE",
            "city": "ROCHESTER",
            "state": "NY",
            "zip": "14620",
            "phone": "585-271-2700",
            "ceo": "Maurice Zauderer",
            "employees": 44,
            "url": "www.vaccinex.com",
            "status": "Filed",
            "sharesOffered": 3333000,
            "priceLow": 12,
            "priceHigh": 15,
            "offerAmount": null,
            "totalExpenses": 2400000,
            "sharesOverAlloted": 499950,
            "shareholderShares": null,
            "sharesOutstanding": 11474715,
            "lockupPeriodExpiration": "",
            "quietPeriodExpiration": "",
            "revenue": 206000,
            "netIncome": -7862000,
            "totalAssets": 4946000,
            "totalLiabilities": 6544000,
            "stockholderEquity": -133279000,
            "companyDescription": "",
            "businessDescription": "",
            "useOfProceeds": "",
            "competition": "",
            "amount": 44995500,
            "percentOffered": "29.05"
        },
        ...
    ],
    "viewData": [
        {
            "Company": "VACCINEX, INC.",
            "Symbol": "VCNX",
            "Price": "$12.00 - 15.00",
            "Shares": "3,333,000",
            "Amount": "44,995,500",
            "Float": "11,474,715",
            "Percent": "29.05%",
            "Market": "NASDAQ Global",
            "Expected": "2018-08-09"
        },
        ...
    ]
   }*/
Json::Value IEX::stocks::todayIPOS()
{
        Json::Value jsonData;
        std::string url(IEX_ENDPOINT);
        url += "/stock/market/today-ipos";
        IEX::sendGetRequest(jsonData, url);
        assert(jsonData.isArray()); //Crash if not an array
        return jsonData;
}
