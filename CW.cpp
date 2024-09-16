#include <iostream>
#include <cstring> // for string functions
using namespace std;

class Passenger {
public:
    char passportId[50]; // Passport ID of the passenger
    string bookedFlightNumber; // Flight number booked by the passenger
    string bookedDestination; // Destination of the booked flight
    string bookedDepartureTime; // Departure time of the booked flight
    string bookedArrivalTime; // Arrival time of the booked flight
    string bookedSeatClass; // Seat class of the booked flight: "First", "Business", "Economy"
    double bookedPrice; // Price of the booked flight
    Passenger* next; // Pointer to the next passenger node

    // Constructor
    Passenger(const char* passportId) {
        strcpy(this->passportId, passportId);
        next = nullptr; // Initialize next pointer to nullptr
        // Initialize booking details
        bookedFlightNumber = "";
        bookedDestination = "";
        bookedDepartureTime = "";
        bookedArrivalTime = "";
        bookedSeatClass = "";
        bookedPrice = 0.0;
    }
};

class Flight {
private:
    string flight_number, destination, departure_time, arrival_time;
    int first_class_seats, business_class_seats, economy_class_seats;
    double first_class_price, business_class_price, economy_class_price;
    Passenger* passengersHead; // Pointer to the head of the linked list of passengers

public:
    Flight();
    void addFlight();
    void displayAllFlights();
    void bookSeat();
    void findBookingByPassportId(const char* passportId);
    bool isAdmin;
};

Flight::Flight() {
    passengersHead = nullptr;
    isAdmin = false; // Initially assume the user is not an admin
}

void Flight::addFlight() {
    if (!isAdmin) {
        cout << "Only admin can add flights." << endl;
        return;
    }
    cout << "Enter flight details: " << endl;
    cout << "Flight Number: ";
    cin >> flight_number;

    cout << "Enter number of available seats: " << endl;
    cout << "First Class: ";
    cin >> first_class_seats;
    cout << "Business Class: ";
    cin >> business_class_seats;
    cout << "Economy Class: ";
    cin >> economy_class_seats;

    cout << "Enter prices for each class: " << endl;
    cout << "First Class: ";
    cin >> first_class_price;
    cout << "Business Class: ";
    cin >> business_class_price;
    cout << "Economy Class: ";
    cin >> economy_class_price;

    cout << "Enter Destination : " << endl;
    cin >> destination;

    cout << "Arrival Time : " << endl;
    cin >> arrival_time;

    cout << "Departure Time : " << endl;
    cin >> departure_time;

    cout << "Flight added successfully!" << endl;
}

void Flight::displayAllFlights() {
    cout << "\nAvailable Flights:" << endl;
    cout << "Flight Number: " << flight_number << endl;
    cout << "Destination: " << destination << endl;
    cout << "Departure Time: " << departure_time << ", Arrival Time: " << arrival_time << endl;
    cout << "Available Seats: " << endl;
    cout << "First Class: " << first_class_seats << endl;
    cout << "Business Class: " << business_class_seats << endl;
    cout << "Economy Class: " << economy_class_seats << endl;
    cout << "------------------------" << endl;
}

void Flight::bookSeat() {
    string passportId;
    string class_type;
    int no_Of_Seats;

    cout << "Enter your Passport ID: ";
    cin >> passportId;

    cout << "Enter desired seat class (First, Business, Economy): ";
    cin >> class_type;
    cout << "Enter Number of Seats : ";
    cin >> no_Of_Seats;

    Passenger* passenger = new Passenger(passportId.c_str()); // Create a new Passenger object
    passenger->bookedFlightNumber = flight_number;
    passenger->bookedDestination = destination;
    passenger->bookedDepartureTime = departure_time;
    passenger->bookedArrivalTime = arrival_time;
    passenger->bookedSeatClass = class_type; // Store the class type
    passenger->bookedPrice = (class_type == "First") ? (first_class_price * no_Of_Seats) :
                            (class_type == "Business") ? (business_class_price * no_Of_Seats) :
                            (economy_class_price * no_Of_Seats);

    // Add the passenger to the linked list
    if (passengersHead == nullptr) {
        passengersHead = passenger;
    } else {
        Passenger* currentPassenger = passengersHead;
        while (currentPassenger->next != nullptr) {
            currentPassenger = currentPassenger->next;
        }
        currentPassenger->next = passenger;
    }

    // Decrease available seats based on class
    if (class_type == "First") {
        first_class_seats -= no_Of_Seats;
    } else if (class_type == "Business") {
        business_class_seats -= no_Of_Seats;
    } else if (class_type == "Economy") {
        economy_class_seats -= no_Of_Seats;
    }
}

void Flight::findBookingByPassportId(const char* passportId) {
    cout << "Booking details for Passport ID: " << passportId << endl;
    // Search for booking details by passport ID
    Passenger* currentPassenger = passengersHead;
    bool found = false;
    while (currentPassenger != nullptr) {
        if (strcmp(currentPassenger->passportId, passportId) == 0) {
            found = true;
            cout << "Flight Number: " << currentPassenger->bookedFlightNumber << endl;
            cout << "Destination: " << currentPassenger->bookedDestination << endl;
            cout << "Departure Time: " << currentPassenger->bookedDepartureTime << ", Arrival Time: " << currentPassenger->bookedArrivalTime << endl;
            cout << "Class: " << currentPassenger->bookedSeatClass << endl;
            cout << "Price: $" << currentPassenger->bookedPrice << endl;
            break;
        }
        currentPassenger = currentPassenger->next;
    }
    if (!found) {
        cout << "No booking found for Passport ID: " << passportId << endl;
    }
}

int main() {
    int userType;
    int choice;
    char passportId[50];
    Flight y;

    cout << "Are you an admin or a passenger?" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Passenger" << endl;
    cout << "Enter your choice: ";
    cin >> userType;

    if (userType == 1) {
        y.isAdmin = true;
    }

    do {
        cout << "\nFlight Ticket Booking System" << endl;
        if (y.isAdmin) {
            cout << "1. Add Flight" << endl;
            cout << "2. Display All Flights" << endl;
            cout << "3. Switch to Passenger Mode" << endl;
            cout << "0. Exit" << endl;
        } else {
            cout << "1. View All Flights" << endl;
            cout << "2. Book Seat" << endl; // Changed to "Book Seat"
            cout << "3. View Booking Details" << endl;
            cout << "4. Switch to Admin Mode" << endl;
            cout << "0. Exit" << endl;
        }
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (y.isAdmin) {
                    y.addFlight();
                } else {
                    // Display all available flights
                    y.displayAllFlights();
                }
                break;
            case 2:
                if (y.isAdmin) {
                    y.displayAllFlights();
                } else {
                    // Display all available flights
                    y.displayAllFlights();
                    // Book a seat
                    y.bookSeat();
                }
                break;
            case 3:
                if (y.isAdmin) {
                    userType = 2; // Switch to passenger mode
                    y.isAdmin = false;
                } else {
                    // Prompt for Passport ID
                    cout << "Please enter your Passport ID: ";
                    cin >> passportId;
                    // Display booking details
                    y.findBookingByPassportId(passportId);
                }
                break;
            case 4:
                if (!y.isAdmin) {
                    userType = 1; // Switch to admin mode
                    y.isAdmin = true;
                }
                break;
            case 0:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
