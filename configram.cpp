/*! \file configram.cpp
 configram.cpp

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
    if ((fast_memory.compare(DEFAULTFASTMEMORY)==0)||(chip_memory.compare("4096")==0)||(chip_memory.compare("8192")==0)){return "";}
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
    //se mi arriva un parametro che non so/devo gestire io non faccio nulla
    //se mi arriva un mio parametro verifico sia valido, se no setto il DEFAULT
    //in questo modo se qualcuno salva la config, manomette (o modifica erroneamente) il file, io garantisco sia una configurazione valida
    if(parameter.compare("chip_memory")==0){
        if ((value.compare("512")==0)||(value.compare("1024")==0)||(value.compare("2048")==0)||(value.compare("4096")==0)||(value.compare("8192")==0)){
            chip_memory=value;}
        else{
            chip_memory=DEFAULTCHIPMEMORY;
        }
    } else if(parameter.compare("slow_memory")==0){
        if ((value.compare("NONE")==0)||(value.compare("512")==0)||(value.compare("1024")==0)||(value.compare("1792")==0)){
            slow_memory=value;}
        else{
            slow_memory=DEFAULTSLOWMEMORY;
        }
    } else if(parameter.compare("fast_memory")==0){
        if ((value.compare("NONE")==0)||(value.compare("1024")==0)||(value.compare("2048")==0)||(value.compare("4096")==0)||(value.compare("8192")==0)){
            fast_memory=value;}
        else{
            fast_memory=DEFAULTFASTMEMORY;
        }
    } else if(parameter.compare("zorro_iii_memory")==0){
        if ((value.compare("NONE")==0)||(value.compare("1024")==0)||(value.compare("2048")==0)||(value.compare("4096")==0)||(value.compare("8192")==0)||(value.compare("16384")==0)||(value.compare("32768")==0)||(value.compare("65536")==0)||(value.compare("131072")==0)||(value.compare("262144")==0)){
            zorro_iii_memory=value;}
        else{
            zorro_iii_memory=DEFAULTZORROIIIMEMORY;
        }
    }
}

void ConfigRam::setToDefaultConfiguration()
{
    chip_memory=DEFAULTCHIPMEMORY;
    slow_memory=DEFAULTSLOWMEMORY;
    fast_memory=DEFAULTFASTMEMORY;
    zorro_iii_memory=DEFAULTZORROIIIMEMORY;

}
