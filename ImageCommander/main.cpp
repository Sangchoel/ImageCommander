#include "ImageCommander.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageCommander w;
    w.show();
    return a.exec();
}
