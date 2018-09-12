#include "TechnicalAnalysis.h"

void TechnicalAnalysis::calcRSI(const JSONdata HistoricalData){
  std::vector<long double> gain, loss, change, avgGain, avgLoss, RS;
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
      RSI.push_back(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
  }
}

void TechnicalAnalysis::calcStochRSI(){
  std::vector<double> tempVec;

  for(int i = 13; i <RSI.size(); i ++){
    copyVec(RSI,tempVec,i);
    auto lowIt= *std::min_element(tempVec.begin(), tempVec.end());
    auto highIt= *std::max_element(tempVec.begin(), tempVec.end());
    stochRSI.push_back((tempVec.back()-lowIt)/(highIt-lowIt));
    tempVec.clear();
    }
}

void copyVec(const std::vector<double> &RSI, std::vector<double> &temp, int loc){
  for(int i = 13; i >= 0; i--){
    temp.push_back(RSI[loc-i]);
  }
}
