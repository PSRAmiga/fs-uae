/**
* \class ConfigGraphics
*/
#ifndef CONFIGGRAPHICS_H
#define CONFIGGRAPHICS_H
#include <string>
#include <vector>
using namespace std;
/// This class is responsible for the Graphics Configuration management.
/** In this class are stored all the variables for GRAPHICS configuration.\n
* You can select the DISPLAY SETTINGS, FILTERS, SHADERS AND SCALING, VIDEO SYNCHRONIZATION, and VIDEO AND TEXTURE BUFFER FORMAT.\n
* DISPLAY SETTINGS: you can change for startup fullscreen mode and make
* possible the resizing window, change fullscreen and window resolution
* and enable full-scene anti-aliasing.\n
* FILTERS, SHADERS AND SCALING: you can edit scanlines parameter, type of shaders, resolution and line doubling.\n
* Here are also managed the position and alignment of the video, textures setting as well as video initial mode .\n
* VIDEO SYNCHRONIZATION: here you can select type and methode of syncronization.\n
* VIDEO AND TEXTURE BUFFER FORMAT: here you can select video and texture format.\n
*/
class ConfigGraphics
{
    string fullscreen;          ///< Fullscreen mode
    string fullscreen_width;    ///< Fullscreen Width
    string fullscreen_height;   ///< Fullscreen Height
    string window_width;        ///< Window Width
    string window_height;       ///< Window Height
    string window_resizable;    ///< Window Resizable
    string fsaa;                ///< Full-scene anti-aliasing
    string keep_aspect;         ///< Keep Aspect Ratio

    string scanlines;           ///< Scanlines
    string rtg_scanlines;       ///< RTG Scanlines
    string scanlines_dark;      ///< Scanlines intensity
    string scanlines_light;     ///< Scanlines light
    string shader;              ///< Shader
    string low_resolution;      ///< Low Resolution
    string line_doubling;       ///< Line Doubling
    string scale_x;             ///< Video Scale x
    string scale_y;             ///< Video Scale y
    string align_x;             ///< Video Align X
    string align_y;             ///< Video Align Y
    string zoom;                ///< Zoom
    string texture_filter;      ///< Texture Filter

    string video_sync;          ///< Video Sync Mode
    string video_sync_method;   ///< Video Sync Method
    string video_format;        ///< Video Format
    string texture_format;      ///< Texture Format

    vector<string> viewport;    ///< List of Video Ports

public:
    ConfigGraphics();               ///< Creates an empty GRAPHICS configuration

    /** \brief Returns the Fullscreen mode string to be written in Config File.
      * \return the string to be written in Config File. If Fullscreen mode has the default value (0), it returns an empty string.
      */
    string getFullscreenConfigString();
    /** \brief Returns the fullscreen mode string
      * \return the fullscreen mode string
      */
    string getFullscreenString();
    /** \brief Returns the Fullscreen Width string to be written in Config File.
      * \return the string to be written in Config File.
      */
    string getFullscreenWidthConfigString();
    /** \brief Returns the fullscreen width string
      * \return the fullscreen width string
      */
    string getFullscreenWidthString();
    /** \brief Returns the Fullscreen Height string to be written in Config File.
      * \return the string to be written in Config File.
      */
    string getFullscreenHeightConfigString();
    /** \brief Returns the fullscreen height string
      * \return the fullscreen height string
      */
    string getFullscreenHeightString();
    /** \brief Returns the Window Width string to be written in Config File.
      * \return the string to be written in Config File. If Window Width has the default value (960), it returns an empty string.
      */
    string getWindowWidthConfigString();
    /** \brief Returns the Window width string
      * \return the Window width string
      */
    string getWindowWidthString();
    /** \brief Returns the Window Height string to be written in Config File.
      * \return the string to be written in Config File. If Window Height has the default value (540), it returns an empty string.
      */
    string getWindowHeightConfigString();
    /** \brief Returns the window height string
      * \return the window height string
      */
    string getWindowHeightString();
    /** \brief Returns the Window resizable string to be written in Config File.
      * \return the string to be written in Config File. If Window resizable has the default value (1), it returns an empty string.
      */
    string getWindowResizableConfigString();
    /** \brief Returns the window resizable string
      * \return the window resizable string
      */
    string getWindowResizableString();
    /** \brief Returns the Full-scene anti-aliasing string to be written in Config File.
      * \return the string to be written in Config File. If Full-scene anti-aliasing has the default value (0), it returns an empty string.
      */
    string getFsaaConfigString();
    /** \brief Returns the Full-scene anti-aliasing string
      * \return the Full-scene anti-aliasing string
      */
    string getFsaaString();
    /** \brief Returns the keep aspect ratio string to be written in Config File.
      * \return the string to be written in Config File. If keep aspect ratio has the default value (0), it returns an empty string.
      */
    string getKeepAspectConfigString();
    /** \brief Returns the keep aspect ratio string
      * \return the keep aspect ratio string
      */
    string getKeepAspectString();
    /** \brief Returns the scanlines string to be written in Config File.
      * \return the string to be written in Config File. If scanlines has the default value (0), it returns an empty string.
      */
    string getScanlinesConfigString();
    /** \brief Returns the scanlines string
      * \return the scanlines string
      */
    string getScanlinesString();
    /** \brief Returns the Rtg scanlines string to be written in Config File.
      * \return the string to be written in Config File. If Rtg scanlines has the default value (0), it returns an empty string.
      */
    string getRtgScanlinesConfigString();
    /** \brief Returns the Rtg scanlines string
      * \return the Rtg scanlines string
      */
    string getRtgScanlinesString();
    /** \brief Returns the scanlines dark string to be written in Config File.
      * \return the string to be written in Config File. If scanlines dark has the default value (10), it returns an empty string.
      */
    string getScanlinesDarkConfigString();
    /** \brief Returns the scanlines dark string
      * \return the scanlines dark string
      */
    string getScanlinesDarkString();
    /** \brief Returns the scanlines light string to be written in Config File.
      * \return the string to be written in Config File. If scanlines light has the default value (5), it returns an empty string.
      */
    string getScanlinesLightConfigString();
    /** \brief Returns the scanlines light string
      * \return the scanlines light string
      */
    string getScanlinesLightString();
    /** \brief Returns the shader string to be written in Config File.
      * \return the string to be written in Config File.
      */
    string getShaderConfigString();
    /** \brief Returns the shader light string
      * \return the shader light string
      */
    string getShaderString();
    /** \brief Returns the low resolution string to be written in Config File.
      * \return the string to be written in Config File. If low resolution has the default value (0), it returns an empty string.
      */
    string getLowResolutionConfigString();
    /** \brief Returns the low resolution string
      * \return the low resolution string
      */
    string getLowResolutionString();
    /** \brief Returns the line doubling string to be written in Config File.
      * \return the string to be written in Config File. If line doubling has the default value (1), it returns an empty string.
      */
    string getLineDoublingConfigString();
    /** \brief Returns the line doubling string
      * \return the line doubling string
      */
    string getLineDoublingString();
    /** \brief Returns the X-scale string to be written in Config File.
      * \return the string to be written in Config File. If X-scale has the default value (-1.0), it returns an empty string.
      */
    string getScaleXConfigString();
    /** \brief Returns the X-scale string
      * \return the X-scale string
      */
    string getScaleXString();
    /** \brief Returns the Y-scale string to be written in Config File.
      * \return the string to be written in Config File. If Y-scale has the default value (-1.0), it returns an empty string.
      */
    string getScaleYConfigString();
    /** \brief Returns the Y-scale string
      * \return the Y-scale string
      */
    string getScaleYString();
    /** \brief Returns the X-alignment string to be written in Config File.
      * \return the string to be written in Config File. If X-alignment has the default value (0.5), it returns an empty string.
      */
    string getAlignXConfigString();
    /** \brief Returns the X-alignment string
      * \return the X-alignment string
      */
    string getAlignXString();
    /** \brief Returns the Y-aligmnent string to be written in Config File.
      * \return the string to be written in Config File. If Y-alignment has the default value (0.5), it returns an empty string.
      */
    string getAlignYConfigString();
    /** \brief Returns the Y-alignment string
      * \return the line doubling string
      */
    string getAlignYString();
    /** \brief Returns the zoom value string to be written in Config File.
      * \return the string to be written in Config File. If zoom value has the default value (auto), it returns an empty string.
      */
    string getZoomConfigString();
    /** \brief Returns the zoom value string
      * \return the zoom value string
      */
    string getZoomString();
    /** \brief Returns the texture filter string to be written in Config File.
      * \return the string to be written in Config File. If texture filter has the default value (nearest), it returns an empty string.
      */
    string getTextureFilterConfigString();
    /** \brief Returns the texture filter string
      * \return the texture filter string
      */
    string getTextureFilterString();

    /** \brief Returns the video syncronization string to be written in Config File.
      * \return the string to be written in Config File. If video syncronization has the default value (auto), it returns an empty string.
      */
    string getVideoSyncConfigString();
    /** \brief Returns the video syncronization string
      * \return the video syncronization string
      */
    string getVideoSyncString();
    /** \brief Returns the video syncronization methode string to be written in Config File.
      * \return the string to be written in Config File. If video syncronization methode has the default value (finish-swap-finish), it returns an empty string.
      */
    string getVideoSyncMethodConfigString();
    /** \brief Returns the video syncronization methode string
      * \return the video syncronization methode string
      */
    string getVideoSyncMethodString();
    /** \brief Returns the video format string to be written in Config File.
      * \return the string to be written in Config File. If video format has the default value (bgra), it returns an empty string.
      */
    string getVideoFormatConfigString();
    /** \brief Returns the video format string
      * \return the video format string
      */
    string getVideoFormatString();
    /** \brief Returns the texture format string to be written in Config File.
      * \return the string to be written in Config File. If texture format has the default value (rgb), it returns an empty string.
      */
    string getTextureFormatConfigString();
    /** \brief Returns the texture format string
      * \return the line doubling string
      */
    string getTextureFormatString();

    /** \brief Checks if you have already remapped a viewport
      * \return true if you have already inserted that viewport
      * \param s is the viewport to be checked
      */
    bool containsViewport(string s);
    /** \brief Returns the size of List of inserted viewports.
      * \return the size of List of inserted viewports.
      */
    int getViewportSize();
    /** \brief Returns the Viewport string at the specified position to be written in Config File.
      *\param position of Viewport string to be returned
      * \return the Viewport string at the specified position to be written in Config File.
      */
    string getViewportAt(int position);
    /** \brief Delete the Viewport at the specified position
      *\param position of the Viewport to be removed
      */
    void eraseViewportAt(int position);

    /** \brief Set GRAPHICS configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set GRAPHICS configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if GRAPHICS configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);
    /** \briefCHecks if viewportString is a valid ViewPort
      *\param viewportString is the string to be checked
      *\return true if viewportString is valid
      */
    bool isValidViewport(string viewportString);
};

#endif // CONFIGGRAPHICS_H
