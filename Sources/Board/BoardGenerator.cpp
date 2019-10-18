#include <QFile>
#include <QFileInfo>
#include <QVersionNumber>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "BoardGenerator.h"
#include "Board/BoardSignals.h"

using namespace std;

BoardGenerator::BoardGenerator() : QWidget()
{
    CurrentBoardNb = -1;
    QObject::connect(BoardSignals::instance(), SIGNAL(boardNavigation(QString, QString)), this, SLOT(boardNavigation(QString, QString)));
}

BoardGenerator::~BoardGenerator()
{
    m_Boards.clear();
}

Board* BoardGenerator::getBoard(int index)
{
    if(!validBoardIndex(index)) return nullptr;
    return m_Boards[index];
}

BoardError BoardGenerator::loadBoards(QString jsonFilePath)
{
    QFileInfo fi(jsonFilePath);
    m_BoardOptions.setPath(fi.absolutePath());

    QFile file;
    file.setFileName(jsonFilePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return BoardError("FILENOTFOUND", "Impossible d'ouvrir le fichier json.");

    QString val = file.readAll();
    if(val == "") return BoardError("EMPTYFILE", "Le fichier json est vide.");
    file.close();

    QJsonParseError jsonErr;
    QJsonDocument parsedFile = QJsonDocument::fromJson(val.toUtf8(), &jsonErr);
    if(parsedFile.isNull()) return BoardError("INVALIDJSON", jsonErr.errorString());

    QJsonObject eyesBoards = parsedFile["EyesBoards"].toObject();
    if(eyesBoards.isEmpty()) return BoardError("NOTJSONBOARDS", "Ce n'est pas un fichier EyesBoards.");

    QVersionNumber version = QVersionNumber::fromString(eyesBoards["Version"].toString("1.0.0"));
    if(version > QVersionNumber(1,0,0)) return BoardError("BADVERSION", "Le fichier json est dans une version trop récente.");

    QJsonArray boards = eyesBoards["Boards"].toArray();
    QJsonArray::iterator it = boards.begin();
    QJsonArray::iterator itEnd = boards.end();
    while(it != itEnd)
    {
        addBoard(it->toObject(), m_BoardOptions);
        ++it;
    }

    return BoardError("","");
}

void BoardGenerator::boardNavigation(QString action, QString name)
{
    QString tmp = action.toUpper();
    if(tmp == "NEXT")
    {
        close(CurrentBoardNb);
        show(CurrentBoardNb+1);
        return;
    }
    if(tmp == "SHOW")
    {
        int foundBoard = searchBoard(name);
        if(foundBoard < 0) return;
        close(CurrentBoardNb);
        show(foundBoard);
        return;
    }
}

void BoardGenerator::close(int index)
{
    if(!validBoardIndex(index)) return;
    m_Boards[index]->close();
}

void BoardGenerator::show(int index)
{
    if(!validBoardIndex(index)) return;
    CurrentBoardNb = index;
    m_Boards[index]->show();
}

bool BoardGenerator::validBoardIndex(int index)
{
    if(index < 0) return false;
    if(index > m_Boards.length()-1) return false;
    return true;
}

int BoardGenerator::searchBoard(QString name)
{
    int i = 0;
    Board* brd;

    while((brd=getBoard(i))!=nullptr)
    {
        if(brd->getName() == name) return i;
        i++;
    }
    return -1;
}

void BoardGenerator::addBoard(QJsonObject jsonBoard, BoardOptions boardOptions)
{
    Board* board = new Board(jsonBoard["Name"].toString());

    QJsonArray frames = jsonBoard["Frames"].toArray();
    QJsonArray::iterator it = frames.begin();
    QJsonArray::iterator itEnd = frames.end();
    while(it != itEnd)
    {
        board->addFrame(it->toObject(), boardOptions);
        ++it;
    }
    m_Boards << board;
}
