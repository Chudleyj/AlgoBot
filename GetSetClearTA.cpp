#include "TechnicalAnalysis.h"

std::mutex mtx; //For std::lock_guard

/* Access functions are used to call either the get or set for a
  member variable, depending on what is past to them
  (hence the boost::optionals)
  Using boost::optional over std::optional so I can pass by reference
  The point of using these instead of directly calling get or set functions
  is to ensure thread safety. This way, no function can look at or set
  a var while another thread has the lock.
  ***Technically, these are not needed for this class as it stands now
  However, as algorithms that will use these variables are added, this will
  be needed. */

//Temp = varible to temporarily hold value to be set via set functions
//Copy = variable that will get a copy of whatever is returned by the get func
void TechnicalAnalysis::accessMACD(boost::optional<std::vector<double>&> copy,
                                   boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx); //Lock function from all other threads

  if(temp)
    setMACD(*temp);
  else if(copy)
    getMACD(*copy);
}

void TechnicalAnalysis::accessSignal(boost::optional<std::vector<double>&> copy,
                                     boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(mtx);

  if(temp)
    setSignal(*temp);
  else if(copy)
    getSignal(*copy);
}

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

/* -------------------- START GETS --------------------
   Get functions take in an vector, and make it a copy of whatever vector
   the specific get function is for. These can be void because the vector
   is passed by reference
   These functions are const because we never modify any part of the class,
   and a const function will ensure this */
void TechnicalAnalysis::getMACD(std::vector <double> &copy) const
{
        copy = indicators.MACD;
}

void TechnicalAnalysis::getSignal(std::vector <double> &copy) const
{
        copy = indicators.MACD_Signal;
}

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

/* -------------------- START SETS --------------------
   Here, set functions take in a value (temp), and push it back to their
   corresponding member variable vector */
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

void TechnicalAnalysis::setMACD(const double &temp)
{
        indicators.MACD.push_back(temp);
}

void TechnicalAnalysis::setSignal(const double &temp)
{
        indicators.MACD_Signal.push_back(temp);
}
/*-------------------- END SETS --------------------*/

/* Clear all the data out of the vectors
   This is done because the data needs to be always as up to date as possible
   So, the data is calculated once, and then cleared and replaced.
   In the future, before it is cleared, it will be used by algorithms
   Which will always want the newest possible data, hence the clear function */
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
