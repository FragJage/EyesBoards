#include "Board.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QtDebug>

using namespace std;

Board::Board(QString name) : WWidget()
{
    m_SelectedFrame = nullptr;
    m_Pointer = new BoardCursor(this);
    m_Name = name;
    resize(800, 500);
    connect(m_Pointer, SIGNAL(clicked()), this, SLOT(clickFrame()));
    connect(m_Pointer, SIGNAL(hovered()), this, SLOT(hoverFrame()));
}

QString Board::getName()
{
    return m_Name;
}

void Board::clickFrame()
{
    if(m_SelectedFrame == nullptr) return;
    m_SelectedFrame->actionClick();
}

void Board::hoverFrame()
{
    if(m_SelectedFrame == nullptr) return;
    m_SelectedFrame->actionHover();
}

void Board::selectFrame(BoardFrame* frame)
{
    if(m_SelectedFrame != nullptr)
    {
        m_SelectedFrame->selected(false);
        m_Pointer->stopClicking();
    }
    if(frame != nullptr)
    {
        frame->selected(true);
        if(frame->isHoverable()) m_Pointer->startHovering();
        if(frame->isClickable()) m_Pointer->startClicking();
    }
    m_SelectedFrame=frame;
}

BoardFrame* Board::isFrameHere(int x, int y)
{
    list<BoardFrame*>::iterator it = m_Frames.begin();
    list<BoardFrame*>::iterator itEnd = m_Frames.end();
    while(it != itEnd)
    {
        if((*it)->isHere(x, y)) return (*it);
        ++it;
    }
    return nullptr;
}

void Board::cursorMove(int tx, int ty)
{
    if(!isVisible()) return;
    QRect geom = geometry();
    int x = tx - geom.x();
    x = x+25;
    if((x<0)||(x>geom.width()))
    {
        selectFrame(nullptr);
        m_Pointer->hide();
        return;
    }
    int y = ty - geom.y();
    y = y+20;
    if((y<0)||(y>geom.height()))
    {
        selectFrame(nullptr);
        m_Pointer->hide();
        return;
    }

    m_Pointer->show();
    m_Pointer->move(x-10, y-10);

    BoardFrame* frame = isFrameHere(x,y);
    if(frame == m_SelectedFrame) return;
    selectFrame(frame);
}

void Board::defaultFrames(int col, int lig)
{
    for(int j=0; j<lig; j++)
    {
        for(int i=0; i<col; i++)
        {
            BoardFrame* frame = new BoardFrame(this);
            frame->setGeometry(5+130*i, 5+90*j, 120, 80);
            frame->setAnchor(100*i/col, 100*j/lig, 100/col, 100/lig);
            frame->stackUnder(m_Pointer);
            m_Frames.push_back(frame);
        }
    }
}

QString Board::readCss(QJsonObject style, BoardOptions boardOptions)
{
    if(style.isEmpty()) return "";

    QString css="";
    QString tmp;

    tmp = style["BorderColor"].toString("");
    if(tmp!="") css += "border-color:"+tmp+";";

    tmp = style["BorderWidth"].toString("");
    if(tmp!="") css += "border-width:"+tmp+";";

    tmp = style["BorderStyle"].toString("");
    if(tmp!="") css += "border-style:"+tmp+";";

    tmp = style["BorderRadius"].toString("");
    if(tmp!="") css += "border-radius:"+tmp+";";

    tmp = style["Css"].toString("");
    if(tmp!="") css += tmp+";";

    tmp = style["BackgroundColor"].toString("");
    if(tmp!="") css += "background-color:"+tmp+";";

    tmp = style["BackgroundImage"].toString("");
    if(tmp!="") css += "background-image:url('"+boardOptions.path().filePath(tmp)+"');";

    return css;
}

void Board::readFunctions(BoardFrame* frame, QJsonArray functions, bool click)
{
    QJsonArray::iterator it = functions.begin();
    QJsonArray::iterator itEnd = functions.end();
    while(it != itEnd)
    {
        QJsonObject func = it->toObject();
        QStringList parameters;

        QJsonArray jsonParam = func["Parameters"].toArray();
        QJsonArray::iterator itp = jsonParam.begin();
        QJsonArray::iterator itpEnd = jsonParam.end();

        while(itp != itpEnd)
        {
            parameters << itp->toString();
            ++itp;
        }

        if(click)
            frame->addClickAction(func["Function"].toString(), parameters);
        else
            frame->addHoverAction(func["Function"].toString(), parameters);
        ++it;
    }
}

void Board::addFrame(QJsonObject jsonFrame, BoardOptions boardOptions)
{
    BoardFrame* frame = new BoardFrame(this);

    frame->setName(jsonFrame["Name"].toString());

    QJsonObject geometry = jsonFrame["Geometry"].toObject();
    if(!geometry.isEmpty())
    {
        frame->setGeometry(geometry["X"].toInt(),
                            geometry["Y"].toInt(),
                            geometry["Width"].toInt(),
                            geometry["Height"].toInt());
    }

    QJsonObject anchor = jsonFrame["Anchor"].toObject();
    if(!anchor.isEmpty())
    {
        frame->setAnchor(anchor["Right"].toDouble(),
                            anchor["Bottom"].toDouble(),
                            anchor["Width"].toDouble(),
                            anchor["Height"].toDouble());
    }

    QJsonObject style = jsonFrame["Frame"].toObject();
    if(!style.isEmpty())
    {
        QString css = readCss(style["Default"].toObject(), boardOptions);
        QString hover = readCss(style["Hover"].toObject(), boardOptions);
        frame->setStyleCss(css, hover);
    }

    QJsonObject label = jsonFrame["Label"].toObject();
    if(!label.isEmpty())
    {
        int align = 0;
        QString tmp;

        frame->setText(label["Text"].toString(""));

        tmp = label["VerticalAlign"].toString("").toUpper();
        if(tmp=="TOP")      align += Qt::AlignTop;
        if(tmp=="CENTER")   align += Qt::AlignVCenter;
        if(tmp=="BOTTOM")   align += Qt::AlignBottom;

        tmp = label["HorizontalAlign"].toString("").toUpper();
        if(tmp=="LEFT")     align += Qt::AlignLeft;
        if(tmp=="CENTER")   align += Qt::AlignHCenter;
        if(tmp=="RIGHT")    align += Qt::AlignRight;
        if(align!=0) frame->setAlignFlags(align);

        tmp = label["Color"].toString("");
        if(tmp!="") frame->setColor(tmp);

        tmp = label["Font"].toString("");
        if(tmp!="") frame->setFont(tmp);
    }

    QJsonObject image = jsonFrame["Image"].toObject();
    if(!image.isEmpty())
    {
        QString src = image["File"].toString("");
        if(src != "") frame->setImage(boardOptions.path().filePath(src));
        QJsonValue space = image["PreserveLabelSpace"];
        if(space.isBool()) frame->setPreserveLabelSpace(space.toBool(false));
    }

    readFunctions(frame, jsonFrame["OnClick"].toArray(), true);
    readFunctions(frame, jsonFrame["OnHover"].toArray(), false);

    //qDebug() << "addFrame : " << jsonFrame["Name"].toString() << " " << geometry["X"].toInt() <<","<< geometry["Y"].toInt() <<" -> "<< geometry["Width"].toInt() <<"x"<< geometry["Height"].toInt() <<" - "<< anchor["Right"].toDouble() <<"%,"<< anchor["Bottom"].toDouble() <<"% -> "<< anchor["Width"].toDouble() <<"%x"<< anchor["Height"].toDouble() << "%";
    frame->stackUnder(m_Pointer);
    m_Frames.push_back(frame);
}
