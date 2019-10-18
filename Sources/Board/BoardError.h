#ifndef BOARDERROR_H
#define BOARDERROR_H

#include <QString>

class BoardError
{
    public:
        BoardError(QString code, QString message);
        QString code();
        QString message();

    private:
        QString m_Code;
        QString m_Message;
};

#endif // BOARDERROR_H
