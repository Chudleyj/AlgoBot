#ifndef TechnicalAnalysis_h
#define TechnicalAnalysis_h
#include<vector>
#include<string>
#include <cmath> //abs val
#include <iostream>
#include "JSONdata.h"

//TODO: add more Technical Indicators
//Holds all TI values in vectors
struct TechnicalIndicators{
  std::vector<double> RSI, stochRSI;
};

//Calculates values of TechnicalIndicators and stores them
class TechnicalAnalysis{
  std::vector<double> RSI, stochRSI;
  public:
    void calcRSI(const JSONdata);
    void calcStochRSI();
};

#endif
