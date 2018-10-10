#ifndef TechnicalAnalysis_h
#define TechnicalAnalysis_h
#include <vector>
#include <string>
#include <cmath> //abs val
#include <iostream>
#include <assert.h>
#include <thread>
#include <mutex>
#include <boost/optional.hpp>
#include "JSONdata.h"

//TODO: add more Technical Indicators

/* This class stores the results of calculations done on the data from JSONdata
   objects (mainly using closing price, but more to come). It stores these
   results into the TechnicalIndicators struct. The calc functions each
   calculate a different vector that is inside TechnicalIndicators struct. */

class TechnicalAnalysis
{
  //Holds all TI values in vectors
  struct TechnicalIndicators
  {
      std::vector<double> RSI, stochRSI,fiftySMA,hundredSMA,hundFifSMA,twoHundSMA,
      fiftyEMA, hundredEMA, hundFifEMA, twoHundEMA, stdDeviation, MACD, MACD_Signal,
      MACD_EMA;
  }indicators;

public:

void accessSignal(boost::optional<std::vector<double>&> copy = boost::none,
                boost::optional<double> temp = boost::none);

void accessMACD(boost::optional<std::vector<double>&> copy = boost::none,
                boost::optional<double> temp = boost::none);

void accessRSI(boost::optional<std::vector<double>&> copy = boost::none,
               boost::optional<double> temp = boost::none);

void accessStoch(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                 boost::optional<double> temp = boost::none);

void accessFifSMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                  boost::optional<double> temp = boost::none);

void accessHundSMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                   boost::optional<double> temp = boost::none);

void accessHundFifSMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                      boost::optional<double> temp = boost::none);

void accessTwoHundSMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                      boost::optional<double> temp = boost::none);

void accessFifEMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                  boost::optional<double> temp = boost::none);

void accessHundEMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                   boost::optional<double> temp = boost::none);

void accessHundFifEMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                      boost::optional<double> temp = boost::none);

void accessTwoHundEMA(boost::optional<std::vector<double>&> EMPTY_VEC = boost::none,
                      boost::optional<double> temp = boost::none);

void getMACD(std::vector<double> &) const;
void getSignal(std::vector<double> &) const;


void getRSI(std::vector<double> &) const;
void getStoch(std::vector<double> &) const;

void getFifSMA(std::vector<double> &) const;
void getHundSMA(std::vector<double> &) const;
void getHundFifSMA(std::vector<double> &) const;
void getTwoHundSMA(std::vector<double> &) const;

void getFifEMA(std::vector<double> &) const;
void getHundEMA(std::vector<double> &) const;
void getHundFifEMA(std::vector<double> &) const;
void getTwoHundEMA(std::vector<double> &) const;

void setFifSMA(const double &);
void setHundSMA(const double &);
void setHundFifSMA(const double &);
void setTwoHundSMA(const double &);

void setFifEMA(const double &);
void setHundEMA(const double &);
void setHundFifEMA(const double &);
void setTwoHundEMA(const double &);

void setRSI(const double &);
void setStoch(const double &);

void setMACD(const double &);
void setSignal(const double &);

//Functions below calculate values of TechnicalIndicators and stores them into TI struct
void calcFiftySMA(JSONdata &);
void calcHundredSMA(JSONdata &);
void calcHundFiftySMA(JSONdata &);
void calcTwoHundSMA(JSONdata &);

void calcFiftyEMA(JSONdata &);
void calcHundredEMA(JSONdata &);
void calcHundFiftyEMA(JSONdata &);
void calcTwoHundEMA(JSONdata &);

void calcRSI(JSONdata &);
void calcStochRSI();

void calcMACD(JSONdata &);

void clearTAobj();
};

#endif
