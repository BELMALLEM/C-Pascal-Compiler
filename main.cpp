#include <iostream>
#include <string>
#include "Pmachine.h"









int main()
{
    Instruction i ;
    Pmachine p("code.txt");
    string opCode = "";
    p.getCode();

    p.interpreterCode();





    return 0;
}
