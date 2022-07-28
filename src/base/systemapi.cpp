#include "systemapi.h"

#include <QCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QPainter>
#include <QScreen>
#include <QWindow>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

void SystemApi::mousePress(const QPointF &pos) {
    QCursor::setPos(int(pos.x()), int(pos.y()));
#ifdef Q_OS_WIN
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
#else
    // TODO: linux鼠标press事件
#endif
}

void SystemApi::mouseRelease(const QPointF &pos) {
    QCursor::setPos(int(pos.x()), int(pos.y()));
#ifdef Q_OS_WIN
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
#else
    // TODO: linux鼠标release事件
#endif
}

void SystemApi::mouseMove(const QPointF &pos) {
    QCursor::setPos(int(pos.x()), int(pos.y()));
#ifdef Q_OS_WIN
    mouse_event(MOUSEEVENTF_MOVE, 0, 0, 0, 0);
#endif
}

QPixmap SystemApi::grabScreen() {
    QPixmap screen;

    screen = QGuiApplication::primaryScreen()->grabWindow(0);

    if (!screen.isNull()) {
        QPainter painter(&screen);
        painter.drawPixmap(QCursor::pos(), grabCursor());
    }

    return screen;
}

QPixmap SystemApi::grabCursor() {
    QPixmap cursorPixmap;
    cursorPixmap.load(":/res/cursor.png");
    return cursorPixmap;
}
