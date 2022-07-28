#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class QLabel;
class Controller;
class ImageProvider;
class ClientMainWindow : public QMainWindow {
    Q_OBJECT

   public:
    ClientMainWindow(QMainWindow* parent = 0);
    ~ClientMainWindow();

   private:
    QLabel* m_label;
    Controller* m_controller;
    ImageProvider* m_provider;
};

#endif  // CLIENT_MAINWINDOW_H
