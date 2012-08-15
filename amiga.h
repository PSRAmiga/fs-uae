/*! \mainpage A Gui designed to simplify the creation of Amiga configuration file
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
/// Create a new main window: Amiga Gui
namespace Ui {
class Amiga;
}
/// This class is responsible for the magement of FS-UAE Gui
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
    void on_accuracyLeastRadio_clicked();   ///< Click to least accuracy.
    void on_accuracyNormalRadio_clicked();  ///< Click to normal accuracy.
    void on_accuracyMostadio_clicked();     ///< Click to most accuracy.
    void on_videoModePALRadio_clicked();    ///< Click to PAL video mode.
    void on_videoModeNTSCRadio_clicked();   ///< Click to NTST video mode.

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

    void on_hardDrive0LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 0.
    void on_hardDrive1LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 1.
    void on_hardDrive2LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 2.
    void on_hardDrive3LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 3.
    void on_hardDrive4LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 4.
    void on_hardDrive5LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 5.
    void on_hardDrive6LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 6.
    void on_hardDrive7LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 7.
    void on_hardDrive8LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 8.
    void on_hardDrive9LabelLineEdit_textChanged(const QString &arg1);///< Type here a new label of Hard Disk stored in Drive 9.

    void on_hardDrive0ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive1ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive2ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive3ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive4ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive5ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive6ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive7ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive8ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_hardDrive9ReadOnlyCheckBox_clicked();///< Zorro III memory setting at 256Mb.

    void on_displaySettingsStartFullscreenRadioButton_clicked();    ///< Zorro III memory setting at 256Mb.
    void on_displaySettingsResizableRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_displaySettingsKeepAspectRatioRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_scanlinesRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_scanlinesRTGRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_lowResolutionRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_lineDoublingRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_fullscreenResolutionXSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_fullscreenResolutionYSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_windowResolutionXSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_windowResolutionYSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_scaleXDoubleSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_scaleYDoubleSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_alignXdoubleSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_alignYDoubleSpinBox_valueChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_scanlinesDarkHorizontalSlider_valueChanged(int position);///< Zorro III memory setting at 256Mb.
    void on_scanlinesLightHorizontalSlider_valueChanged(int position);///< Zorro III memory setting at 256Mb.
    void on_fullSceneAntiAliasingOffRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_fullSceneAntiAliasing2xRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_fullSceneAntiAliasing4xRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_fullSceneAntiAliasing8xRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_textureFilterLinearRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_textureFilterNearestRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_f11InitalModeAutoRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_f11InitalModeFullRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_f11InitalMode640x400RadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_f11InitalMode640x480RadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_f11InitalMode640x512RadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_f11InitialModeWithBorderCheckBox_clicked();///< Zorro III memory setting at 256Mb.
    void on_videoFormatBGRARadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_videoFormatRGBARadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_textureFormatModeRGBRadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_textureFormatModeRGB8RadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_textureFormatModeRGBARadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_textureFormatModeRGBA8RadioButton_clicked();///< Zorro III memory setting at 256Mb.
    void on_shaderComboBox_currentIndexChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_videoSyncComboBox_currentIndexChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.
    void on_videoSynkMethodeComboBox_currentIndexChanged(const QString &arg1);///< Zorro III memory setting at 256Mb.

    void on_viewportIn1LineEdit_textChanged(const QString &arg1);
    void on_viewportIn2LineEdit_textChanged(const QString &arg1);
    void on_viewportIn3LineEdit_textChanged(const QString &arg1);
    void on_viewportIn4LineEdit_textChanged(const QString &arg1);
    void on_viewportOut1LineEdit_textChanged(const QString &arg1);
    void on_viewportOut2LineEdit_textChanged(const QString &arg1);
    void on_viewportOut3LineEdit_textChanged(const QString &arg1);
    void on_viewportOut4LineEdit_textChanged(const QString &arg1);

    void on_alternativeBaseDirPushButton_clicked();
    void on_alternativeKickstartDirPushButton_clicked();
    void on_alernativeSaveStatesDirPushButton_clicked();
    void on_alternativeFloppyOverlaysDirPushButton_clicked();
    void on_alternativeFlashMemoryDirPushButton_clicked();
    void on_alternativeControllersDirPushButton_clicked();
    void on_alternativeLogsDirPushButton_clicked();
    void on_alternativeHardDrivesDirPushButton_clicked();
    void on_alternativeCdromsDirPushButton_clicked();
    void on_alternativeFloppiesDirPushButton_clicked();

    void on_grabMouseCheckBox_clicked();
    void on_grabMouseAutoCheckBox_clicked();
    void on_useBSDCheckBox_clicked();
    void on_audioBufferLineEdit_textChanged(const QString &arg1);
    void on_menuTitleLineEdit_textChanged(const QString &arg1);
    void on_menuSubtitleLineEdit_textChanged(const QString &arg1);

    void on_serverIPLineEdit_textChanged(const QString &arg1);
    void on_serverPortLineEdit_textChanged(const QString &arg1);
    void on_playerUsernameLineEdit_textChanged(const QString &arg1);
    void on_playerPasswordLineEdit_textChanged(const QString &arg1);

    void on_fadeColorPushButton_clicked();
    void on_wallColor1PushButton_clicked();
    void on_wallColor2PushButton_clicked();
    void on_floorColor1PushButton_clicked();
    void on_floorColor2PushButton_clicked();
    void on_headColorPushButton_clicked();
    void on_themeOverlayImagerPushButton_clicked();
    void on_themeFolderPushButton_clicked();
    void on_mouseSpeedLineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();
    void keyPressEvent(QKeyEvent *e);

    void on_readKeyPushButton_clicked();

    void on_customInputMappingAddPushButton_clicked();

    void on_customInputMappingRemovePushButton_clicked();

private:
    Ui::Amiga *ui;
    ConfigChipset chipsetConfiguration;
    ConfigRam ramConfiguration;
    ConfigFloppy floppyConfiguration;
    ConfigCDRom cdromConfiguration;
    ConfigHardDisks hardDiskConfiguration;
    ConfigInput inputConfiguration;
    ConfigGraphics graphicsConfiguration;
    ConfigTheme themeConfiguration;
    ConfigMisc miscConfiguration;

    void parseLine(string line);
    void checkConfigurationConsistency();

    void setFastMemoryDisabled(bool state);
    void setZorroIIIMemoryDisabled(bool state);

    void updateGraphicsFromInternalConfiguration();
    int getConfigurationAreaFromParameterName(string parameterName);
    void saveConfigInFile(string fileName);
    void loadDefaultValues();

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // AMIGA_H
