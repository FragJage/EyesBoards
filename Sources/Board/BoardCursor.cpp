#include "BoardCursor.h"
#include <QPainter>

BoardCursor::BoardCursor(QWidget *parent, Qt::WindowFlags f) : QFrame(parent, f)
{
    setStyleSheet("QFrame { border: 2px solid red; border-radius: 10px;}");
    setGeometry(5, 5, 20, 20);

    m_ProgressClick = 0;
    m_ClickTimer = new QTimer(this);
    m_HoverTimer = new QTimer(this);
    connect(m_ClickTimer, SIGNAL(timeout()), this, SLOT(ClickingTimerSlot()));
    connect(m_HoverTimer, SIGNAL(timeout()), this, SLOT(HoveringTimerSlot()));
}

void BoardCursor::startClicking()
{
    m_ProgressClick = 0;
    m_ClickTimer->start(200);
}

void BoardCursor::stopClicking()
{
    m_ClickTimer->stop();
    m_ProgressClick = 0;
    update();
}

void BoardCursor::startHovering()
{
    m_HoverTimer->start(200);
}

void BoardCursor::stopHovering()
{
    m_HoverTimer->stop();
}

void BoardCursor::ClickingTimerSlot()
{
    m_ProgressClick++;
    update();
    if(m_ProgressClick > 8)
    {
        stopClicking();
        emit clicked();
    }
}

void BoardCursor::HoveringTimerSlot()
{
    emit hovered();
    stopHovering();
}

void BoardCursor::paintEvent(QPaintEvent*)
{
    QRectF rectangle(4, 4, 12, 12);
    int spanAngle = (45 * m_ProgressClick) * 16;

    QPen pen(Qt::red, 4);

    QPainter painter(this);
    painter.setPen(pen);
    painter.drawArc(rectangle, 0, spanAngle);
    painter.end();
}
