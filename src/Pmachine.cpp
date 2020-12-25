#include "Pmachine.h"

Pmachine::Pmachine(string file)
{
    FluxCode.open(file);
    SP = 0;
    BEG = 0;
    BEL = 0;
    CO = 0;

}


void Pmachine::getCode(){

     string line;
     getline(FluxCode,line);
     while(line != "EOF"){
         if(line == "")
            break;
        code.push_back(line);
        getline(FluxCode,line);
    }

}


Instruction Pmachine::getInstruction(int index){

    stringstream line(code[index]);
    string token = "";
    vector <string> tokens;
    Instruction Ins;
    while(getline(line, token, ' '))
    {
        tokens.push_back(token);
    }
    switch(tokens.size()){
        case 1:
            Ins.operation = tokens[0];
            Ins.attribut = NULL;
            break;
        case 2:
            Ins.operation = tokens[0];
            Ins.attribut = stoi(tokens[1]);
            break;
    }

    return Ins;
}

void Pmachine::interpreter(Instruction instCourante){
    if(instCourante.operation == "EMPC"){
        pile.push_back(instCourante.attribut);
        CO++;
    }
    if(instCourante.operation == "EMPL"){
        pile.push_back(localPile[BEL + instCourante.attribut]);
        CO++;
    }
    if(instCourante.operation == "DEPL"){

        if(BEL + instCourante.attribut > localPile.size()-1){
             localPile.push_back(0);
        }

        else{
        globalPile[BEL + instCourante.attribut] = pile[pile.size()-1];
        pile.pop_back();
        }
        CO++;

    }
    if(instCourante.operation == "EMPG"){
        pile.push_back(globalPile[BEG + instCourante.attribut]);
        CO++;
    }
    if(instCourante.operation == "DEPG"){
        if(BEG + instCourante.attribut > globalPile.size()-1){
             globalPile.push_back(0);
        }

        else{
        globalPile[BEG + instCourante.attribut] = pile[pile.size()-1];
        pile.pop_back();
        }
        CO++;
    }
    if(instCourante.operation == "EMPT"){
        //////////////////////
    }
    if(instCourante.operation == "DEPT"){
        /////////////////////
    }
    if(instCourante.operation == "ADD"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back(b + a);
        CO++;
    }
    if(instCourante.operation == "SOUS"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back(b - a);
        CO++;
    }
    if(instCourante.operation == "MULT"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back(b * a);
        CO++;
    }
    if(instCourante.operation == "DIV"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back(b / a);
        CO++;
    }
    if(instCourante.operation == "MOD"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back(b % a);
        CO++;
    }
    if(instCourante.operation == "EGAL"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back((a == b));
        CO++;

    }
    if(instCourante.operation == "INF"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back((a < b));
        CO++;

    }
    if(instCourante.operation == "INF"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        b = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back((a <= b));
        CO++;

    }
    if(instCourante.operation == "NON"){
        int a,b;
        a = pile[pile.size()-1];
        pile.pop_back();
        pile.push_back((!a));
        CO++;

    }
    if(instCourante.operation == "LIRE"){
        int a;
        cin >> a;
        pile.push_back(a);
        CO++;

    }

    if(instCourante.operation == "ECRIV"){
        cout<< pile[pile.size()-1]<<endl;
        CO++;
    }

    if(instCourante.operation == "SAUT"){
        CO = instCourante.attribut;
    }

    if(instCourante.operation == "SIVRAI"){
        int a = pile[pile.size()-1];
        pile.pop_back();
        if(a != 0){
            CO = instCourante.attribut;
        }
        else{
            CO++;
        }
    }
    if(instCourante.operation == "SIFAUX"){
        int a = pile[pile.size()-1];
        pile.pop_back();
        if(a == 0){
            CO = instCourante.attribut;
        }
        else{
            CO++;
        }
    }
    if(instCourante.operation == "APPEL"){
        pile.push_back(BEL);
        pile.push_back(CO + 1);
        pile.push_back(SP);
        SP = pile.size();
        CO = instCourante.attribut;
        BEL = localPile.size();
    }
    if(instCourante.operation == "RETOUR"){
        //////////////////////
    }
    if(instCourante.operation == "ENTREE"){
        //////////////////////
    }
    if(instCourante.operation == "SORTIE"){
        //////////////////////
    }
    if(instCourante.operation == "DUP"){
        pile.push_back(pile[pile.size()-1]);
        CO++;
    }
    if(instCourante.operation == "POP"){
        pile.pop_back();
        CO++;
    }
    if(instCourante.operation == "STOP"){
        exit(EXIT_SUCCESS);
    }


}

void Pmachine::interpreterCode(){


    while(1){
        interpreter(getInstruction(CO));
    }



}
