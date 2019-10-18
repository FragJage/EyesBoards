#include "WPushButton.h"

WPushButton::WPushButton(WWidget *parent) : QPushButton(parent), WAnchor(this)
{
    QObject::connect(parent, SIGNAL(initAnchor()), this, SLOT(initialise()));
    QObject::connect(parent, SIGNAL(refreshAnchor(QSize)), this, SLOT(refresh(QSize)));
}

WPushButton::WPushButton(const QString &text, WWidget *parent) : QPushButton(text, parent), WAnchor(this)
{
    QObject::connect(parent, SIGNAL(initAnchor()), this, SLOT(initialise()));
    QObject::connect(parent, SIGNAL(refreshAnchor(QSize)), this, SLOT(refresh(QSize)));
}

WPushButton::WPushButton(const QIcon &icon, const QString &text, WWidget *parent) : QPushButton(icon, text, parent), WAnchor(this)
{
    QObject::connect(parent, SIGNAL(initAnchor()), this, SLOT(initialise()));
    QObject::connect(parent, SIGNAL(refreshAnchor(QSize)), this, SLOT(refresh(QSize)));
}

void WPushButton::initialise()
{
    WAnchor::initialise();
}

void WPushButton::refresh(QSize relativeSize)
{
    WAnchor::refresh(relativeSize);
}
