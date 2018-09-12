#ifndef main_h
#define main_h


#include <vector>
#include "TechnicalAnalysis.h"
#include "JSONdata.h"
#include "IEX.h"
#include <string>
#include <iostream>
#include <json/json.h>
#include <curl/curl.h>

void parseIEXdata(const Json::Value &, JSONdata &);

#endif
