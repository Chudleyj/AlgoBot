#include "JSONdata.h"

std::mutex _mtx;

void JSONdata::setOpen(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  open.push_back(temp);
}

void JSONdata::setHigh(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  high.push_back(temp);
}

void JSONdata::setLow(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  low.push_back(temp);
}

void JSONdata::setClose(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  close.push_back(temp);
}

void JSONdata::setChange(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  change.push_back(temp);
}

void JSONdata::setChgPer(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  changePercent.push_back(temp);
}

void JSONdata::setVmap(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  vmap.push_back(temp);
}

void JSONdata::setChgOvrTime(const double &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  changeOverTime.push_back(temp);
}

void JSONdata::setDate(const std::string &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  date.push_back(temp);
}

void JSONdata::setLabel(const std::string &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  label.push_back(temp);
}

void JSONdata::setVol(const long long &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  volume.push_back(temp);
}

void JSONdata::setUnAdjVol(const long long &temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  unadjustedVolume.push_back(temp);
}

std::vector<double> JSONdata::getOpen() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return open;
}

std::vector<double> JSONdata::getHigh() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return high;
}

std::vector<double> JSONdata::getLow() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return low;
}

std::vector<double> JSONdata::getClose() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return close;
}

std::vector<double> JSONdata::getChange() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return change;
}

std::vector<double> JSONdata::getChgPer() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return changePercent;
}

std::vector<double> JSONdata::getVmap() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return vmap;
}

std::vector<double> JSONdata::getChgOvrTime() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return changeOverTime;
}

std::vector<std::string> JSONdata::getDate() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return date;
}

std::vector<std::string> JSONdata::getLabel() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return label;
}

std::vector<long long> JSONdata::getVol() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return volume;
}

std::vector<long long> JSONdata::getUnAdjVol() const
{
  std::lock_guard<std::mutex> guard(_mtx);
  return unadjustedVolume;
}

void JSONdata::parseIEXdata(const Json::Value &IEXdata)
{
        assert(!IEXdata.empty());
        assert(isEmpty());
        int i = 0;

        //Step through JSON file until the end is reached
        while(i < IEXdata.size()) {
                //Parse the JSON data into the struct
                open.push_back(IEXdata[i]["open"].asDouble());
                high.push_back(IEXdata[i]["high"].asDouble());
                low.push_back(IEXdata[i]["low"].asDouble());
                close.push_back(IEXdata[i]["close"].asDouble());
                volume.push_back(IEXdata[i]["volume"].asInt64());
                unadjustedVolume.push_back(IEXdata[i]["unadjustedVolume"].asInt64());
                change.push_back(IEXdata[i]["change"].asDouble());
                changePercent.push_back(IEXdata[i]["changePercent"].asDouble());
                vmap.push_back(IEXdata[i]["vmap"].asDouble());
                changeOverTime.push_back(IEXdata[i]["changeOverTime"].asDouble());
                date.push_back(IEXdata[i]["date"].asString());
                label.push_back(IEXdata[i]["label"].asString());
                i++;
        }
}

void JSONdata::clearJSONstruct(){
        open.clear();
        high.clear();
        low.clear();
        close.clear();
        change.clear();
        changePercent.clear();
        changePercent.clear();
        vmap.clear();
        changeOverTime.clear();
        date.clear();
        label.clear();
        volume.clear();
        unadjustedVolume.clear();
}

bool JSONdata::isEmpty() const
{
        if(!open.empty())
                return false;

        else if(!high.empty())
                return false;

        else if(!low.empty())
                return false;

        else if(!close.empty())
                return false;

        else if(!change.empty())
                return false;

        else if(!changePercent.empty())
                return false;

        else if(!vmap.empty())
                return false;

        else if(!changeOverTime.empty())
                return false;

        else if(!date.empty())
                return false;

        else if(!label.empty())
                return false;

        else if(!volume.empty())
                return false;

        else if(!unadjustedVolume.empty())
                return false;

        else
                return true;
}
