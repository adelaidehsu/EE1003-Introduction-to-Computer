#include "Simulator.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>

char Mcell[256];
char Regi[16] = {0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0};
unsigned short InstruRegi[1];
bool Simulator::loadMemory(string path) {
    //TODO
    char buff[256];
    ifstream file(path, ios::in | ios::binary);
    if(!file)
    {
        cout<<"can't open the file."<<endl;
        return false;
    }
    file.read(buff, sizeof(buff));
    for(int i=0; i<256; ++i)
    {
        Mcell[i] = buff[i];
    }
    
    file.close();
    return true;
}
bool Simulator::storeMemory(string path) {
    //TODO
    ofstream file(path, ios::binary);
    file.write(Mcell, 256);
    file.close();
    return true;
}
bool Simulator::simulate() {
    //TODO
    int programcnt = 0;
    bool halt = false;
    while(programcnt <256 && halt == false)
    {
        bool jump = false;
        InstruRegi[0] = *(unsigned short*)&Mcell[programcnt];
        int address = (InstruRegi[0] >> 8) & ((1 << 8)-1);
        int op2 = (InstruRegi[0] >> 12) & ((1 << 4)-1);
        int op3 = (InstruRegi[0] >> 8) & ((1 << 4)-1);
        int opcode = (InstruRegi[0] >> 4) & ((1 << 4)-1);
        int op1 = (InstruRegi[0]) & ((1 << 4)-1);
        
        switch(opcode)
        {
            case 1:
                Regi[op1] = Mcell[address];
                break;
            case 2:
                Regi[op1] = *(char*)&address;
                break;
            case 3:
                Mcell[address] = Regi[op1];
                break;
            case 4:
                Regi[op3] = Regi[op2];
                break;
            case 5:
                Regi[op1] = Regi[op2] + Regi[op3];
                break;
            case 6:
                Regi[op1] = Regi[op2] + Regi[op3];
                break;
            case 7:
                Regi[op1] = Regi[op2] | Regi[op3];
                break;
            case 8:
                Regi[op1] = Regi[op2] & Regi[op3];
                break;
            case 9:
                Regi[op1] = Regi[op2] ^ Regi[op3];
                break;
            case 10:
                (Regi[op1] >> op3) | (Regi[op1] << (sizeof(char)*8 - op3));
                break;
            case 11:
                if(Regi[op1] == Regi[0])
                {
                    jump = true;
                    programcnt = address;
                }
                break;
            case 12:
                halt = true;
                break;
        }
        if(!jump)
            programcnt+=2;
    }
    return true;
}

