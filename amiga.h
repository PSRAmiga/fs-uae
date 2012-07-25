#ifndef AMIGA_H
#define AMIGA_H

#include <QMainWindow>
#include <configchipset.h>

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


    void on_actionReport_bug_triggered();

private:
    Ui::Amiga *ui;
    ConfigChipset configChipset;
    void parseLine(string line);
    void updateGraphicsFromInternalConfiguration();
};

#endif // AMIGA_H
