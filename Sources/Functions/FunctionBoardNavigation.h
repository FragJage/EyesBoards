#ifndef FUNCTIONBOARDNAVIGATION_H
#define FUNCTIONBOARDNAVIGATION_H

#include "Functions/IFunction.h"

class FunctionBoardNavigation : public IFunction
{
    public:
        FunctionBoardNavigation();
        ~FunctionBoardNavigation();
        void Execute(QStringList parameters);
};

#endif // FUNCTIONBOARDNAVIGATION_H
