#include "FunctionSay.h"
#include <QDebug>

FunctionSay::FunctionSay()
{
    m_Speech = new QTextToSpeech();
}

FunctionSay::~FunctionSay()
{
    delete m_Speech;
}

void FunctionSay::Execute(QStringList parameters)
{
    m_Speech->say(parameters.first());
}
