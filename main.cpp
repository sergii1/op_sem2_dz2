#include "xmlview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMLView w;
    w.resize(400, 800);
    w.show();

    return a.exec();
}
