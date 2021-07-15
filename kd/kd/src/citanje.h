#ifndef CITANJE
#define CITANJE 
#include <string>
using namespace std;

bool labela(string& line,string& lab);
bool equ(string& line,string& arg1,string& arg2);
bool skip(string& line,string& arg1);
bool word(string& line,string& arg1);
bool byte(string& line,string& arg1);
bool global(string& line,string& arg1);
bool is_extern(string& line,string& arg1);
bool sekcija(string& line);
bool citaj0(string& line,int& kod);
bool citaj1(string& line,string& arg1,int& kod,int& velicina);
bool citaj2(string& line,string& arg1,string& arg2,int& kod,int& velicina);
#endif