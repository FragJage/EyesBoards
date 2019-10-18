#ifndef BOARDFUNCTION_H
#define BOARDFUNCTION_H

#include <QStringList>
#include <QString>

class BoardFunction
{
    public:
        BoardFunction(QString name, QStringList parameters);
        QString getName() const;
        QStringList getParameters() const;

    private:
        QString m_Name;
        QStringList m_Parameters;
};

#endif // BOARDFUNCTION_H
