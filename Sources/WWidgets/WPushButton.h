#ifndef WPUSHBUTTON_H
#define WPUSHBUTTON_H

#include "WWidget.h"
#include "WAnchor.h"
#include <QPushButton>

class WPushButton : public QPushButton, public WAnchor
{
    Q_OBJECT

    public:
        WPushButton(WWidget *parent);
        WPushButton(const QString &text, WWidget *parent);
        WPushButton(const QIcon &icon, const QString &text, WWidget *parent);

    public slots:
        void initialise();
        void refresh(QSize relativeSize);
};

#endif // WPUSHBUTTON_H
