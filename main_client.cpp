#include <QApplication>

#include "client_mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ClientMainWindow w;
    w.setWindowTitle("Client");
    w.move(800, 600);
    w.show();

    return a.exec();
}
