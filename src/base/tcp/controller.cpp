#include "controller.h"

#include <QGuiApplication>
#include <QHostAddress>

#include "imageprovider.h"
#include "socket.h"

Controller::Controller(QObject *parent) : QObject(parent) {
    m_provider = new ImageProvider;

    m_socket = new Socket;
    connect(m_socket, &Socket::connected, this, &Controller::connected);
    connect(m_socket, &Socket::disconnected, this, &Controller::disconnected);
    connect(m_socket, &Socket::hasScreenData, this,
            [this](const QByteArray &screenData) {
                QPixmap pixmap;
                pixmap.loadFromData(screenData);
                m_provider->setPixmap(pixmap);
                Q_EMIT needUpdate();
            });
}

void Controller::finish() { m_socket->abort(); }

void Controller::mousePressed(const QPointF &position) {
    sendRemoteEvent(RemoteEvent::EventType::Pressed, position);
}

void Controller::mouseReleased(const QPointF &position) {
    sendRemoteEvent(RemoteEvent::EventType::Released, position);
}

void Controller::mouseMoved(const QPointF &position) {
    sendRemoteEvent(RemoteEvent::EventType::Moved, position);
}

void Controller::requestNewConnection(const QString &address) {
    QHostAddress hostAddress(address);
    m_socket->abort();
    m_socket->connectHost(hostAddress, 43800);
}

void Controller::sendRemoteEvent(RemoteEvent::EventType type,
                                 const QPointF &position) {
    RemoteEvent event(type, position);
    m_socket->writeToSocket(event);
}
