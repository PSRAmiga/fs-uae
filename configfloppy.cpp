/*! \file configfloppy.cpp
 configfloppy.cpp

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 Written by Riva Alessandro Mario, alessandromario.riva@gmail.com
 and Sanvito Davide, dsanvito90@gmail.com. */
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
    if (position>=(int)floppy_image.size()){return "";}
    return floppy_image.at(position);
}

void ConfigFloppy::pushBackFloppyImage(string s)
{
    floppy_image.push_back(s);
}

void ConfigFloppy::eraseFloppyImageAt(int position)
{
    if (position>=(int)floppy_image.size()){return;}
    floppy_image.erase(floppy_image.begin()+ position);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool static isNumber(string s){
    istringstream buffer(s);
    int intValue;
    buffer >> intValue;
    //la conversione ritorna 0 se non è un numero. Devo stare attento al caso in cui la stringa sia proprio "0"
    if (intValue==0 && s.compare("0")==0) return true;
    return intValue!=0;
}

int static strToInt(string s){
    istringstream buffer(s);
    int intValue;
    buffer >> intValue;
    return intValue;
}
int ConfigFloppy::setParameter(string parameter, string value)
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
        if (isNumber(value) && strToInt(value)>=0 && strToInt(value)<=100){
            floppy_drive_volume=value;}
        else{
            floppy_drive_volume=DEFAULTFLOPPYDRIVEVOLUME;
            return -1;
        }
    } else if(parameter.compare("floppy_drive_speed")==0){

        if ((value.compare("0")==0)||(value.compare("100")==0)||(value.compare("200")==0)||(value.compare("300")==0)||(value.compare("400")==0)||(value.compare("500")==0)||(value.compare("600")==0)||(value.compare("700")==0)||(value.compare("800")==0)||(value.compare("900")==0)||(value.compare("1000")==0)||(value.compare("1100")==0)||(value.compare("1200")==0)){
            floppy_drive_speed=value;
        }
        else{
            floppy_drive_speed=DEFAULTFLOPPYDRIVESPEED;
            return -1;
        }

    } else if((parameter.substr(0,parameter.length()-1).compare("floppy_image_")==0 || parameter.substr(0,parameter.length()-2).compare("floppy_image_")==0)&& floppy_image.size()<20){
        floppy_image.push_back(value);
    }
    return 0;
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

bool ConfigFloppy::hasParameter(string parameterName)
{
    return (parameterName.substr(0,parameterName.length()-1).compare("floppy_drive_")==0)||(parameterName.substr(0,parameterName.length()-1).compare("floppy_image_")==0)||(parameterName.substr(0,parameterName.length()-2).compare("floppy_image_")==0)||(parameterName.compare("floppy_drive_volume")==0)||(parameterName.compare("floppy_drive_speed")==0);
}
