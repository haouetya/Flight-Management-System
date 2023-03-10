
#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>
#include<string>
#include "Passenger.h"
using namespace std;



class Flight
{
    public:

	string FlightID;
	string Airline;
	string TakeOffTime;
	string ArrivalTime;
	string DeparturePlace;
	string ArrivalPlace;
	Passenger* fData;
	int NumPassengers;
	int SeatsLeft;
	float Price; 


    public:

	int FindPassenger(const Passenger& passenger);

    void AddPassenger(const Passenger& new_passenger);

	bool DeletePassenger(const Passenger& passenger);

	void setFlightID(const string& flight_ID);
	void setAirline(const string& flight_Airline);
	void setTakeOffTime(const string& flight_Takeoff);
	void setArrivalTime(const string& flight_ArrivalT);
	void setDeparturePlace(const string& flight_Depart);
	void setArrivalPlace(const string& flight_ArrivalP);
	void setPrice(float flight_Price);


	




	// global friend operator for reading/writing Flight data
	friend ostream& operator << (ostream& os, const Flight& flight) {
		os <<"The Flight Details"<<endl << "FlightID :" << flight.FlightID << endl << "Airline :" << flight.Airline << endl << "TakeOffTime(DD/MM/YYYY) :" << flight.TakeOffTime << endl << "ArrivalTime(DD/MM/YYYY) :" << flight.ArrivalTime << endl;
		os << "From :" << flight.DeparturePlace << endl << "To :" << flight.ArrivalPlace << endl;
		os << "Price :" << flight.Price <<" $"<< endl;
		return os;

	}
	friend istream& operator >> (istream& is, Flight& flight) {

		
		cout << endl;
		do {
			cout << "Flight ID :";
			is >> flight.FlightID;
		} while ((flight.FlightID).length() != 5);
		cout << "Airline :";
		is >> flight.Airline;
		cout << "TakeOffTime(DD/TIME) :";
		is >> flight.TakeOffTime;
		cout << "ArrivalTime(DD/TIME) :";
		is >> flight.ArrivalTime ;
		cout << "From :";
		is >> flight.DeparturePlace;
		cout<< "To :";
		is >> flight.ArrivalPlace;
		do {
			cout << "Price :";
			is >> flight.Price;
		} while ((flight.Price > 1000) || (flight.Price < 0));
		
		return is;

	}


public:
	// Constructors, destructor
	Flight(string Flight_Num = "", string TakeOff_Time = "", string Arrival_Time = "", string Departure_Place = "", string Arrival_Place = "", int Num_Passengers = 0, float _Price = 0) :
		FlightID(Flight_Num), TakeOffTime(TakeOff_Time), ArrivalTime(Arrival_Time), DeparturePlace(Departure_Place), ArrivalPlace(Arrival_Place),fData(NULL),NumPassengers(Num_Passengers), SeatsLeft(200), Price(_Price) {
};
	~Flight() { delete[]fData; }
	
};
#endif 
