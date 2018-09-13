#ifndef JSONdata_h
#define JSONdata_h

#include <string>
#include <vector>

//Stores data points fetched from IEX API JSON file
//One struct per JSON entry
struct JSONdata {
        std::vector <double> open, high, low, close, change, changePercent, vmap, changeOverTime;
        std::vector <std::string> date, label;
        std::vector <long long> volume, unadjustedVolume;
        bool isEmpty() const;
        void clearJSONstruct();
};

#endif
