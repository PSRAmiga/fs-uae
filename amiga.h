/*! \mainpage A Gui designed to simplify the creation of Amiga configuration file
* \section FS-UAE FS-UAE README
* FS-UAE is an Amiga emulator for Windows, Linux and Mac OS X based on UAE/WinUAE, with a focus on emulating games.\n
* Features include emulation of Amiga 500, 1200, 4000, CD32 and CDTV, perfectly smooth scrolling on 50Hz displays, support \n
* for floppy images in ADF and IPF formats, CD-ROM images in ISO or BIN/CUE format, mounting folders on your computer as \n
* Amiga hard drives, support for Picasso 96 drivers for high-color and high-resolution Workbench displays, and more! A unique\n
* feature is support for cross-platform online play. You can now play Amiga games against (or with) friends over the Internet.\n
* The emulator uses the latest Amiga emulation code from the WinUAE project and requires a moderately fast computer with\n
* accelerated graphics (OpenGL) to work. A game pad or joystick is recommended, but not required (FS-UAE can emulate a joystick\n
* using the cursor keys and right ctrl/alt keys).\n
* The official home page of FS-UAE is:\n
* http://fengestad.no/fs-uae/\n
* The complete README can be found here:\n
* http://fengestad.no/fs-uae/README\n
* \section FS-UAEGUI Why a Gui?
* FS-UAE does not include a configuration UI, so you must create a configuration file before the emulator will be usable.\n
* This application can help you to create a new configuration file and launch the emulator for you.\n
* When you start the application all the parameters are set to the default values. You can create your own configuration file\n
* or load an existing one. Finally you can launch directly FS-UAE. The application can control the consistency of the configuration\n
* and correct it before launching FS-UAE (for example it checks that you have not load a CD-ROM iso image if the model you have\n
* selected has not a CD player!).\n
* If you have more than one device of the same model, this application can also automatically number joystick to distinguish them.\n
* The application is divided in 9 different configuration area:\n-Chipset\n-Floppy\n-CD-ROM\n-HD\n-Input Devices\n-Input Map\n-Graphics\n-Theme\n-Misc\n
*/

/**
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

namespace Ui {
class Amiga;
}
/// This class is responsible for the magement of FS-UAE Gui
/** This main window contains several tabs for the correct configuration of FS-UAE:
 * For further explanations, see the respective configuration area code.\n
 * When the application is started, all parameters are set to the default value.
 * User can Load default values, Load an existing configuration file, Save current configuration in a file or Launch FS-UAE with the current configuration.
 */
class Amiga : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit Amiga(QWidget *parent = 0); ///< Create the GUI.
    ~Amiga();                            ///< Destroy the GUI,

private slots:
    void on_saveConfigToolButton_clicked();         ///< Save current configuration.
    void on_loadConfigToolButton_clicked();         ///< Load an existing configuration.
    void on_loadDefaultValuesToolButton_clicked();  ///< Reset configuration to the default values.
    void on_runConfigButton_clicked();              ///< Run FS-UAE with current configuration.

    void on_actionAmiga_triggered();        ///< Help menu: what's Amiga?
    void on_actionSummary_triggered();      ///< Help menu: a brief summary.
    void on_actionReport_bug_triggered();   ///< Help menu: open an email browser to report bug.

    void on_kickstartFileToolButton_clicked();                              ///< Select Kickstart file.
    void on_kickstartExtFileToolButton_clicked();                           ///< Select Extended Kickstart file.
    void on_amigaModelComboBox_currentIndexChanged(const QString &arg1);    ///< Select Amiga model.
    void on_accuracyLeastRadio_clicked();    ///< Switch to least accuracy.
    void on_accuracyNormalRadio_clicked();  ///< Switch to normal accuracy.
    void on_accuracyMostadio_clicked();     ///< Switch to most accuracy.
    void on_videoModePALRadio_clicked();    ///< Switch to PAL video mode.
    void on_videoModeNTSCRadio_clicked();   ///< Switch to NTST video mode.

    void on_chipMem4MbRadio_clicked();      ///< Set Chip memory to 4Mb.
    void on_chipMeme8MbRadio_clicked();     ///< Set Chip memory at 8Mb.
    void on_chipMem512KbRadio_clicked();    ///< Set Chip memory at 512Kb.
    void on_chipMem1MbRadio_clicked();      ///< Set Chip memory at 1Mb.
    void on_chipMem2MbRadio_clicked();      ///< Set Chip memory at 2Mb.
    void on_slowMemNoneRadio_clicked();     ///< Disable Slow memory.
    void on_slowMem512KbRadio_clicked();    ///< Set Slow memory at 512kb.
    void on_slowMem1MbRadio_clicked();      ///< Set Slow memory at 1Mb.
    void on_slowMem1_8MbRadio_clicked();    ///< Set Slow memory at 1.8Mb.
    void on_fastMemNoneRadio_clicked();     ///< Disable Fast memory.
    void on_fastMem1MbRadio_clicked();      ///< Set Fast memory at 1Mb.
    void on_fastMem2MbRadio_clicked();      ///< Set Fast memory at 2Mb.
    void on_fastMem4MbRadio_clicked();      ///< Set Fast memory at 4Mb.
    void on_fastMem8MbRadio_clicked();      ///< Set Fast memory at 8Mb.
    void on_z3MemNoneRadio_clicked();       ///< Disable Zorro III memory.
    void on_z3Mem1MbRadio_clicked();        ///< Set Zorro III memory at 1Mb.
    void on_z3Mem2MbRadio_clicked();        ///< Set Zorro III memory at 2Mb.
    void on_z3Mem4MbRadio_clicked();        ///< Set Zorro III memory at 4Mb.
    void on_z3Mem8MbRadio_clicked();        ///< Set Zorro III memory at 8Mb.
    void on_z3Mem16MbRadio_clicked();       ///< Set Zorro III memory at 16Mb.
    void on_z3Mem32MbRadio_clicked();       ///< Set Zorro III memory at 32Mb.
    void on_z3Mem64MbRadio_clicked();       ///< Set Zorro III memory at 64Mb.
    void on_z3Mem128MbRadio_clicked();      ///< Set Zorro III memory at 128Mb.
    void on_z3Mem256MbRadio_clicked();      ///< Set Zorro III memory at 256Mb.

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
    void on_hardDrive0ToolButton_clicked();///< Load Hard Disk file in Drive 0.
    void on_hardDrive1ToolButton_clicked();///< Load Hard Disk file in Drive 1.
    void on_hardDrive1FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 1.
    void on_hardDrive2ToolButton_clicked();///< Load Hard Disk file in Drive 2.
    void on_hardDrive2FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 2.
    void on_hardDrive3ToolButton_clicked();///< Load Hard Disk file in Drive 3.
    void on_hardDrive3FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 3.
    void on_hardDrive4FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 4.
    void on_hardDrive4ToolButton_clicked();///< Load Hard Disk file in Drive 4.
    void on_hardDrive5ToolButton_clicked();///< Load Hard Disk file in Drive 5.
    void on_hardDrive5FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 5.
    void on_hardDrive6ToolButton_clicked();///< Load Hard Disk file in Drive 6.
    void on_hardDrive6FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 6.
    void on_hardDrive7ToolButton_clicked();///< Load Hard Disk file in Drive 7.
    void on_hardDrive7FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 7.
    void on_hardDrive8ToolButton_clicked();///< Load Hard Disk file in Drive 8.
    void on_hardDrive8FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 8.
    void on_hardDrive9ToolButton_clicked();///< Load Hard Disk file in Drive 9.
    void on_hardDrive9FolderToolButton_clicked();///< Load Hard Disk Folder in Drive 9.

    void on_hardDrive0LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 0.
    void on_hardDrive1LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 1.
    void on_hardDrive2LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 2.
    void on_hardDrive3LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 3.
    void on_hardDrive4LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 4.
    void on_hardDrive5LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 5.
    void on_hardDrive6LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 6.
    void on_hardDrive7LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 7.
    void on_hardDrive8LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 8.
    void on_hardDrive9LabelLineEdit_textChanged(const QString &arg1);       ///< Change label of Hard Disk stored in Drive 9.

    void on_hardDrive0ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 0 as Read Only.
    void on_hardDrive1ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 1 as Read Only.
    void on_hardDrive2ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 2 as Read Only.
    void on_hardDrive3ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 3 as Read Only.
    void on_hardDrive4ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 4 as Read Only.
    void on_hardDrive5ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 5 as Read Only.
    void on_hardDrive6ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 6 as Read Only.
    void on_hardDrive7ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 7 as Read Only.
    void on_hardDrive8ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 8 as Read Only.
    void on_hardDrive9ReadOnlyCheckBox_clicked();       ///< Set/unset hard drive 9 as Read Only.

    void on_displaySettingsStartFullscreenRadioButton_clicked();                ///< Enable/disable emulation start in fulscreen mode.
    void on_displaySettingsResizableRadioButton_clicked();                      ///< Enable/disable the resizing of emulation window.
    void on_displaySettingsKeepAspectRatioRadioButton_clicked();                ///< Enable/disable keep aspect ratio.
    void on_scanlinesRadioButton_clicked();                                     ///< Enable/disable scanlines.
    void on_scanlinesRTGRadioButton_clicked();                                  ///< Enable/disable RTG scanlines.
    void on_lowResolutionRadioButton_clicked();                                 ///< Enable/disable emulation start with low resolution.
    void on_lineDoublingRadioButton_clicked();                                  ///< Enable/disable line doubling.
    void on_fullscreenResolutionXSpinBox_valueChanged(const QString &arg1);     ///< Change X-resolution in fullscreen mode.
    void on_fullscreenResolutionYSpinBox_valueChanged(const QString &arg1);     ///< Change Y-resolution in fullscreen mode.
    void on_windowResolutionXSpinBox_valueChanged(const QString &arg1);         ///< Change X-resolution in window mode.
    void on_windowResolutionYSpinBox_valueChanged(const QString &arg1);         ///< Change Y-resolution in window mode.
    void on_scaleXDoubleSpinBox_valueChanged(const QString &arg1);              ///< Change X-scale.
    void on_scaleYDoubleSpinBox_valueChanged(const QString &arg1);              ///< Change Y-scale.
    void on_alignXdoubleSpinBox_valueChanged(const QString &arg1);              ///< Change X-alignment.
    void on_alignYDoubleSpinBox_valueChanged(const QString &arg1);              ///< Change Y-alignment.
    void on_scanlinesDarkHorizontalSlider_valueChanged(int position);           ///< Change scanlines dark.
    void on_scanlinesLightHorizontalSlider_valueChanged(int position);          ///< Change scanline light.
    void on_fullSceneAntiAliasingOffRadioButton_clicked();                      ///< Disable fullScene anti-aliasing mode.
    void on_fullSceneAntiAliasing2xRadioButton_clicked();                       ///< Enable 2x fullScene anti-aliasing mode.
    void on_fullSceneAntiAliasing4xRadioButton_clicked();                       ///< Enable 4x fullScene anti-aliasing mode.
    void on_fullSceneAntiAliasing8xRadioButton_clicked();                       ///< Enable 8x fullScene anti-aliasing mode.
    void on_textureFilterLinearRadioButton_clicked();                           ///< Apply a linear filter on the texture.
    void on_textureFilterNearestRadioButton_clicked();                          ///< Apply a nearest filter on the texture.
    void on_f11InitalModeAutoRadioButton_clicked();                             ///< Set F11 initial mode ti automatic.
    void on_f11InitalModeFullRadioButton_clicked();                             ///< Set F11 initial mode ti fullscreen.
    void on_f11InitalMode640x400RadioButton_clicked();                          ///< Set F11 initial mode ti 640x400 px.
    void on_f11InitalMode640x480RadioButton_clicked();                          ///< Set F11 initial mode ti 640x480 px.
    void on_f11InitalMode640x512RadioButton_clicked();                          ///< Set F11 initial mode ti 640x512 px.
    void on_f11InitialModeWithBorderCheckBox_clicked();                         ///< Enable/disable border in F11 initial mode.
    void on_videoFormatBGRARadioButton_clicked();                               ///< Set BRGA video format.
    void on_videoFormatRGBARadioButton_clicked();                               ///< Set RBGA video format.
    void on_textureFormatModeRGBRadioButton_clicked();                          ///< Set RGB video texture.
    void on_textureFormatModeRGB8RadioButton_clicked();                         ///< Set RGB8 video texture.
    void on_textureFormatModeRGBARadioButton_clicked();                         ///< Sett RGBA video texture.
    void on_textureFormatModeRGBA8RadioButton_clicked();                        ///< Set RGBA8 video texture.
    void on_shaderComboBox_currentIndexChanged(const QString &arg1);            ///< Select shader type.
    void on_videoSyncComboBox_currentIndexChanged(const QString &arg1);         ///< Select video syncronization.
    void on_videoSynkMethodeComboBox_currentIndexChanged(const QString &arg1);  ///< Select video syncronization method.
    void on_themeAddViewportPushButton_clicked();                               ///< Add a new viewport
    void on_themeRemoveViewportPushButton_clicked();                            ///< Remove a viewport

    void on_alternativeBaseDirPushButton_clicked();                 ///< Select an Alternative Base directory.
    void on_alternativeKickstartDirPushButton_clicked();            ///< Select an Alternative Kickstart directory.
    void on_alernativeSaveStatesDirPushButton_clicked();            ///< Select an Alternative SaveStates directory.
    void on_alternativeFloppyOverlaysDirPushButton_clicked();       ///< Select an Alternative FloppyOverlay directory.
    void on_alternativeFlashMemoryDirPushButton_clicked();          ///< Select an Alternative FlashMemory directory.
    void on_alternativeControllersDirPushButton_clicked();          ///< Select an Alternative Controllers directory.
    void on_alternativeLogsDirPushButton_clicked();                 ///< Select an Alternative Logs directory.
    void on_alternativeHardDrivesDirPushButton_clicked();           ///< Select an Alternative HardDrivers directory.
    void on_alternativeCdromsDirPushButton_clicked();               ///< Select an Alternative Cdroms directory.
    void on_alternativeFloppiesDirPushButton_clicked();             ///< Select an Alternative Floppies directory.

    void on_grabMouseCheckBox_clicked();                            ///< Enable/disable mouse grabbing.
    void on_grabMouseAutoCheckBox_clicked();                        ///< Enable/disable automatic mouse grabbing.
    void on_useBSDCheckBox_clicked();                               ///< Enable/disable BSD.
    void on_audioBufferLineEdit_textChanged(const QString &arg1);   ///< Change size of audio buffer.
    void on_menuTitleLineEdit_textChanged(const QString &arg1);     ///< Change menu title.
    void on_menuSubtitleLineEdit_textChanged(const QString &arg1);  ///< Change menu subtitle.

    void on_serverIPLineEdit_textChanged(const QString &arg1);      ///< Set the server IP address.
    void on_serverPortLineEdit_textChanged(const QString &arg1);    ///< Set the server port.
    void on_playerUsernameLineEdit_textChanged(const QString &arg1);///< Set user's Username.
    void on_playerPasswordLineEdit_textChanged(const QString &arg1);///< Set user's password.

    void on_fadeColorPushButton_clicked();                          ///< Change the fade color
    void on_wallColor1PushButton_clicked();                         ///< Chaneg the first wall color
    void on_wallColor2PushButton_clicked();                         ///< Change the second wall color
    void on_floorColor1PushButton_clicked();                        ///< Change the first floor color
    void on_floorColor2PushButton_clicked();                        ///< Change the second wall color
    void on_headColorPushButton_clicked();                          ///< Change the head color
    void on_themeOverlayImagerPushButton_clicked();                 ///< Change the theme overlay image
    void on_themeFolderPushButton_clicked();                        ///< Change the theme folder
    void on_mouseSpeedLineEdit_textChanged(const QString &arg1);    ///< Change mouse speed

    void customJoystick0Slot(QString s);        ///< Custom slot for joystick 0 selection
    void customJoystick1Slot(QString s);        ///< Custom slot for joystick 1 selection
    void customJoystick2Slot(QString s);        ///< Custom slot for joystick 2 selection
    void customJoystick3Slot(QString s);        ///< Custom slot for joystick 3 selection

    void on_readKeyPushButton_clicked();        ///< Start reading keyboard

    void on_customInputMappingAddPushButton_clicked();                              ///< Add a custom keyboard mapping
    void on_customInputMappingRemovePushButton_clicked();                           ///< Remove a custom keyboard mapping
    void on_joystickPort0CustomizePushButton_clicked();                             ///< Customize joystick on port 0
    void on_joystickPort1CusomizePushButton_clicked();                              ///< Customize joystick on port 1
    void on_joystickPort2CustomizePushButton_clicked();                             ///< Customize joystick on port 2
    void on_joystickPort3CustomizePushButton_clicked();                             ///< Customize joystick on port 3
    void on_joystickPort0CustomJoystickRadioButton_clicked();                       ///< Select a Custom joystick on port 0
    void on_joystickPort1CustomJoystickRadioButton_clicked();                       ///< Select a Custom joystick on port 1
    void on_joystickPort2CustomJoystickRadioButton_clicked();                       ///< Select a Custom joystick on port 2
    void on_joystickPort3CustomJoystickRadioButton_clicked();                       ///< Select a Custom joystick on port 3
    void on_joystickPort0JoystickRadioButton_clicked();                             ///< Select an existing joystick on port 0
    void on_joystickPort1JoystickRadioButton_clicked();                             ///< Select an existing joystick on port 1
    void on_joystickPort2JoystickRadioButton_clicked();                             ///< Select an existing joystick on port 2
    void on_joystickPort3JoystickRadioButton_clicked();                             ///< Select an existing joystick on port 3
    void on_joystickPort0MouseRadioButton_clicked();                                ///< Select a mouse on port 0
    void on_joystickPort1MouseRadioButton_clicked();                                ///< Select a mouse on port 1
    void on_joystickPort2MouseRadioButton_clicked();                                ///< Select a mouse on port 2
    void on_joystickPort3MouseRadioButton_clicked();                                ///< Select a mouse on port 3
    void on_joystickPort0KeyboardRadioButton_clicked();                             ///< Select a keyboard on port 0
    void on_joystickPort1KeyboardRadioButton_clicked();                             ///< Select a keyboard on port 1
    void on_joystickPort2KeyboardRadioButton_clicked();                             ///< Select a keyboard on port 2
    void on_joystickPort3KeyboardRadioButton_clicked();                             ///< Select a keyboard on port 3
    void on_joystickPort0NothingRadioButton_clicked();                              ///< Select nothing on port 0
    void on_joystickPort1NothingRadioButton_clicked();                              ///< Select nothing on port 1
    void on_joystickPort2NothingRadioButton_clicked();                              ///< Select nothing on port 2
    void on_joystickPort3NothingRadioButton_clicked();                              ///< Select nothing on port 3
    void on_joystickPort0ModelComboBox_currentIndexChanged(const QString &arg1);    ///< Select an existing joystick on port 0
    void on_joystickPort1ModelComboBox_currentIndexChanged(const QString &arg1);    ///< Select an existing joystick on port 1
    void on_joystickPort2ModelComboBox_currentIndexChanged(const QString &arg1);    ///< Select an existing joystick on port 2
    void on_joystickPort3ModelComboBox_currentIndexChanged(const QString &arg1);    ///< Select an existing joystick on port 3

private:
    Ui::Amiga *ui;                              ///< Amiga main window
    ConfigChipset chipsetConfiguration;         ///< Chipset configuration
    ConfigRam ramConfiguration;                 ///< RAM configuration
    ConfigFloppy floppyConfiguration;           ///< Floppy configuration
    ConfigCDRom cdromConfiguration;             ///< CDROM configuraion
    ConfigHardDisks hardDiskConfiguration;      ///< Hard Disks configuration
    ConfigInput inputConfiguration;             ///< Input configuration
    ConfigGraphics graphicsConfiguration;       ///< Graphics configuration
    ConfigTheme themeConfiguration;             ///< Theme configuration
    ConfigMisc miscConfiguration;               ///< Misc configuration

    /**
      * Check if FS-UAE folder exists
      */
    void checkFoldersExistence();
    /** \brief Process a line read from file and store the setting
         * \param line to be processed
         */
    void parseLine(string line);
    /** \brief Verify the consistency of configuration \n
         * Checks if the current configuration is valid. For example if the selected model has not a CD drive, user can't have selected a CD iso image.
         */
    void checkConfigurationConsistency();
    /** \brief Enable/disable Fast Memory radio buttons
         * \param state can be true (disable) or false (enable)
         */
    void setFastMemoryDisabled(bool state);
    /** \brief Enable/disable Zorro III radio buttons
         * \param state can be true (disable) or false (enable)
         */
    void setZorroIIIMemoryDisabled(bool state);

    void updateGraphicsFromInternalConfiguration(); ///< Read the internal configuration and update Gui
    /** \brief Save current configuration in a file fileName. Please note that parameters set to default values are not stored in the file.
         * \param fileName is the name of the file
         */
    void saveConfigInFile(string fileName);
    void loadDefaultValues();                       ///< Set all the parameter to the default values
    /** \brief Checks if parameterName is an existing parameter
         * \param parameterName is the name of the parameter to be checked
         * \return true if the parameterName is the name of an existing parameter
         */
    bool isExistingParameter(string parameterName);

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // AMIGA_H
