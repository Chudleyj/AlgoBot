#ifndef JSONdata_h
#define JSONdata_h

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <json/json.h>

//Stores data points fetched from IEX API JSON file
//One struct per JSON entry
class JSONdata {
        std::vector <double> open, high, low, close, change, changePercent, vmap, changeOverTime;
        std::vector <std::string> date, label;
        std::vector <long long> volume, unadjustedVolume;

      public:
        void setOpen(const double &);
        void setHigh(const double &);
        void setLow(const double &);
        void setClose(const double &);
        void setChange(const double &);
        void setChgPer(const double &);
        void setVmap(const double &);
        void setChgOvrTime(const double &);

        void setDate(const std::string &);
        void setLabel(const std::string &);

        void setVol(const long long &);
        void setUnAdjVol(const long long &);

        std::vector<double> getOpen() const;
        std::vector<double> getHigh() const;
        std::vector<double> getLow() const;
        std::vector<double> getClose() const;
        std::vector<double> getChange() const;
        std::vector<double> getChgPer() const;
        std::vector<double> getVmap() const;
        std::vector<double> getChgOvrTime() const;

        std::vector<std::string> getDate() const;
        std::vector<std::string> getLabel() const;

        std::vector<long long> getVol() const;
        std::vector<long long> getUnAdjVol() const;


        bool isEmpty() const;
        void clearJSONstruct();
        void parseIEXdata(const Json::Value &);

};

#endif
