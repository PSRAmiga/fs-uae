/**
* \class ConfigMisc
*/
#ifndef CONFIGMISC_H
#define CONFIGMISC_H
#include <string>
using namespace std;
/// This class is responsible for the Miscellaneous Configuration management
/** In this class are stored all the variables for MISC configuration.\n
* You can set audio buffer, mouse speed, the tile and subtitle of the window.\n
* You can also set the automatic grabbing of mouse and keyboard and the settings \n
* of network game. Finally you can config the path of alternative directories.*/
class ConfigMisc
{
    string input_grab;                  ///< Mouse and keyboard grabbing on start
    string automatic_input_grab;        ///< Mouse and keyboard automatic grabbing
    string bsdsocket_library;           ///< BSD socket library
    string audio_buffer_target_bytes;   ///< Audio buffer (in KB)
    string mouse_speed;                 ///< Mouse speed
    string title;                       ///< Window Title
    string sub_title;                   ///< Window Subtitle

    string netplay_server;              ///< Netplay Server IP Address
    string netplay_port;                ///< Netplay Server Port
    string netplay_tag;                 ///< Netplay Username
    string netplay_password;            ///< Netplay user's Password

    string base_dir;            ///< Base directory path
    string kickstarts_dir;      ///< Kickstarts directory path
    string save_states_dir;     ///< Save states directory path
    string floppy_overlays_dir; ///< Floppy Overlays directory path
    string flash_memory_dir;    ///< Flash Memory directory path
    string controllers_dir;     ///< Controllers directory path
    string logs_dir;            ///< Logs directory path
    string hard_drives_dir;     ///< Hard Drives directory path
    string cdroms_dir;          ///< CD-ROMs directory path
    string floppies_dir;        ///< Floppies directory path

public:
    ConfigMisc();               ///< Creates an empty MISC configuration

    /** \brief Returns the Input Grab setting to be written in Config File.
     * \return the string to be written in Config File. If Input Grab has the default value (1), it returns an empty string
     */
    string getInputGrabConfigString();
    /** \brief Returns the Input Grab value.
     * \return the Input Grab value.
     */
    string getInputGrabString();
    /** \brief Returns the Automatic Input Grab setting to be written in Config File.
     * \return the string to be written in Config File. If Automatic Input Grab has the default value (1), it returns an empty string
     */
    string getAutomaticInputGrabConfigString();
    /** \brief Returns the Automatic Input Grab value.
     * \return the Automatic Input Grab value.
     */
    string getAutomaticInputGrabString();
    /** \brief Returns the BSD Socket Library setting to be written in Config File.
     * \return the string to be written in Config File. If BSD Socket Library has the default value (0), it returns an empty string
     */
    string getBsdSocketLibraryConfigString();
    /** \brief Returns the BSD Socket Library value.
     * \return the BSD Socket Library value.
     */
    string getBsdSocketLibraryString();
    /** \brief Returns the Audio Buffer setting to be written in Config File.
     * \return the string to be written in Config File. If Audio Buffer has the default value (8192), it returns an empty string
     */
    string getAudioBufferConfigString();
    /** \brief Returns the Audio Buffer value.
     * \return the Audio Buffer value.
     */
    string getAudioBufferString();
    /** \brief Returns the Mouse Speed setting to be written in Config File.
     * \return the string to be written in Config File. If Mouse Speed has the default value (100), it returns an empty string
     */
    string getMouseSpeedConfigString();
    /** \brief Returns the Mouse Speed value.
     * \return the Mouse Speed value.
     */
    string getMouseSpeedString();
    /** \brief Returns the Title string to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getTitleConfigString();
    /** \brief Returns the Title string.
     * \return the Title string.
     */
    string getTitleString();
    /** \brief Returns the SubTitle string to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getSubTitleConfigString();
    /** \brief Returns the SubTitle string.
     * \return the SubTitle string.
     */
    string getSubTitleString();

    /** \brief Returns the NetPlay Server IP to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getNetPlayServerConfigString();
    /** \brief Returns the NetPlay Server IP.
     * \return the NetPlay Server IP.
     */
    string getNetPlayServerString();
    /** \brief Returns the NetPlay Server Port to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getNetPlayPortConfigString();
    /** \brief Returns the NetPlay Server Port.
     * \return the NetPlay Server IP.
     */
    string getNetPlayPortString();
    /** \brief Returns the NetPlay Username to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getNetPlayTagConfigString();
    /** \brief Returns the NetPlay Username.
     * \return the NetPlay Username.
     */
    string getNetPlayTagString();
    /** \brief Returns the NetPlay user's Password to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getNetPlayPasswordConfigString();
    /** \brief Returns the NetPlay user's Password.
     * \return the NetPlay user's Password.
     */
    string getNetPlayPasswordString();

    /** \brief Returns the Base directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getBaseDirConfigString();
    /** \brief Returns the Base directory path.
     * \return the Base directory path.
     */
    string getBaseDirString();
    /** \brief Returns the Kickstarts directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getKickstartsDirConfigString();
    /** \brief Returns the Kickstarts directory path.
     * \return the Kickstarts directory path.
     */
    string getKickstartsDirString();
    /** \brief Returns the Save States directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getSaveStatesDirConfigString();
    /** \brief Returns the Save States directory path.
     * \return the Save States directory path.
     */
    string getSaveStatesDirString();
    /** \brief Returns the Floppy Overlays directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getFloppyOverlaysDirConfigString();
    /** \brief Returns the Floppy Overlays directory path.
     * \return the Floppy Overlays directory path.
     */
    string getFloppyOverlaysDirString();
    /** \brief Returns the Flash Memory directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getFlashMemoryDirConfigString();
    /** \brief Returns the Flash Memory directory path.
     * \return the Flash Memory directory path.
     */
    string getFlashMemoryDirString();
    /** \brief Returns the Controllers directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getControllersDirConfigString();
    /** \brief Returns the Controllers directory path.
     * \return the Controllers directory path.
     */
    string getControllersDirString();
    /** \brief Returns the Logs directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getLogsDirConfigString();
    /** \brief Returns the Logs directory path.
     * \return the Logs directory path.
     */
    string getLogsDirString();
    /** \brief Returns the Hard Drives directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getHardDrivesDirConfigString();
    /** \brief Returns the Hard Drives directory path.
     * \return the Hard Drives directory path.
     */
    string getHardDrivesDirString();
    /** \brief Returns the CD-ROMs directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getCDRomsDirConfigString();
    /** \brief Returns the CD-ROMs directory path.
     * \return the CD-ROMs directory path.
     */
    string getCDRomsDirString();
    /** \brief Returns the Floppies directory path to be written in Config File.
     * \return the string to be written in Config File.
     */
    string getFloppiesDirConfigString();
    /** \brief Returns the Floppies directory path.
     * \return the Floppies directory path.
     */
    string getFloppiesDirString();

    /** \brief Set MISC configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set MISC configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if MISC configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);
};

#endif // CONFIGMISC_H
