#include "view.h"
#include "Map.h"
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

view::view(Map* m)
{
    subject = m;
    subject->Attach(this);
    displayConti = false;
    displayPerc = false;
}

view::~view()
{
    //dtor
}

void view::setDisplayConti(bool b)
{
    displayConti = b;
}


void view::setDisplayPerc(bool b)
{
    displayPerc = b;
}


void view::Update() {
    state = subject->getState();

    if(displayConti && state->ownershipChange){
        for(int i = 0; i < state->owners.size(); i++){
            cout << state->owners[i] << endl;
        }
        cout << endl;
    }

    if(displayPerc)
        print();
}

void view::print() {
    map<string,int> players = state->players;

    for (MapIterator it=players.begin(); it!=players.end(); ++it) {
        double percentageOwned = it->second / (double)state->numOfCountries * 100;
        cout << it->first << "\t" << std::fixed << setprecision(1) << percentageOwned << "%\t";
        for(int i = 2; i < 100; i = i + 2){
            if(percentageOwned >= i)
                cout << "|";
            else
                break;
        }
        cout << endl;
    }
    cout << endl;
}

