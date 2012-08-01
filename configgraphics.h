#ifndef CONFIGGRAPHICS_H
#define CONFIGGRAPHICS_H
#include <string>
using namespace std;

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

    void setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGGRAPHICS_H
