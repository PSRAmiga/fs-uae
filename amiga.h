#ifndef AMIGA_H
#define AMIGA_H

#include <QMainWindow>
#include <configchipset.h>
#include <configram.h>

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

    void on_kickstartFileToolButton_clicked();

    void on_kickstartExtFileToolButton_clicked();

    void on_amigaModelComboBox_currentIndexChanged(const QString &arg1);

    void on_accuracyLeastRadio_clicked();

    void on_accuracyNormalRadio_clicked();

    void on_accuracyMostadio_clicked();

    void on_saveConfigToolButton_clicked();

    void on_loadConfigToolButton_clicked();

    void on_videoModePALRadio_clicked();

    void on_videoModeNTSCRadio_clicked();

    void on_fadeColorPushButton_clicked();

    void on_loadDefaultValuesToolButton_clicked();

    void on_actionReport_bug_triggered();

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

    void on_runConfigButton_clicked();

    void on_actionAmiga_triggered();

    void on_actionSummary_triggered();

private:
    Ui::Amiga *ui;
    ConfigChipset chipsetConfiguration;
    ConfigRam ramConfiguration;

    void parseLine(string line);
    void setFastMemoryDisabled(bool state);
    void updateGraphicsFromInternalConfiguration();
    int getConfigurationAreaFromParameterName(string parameterName);
    void saveConfigInFile(string fileName);
};

#endif // AMIGA_H
