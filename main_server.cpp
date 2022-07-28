#include <QApplication>

#include "server_mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ServerMainWindow w;
    w.setWindowTitle("Server");
    w.move(800, 600);
    w.show();

    return a.exec();
}
