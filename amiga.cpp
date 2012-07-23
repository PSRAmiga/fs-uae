#include "amiga.h"
#include "ui_amiga.h"
#include <QFileDialog>

Amiga::Amiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amiga)
{
    ui->setupUi(this);
}

Amiga::~Amiga()
{
    delete ui;
}




void Amiga::on_loadKickstartDirButt_clicked()
{
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks); show anly dir
    QString fileName=QFileDialog::getOpenFileName(this, tr("open file"), "/", tr("Image adf/rom(*.adf *.rom)")); //
    ui->kickstartDir->setText(fileName);

}
