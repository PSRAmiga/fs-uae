#include "configchipset.h"
#include "amiga.h"

const string DEFAULTACCURACY = "1";
const string DEFAULTNTSCMODE = "0";


ConfigChipset::ConfigChipset()
{
    setToDefaultConfiguration();
}

//NB se il valore è quello di default devo ritornare la stringa vuota almeno so che non devo salvarlo nella config che tanto è un inutile spreco
string ConfigChipset::getAccuracyConfigString()
{
    if (accuracy.compare(DEFAULTACCURACY)==0){return "";}
    else {return "accuracy = " + accuracy;}
}

string ConfigChipset::getAccuracyString()
{
    return accuracy;
}

string ConfigChipset::getNTSCModeConfigString()
{
    if (ntsc_mode.compare(DEFAULTNTSCMODE)==0){return "";}
    else {return "ntsc_mode = 1";}
}

string ConfigChipset::getNTSCModeString()
{
    return ntsc_mode;
}

void ConfigChipset::setParameter(string parameter, string value)
{
    if(parameter.compare("accuracy")==0){
        accuracy=value;
    } else  if(parameter.compare("ntsc_mode")==0){
        ntsc_mode=value;
    }

    //else if (parameter.compare("......  con gli altri parametri di quetsa area di configurazione
}

void ConfigChipset::setToDefaultConfiguration()
{
    //set options to default values
    amiga_model="A500";
    accuracy=DEFAULTACCURACY;
    kickstart_file="";
    kickstart_ext_file="";
    ntsc_mode=DEFAULTNTSCMODE;
}
