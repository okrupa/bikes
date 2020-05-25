﻿#include <iostream>
#include "UserDataBase.h"
#include "BikeDatabase.h"
#include "RentalPoint.h"
#include "ClientPremium.h"

using namespace std;

#ifdef _DEBUG
#endif

int main()
{
    BikeDatabase database;
    database.importFromFile();
    vector<string> names{ "another location", "one more location" };
    MainLocation point(names, database);
    UserDataBase base;
    base.menuStart(point, database);
    database.exportToFile("exporteddatabase.txt");
  
     /* ClientPremium c("a", "b", "c", "d", 1);
    if (typeid(c) == typeid(ClientPremium))
        cout << "Jej";
    else
        cout << typeid(c).name();*/
}