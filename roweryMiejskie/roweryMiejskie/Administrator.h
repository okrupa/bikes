//Plik nagłówkowy klasy Administrator, Ewa Roszczyk, nr. indeksu: 304077
#ifndef Administrator_h
#define Administrator_h

#include "User.h"

class Administrator: public User
{
	bool ifAdministrator;

public:
	Administrator(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword, const int& id);
	void menu(MainLocation& rental, BikeDatabase& database, UserBase& base);
	void viewRentalPointLocation(MainLocation& rental);
	void disactivateRentalPoint(MainLocation& rental);
	void addBike(MainLocation& rental) {}
	void deleteBike(MainLocation& rental) {}
	void changeUsersPassword(UserBase& base);
	void changeUsersName(UserBase& base);
	void changeUsersSurname(UserBase& base);
	void changeUsersUsername(UserBase& base);
	void deleteUser(UserBase& base);
	void deleteAdministrator(UserBase& base);
};

#endif
