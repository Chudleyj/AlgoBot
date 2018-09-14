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
