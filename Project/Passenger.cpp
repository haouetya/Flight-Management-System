#include <iostream>
#include<string>
#include <fstream>
#include "Passenger.h"
using namespace std;

bool Passenger::operator==(const Passenger& passenger)const {
	return(PassengerName == passenger.PassengerName && FlightNum == passenger.FlightNum && CustomerID == passenger.CustomerID && Seat == passenger.Seat);
}
bool Passenger::operator!=(const Passenger& passenger)const {
	return(PassengerName != passenger.PassengerName && FlightNum != passenger.FlightNum && CustomerID != passenger.CustomerID && Seat != passenger.Seat);
}