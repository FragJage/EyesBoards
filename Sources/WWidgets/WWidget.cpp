#include "WWidget.h"

WWidget::WWidget(QWidget *parent) : QWidget(parent)
{

}

void WWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    m_InitialSize = size();
    emit initAnchor();
}

void WWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int w = event->size().width()-m_InitialSize.width();
    int h = event->size().height()-m_InitialSize.height();
    emit refreshAnchor(QSize(w, h));
}
