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
#include <thread>

void AcquireIEXdata(JSONdata &, const std::string &, const std::string &);


#endif
