/**
* \class ConfigGraphics
*/
#ifndef CONFIGGRAPHICS_H
#define CONFIGGRAPHICS_H
#include <string>
#include <vector>
using namespace std;
/// This class is responsible for the Graphics Configuration management.
/** In this class are defined all the variables for the correct management
* of graphics configuration's tab.\n
* This board is composed of 4 parts: the first section with the DISPLAY SETTINGS,
* the second FILTERS, SHADERS AND SCALING, the third VIDEO SYNCHRONIZATION, and
* fourth VIDEO AND TEXTURE BUFFER FORMAT.\n
* DISPLAY SETTINGS: you can change for startup fullscreen mode and make
* possible the resizing window, change fullscreen and window resolution
* and enable full-scene anti-aliasing.\n
* FILTERS, SHADERS AND SCALING: in this section are all the settings relating scanlines
* (enable, RTG and variation of light and dark), type of shaders, resolution and line doubling.\n
* Here are also managed the position and alignment of the texture as well as their filtering and
* how to start the video emulation.\n
* VIDEO SYNCHRONIZATION: here you can select type and methode of syncronization.\n
* VIDEO AND TEXTURE BUFFER FORMAT: here you can select video and texture format.\n
*/
class ConfigGraphics
{
    string fullscreen;
    string fullscreen_width;
    string fullscreen_height;
    string window_width;
    string window_height;
    string window_resizable;
    string fsaa;
    string keep_aspect;

    string scanlines;
    string rtg_scanlines;
    string scanlines_dark;
    string scanlines_light;
    string shader;
    string low_resolution;
    string line_doubling;
    string scale_x;
    string scale_y;
    string align_x;
    string align_y;
    string zoom;
    string texture_filter;

    string video_sync;
    string video_sync_method;
    string video_format;
    string texture_format;

    vector<string> viewport;

public:
    ConfigGraphics();

    string getFullscreenConfigString();
    string getFullscreenString();
    string getFullscreenWidthConfigString();
    string getFullscreenWidthString();
    string getFullscreenHeightConfigString();
    string getFullscreenHeightString();
    string getWindowWidthConfigString();
    string getWindowWidthString();
    string getWindowHeightConfigString();
    string getWindowHeightString();
    string getWindowResizableConfigString();
    string getWindowResizableString();
    string getFsaaConfigString();
    string getFsaaString();
    string getKeepAspectConfigString();
    string getKeepAspectString();

    string getScanlinesConfigString();
    string getScanlinesString();
    string getRtgScanlinesConfigString();
    string getRtgScanlinesString();
    string getScanlinesDarkConfigString();
    string getScanlinesDarkString();
    string getScanlinesLightConfigString();
    string getScanlinesLightString();
    string getShaderConfigString();
    string getShaderString();
    string getLowResolutionConfigString();
    string getLowResolutionString();
    string getLineDoublingConfigString();
    string getLineDoublingString();
    string getScaleXConfigString();
    string getScaleXString();
    string getScaleYConfigString();
    string getScaleYString();
    string getAlignXConfigString();
    string getAlignXString();
    string getAlignYConfigString();
    string getAlignYString();
    string getZoomConfigString();
    string getZoomString();
    string getTextureFilterConfigString();
    string getTextureFilterString();

    string getVideoSyncConfigString();
    string getVideoSyncString();
    string getVideoSyncMethodConfigString();
    string getVideoSyncMethodString();
    string getVideoFormatConfigString();
    string getVideoFormatString();
    string getTextureFormatConfigString();
    string getTextureFormatString();

    bool containsViewport(string s);
    int getViewportSize();
    string getViewportAt(int position);
    void eraseViewportAt(int position);

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
    bool hasParameter(string parameterName);
    bool isValidViewport(string viewportString);
};

#endif // CONFIGGRAPHICS_H
