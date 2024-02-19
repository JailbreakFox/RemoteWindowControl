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

void SystemApi::mousePress(const QPointF &pos)
{
    int pos_x = static_cast<int>(pos.x());
    int pos_y = static_cast<int>(pos.y());

#ifdef Q_OS_WIN
    DWORD x = static_cast<DWORD>(pos_x * 65536 / GetSystemMetrics(SM_CXSCREEN));
    DWORD y = static_cast<DWORD>(pos_y * 65536 / GetSystemMetrics(SM_CYSCREEN));
    mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
#else
    QCursor::setPos(pos_x, pos_y);
#endif
}

void SystemApi::mouseRelease(const QPointF &pos)
{
    int pos_x = static_cast<int>(pos.x());
    int pos_y = static_cast<int>(pos.y());

#ifdef Q_OS_WIN
    DWORD x = static_cast<DWORD>(pos_x * 65536 / GetSystemMetrics(SM_CXSCREEN));
    DWORD y = static_cast<DWORD>(pos_y * 65536 / GetSystemMetrics(SM_CYSCREEN));
    mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
#else
    QCursor::setPos(pos_x, pos_y);
#endif
}

void SystemApi::mouseMove(const QPointF &pos)
{
    int pos_x = static_cast<int>(pos.x());
    int pos_y = static_cast<int>(pos.y());

#ifdef Q_OS_WIN
    DWORD x = static_cast<DWORD>(pos_x * 65536 / GetSystemMetrics(SM_CXSCREEN));
    DWORD y = static_cast<DWORD>(pos_y * 65536 / GetSystemMetrics(SM_CYSCREEN));
    mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
#else
    QCursor::setPos(pos_x, pos_y);
#endif
}

int translateKeyCode(int key)
{
    int k = key;
    bool legal = true;
    if(k >= Qt::Key_0 && k <= Qt::Key_9)
    {
    }
    else if(k >= Qt::Key_A && k <= Qt::Key_Z)
    {
    }
    else if(k >= Qt::Key_F1 && k <= Qt::Key_F24)
    {
        k &= 0x000000ff;
        k += 0x40;
    }
    else if(k == Qt::Key_Tab)
    {
        k = 0x09;
    }
    else if(k == Qt::Key_Backspace)
    {
        k = 0x08;
    }
    else if(k == Qt::Key_Return)
    {
        k = 0x0d;
    }
    else if(k <= Qt::Key_Down && k >= Qt::Key_Left)
    {
        int off = k - Qt::Key_Left;
        k = 0x25 + off;
    }
    else if(k == Qt::Key_Shift)
    {
        k = 0x10;
    }
    else if(k == Qt::Key_Control)
    {
        k = 0x11;
    }
    else if(k == Qt::Key_Alt)
    {
        k = 0x12;
    }
    else if(k == Qt::Key_Meta)
    {
        k = 0x5b;
    }
    else if(k == Qt::Key_Insert)
    {
        k = 0x2d;
    }
    else if(k == Qt::Key_Delete)
    {
        k = 0x2e;
    }
    else if(k == Qt::Key_Home)
    {
        k = 0x24;
    }
    else if(k == Qt::Key_End)
    {
        k = 0x23;
    }
    else if(k == Qt::Key_PageUp)
    {
        k = 0x21;
    }
    else if(k == Qt::Key_Down)
    {
        k = 0x22;
    }
    else if(k == Qt::Key_CapsLock)
    {
        k = 0x14;
    }
    else if(k == Qt::Key_NumLock)
    {
        k = 0x90;
    }
    else if(k == Qt::Key_Space)
    {
        k = 0x20;
    }
    else
        legal = false;

    if(!legal)
        return 0;
    return k;
}

void SystemApi::keyInput(const QPointF &key)
{
#ifdef Q_OS_WIN
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = static_cast<WORD>(translateKeyCode(static_cast<int>(key.x())));
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
#else
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
