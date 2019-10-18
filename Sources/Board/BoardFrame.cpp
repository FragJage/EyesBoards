#include "BoardFrame.h"
#include "Functions/FunctionManager.h"
#include <QPainter>
#include <QDebug>

using namespace std;

BoardFrame::BoardFrame(WWidget *parent, Qt::WindowFlags f) : WFrame(parent, f)
{
    m_Name = "";
    m_Text = "";
    m_AlignFlags = Qt::AlignCenter;
}

void BoardFrame::setName(QString name)
{
    m_Name = name;
}

QString BoardFrame::name()
{
    return m_Name;
}

void BoardFrame::setText(QString text)
{
    m_Text = text;
}

void BoardFrame::setAlignFlags(int alignFlags)
{
    m_AlignFlags = alignFlags;
}

void BoardFrame::setColor(QString color)
{
    m_Pen.setColor(QColor(color));
}

void BoardFrame::setFont(QString font)
{
    m_Font.fromString(font);
}

void BoardFrame::setStyleCss(QString css, QString hover)
{
    m_CssDefault = css;
    m_CssHover = hover;

    if(m_CssDefault!="") m_CssDefault = "QFrame { "+m_CssDefault+" }";
    if(m_CssHover!="") m_CssHover = "QFrame { "+m_CssHover+" }";

    setStyleSheet(m_CssDefault);
}

void BoardFrame::setImage(QString image)
{
    m_Image.load(image);
}

void BoardFrame::setPreserveLabelSpace(bool value)
{
    m_PreserveLabelSpace = value;
}

void BoardFrame::addClickAction(QString functionName, QStringList parameters)
{
    m_ClickFunctions.emplace_back(functionName, parameters);
}

void BoardFrame::addHoverAction(QString functionName, QStringList parameters)
{
    m_HoverFunctions.emplace_back(functionName, parameters);
}

void BoardFrame::actionClick()
{
    actionExec(&m_ClickFunctions);
}

void BoardFrame::actionHover()
{
    actionExec(&m_HoverFunctions);
}

void BoardFrame::actionExec(list<BoardFunction>* actions)
{
    FunctionManager* manager = FunctionManager::instance();
    list<BoardFunction>::iterator it = actions->begin();
    list<BoardFunction>::iterator itEnd = actions->end();
    while(it!=itEnd)
    {
        qDebug() << it->getName() << " " << it->getParameters();
        manager->execute(it->getName(), it->getParameters());
        ++it;
    }
}

void BoardFrame::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if(!m_Image.isNull())
    {
        int labelHeight = 0;
        int labelDecal = 0;
        if(m_PreserveLabelSpace) labelHeight = painter.fontMetrics().boundingRect(m_Text).height();
        if((m_AlignFlags&Qt::AlignTop)>0) labelDecal = labelHeight;

        QRect rect = contentsRect();
        int width = rect.size().width();
        int height = rect.size().height()-labelHeight;
        QPixmap tmpImg = m_Image.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(rect.left()+(width-tmpImg.width())/2, rect.top()+labelDecal+(height-tmpImg.height())/2, tmpImg);
    }

    if(m_Text != "")
    {
        painter.setPen(m_Pen);
        painter.setFont(m_Font);
        painter.drawText(contentsRect(), m_AlignFlags, m_Text);
    }

    QWidget::paintEvent(event);
}

bool BoardFrame::isClickable()
{
    return !m_ClickFunctions.empty();
}

bool BoardFrame::isHoverable()
{
    return !m_HoverFunctions.empty();
}

bool BoardFrame::isHere(int x, int y)
{
    QRect geom = geometry();
    if(x < geom.x()) return false;
    if(y < geom.y()) return false;
    if(x > geom.x()+geom.width()) return false;
    if(y > geom.y()+geom.height()) return false;
    return true;
}

void BoardFrame::selected(bool set)
{
    if(set)
        setStyleSheet(m_CssHover);
    else
        setStyleSheet(m_CssDefault);
}
