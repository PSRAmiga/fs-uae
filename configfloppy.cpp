#include "configfloppy.h"
#include <sstream>
#include <string>

const string DEFAULTFLOPPYDRIVE = "";
const string DEFAULTFLOPPYDRIVEVOLUME = "20";
const string DEFAULTFLOPPYDRIVESPEED = "100";

ConfigFloppy::ConfigFloppy()
{
    setToDefaultConfiguration();
}

string ConfigFloppy::getFloppyDriveConfigStringAt(int i)
{
    string iString=static_cast<ostringstream*>( &(ostringstream() << i) )->str();
    if (i<0 || i>3){return "";}
    if (floppy_drive[i].compare(DEFAULTFLOPPYDRIVE)==0){return "";}
    else {return "floppy_drive_" + iString + " = " + floppy_drive[i];}
}

string ConfigFloppy::getFloppyDriveStringAt(int i)
{
    if (i<0 || i>3){return "";}
    return floppy_drive[i];
}

string ConfigFloppy::getFloppyDriveVolumeConfigString()
{
    if (floppy_drive_volume.compare(DEFAULTFLOPPYDRIVEVOLUME)==0){return "";}
    else {return "floppy_drive_volume = " + floppy_drive_volume;}
}

string ConfigFloppy::getFloppyDriveVolumeString()
{
    return floppy_drive_volume;
}

string ConfigFloppy::getFloppyDriveSpeedConfigString()
{
    if (floppy_drive_speed.compare(DEFAULTFLOPPYDRIVESPEED)==0){return "";}
    else {return "floppy_drive_speed = " + floppy_drive_speed;}
}

string ConfigFloppy::getFloppyDriveSpeedString()
{
    return floppy_drive_speed;
}

int ConfigFloppy::getFloppyImageSize()
{
    return floppy_image.size();
}

string ConfigFloppy::getFloppyImageAt(int position)
{
    if (position>=floppy_image.size()){return "";}
    return floppy_image.at(position);
}

void ConfigFloppy::pushBackFloppyImage(string s)
{
    floppy_image.push_back(s);
}

void ConfigFloppy::eraseFloppyImageAt(int position)
{
    if (position>=floppy_image.size()){return;}
    floppy_image.erase(floppy_image.begin()+ position);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigFloppy::setParameter(string parameter, string value)
{
    if(parameter.compare("floppy_drive_0")==0){
        floppy_drive[0]=value;
    } else if(parameter.compare("floppy_drive_1")==0){
        floppy_drive[1]=value;
    } else if(parameter.compare("floppy_drive_2")==0){
        floppy_drive[2]=value;
    } else if(parameter.compare("floppy_drive_3")==0){
        floppy_drive[3]=value;
    } else if(parameter.compare("floppy_drive_volume")==0){
        istringstream buffer(value);
        int intValue;
        buffer >> intValue;
        //questa conversione ritorna zero se ci sono lettere nella stringa, quindi devo distinguere uno zero vero da uno falso
        if (value.compare("0")==0 || (intValue>=0 && intValue<=100)){
            floppy_drive_volume=value;}
        else{
            floppy_drive_volume=DEFAULTFLOPPYDRIVEVOLUME;
        }
    } else if(parameter.compare("floppy_drive_speed")==0){

        if ((value.compare("0")==0)||(value.compare("100")==0)||(value.compare("200")==0)||(value.compare("300")==0)||(value.compare("400")==0)||(value.compare("500")==0)||(value.compare("600")==0)||(value.compare("700")==0)||(value.compare("800")==0)||(value.compare("900")==0)||(value.compare("1000")==0)||(value.compare("1100")==0)||(value.compare("1200")==0)){
            floppy_drive_speed=value;
        }
        else{
            floppy_drive_speed=DEFAULTFLOPPYDRIVESPEED;
        }

    } else if((parameter.substr(0,parameter.length()-1).compare("floppy_image_")==0 || parameter.substr(0,parameter.length()-2).compare("floppy_image_")==0)&& floppy_image.size()<20){
        floppy_image.push_back(value);
    }
}

void ConfigFloppy::setToDefaultConfiguration()
{
    //set options to default values

    for(int i=0;i<4;i++){
        floppy_drive[i]=DEFAULTFLOPPYDRIVE;
    }
    floppy_drive_volume=DEFAULTFLOPPYDRIVEVOLUME;
    floppy_drive_speed=DEFAULTFLOPPYDRIVESPEED;
    floppy_image.clear();


}
