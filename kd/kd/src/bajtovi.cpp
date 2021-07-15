#include "bajtovi.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include "citanje.h"
#include "strukture.h"
#include "tabela_simbola.h"
#include "adresiranje.h"
#include <vector>
using namespace std;


void sredi_1(int& bajt1,int& kod,int velicina){
    bajt1=kod=kod<<3;
    bajt1=bajt1|(velicina<<2);
    if (bajt1<=15){ 
       // izlaz<<"0";
        niz[lc]="0"; 
    }
   // izlaz<<std::hex<<bajt1<<" ";
    //dodaje string u niz preko streama
    std::stringstream stream;
    stream << std::hex << bajt1;
    niz[lc]+=stream.str();
    //
    lc++;
}

void sredi_2(int& bajt2,string arg1,int& reg,int& pomeraj,int velicina,string& izraz,int br_arg){
    adresiranje=bajt2=nadji_adresiranje(arg1,reg,pomeraj,izraz,velicina);
    if (adresiranje==0 && br_arg==2){
        izlaz<<"Greska!!!! Koristite neposredno adresiranje za destinacioni operand a instukcija je "<<ins;
        izlaz.close();
    }
    if (adresiranje==0 && br_arg==1 && ins=="shr"){
        izlaz<<"Greska!!!! Koristite neposredno adresiranje za destinacioni operand a instukcija je "<<ins;
        izlaz.close();
    }
    if (adresiranje==0 && (ins=="pop")){
        izlaz<<"Greska!!!! Koristite neposredno adresiranje za destinacioni operand a instrukcija je "<<ins;
        izlaz.close();
    }
    bool uslov=false;
    if ((bajt2==4) && skok() && izraz!="-1") {
        dodaj(izraz,lc+1,velicina,'x',0);
    }
    
    if ((bajt2==1) && (velicina==0)) {
    
        if (arg1[arg1.size()-1]=='l') arg1.erase(arg1.size()-1,arg1.size());
        else if (arg1[arg1.size()-1]=='h') {
            arg1.erase(arg1.size()-1,arg1.size());
            uslov=true;
        }
    }
    if (bajt2==3 && reg==7){
        Relativno r;
        r.adresa=lc+1;
        r.sekcija=sek;
        r.simbol=arg1;
        r.simbol.erase(r.simbol.find('('),r.simbol.size());
        if (skok()) r.simbol.erase(0,1);
        if (ins=="push" || ins=="pop" || skok()){
            r.sledeca=lc+3;
        }else{
           if (br_arg==1) r.sledeca=lc+6;
           if (br_arg==2) r.sledeca=lc+3;
        } 
        relativno.push_back(r);
    }
    if (bajt2!=4) izraz="-1";
    bajt2<<=5;
    if (reg!=-1)reg=reg<<1;
    else reg=0;
    bajt2=bajt2|reg;
    if (uslov) bajt2|=1;
    if (bajt2<=15) {
     //   izlaz<<"0";
        niz[lc]="0";
    }
    //izlaz<<std::hex<<bajt2<<" ";
    //dodaje string u niz preko streama
    std::stringstream stream;
    stream << std::hex << bajt2;
    niz[lc]+=stream.str();
    //
    lc++;
}

void sredi_34(int& bajt3,int& bajt4,int& pomeraj,int velicina,string& izraz){
    if (izraz!="-1" && !simbol(izraz)){
       
        int vrednost=0;
        char znak='+';
        regex r1("^([\\w|\\d]+\\+.*)$");
        regex r2("^([\\w|\\d]+\\-.*)$");
        regex r3("^([\\+|\\-][\\w|\\d]+.*)$");
        regex r4("^([\\w|\\d]+)$");
        while(izraz.size()>0){
            if (regex_match(izraz,r1)){
                string izraz1=izraz;
                izraz1.erase(izraz1.find('+'),izraz1.size());
                if (!simbol(izraz1)){
                    if (znak=='+') vrednost+=stoi(izraz1);
                    else vrednost-=stoi(izraz1);
                    izraz.erase(0,izraz.find('+'));
                }
                else{
                    int dod;
                    dodaj_relokacioni(lc,"R_386_16",izraz1);
                    if (nadji(izraz1,dod)){
                        if (znak=='+') vrednost+=dod;
                        else vrednost-=dod;
                        izraz.erase(0,izraz.find('+'));
                    }else{
                        dodaj(izraz1,lc,velicina,znak,0);
                        izraz.erase(0,izraz.find('+'));
                    }
                }
            }else if (regex_match(izraz,r2)){
                    string izraz1=izraz;
                    izraz1.erase(izraz1.find('-'),izraz1.size());
                    if (!simbol(izraz1)){
                        if (znak=='+') vrednost+=stoi(izraz1);
                        else vrednost-=stoi(izraz1);
                        izraz.erase(0,izraz.find('-'));
                    }
                    else{
                        int dod;
                        dodaj_relokacioni(lc,"R_386_16",izraz1);
                        if (nadji(izraz1,dod)){
                            if (znak=='+') vrednost+=dod;
                            else vrednost-=dod;
                            izraz.erase(0,izraz.find('-'));
                        }else{
                            dodaj(izraz1,lc,velicina,znak,0);
                        }
                    }
                  } else if (regex_match(izraz,r3)){
                            znak=izraz[0];
                            izraz.erase(0,1);
                        }else if (regex_match(izraz,r4)){
                                  if (!simbol(izraz)){
                                      
                                      if (znak=='+') vrednost+=stoi(izraz);
                                      else vrednost-=stoi(izraz);
                                      izraz.erase(0,izraz.size());
                                  }
                                  else{
                                      int dod;
                                      dodaj_relokacioni(lc,"R_386_16",izraz);
                                      if (nadji(izraz,dod)){
                                          if (znak=='+') vrednost+=dod;
                                          else vrednost-=dod;
                                          izraz.erase(0,izraz.size());
                                      }else{
                                          dodaj(izraz,lc,velicina,znak,0);
                                          izraz.erase(0,izraz.size());
                                      }
                                  }           
                              }
        }
        pomeraj=vrednost;
    }
    if (simbol(izraz)){
        if (!nadji(izraz,pomeraj)) {
            pomeraj=0;
            
            //dodaj(izraz,lc,velicina,'x',0);
        }
        if (globalan(izraz)) pomeraj=0;
        dodaj_relokacioni(lc,"R_386_16",izraz);
    }
    if (velicina==0){
        bajt4=-1;
        bajt3=pomeraj;
    }
    else {
        bajt4=pomeraj>>8;
        bajt3=(pomeraj&(0xFF));
    }
    if (velicina) { 
        if (bajt3<=15 && bajt3>=0) {
            //izlaz<<"0";
            niz[lc]="0";
        }
        
        //dodaje string u niz preko streama
        std::stringstream stream;
        stream << std::hex << bajt3;
        std::stringstream org_stream;
        string pomocni=stream.str();
        if (pomocni.size()>2) {
            pomocni.erase(0,6);
            org_stream<<pomocni;
        }else org_stream<<stream.str();
        //izlaz<<org_stream.str()<<" ";
        niz[lc]+=org_stream.str();
        //
        lc++;
        if (bajt4<=15 && bajt4>=0) {
            //izlaz<<"0";
            niz[lc]="0";
        }
        
        std::stringstream stream1;
        std::stringstream org_stream1;
        stream1 << std::hex << bajt4;
        pomocni=stream1.str();
        if (pomocni.size()>2){
            pomocni.erase(0,6);
            org_stream1<<pomocni;
        }else org_stream1<<stream1.str();
        niz[lc]+=org_stream1.str();
      // izlaz<<org_stream1.str()<<" ";
        lc++;
    }
    else {
        if (bajt3<=15 && bajt3>=0) {
          //  izlaz<<"0";
            niz[lc]="0";
        }
        std::stringstream org_stream;
        std::stringstream stream;
        stream << std::hex << bajt3;
        string pomocni=stream.str();
        if (pomocni.size()>2){
            pomocni.erase(0,6);
            org_stream<<pomocni;
        }else org_stream<<stream.str();
        niz[lc]+=org_stream.str();
        lc++;
    }
}

bool simbol(string arg){
    regex r("^([A-z]+\\w*)$");
    if (regex_match(arg,r)) return true;
    return false;
}

bool hex_to_int(string& arg1,int& vrednost){
    
    regex r("^(0x\\w+)$");
    if (regex_match(arg1,r)){  
        arg1.erase(0,2);
        vrednost=stoi(arg1,0,16);
        return true;
    }
    return false;
}

bool bin_to_int(string& arg1,int& vrednost){
    regex r("^(0b\\d+)$");
    if (regex_match(arg1,r)){  
        arg1.erase(0,2);
        vrednost=stoi(arg1,0,2);
        return true;
    }
    return false;
}


