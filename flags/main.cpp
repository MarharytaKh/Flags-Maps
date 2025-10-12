#include "flags.h"
#include "DialogStart.h"
#include <iostream>
#include <filesystem>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{   
    QApplication app(argc, argv);
    DialogStart windowSt;
    windowSt.show();
    return app.exec();

}
