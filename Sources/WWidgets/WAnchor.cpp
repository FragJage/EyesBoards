#include "WAnchor.h"

WAnchor::WAnchor(QWidget *anchorWidget)
{
    m_Initialized = false;
    m_AnchorWidget = anchorWidget;
    m_RateBottom = 0;
    m_RateRight = 0;
    m_RateWidth = 0;
    m_RateHeight = 0;
}

double WAnchor::anchorRateBottom() const
{
    return m_RateBottom;
}

double WAnchor::anchorRateRight() const
{
    return m_RateRight;
}

double WAnchor::anchorRateHeight() const
{
    return m_RateHeight;
}

double WAnchor::anchorRateWidth() const
{
    return m_RateWidth;
}

void WAnchor::setAnchor(WAnchorFlags anchor)
{
    setAnchor(static_cast<int>(anchor));
}
void WAnchor::setAnchor(int anchor)
{
    if((anchor&WAnchorFlags::Bottom)==WAnchorFlags::Bottom) m_RateBottom = 100;
    if((anchor&WAnchorFlags::Right)==WAnchorFlags::Right) m_RateRight = 100;
    if((anchor&WAnchorFlags::Width)==WAnchorFlags::Width) m_RateWidth = 100;
    if((anchor&WAnchorFlags::Height)==WAnchorFlags::Height) m_RateHeight = 100;
}

void WAnchor::setAnchor(double rateRight, double rateBottom, double rateWidth, double rateHeight)
{
    if(static_cast<int>(rateBottom) != -1) setAnchorRateBottom(rateBottom);
    if(static_cast<int>(rateRight) != -1) setAnchorRateRight(rateRight);
    if(static_cast<int>(rateHeight) != -1) setAnchorRateHeight(rateHeight);
    if(static_cast<int>(rateWidth) != -1) setAnchorRateWidth(rateWidth);
}

void WAnchor::setAnchorRateBottom(double rate)
{
    m_RateBottom = rate;
}

void WAnchor::setAnchorRateRight(double rate)
{
    m_RateRight = rate;
}

void WAnchor::setAnchorRateHeight(double rate)
{
    m_RateHeight = rate;
}

void WAnchor::setAnchorRateWidth(double rate)
{
    m_RateWidth = rate;
}

void WAnchor::initialise()
{
    if(m_Initialized) return;
    m_Initialized = true;
    m_InitialGeom = m_AnchorWidget->geometry();
}

void WAnchor::refresh(QSize relativeSize)
{
    if(!m_Initialized) return;
    QRect newGeom(m_InitialGeom);
    newGeom.setX(static_cast<int>(m_InitialGeom.x()+relativeSize.width()*m_RateRight/100));
    newGeom.setY(static_cast<int>(m_InitialGeom.y()+relativeSize.height()*m_RateBottom/100));
    newGeom.setWidth(static_cast<int>(m_InitialGeom.width()+relativeSize.width()*m_RateWidth/100));
    newGeom.setHeight(static_cast<int>(m_InitialGeom.height()+relativeSize.height()*m_RateHeight/100));
    m_AnchorWidget->setGeometry(newGeom);
}
