#include<iostream>
#include<string>
using namespace std;
 
 class Flight{                          
 	private:
 		string flightNumber;
        string departure ;
        string destination;
        string date;
        int seatsAvailable;
    public:
    	 // Default constructor
    Flight() {
       	 flightNumber="";
    	 departure="";
    	 destination="";
    	 date="";
    	 seatsAvailable=0;
	}
    
    //constructor
    Flight(string fn,string d,string de, string dt, int s){
    	 flightNumber=fn;
    	 departure=d;
    	 destination=de;
    	 date=dt;
    	 seatsAvailable=s;
	}
	
	bool bookSeat(int seat){
		if(seat<=seatsAvailable){
		seatsAvailable-=seat;
		cout<<"Booking Confirmed!!"<<endl;
		return true;	
		}
		else{
		cout<<"No seats Availabe!!"<<endl;	
			return false;
		}
	}
	void searchFlights(Flight flight[],int size,string departure,string destination){
		bool found=false;
		for(int i=0;i<6;i++){
		if(flight[i].departure==departure && flight[i].destination==destination){
			flight[i].display();
			found=true;
		}
	}
	if(!found){
		cout<<"No Flights Available!!"<<endl;
	}
}
	string getFlightNumber() {
        return flightNumber;
    }

	void display() {
        cout << "Flight: " << flightNumber << " from " << departure
             << " to " << destination << " on " << date
             << " | Available Seats: " << seatsAvailable << endl;
    }
 };
 class Passenger{
 	private:
 	string name;
    int age;
    string gender;
    string passportNumber;
    string bookedFlightNumber;
    public:
    	 // Default constructor
    Passenger() {
        name = "";
        age = 0;
        gender = "";
        passportNumber = "";
        bookedFlightNumber = "";
    }
    //constructor
    Passenger(string n,int a,string g,string p,string b){
    	name=n;
    	age=a;
    	gender=g;
    	passportNumber=p;
    	bookedFlightNumber=b;
	}
	void display() {
        cout << "Name: " <<name<<endl;
        cout << "Age: " <<age<<endl;
        cout << "Gender: " <<gender<<endl;
        cout << "PassportNum: " <<passportNumber<<endl;
        cout << "BookFlightNum: " <<bookedFlightNumber<<endl;
    }
	
 };
 class Booking{
 	private:
    static int bookingCounter; // for unique IDs
    int bookingID;
    Passenger passenger;
    Flight flight;

public:
    Booking(Passenger p, Flight &f, int seats) {
        bookingID = ++bookingCounter; // generate unique ID
        passenger = p;

        if (f.bookSeat(seats)) {
            flight = f;
        } else {
            cout << "\nBooking failed for booking ID: " << bookingID << endl;
        }
    }
    	void display() {
        cout << "BookingID: " <<bookingID<<endl;
      passenger.display();
    flight.display();
        
    }
    
 };
 // Initialize static member
int Booking::bookingCounter = 100;

int main() {
    // Flights array
    Flight flights[6] = {
        Flight("D101", "Lahore", "Karachi", "2025-08-15", 100),
        Flight("D121", "Lahore", "Karachi", "2025-08-08", 10),
        Flight("A102", "Karachi", "Islamabad", "2025-08-16", 80),
        Flight("B103", "Lahore", "Dubai", "2025-08-20", 50),
        Flight("A104", "Islamabad", "Lahore", "2025-08-18", 60),
        Flight("F105", "Karachi", "Lahore", "2025-08-19", 70)
    };

    Booking* bookings[100];  // Array to store bookings
    int bookingCount = 0;   // Number of bookings

    char choice;
    do {
        cout << "\n===== Flight Booking Menu =====\n";
        cout << "1. Search Flights\n";
        cout << "2. Book Flight\n";
        cout << "3. Display All Bookings\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case '1': {
                string from, to;
                cout << "Enter Departure: ";
                cin >> from;
                cout << "Enter Destination: ";
                cin >> to;
                flights[0].searchFlights(flights, 6, from, to);
                break;
            }
            case '2': {
            	cout<<"Available Flights:"<<endl;
            	for(int i=0;i<6;i++){
            		flights[i].display();
				}
                string ftNum, name, gender, passport;
                int seat, age;
                cout << "Enter flight number to book: ";
                cin >> ftNum;
                cout << "Enter number of seats: ";
                cin >> seat;

                bool booked = false;
                for(int i = 0; i < 6; i++) {
                    if(flights[i].getFlightNumber() == ftNum) {
                        cout << "Enter Passenger Name: ";
                        cin >> name;
                        cout << "Enter Age: ";
                        cin >> age;
                        cout << "Enter Gender: ";
                        cin >> gender;
                        cout << "Enter Passport Number: ";
                        cin >> passport;

                       Passenger p(name, age, gender, passport, ftNum);
                       bookings[bookingCount] = new Booking(p, flights[i], seat); // create dynamically
                       bookings[bookingCount]->display();
                       bookingCount++;

                    }
                }
                if(!booked) cout << "Flight number not found or not enough seats!" << endl;
                break;
            }
            case '3': {
                cout << "\nAll Bookings:\n";
                for(int i = 0; i < bookingCount; i++) {
                    bookings[i]->display();
                    cout << "----------------\n";
                }
                break;
            }
            case '4':
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

    } while(choice != '4');

    return 0;
}

