#ifndef IEX_h
#define IEX_h

#include <json/json.h>
#include <curl/curl.h>
#include <locale> //std::locale, std::isdigit
#include <string>
#include <cassert>
#include <iostream>

#define IEX_ENDPOINT "https://api.iextrading.com/1.0"

namespace IEX {
void sendGetRequest(Json::Value &data, const std::string url);
namespace stocks {
Json::Value batch(const std::string &);
Json::Value book(const std::string &);
Json::Value chart(const std::string &);
Json::Value chartRange(const std::string &, const std::string &);
Json::Value chartDate(const std::string &, const std::string &);
Json::Value chartDynamic(const std::string &);
Json::Value company(const std::string &);
Json::Value crypto();
Json::Value delayedQuote(const std::string &);
Json::Value dividends(const std::string &, const std::string &);
Json::Value earnings(const std::string &);
Json::Value earningsToday();
Json::Value effectiveSpread(const std::string &);
Json::Value financials(const std::string &);
Json::Value upcomingIPOS();
Json::Value todayIPOS();
Json::Value stats(const std::string &);
Json::Value largestTrades(const std::string &);
Json::Value list(const std::string &);
Json::Value logo(const std::string &);
Json::Value news(const std::string &, int last = 0);
Json::Value OHLC(const std::string &);
Json::Value peers(const std::string &);
Json::Value previous(const std::string &);
Json::Value price(const std::string &);
Json::Value quote(const std::string &, bool displayPercent = false);
Json::Value relevant(const std::string &);
Json::Value sectorPerformance();
Json::Value splits(const std::string &, const std::string &);
Json::Value relevant(const std::string &);
Json::Value timeSeries(const std::string &);
Json::Value VolumeByVenue(const std::string &);
}

namespace refData {
Json::Value symbols();
Json::Value corporateActions(std::string date = "");
Json::Value dividends(std::string date = "");
Json::Value nextDayExDate(std::string date = "");
Json::Value symbolDirectory(std::string date = "");
}

namespace marketData {

}

namespace stats {
Json::Value intraday();
Json::Value recent();
Json::Value records();
Json::Value historical(std::string date = "");
Json::Value historicalDaily(std::string date = "");
}

namespace markets {
Json::Value market();
}
}

#endif
