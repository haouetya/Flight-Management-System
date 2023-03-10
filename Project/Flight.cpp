#include <iostream>
#include <fstream>
#include<string>
#include "Flight.h"
#include "Passenger.h"
using namespace std;

int Flight::FindPassenger(const Passenger& passenger) { //function to find a specific passeneger in the fData array of a flight

    for (int i = 0; i < NumPassengers; i++) {
        if (fData[i] == passenger) {
            return i;
        }
    }
    return -1;
}
void Flight::AddPassenger(const Passenger& new_passenger)  { //this function adds a passeneger to the fData array and to the .txt file corresponding to this flight
    
	if (SeatsLeft != 0 && FindPassenger(new_passenger) == -1) {
        Passenger* temp = new Passenger[NumPassengers + 1];
        for (int i = 0; i < NumPassengers; i++) {
            *(temp+i) = *(fData+i);
        }
        *(temp+NumPassengers)=new_passenger ;
        delete[] fData;
        fData = temp;
        SeatsLeft--;
        NumPassengers++;
        cout << "Seat Booked Successfully !" << endl;
        fstream flight;
        string s = new_passenger.FlightNum + ".txt";
        flight.open(s, ios::app);
        if (flight.is_open()) {
            flight << new_passenger.PassengerName << "\t" << new_passenger.CustomerID << "\t" << new_passenger.Seat << "\n";
            flight.close();
        }           
	}
    else if (FindPassenger(new_passenger) != -1) {
        cout << "This Passenger Has Already Booked a Seat On This flight !" << endl;
    }
    else {
        cout << "There Are No Empty Seats Available On This Flight !" << endl;
    }
}


bool Flight::DeletePassenger(const Passenger& passenger) { //this function delets a passeneger from the fData array and to the .txt file corresponding to this flight 
    int find = FindPassenger(passenger);
    if (find != -1) {
        Passenger* temp = new Passenger[NumPassengers - 1];
        for (int i = 0; i < NumPassengers; i++) {
            int j = 0;
            if (fData[i] != passenger) {
                temp[j] = fData[i];
                j++;
            }

        }
        delete[] fData;
        fData = temp;
        NumPassengers--;
        SeatsLeft++;
        fstream flight;
        string s = passenger.FlightNum + ".txt";
        string copy, new_version;

        flight.open(s, ios::in);
        int i = 0;

        while (getline(flight, copy)) {
            if (i != find) {
                new_version += copy + "\n";
            }
            i++;

        }
        flight.close();
        flight.open(s, ios::out);
        flight << new_version;
        flight.close();
        cout << "Flight Canceled Sucessfully" << endl;
            
        
        return true;
    }
    else {
        cout << "Passenger Not Found On This Flight" << endl;;
        return false;
    }
}


//setters to change the value of attributes

void Flight::setFlightID(const string& flight_ID) { FlightID = flight_ID; }
void Flight::setAirline(const string& flight_Airline) { Airline = flight_Airline; }
void Flight::setTakeOffTime(const string& flight_Takeoff) { TakeOffTime = flight_Takeoff; }
void Flight::setArrivalTime(const string& flight_ArrivalT) { ArrivalTime = flight_ArrivalT; }
void Flight::setDeparturePlace(const string& flight_Depart) { DeparturePlace = flight_Depart; }
void Flight::setArrivalPlace(const string& flight_ArrivalP) { ArrivalPlace = flight_ArrivalP; }
void Flight::setPrice(float flight_Price) { Price = flight_Price ; }




