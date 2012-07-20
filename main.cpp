#include <QtGui/QApplication>
#include "amiga.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Amiga w;
    w.show();
    
    return a.exec();
}
