/**
* \class ConfigGraphics
*/
#ifndef CONFIGGRAPHICS_H
#define CONFIGGRAPHICS_H
#include <string>
#include <vector>
using namespace std;
/// This class is responsible for the Graphics Configuration
/** In this class are defined all the variables for the correct management
 * of graphics configuration's tab.\n
 *
 *
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
