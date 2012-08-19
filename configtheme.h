/** \class ConfigTheme
*/
#ifndef CONFIGTHEME_H
#define CONFIGTHEME_H
#include <string>
using namespace std;
/// This class is responsible for the Theme Configuration.
class ConfigTheme
{
    string theme;
    string theme_fade_color;
    string theme_wall_color_1;
    string theme_wall_color_2;
    string theme_floor_color_1;
    string theme_floor_color_2;
    string theme_heading_color;
    string theme_overlay_image;

public:
    ConfigTheme();

    string getThemeConfigString();
    string getThemeString();
    string getFadeColorConfigString();
    string getFadeColorString();
    string getWallColor1ConfigString();
    string getWallColor1String();
    string getWallColor2ConfigString();
    string getWallColor2String();
    string getFloorColor1ConfigString();
    string getFloorColor1String();
    string getFloorColor2ConfigString();
    string getFloorColor2String();
    string getHeadingColorConfigString();
    string getHeadingColorString();
    string getOverlayImageConfigString();
    string getOverlayImageString();

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGTHEME_H
