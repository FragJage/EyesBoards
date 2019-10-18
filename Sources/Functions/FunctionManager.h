#ifndef FUNCTIONMANAGER_H
#define FUNCTIONMANAGER_H

#include <QStringList>
#include <QString>
#include <QMap>
#include "IFunction.h"

class FunctionManager
{
    public:
        static FunctionManager* instance()
        {
            static FunctionManager INSTANCE;
            return &INSTANCE;
        }
        ~FunctionManager();
        void execute(QString name, QStringList parameters);

    private:
        FunctionManager();
        QMap<QString, IFunction*> m_FunctionsList;
};
#endif // FUNCTIONMANAGER_H
