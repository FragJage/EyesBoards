#include "WFrame.h"

WFrame::WFrame(WWidget *parent, Qt::WindowFlags f) : QFrame(parent, f), WAnchor(this)
{
    QObject::connect(parent, SIGNAL(initAnchor()), this, SLOT(initialise()));
    QObject::connect(parent, SIGNAL(refreshAnchor(QSize)), this, SLOT(refresh(QSize)));
}

void WFrame::initialise()
{
    WAnchor::initialise();
}

void WFrame::refresh(QSize relativeSize)
{
    WAnchor::refresh(relativeSize);
}
