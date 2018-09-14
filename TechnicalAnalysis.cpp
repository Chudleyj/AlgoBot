#include "TechnicalAnalysis.h"

void TechnicalAnalysis::clearTAobj()
{
        RSI.clear();
        stochRSI.clear();
        fiftySMA.clear();
        hundredSMA.clear();
        hundFifSMA.clear();
        twoHundSMA.clear();
        fiftyEMA.clear();
        hundredEMA.clear();
        hundFifEMA.clear();
        twoHundEMA.clear();
}

/*-------------------- START EMAs --------------------*/
void TechnicalAnalysis::calcFiftyEMA(const JSONdata &HistoricalData)
{
  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 50, j = 0;

  for(int i = 0; i < period; i++)
    sum += HistoricalData.close[i];

  SMA = sum/period;
  fiftyEMA.push_back(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (HistoricalData.close.size() - period); i++){
    fiftyEMA.push_back((HistoricalData.close[i]-fiftyEMA[j])*multipler+fiftyEMA[j]);
    j++;
  }
}

void TechnicalAnalysis::calcHundredEMA(const JSONdata &HistoricalData)
{
  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 100, j = 0;

  for(int i = 0; i < period; i++)
    sum += HistoricalData.close[i];

  SMA = sum/period;
  fiftyEMA.push_back(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (HistoricalData.close.size() - period); i++){
    hundredEMA.push_back((HistoricalData.close[i]-fiftyEMA[j])*multipler+fiftyEMA[j]);
    j++;
  }
}

void TechnicalAnalysis::calcHundFiftyEMA(const JSONdata &HistoricalData)
{
  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 50, j = 0;

  for(int i = 0; i < period; i++)
    sum += HistoricalData.close[i];

  SMA = sum/period;
  hundFifEMA.push_back(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (HistoricalData.close.size() - period); i++){
    fiftyEMA.push_back((HistoricalData.close[i]-fiftyEMA[j])*multipler+fiftyEMA[j]);
    j++;
  }
}

void TechnicalAnalysis::calcTwoHundEMA(const JSONdata &HistoricalData)
{
  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 50, j = 0;

  for(int i = 0; i < period; i++)
    sum += HistoricalData.close[i];

  SMA = sum/period;
  fiftyEMA.push_back(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (HistoricalData.close.size() - period); i++){
    twoHundEMA.push_back((HistoricalData.close[i]-fiftyEMA[j])*multipler+fiftyEMA[j]);
    j++;
  }

  for(double i : twoHundEMA){
      std::cout<<std::endl<<i;
  }
}
/*-------------------- END EMAs   --------------------*/


/*-------------------- START SMAs --------------------*/
void TechnicalAnalysis::calcFiftySMA(const JSONdata &HistoricalData)
{
  double sum;
  int period = 50;

  for(int i = 0; i <= (HistoricalData.close.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += HistoricalData.close[j];

    fiftySMA.push_back(sum/period);
  }
}

void TechnicalAnalysis::calcHundredSMA(const JSONdata &HistoricalData)
{
  double sum;
  int period = 100;

  for(int i = 0; i <= (HistoricalData.close.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += HistoricalData.close[j];

    hundredSMA.push_back(sum/period);
  }
}

void TechnicalAnalysis::calcHundFiftySMA(const JSONdata &HistoricalData)
{
  double sum;
  int period = 150;

  for(int i = 0; i <= (HistoricalData.close.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += HistoricalData.close[j];

    hundFifSMA.push_back(sum/period);
  }
}

void TechnicalAnalysis::calcTwoHundSMA(const JSONdata &HistoricalData)
{
  double sum;
  int period = 200;

  for(int i = 0; i <= (HistoricalData.close.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += HistoricalData.close[j];

    twoHundSMA.push_back(sum/period);
  }
}
/*-------------------- END SMAs   --------------------*/


/*-------------------- START RSI  --------------------*/
void TechnicalAnalysis::calcRSI(const JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        auto pushCurrentPeriod = [] (const std::vector<long double> &currPeri, std::vector<long double> &change){
                                         for(int i = 1; i < currPeri.size(); i++)
                                                 change.push_back(currPeri[i] - currPeri[i-1]);
                                 };

        std::vector<long double> gain, loss, change, avgGain, avgLoss, RS;

        //We need these if/else statements so program works when there hasn't been 250 min in the day yet.
        if(HistoricalData.close.size() > 250) {
                std::vector <long double> currentPeriod(HistoricalData.close.end()-250,HistoricalData.close.end());
                pushCurrentPeriod(currentPeriod, change);
        }

        else{
                std::vector <long double> currentPeriod(HistoricalData.close.begin(),HistoricalData.close.end());
                pushCurrentPeriod(currentPeriod, change);
        }

        double sumGain = 0, sumLoss = 0;

        for(int i = 0; i < change.size(); i++) {
                change[i] > 0 ? gain.push_back(change[i]) : gain.push_back(0);
                change[i] < 0 ? loss.push_back(abs(change[i])) : loss.push_back(0);
                sumGain += gain[i];
                sumLoss += loss[i];
        }

        avgGain.push_back(sumGain/14);
        avgLoss.push_back(sumLoss/14);

        for(int i = 14, j = 1; i < gain.size(); i++) {
                avgGain.push_back(((avgGain[j-1] * 13)+ gain[i])/14);
                avgLoss.push_back(((avgLoss[j-1] * 13)+ loss[i])/14);
                j++;
        }

        for(int i = 0; i < avgGain.size(); i++) {
                RS.push_back(avgGain[i]/avgLoss[i]);
                RSI.push_back(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
              //  std::cout<<"RSI: " << RSI[i] << std::endl;
        }
}

void TechnicalAnalysis::calcStochRSI()
{
        assert(!RSI.empty());

        auto copy = [] (const std::vector<double> &RSI, std::vector<double> &temp, const int &loc){
                            for(int i = 13; i >= 0; i--)
                                    temp.push_back(RSI[loc-i]);
                    };

        std::vector<double> tempVec;


        for(int i = 13; i <RSI.size(); i++) {
                copy(RSI,tempVec,i);
                auto lowIt= *std::min_element(tempVec.begin(), tempVec.end());
                auto highIt= *std::max_element(tempVec.begin(), tempVec.end());
                stochRSI.push_back((tempVec.back()-lowIt)/(highIt-lowIt));
                tempVec.clear();
        }
}
/*-------------------- END RSI  --------------------*/
