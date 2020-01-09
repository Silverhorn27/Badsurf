#include <unistd.h>
#include "Widgets/Application/Application.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application app;
    QApplication::addLibraryPath("/lib");

//    if (getuid()) {
//        QMessageBox::critical(&app, "Error!", "Fuck you pidor! Start program with root!");
//        return 1;
//    }


    app.show();
    return a.exec();
}
