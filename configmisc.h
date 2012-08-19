/**
* \class ConfigMisc
*/
#ifndef CONFIGMISC_H
#define CONFIGMISC_H
#include <string>
using namespace std;
/// This class is responsible for the Miscellaneous Configuration
class ConfigMisc
{
    string input_grab;
    string automatic_input_grab;
    string bsdsocket_library;
    string audio_buffer_target_bytes;
    string mouse_speed;
    string title;
    string sub_title;

    string netplay_server;
    string netplay_port;
    string netplay_tag;
    string netplay_password;

    string base_dir;
    string kickstarts_dir;
    string save_states_dir;
    string floppy_overlays_dir;
    string flash_memory_dir;
    string controllers_dir;
    string logs_dir;
    string hard_drives_dir;
    string cdroms_dir;
    string floppies_dir;

public:
    ConfigMisc();

    string getInputGrabConfigString();
    string getInputGrabString();
    string getAutomaticInputGrabConfigString();
    string getAutomaticInputGrabString();
    string getBsdSocketLibraryConfigString();
    string getBsdSocketLibraryString();
    string getAudioBufferConfigString();
    string getAudioBufferString();
    string getMouseSpeedConfigString();
    string getMouseSpeedString();
    string getTitleConfigString();
    string getTitleString();
    string getSubTitleConfigString();
    string getSubTitleString();

    string getNetPlayServerConfigString();
    string getNetPlayServerString();
    string getNetPlayPortConfigString();
    string getNetPlayPortString();
    string getNetPlayTagConfigString();
    string getNetPlayTagString();
    string getNetPlayPasswordConfigString();
    string getNetPlayPasswordString();

    string getBaseDirConfigString();
    string getBaseDirString();
    string getKickstartsDirConfigString();
    string getKickstartsDirString();
    string getSaveStatesDirConfigString();
    string getSaveStatesDirString();
    string getFloppyOverlaysDirConfigString();
    string getFloppyOverlaysDirString();
    string getFlashMemoryDirConfigString();
    string getFlashMemoryDirString();
    string getControllersDirConfigString();
    string getControllersDirString();
    string getLogsDirConfigString();
    string getLogsDirString();
    string getHardDrivesDirConfigString();
    string getHardDrivesDirString();
    string getCDRomsDirConfigString();
    string getCDRomsDirString();
    string getFloppiesDirConfigString();
    string getFloppiesDirString();

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGMISC_H
