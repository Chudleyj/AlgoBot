#include "JSONdata.h"

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
        if(open.empty())
                return true;

        else if(high.empty())
                return true;

        else if(low.empty())
                return true;

        else if(close.empty())
                return true;

        else if(change.empty())
                return true;

        else if(changePercent.empty())
                return true;

        else if(vmap.empty())
                return true;

        else if(changeOverTime.empty())
                return true;

        else if(date.empty())
                return true;

        else if(label.empty())
                return true;

        else if(volume.empty())
                return true;

        else if(unadjustedVolume.empty())
                return true;

        else
                return false;
}
