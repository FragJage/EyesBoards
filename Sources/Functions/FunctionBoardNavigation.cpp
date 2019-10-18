#include "FunctionBoardNavigation.h"
#include "Board/BoardSignals.h"

FunctionBoardNavigation::FunctionBoardNavigation()
{

}

FunctionBoardNavigation::~FunctionBoardNavigation()
{
}

void FunctionBoardNavigation::Execute(QStringList parameters)
{
    if(parameters.length() == 1)
        emit BoardSignals::instance()->boardNavigation(parameters[0], "");
    else
        emit BoardSignals::instance()->boardNavigation(parameters[0], parameters[1]);
}
