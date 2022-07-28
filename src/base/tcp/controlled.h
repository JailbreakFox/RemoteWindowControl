#ifndef CONTROLLED_H
#define CONTROLLED_H

#include <QObject>
#include <QTcpServer>

#include "protocol.h"

class Socket;
class RemoteEvent;
class Controlled : public QTcpServer {
    Q_OBJECT

   public:
    explicit Controlled(QObject *parent = nullptr);
    ~Controlled();

    void finish();

   signals:
    void connected();
    void disconnected();

   public slots:
    void processEvent(const RemoteEvent &ev);

   protected:
    void timerEvent(QTimerEvent *event);
    void incomingConnection(qintptr socketDescriptor);

   private:
    Socket *m_controlled = nullptr;
    int m_timerId = 0;
};

#endif  // CONTROLLED_H
