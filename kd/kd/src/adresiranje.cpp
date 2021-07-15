#include "adresiranje.h"
#include "bajtovi.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

bool skok(){
    return ((ins=="int") || (ins=="call") || (ins=="jmp") || (ins=="jeq") || (ins=="jne") || (ins=="jgt"));
}

int regdir(string arg1){
    regex r1("^(\\%r\\d+[h|l]?)$");
    regex r2("^(\\*\\%r\\d+[h|l]?)$");
    if (regex_match(arg1,r1)){
        arg1.erase(0,2);
        if ((arg1.size()>0) && ((stoi(arg1) >= 0) && (stoi(arg1)<=15))) return stoi(arg1);
    }
    else if (regex_match(arg1,r2)  &&  skok()){
        arg1.erase(0,3);
        if ((arg1.size()>0) && ((stoi(arg1) >= 0) && (stoi(arg1)<=15))) return stoi(arg1);
    }
    return -1;
}

int regind(string arg1){
    regex r1("^(\\(\\%r\\d+\\))$");
    regex r2("^(\\*\\(\\%r\\d+\\))$");
    if (regex_match(arg1,r1)){
        arg1.erase(0,1);
        arg1.erase(arg1.size()-1,arg1.size());    
    }else if (regex_match(arg1,r2)  &&  skok()){
        arg1.erase(0,2);
        arg1.erase(arg1.size()-1,arg1.size());
    }
    return regdir(arg1);
}

int regindpom(string arg1,int& pomeraj,int velicina){
    regex r1("^(\\-?[\\d|\\w]+\\(\\%r\\d+\\))$");
    regex r2("^(\\*[\\d|\\w]+\\(\\%r\\d+\\))$");
    regex r3("^(\\-?[\\d|\\w]+\\(\\%pc\\))$");
    regex r4("^(\\*[\\d|\\w]+\\(\\%pc\\))$");
    string registar="-1";
    string pomerajj=arg1;
    if(regex_match(arg1,r3)) {
        arg1.replace(arg1.find("pc"),2,"r7");
        pc_rel=true;
    }
    if(regex_match(arg1,r1)){ 
        pomerajj.erase(pomerajj.find('('),pomerajj.size());
        registar=arg1;
        registar.erase(0,registar.find('(')+3);
        registar.erase(registar.size()-1,registar.size());
        if (registar=="7") pc_rel=true;
        if (!resi(pomerajj,pomeraj)){
            dodaj(pomerajj,lc+1,velicina,'+',0);
        }
    }else{
        if(regex_match(arg1,r4) && skok()) {
            arg1.replace(arg1.find("pc"),2,"r7");
            pc_rel=true;
        }
        if(regex_match(arg1,r2) && skok()){
        pomerajj.erase(0,1);
        pomerajj.erase(pomerajj.find('('),pomerajj.size());
        registar=arg1;
        registar.erase(0,registar.find('(')+3);
        registar.erase(registar.size()-1,registar.size());
        if (registar=="7") pc_rel=true;
        if (!resi(pomerajj,pomeraj)){
            dodaj(pomerajj,lc+1,velicina,'+',0);
        }
    }
    }
    if (simbol(pomerajj) && globalan(pomerajj)) pomeraj=0;
    return stoi(registar);
}

int immed(string arg1,int& reg,int velicina){
    
    regex r1("^(\\$\\-?[0x]?\\w+)$");  
    regex r2("^(\\$0x\\w+)$");
    regex r3("^(\\-?[0x]?\\w+)$");  
    regex r4("^(0x\\w+)$");
    int vrednost;  
    if (regex_match(arg1,r1) || regex_match(arg1,r2)){
        arg1.erase(0,1);
        reg=-1;
        if (!resi(arg1,vrednost)){
            dodaj(arg1,lc+1,velicina,'+',0);
        }
        if (simbol(arg1) && globalan(arg1)) vrednost=0;
        return vrednost;
    }else if ((regex_match(arg1,r3) || regex_match(arg1,r4)) && skok()){
        reg=-1;
        if (!resi(arg1,vrednost)){
            //dodaj(arg1,lc+1,velicina,'+',0);
        }
        return vrednost;
    }
    return -1;
}

int nadji_adresiranje(string arg1,int& reg,int& pomeraj,string& izraz,int velicina){
   pomeraj=immed(arg1,reg,velicina);
   if (pomeraj!=-1) {
       izraz="-1";
       return 0;
   }
   reg=regdir(arg1);
   if (reg!=-1) {
       pomeraj=0;
       izraz="-1";
       return 1;
   }
   
   reg=regind(arg1);
   if (reg!=-1) {
       pomeraj=0;
       izraz="-1";
       return 2;
   }

   reg=regindpom(arg1,pomeraj,velicina);
   if (reg!=-1) {
       izraz="-1";
       return 3;
   }
   izraz="-1";
   if (skok()) arg1.erase(0,1);
  
   arg1.erase(remove(arg1.begin(), arg1.end(), ' '), arg1.end());
   arg1.erase(remove(arg1.begin(), arg1.end(), '\t'), arg1.end());
   if (simbol(arg1)) { pomeraj=0; izraz=arg1; }
   else{
       if(!hex_to_int(arg1,pomeraj)){
          if(!bin_to_int(arg1,pomeraj)){
              regex r("^(\\d+)$");
              if(regex_match(arg1,r)) pomeraj=stoi(arg1);
              else izraz=arg1; 
          }
       }
   }
   return 4;
}


