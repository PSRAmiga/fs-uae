/*! \mainpage A Gui designed to simplify the creation of Amiga configuration file
* \section UAE "There are several options available to tune your Amiga experience."
* Unix Amiga Emulator (UAE) is a software emulator of the Amiga platform that runs on Unix machines.\n
* Its purpose is to reproduce the hardware of the original system, so that software written for the emulated
* machine "does not notice" the difference between the real and the virtual machine created by the emulator,
* and then "turns" just like on the original system.
* \subsection AmigaDOS AmigaDOS Beer: a brief "story" of Amiga.
* The company has gone out of business, but their recipe has been
* picked up by some weird German company, so now this beer will be an import. This
* beer never really sold very well because the original manufacturer didn’t understand
* marketing. Like Unix Beer, AmigaDOS Beer fans are an extremely loyal and loud
* group. It originally came in a 16-oz. can, but now comes in 32-oz. cans too. When
* this can was originally introduced, it appeared flashy and colorful, but the design hasn’t
* changed much over the years, so it appears dated now. Critics of this beer claim that it
* is only meant for watching TV anyway.
* \subsection Hardware Hradware
* The Amiga hardware characteristic is the Motorola 68000 processor flanked by three custom-built
* chips that are designed to alleviate the workload of the processor: Agnus, Denise and Paula.
* \subsubsection Agnus Agnus:
* Agnus performs three functions:\n
* \subsection Denise Denise:
* Denise is the chip that deals with the generation of the video output.\n
* Denise displays up to 64 colors (at most 6 bits per pixel indicating the color to be used,
* among those in the registers of color), from a palette of 4096 (12 bit, ie 4 for each color component
* R, G and B, for each color register). Through mode called HAM (short for Hold And Modify)
* can simultaneously show 4096 colors.\n
* Another function of the chip Denise is the management of the sprite, graphic objects of limited size
* (16 pixels wide and up to 255 high), completely independent resolution and number of colors
* from the screen below (called "playfield"), and which is the same hardware to implement the display
* and movement. Denise handles up to eight sprites to four colors; they can then be combined to obtain
* moving objects larger and with a greater number of colors; in the same frame a sprite can be reused
* several times, on the condition that between two copies is maintained distance of a video line horizontal.\n
* \subsubsection Paula Paula:
* Paula is the sound chip, which manages four entries digital 8-bit Amiga.\n
* Amiga produces stereo sound: two items are associated audio to the right channel,
* and two to the left channel, all items are independent, then the two channels from
* sounds completely different.\n
* Paula is also responsible for the management of floppy-disk driver and port I/O: the parallel port "Centronics"
* and the RS-232 25-pin.\n
* \namespace Ui
* \class Amiga
*/
#ifndef AMIGA_H
#define AMIGA_H

#include <QMainWindow>
#include <configchipset.h>
#include <configram.h>
#include <configfloppy.h>
#include <configcdrom.h>
#include <configharddisks.h>
#include <configgraphics.h>
#include <configinput.h>
#include <configtheme.h>
#include <configmisc.h>
/// Create a new main window: Amiga Gui
/** This main window contains several tabs for the correct configuration of FS-UAE.\n
  * For further explanations, see the respective codes.
  */
namespace Ui {
class Amiga;
}
/// This class is responsible for the magement of FS-UAE Gui
/** In this class are defined all the variables for the correct management
 * of all types of settings possible to run FS-UAE.\n
 * We have also introduced some secondary features for FS-UAE but not for
 * the end user such as saving and loading configurations, the possibility
 * of refreshing the gui and reporting bugs.
 */
class Amiga : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit Amiga(QWidget *parent = 0);
    ~Amiga();

private slots:
    void on_saveConfigToolButton_clicked(); ///< Save configuration.
    void on_loadConfigToolButton_clicked(); ///< Load configuration.
    void on_loadDefaultValuesToolButton_clicked();  ///< Reset configuration.
    void on_runConfigButton_clicked();  ///< Run FS-UAE.

    void on_actionAmiga_triggered();    ///< Help menu: what's Amiga?
    void on_actionSummary_triggered();  ///< Help menu: a brief summary.
    void on_actionReport_bug_triggered();   ///< Help menu: open an email browser to report bug.

    void on_kickstartFileToolButton_clicked(); ///< Load Kickstart file.
    void on_kickstartExtFileToolButton_clicked(); ///< Load Extended Kickstart file.
    void on_amigaModelComboBox_currentIndexChanged(const QString &arg1);    ///< List of avaiable Amiga models.
    void on_accuracyLeastRadio_clicked();   ///< Switch to least accuracy.
    void on_accuracyNormalRadio_clicked();  ///< Switch to normal accuracy.
    void on_accuracyMostadio_clicked();     ///< Switch to most accuracy.
    void on_videoModePALRadio_clicked();    ///< Switch to PAL video mode.
    void on_videoModeNTSCRadio_clicked();   ///< Switch to NTST video mode.

    void on_chipMem4MbRadio_clicked();      ///< Chip memory setting at 4Mb.
    void on_chipMeme8MbRadio_clicked();     ///< Chip memory setting at 8Mb.
    void on_chipMem512KbRadio_clicked();    ///< Chip memory setting at 512Kb.
    void on_chipMem1MbRadio_clicked();      ///< Chip memory setting at 1Mb.
    void on_chipMem2MbRadio_clicked();      ///< Chip memory setting at 2Mb.
    void on_slowMemNoneRadio_clicked();     ///< None slow memory.
    void on_slowMem512KbRadio_clicked();    ///< Slow memory setting at 512kb.
    void on_slowMem1MbRadio_clicked();      ///< Slow memory setting at 1Mb.
    void on_slowMem1_8MbRadio_clicked();    ///< Slow memory setting at 1.8Mb.
    void on_fastMemNoneRadio_clicked();     ///< None fast memory.
    void on_fastMem1MbRadio_clicked();      ///< Fast memory setting at 1Mb.
    void on_fastMem2MbRadio_clicked();      ///< Fast memory setting at 2Mb.
    void on_fastMem4MbRadio_clicked();      ///< Fast memory setting at 4Mb.
    void on_fastMem8MbRadio_clicked();      ///< Fast memory setting at 8Mb.
    void on_z3MemNoneRadio_clicked();       ///< None Zorro III memory.
    void on_z3Mem1MbRadio_clicked();        ///< Zorro III memory setting at 1Mb.
    void on_z3Mem2MbRadio_clicked();        ///< Zorro III memory setting at 2Mb.
    void on_z3Mem4MbRadio_clicked();        ///< Zorro III memory setting at 4Mb.
    void on_z3Mem8MbRadio_clicked();        ///< Zorro III memory setting at 8Mb.
    void on_z3Mem16MbRadio_clicked();       ///< Zorro III memory setting at 16Mb.
    void on_z3Mem32MbRadio_clicked();       ///< Zorro III memory setting at 32Mb.
    void on_z3Mem64MbRadio_clicked();       ///< Zorro III memory setting at 64Mb.
    void on_z3Mem128MbRadio_clicked();      ///< Zorro III memory setting at 128Mb.
    void on_z3Mem256MbRadio_clicked();      ///< Zorro III memory setting at 256Mb.

    void on_floppyDrive0ToolButton_clicked();                   ///< Load Floppy in Drive 0.
    void on_floppyDrive1ToolButton_clicked();                   ///< Load Floppy in Drive 1.
    void on_floppyDrive2ToolButton_clicked();                   ///< Load Floppy in Dirve 2.
    void on_floppyDrive3ToolButton_clicked();                   ///< Load Floppy in Drive 3.
    void on_floppySwappingImagesAddPushButton_clicked();        ///< Add Floppy image(s) in Swapping area.
    void on_floppySwappingImagerRemovePushButton_clicked();     ///< Remove floppy image(s) from swapping area.
    void on_floppyDriveVolumeSlider_valueChanged(int value);    ///< Change floppy drive volume (slider).
    void on_floppyDriveVolumeMuteCheckBox_clicked();            ///< Mute floppy drive volume.
    void on_floppyDriveSpeedSlider_valueChanged(int position);  ///< Change floppy dirve speed (slider).

    void on_cdromDrive0ToolButton_clicked();                ///< Load CD-ROM in Drive 0.
    void on_cdromSwappingImagesAddPushButton_clicked();     ///< Add CD-ROM(s) in Swapping area.
    void on_cdromSwappingImagesRemovePushButton_clicked();  ///< Remove CD-ROM(s) from Swapping area.

    void on_hardDrive0FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 0.
    void on_hardDrive0ToolButton_clicked();///< Load Hard Disks in Drive 0.
    void on_hardDrive1ToolButton_clicked();///< Load Hard Disks in Drive 1.
    void on_hardDrive1FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 1.
    void on_hardDrive2ToolButton_clicked();///< Load Hard Disks in Drive 2.
    void on_hardDrive2FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 2.
    void on_hardDrive3ToolButton_clicked();///< Load Hard Disks in Drive 3.
    void on_hardDrive3FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 3.
    void on_hardDrive4FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 4.
    void on_hardDrive4ToolButton_clicked();///< Load Hard Disks in Drive 4.
    void on_hardDrive5ToolButton_clicked();///< Load Hard Disks in Drive 5.
    void on_hardDrive5FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 5.
    void on_hardDrive6ToolButton_clicked();///< Load Hard Disks in Drive 6.
    void on_hardDrive6FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 6.
    void on_hardDrive7ToolButton_clicked();///< Load Hard Disks in Drive 7.
    void on_hardDrive7FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 7.
    void on_hardDrive8ToolButton_clicked();///< Load Hard Disks in Drive 8.
    void on_hardDrive8FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 8.
    void on_hardDrive9ToolButton_clicked();///< Load Hard Disks in Drive 9.
    void on_hardDrive9FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 9.

    void on_hardDrive0LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 0.
    void on_hardDrive1LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 1.
    void on_hardDrive2LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 2.
    void on_hardDrive3LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 3.
    void on_hardDrive4LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 4.
    void on_hardDrive5LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 5.
    void on_hardDrive6LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 6.
    void on_hardDrive7LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 7.
    void on_hardDrive8LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 8.
    void on_hardDrive9LabelLineEdit_textChanged(const QString &arg1);///< Change label of Hard Disk stored in Drive 9.

    void on_hardDrive0ReadOnlyCheckBox_clicked();///< Set hard drive 0 as Read Only.
    void on_hardDrive1ReadOnlyCheckBox_clicked();///< Set hard drive 1 as Read Only.
    void on_hardDrive2ReadOnlyCheckBox_clicked();///< Set hard drive 2 as Read Only.
    void on_hardDrive3ReadOnlyCheckBox_clicked();///< Set hard drive 3 as Read Only.
    void on_hardDrive4ReadOnlyCheckBox_clicked();///< Set hard drive 4 as Read Only.
    void on_hardDrive5ReadOnlyCheckBox_clicked();///< Set hard drive 5 as Read Only.
    void on_hardDrive6ReadOnlyCheckBox_clicked();///< Set hard drive 6 as Read Only.
    void on_hardDrive7ReadOnlyCheckBox_clicked();///< Set hard drive 7 as Read Only.
    void on_hardDrive8ReadOnlyCheckBox_clicked();///< Set hard drive 8 as Read Only.
    void on_hardDrive9ReadOnlyCheckBox_clicked();///< Set hard drive 9 as Read Only.

    void on_displaySettingsStartFullscreenRadioButton_clicked();    ///< Start emulation in fulscreen mode.
    void on_displaySettingsResizableRadioButton_clicked();///< Disable resizing of emulation window.
    void on_displaySettingsKeepAspectRatioRadioButton_clicked();///< Enable keep aspect ratio.
    void on_scanlinesRadioButton_clicked();///< Enable scanlines.
    void on_scanlinesRTGRadioButton_clicked();///< Enable RTG scanlines.
    void on_lowResolutionRadioButton_clicked();///< Start emulatio with low resolution.
    void on_lineDoublingRadioButton_clicked();///< Enable line doubling.
    void on_fullscreenResolutionXSpinBox_valueChanged(const QString &arg1);///< Change X-resolution in fullscreen mode.
    void on_fullscreenResolutionYSpinBox_valueChanged(const QString &arg1);///< Change Y-resolution in fullscreen mode.
    void on_windowResolutionXSpinBox_valueChanged(const QString &arg1);///< Change X-resolution in window mode.
    void on_windowResolutionYSpinBox_valueChanged(const QString &arg1);///< Change Y-resolution in window mode.
    void on_scaleXDoubleSpinBox_valueChanged(const QString &arg1);///< Change X-scale.
    void on_scaleYDoubleSpinBox_valueChanged(const QString &arg1);///< Change Y-scale.
    void on_alignXdoubleSpinBox_valueChanged(const QString &arg1);///< Change X-alignment.
    void on_alignYDoubleSpinBox_valueChanged(const QString &arg1);///< Change Y-alignment.
    void on_scanlinesDarkHorizontalSlider_valueChanged(int position);///< Change scanlines dark.
    void on_scanlinesLightHorizontalSlider_valueChanged(int position);///< Change scanline light.
    void on_fullSceneAntiAliasingOffRadioButton_clicked();///< Disable fullScene anti-aliasing mode.
    void on_fullSceneAntiAliasing2xRadioButton_clicked();///< Enable 2x fullScene anti-aliasing mode.
    void on_fullSceneAntiAliasing4xRadioButton_clicked();///< Enable 4x fullScene anti-aliasing mode.
    void on_fullSceneAntiAliasing8xRadioButton_clicked();///< Enable 8x fullScene anti-aliasing mode.
    void on_textureFilterLinearRadioButton_clicked();///< Apply a linear filter on the texture.
    void on_textureFilterNearestRadioButton_clicked();///< Apply a nearest filter on the texture.
    void on_f11InitalModeAutoRadioButton_clicked();///< Setting F11 initial mode as automatic.
    void on_f11InitalModeFullRadioButton_clicked();///< Setting F11 initial mode as fullscreen.
    void on_f11InitalMode640x400RadioButton_clicked();///< Setting F11 initial mode as 640x400 px.
    void on_f11InitalMode640x480RadioButton_clicked();///< Setting F11 initial mode as 640x480 px.
    void on_f11InitalMode640x512RadioButton_clicked();///< Setting F11 initial mode as 640x512 px.
    void on_f11InitialModeWithBorderCheckBox_clicked();///< Enable border in F11 initial mode.
    void on_videoFormatBGRARadioButton_clicked();///< Setting video format as BRGA.
    void on_videoFormatRGBARadioButton_clicked();///< Setting video format as RBGA.
    void on_textureFormatModeRGBRadioButton_clicked();///< Setting video texture as RGB.
    void on_textureFormatModeRGB8RadioButton_clicked();///< Setting video texture as RGB8.
    void on_textureFormatModeRGBARadioButton_clicked();///< Setting video texture as RGBA.
    void on_textureFormatModeRGBA8RadioButton_clicked();///< Setting vide texture as RGBA8.
    void on_shaderComboBox_currentIndexChanged(const QString &arg1);///< A list of type of shader.
    void on_videoSyncComboBox_currentIndexChanged(const QString &arg1);///< A list of type of video syncronization.
    void on_videoSynkMethodeComboBox_currentIndexChanged(const QString &arg1);///< A list of method of video syncronization.

    void on_alternativeBaseDirPushButton_clicked();                 ///< Explore system for an Alternative Base directory
    void on_alternativeKickstartDirPushButton_clicked();            ///< Explore system for an Alternative Kickstart directory
    void on_alernativeSaveStatesDirPushButton_clicked();            ///< Explore system for an Alternative SaveStates directory
    void on_alternativeFloppyOverlaysDirPushButton_clicked();       ///< Explore system for an Alternative FloppyOverlay directory
    void on_alternativeFlashMemoryDirPushButton_clicked();          ///< Explore system for an Alternative FlashMemory directory
    void on_alternativeControllersDirPushButton_clicked();          ///< Explore system for an Alternative Controllers directory
    void on_alternativeLogsDirPushButton_clicked();                 ///< Explore system for an Alternative Logs directory
    void on_alternativeHardDrivesDirPushButton_clicked();           ///< Explore system for an Alternative HardDrivers directory
    void on_alternativeCdromsDirPushButton_clicked();               ///< Explore system for an Alternative Cdroms directory
    void on_alternativeFloppiesDirPushButton_clicked();             ///< Explore system for an Alternative Floppies directory

    void on_grabMouseCheckBox_clicked();                            ///< Disable grabbing mouse
    void on_grabMouseAutoCheckBox_clicked();                        ///< Disable automatic grabbing mouse
    void on_useBSDCheckBox_clicked();                               ///< Enable BSD
    void on_audioBufferLineEdit_textChanged(const QString &arg1);   ///< Change size of audio buffer
    void on_menuTitleLineEdit_textChanged(const QString &arg1);     ///< Change menu title
    void on_menuSubtitleLineEdit_textChanged(const QString &arg1);  ///< Change menu subtitle

    void on_serverIPLineEdit_textChanged(const QString &arg1);      ///< Insert an IP address
    void on_serverPortLineEdit_textChanged(const QString &arg1);    ///< Insert a Internet port
    void on_playerUsernameLineEdit_textChanged(const QString &arg1);///< Choose a Username
    void on_playerPasswordLineEdit_textChanged(const QString &arg1);///< Choose a password

    void on_fadeColorPushButton_clicked();          ///< Change the fade color
    void on_wallColor1PushButton_clicked();         ///< Chaneg the first wall color
    void on_wallColor2PushButton_clicked();         ///< Change the second wall color
    void on_floorColor1PushButton_clicked();        ///< Change the first floor color
    void on_floorColor2PushButton_clicked();        ///< Change the second wall color
    void on_headColorPushButton_clicked();          ///< Change the head color
    void on_themeOverlayImagerPushButton_clicked(); ///< Change the theme overlay image
    void on_themeFolderPushButton_clicked();        ///< Change the theme folder
    void on_mouseSpeedLineEdit_textChanged(const QString &arg1);    ///< Change mouse speed

    void customJoystick0Slot(QString s);        ///< Custom slot for joystick 0
    void customJoystick1Slot(QString s);        ///< Custom slot for joystick 1
    void customJoystick2Slot(QString s);        ///< Custom slot for joystick 2
    void customJoystick3Slot(QString s);        ///< Custom slot for joystick 3

    void on_readKeyPushButton_clicked();        ///< Start recording keyboard to change a default key

    void on_customInputMappingAddPushButton_clicked();          ///< Add a new different mapping for a key.
    void on_customInputMappingRemovePushButton_clicked();       ///< Remove a different mapping for a key.
    void on_joystickPort0CustomizePushButton_clicked();         ///< Customize joystick in port 0
    void on_joystickPort0CustomJoystickRadioButton_clicked();   ///<
    void on_joystickPort0JoystickRadioButton_clicked();         ///<
    void on_joystickPort0MouseRadioButton_clicked();            ///<
    void on_joystickPort0KeyboardRadioButton_clicked();         ///<
    void on_joystickPort0NothingRadioButton_clicked();          ///<
    void on_joystickPort0ModelComboBox_currentIndexChanged(const QString &arg1);    ///< A list of type of joystick's model
    void on_joystickPort1MouseRadioButton_clicked();
    void on_joystickPort2MouseRadioButton_clicked();
    void on_joystickPort3MouseRadioButton_clicked();
    void on_joystickPort1KeyboardRadioButton_clicked();
    void on_joystickPort2KeyboardRadioButton_clicked();
    void on_joystickPort3KeyboardRadioButton_clicked();
    void on_joystickPort1JoystickRadioButton_clicked();
    void on_joystickPort2JoystickRadioButton_clicked();
    void on_joystickPort3JoystickRadioButton_clicked();
    void on_joystickPort1ModelComboBox_currentIndexChanged(const QString &arg1);    ///< A list of type of joystick's model
    void on_joystickPort2ModelComboBox_currentIndexChanged(const QString &arg1);    ///< A list of type of joystick's model
    void on_joystickPort3ModelComboBox_currentIndexChanged(const QString &arg1);    ///< A list of type of joystick's model
    void on_joystickPort1CustomJoystickRadioButton_clicked();
    void on_joystickPort2CustomJoystickRadioButton_clicked();
    void on_joystickPort3CustomizePushButton_clicked();
    void on_joystickPort3CustomJoystickRadioButton_clicked();
    void on_joystickPort1NothingRadioButton_clicked();
    void on_joystickPort2NothingRadioButton_clicked();
    void on_joystickPort3NothingRadioButton_clicked();
    void on_joystickPort1CusomizePushButton_clicked();
    void on_joystickPort2CustomizePushButton_clicked();

    void on_themeAddViewportPushButton_clicked();       ///< Add a new viewport

    void on_themeRemoveViewportPushButton_clicked();    ///< Report a viewport

private:
    Ui::Amiga *ui;                              ///< Amiga main window
    ConfigChipset chipsetConfiguration;         ///< Chipset configuration tab
    ConfigRam ramConfiguration;                 ///< RAM configuration tab
    ConfigFloppy floppyConfiguration;           ///< Floppy configuration tab
    ConfigCDRom cdromConfiguration;             ///< CDROM configuraion tab
    ConfigHardDisks hardDiskConfiguration;      ///< Hard Disks configuration tab
    ConfigInput inputConfiguration;             ///< Input configuration tab
    ConfigGraphics graphicsConfiguration;       ///< Graphics configuration tab
    ConfigTheme themeConfiguration;             ///< Theme configuration tab
    ConfigMisc miscConfiguration;               ///< Misc configuration tab

    void parseLine(string line);
    void checkConfigurationConsistency();       ///< Verify the consistency of configuration

    void setFastMemoryDisabled(bool state);
    void setZorroIIIMemoryDisabled(bool state);

    void updateGraphicsFromInternalConfiguration();
    void saveConfigInFile(string fileName);
    void loadDefaultValues();
    bool isExistingParameter(string parameterName);

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // AMIGA_H
