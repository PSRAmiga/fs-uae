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
    bool hasParameter(string parameterName);
};

#endif // CONFIGTHEME_H

/*
The option viewport specifies a crop rectangle to apply to the Amiga video­out. The default, if not specified,
is to calculate this automatically (auto­scaling). If auto­scaling does not work perfectly for a game, and you
want a cropped output, you can specify any crop rectangle (x y width height).
To force an uncropped viewport (and effectively disable autoscaling), you can specify:
viewport = * * * * => 0 0 752 574
Often, Amiga games have viewports with varying size and position. The default autoscaling system works well
with many games, but not all. You can modify the auto­scaling algorithm by specifying patterns to replace.
The viewport setting will be consulted each time the auto­scaling algorithm chooses a new viewport.
The following viewport specification does nothing:
viewport = * * * * => * * * *
*/
