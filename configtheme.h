/** \class ConfigTheme
*/
#ifndef CONFIGTHEME_H
#define CONFIGTHEME_H
#include <string>
using namespace std;
/// This class is responsible for the Theme Configuration management.
/** In this class are stored all the variables for THEME configuration.\n
 * You can choose a theme, an overlay image and the colours of theme.
*/
class ConfigTheme
{
    string theme;                   ///< Theme folder path
    string theme_fade_color;        ///< Theme fade color
    string theme_wall_color_1;      ///< Theme wall color 1
    string theme_wall_color_2;      ///< Theme wall color 2
    string theme_floor_color_1;     ///< Theme floor color 1
    string theme_floor_color_2;     ///< Theme floor color 2
    string theme_heading_color;     ///< Theme heading color
    string theme_overlay_image;     ///< Theme overlay image path

public:
    ConfigTheme();      ///< Creates an empty Theme configuration

    /** \brief Returns the string of theme folder path to be written in Config File.
      * \return the string to be written in Config File.
      */
    string getThemeConfigString();
    /** \brief Returns the theme folder path.
      * \return the theme folder path.
      */
    string getThemeString();
    /** \brief Returns the string of fade color to be written in Config File.
      * \return the string to be written in Config File. If the color has the default value (#3c3b37), it returns an empty string.
      */
    string getFadeColorConfigString();
    /** \brief Returns the fade color rgb value.
      * \return the fade color rgb value.
      */
    string getFadeColorString();
    /** \brief Returns the string of wall color 1 to be written in Config File.
      * \return the string to be written in Config File. If the color has the default value (#3c3b37), it returns an empty string.
      */
    string getWallColor1ConfigString();
    /** \brief Returns the wall color 1 rgb value.
      * \return the wall color 1 rgb value.
      */
    string getWallColor1String();
    /** \brief Returns the string of wall color 2 to be written in Config File.
      * \return the string to be written in Config File. If the color has the default value (#3c3b37), it returns an empty string.
      */
    string getWallColor2ConfigString();
    /** \brief Returns the wall color 2 rgb value.
      * \return the wall color 2 rgb value.
      */
    string getWallColor2String();
    /** \brief Returns the string of floor color 1 to be written in Config File.
      * \return the string to be written in Config File. If the color has the default value (#1d1d1b), it returns an empty string.
      */
    string getFloorColor1ConfigString();
    /** \brief Returns the floor color 1 rgb value.
      * \return the floor color 1 rgb value.
      */
    string getFloorColor1String();
    /** \brief Returns the string of floor color 2 to be written in Config File.
      * \return the string to be written in Config File. If the color has the default value (#111110), it returns an empty string.
      */
    string getFloorColor2ConfigString();
    /** \brief Returns the floor color 2 rgb value.
      * \return the floor color 2 rgb value.
      */
    string getFloorColor2String();
    /** \brief Returns the string of heading color to be written in Config File.
      * \return the string to be written in Config File. If the color has the default value (#f68355), it returns an empty string.
      */
    string getHeadingColorConfigString();
    /** \brief Returns the heading color rgb value.
      * \return the heading color rgb value.
      */
    string getHeadingColorString();
    /** \brief Returns the string of theme overlay image path to be written in Config File.
      * \return the string to be written in Config File.
      */
    string getOverlayImageConfigString();
    /** \brief Returns the theme overlay image path.
      * \return the theme overlay image path.
      */
    string getOverlayImageString();

    /** \brief Set Theme configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set Theme configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if Theme configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
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
