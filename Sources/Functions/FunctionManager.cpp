#include <QDebug>
#include "FunctionManager.h"
#include "FunctionSay.h"
#include "FunctionBoardNavigation.h"

FunctionManager::FunctionManager()
{
    //Build-in functions
    m_FunctionsList["Say"] = new FunctionSay();
    m_FunctionsList["BoardNavigation"] = new FunctionBoardNavigation();
}

FunctionManager::~FunctionManager()
{
    QMap<QString, IFunction*>::iterator it = m_FunctionsList.begin();
    QMap<QString, IFunction*>::iterator itEnd = m_FunctionsList.end();
    while(it!=itEnd)
    {
        delete it.value();
        ++it;
    }
}

void FunctionManager::execute(QString name, QStringList parameters)
{
    QMap<QString, IFunction*>::iterator it = m_FunctionsList.find(name);
    if(it == m_FunctionsList.end()) return;
    it.value()->Execute(parameters);
}
