#include "main.h"

auto main() -> int
{
  JSONdata formattedHistoricalData; //Vec to hold JSONdata structs
  TechnicalAnalysis TIobj;

  Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d"); //Pull stock data from IEX API

  parseIEXdata(IEXdata, formattedHistoricalData);

  //TIobj.calcRSI(formattedHistoricalData);
  //TIobj.calcStochRSI();
  for(int i = 0; i < 236; i++){
    std::cout << i << ", ";
  }
}

void parseIEXdata(const Json::Value IEXdata, JSONdata &formattedHistoricalData)
{
  JSONdata parsedData;
  int i = 0;
  //Step through JSON file until the end is reached
  while(i < IEXdata.size()){
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
      //formattedHistoricalData.push_back(parsedData);
      i++;
    }

}
