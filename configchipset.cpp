#include "configchipset.h"

const string DEFAULTACCURACY = "1";
const string DEFAULTNTSCMODE = "0";
const string DEFAULTAMIGAMODEL = "A500";
const string DEFAULTKICKSTARTFILE = "";
const string DEFAULTKICKSTARTEXTFILE = "";

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

string ConfigChipset::getAmigaModelConfigString()
{
    if (amiga_model.compare(DEFAULTAMIGAMODEL)==0){return "";}
    else {return "amiga_model = " + amiga_model;}
}

string ConfigChipset::getAmigaModelString()
{
    return amiga_model;
}

string ConfigChipset::getKickstartFileConfigString()
{
    if (kickstart_file.compare(DEFAULTKICKSTARTFILE)==0){return "";}
    else {return "kickstart_file = " + kickstart_file;}
}

string ConfigChipset::getKickstartFileString()
{
    return kickstart_file;
}

string ConfigChipset::getKickstartExtFileConfigString()
{
    if (kickstart_ext_file.compare(DEFAULTKICKSTARTEXTFILE)==0){return "";}
    else {return "kickstart_ext_file = " + kickstart_ext_file;}
}

string ConfigChipset::getKickstartExtFileString()
{
    return kickstart_ext_file;
}

void ConfigChipset::setParameter(string parameter, string value)
{
    if(parameter.compare("accuracy")==0){
        accuracy=value;
    } else if(parameter.compare("ntsc_mode")==0){
        ntsc_mode=value;
    } else if(parameter.compare("amiga_model")==0){
        amiga_model=value;
    } else if(parameter.compare("kickstart_file")==0){
        kickstart_file=value;
    } else if(parameter.compare("kickstart_ext_file")==0){
        kickstart_ext_file=value;
    }
}

void ConfigChipset::setToDefaultConfiguration()
{
    //set options to default values
    amiga_model=DEFAULTAMIGAMODEL;
    accuracy=DEFAULTACCURACY;
    kickstart_file=DEFAULTKICKSTARTFILE;
    kickstart_ext_file=DEFAULTKICKSTARTEXTFILE;
    ntsc_mode=DEFAULTNTSCMODE;
}
