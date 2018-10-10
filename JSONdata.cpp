#include "JSONdata.h"

std::mutex _mtx; //For std::lock_guard

/* Access functions are used to call either the get or set for a
  member variable, depending on what is past to them
  (hence the boost::optionals)
  Using boost::optional over std::optional so I can pass by reference
  The point of using these instead of directly calling get or set functions
  is to ensure thread safety. This way, no function can look at or set
  a var while another thread has the lock. */

//Temp = varible to temporarily hold value to be set via set functions
//Copy = variable that will get a copy of whatever is returned by the get func
void JSONdata::accessUnAdjVol(boost::optional<std::vector<long long>&> copy,
                              boost::optional<long long> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setUnAdjVol(*temp);
  else if(copy)
    getUnAdjVol(*copy);
}

void JSONdata::accessVol(boost::optional<std::vector<long long>&> copy,
                         boost::optional<long long> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setVol(*temp);
  else if(copy)
    getVol(*copy);
}

void JSONdata::accessLabel(boost::optional<std::vector<std::string>&> copy,
                           boost::optional<std::string> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setLabel(*temp);
  else if(copy)
    getLabel(*copy);
}

void JSONdata::accessDate(boost::optional<std::vector<std::string>&> copy,
                          boost::optional<std::string> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setDate(*temp);
  else if(copy)
    getDate(*copy);
}

void JSONdata::accessChgOvrTime(boost::optional<std::vector<double>&> copy,
                                boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setChgOvrTime(*temp);
  else if(copy)
    getChgOvrTime(*copy);
}

void JSONdata::accessVmap(boost::optional<std::vector<double>&> copy,
                          boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setVmap(*temp);
  else if(copy)
    getVmap(*copy);
}

void JSONdata::accessChgPer(boost::optional<std::vector<double>&> copy,
                            boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setChgPer(*temp);
  else if(copy)
    getChgPer(*copy);
}

void JSONdata::accessChange(boost::optional<std::vector<double>&> copy,
                            boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setChange(*temp);
  else if(copy)
    getChange(*copy);
}

void JSONdata::accessClose(boost::optional<std::vector<double>&> copy,
                           boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setClose(*temp);
  else if(copy)
    getClose(*copy);
}

void JSONdata::accessLow(boost::optional<std::vector<double>&> copy,
                         boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setLow(*temp);
  else if(copy)
    getLow(*copy);
}

void JSONdata::accessHigh(boost::optional<std::vector<double>&> copy,
                          boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setHigh(*temp);
  else if(copy)
    getHigh(*copy);
}

void JSONdata::accessOpen(boost::optional<std::vector<double>&> copy,
                          boost::optional<double> temp)
{
  std::lock_guard<std::mutex> guard(_mtx);
  if(temp)
    setOpen(*temp);
  else if(copy)
    getOpen(*copy);
}

/* Here, set functions take in a value (temp), and push it back to their
corresponding member variable vector */
void JSONdata::setOpen(const double &temp)
{
        pricingData.open.push_back(temp);
}

void JSONdata::setHigh(const double &temp)
{
        pricingData.high.push_back(temp);
}

void JSONdata::setLow(const double &temp)
{
        pricingData.low.push_back(temp);
}

void JSONdata::setClose(const double &temp)
{
        pricingData.close.push_back(temp);
}

void JSONdata::setChange(const double &temp)
{
        pricingData.change.push_back(temp);
}

void JSONdata::setChgPer(const double &temp)
{
        pricingData.changePercent.push_back(temp);
}

void JSONdata::setVmap(const double &temp)
{
        pricingData.vmap.push_back(temp);
}

void JSONdata::setChgOvrTime(const double &temp)
{
        pricingData.changeOverTime.push_back(temp);
}

void JSONdata::setDate(const std::string &temp)
{
        pricingData.date.push_back(temp);
}

void JSONdata::setLabel(const std::string &temp)
{
        pricingData.label.push_back(temp);
}

void JSONdata::setVol(const long long &temp)
{
        pricingData.volume.push_back(temp);
}

void JSONdata::setUnAdjVol(const long long &temp)
{
        pricingData.unadjustedVolume.push_back(temp);
}

/* Get functions take in an vector, and make it a copy of whatever vector
   the specific get function is for. These can be void because the vector
   is passed by reference
   These functions are const because we never modify any part of the class,
   and a const function will ensure this */
void JSONdata::getOpen(std::vector <double> &copy) const
{
        copy = pricingData.open;
}

void JSONdata::getHigh(std::vector <double> &copy) const
{

        copy = pricingData.high;
}

void JSONdata::getLow(std::vector <double> &copy) const
{

        copy = pricingData.low;
}

void JSONdata::getClose(std::vector <double> &copy) const
{

        copy = pricingData.close;
}

void JSONdata::getChange(std::vector <double> &copy) const
{

        copy = pricingData.change;
}

void JSONdata::getChgPer(std::vector <double> &copy) const
{

        copy = pricingData.changePercent;
}

void JSONdata::getVmap(std::vector <double> &copy) const
{

        copy = pricingData.vmap;
}

void JSONdata::getChgOvrTime(std::vector <double> &copy) const
{

        copy = pricingData.changeOverTime;
}

void JSONdata::getDate(std::vector<std::string> &copy) const
{

        copy = pricingData.date;
}

void JSONdata::getLabel(std::vector<std::string> &copy) const
{

        copy = pricingData.label;
}

void JSONdata::getVol(std::vector<long long> &copy) const
{

        copy = pricingData.volume;
}

void JSONdata::getUnAdjVol(std::vector<long long> &copy) const
{
        copy = pricingData.unadjustedVolume;
}

/* This function will take the data fetched by the IEX::stocks::chartRange()
   function. It will then parse that data into its corresponding vector inside
   the priceData struct */
void JSONdata::parseIEXdata(const Json::Value &IEXdata)
{
        assert(!IEXdata.empty() && isEmpty());

        int i = 0;
        double temp;
        long long temp_lng;
        std::string temp_str;

        //Step through JSON file until the end is reached
        while(i < IEXdata.size()) {
                //Parse the JSON data into the struct
                temp = IEXdata[i]["open"].asDouble();
                accessOpen(boost::none, temp);

                temp = IEXdata[i]["low"].asDouble();
                accessLow(boost::none, temp);

                temp = IEXdata[i]["close"].asDouble();
                accessClose(boost::none, temp);

                temp = IEXdata[i]["change"].asDouble();
                accessChange(boost::none, temp);

                temp = IEXdata[i]["changePercent"].asDouble();
                accessChgPer(boost::none, temp);

                temp = IEXdata[i]["vmap"].asDouble();
                accessVmap(boost::none, temp);

                temp = IEXdata[i]["changeOverTime"].asDouble();
                accessChgOvrTime(boost::none, temp);

                temp_lng = IEXdata[i]["volume"].asInt64();
                accessVol(boost::none, temp_lng);

                temp_lng = IEXdata[i]["unadjustedVolume"].asInt64();
                accessUnAdjVol(boost::none, temp_lng);

                temp_str = IEXdata[i]["date"].asString();
                accessDate(boost::none, temp_str);

                temp_str = IEXdata[i]["date"].asString();
                accessLabel(boost::none,temp_str);
                i++;
        }
}

/* Clear all the data out of the vectors
   This is done because the data needs to be always as up to date as possible
   So, the data is gathered once, passed off to the Tech Analysis class for
   calculations, and then cleared and replaced */
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

/* This function is used by some assert() statements.
   There are times where the program will produce horrible results
   if data is empty, this allows the program to use asserts to error check
   (The assert should never crash the program, but this lets me be sure)
   This is a const function in order to ensure that none of calling object
   is modified */
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
