#ifndef TechnicalAnalysis_h
#define TechnicalAnalysis_h
#include <vector>
#include <string>
#include <cmath> //abs val
#include <iostream>
#include <assert.h>
#include <thread>
#include <mutex>
#include "JSONdata.h"

//TODO: add more Technical Indicators
//Holds all TI values in vectors



//Calculates values of TechnicalIndicators and stores them
class TechnicalAnalysis
{
std::vector<double> RSI, stochRSI,fiftySMA,hundredSMA,hundFifSMA,twoHundSMA,
                    fiftyEMA, hundredEMA, hundFifEMA, twoHundEMA, stdDeviation;
public:

std::vector<double> getRSI();
std::vector<double> getStoch();

std::vector<double> getFifSMA();
std::vector<double> getHundSMA();
std::vector<double> getHundFifSMA();
std::vector<double> getTwoHundSMA();

std::vector<double> getFifEMA();
std::vector<double> getHundEMA();
std::vector<double> getHundFifEMA();
std::vector<double> getTwoHundEMA();

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

void calcFiftySMA(const JSONdata &);
void calcHundredSMA(const JSONdata &);
void calcHundFiftySMA(const JSONdata &);
void calcTwoHundSMA(const JSONdata &);

void calcFiftyEMA(const JSONdata &);
void calcHundredEMA(const JSONdata &);
void calcHundFiftyEMA(const JSONdata &);
void calcTwoHundEMA(const JSONdata &);

void calcRSI(const JSONdata &);
void calcStochRSI();

void clearTAobj();
};

#endif
