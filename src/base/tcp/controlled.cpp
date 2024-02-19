#include "controlled.h"

#include <QBuffer>
#include <QGuiApplication>
#include <QScreen>
#include <QTime>

#include "remoteevent.h"
#include "socket.h"
#include "systemapi.h"

Controlled::Controlled(QObject *parent) : QTcpServer(parent) {
    // 监听本地的43800端口
    listen(QHostAddress::Any, 43800);
}

Controlled::~Controlled() {}

void Controlled::finish() {
    if (m_controlled) m_controlled->abort();
}

void Controlled::processEvent(const RemoteEvent &ev)
{
    switch (ev.type()) {
        case RemoteEvent::EventType::Pressed:
            SystemApi::mousePress(ev.position());
            break;
        case RemoteEvent::EventType::Released:
            SystemApi::mouseRelease(ev.position());
            break;
        case RemoteEvent::EventType::Moved:
            SystemApi::mouseMove(ev.position());
            break;
        case RemoteEvent::EventType::KeyInput:
            SystemApi::keyInput(ev.position());
            break;
        default:
            break;
    }
}

void Controlled::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    if (m_controlled) {
        QBuffer buffer;
        buffer.open(QIODevice::WriteOnly);
        QTime time = QTime::currentTime();
        QPixmap pixmap = SystemApi::grabScreen();
        // qDebug() << time.msecsTo(QTime::currentTime());
        pixmap.save(&buffer, "jpg", -1);
        BlockHeader header = {SCREEN_TYPE, qint32(buffer.size())};
        DataBlock data = {header, buffer.data()};
        m_controlled->writeToSocket(data);
    }
}

void Controlled::incomingConnection(qintptr socketDescriptor) {
    if (!m_controlled) {
        m_controlled = new Socket;
        connect(m_controlled, &Socket::stateChanged, this,
                [this](QAbstractSocket::SocketState socketState) {
                    switch (socketState) {
                        case QAbstractSocket::ConnectedState:
                            emit connected();
                            break;
                        default:
                            break;
                    }
                });
        connect(m_controlled, &Socket::disconnected, this, [this]() {
            Socket *socket = m_controlled;
            m_controlled = nullptr;
            socket->deleteLater();
            killTimer(m_timerId);
            m_timerId = 0;
            emit disconnected();
        });
        connect(m_controlled, &Socket::hasEventData, this,
                [this](const RemoteEvent &event) { processEvent(event); });
        m_controlled->setSocketDescriptor(socketDescriptor);

        if (!m_timerId) m_timerId = startTimer(30);
    }
}
