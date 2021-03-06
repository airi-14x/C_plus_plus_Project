/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   part1driver.cpp
 * Author: Earl Steven Aromin 40004997
 *
 * Created on September 19, 2017, 7:31 PM
 */

#include <cstdlib>
#include <iostream>
#include <iterator>
#include "Map.h"
using std::string;
using std::cout;
using std::endl;

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Continent nohr{"Nohr"}; //continent 2
    Continent* pnohr = &nohr;
    Continent hoshido{"Hoshido"}; //continent 1
    Continent* phoshido = &hoshido;

    Map ylisse{"Ylisse"}; //Map name
    ylisse.addContinent(phoshido);
    ylisse.addContinent(pnohr);


    //countries that belong to nohr
    Country valla{"Valla"};
    Country sagesse{"Sagesse"};
    Country nestra{"Nestra"};
    Country car{"Carrion"};
    Country plegia{"Plegia"};
    Country valentia{"Valentia"};
    Country jugdral{"Jugdral"};
    Country archanea{"Archanea"};
    Country etruria{"Etruria"};
    Country gallia{"Gallia"};

    //pointers for nohrian countries
    Country* pval = &valla;
    Country* psag = &sagesse;
    Country* pnes = &nestra;
    Country* pcar = &car;
    Country* ppleg = &plegia;
    Country* plentia = &valentia;
    Country* pjugd = &jugdral;
    Country* parch = &archanea;
    Country* petr = &etruria;
    Country* pgal = &gallia;

    //shoving ccountries in nohr
    pnohr->addCountry(pval);
    pnohr->addCountry(psag);
    pnohr->addCountry(pnes);
    pnohr->addCountry(pcar);
    pnohr->addCountry(ppleg);
    pnohr->addCountry(plentia);
    pnohr->addCountry(pjugd);
    pnohr->addCountry(parch);
    pnohr->addCountry(petr);
    pnohr->addCountry(pgal);

    //Hoshido countries
    Country mokushu{"Mokushu"};
    Country kohga{"Kohga"};
    Country izumo{"Izumo"};
    Country sacae{"Sacae"};

    Country* pmokushu = &mokushu;
    Country* pkohga = &kohga;
    Country* pizumo = &izumo;
    Country* psacae = &sacae;

    phoshido->addCountry(pmokushu);
    phoshido->addCountry(pkohga);
    phoshido->addCountry(pizumo);
    phoshido->addCountry(psacae);


    //Paths within hoshido    
    ylisse.link(pmokushu, pkohga);
    ylisse.link(pkohga, pizumo);
    ylisse.link(pizumo, psacae);

    //paths in nohr
    ylisse.link(pval, psag);
    ylisse.link(pval, pnes);
    ylisse.link(pnes, pcar);
    ylisse.link(pcar, ppleg);
    ylisse.link(pnes, ppleg);
    ylisse.link(ppleg, plentia);
    ylisse.link(ppleg, pjugd);
    ylisse.link(pjugd, parch);
    ylisse.link(parch, petr);
    ylisse.link(petr, pgal);
    //link between nohr and hoshido
    ylisse.link(pjugd, pizumo);
    
    cout << "\n\nValidating " << phoshido->getName() << endl;
    ylisse.valiCont(phoshido);

    cout << "\nValidating Map through " << pnes->getName() << endl;
    ylisse.validate(pnes);

    return 0;
}

