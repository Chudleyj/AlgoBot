#include "main.h"

/* As requested by some folks struggling to understand this code,
   The general flow of this entire program is as follows:

   Create objects

   Fetch latest stock data from IEX::stocks::chartRange as a Json::value object

   Parse this data into a JSONdata object (see JSONdata files for more info) via
   parseIEXdata function.

   At this point, the program now has its' first set of data points ready to be
   used by TechnicalAnalysis member functions. This is where the threads come
   into play.

   First, create a thread (t1) that will call AcquireIEXdata, passing
   JSONdata obj (threadData) by reference (std::ref) to the function as well as
   copies (std::move) of 'appl' (Apple's stock symbol which I am using for
   testing this program) and '1d', 1d tells chartRange to return minute by
   minute data (hence why all data from chartRange ends up in a variable called
   minData). Thread T1 will gather a new set of data for minData obj, while the
   other 9 threads use the current set of minData for calculations.

   Each thread, T2 through T10, calls a different member function
   of class TechnicalAnalysis that will calculate one of the TechnicalIndicators
   inside the TechnicalIndicators struct (part of the TechnicalAnalysis class)

   After all threads have been called, the program then waits for all of them to
   finish running (join() functions).
   Once they finish running, the objects that are full of old data are cleared,
   and then the object filled with new data by thread T1 is copied into the
   minData object. T1's threadData obj is then cleared, and the whole thread
   process repeats.

   NOTE: In the future, BEFORE the TIobj is cleared that data will be passed
   into algorithms to make buy, sell, or hold decisions on the stock market. */

int main()
{
        //Create objects
        JSONdata minData, threadData, test;
        TechnicalAnalysis TIobj;

        Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d"); //Pull stock data from IEX API
        minData.parseIEXdata(IEXdata); //Move data from IEXdata into minData

        while(1){
                //Use a seperate thread to update data for next calcs while current calcs are done.
                std::thread t1(AcquireIEXdata, std::ref(threadData),std::move("aapl"), std::move("1d"));

                //Put all calcs onto threads, they all use thread safe methods for TIobj
                std::thread t2(&TechnicalAnalysis::calcRSI,TIobj,std::ref(minData));
                std::thread t3(&TechnicalAnalysis::calcFiftySMA,TIobj,std::ref(minData));
                std::thread t4(&TechnicalAnalysis::calcHundredSMA,TIobj,std::ref(minData));
                std::thread t5(&TechnicalAnalysis::calcHundFiftySMA,TIobj,std::ref(minData));
                std::thread t6(&TechnicalAnalysis::calcTwoHundSMA,TIobj,std::ref(minData));
                std::thread t7(&TechnicalAnalysis::calcFiftyEMA,TIobj,std::ref(minData));
                std::thread t8(&TechnicalAnalysis::calcHundredEMA,TIobj,std::ref(minData));
                std::thread t9(&TechnicalAnalysis::calcHundFiftyEMA,TIobj,std::ref(minData));
                std::thread t10(&TechnicalAnalysis::calcTwoHundEMA,TIobj,std::ref(minData));

                t1.join(); //Rejoin main thread, adding new data for next calcs
                t2.join(); //Rejoin all threads to clear data before next calcs
                t3.join();
                t4.join();
                t5.join();
                t6.join();
                t7.join();
                t8.join();
                t9.join();
                t10.join();

                //Clean up for reassignment
                TIobj.clearTAobj();
                minData.clearJSONstruct();

                //Using var threadData here to temp store minData avoids deadlock.
                minData = threadData;
                test = threadData;

                //Clean up for reassignment
                threadData.clearJSONstruct();
        }

        return 0;
}

/* THREAD T1 USES THIS
   This function essentially does the same thing as the lines:
   Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d");
   minData.parseIEXdata(IEXdata);
   from the main function, but this needs to be
   in its own function this time because a thread is calling it, and I do not
   want to overwrtie minData beforte TIobj is done with the data that is in
   minData currently */
void AcquireIEXdata(JSONdata &dataToFormat, const std::string &stock, const std::string &range)
{
        assert(dataToFormat.isEmpty() && !range.empty() && !stock.empty());

        Json::Value IEXdata = IEX::stocks::chartRange(stock, range);
        dataToFormat.parseIEXdata(IEXdata);
}
