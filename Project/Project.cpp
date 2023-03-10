#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Flight.h"
#include "Passenger.h"
#include <stdio.h>
#include<cstring>
#include<string>
#include<exception>
#include <ctime>
using namespace std;


class FileOpeningException : public exception  //EXCEPTION HANDLING : FILE UNOPENED
{
    virtual const char* what() const throw()
    {
        return "Unable To Open The File";
    }
}FileOpeningEx;


void time() { //This function is meant to dispaly the current local time on the screen

    time_t now = time(0);
    string dt = ctime(&now);
    dt.erase(16, 3);
    dt.erase(8, 1);
    cout << endl << "\t\t\t" "The Local Date And Time : " << dt << endl;

}

void DisplayFlights() {  //this function loads all the available flights from the .txt file and displays them on the screen

        fstream my_file;
        string flight;
        try {
            my_file.open("Flights.txt", ios::in);
            if (!my_file.is_open())
                throw(FileOpeningEx);
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }
        while (getline(my_file,flight)) {
            cout <<"\t\t\t" << flight <<endl;
        }
        my_file.close();
    
}

bool ExistantFlight(string& flightID) { //this function checks whether a flight is already existant by searching for its ID in the .txt file 
    fstream file;
    string s;
    try {
        file.open("Flights.txt", ios::in);
        if (!file.is_open())
            throw(FileOpeningEx);
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
    while (!(file.eof())) {
        file >> s;
        if (s == flightID)
            return true;;
            
    }
    return false;
}

void AddFlight(Flight& flight) { //this function adds the details of a new flight to .txt file
    if (!(ExistantFlight(flight.FlightID))) {
        fstream file;
        string s;
        try {
            file.open("Flights.txt", ios::app);
            if (!file.is_open())
                throw(FileOpeningEx);
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }        
        file << endl<< flight.FlightID << "\t" << flight.Airline << "\t" << flight.DeparturePlace << "\t" << flight.ArrivalPlace << "\t" << flight.TakeOffTime << "\t" << flight.ArrivalTime << "\t" << flight.Price << "\t";
        file.close();
        cout << "Flight Added Successfully To The System " << endl;
    }
    else {
        cout << "There is Already A Flight With The Same Flight ID You Enterd ! " << endl;
    }
  
}
void AddFlights(Flight& flight) {
        fstream file;
        string s;
        try {
            file.open("Flights.txt", ios::app);
            if (!file.is_open())
                throw(FileOpeningEx);
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }              
        file << flight.FlightID << "\t" << flight.Airline << "\t" << flight.DeparturePlace << "\t" << flight.ArrivalPlace << "\t" << flight.TakeOffTime << "\t" << flight.ArrivalTime << "\t" << flight.Price << "\t";
        file.close();
       
}
void DeleteFlight(string& s) { //this function deletes a flight from the .txt file
    fstream file;
    string copy,temp;
    int i = 0;
    try {
        file.open("Flights.txt", ios::in);
        if (!file.is_open())
            throw(FileOpeningEx);
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }          
    
    if (ExistantFlight(s)) {

        while (getline(file, copy)) {
            if (copy.substr(0, 5) != s) {
                temp += copy + "\n";
            }           
        }
        cout << "Flight Deleted Successfully" << endl;
        file.close();
        try {
            file.open("Flights.txt", ios::out);
            if (!file.is_open())
                throw(FileOpeningEx);
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }              
        file << temp;
        file.close();
        temp = s + ".txt";
        char* char_arr;
        string str_obj(temp);
        char_arr = &str_obj[0];
        remove(char_arr);


    }
    else {
        cout << "Flight Not Found !"<<endl;
    }   
    
}
void DeleteFlights(string& s) {

    fstream file;
    string copy, temp;
    int i = 0;
    try {
        file.open("Flights.txt", ios::in);
        if (!file.is_open())
            throw(FileOpeningEx);
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
        while (getline(file, copy)) {
            if (copy.substr(0, 5) != s) {
                temp += copy + "\n";
            }
        }
        file.close();
        try {
            file.open("Flights.txt", ios::out);
            if (!file.is_open())
                throw(FileOpeningEx);
        }
        catch (exception& ex)
        {
            cout << ex.what() << endl;
        }              
        file << temp;
        file.close();

}

Flight CreateInstance(const string& ID) { //this function opens the Flights.txt file and look for a flight with a given ID. If found, It constructs an object of type Flight using the informations related to that ID and returns it.
    Flight fx;
    fstream file;
    string s, temp;
    try {
        file.open("Flights.txt", ios::in);
        if (!file.is_open())
            throw(FileOpeningEx);
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
    while (!(file.eof())) {
        file >> s;
        if (s == ID)
            break;
    }

    fx.FlightID = s;
    file >> fx.Airline;
    file >> fx.DeparturePlace;
    file >> fx.ArrivalPlace;
    file >> fx.TakeOffTime;
    file >> fx.ArrivalTime;
    file >> fx.Price;
    file.close();
    return fx;
}


int main()
{   
    
    Flight flight,fx;
    fstream file1;
    int choice;
    string s,temp;
    int NbPassengers = 0;
    float price;
    Passenger* array;
    Passenger P;


    cout <<"\t\t\t\t"<< "      ******************************************" << endl;
    cout << "\t\t\t\t"<<"      * Welcome To Airlines Reservation System *" << endl;
    cout << "\t\t\t\t"<<"      ******************************************" << endl<<endl;
    DisplayFlights();
    time();
    cout <<endl<<endl<< "Airlines Reservation System Menu" << endl; //this is the main menu of the fligth management system
    cout << "1. Reserve Seat " << endl;  
    cout << "2. Cancel Flight " << endl;
    cout << "3. Add Flight To The Database " << endl;
    cout << "4. Delete Flight From The Database " << endl;
    cout << "5. Change Flight Details " << endl;
    cout << "6. Exit Program (Press Any Key)" << endl;
    cout << "Choose One: ";
    cin >> choice;
    switch (choice)//depending on the user choice, we execute the program accordingly
    {


    case 1:
        cout << "Enter The Flight ID Of Your Desired Flight ";
        cin >> s;
        if (ExistantFlight(s)) {
            fx = CreateInstance(s);
            cout << endl<< fx;
            file1.open(s + ".txt", ios::in);
            while (getline(file1, temp))
                NbPassengers++;        
            file1.clear();
            file1.seekg(0);
            array = new Passenger[NbPassengers];
            for (int i = 0; i < NbPassengers; i++) {
                string PassengerName = "";
                string FlightNum = s;
                string CustomerID = "";       //Here, I am loading the passenegers of a specific flight from the corresponding file and putting them into the fData array inside the object.
                int Seat = 0;
                file1 >> PassengerName;
                file1 >> CustomerID;
                file1 >> Seat;
                Passenger P(PassengerName, FlightNum, CustomerID, Seat);
                array[i] = P;
            }
            delete[] fx.fData;
            fx.fData = array;
            fx.NumPassengers += NbPassengers;
            fx.SeatsLeft -= NbPassengers;
            file1.close();
            cin >> P;
            P.FlightNum = s;
            fx.AddPassenger(P);
        }
        else
            cout << "Flight Not Found In The Database !" << endl;
        cout << "1. Go Back To The Main Menu" << endl;
        cout << "2. Exit Program" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            main();
            break;
        case 2:
            return 0;
            break;
        }
        break;

    case 2:
        cout << "Enter The Flight ID Of The Flight You Want To Cancel ";
        cin >> s;
        if (ExistantFlight(s)) {

            fx = CreateInstance(s);
            cout << fx;
            file1.open(s + ".txt", ios::in);
            while (getline(file1, temp))
                NbPassengers++;
            file1.clear();
            file1.seekg(0);
            array = new Passenger[NbPassengers];
            for (int i = 0; i < NbPassengers; i++) {
                string PassengerName = "";
                string FlightNum = s;
                string CustomerID = "";
                int Seat = 0;
                file1 >> PassengerName;
                file1 >> CustomerID;
                file1 >> Seat;
                Passenger P(PassengerName, FlightNum, CustomerID, Seat);
                array[i] = P;


            }
            delete[] fx.fData;
            fx.fData = array;
            fx.NumPassengers += NbPassengers;
            fx.SeatsLeft -= NbPassengers;
            file1.close();
            cin >> P;
            P.FlightNum = s;
            fx.DeletePassenger(P);
        }
        else
            cout << "Flight Not Found In The Database !"<<endl;
        cout << "1. Go Back To The Main Menu" << endl;
        cout << "2. Exit Program " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            main();
            break;
        case 2:
            return 0;
            break;
        }
        break;


    case 3:
        cout <<endl<< "Enter the Flight Details : ";
        cin >> flight;
        AddFlight(flight);
        cout << "1. Go Back To The Main Menu" << endl;
        cout << "2. Exit Program " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            main();
            break;
        case 2:
            return 0;
            break;
        }
        break;
    case 4:
        cout << "Enter the Flight ID : ";
        cin >> s;
        DeleteFlight(s);
        cout << "1. Go Back To The Main Menu" << endl;
        cout << "2. Exit Program " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            main();
            break;
        case 2:
            return 0;
            break;
        }
        break;
    case 5:
        cout <<endl<< "1. Change Airline " << endl;
        cout << "2. Change Departure Place " << endl;
        cout << "3. Change Arrival Place " << endl;
        cout << "4. Change Departure Time " << endl;
        cout << "5. Change Arrival Time " << endl;
        cout << "6. Change Price " << endl;
        cout << "7. Go Back To The Main Menu " << endl;
        cout << "8. Exit Program (Press Any Key)" << endl;
        cout << "Choose One: ";
        cin >> choice;
        switch (choice)
        {
        
        case 1:
            cout << "Enter The Flight ID ";
            cin >> s;
            if (ExistantFlight(s)) {
                fx=CreateInstance(s);
                cout << "Enter The New Airline Name ";
                cin >> temp;
                fx.setAirline(temp);
                DeleteFlights(s);
                AddFlights(fx);
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;

            }
            else {
                cout << "Flight Not Found In The Database !" << endl;
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
        case 2:
            cout << "Enter The Flight ID ";
            cin >> s;
            if (ExistantFlight(s)) {
                fx = CreateInstance(s);
                cout << "Enter The New Departure Place ";
                cin >> temp;
                fx.setDeparturePlace(temp);
                DeleteFlights(s);
                AddFlights(fx);
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
            else {
                cout << "Flight Not Found In The Database !" << endl;
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
        case 3:
            cout << "Enter The Flight ID ";
            cin >> s;
            if (ExistantFlight(s)) {
                fx = CreateInstance(s);
                cout << "Enter The New Arrival Place ";
                cin >> temp;
                fx.setArrivalPlace(temp);
                DeleteFlights(s);
                AddFlights(fx);
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;

            }
            else {
                cout << "Flight Not Found In The Database !" << endl;
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
        case 4:
            cout << "Enter The Flight ID ";
            cin >> s;
            if (ExistantFlight(s)) {
                fx = CreateInstance(s);
                cout << "Enter The New Departure Time ";
                cin >> temp;
                fx.setTakeOffTime(temp);
                DeleteFlights(s);
                AddFlights(fx);
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
            else {
                cout << "Flight Not Found In The Database !" << endl;
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
        case 5:
            cout << "Enter The Flight ID ";
            cin >> s;
            if (ExistantFlight(s)) {
                fx = CreateInstance(s);
                cout << "Enter The New Arrival Time ";
                cin >> temp;
                fx.setArrivalTime(temp);
                DeleteFlights(s);
                AddFlights(fx);
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
            else {
                cout << "Flight Not Found In The Database !" << endl;
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
        case 6:
            cout << "Enter The Flight ID ";
            cin >> s;
            if (ExistantFlight(s)) {
                fx = CreateInstance(s);
                cout << "Enter The New Price ";
                cin >> price;
                fx.setPrice(price);
                DeleteFlights(s);
                AddFlights(fx);
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
            else {
                cout << "Flight Not Found In The Database !" << endl;
                cout << "1. Go Back To The Main Menu" << endl;
                cout << "2. Exit Program " << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    main();
                    break;
                case 2:
                    return 0;
                    break;
                }
                break;
            }
        case 7 :
            main();
            break;

        default:
            return 0;
            break;
        }
    case 6:
        return 0;
        break;



     default:
         return 0;
         break;
    }

 
    return 0;

}
   

