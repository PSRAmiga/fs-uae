/*! \file configtheme.cpp
 configtheme.cpp

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
#include "configtheme.h"
#include <QRegExp>

const string DEFAULTTHEME="";
const string DEFAULTTHEMEFADECOLOR="#3c3b37";
const string DEFAULTTHEMEWALLCOLOR="#3c3b37";
const string DEFAULTTHEMEFLOORCOLOR1="#1d1d1b";
const string DEFAULTTHEMEFLOORCOLOR2="#111110";
const string DEFAULTTHEMEHEADINGCOLOR="#f68355";
const string DEFAULTTHEMEOVERLAYIMAGE="";

ConfigTheme::ConfigTheme()
{
    setToDefaultConfiguration();
}

string ConfigTheme::getThemeConfigString()
{
    if (theme.compare(DEFAULTTHEME)==0){return "";}
    else {return "theme = " + theme;}
}

string ConfigTheme::getThemeString()
{
    return theme;
}

string ConfigTheme::getFadeColorConfigString()
{
    if (theme_fade_color.compare(DEFAULTTHEMEFADECOLOR)==0){return "";}
    else {return "theme_fade_color = " + theme_fade_color;}
}

string ConfigTheme::getFadeColorString()
{
    return theme_fade_color;
}

string ConfigTheme::getWallColor1ConfigString()
{
    if (theme_wall_color_1.compare(DEFAULTTHEMEWALLCOLOR)==0){return "";}
    else {return "theme_wall_color_1 = " + theme_wall_color_1;}
}

string ConfigTheme::getWallColor1String()
{
    return theme_wall_color_1;
}

string ConfigTheme::getWallColor2ConfigString()
{
    if (theme_wall_color_2.compare(DEFAULTTHEMEWALLCOLOR)==0){return "";}
    else {return "theme_wall_color_2 = " + theme_wall_color_2;}
}

string ConfigTheme::getWallColor2String()
{
    return theme_wall_color_2;
}

string ConfigTheme::getFloorColor1ConfigString()
{
    if (theme_floor_color_1.compare(DEFAULTTHEMEFLOORCOLOR1)==0){return "";}
    else {return "theme_floor_color_1 = " + theme_floor_color_1;}
}

string ConfigTheme::getFloorColor1String()
{
    return theme_floor_color_1;
}

string ConfigTheme::getFloorColor2ConfigString()
{
    if (theme_floor_color_2.compare(DEFAULTTHEMEFLOORCOLOR2)==0){return "";}
    else {return "theme_floor_color_2 = " + theme_floor_color_2;}
}

string ConfigTheme::getFloorColor2String()
{
    return theme_floor_color_2;
}

string ConfigTheme::getHeadingColorConfigString()
{
    if (theme_heading_color.compare(DEFAULTTHEMEHEADINGCOLOR)==0){return "";}
    else {return "theme_heading_color = " + theme_heading_color;}
}

string ConfigTheme::getHeadingColorString()
{
    return theme_heading_color;
}

string ConfigTheme::getOverlayImageConfigString()
{
    if (theme_overlay_image.compare(DEFAULTTHEMEOVERLAYIMAGE)==0){return "";}
    else {return "theme_overlay_image = " + theme_overlay_image;}
}

string ConfigTheme::getOverlayImageString()
{
    return theme_overlay_image;
}

void ConfigTheme::setParameter(string parameter, string value)
{
    QRegExp rx("#[A-Fa-f0-9]{6}");
    if(parameter.compare("theme")==0){
        theme=value;
    } else if(parameter.compare("theme_fade_color")==0){
        if (rx.exactMatch(QString::fromStdString(value))){
            theme_fade_color=value;}
        else{
            theme_fade_color=DEFAULTTHEMEFADECOLOR;
        }
    } else if(parameter.compare("theme_wall_color_1")==0){
        if (rx.exactMatch(QString::fromStdString(value))){
            theme_wall_color_1=value;}
        else{
            theme_wall_color_1=DEFAULTTHEMEWALLCOLOR;
        }
    } else if(parameter.compare("theme_wall_color_2")==0){
        if (rx.exactMatch(QString::fromStdString(value))){
            theme_wall_color_2=value;}
        else{
            theme_wall_color_2=DEFAULTTHEMEWALLCOLOR;
        }
    } else if(parameter.compare("theme_floor_color_1")==0){
        if (rx.exactMatch(QString::fromStdString(value))){
            theme_floor_color_1=value;}
        else{
            theme_floor_color_1=DEFAULTTHEMEFLOORCOLOR1;
        }
    } else if(parameter.compare("theme_floor_color_2")==0){
        if (rx.exactMatch(QString::fromStdString(value))){
            theme_floor_color_2=value;}
        else{
            theme_floor_color_2=DEFAULTTHEMEFLOORCOLOR2;
        }
    } else if(parameter.compare("theme_heading_color")==0){
        if (rx.exactMatch(QString::fromStdString(value))){
            theme_heading_color=value;}
        else{
            theme_heading_color=DEFAULTTHEMEHEADINGCOLOR;
        }
    } else if(parameter.compare("theme_overlay_image")==0){
        theme_overlay_image=value;
    }
}

void ConfigTheme::setToDefaultConfiguration()
{
    theme=DEFAULTTHEME;
    theme_fade_color=DEFAULTTHEMEFADECOLOR;
    theme_wall_color_1=DEFAULTTHEMEWALLCOLOR;
    theme_wall_color_2=DEFAULTTHEMEWALLCOLOR;
    theme_floor_color_1=DEFAULTTHEMEFLOORCOLOR1;
    theme_floor_color_2=DEFAULTTHEMEFLOORCOLOR2;
    theme_heading_color=DEFAULTTHEMEHEADINGCOLOR;
    theme_overlay_image=DEFAULTTHEMEOVERLAYIMAGE;
}
