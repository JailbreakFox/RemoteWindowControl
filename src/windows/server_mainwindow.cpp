#include "server_mainwindow.h"

#include <QMessageBox>
#include <QPushButton>

#include "tcp/controlled.h"

ServerMainWindow::ServerMainWindow(QMainWindow *parent) : QMainWindow(parent) {
    //创建一个PushButton
    QPushButton *btn = new QPushButton(tr("Stop Connection"), this);

    m_server = new Controlled(this);

    connect(btn, &QPushButton::clicked, m_server, &Controlled::finish);
}

ServerMainWindow::~ServerMainWindow() {}
