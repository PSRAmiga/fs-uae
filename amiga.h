#ifndef AMIGA_H
#define AMIGA_H

#include <QMainWindow>

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
    void on_loadKickstartDirButt_clicked();

private:
    Ui::Amiga *ui;
};

#endif // AMIGA_H
