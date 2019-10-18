#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QJsonObject>
#include "BoardError.h"
#include "BoardOptions.h"
#include "Board.h"

class BoardGenerator : public QWidget
{
    Q_OBJECT

    public:
        BoardGenerator();
        ~BoardGenerator();
        BoardError loadBoards(QString jsonFilePath);
        void show(int index=0);
        void close(int index);
        Board* getBoard(int index);

    public slots:
        void boardNavigation(QString action, QString name);

    private:
        int searchBoard(QString name);
        void addBoard(QJsonObject jsonBoard, BoardOptions boardOptions);
        bool validBoardIndex(int index);
        QList<Board*> m_Boards;
        BoardOptions m_BoardOptions;
        int CurrentBoardNb;
};

#endif // BOARDGENERATOR_H
