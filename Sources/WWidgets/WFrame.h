#ifndef WFRAME_H
#define WFRAME_H

#include "WWidget.h"
#include "WAnchor.h"
#include <QFrame>

class WFrame : public QFrame, public WAnchor
{
    Q_OBJECT

    public:
        WFrame(WWidget *parent, Qt::WindowFlags f=Qt::WindowFlags());

    public slots:
        void initialise();
        void refresh(QSize relativeSize);
};

#endif // WFRAME_H
