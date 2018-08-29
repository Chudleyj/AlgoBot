#include "TechnicalAnalysis.h"

//Calculates RSI of a given stock
void TechnicalAnalysis::calcRSI(const JSONdata HistoricalData){
  //TechnicalIndicators RSIstruct;
  std::vector<long double> gain, loss, change, avgGain, avgLoss, RS;
  std::cout << HistoricalData.close.size();
  std::vector <long double> currentPeriod(HistoricalData.close.end()-250,HistoricalData.close.end());
  double sumGain = 0, sumLoss = 0;
  for(int i = 1; i < currentPeriod.size(); i++)
      change.push_back(currentPeriod[i] - currentPeriod[i-1]);
  for(int i = 0; i < change.size(); i++){
      change[i] > 0 ? gain.push_back(change[i]) : gain.push_back(0);
      change[i] < 0 ? loss.push_back(abs(change[i])) : loss.push_back(0);
      sumGain += gain[i];
      sumLoss += loss[i];
  }

  avgGain.push_back(sumGain/14);
  avgLoss.push_back(sumLoss/14);

  for(int i = 14, j = 1; i < gain.size(); i++){
      avgGain.push_back(((avgGain[j-1] * 13)+ gain[i])/14);
      avgLoss.push_back(((avgLoss[j-1] * 13)+ loss[i])/14);
      j++;
  }

  for(int i = 0; i < avgGain.size(); i++){
      RS.push_back(avgGain[i]/avgLoss[i]);
      RSI.push_back(avgLoss[i] == 0 ? 100 : (100 - (100/(1+RS[i])));
  }
}
//Calculates stochRSI of a given stock
void TechnicalAnalysis::calcStochRSI(){
  for(int i =0; i < RSI.size(); i++){
    std::cout<<RSI[i] <<", ";
  }
  std::cout << RSI.size() << std::endl;
}
