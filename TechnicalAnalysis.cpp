#include "TechnicalAnalysis.h"

/*
   void TechnicalAnalysis::calcSD()
   {
    double sum = 0.0, mean, standardDeviation = 0.0;

    for(int i = 0; i < 10; ++i)
        sum += data[i];

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
   }

 */
/*-------------------- START EMAs --------------------*/

void TechnicalAnalysis::calcFiftyEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        int period = 50, j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(int i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setFifEMA(SMA);
        multipler = 2/(period + 1);

        for(int i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setFifEMA(tempEMA[j]);
        }
}

void TechnicalAnalysis::calcHundredEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        int period = 100, j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);


        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(int i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setHundEMA(SMA);
        multipler = 2/(period + 1);

        for(int i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setHundEMA(tempEMA[j]);
        }
}

void TechnicalAnalysis::calcHundFiftyEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        int period = 150, j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(int i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setHundFifEMA(SMA);
        multipler = 2/(period + 1);

        for(int i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setHundFifEMA(tempEMA[j]);
        }
}

void TechnicalAnalysis::calcTwoHundEMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double SMA = 0.0, sum = 0.0, multipler = 0.0;
        int period = 200, j = 0;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY EMA YET";
          return;
        }

        std::vector<double> tempEMA;

        for(int i = 0; i < period; i++)
                sum += closePrices[i];

        SMA = sum/period;
        tempEMA.push_back(SMA);
        setTwoHundEMA(SMA);
        multipler = 2/(period + 1);

        for(int i = period; i <= (closePrices.size() - period); i++) {
                tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
                j++;
                setTwoHundEMA(tempEMA[j]);
        }
}

/*-------------------- END EMAs   --------------------*/


/*-------------------- START SMAs --------------------*/
void TechnicalAnalysis::calcFiftySMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        int period = 50;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices,boost::none);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(int i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (int j = i; j < i + period; j++)
                        sum += closePrices[j];

                setFifSMA(sum/period);
        }
}


void TechnicalAnalysis::calcHundredSMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        int period = 100;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(int i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (int j = i; j < i + period; j++)
                        sum += closePrices[j];

                setHundSMA(sum/period);
        }
}

void TechnicalAnalysis::calcHundFiftySMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        int period = 150;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(int i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (int j = i; j < i + period; j++)
                        sum += closePrices[j];

                setHundFifSMA(sum/period);
        }
}

void TechnicalAnalysis::calcTwoHundSMA(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());
        double sum;
        int period = 200;

        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        if(closePrices.size() <= period){
          std::cout<<std::endl <<"NOT ENOUGH DATA FOR " << period << " DAY SMA YET";
          return;
        }

        for(int i = 0; i <= (closePrices.size() - period); i++) {
                sum = 0.0;

                for (int j = i; j < i + period; j++)
                        sum += closePrices[j];

                setTwoHundSMA(sum/period);
        }
}
/*-------------------- END SMAs   --------------------*/


/*-------------------- START RSI  --------------------*/
void TechnicalAnalysis::calcRSI(JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        auto pushCurrentPeriod = [] (const std::vector<long double> &currPeri, std::vector<long double> &change){
                                         for(int i = 1; i < currPeri.size(); i++)
                                                 change.push_back(currPeri[i] - currPeri[i-1]);
                                 };

        std::vector<long double> gain, loss, change, avgGain, avgLoss, RS;
        std::vector<double> closePrices;
        HistoricalData.accessClose(closePrices);

        //We need these if/else statements so program works when there hasn't been 250 data points yet.
        if(closePrices.size() > 250) {
                std::vector <long double> currentPeriod(closePrices.end()-250,closePrices.end());
                pushCurrentPeriod(currentPeriod, change);
        }

        else{
                std::vector <long double> currentPeriod(closePrices.begin(),closePrices.end());
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
                setRSI(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
        }
        calcStochRSI();

        for(int i : indicators.RSI) {
                std::cout<<std::endl<<i;
        }
}

void TechnicalAnalysis::calcStochRSI()
{
        assert(!indicators.RSI.empty());

        auto copy = [] (const std::vector<double> &RSI, std::vector<double> &temp, const int &loc){
                            for(int i = 13; i >= 0; i--)
                                    temp.push_back(RSI[loc-i]);
                    };

        std::vector<double> tempVec, tempRSI;
        getRSI(tempRSI);

        for(int i = 13; i <tempRSI.size(); i++) {
                copy(tempRSI,tempVec,i);
                auto lowIt= *std::min_element(tempVec.begin(), tempVec.end());
                auto highIt= *std::max_element(tempVec.begin(), tempVec.end());
                setStoch((tempVec.back()-lowIt)/(highIt-lowIt));
                tempVec.clear();
        }
}
/*-------------------- END RSI  --------------------*/
