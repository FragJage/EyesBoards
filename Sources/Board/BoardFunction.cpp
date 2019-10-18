#include "BoardFunction.h"

BoardFunction::BoardFunction(QString name, QStringList parameters)
{
    m_Name = name;
    m_Parameters = parameters;
}

QString BoardFunction::getName() const
{
    return m_Name;
}

QStringList BoardFunction::getParameters() const
{
    return m_Parameters;
}
