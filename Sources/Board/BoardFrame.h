#ifndef BOARDFRAME_H
#define BOARDFRAME_H

#include <QString>
#include <QPixmap>
#include <QPen>
#include <QFont>
#include <list>
#include <QPaintEvent>
#include "WWidgets/WFrame.h"
#include "Board/BoardFunction.h"

class BoardFrame : public WFrame
{
    public:
        BoardFrame(WWidget *parent, Qt::WindowFlags f=Qt::WindowFlags());

        void setName(QString name);
        QString name();
        void setText(QString text);
        void setAlignFlags(int alignFlags);
        void setColor(QString color);
        void setFont(QString font);
        void setStyleCss(QString css, QString hover="");
        void setImage(QString image);
        void setPreserveLabelSpace(bool value);
        void addClickAction(QString functionName, QStringList parameters);
        void addHoverAction(QString functionName, QStringList parameters);

        bool isClickable();
        bool isHoverable();
        bool isHere(int x, int y);
        void selected(bool set);

        void actionClick();
        void actionHover();
        void actionExec(std::list<BoardFunction>* actions);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QString m_Name;
        QString m_Text;
        int m_AlignFlags;
        QPixmap m_Image;
        QPen m_Pen;
        QFont m_Font;
        bool m_PreserveLabelSpace;
        QString m_CssDefault;
        QString m_CssHover;
        std::list<BoardFunction> m_HoverFunctions;
        std::list<BoardFunction> m_ClickFunctions;
};

#endif // BOARDFRAME_H
