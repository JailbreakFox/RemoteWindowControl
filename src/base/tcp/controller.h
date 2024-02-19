#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "remoteevent.h"

class Socket;
class ImageProvider;
class Controller : public QObject {
    Q_OBJECT
   public:
    explicit Controller(QObject *parent = nullptr);

    ImageProvider *getImageProvider() { return m_provider; }

    void finish();
    void mousePressed(const QPointF &position);
    void mouseReleased(const QPointF &position);
    void mouseMoved(const QPointF &position);
    void keyInput(int key);
    void requestNewConnection(const QString &address);

signals:
    void connected();
    void disconnected();
    void needUpdate();

   private:
    inline void sendRemoteEvent(RemoteEvent::EventType type,
                                const QPointF &position);

    Socket *m_socket;
    ImageProvider *m_provider;
};

#endif  // CONTROLLER_H
