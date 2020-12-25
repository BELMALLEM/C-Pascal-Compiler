#ifndef PMACHINE_H
#define PMACHINE_H
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <../structure.h>


class Pmachine
{
    public:


        Pmachine(string file);//Constructeur
        Instruction getInstruction(int index);
        void getCode();// stock le code dans la mempoire
        void interpreter(Instruction instCourante);// fonction principale
        void interpreterCode();// boucle


    private:

        vector<int> pile;
        vector<string> code;
        vector<int> globalPile;
        vector<int> localPile;
        ifstream FluxCode;
        int SP,BEL,BEG,CO;
};

#endif // PMACHINE_H
