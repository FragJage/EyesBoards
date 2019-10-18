#ifndef BOARDCURSOR_H
#define BOARDCURSOR_H

#include <QWidget>
#include <QFrame>
#include <QTimer>

class BoardCursor : public QFrame
{
    Q_OBJECT

    public:
        BoardCursor(QWidget* parent, Qt::WindowFlags f=Qt::WindowFlags());
        void startClicking();
        void stopClicking();
        void startHovering();
        void stopHovering();

    public slots:
        void ClickingTimerSlot();
        void HoveringTimerSlot();

    signals:
        void clicked();
        void hovered();

    protected:
        void paintEvent(QPaintEvent*);
        QTimer* m_ClickTimer;
        QTimer* m_HoverTimer;
        int m_ProgressClick;
};

#endif // BOARDCURSOR_H
