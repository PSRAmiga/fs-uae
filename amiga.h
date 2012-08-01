#ifndef AMIGA_H
#define AMIGA_H

#include <QMainWindow>
#include <configchipset.h>
#include <configram.h>
#include <configfloppy.h>
#include <configcdrom.h>
#include <configharddisks.h>
#include <configgraphics.h>

namespace Ui {
class Amiga;
}

class Amiga : public QMainWindow
{
    Q_OBJECT

    
public:
    explicit Amiga(QWidget *parent = 0);
    ~Amiga();

private slots:
    void on_saveConfigToolButton_clicked();
    void on_loadConfigToolButton_clicked();
    void on_loadDefaultValuesToolButton_clicked();
    void on_runConfigButton_clicked();

    void on_actionAmiga_triggered();
    void on_actionSummary_triggered();
    void on_actionReport_bug_triggered();

    void on_kickstartFileToolButton_clicked();
    void on_kickstartExtFileToolButton_clicked();
    void on_amigaModelComboBox_currentIndexChanged(const QString &arg1);
    void on_accuracyLeastRadio_clicked();
    void on_accuracyNormalRadio_clicked();
    void on_accuracyMostadio_clicked();
    void on_videoModePALRadio_clicked();
    void on_videoModeNTSCRadio_clicked();

    void on_chipMem4MbRadio_clicked();
    void on_chipMeme8MbRadio_clicked();
    void on_chipMem512KbRadio_clicked();
    void on_chipMem1MbRadio_clicked();
    void on_chipMem2MbRadio_clicked();
    void on_slowMemNoneRadio_clicked();
    void on_slowMem512KbRadio_clicked();
    void on_slowMem1MbRadio_clicked();
    void on_slowMem1_8MbRadio_clicked();
    void on_fastMemNoneRadio_clicked();
    void on_fastMem1MbRadio_clicked();
    void on_fastMem2MbRadio_clicked();
    void on_fastMem4MbRadio_clicked();
    void on_fastMem8MbRadio_clicked();
    void on_z3MemNoneRadio_clicked();
    void on_z3Mem1MbRadio_clicked();
    void on_z3Mem2MbRadio_clicked();
    void on_z3Mem4MbRadio_clicked();
    void on_z3Mem8MbRadio_clicked();
    void on_z3Mem16MbRadio_clicked();
    void on_z3Mem32MbRadio_clicked();
    void on_z3Mem64MbRadio_clicked();
    void on_z3Mem128MbRadio_clicked();
    void on_z3Mem256MbRadio_clicked();

    void on_floppyDrive0ToolButton_clicked();
    void on_floppySwappingImagesAddPushButton_clicked();
    void on_floppyDriveVolumeSlider_valueChanged(int value);
    void on_floppyDriveVolumeMuteCheckBox_clicked();
    void on_floppyDriveSpeedSlider_valueChanged(int position);
    void on_floppyDrive1ToolButton_clicked();
    void on_floppyDrive2ToolButton_clicked();
    void on_floppyDrive3ToolButton_clicked();
    void on_floppySwappingImagerRemovePushButton_clicked();

    void on_cdromDrive0ToolButton_clicked();
    void on_cdromSwappingImagesAddPushButton_clicked();
    void on_cdromSwappingImagesRemovePushButton_clicked();

    void on_hardDrive0FolderToolButton_clicked();
    void on_hardDrive0ToolButton_clicked();
    void on_hardDrive1ToolButton_clicked();
    void on_hardDrive1FolderToolButton_clicked();
    void on_hardDrive2ToolButton_clicked();
    void on_hardDrive2FolderToolButton_clicked();
    void on_hardDrive3ToolButton_clicked();
    void on_hardDrive3FolderToolButton_clicked();
    void on_hardDrive4FolderToolButton_clicked();
    void on_hardDrive4ToolButton_clicked();
    void on_hardDrive5ToolButton_clicked();
    void on_hardDrive5FolderToolButton_clicked();
    void on_hardDrive6ToolButton_clicked();
    void on_hardDrive6FolderToolButton_clicked();
    void on_hardDrive7ToolButton_clicked();
    void on_hardDrive7FolderToolButton_clicked();
    void on_hardDrive8ToolButton_clicked();
    void on_hardDrive8FolderToolButton_clicked();
    void on_hardDrive9ToolButton_clicked();
    void on_hardDrive9FolderToolButton_clicked();

    void on_hardDrive0LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive1LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive2LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive3LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive4LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive5LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive6LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive7LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive8LabelLineEdit_textChanged(const QString &arg1);
    void on_hardDrive9LabelLineEdit_textChanged(const QString &arg1);

    void on_hardDrive0ReadOnlyCheckBox_clicked();
    void on_hardDrive1ReadOnlyCheckBox_clicked();
    void on_hardDrive2ReadOnlyCheckBox_clicked();
    void on_hardDrive3ReadOnlyCheckBox_clicked();
    void on_hardDrive4ReadOnlyCheckBox_clicked();
    void on_hardDrive5ReadOnlyCheckBox_clicked();
    void on_hardDrive6ReadOnlyCheckBox_clicked();
    void on_hardDrive7ReadOnlyCheckBox_clicked();
    void on_hardDrive8ReadOnlyCheckBox_clicked();
    void on_hardDrive9ReadOnlyCheckBox_clicked();

    void on_displaySettingsStartFullscreenRadioButton_clicked();
    void on_displaySettingsResizableRadioButton_clicked();
    void on_displaySettingsKeepAspectRatioRadioButton_clicked();
    void on_scanlinesRadioButton_clicked();
    void on_scanlinesRTGRadioButton_clicked();
    void on_lowResolutionRadioButton_clicked();
    void on_lineDoublingRadioButton_clicked();
    void on_fullscreenResolutionXSpinBox_valueChanged(const QString &arg1);
    void on_fullscreenResolutionYSpinBox_valueChanged(const QString &arg1);
    void on_windowResolutionXSpinBox_valueChanged(const QString &arg1);
    void on_windowResolutionYSpinBox_valueChanged(const QString &arg1);
    void on_scaleXDoubleSpinBox_valueChanged(const QString &arg1);
    void on_scaleYDoubleSpinBox_valueChanged(const QString &arg1);
    void on_alignXdoubleSpinBox_valueChanged(const QString &arg1);
    void on_alignYDoubleSpinBox_valueChanged(const QString &arg1);
    void on_scanlinesDarkHorizontalSlider_valueChanged(int position);
    void on_scanlinesLightHorizontalSlider_valueChanged(int position);
    void on_fullSceneAntiAliasingOffRadioButton_clicked();
    void on_fullSceneAntiAliasing2xRadioButton_clicked();
    void on_fullSceneAntiAliasing4xRadioButton_clicked();
    void on_fullSceneAntiAliasing8xRadioButton_clicked();
    void on_textureFilterLinearRadioButton_clicked();
    void on_textureFilterNearestRadioButton_clicked();
    void on_f11InitalModeAutoRadioButton_clicked();
    void on_f11InitalModeFullRadioButton_clicked();
    void on_f11InitalMode640x400RadioButton_clicked();
    void on_f11InitalMode640x480RadioButton_clicked();
    void on_f11InitalMode640x512RadioButton_clicked();
    void on_f11InitialModeWithBorderCheckBox_clicked();
    void on_videoFormatBGRARadioButton_clicked();
    void on_videoFormatRGBARadioButton_clicked();
    void on_textureFormatModeRGBRadioButton_clicked();
    void on_textureFormatModeRGB8RadioButton_clicked();
    void on_textureFormatModeRGBARadioButton_clicked();
    void on_textureFormatModeRGBA8RadioButton_clicked();
    void on_shaderComboBox_currentIndexChanged(const QString &arg1);
    void on_videoSyncComboBox_currentIndexChanged(const QString &arg1);
    void on_videoSynkMethodeComboBox_currentIndexChanged(const QString &arg1);

    void on_alternativeBaseDirPushButton_clicked();
    void on_fadeColorPushButton_clicked();

private:
    Ui::Amiga *ui;
    ConfigChipset chipsetConfiguration;
    ConfigRam ramConfiguration;
    ConfigFloppy floppyConfiguration;
    ConfigCDRom cdromConfiguration;
    ConfigHardDisks hardDiskConfiguration;
    ConfigGraphics graphicsConfiguration;

    void parseLine(string line);
    bool checkConfigurationConsistency();

    void setFastMemoryDisabled(bool state);
    void setZorroIIIMemoryDisabled(bool state);

    void updateGraphicsFromInternalConfiguration();
    int getConfigurationAreaFromParameterName(string parameterName);
    void saveConfigInFile(string fileName);
};

#endif // AMIGA_H
