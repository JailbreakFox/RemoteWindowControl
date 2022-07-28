#ifndef SERVER_MAINWINDOW_H
#define SERVER_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class Controlled;
class ServerMainWindow : public QMainWindow {
    Q_OBJECT

   public:
    ServerMainWindow(QMainWindow *parent = 0);
    ~ServerMainWindow();

   private:
    Controlled *m_server;
};

#endif  // SERVER_MAINWINDOW_H
