#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include "citanje.h"
#include "strukture.h"
#include "tabela_simbola.h"
#include "adresiranje.h"
#include "bajtovi.h"
#include <vector>
using namespace std;

int main(int argc,char* argv[]){
    
    string ulazstring=argv[3]; 
    string izlazstring=argv[2];
    ulazstring.pop_back();
    izlazstring.pop_back();
    ulazstring+="txt";
    izlazstring+="txt";
    
    ifstream ulaz;    
    string line;
    int kod;
    int velicina;
    int reg;
    int pomeraj;
    int izraz;
    string izraz1;
    string lab;
    string arg1;
    string arg2;
    int bajt1,bajt2,bajt3,bajt4,bajt5,bajt6,bajt7,bajt8;
    ulaz.open("../test/"+ulazstring);
    izlaz.open("../test/"+izlazstring);
    
    while(getline(ulaz,line)){
            
            dodaj_za_relokacioni=0;
        
            arg1="-1";
            arg2="-1";
            izraz1="-1";
            reg=-1;
            pomeraj=-1;
            velicina=0;
            adresiranje=-1;
            pc_rel=false;
            if (labela(line,lab)){
                ins="labela";
                dodaj_vrednost(lab,lc,0,-1);
            }
            if (global(line,arg1)){
                ins=line;
                while(arg1.size()>0){
                    string argument=izdvoji_arg(arg1);
                    dodaj(argument,0,1,'x',1);
                }
            }else 
            if(is_extern(line,arg1)){
                ins=line;
                while(arg1.size()>0){
                    string argument=izdvoji_arg(arg1);
                    dodaj_vrednost(argument,0,1,-1);
                }
            }else
            if (skip(line,arg1)){
                ins=line;
                ins="dosta";
                int pomeraj;
                resi(arg1,pomeraj);
                for (int i=0; i<pomeraj; i++) niz[i+lc]="00";
                lc+=pomeraj;
            }else
            if (word(line,arg1)){
                ins=line;
                while(arg1.size()>0){
                    string argument=izdvoji_arg(arg1);
                    int upis;
                    if (!resi(argument,upis)) dodaj(argument,lc,1,'+',0); 
                    sredi_34(bajt3,bajt4,upis,1,izraz1);
                }
            }
            else if(byte(line,arg1)){
                 ins=line;
                 while(arg1.size()>0){
                    string argument=izdvoji_arg(arg1);
                    int upis;
                    if(!resi(argument,upis)) dodaj(argument,lc,0,'+',0);
                    sredi_34(bajt3,bajt4,upis,0,izraz1);
                }
            }else
            if (equ(line,arg1,arg2)) { 
             
                ins=line;
                if (resi(arg2,izraz)) {
                    
                    int dodatno;
                    resi1(arg2,dodatno);
                    dodaj_vrednost(arg1,izraz,0,dodatno);
                }
                else {
                    NS novi;
                    novi.sekcija=sek;
                    novi.ime=arg1;
                    novi.izraz=arg2;
                    nereseni.push_back(novi);
                }
             
                
            }else if (sekcija(line)){
                TS novi;
                sek=line;
                novi.broj=broj_sekcije++;
                novi.ime=line;
                novi.offset=0;
                novi.pocetak=lc;
                tabelasek.push_back(novi);
                list<Zapis> lista;
                niz_zapisa.push_back(lista);
            }else 
            if (!citaj0(line,kod)){
                if (citaj1(line,arg1,kod,velicina)){
                    ins=line; 
                    if(simbol(arg1)) {
                        dodaj(arg1,lc+2,velicina,'x',0);
                    }
                    sredi_1(bajt1,kod,velicina);
                    dodaj_za_relokacioni=1;
                    sredi_2(bajt2,arg1,reg,pomeraj,velicina,izraz1,1);
                    dodaj_za_relokacioni=0;
                    if (adresiranje!=1 && adresiranje!=2) sredi_34(bajt3,bajt4,pomeraj,velicina,izraz1);
                    pc_rel=false;
                   // izlaz<<endl;    
                }else if (citaj2(line,arg1,arg2,kod,velicina)){
                    ins=line;
                    if(simbol(arg1)) {
                        dodaj(arg1,lc+2,velicina,'x',0);
                    }
                    sredi_1(bajt1,kod,velicina);
                    dodaj_za_relokacioni=1;
                    sredi_2(bajt2,arg1,reg,pomeraj,velicina,izraz1,1);
                    dodaj_za_relokacioni=0;
                    if (adresiranje!=1 && adresiranje!=2)sredi_34(bajt3,bajt4,pomeraj,velicina,izraz1);
                    pc_rel=false;
                    dodaj_za_relokacioni=1;
                    sredi_2(bajt5,arg2,reg,pomeraj,velicina,izraz1,2);
                    if(simbol(arg2)) {
                        dodaj(arg2,lc,velicina,'x',0);
                    }
                    dodaj_za_relokacioni=0;
                    if (adresiranje!=1 && adresiranje!=2)sredi_34(bajt6,bajt7,pomeraj,velicina,izraz1);
                    //izlaz<<endl;
                }
            }else {
                ins=line;
                sredi_1(bajt1,kod,velicina);
                //izlaz<<endl;
            }
            
                                      
    }
    ins="equ";
    ostalo();
    pisi();
    ins="dosta";
    prodji();
    pisi_sek();  
    prodji_relativno(); 
    
    prodji_relokacioni();
    pisi_relokacioni();
    //for (int i=0; i<lc; i++) cout<<niz[i]<<" ";
    pisi_masinski_relokacioni();
    ulaz.close();
    izlaz.close();
    return 0;
}