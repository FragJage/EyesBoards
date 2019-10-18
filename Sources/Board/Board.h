#ifndef BOARD_H
#define BOARD_H

#include <QJsonObject>
#include <QTextToSpeech>
#include "WWidgets/WWidget.h"
#include "WWidgets/WFrame.h"
#include "BoardFrame.h"
#include "BoardCursor.h"
#include "BoardOptions.h"

class Board : public WWidget
{
    Q_OBJECT

    public:
        Board(QString name);
        void defaultFrames(int col, int lig);
        void addFrame(QJsonObject jsonFrame, BoardOptions boardOptions);
        QString getName();

    public slots:
        void cursorMove(int x, int y);
        void clickFrame();
        void hoverFrame();

    private :
        QString readCss(QJsonObject style, BoardOptions boardOptions);
        void readFunctions(BoardFrame* frame, QJsonArray functions, bool click);
        BoardFrame* isFrameHere(int x, int y);
        void selectFrame(BoardFrame* frame);

        QString m_Name;
        std::list<BoardFrame*> m_Frames;
        BoardFrame* m_SelectedFrame;
        BoardCursor* m_Pointer;
};

#endif // BOARD_H
