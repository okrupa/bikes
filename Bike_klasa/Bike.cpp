#include "Bike.h"
//Klasa Bike
//Olga Krupa,nr indeksu 304048
ostream& operator<<(ostream& os, const Bike& b)
{
    os << b.id << endl;
    os << b.holder << endl;
    os << b.account << endl;
    os << b.price << endl;
    os << b.time_hold << endl;
    os << b.start << endl;
    os << b.end << endl;
    for (std::vector<string>::const_iterator i = b.history.begin(); i != b.history.end(); ++i)
        os << *i << endl;

    return os;
}

istream& operator>>(istream& is, Bike& b)
{
    is >> b.id >> b.holder >> b.account;
    return is;
}

Bike& Bike::operator=(const Bike& b)
{
    // self-assignment check
    //zmiana roweru, np w przypadku checi zmiany rowru lub zepsucia poprzedniego, przypisanie nowego roweru
    if (this == &b)
        return *this;

    holder = b.holder;
    account = b.account;
    start = b.start;
    price = b.price;
    end = 0;
    time_hold = 0;

    return *this;
}

void Bike::FullHistory() //Funkcja wypisuje cala historie wypozyczenia
{
    cout << endl;
    for (auto const& v : history)
    {
        cout << v << endl;
    }
}
void Bike::HistoryOfRent(Bike& b) //wpisanie obiektu do historii
{
    if (b.id == id)
    {
        string line = b.holder + " | " + to_string(b.state) + " | " + to_string(b.time_hold) + " | " + to_string(b.price);
        if (history.empty())
        {
            string pi = "Bike " + to_string(b.id) + ": " + "USER | STATE | TIME OF RENT | PRICE\n";
            b.history.push_back(pi);
            b.history.push_back(line);
        }
        else
        {
            history.push_back(line);
        }
    }
    else
    {
        b.HistoryOfRent(b);
    }
}

void Bike::Stop(map<int, char>& bikes, map<int, int>& states) //koniec wypozyczenia, po wys�aniu wiadomosci o checi oddania roweru od uzytkownika lub wypozyczalni
{

    bool endassingnment;
    endassingnment = StandAssignment(states);
    if (endassingnment)
    {
        time(&end);
        time_hold = difftime(end, start) / 60;
        cout << "Time of rent " << time_hold << " minutes." << endl;
        Pay();
        bikes[id] = 0;
    }
}

void Bike::Pay()
{
    //Pobieranie �rodk�w z konta u�ytkownika
    int ftime;
    double mtime = time_hold;
    if (mtime < 21)
    {
        account = account - 1;
        price = 1;
    }
    if (mtime > 20 && mtime < 61)
    {
        account -= 2;
        price = 2;
    }
    if (mtime > 60 && mtime < 121)
    {
        account -= 5;
        price = 5;
    }
    if (mtime > 120 && mtime < 181)
    {
        account -= 10;
        price = 10;
    }
    if (mtime > 180)
    {
        ftime = mtime - 180;
        price = 10 + ((ftime / 60 + 1) * 7);
        account -= price;
    }
};

void Bike::StartOfRent(map<int, int>& states, map<int, char>& bikes, string person, float money)
{
    holder = person;
    account = money;
    //Sprawdzanie konta
    if (account < 10)
    {
        cout << "You do not have enough money to rent a bike." << endl;
        bikes[id] == 'F';
        //funkcja do dodania �rodk�w, odes�anie do u�ytkownika?
    }
    else
    {
        int state;
        //zwalnianie stojaka
        for (map<int, int>::iterator it = states.begin(); it != states.end(); ++it)
        {
            if (it->second == id)
            {
                state = it->first;
                states[state] = 1;
            }
        }
        end = 0;
        time_hold = 0;
        price = 0;
        /*for (auto it = states.begin(); it != states.end(); ++it)
            if (it->second == id)
            {
                it->second == 0;
            }*/
            //  Obliczanie czasu wypozyczenia, informacja o czasie wypzyczenia oraz wywolanie funkcji do pobrania srodkow
        cout << "Rental time has begun" << endl;
        time(&start);
        //odliczanie czasu od wynajecia 
    }

};

bool Bike::FindStand(map<int, int>& states, int stateid)
{
    bool available = false;
    std::map<int, int>::iterator itr;
    itr = states.find(stateid);
    if (states.find(stateid) != states.end())
    {
        if (itr->second == 1)
        {
            available = true;
        }
    }
    return available;
};

bool Bike::StandAssignment(map<int, int>& states)
{
    int stateid;
    bool choice = false;
    bool use = false;
    char c;
    bool ava;
    do
    {
        cout << "Give id of state" << endl;
        cin >> stateid;
        ava = FindStand(states, stateid);
        if (ava == true)
        {
            cout << "Would you like to use this state [Y - YES/N - NO]" << endl;
            cin >> c;
            if (c == 'Y' || c == 'y')
            {
                states[stateid] = id;
                state = stateid;
                choice = true;
                use = true;
            }
            else if (c == 'N' || c == 'n')
            {
                cout << "Would you like to use another state [Y - YES/N - NO]" << endl;
                cin >> c;
                if (c == 'N' || c == 'n')
                {
                    choice = true;
                }

            }
            else
            {
                cout << "You put wrong value" << endl;
            }
        }
        else
        {
            cout << "State is not available" << endl;
            cout << "Would you like to use another state [Y - YES/N - NO]" << endl;
            cin >> c;
            if (c == 'N' || c == 'n')
            {
                choice = true;
            }
        }

    } while (choice == false);
    return use;

};

//poczatkowo sprawdzalam czy rower moze byc wypozyczony, po konsultacji z osoba odpowiedzialna za wypozyczalnie
//prawdopodobnie wypozyczalnia bedzie sprawdzac stan roweru, a nastepnie wysylac id do obslugi przez klase BIKE
//ponizsze funkcje sluzyly do sprawdzania stanu[zajety/wolny]

//bool Bike::RentingBicycle(map<int, char> bikes)
//{
//  //poczatkowo sprawdzalam czy rower moze byc wypozyczony, po konsultacji z osoba odpowiedzialna za wypozyczalnie
//  //prawdopodobnie wypozyczalnia bedzie sprawdzac stan roweru, a nastepnie wysylac id do obslugi przez klase BIKE
//
//
//    // przyjmuje ze indeks i stan jest po��czony map�.
//    // zwraca stan roweru , zaj�ty czy woly, pobiera od bazy
//    // jesli zwraca zajety, prosi o podanie nowego indeksu 
//    int newid;
//    bool free;
//    do 
//    {
//        if (bikes.count(id) > 0)
//        {
//            if (bikes[id] == 'F')
//            {
//                bikes[id] = 'O';
//                free = true;
//                cout << "You rent bike number " << id <<  endl;
//                return free;
//            }
//            else
//            {
//                cout << "Bike is occupied, please choose another one[put new id]" << endl;
//                cin >> newid;
//                id = newid;
//                free = false;
//            }
//        }
//        else
//        {
//            cout << "Bike Not Found, , please choose another one[put new id]" << endl;
//            cin >> newid;
//            id = newid;
//            free = false;
//        }
//    } while (free == false);
//    return free;
//};


//void Bike::AvailableBikes(map<int, char> bikes)
//{
//    map<int, char>::iterator it_b = bikes.begin();
//    for (map<int, char>::iterator it_b = bikes.begin(); it_b != bikes.end(); ++it_b)
//    {
//        if (it_b->second == 'F')
//        {
//            available_bikes_list.push_back(it_b->first);
//        }
//    }
//};