#include "configchipset.h"
const string DEFAULTACCURACY = "1";


ConfigChipset::ConfigChipset()
{
    //set options to default values
    amiga_model="A500";
    kickstart_file="";
    kickstart_ext_file="";
    accuracy=DEFAULTACCURACY;
    ntsc_mode="0";
}

void ConfigChipset::setAccuracy(bool least, bool normal, bool most)
{
    if (least+normal+most!=1){
        accuracy=DEFAULTACCURACY;
    }

    if (least==true){accuracy="-1";}
    else if (normal==true){accuracy="0";}
    else {accuracy="1";}
}

//NB se il valore è quello di default devo ritornare la stringa vuota almeno so che non devo salvarlo nella config che tanto è un inutile spreco
string ConfigChipset::getAccuracyString()
{
    if (accuracy.compare(DEFAULTACCURACY)==0){return "";}
    else {return "accuracy = " + accuracy;}
}
