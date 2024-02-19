#include "client_mainwindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

#include "imageprovider.h"
#include "tcp/controller.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 800
#define REMOTE_IP "192.168.1.157"

ClientMainWindow::ClientMainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    this->setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QWidget *content = new QWidget(this);
    content->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *layout = new QVBoxLayout(content);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_label = new QLabel(this);
    m_label->setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    this->setCentralWidget(content);
    layout->addWidget(m_label);
    this->setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
    m_label->setMouseTracking(true);

    m_controller = new Controller(this);
    m_provider = m_controller->getImageProvider();

    if (m_controller) m_controller->requestNewConnection(REMOTE_IP);

    connect(m_controller, &Controller::needUpdate, this, [=]()
    {
        if (m_provider)
        {
            QPixmap pixmap = m_provider->requestPixmap("", QSize(0, 0));
            if (m_label)
            {
                this->setFixedSize(pixmap.size());
                m_label->setPixmap(pixmap);
            }
        }
    });
}

ClientMainWindow::~ClientMainWindow()
{

}

void ClientMainWindow::mousePressEvent(QMouseEvent *event)
{
    QPointF relativePos = event->pos();
    m_controller->mousePressed(relativePos);
}

void ClientMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF relativePos = event->pos();
    m_controller->mouseReleased(relativePos);
}

void ClientMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPointF relativePos = event->pos();
    m_controller->mouseMoved(relativePos);
}

void ClientMainWindow::keyPressEvent(QKeyEvent *event)
{
    m_controller->keyInput(event->key());
}
