#include "client_mainwindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "imageprovider.h"
#include "tcp/controller.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700
#define REMOTE_IP "127.0.0.1"

ClientMainWindow::ClientMainWindow(QMainWindow *parent) : QMainWindow(parent) {
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT + 50);

    QWidget *content = new QWidget(this);
    content->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *layout = new QVBoxLayout(content);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_label = new QLabel(this);
    m_label->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //创建一个PushButton
    QPushButton *btn = new QPushButton(tr("start connect"), this);

    this->setCentralWidget(content);
    layout->addWidget(m_label);
    layout->addWidget(btn);

    m_controller = new Controller(this);
    m_provider = m_controller->getImageProvider();

    connect(btn, &QPushButton::clicked, this, [=]() {
        if (m_controller) m_controller->requestNewConnection(REMOTE_IP);
    });

    connect(m_controller, &Controller::needUpdate, this, [=]() {
        if (m_provider) {
            QPixmap pixmap = m_provider->requestPixmap("", m_label->size());
            if (m_label) {
                m_label->setPixmap(pixmap);
            }
        }
    });
}

ClientMainWindow::~ClientMainWindow() {}
