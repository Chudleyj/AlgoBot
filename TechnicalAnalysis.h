#ifndef TechnicalAnalysis_h
#define TechnicalAnalysis_h
#include <vector>
#include <string>
#include <cmath> //abs val
#include <iostream>
#include <assert.h>
#include "JSONdata.h"

//TODO: add more Technical Indicators
//Holds all TI values in vectors



//Calculates values of TechnicalIndicators and stores them
class TechnicalAnalysis
{
std::vector<double> RSI, stochRSI,fiftySMA,hundredSMA,hundFifSMA,twoHundSMA,
                    fiftyEMA, hundredEMA, hundFifEMA, twoHundEMA;
public:

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
