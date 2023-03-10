#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>
#include <fstream>
#include<string>
using namespace std;


class Passenger
{
	public:

	string PassengerName;
	string FlightNum;
	string CustomerID;
	int Seat;


	// global friend operator for reading/writing passenger data
	friend ostream& operator << (ostream& os, const Passenger& passenger) {
		
		os <<endl<< "Passenger Name : " << passenger.PassengerName << endl;
		os << "Flight ID : " << passenger.FlightNum << endl ;
		os << "Customer ID : " << passenger.CustomerID << endl;
		os << "Seat Number : " << passenger.Seat << endl;
		
		return os;

	}
	friend istream& operator >> (istream& is, Passenger& passenger) {


		cout << endl << "Passenger Name : ";
		is >> passenger.PassengerName;
		cout << "Customer ID : ";
		is >> passenger.CustomerID;
		cout << "Seat Number : ";
		is >> passenger.Seat;
		return is;

	}


public:
	// Constructors, destructor
	Passenger(string Passengername = "", string Flight_Num = "", string Customer_ID="", int seat=0) : PassengerName(Passengername), FlightNum(Flight_Num), CustomerID(Customer_ID), Seat(seat) {};
	Passenger(const Passenger& theOther) {
		PassengerName = theOther.PassengerName;
		FlightNum = theOther.FlightNum;
		CustomerID = theOther.CustomerID;
		Seat = theOther.Seat;
	}
	~Passenger() {}
	bool operator==(const Passenger& passenger)const;
	bool operator!=(const Passenger& passenger)const;

};
#endif
