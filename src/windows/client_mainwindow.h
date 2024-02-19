#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>

class QLabel;
class Controller;
class ImageProvider;
class ClientMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ClientMainWindow(QMainWindow* parent = nullptr);
    ~ClientMainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QLabel* m_label;
    Controller* m_controller;
    ImageProvider* m_provider;
};

#endif  // CLIENT_MAINWINDOW_H
