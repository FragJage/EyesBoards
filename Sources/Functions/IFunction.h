#ifndef IFUNCTION_H
#define IFUNCTION_H

#include <QStringList>

class IFunction
{
    public:
        virtual ~IFunction() = 0;
        virtual void Execute(QStringList parameters) = 0;
};

#endif // IFUNCTION_H
