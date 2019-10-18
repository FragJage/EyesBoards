#ifndef FUNCTIONSAY_H
#define FUNCTIONSAY_H

#include <QTextToSpeech>
#include "Functions/IFunction.h"

class FunctionSay : public IFunction
{
    public:
        FunctionSay();
        ~FunctionSay();
        void Execute(QStringList parameters);

    private:
        QTextToSpeech* m_Speech;
};

#endif // FUNCTIONSAY_H
