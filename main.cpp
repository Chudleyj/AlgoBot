#include "main.h"

int main()
{
    JSONdata formattedHistoricalData;
    TechnicalAnalysis TIobj;

    Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d"); //Pull stock data from IEX API
    parseIEXdata(IEXdata, formattedHistoricalData);
    while(1){
        //Use a seperate thread to update data for next calcs while current calcs are done.
        std::thread t1(getAndParseData, std::ref(formattedHistoricalData));

        TIobj.calcRSI(formattedHistoricalData);
        TIobj.calcStochRSI();

        //Clean up for reassignment
        TIobj.clearTAobj();
        formattedHistoricalData.clearJSONstruct();
        IEXdata = &nanl;

        t1.join(); //Rejoin main thread, adding new data for next calcs
        std::cout<<std::endl << "--------------------------" <<std::endl; //TODO temp, remove
      }
      return 0;
}

//MULTITHREAD USES THIS
void getAndParseData(JSONdata &formattedHistoricalData){
  Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d");
  parseIEXdata(IEXdata, formattedHistoricalData);
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
