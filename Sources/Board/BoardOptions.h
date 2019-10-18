#ifndef BOARDOPTIONS_H
#define BOARDOPTIONS_H

#include <QString>
#include <QDir>

class BoardOptions
{
    public:
        BoardOptions();
        QDir path() const;
        void setPath(QString directory);

    private:
        QDir m_Dir;
};

#endif // BOARDOPTIONS_H
