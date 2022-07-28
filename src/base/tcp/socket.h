#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>

#include "protocol.h"

class RemoteEvent;
class Socket : public QTcpSocket {
    Q_OBJECT
   public:
    explicit Socket(QObject *parent = nullptr);
    ~Socket();

    void abort();
    void connectHost(const QHostAddress &host, quint16 port) {
        QTcpSocket::connectToHost(host, port);
    }
    void writeToSocket(const QByteArray &block) { write(block); }
    void writeToSocket(const DataBlock &block);
    void writeToSocket(const RemoteEvent &event);

   signals:
    void hasScreenData(const QByteArray &screenData);
    void hasEventData(const RemoteEvent &event);

   private:
    void processRecvBlock();

    QByteArray m_recvData;
    BlockHeader m_recvHeader;
};

#endif  // SOCKET_H
