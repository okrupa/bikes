#pragma once
//Klasa Bike
//Olga Krupa,nr indeksu 304048
#include "BikeDatabase.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <conio.h>
#include <sstream>

using namespace std;

class Bike {
private:
    int id;
    string holder;
    time_t start, end;
    //vector <int> available_bikes_list;

public:

    float account;
    float price;
    double time_hold;
    int state;
    vector <string> history;
    Bike(int id) {
        this->id = id;
    }

    //bool RentingBicycle(map<int, char> bikes);
    Bike& operator=(const Bike& b);
    void StartOfRent(BikeDatabase& database, int person, const float money);
    bool StandAssignment(BikeDatabase& database, map<int, bool>& states);
    bool FindStand(map<int, bool>& states, int stateid);
    //void AvailableBikes(map<int, char> bikes);
    void Pay();
    void FullHistory();
    void Stop(BikeDatabase& database, map<int, bool>& states);
    void HistoryOfRent(Bike& b);

    friend
        ostream& operator<< (ostream& os, const Bike& b);
    friend
        istream& operator>> (istream& is, Bike& b);
};
