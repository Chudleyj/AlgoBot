#include "main.h"

int main()
{
        JSONdata minData, threadData, test;
        TechnicalAnalysis TIobj;

        Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d"); //Pull stock data from IEX API
        parseIEXdata(IEXdata, minData);

        while(1) {
                //Use a seperate thread to update data for next calcs while current calcs are done.
                std::thread t1(getAndParseData, std::ref(threadData),std::move("aapl"), std::move("1d"));
                //std::thread t2(getAndParseData, std::ref(test), std::move("1y"));

                TIobj.calcRSI(minData);
                TIobj.calcStochRSI();

                TIobj.calcFiftySMA(minData);
                TIobj.calcHundredSMA(minData);
                TIobj.calcHundFiftySMA(minData);
                TIobj.calcTwoHundSMA(minData);

                TIobj.calcFiftyEMA(minData);
                TIobj.calcHundredEMA(minData);
                TIobj.calcHundFiftyEMA(minData);
                TIobj.calcTwoHundEMA(minData);

                //Clean up for reassignment
                TIobj.clearTAobj();
                minData.clearJSONstruct();

                t1.join(); //Rejoin main thread, adding new data for next calcs
                //t2.join();

                //Using var threadData here to temp store minData avoids deadlock.
                minData = threadData;
                threadData.clearJSONstruct();
        }

        return 0;
}

//MULTITHREAD T1 USES THIS
void getAndParseData(JSONdata &dataToFormat, const std::string &stock, const std::string &range)
{
        assert(dataToFormat.isEmpty());
        assert(!range.empty());
        assert(!stock.empty());

        Json::Value IEXdata = IEX::stocks::chartRange(stock, range);
        parseIEXdata(IEXdata, dataToFormat);
}

void parseIEXdata(const Json::Value &IEXdata, JSONdata &formattedHistoricalData)
{
        assert(!IEXdata.empty());
        int i = 0;

        //Step through JSON file until the end is reached
        while(i < IEXdata.size()) {
                //Parse the JSON data into the struct
                formattedHistoricalData.open.push_back(IEXdata[i]["open"].asDouble());
                formattedHistoricalData.high.push_back(IEXdata[i]["high"].asDouble());
                formattedHistoricalData.low.push_back(IEXdata[i]["low"].asDouble());
                formattedHistoricalData.close.push_back(IEXdata[i]["close"].asDouble());
                formattedHistoricalData.volume.push_back(IEXdata[i]["volume"].asInt64());
                formattedHistoricalData.unadjustedVolume.push_back(IEXdata[i]["unadjustedVolume"].asInt64());
                formattedHistoricalData.change.push_back(IEXdata[i]["change"].asDouble());
                formattedHistoricalData.changePercent.push_back(IEXdata[i]["changePercent"].asDouble());
                formattedHistoricalData.vmap.push_back(IEXdata[i]["vmap"].asDouble());
                formattedHistoricalData.changeOverTime.push_back(IEXdata[i]["changeOverTime"].asDouble());
                formattedHistoricalData.date.push_back(IEXdata[i]["date"].asString());
                formattedHistoricalData.label.push_back(IEXdata[i]["label"].asString());
                i++;
        }

}
