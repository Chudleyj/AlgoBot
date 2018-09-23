#include "TechnicalAnalysis.h"

std::mutex mtx;

void TechnicalAnalysis::accessRSI(boost::optional<std::vector<double>&> copy,
                                  boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);

  if(temp)
    setRSI(*temp);
  else if(copy)
      getRSI(*copy);
}

void TechnicalAnalysis::accessStoch(boost::optional<std::vector<double>&> copy,
                                    boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setStoch(*temp);
  else if(copy)
    getStoch(*copy);
}

void TechnicalAnalysis::accessFifSMA(boost::optional<std::vector<double>&> copy,
                                    boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setFifSMA(*temp);
  else if (copy)
    getFifSMA(*copy);
}

void TechnicalAnalysis::accessHundSMA(boost::optional<std::vector<double>&> copy,
                                      boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setHundSMA(*temp);
  else if (copy)
    getHundSMA(*copy);
}

void TechnicalAnalysis::accessHundFifSMA(boost::optional<std::vector<double>&> copy,
                                         boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setHundFifSMA(*temp);
  else if (copy)
    getHundFifSMA(*copy);
}

void TechnicalAnalysis::accessTwoHundSMA(boost::optional<std::vector<double>&> copy,
                                         boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setTwoHundSMA(*temp);
  else if (copy)
    getTwoHundSMA(*copy);
}

void TechnicalAnalysis::accessFifEMA(boost::optional<std::vector<double>&> copy,
                                     boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setFifEMA(*temp);
  else if (copy)
    getFifEMA(*copy);
}

void TechnicalAnalysis::accessHundEMA(boost::optional<std::vector<double>&> copy,
                                      boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setHundEMA(*temp);
  else if (copy)
    getHundEMA(*copy);
}

void TechnicalAnalysis::accessHundFifEMA(boost::optional<std::vector<double>&> copy,
                                         boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setHundFifEMA(*temp);
  else if (copy)
    getHundFifEMA(*copy);
}

void TechnicalAnalysis::accessTwoHundEMA(boost::optional<std::vector<double>&> copy,
                                         boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  if(temp)
    setTwoHundEMA(*temp);
  else if (copy)
    getTwoHundEMA(*copy);
}
/*-------------------- START GETS --------------------*/
void TechnicalAnalysis::getRSI(std::vector <double> &copy) const
{
        copy = indicators.RSI;
}

void TechnicalAnalysis::getStoch(std::vector <double> &copy) const
{
        copy = indicators.stochRSI;
}

void TechnicalAnalysis::getFifSMA(std::vector <double> &copy) const
{
        copy = indicators.fiftySMA;
}

void TechnicalAnalysis::getHundSMA(std::vector <double> &copy) const
{
        copy = indicators.hundredSMA;
}

void TechnicalAnalysis::getHundFifSMA(std::vector <double> &copy) const
{
        copy = indicators.hundFifSMA;
}

void TechnicalAnalysis::getTwoHundSMA(std::vector <double> &copy) const
{
        copy = indicators.twoHundSMA;
}

void TechnicalAnalysis::getFifEMA(std::vector <double> &copy) const
{
        copy = indicators.fiftyEMA;
}

void TechnicalAnalysis::getHundEMA(std::vector <double> &copy) const
{
        copy = indicators.hundredEMA;
}

void TechnicalAnalysis::getHundFifEMA(std::vector <double> &copy) const
{
        copy = indicators.hundFifEMA;
}

void TechnicalAnalysis::getTwoHundEMA(std::vector <double> &copy) const
{
        copy = indicators.twoHundEMA;
}
/*-------------------- END GETS --------------------*/

/*-------------------- START SETS --------------------*/
void TechnicalAnalysis::setFifSMA(const double &temp)
{
        indicators.fiftySMA.push_back(temp);
}

void TechnicalAnalysis::setHundSMA(const double &temp)
{

        indicators.hundredSMA.push_back(temp);
}

void TechnicalAnalysis::setHundFifSMA(const double &temp)
{
        indicators.hundFifSMA.push_back(temp);
}

void TechnicalAnalysis::setTwoHundSMA(const double &temp)
{
        indicators.twoHundSMA.push_back(temp);
}

void TechnicalAnalysis::setFifEMA(const double &temp)
{
        indicators.fiftyEMA.push_back(temp);
}

void TechnicalAnalysis::setHundEMA(const double &temp)
{
        indicators.hundredEMA.push_back(temp);
}

void TechnicalAnalysis::setHundFifEMA(const double &temp)
{
        indicators.hundFifEMA.push_back(temp);
}

void TechnicalAnalysis::setTwoHundEMA(const double &temp)
{
        indicators.twoHundEMA.push_back(temp);
}

void TechnicalAnalysis::setRSI(const double &temp)
{
        indicators.RSI.push_back(temp);
}

void TechnicalAnalysis::setStoch(const double &temp)
{
        indicators.stochRSI.push_back(temp);
}
/*-------------------- END SETS --------------------*/
void TechnicalAnalysis::clearTAobj()
{
        indicators.RSI.clear();
        indicators.stochRSI.clear();
        indicators.fiftySMA.clear();
        indicators.hundredSMA.clear();
        indicators.hundFifSMA.clear();
        indicators.twoHundSMA.clear();
        indicators.fiftyEMA.clear();
        indicators.hundredEMA.clear();
        indicators.hundFifEMA.clear();
        indicators.twoHundEMA.clear();
        indicators.stdDeviation.clear();
}
