#include "BoardError.h"

BoardError::BoardError(QString code, QString message)
{
    m_Code = code;
    m_Message = message;
}

QString BoardError::code()
{
    return m_Code;
}

QString BoardError::message()
{
    return m_Message;
}
