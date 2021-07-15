#include <iostream>
#include <regex>
#include "citanje.h"
#include "strukture.h"
#include "tabela_simbola.h"
using namespace std;

bool labela(string &line,string &lab){
    
    regex r("^(\\s*\\w+\\s*:.*)");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){ 
       lab=line;
       lab.erase(lab.find(':'));
       lab.erase(remove(lab.begin(), lab.end(), ' '), lab.end());
       lab.erase(remove(lab.begin(), lab.end(), '\t'), lab.end());
       lab.erase(remove(lab.begin(), lab.end(), '\r'), lab.end());
    
       line.erase(0,line.find(':')+1);
       return true;
    }
    return false;
}

bool equ(string& line,string& arg1,string& arg2){
    regex r("^(\\s*\\.equ\\s+\\w+\\s*,\\s*[\\+|\\-|\\w+|\\s+]+\\s*)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){ 
       line.erase(0,line.find("equ")+4);
       arg1=line;
       arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
       line.erase(remove(line.begin(), line.end(), '\t'), line.end());
       line.erase(remove(line.begin(), line.end(), '\r'), line.end());
       arg2=arg1;
       arg1.erase(arg1.find(','));
       arg2.erase(0,arg2.find(',')+1);
       line="equ";
       return true;
    }
    return false;  
}

bool skip(string& line,string& arg1){
    regex r("^(\\s*\\.skip\\s*[^]+)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if(regex_match(line,r)){
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(0,5);
        arg1=line;
        line="skip";
        return true;
    }
    return false;
}

bool word(string& line,string& arg1){
    regex r("^(\\s*\\.word\\s+[^]+)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){
        line.erase(0,line.find("word")+5);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        arg1=line;
        line="word";
        return true;
    }
    return false;
}

bool byte(string& line,string& arg1){
    regex r("^(\\s*\\.byte\\s+[^]+)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){
        line.erase(0,line.find("byte")+5);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        arg1=line;
        line="byte";
        return true;
    }
    return false;
}

bool global(string& line,string& arg1){
    regex r("^(\\s*\\.global\\s+[^]+)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){
        line.erase(0,line.find("global")+7);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());  
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        arg1=line;
        line="global";
        return true;
    }
    return false;
}

bool is_extern(string& line,string& arg1){
    regex r("^(\\s*\\.extern\\s+[^]+)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){
        line.erase(0,line.find("extern")+7);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());  
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        arg1=line;
        line="extern";
        return true;
    }
    return false;
}

bool sekcija(string& line){
    regex r("^(\\s*\\.section\\s+\\w+\\s*:\\s*)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r)){
         line.erase(remove(line.begin(), line.end(), ' '), line.end());  
         line.erase(remove(line.begin(), line.end(), '\t'), line.end());  
         line.erase(remove(line.begin(), line.end(), '\r'), line.end());
         line.erase(line.size()-1,line.size());
         line.erase(0,8);
         return true;
    }
    return false;
}

bool citaj0(string& line,int& kod){
    regex r1("^(\\s*halt\\s*)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r1)){ 
        line="halt";
        kod=0;
        return true;
    }
    regex r2("^(\\s*iret\\s*)$");
    if (regex_match(line,r2)){ 
        line="iret";
        kod=1;
        return true;
    }
    regex r3("^(\\s*ret\\s*)$");
    if (regex_match(line,r3)){ 
        line="ret";
        kod=2;
        return true;
    }

    return false;
}

bool citaj1(string& line,string& arg1,int& kod,int& velicina){
    regex r1("^(\\s*int[bw]?\\s+[^]+\\s*)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r1)){ 
        if (line[line.find("int")+3]=='b') velicina=0;
        else velicina=1;
        arg1=line;
        arg1=arg1.erase(line.find("int"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="int";
        kod=3;
        return true;
    }
    regex r2("^(\\s*call[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r2)){
        if (line[line.find("call")+4]=='b') velicina=0;
        else velicina=1; 
        arg1=line;
        arg1=arg1.erase(line.find("call"),5);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="call";
        kod=4;
        return true;
    }
    regex r3("^(\\s*jmp[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r3)){ 
        if (line[line.find("jmp")+3]=='b') velicina=0;
        else velicina=1;
        arg1=line;
        arg1=arg1.erase(line.find("jmp"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="jmp";
        kod=5;
        return true;
    }
    regex r4("^(\\s*jeq[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r4)){ 
        if (line[line.find("jeq")+3]=='b') velicina=0;
        else velicina=1;
        arg1=line;
        arg1=arg1.erase(line.find("jeq"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="jeq";
        kod=6;
        return true;
    }
    regex r5("^(\\s*jne[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r5)){
        if (line[line.find("jne")+3]=='b') velicina=0;
        else velicina=1; 
        arg1=line.erase(line.find("jne"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="jne";
        kod=7;
        return true;
    }
    regex r6("^(\\s*jgt[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r6)){ 
        if (line[line.find("jgt")+3]=='b') velicina=0;
        else velicina=1;
        arg1=line;
        arg1=arg1.erase(line.find("jgt"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="jgt";
        kod=8;
        return true;
    }
    regex r7("^(\\s*push[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r7)){ 
        if (line[line.find("push")+4]=='b') velicina=0;
        else velicina=1;
        arg1=line;
        arg1.erase(arg1.find("push"),5);
        arg1.erase(remove(arg1.begin(), arg1.end(),' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="push";
        kod=9;
        return true;
    }
    regex r8("^(\\s*pop[bw]?\\s+[^]+\\s*)$");
    if (regex_match(line,r8)){ 
        if (line[line.find("pop")+3]=='b') velicina=0;
        else velicina=1;
        arg1=line;
        arg1=arg1.erase(line.find("pop"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line="pop";
        kod=10;
       
        return true;
    }
   
    return false;
}

bool citaj2(string& line,string& arg1,string& arg2,int& kod,int& velicina){
    regex r1("^(\\s*xchg[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    if (regex_match(line,r1)){
        if (line[line.find("xchg")+4]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("xchg"),5);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="xchg";
        kod=11;
        return true;
    }
    regex r2("^(\\s*mov[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r2)){
        if (line[line.find("mov")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("mov"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="mov";
        kod=12;
        return true;
    }
    regex r3("^(\\s*add[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r3)){
        if (line[line.find("add")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("add"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end()); 
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="add";
        kod=13;
        return true;
    }
    regex r4("^(\\s*sub[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r4)){
        if (line[line.find("sub")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("sub"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="sub";
        kod=14;
        return true;
    }
    regex r5("^(\\s*mul[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r5)){
        if (line[line.find("mul")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("mul"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="mul";
        kod=15;
        return true;
    }
    regex r6("^(\\s*div[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r6)){
        if (line[line.find("div")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("div"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="div";
        kod=16;
        return true;
    }
    regex r7("^(\\s*cmp[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r7)){
        if (line[line.find("cmp")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("cmp"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="cmp";
        kod=17;
        return true;
    }
    regex r8("^(\\s*not[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r8)){
        if (line[line.find("not")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("not"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="not";
        kod=18;
        return true;
    }
    regex r9("^(\\s*and[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r9)){
        if (line[line.find("and")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("and"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="and";
        kod=19;
        return true;
    }
    regex r10("^(\\s*or[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r10)){
        if (line[line.find("or")+2]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("or"),3);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="or";
        kod=20;
        return true;
    }
    regex r11("^(\\s*xor[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r11)){
        if (line[line.find("xor")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("xor"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="xor";
        kod=21;
        return true;
    }
    regex r12("^(\\s*test[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r12)){
        if (line[line.find("test")+4]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("test"),5);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="test";
        kod=22;
        return true;
    }
    regex r13("^(\\s*shl[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r13)){
        if (line[line.find("shl")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("shl"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="shl";
        kod=23;
        return true;
    }
    regex r14("^(\\s*shr[bw]?\\s+[^]+\\s*,\\s*[^]+\\s*)$");
    if (regex_match(line,r14)){
        if (line[line.find("shr")+3]=='b') velicina=0;
        else velicina=1;
        line=arg1=line.erase(line.find("shr"),4);
        arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
        arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        int pos=arg1.find(',');
        arg1.erase(pos,arg1.size()-pos);
        arg2=line.erase(0,pos+1);
        line="shr";
        kod=24;
        return true;
    }
    return false;
}

