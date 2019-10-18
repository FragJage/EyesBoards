#include "WLabel.h"

WLabel::WLabel(WWidget *parent, Qt::WindowFlags f) : QLabel(parent, f), WAnchor(this)
{
    QObject::connect(parent, SIGNAL(initAnchor()), this, SLOT(initialise()));
    QObject::connect(parent, SIGNAL(refreshAnchor(QSize)), this, SLOT(refresh(QSize)));
}

WLabel::WLabel(const QString &text, WWidget *parent, Qt::WindowFlags f) : QLabel(text, parent, f), WAnchor(this)
{
    QObject::connect(parent, SIGNAL(initAnchor()), this, SLOT(initialise()));
    QObject::connect(parent, SIGNAL(refreshAnchor(QSize)), this, SLOT(refresh(QSize)));
}

void WLabel::initialise()
{
    WAnchor::initialise();
}

void WLabel::refresh(QSize relativeSize)
{
    WAnchor::refresh(relativeSize);
}
