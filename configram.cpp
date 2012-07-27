#include "configram.h"

const string DEFAULTCHIPMEMORY = "512";
const string DEFAULTSLOWMEMORY = "NONE";
const string DEFAULTFASTMEMORY = "NONE";
const string DEFAULTZORROIIIMEMORY = "NONE";

ConfigRam::ConfigRam()
{
     setToDefaultConfiguration();
}

string ConfigRam::getChipMemoryConfigString()
{
    if (chip_memory.compare(DEFAULTCHIPMEMORY)==0){return "";}
    else {return "chip_memory = " + chip_memory;}
}

string ConfigRam::getChipMemoryString()
{
    return chip_memory;
}
//////////////////////////////////////////////////////////////////////////////////////////
string ConfigRam::getSlowMemoryConfigString()
{
    if (slow_memory.compare(DEFAULTSLOWMEMORY)==0){return "";}
    else {return "slow_memory = " + slow_memory;}
}

string ConfigRam::getSlowMemoryString()
{
    return slow_memory;
}
//////////////////////////////////////////////////////////////////////////////////////////
string ConfigRam::getFastMemoryConfigString()
{
    if (fast_memory.compare(DEFAULTFASTMEMORY)==0){return "";}
    else {return "fast_memory = " + fast_memory;}
}

string ConfigRam::getFastMemoryString()
{
    return fast_memory;
}
//////////////////////////////////////////////////////////////////////////////////////////
string ConfigRam::getZorro3ConfigString()
{
    if (zorro_iii_memory.compare(DEFAULTZORROIIIMEMORY)==0){return "";}
    else {return "zorro_iii_memory = " + zorro_iii_memory;}
}

string ConfigRam::getZorro3String()
{
    return zorro_iii_memory;
}
//////////////////////////////////////////////////////////////////////////////////////////

void ConfigRam::setParameter(string parameter, string value)
{
    if(parameter.compare("chip_memory")==0){
        chip_memory=value;
    } else if(parameter.compare("slow_memory")==0){
        slow_memory=value;
    } else if(parameter.compare("fast_memory")==0){
        fast_memory=value;
    } else if(parameter.compare("zorro_iii_memory")==0){
        zorro_iii_memory=value;
    }
}

void ConfigRam::setToDefaultConfiguration()
{
    chip_memory=DEFAULTCHIPMEMORY;
    slow_memory=DEFAULTSLOWMEMORY;
    fast_memory=DEFAULTFASTMEMORY;
    zorro_iii_memory=DEFAULTZORROIIIMEMORY;

}
