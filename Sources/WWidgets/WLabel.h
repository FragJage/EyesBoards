#ifndef WLABEL_H
#define WLABEL_H

#include "WWidget.h"
#include "WAnchor.h"
#include <QLabel>

class WLabel : public QLabel, public WAnchor
{
    Q_OBJECT

    public:
        WLabel(WWidget *parent, Qt::WindowFlags f=Qt::WindowFlags());
        WLabel(const QString &text, WWidget *parent, Qt::WindowFlags f=Qt::WindowFlags());

    public slots:
        void initialise();
        void refresh(QSize relativeSize);
};

#endif // WLABEL_H
