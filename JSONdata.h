#ifndef JSONdata_h
#define JSONdata_h

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <boost/optional.hpp>
#include <json/json.h>

/* This class store the values of data fetched from the IEX::stocks::chartRange
   function inside the priceData struct. It's member functions are
   explain in the file JSONdata.cpp. The priceData struct is passed to the
   TechnicalAnalysis class for calculations. */
class JSONdata
{
  struct priceData
  {
    std::vector <double> open, high, low, close, change, changePercent, vmap, changeOverTime;
    std::vector <std::string> date, label;
    std::vector <long long> volume, unadjustedVolume;
  }pricingData;

public:
void accessUnAdjVol(boost::optional<std::vector<long long>&> EMPTY_VEC = boost::none,
                    boost::optional<long long> TEMP = boost::none);

void accessVol(boost::optional<std::vector<long long>&> EMPTY_VEC = boost::none,
               boost::optional<long long> TEMP = boost::none);

void accessLabel(boost::optional<std::vector<std::string>&> EMPTY_VEC = boost::none,
                 boost::optional<std::string> TEMP = boost::none);

void accessDate(boost::optional<std::vector<std::string>&> EMPTY_VEC = boost::none,
                boost::optional<std::string> TEMP = boost::none);

void accessChgOvrTime(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                      boost::optional<double> TEMP = boost::none);

void accessVmap(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                boost::optional<double> TEMP = boost::none);

void accessChgPer(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                  boost::optional<double> TEMP = boost::none);

void accessChange(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                  boost::optional<double> TEMP = boost::none);

void accessClose(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                 boost::optional<double> TEMP = boost::none);

void accessLow(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
               boost::optional<double> TEMP = boost::none);

void accessHigh(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                boost::optional<double> TEMP = boost::none);

void accessOpen(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                boost::optional<double> TEMP = boost::none);

void setOpen(const double &);
void setHigh(const double &);
void setLow(const double &);
void setClose(const double &);
void setChange(const double &);
void setChgPer(const double &);
void setVmap(const double &);
void setChgOvrTime(const double &);

void setDate(const std::string &);
void setLabel(const std::string &);

void setVol(const long long &);
void setUnAdjVol(const long long &);

void getOpen(std::vector<double> &) const;
void getHigh(std::vector<double> &) const;
void getLow(std::vector<double> &) const;
void getClose(std::vector<double> &) const;
void getChange(std::vector<double> &) const;
void getChgPer(std::vector<double> &) const;
void getVmap(std::vector<double> &) const;
void getChgOvrTime(std::vector<double> &) const;

void getDate(std::vector<std::string> &) const;
void getLabel(std::vector<std::string> &) const;

void getVol(std::vector<long long> &) const;
void getUnAdjVol(std::vector<long long> &) const;


bool isEmpty() const;
void clearJSONstruct();
void parseIEXdata(const Json::Value &);

};

#endif
