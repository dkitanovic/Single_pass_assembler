#ifndef ADRESIRANJE 
#define ADRESIRANJE
#include <string> 
using namespace std;

int regdir(string arg1);
int regind(string arg1);
int regindpom(string arg1,int& pomeraj,int velicina);
int immed(string arg1,int& reg,int velicina);
int nadji_adresiranje(string arg1,int& reg,int& pomeraj,string& izraz,int velicina); 
bool skok();

#endif