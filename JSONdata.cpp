#include "JSONdata.h"

std::mutex _mtx;

void JSONdata::setOpen(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.open.push_back(temp);
}

void JSONdata::setHigh(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.high.push_back(temp);
}

void JSONdata::setLow(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.low.push_back(temp);
}

void JSONdata::setClose(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.close.push_back(temp);
}

void JSONdata::setChange(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.change.push_back(temp);
}

void JSONdata::setChgPer(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.changePercent.push_back(temp);
}

void JSONdata::setVmap(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.vmap.push_back(temp);
}

void JSONdata::setChgOvrTime(const double &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.changeOverTime.push_back(temp);
}

void JSONdata::setDate(const std::string &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.date.push_back(temp);
}

void JSONdata::setLabel(const std::string &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.label.push_back(temp);
}

void JSONdata::setVol(const long long &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.volume.push_back(temp);
}

void JSONdata::setUnAdjVol(const long long &temp)
{
        std::lock_guard<std::mutex> guard(_mtx);
        pricingData.unadjustedVolume.push_back(temp);
}

std::vector<double> JSONdata::getOpen() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.open;
}

std::vector<double> JSONdata::getHigh() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.high;
}

std::vector<double> JSONdata::getLow() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.low;
}

std::vector<double> JSONdata::getClose() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.close;
}

std::vector<double> JSONdata::getChange() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.change;
}

std::vector<double> JSONdata::getChgPer() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.changePercent;
}

std::vector<double> JSONdata::getVmap() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.vmap;
}

std::vector<double> JSONdata::getChgOvrTime() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.changeOverTime;
}

std::vector<std::string> JSONdata::getDate() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.date;
}

std::vector<std::string> JSONdata::getLabel() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.label;
}

std::vector<long long> JSONdata::getVol() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.volume;
}

std::vector<long long> JSONdata::getUnAdjVol() const
{
        std::lock_guard<std::mutex> guard(_mtx);
        return pricingData.unadjustedVolume;
}

void JSONdata::parseIEXdata(const Json::Value &IEXdata)
{
        assert(!IEXdata.empty());
        assert(isEmpty());
        int i = 0;

        //Step through JSON file until the end is reached
        while(i < IEXdata.size()) {
                //Parse the JSON data into the struct
                setOpen(IEXdata[i]["open"].asDouble());
                setHigh(IEXdata[i]["high"].asDouble());
                setLow(IEXdata[i]["low"].asDouble());
                setClose(IEXdata[i]["close"].asDouble());
                setVol(IEXdata[i]["volume"].asInt64());
                setUnAdjVol(IEXdata[i]["unadjustedVolume"].asInt64());
                setChange(IEXdata[i]["change"].asDouble());
                setChgPer(IEXdata[i]["changePercent"].asDouble());
                setVmap(IEXdata[i]["vmap"].asDouble());
                setChgOvrTime(IEXdata[i]["changeOverTime"].asDouble());
                setDate(IEXdata[i]["date"].asString());
                setLabel(IEXdata[i]["label"].asString());

                i++;
        }
}

void JSONdata::clearJSONstruct(){
        pricingData.open.clear();
        pricingData.high.clear();
        pricingData.low.clear();
        pricingData.close.clear();
        pricingData.change.clear();
        pricingData.changePercent.clear();
        pricingData.changePercent.clear();
        pricingData.vmap.clear();
        pricingData.changeOverTime.clear();
        pricingData.date.clear();
        pricingData.label.clear();
        pricingData.volume.clear();
        pricingData.unadjustedVolume.clear();
}

bool JSONdata::isEmpty() const
{
        if(!pricingData.open.empty())
                return false;

        else if(!pricingData.high.empty())
                return false;

        else if(!pricingData.low.empty())
                return false;

        else if(!pricingData.close.empty())
                return false;

        else if(!pricingData.change.empty())
                return false;

        else if(!pricingData.changePercent.empty())
                return false;

        else if(!pricingData.vmap.empty())
                return false;

        else if(!pricingData.changeOverTime.empty())
                return false;

        else if(!pricingData.date.empty())
                return false;

        else if(!pricingData.label.empty())
                return false;

        else if(!pricingData.volume.empty())
                return false;

        else if(!pricingData.unadjustedVolume.empty())
                return false;

        else
                return true;
}
