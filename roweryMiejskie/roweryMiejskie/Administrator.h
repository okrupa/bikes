//Plik nagłówkowy klasy Administrator, Ewa Roszczyk, nr. indeksu: 304077
#ifndef Administrator_h
#define Administrator_h

#include "User.h"

class Administrator: public User
{
	bool ifAdministrator;

public:
	Administrator(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id);
	void menu(MainLocation& rental, BikeDatabase& database, UserBase& base);
	void changeUsersPassword(UserBase& base);
	void changeUsersName(UserBase& base);
	void changeUsersSurname(UserBase& base);
	void changeUsersUsername(UserBase& base);
	void deleteUser(UserBase& base);
	void deleteAdministrator(UserBase& base);
};

#endif
