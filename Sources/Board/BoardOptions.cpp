#include "BoardOptions.h"

BoardOptions::BoardOptions()
{

}

QDir BoardOptions::path() const
{
    return m_Dir;
}

void BoardOptions::setPath(QString directory)
{
    m_Dir.setPath(directory);
}
