//bookticket increment decrement Action add Update Flight and Search flight
#include<iostream>
#include<fstream>
#include <iomanip>
#include <string>
#include<conio.h>
#include<stdio.h>
#include <sstream>
#include <cstdlib>  // for rand(), srand()
#include <ctime>    // for time()
#include <cstdio> //for remove() and rename()
#include <algorithm> 
#include<string.h>

using namespace std;

class temp{
	string username,password,email;
	fstream file;
	public:
		void visitorlogin();
		void visitorregistration();
		void managerlogin();
		void managermenu();
		void visitormenu();
		void forgotPassword();
		void managermodule();
		void visitormodule();
		void bookTicket();
		void viewBookings();
		void showAvailableFlights();
		//admin modules
		void bookingmanagement();
		void flightmanagement();
		void addflight();
		void viewflight();
		void searchflight();
		void updateflight();
		void deleteflight();
		void adminusermanagement();
		void adminviewuser();
		void admindeleteuser();
		void adminupdateuser();
		void adminsearchuser();
		void viewallbooking();
		void cancelbooking();
		void boardingpass();
	
		string getHiddenPassword();
	    bool isValidEmail(const string &);
	    bool isValidPassword(const string &);
	    
	    string generateBookingID();
}obj;

bool temp::isValidEmail(const string &email) {
    int at = email.find('@');
    int dot = email.find('.', at);
    return (at > 0 && dot > at + 1 && dot < email.length() - 1);
}


bool temp::isValidPassword(const string &pass) {
    if (pass.length() < 6) return false;
    bool hasDigit = false;
    for (int i = 0; i < pass.length(); i++)
        if (isdigit(pass[i])) hasDigit = true;
    return hasDigit;
}

string temp::getHiddenPassword() {
    string pass = "";
    char ch;

    cout << "\n\t\t\t\t\tEnter Password (Passowrd must have minimum 6 characters) : ";

    while (true) {
        ch = _getch();  // get character without echo

        // Stop when Enter is pressed
        if (ch == '\r') {  
            cout << endl;
            break;
        }

        // Handle Backspace
        else if (ch == '\b') {  
            if (!pass.empty()) {
                pass = pass.substr(0, pass.length() - 1);         // remove last character
                cout << "\b \b";       // move back, erase, move back again
            }
        }

        // Normal character input
        else {
            pass += ch;
            cout << '*';
        }
    }

    return pass;
}

string temp::generateBookingID() {
	system("cls");
    ifstream file("bookings.csv");
    string line, lastID = "BK1000";
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, lastID, ',');
    }
    file.close();

    int num;
    stringstream ss(lastID.substr(2));
    ss >> num;
    num = num + 1;

    stringstream newID;
    newID << "B" << num;
    return newID.str();
}

//admin menu
void temp :: managermenu(){
	int choice;
	do{
		cout << "\n\t\t\t\t\t--------------------Admin Menu--------------------";
		cout << "\n\t\t\t\t\t1.Access your Account";
		cout << "\n\t\t\t\t\t2.New User Registration";
		cout << "\n\t\t\t\t\t3.Recover Password";
		cout << "\n\t\t\t\t\t4.Logout";
		cout << "\n\t\t\t\t\tEnter your choice : ";
		cin >> choice;
		
		switch(choice){
			case 1:
				obj.managerlogin();
				break;
				
			case 2:
//				obj.managerregistration();
				break;
				
			case 3:
				obj.forgotPassword();
				break;
				
			case 4:
				cout << "\n\t\t\t\t\tLogout complete - Come back anytime";
				break;
				
			default:
				cout << "Invalid choice";	
		}
	}while(choice !=4);
}

//user menu
void temp :: visitormenu(){
	int choice;
	do{
	cout << "\n\t\t\t\t\t+-----------------------------------------------+";
	    cout << "\n\t\t\t\t\t|                  VISITOR MENU                	|";
	    cout << "\n\t\t\t\t\t|-----------------------------------------------|";
	    cout << "\n\t\t\t\t\t|  1. Access Your Account                       |";
	    cout << "\n\t\t\t\t\t|  2. New User Registration                     |";
	    cout << "\n\t\t\t\t\t|  3. Recover Password                          |";
	    cout << "\n\t\t\t\t\t|  4. Logout                                    |";
	    cout << "\n\t\t\t\t\t+-----------------------------------------------+";
		cout << "\n\t\t\t\t\tEnter Your Choice : ";
		cin >> choice;
		
		switch(choice){
			case 1:
				obj.visitorlogin();
				break;
				
			case 2:
				obj.visitorregistration();
				break;
				
			case 3:
				obj.forgotPassword();
				break;
				
			case 4:
				cout << "\n\t\t\t\t\tLogout complete - Come back anytime";
				break;
				
			default:
				cout << "Invalid choice";	
		}
	}while(choice !=4);
}

//register user
void temp :: visitorregistration(){
	system("cls");
	cout << "\t\t\t\t\tEnter your username : ";
	cin >> username;
		
	cout << "\t\t\t\t\tEnter your email address :(Use of @ and .com is complusory) ";
	cin >> email;
	
	if (!isValidEmail(email)) { cout << "Invalid email!\n"; return; }
    password = getHiddenPassword();
    if (!isValidPassword(password)) { 
		cout << "Weak password!\n"; 
		return; 
	}

	
	file.open("userloginData.txt",ios::out | ios::app);//out is used to read a file and app is used to write.
	//write data for this structure
	file << username << "," << email << "," << password << "\n"; // , is used for sperator.
	file.close();
	
	cout << "\n\t\t\t\t\tWelcome! Your registration was successful. Let’s get started.!!";
	
}

//login user
void temp :: visitorlogin(){
	system("cls");
	string searchName,searchPassword;
	cout << "\n\t\t\t\t\t+------------------------------------------------+";
	cout << "\n\t\t\t\t\t|                 LOGIN HERE!                    |";
	cout << "\n\t\t\t\t\t+------------------------------------------------+";
	cout << "\n\t\t\t\t\tEnter Your Username : ";
	cin >> searchName;
	
	searchPassword = getHiddenPassword();
	
	
	file.open("userloginData.txt",ios::in);
	getline(file,username,','); //getline:- read data until the delimeter.delimeter mSSeans ',' means separator.
	getline(file,email,',');
	getline(file,password,'\n');
	
	bool found = false;   // flag to check if login is successful

	while(getline(file, username, ',') &&
      getline(file, email, ',') &&
      getline(file, password, '\n')) {
    
    if(username == searchName && password == searchPassword) {
        cout << "\n\n\t\t\t\t\tAccess Granted..Welcome!!...\n";
        found = true; // mark success
		visitormodule();
        break;          // stop checking further records
    }
}

// after loop ends
if(!found) {
    cout << "\n\n\t\t\t\t\t Authentication Failed...Check your security information!!!\n";
}

	file.close();
}

//login Admin
void temp::managerlogin() {
	system("cls");
    string searchName, searchPassword;
    cout << "\n\t\t\t\t\t+------------------------------------------------+";
    cout << "\n\t\t\t\t\t|                 LOGIN HERE!                    |";
    cout << "\n\t\t\t\t\t+------------------------------------------------+";
    cout << "\n\t\t\t\t\tEnter Your Username : ";
    cin >> searchName;

    // Get hidden password
    searchPassword = getHiddenPassword();
    if (!isValidPassword(searchPassword)) {
        cout << "\n\t\t\t\t\tPassword must be at least 6 characters and contain a number!\n";
        return;
    }

    file.open("adminloginData.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\t\t\tError: Cannot open adminloginData.txt\n";
        return;
    }

    bool found = false;
    while (getline(file, username, ',') &&
           getline(file, email, ',') &&
           getline(file, password, '\n')) {

        if (username == searchName && password == searchPassword) {
            cout << "\n\n\t\t\t\t\tAccess Granted.. Welcome!!...\n";
            found = true;
            managermodule(); // go to next module
            break;
        }
    }

    if (!found) {
        cout << "\n\n\t\t\t\t\tAuthentication Failed... Check your credentials!\n";
    }

    file.close();
}

//manager Module
void temp :: managermodule(){
	int choice;
	do{
		cout << "\n\t\t\t\t\t+----------------------------------------------------+";
	    cout << "\n\t\t\t\t\t|                  MANAGER  MODULE                   |";
	    cout << "\n\t\t\t\t\t|----------------------------------------------------|";
	    cout << "\n\t\t\t\t\t|  1. Flight Management                              |";
	    cout << "\n\t\t\t\t\t|  2. Admin User Management                          |";
	    cout << "\n\t\t\t\t\t|  3. Booking Management                             |";
	    cout << "\n\t\t\t\t\t|  4. Boarding Pass                                  |";
	    cout << "\n\t\t\t\t\t|  5. Logout                                         |";
	    cout << "\n\t\t\t\t\t+----------------------------------------------------+";
	    cout << "\n\t\t\t\t\tEnter Your Choice : ";
	    cin >> choice;
        
        switch(choice){
        	case 1:
        		obj.flightmanagement();
        		break;
        		
        	case 2:
        		obj.adminusermanagement();
        		break;
        	
        	case 3:
        		obj.bookingmanagement();
        		break;
        		
        	case 4:
        		obj.boardingpass();
        		break;
        		
        	case 5:
                cout << "\n\t\t\t\t\tLogging out from MANAGER Module...\n";
        		break;
        		
        	default:
        		cout << "\n\t\t\t\t\tInvalid Choice. Try again!\n";
		}
	} while(choice != 5);
}

//Flight Management
void temp :: flightmanagement()
{
	int choice;
	do{
		cout << "\n\t\t\t\t\t+---------------------------------------------------+";
	    cout << "\n\t\t\t\t\t|              	FLIGHT MANAGEMENT  	            |";
	    cout << "\n\t\t\t\t\t|---------------------------------------------------|";
	    cout << "\n\t\t\t\t\t|  1. Add Flight                                    |";
	    cout << "\n\t\t\t\t\t|  2. View Flights                                  |";
	    cout << "\n\t\t\t\t\t|  3. Search Flight                                 |";
	    cout << "\n\t\t\t\t\t|  4. Update Flight                                 |";
	    cout << "\n\t\t\t\t\t|  5. Delete Flight                                 |";
	    cout << "\n\t\t\t\t\t|  6. Back to Manager Menu                          |";
	    cout << "\n\t\t\t\t\t+---------------------------------------------------+";
	    cout << "\n\t\t\t\tSelect your operation : ";
	    cin >> choice;
        
        switch(choice){
        	case 1:
        		obj.addflight();
        		break;
        	
        	case 2:
        		obj.viewflight();
        		break;
			
			case 3:
        		obj.searchflight();
        		break;
        		
        	case 4:
        		obj.updateflight();
        		break;
        		
        	case 5:
        		obj.deleteflight();
        		break;
        		
        	case 6:
        		obj.managermodule();
        		break;
        		
        	default:
        		cout << "\n\t\t\t\t\tInvalid Choice. Try again!\n";
		}
	}while(choice!=6);
	
}

//add flight
bool isValidDateRange(const string &dateStr) {
    int d, m, y;
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &d, &m, &y) != 3)
        return false;

    // Entered date
    tm entered = {};
    entered.tm_mday = d;
    entered.tm_mon  = m - 1;
    entered.tm_year = y - 1900;
    time_t enteredTime = mktime(&entered);

    // Today's date (time removed)
    time_t now = time(0);
    tm *t = localtime(&now);

    tm today = {};
    today.tm_mday = t->tm_mday;
    today.tm_mon  = t->tm_mon;
    today.tm_year = t->tm_year;

    time_t todayTime = mktime(&today);

    // 45 days from today
    time_t maxAllowed = todayTime + (45 * 24 * 60 * 60);

    if (enteredTime < todayTime) return false;    // past date ?
    if (enteredTime > maxAllowed) return false;   // more than 45 days ?

    return true;
}



void temp::addflight() {
    system("cls");
    string flightNo, airline, from, to, date, depTime, arrTime;
    int totalSeats, price;

    cout << "\n\t\t\t\t\tEnter Flight No : ";
    cin >> flightNo;

    // Check flight exists
    ifstream fin("flights.txt");
    string line;
    bool exists = false;

    if (fin) {
        while (getline(fin, line)) {
            stringstream ss(line);
            string existingFlightNo;
            getline(ss, existingFlightNo, ',');
            if (existingFlightNo == flightNo) {
                exists = true;
                break;
            }
        }
        fin.close();
    }

    if (exists) {
        cout << "\n\t\t\t\t\t Flight ID already exists! Please use a unique Flight No.\n";
        return;
    }

    // Continue details
    cout << "\n\t\t\t\t\tEnter Airline : ";
    cin >> airline;

    cout << "\n\t\t\t\t\tFrom : ";
    cin >> from;

    cout << "\n\t\t\t\t\tTo : ";
    cin >> to;

    // ---------------- DATE VALIDATION ----------------
    cout << "\n\t\t\t\t\tDate (DD-MM-YYYY): ";
    cin >> date;

    while (!isValidDateRange(date)) {
        cout << "\n\t\t\t\t Invalid Date!";
        cout << "\n\t\t\t\t Today or future date";
        cout << "\tWithin 45 days only";
        cout << "\n\t\t\t\tEnter again (DD-MM-YYYY): ";
        cin >> date;
    }
    // -------------------------------------------------

    cout << "\n\t\t\t\t\tDeparture Time : ";
    cin >> depTime;

    cout << "\n\t\t\t\t\tArrival Time : ";
    cin >> arrTime;

    cout << "\n\t\t\t\t\tTotal Seats : ";
    cin >> totalSeats;

    cout << "\n\t\t\t\t\tPrice : ";
    cin >> price;

    // Save to file
    ofstream file("flights.txt", ios::app);
    if (!file) {
        cout << "\n\t\t\t\t\t File could not be opened.";
        return;
    }

    file << flightNo << "," << airline << "," << from << "," << to << ","
         << date << "," << depTime << "," << arrTime << ","
         << totalSeats << "," << price << "\n";

    file.close();

    // Display table
    cout << "\nFlight Added Successfully!\n";
    cout << "+----------+----------+-----------+----------+------------+----------------+--------------+-------+---------+\n";
    cout << "| FlightID | Airline  | From      | To       | Date       | Departure Time | Arrival Time | Seats | Price   |\n";
    cout << "+----------+----------+-----------+----------+------------+----------------+--------------+-------+---------+\n";

    cout << "| " << left << setw(8)  << flightNo
         << " | " << setw(8)  << airline
         << " | " << setw(9)  << from
         << " | " << setw(8)  << to
         << " | " << setw(10) << date
         << " | " << setw(14) << depTime
         << " | " << setw(12) << arrTime
         << " | " << setw(5)  << totalSeats
         << " | " << setw(7)  << price
         << " |\n";

    cout << "+----------+----------+-----------+----------+------------+----------------+--------------+-------+---------+\n";
}

//View Flight
void temp::viewflight() {
    system("cls");

    ifstream file("flights.txt");
    if (!file) {
        cout << "\nFlight file not found!";
        return;
    }

    string flightNo, airline, from, to, date, depTime, arrTime, seats, price;

    cout << "\n==================== Available Flights ====================\n";
    cout << "+----------+---------------+--------------+--------------+------------+------------------+----------------+--------+--------+\n";
    cout << "| FlightID | Airline       | From         | To           | Date       | Departure Time   | Arrival Time   | Seats  | Price  |\n";
    cout << "+----------+---------------+--------------+--------------+------------+------------------+----------------+--------+--------+\n";

    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        getline(ss, flightNo, ',');
        getline(ss, airline, ',');
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, date, ',');
        getline(ss, depTime, ',');
        getline(ss, arrTime, ',');
        getline(ss, seats, ',');
        getline(ss, price, '\n');

        if (flightNo == "") continue;  // skip empty lines

        cout << "| " << left << setw(8)  << flightNo
             << " | " << setw(13) << airline
             << " | " << setw(12) << from
             << " | " << setw(12) << to
             << " | " << setw(10) << date
             << " | " << setw(16) << depTime
             << " | " << setw(14) << arrTime
             << " | " << setw(6)  << seats
             << " | " << setw(6)  << price
             << " |\n";
    }

    cout << "+----------+---------------+--------------+--------------+------------+------------------+----------------+--------+--------+\n";

    file.close();
}

// Search Flight
void temp::searchflight() {
    system("cls");
    string line;

    ifstream file("flights.txt");
    if (!file) {
        cout << "\nNo flight data found!\n";
        return;
    }

    // -------------------- DISPLAY ALL FLIGHTS --------------------
    cout << "\n====================== ALL AVAILABLE FLIGHTS ======================\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
    cout << "| FlightID | Airline      | From       | To         | Date       | Departure Time   | Arrival Time  | Seats  | Price   |\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string flightNo, airline, from, to, date, depTime, arrTime, seats, price;

        getline(ss, flightNo, ',');
        getline(ss, airline, ',');
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, date, ',');
        getline(ss, depTime, ',');
        getline(ss, arrTime, ',');
        getline(ss, seats, ',');
        getline(ss, price, '\n');

        cout << "| " << left << setw(8)  << flightNo
             << " | " << setw(12) << airline
             << " | " << setw(10) << from
             << " | " << setw(10) << to
             << " | " << setw(10) << date
             << " | " << setw(16) << depTime
             << " | " << setw(13) << arrTime
             << " | " << setw(6)  << seats
             << " | " << setw(7)  << price << " |\n";
    }

    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
    file.close();


    // ---------------------- SEARCH INPUT ----------------------
    string fromCity, toCity;

    cout << "\nEnter Departure City (From): ";
    cin >> ws;
    getline(cin, fromCity);

    cout << "Enter Destination City (To): ";
    getline(cin, toCity);

    // lowercase for matching
    transform(fromCity.begin(), fromCity.end(), fromCity.begin(), ::tolower);
    transform(toCity.begin(), toCity.end(), toCity.begin(), ::tolower);


    // ---------------------- SEARCH RESULTS ----------------------
    ifstream searchFile("flights.txt");
    if (!searchFile) {
        cout << "\nError reopening flight file!\n";
        return;
    }

    cout << "\n=============== Flights from " << fromCity << " to " << toCity << " ===============\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
    cout << "| FlightID | Airline      | From       | To         | Date       | Departure Time   | Arrival Time  | Seats  | Price   |\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";

    bool found = false;

    while (getline(searchFile, line)) {
        stringstream ss(line);
        string flightNo, airline, from, to, date, depTime, arrTime, seats, price;

        getline(ss, flightNo, ',');
        getline(ss, airline, ',');
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, date, ',');
        getline(ss, depTime, ',');
        getline(ss, arrTime, ',');
        getline(ss, seats, ',');
        getline(ss, price, '\n');

        string lf = from, lt = to;
        transform(lf.begin(), lf.end(), lf.begin(), ::tolower);
        transform(lt.begin(), lt.end(), lt.begin(), ::tolower);

        if (lf.find(fromCity) != string::npos && lt.find(toCity) != string::npos) {

            cout << "| " << left << setw(8)  << flightNo
                 << " | " << setw(12) << airline
                 << " | " << setw(10) << from
                 << " | " << setw(10) << to
                 << " | " << setw(10) << date
                 << " | " << setw(16) << depTime
                 << " | " << setw(13) << arrTime
                 << " | " << setw(6)  << seats
                 << " | " << setw(7)  << price << " |\n";

            found = true;
        }
    }

    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";

    if (!found)
        cout << "\nNo flights found for this route!\n";

    searchFile.close();
}

// Update Flight
void temp::updateflight()
{
    system("cls");

    // ---- Step 1: Read all flights into arrays ----
    ifstream fin("flights.txt");
    if (!fin) {
        cout << "\n\t\t\t\t\tFlights file not found!\n";
        return;
    }

    string fNo[500], airline[500], from[500], to[500], date[500], dep[500], arr[500], seats[500], price[500];
    int count = 0;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);

        getline(ss, fNo[count], ',');
        getline(ss, airline[count], ',');
        getline(ss, from[count], ',');
        getline(ss, to[count], ',');
        getline(ss, date[count], ',');
        getline(ss, dep[count], ',');
        getline(ss, arr[count], ',');
        getline(ss, seats[count], ',');
        getline(ss, price[count], '\n');

        count++;
    }
    fin.close();

    if (count == 0) {
        cout << "\n\t\t\t\t\tNo flights found!\n";
        return;
    }

    // ---- Step 2: Display flight table ----
    cout << "\n\t\t\t\t\t==================== Available Flights ======================\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
    cout << "| FlightID | Airline      | From       | To         | Date       | Departure Time   | Arrival Time  | Seats  | Price   |\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";

    for (int i = 0; i < count; i++) {
        cout << "| " << left << setw(8) << fNo[i]
             << " | " << setw(12) << airline[i]
             << " | " << setw(10) << from[i]
             << " | " << setw(10) << to[i]
             << " | " << setw(10) << date[i]
             << " | " << setw(16) << dep[i]
             << " | " << setw(13) << arr[i]
             << " | " << setw(6)  << seats[i]
             << " | " << setw(7)  << price[i] << " |\n";
    }

    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";

    // ---- Step 3: Ask which flight to update ----
    string id;
    cout << "\n\t\t\t\t\tEnter Flight ID to update: ";
    cin >> id;
    cin.ignore();

    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (fNo[i] == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "\n\t\t\t\t\tFlight not found!\n";
        return;
    }

    // ---- Step 4: Update menu ----
    int choice;
    string input;

    cout << "\n\t\t\t\t\tWhat do you want to update?\n";
    cout << "\t\t\t\t\t1. Airline\n";
    cout << "\t\t\t\t\t2. From\n";
    cout << "\t\t\t\t\t3. To\n";
    cout << "\t\t\t\t\t4. Date\n";
    cout << "\t\t\t\t\t5. Departure Time\n";
    cout << "\t\t\t\t\t6. Arrival Time\n";
    cout << "\t\t\t\t\t7. Seats\n";
    cout << "\t\t\t\t\t8. Price\n";
    cout << "\t\t\t\t\t9. Update All Fields\n";
    cout << "\n\t\t\t\t\tEnter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            cout << "Enter new Airline (" << airline[idx] << "): ";
            getline(cin, input); if (!input.empty()) airline[idx] = input;
            break;

        case 2:
            cout << "Enter new From (" << from[idx] << "): ";
            getline(cin, input); if (!input.empty()) from[idx] = input;
            break;

        case 3:
            cout << "Enter new To (" << to[idx] << "): ";
            getline(cin, input); if (!input.empty()) to[idx] = input;
            break;

        case 4:
            cout << "Enter new Date (" << date[idx] << "): ";
            getline(cin, input); if (!input.empty()) date[idx] = input;
            break;

        case 5:
            cout << "Enter new Departure Time (" << dep[idx] << "): ";
            getline(cin, input); if (!input.empty()) dep[idx] = input;
            break;

        case 6:
            cout << "Enter new Arrival Time (" << arr[idx] << "): ";
            getline(cin, input); if (!input.empty()) arr[idx] = input;
            break;

        case 7:
            cout << "Enter new Seats (" << seats[idx] << "): ";
            getline(cin, input); if (!input.empty()) seats[idx] = input;
            break;

        case 8:
            cout << "Enter new Price (" << price[idx] << "): ";
            getline(cin, input); if (!input.empty()) price[idx] = input;
            break;

        case 9:
            cout << "\nEnter new details (leave blank to keep old):\n";

            cout << "Airline (" << airline[idx] << "): ";
            getline(cin, input); if (!input.empty()) airline[idx] = input;

            cout << "From (" << from[idx] << "): ";
            getline(cin, input); if (!input.empty()) from[idx] = input;

            cout << "To (" << to[idx] << "): ";
            getline(cin, input); if (!input.empty()) to[idx] = input;

            cout << "Date (" << date[idx] << "): ";
            getline(cin, input); if (!input.empty()) date[idx] = input;

            cout << "Departure Time (" << dep[idx] << "): ";
            getline(cin, input); if (!input.empty()) dep[idx] = input;

            cout << "Arrival Time (" << arr[idx] << "): ";
            getline(cin, input); if (!input.empty()) arr[idx] = input;

            cout << "Seats (" << seats[idx] << "): ";
            getline(cin, input); if (!input.empty()) seats[idx] = input;

            cout << "Price (" << price[idx] << "): ";
            getline(cin, input); if (!input.empty()) price[idx] = input;
            break;

        default:
            cout << "\n\t\t\t\t\tInvalid choice!\n";
            return;
    }

    // ---- Step 5: Rewrite entire file ----
    ofstream fout("flights.txt");
    for (int i = 0; i < count; i++) {
        fout << fNo[i] << "," << airline[i] << "," << from[i] << "," << to[i] << ","
             << date[i] << "," << dep[i] << "," << arr[i] << "," << seats[i] << "," << price[i] << "\n";
    }
    fout.close();

    // ---- Step 6: Show updated record ----
    cout << "\n\t\t\t\t\t? Flight updated successfully!\n";

    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
    cout << "| FlightID | Airline      | From       | To         | Date       | Departure Time   | Arrival Time  | Seats  | Price   |\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
    cout << "| " << left << setw(8)  << fNo[idx]
         << " | " << setw(12) << airline[idx]
         << " | " << setw(10) << from[idx]
         << " | " << setw(10) << to[idx]
         << " | " << setw(10) << date[idx]
         << " | " << setw(16) << dep[idx]
         << " | " << setw(13) << arr[idx]
         << " | " << setw(6)  << seats[idx]
         << " | " << setw(7)  << price[idx] << " |\n";
    cout << "+----------+--------------+------------+------------+------------+------------------+---------------+--------+---------+\n";
}

// Delete Flight
void temp :: deleteflight() {
    system("cls");
    obj.viewflight();

    string flightNo;
    cout << "\n\n\t\tEnter Flight Number to delete: ";
    cin >> flightNo;

    ifstream fin("flights.txt");
    if (!fin) {
        cout << "\n\t\tFlights file not found!\n";
        return;
    }

    ofstream fout("temp.txt");
    bool found = false;

    string fNo, airline, from, to, date, depTime, arrTime, seatsStr, priceStr;

    while (getline(fin, fNo, ',') &&
           getline(fin, airline, ',') &&
           getline(fin, from, ',') &&
           getline(fin, to, ',') &&
           getline(fin, date, ',') &&
           getline(fin, depTime, ',') &&
           getline(fin, arrTime, ',') &&
           getline(fin, seatsStr, ',') &&
           getline(fin, priceStr, '\n'))
    {
        if (fNo == flightNo) {
            found = true;

            cout << "\n\t\tFlight Deleted Successfully!\n\n";

            // -------------------- PROPER TABLE FORMAT --------------------
            cout << "+----------+---------------+--------------+--------------+------------+------------------+----------------+--------+--------+\n";
            cout << "| FlightID | Airline       | From         | To           | Date       | Departure Time   | Arrival Time   | Seats  | Price  |\n";
            cout << "+----------+---------------+--------------+--------------+------------+------------------+----------------+--------+--------+\n";

            cout << "| " << left << setw(8)  << fNo
                 << " | " << setw(13) << airline
                 << " | " << setw(12) << from
                 << " | " << setw(12) << to
                 << " | " << setw(10) << date
                 << " | " << setw(16) << depTime
                 << " | " << setw(14) << arrTime
                 << " | " << setw(6)  << seatsStr
                 << " | " << setw(6)  << priceStr
                 << " |\n";

            cout << "+----------+---------------+--------------+--------------+------------+------------------+----------------+--------+--------+\n";
            // --------------------------------------------------------------

            continue; // Skip writing — meaning delete this flight
        }

        // Write all other records unchanged
        fout << fNo << "," << airline << "," << from << "," << to << "," << date << ","
             << depTime << "," << arrTime << "," << seatsStr << "," << priceStr << "\n";
    }

    fin.close();
    fout.close();

    remove("flights.txt");
    rename("temp.txt", "flights.txt");

    if (!found) {
        cout << "\n\t\tFlight not found!\n";
    }
}

//Admin User Management
void temp :: adminusermanagement()
{
	int choice;
	do{
		cout << "\n\t\t\t\t\t+-----------------------------------------------------+";
	    cout << "\n\t\t\t\t\t|              Admin USER MANAGEMENT  	               |";
	    cout << "\n\t\t\t\t\t|-----------------------------------------------------|";
	    cout << "\n\t\t\t\t\t|  1. View All Users                                  |";
	    cout << "\n\t\t\t\t\t|  2. Delete users                                    |";
	    cout << "\n\t\t\t\t\t|  3. Update user details                             |";
	    cout << "\n\t\t\t\t\t|  4. Search for a user                               |";
	    cout << "\n\t\t\t\t\t|  5. Back to Manager Module                          |";
	    cout << "\n\t\t\t\t\t+----------------------------------------------------+";
	    cout << "\n\t\t\t\tSelect your operation : ";
	    cin >> choice;
	    
	    switch(choice){
        	case 1:
        		obj.adminviewuser();
        		break;
        	
			case 2:
        		obj.admindeleteuser();
        		break;
        		
        	case 3:
        		obj.adminupdateuser();
        		break;
        		
        	case 4:
        		obj.adminsearchuser();
        		break;
        		
        	case 5:
        		obj.managermodule();
        		break;
        		
        	default:
        		cout << "\n\t\t\t\t\tInvalid Choice. Try again!\n";
		}
	}while(choice!=5);
	
}

//Admin View ALl User
void temp::adminviewuser() {
	system("cls");
    ifstream fin("userloginData.txt"); // Read file
    if (!fin) {
        cout << "\n\t\t\t\t\tUser Not Found...";
        return;
    }

    string uname, mail, pass;

    cout << "\n\t\t\t\t\t==================== Registered Users ====================\n";
    cout << "+---------------+-------------------------+---------------+\n";
    cout << "| Username      | Email                   | Password      |\n";
    cout << "+---------------+-------------------------+---------------+\n";

    while (getline(fin, uname, ',') &&
           getline(fin, mail, ',') &&
           getline(fin, pass, '\n')) {

        // ?? Replace password with * symbols
        string hiddenPass(pass.length(), '*');

        cout << "| " << left << setw(13) << uname
             << " | " << setw(23) << mail
             << " | " << setw(13) << hiddenPass << " |\n";
    }

    cout << "+---------------+-------------------------+---------------+\n";

    fin.close();
}
//admin delete user
void temp :: admindeleteuser() {
	system("cls");
	obj.adminviewuser();
    string unameToDelete;
    cout << "\n\t\t\t\t\tEnter Username to delete: ";
    cin >> unameToDelete;

    ifstream fin("userloginData.txt");
    if (!fin) {
        cout << "\n\t\t\t\t\tUser file not found!\n";
        return;
    }

    ofstream fout("temp.txt");
    bool found = false;

    string uname, mail, pass;

    while (getline(fin, uname, ',') &&
           getline(fin, mail, ',') &&
           getline(fin, pass, '\n')) 
    {
        if (uname == unameToDelete) {
            found = true;
            cout << "\n\t\t\t\t\tUser Deleted Successfully!\n";

            // Show deleted user in table format
            cout << "+---------------+-------------------------+---------------+\n";
            cout << "| Username      | Email                   | Password      |\n";
            cout << "+---------------+-------------------------+---------------+\n";
            cout << "| " << left << setw(13) << uname
                 << " | " << setw(23) << mail
                 << " | " << setw(13) << pass << " |\n";
            cout << "+---------------+-------------------------+---------------+\n";

            continue; // skip writing this record ? deletes it
        }
        // copy remaining users
        fout << uname << "," << mail << "," << pass << "\n";
    }

    fin.close();
    fout.close();

    remove("userloginData.txt");
    rename("temp.txt", "userloginData.txt");

    if (!found) {
        cout << "\n\t\t\t\t\tUser not found!\n";
    }
}

//Admin Update User Details
void temp::adminupdateuser() {
    system("cls");

    // ---- Step 1: Read all users ----
    ifstream fin("userloginData.txt");
    if (!fin) {
        cout << "\n\t\t\t\t\tUser file not found!\n";
        return;
    }

    string uname[500], mail[500], pass[500];
    int count = 0;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        getline(ss, uname[count], ',');
        getline(ss, mail[count], ',');
        getline(ss, pass[count], '\n');
        count++;
    }
    fin.close();

    if (count == 0) {
        cout << "\n\t\t\t\t\tNo users found!\n";
        return;
    }

    // ---- Step 2: Display all users in table ----
    cout << "\n\t\t\t\t\t==================== Registered Users ==========================\n";
    cout << "+---------------+------------------------------+---------------+\n";
    cout << "| Username      | Email                        | Password      |\n";
    cout << "+---------------+------------------------------+---------------+\n";

    for (int i = 0; i < count; i++) {
        cout << "| " << left << setw(13) << uname[i]
             << " | " << setw(28) << mail[i]
             << " | " << setw(13) << pass[i] << " |\n";
    }
    cout << "+---------------+------------------------------+---------------+\n";

    // ---- Step 3: Choose username to update ----
    string userToUpdate;
    cout << "\n\t\t\t\t\tEnter Username to update: ";
    cin >> userToUpdate;

    int idx = -1;
    for (int i = 0; i < count; i++) {
        if (uname[i] == userToUpdate) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << "\n\t\t\t\t\tUser not found!\n";
        return;
    }

    // ---- Step 4: Update menu ----
    cout << "\n\t\t\t\t\tWhat do you want to update?\n";
    cout << "\t\t\t\t\t1. Username\n";
    cout << "\t\t\t\t\t2. Email\n";
    cout << "\t\t\t\t\t3. Password\n";
    cout << "\t\t\t\t\t4. Update All Fields\n";
    cout << "\n\t\t\t\t\tEnter your choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    string input;

    switch (choice) {
        case 1:
            cout << "Enter new Username (" << uname[idx] << "): ";
            getline(cin, input);
            if (!input.empty()) uname[idx] = input;
            break;

        case 2:
            cout << "Enter new Email (" << mail[idx] << "): ";
            getline(cin, input);
            if (!input.empty()) mail[idx] = input;
            break;

        case 3:
            cout << "Enter new Password (" << pass[idx] << "): ";
            getline(cin, input);
            if (!input.empty()) pass[idx] = input;
            break;

        case 4:
            cout << "\nEnter new details (leave blank to keep old):\n";
            cout << "Username (" << uname[idx] << "): ";
            getline(cin, input); if (!input.empty()) uname[idx] = input;
            cout << "Email (" << mail[idx] << "): ";
            getline(cin, input); if (!input.empty()) mail[idx] = input;
            cout << "Password (" << pass[idx] << "): ";
            getline(cin, input); if (!input.empty()) pass[idx] = input;
            break;

        default:
            cout << "\n\t\t\t\t\tInvalid choice!\n";
            return;
    }

    // ---- Step 5: Rewrite all users back to file ----
    ofstream fout("userloginData.txt");
    for (int i = 0; i < count; i++) {
        fout << uname[i] << "," << mail[i] << "," << pass[i] << "\n";
    }
    fout.close();

    // ---- Step 6: Show updated table ----
    cout << "\n\t\t\t\t\t? User updated successfully!\n";

    cout << "+---------------+------------------------------+---------------+\n";
    cout << "| Username      | Email                        | Password      |\n";
    cout << "+---------------+------------------------------+---------------+\n";
    cout << "| " << left << setw(13) << uname[idx]
         << " | " << setw(28) << mail[idx]
         << " | " << setw(13) << pass[idx] << " |\n";
    cout << "+---------------+------------------------------+---------------+\n";
}


// Admin Search User
void temp::adminsearchuser() {
	system("cls");
    ifstream fin("userloginData.txt");
    if (!fin) {
        cout << "\n\t\t\t\t\tUser file not found!\n";
        return;
    }

    string uname, mail, pass;
    bool hasData = false;

    // --- Step 1: Display all users ---
    cout << "\n\t\t\t\t\t==================== All Registered Users ====================\n";
    cout << "+---------------+-------------------------+---------------+\n";
    cout << "| Username      | Email                   | Password      |\n";
    cout << "+---------------+-------------------------+---------------+\n";

    while (getline(fin, uname, ',') &&
           getline(fin, mail, ',') &&
           getline(fin, pass, '\n')) {
        hasData = true;
        cout << "| " << left << setw(13) << uname
             << " | " << setw(23) << mail
             << " | " << setw(13) << pass << " |\n";
    }

    if (!hasData) {
        cout << "|              No user data available in the file.                |\n";
        cout << "+---------------+-------------------------+---------------+\n";
        fin.close();
        return;
    }

    cout << "+---------------+-------------------------+---------------+\n";
    fin.close();

    // --- Step 2: Ask for search input ---
    string searchUser;
    cout << "\n\t\t\t\t\tEnter Username or Email to search: ";
    cin >> searchUser;

    // Reopen file to search
    fin.open("userloginData.txt");
    bool found = false;

    cout << "\n\t\t\t\t\t==================== Search Result ====================\n";
    cout << "+---------------+-------------------------+---------------+\n";
    cout << "| Username      | Email                   | Password      |\n";
    cout << "+---------------+-------------------------+---------------+\n";

    while (getline(fin, uname, ',') &&
           getline(fin, mail, ',') &&
           getline(fin, pass, '\n')) {
        if (uname == searchUser || mail == searchUser) {
            cout << "| " << left << setw(13) << uname
                 << " | " << setw(23) << mail
                 << " | " << setw(13) << pass << " |\n";
            found = true;
        }
    }

    if (!found)
        cout << "|                   No user found matching input                     |\n";

    cout << "+---------------+-------------------------+---------------+\n";

    fin.close();
}

//admin booking management
void temp :: bookingmanagement()
{
	int choice;
	do{
		cout << "\n\t\t\t\t\t+---------------------------------------------------+";
	    cout << "\n\t\t\t\t\t|              	Booking MANAGEMENT  	         |";
	    cout << "\n\t\t\t\t\t|---------------------------------------------------|";
	    cout << "\n\t\t\t\t\t|  1. View All Booking                              |";
	    cout << "\n\t\t\t\t\t|  2. Cancel Booking                                |";
	    cout << "\n\t\t\t\t\t|  3. Back to Manager Menu                          |";
	    cout << "\n\t\t\t\t\t+---------------------------------------------------+";
	    cout << "\n\t\t\t\tSelect your operation : ";
	    cin >> choice;
        
        switch(choice){
        	case 1:
        		obj.viewallbooking();
        		break;
        	
        	case 2:
        		obj.cancelbooking();
        		break;
			
			case 3:
        		obj.managermodule();
        		break;
        		
        	default:
        		cout << "\n\t\t\t\t\tInvalid Choice. Try again!\n";
		}
	}while(choice!=3);
	
}

//view all booking
void temp::viewallbooking() {
    system("cls");

    ifstream inFile("bookings.txt");
    if (!inFile) {
        cout << "\n\t\t\t\t\tNo bookings found!\n";
        return;
    }

    cout << "\n\t\t\t\t\t==================== All Bookings ====================\n";

    cout << "+-------------+------------------+-----------+-----------+------+--------+-------------+------------+-----------+-----------+\n";
    cout << "| BookingID   | Passenger Name   | Flight No | Airline   | Age  | Gender | From        | To         | Date      | Price     |\n";
    cout << "+-------------+------------------+-----------+-----------+------+--------+-------------+------------+-----------+-----------+\n";

    string bookingID, passengerName, age, gender, airline, from, to, flightNo, date, price;

    while (
        getline(inFile, bookingID, ',') &&
        getline(inFile, passengerName, ',') &&
        getline(inFile, flightNo, ',') &&
        getline(inFile, airline, ',') &&
        getline(inFile, age, ',') &&
        getline(inFile, gender, ',') &&
        getline(inFile, from, ',') &&
        getline(inFile, to, ',') &&
        getline(inFile, date, ',') &&
        getline(inFile, price, '\n')
    ) {
        if (bookingID.empty()) continue;

        cout << "| " << setw(11) << left << bookingID
             << " | " << setw(16) << passengerName
             << " | " << setw(9)  << flightNo
             << " | " << setw(9)  << airline
             << " | " << setw(4)  << age
             << " | " << setw(6)  << gender
             << " | " << setw(11) << from
             << " | " << setw(10) << to
             << " | " << setw(9)  << date
             << " | " << setw(9)  << price << " |\n";
    }

    cout << "+-------------+------------------+-----------+-----------+------+--------+-------------+------------+-----------+-----------+\n";

    inFile.close();
}



//Boarding Pass (invoice ticket)
void temp::boardingpass() {
    system("cls");

    // ================== STEP 1: SHOW ALL BOOKINGS ==================
    ifstream fin("bookings.txt");
    if (!fin) {
        cout << "\n\t\t\t\tBooking file not found!\n";
        return;
    }

    cout << "\n========================= ALL BOOKINGS =========================\n";
    cout << "+-------------+------------------+-----------+-----------+------+--------+-------------+------------+-----------+-----------+\n";
    cout << "| BookingID   | Passenger Name   | Flight No | Airline   | Age  | Gender | From        | To         | Date      | Price     |\n";
    cout << "+-------------+------------------+-----------+-----------+------+--------+-------------+------------+-----------+-----------+\n";

    string bID, passengerName, age, gender, airline, from, to, flightNo, date, priceStr;

    while (getline(fin, bID, ',') &&
        getline(fin, passengerName, ',') &&
        getline(fin, flightNo, ',') &&
        getline(fin, airline, ',') &&
        getline(fin, age, ',') &&
        getline(fin, gender, ',') &&
        getline(fin, from, ',') &&
        getline(fin, to, ',') &&
        getline(fin, date, ',') &&
           getline(fin, priceStr, '\n'))
    {
        cout << "| " << left << setw(11) << bID
              << " | " << setw(16) << passengerName
             << " | " << setw(9)  << flightNo
             << " | " << setw(9)  << airline
             << " | " << setw(4)  << age
             << " | " << setw(6)  << gender
             << " | " << setw(11) << from
             << " | " << setw(10) << to
             << " | " << setw(9)  << date
             << " | " << setw(9)  << priceStr << " |\n";
    }

    cout << "+-------------+------------------+-----------+-----------+------+--------+-------------+------------+-----------+-----------+\n";
    fin.close();

    // ================== STEP 2: ASK USER FOR BOOKING ID ==================
    string bookingID;
    cout << "\nEnter Booking ID to generate Boarding Pass: ";
    cin >> bookingID;

    fin.open("bookings.txt");
    if (!fin) {
        cout << "\n\t\t\t\tBooking file not found!\n";
        return;
    }

    bool found = false;

    // ================== STEP 3: SEARCH BOOKING AND PRINT BOARDING PASS ==================
    while (getline(fin, bID, ',') &&
            getline(fin, passengerName, ',') &&
	        getline(fin, flightNo, ',') &&
	        getline(fin, airline, ',') &&
	        getline(fin, age, ',') &&
	        getline(fin, gender, ',') &&
	        getline(fin, from, ',') &&
	        getline(fin, to, ',') &&
	        getline(fin, date, ',') &&
            getline(fin, priceStr, '\n'))
    {
        if (bID == bookingID) {
            found = true;

            cout << "\n======================= BOARDING PASS =======================\n";
            cout << "+----------------+-------------------------------------------+\n";
            cout << "| Passenger Name | " << left << setw(41) << passengerName << "|\n";
            cout << "| Flight No      | " << setw(41) << flightNo << "|\n";
            cout << "| Airline        | " << setw(41) << airline << "|\n";
            cout << "| Age            | " << setw(41) << age << "|\n";
            cout << "| Gender         | " << setw(41) << gender << "|\n";
            cout << "| From           | " << setw(41) << from << "|\n";
            cout << "| To             | " << setw(41) << to << "|\n";
            cout << "| Travel Date    | " << setw(41) << date << "|\n";
            cout << "| Price          | " << setw(41) << priceStr << "|\n";
            cout << "+----------------+-------------------------------------------+\n";
            cout << "==================== HAVE A SAFE FLIGHT! ====================\n";

            break;
        }
    }

    if (!found) {
        cout << "\n\t\t\t\tBooking ID not found!\n";
    }

    fin.close();
}

	    	
//visitor module
void temp :: visitormodule() {
    int choice;
    do {
        cout << "\n\t\t\t\t\t+----------------------------------------------------+";
	    cout << "\n\t\t\t\t\t|                  VISITOR  MODULE                   |";
	    cout << "\n\t\t\t\t\t|----------------------------------------------------|";
	    cout << "\n\t\t\t\t\t|  1. View Available Flights                         |";
	    cout << "\n\t\t\t\t\t|  2. Book a Ticket                                  |";
	    cout << "\n\t\t\t\t\t|  3. Cancel Booking                                 |";
	    cout << "\n\t\t\t\t\t|  4. View My Bookings                               |";
	    cout << "\n\t\t\t\t\t|  5. Logout                                         |";
	    cout << "\n\t\t\t\t\t+----------------------------------------------------+";
	    cout << "\n\t\t\t\t\tEnter Your Choice : ";
	    cin >> choice;

        switch(choice) {
            case 1:
                cout << "\n\t\t\t\t\tShowing Available Flights...\n";
                obj.showAvailableFlights();
                break;

            case 2:
                cout << "\n\t\t\t\t\tBooking a Ticket...\n";
               obj.bookTicket();
                break;

            case 3:
                cout << "\n\t\t\t\t\tCancelling Your Booking...\n";
                obj.cancelbooking();
                break;

            case 4:
                cout << "\n\t\t\t\t\tYour Bookings...\n";
                obj.viewBookings();
                break;

            case 5:
                cout << "\n\t\t\t\t\tLogging out from Visitor Module...\n";
                break;

            default:
                cout << "\n\t\t\t\t\tInvalid choice, please try again.";
        }
    } while(choice != 5);
}

// show available flights
void temp :: showAvailableFlights() {
	system("cls");
    ifstream file("flights.txt");
    if (!file) {
        cout << "Error: Flights data file not found!\n";
        return;
    }

    string line;

    // Print table header
    cout << "+------------+---------------+------------+------------+------------+---------------+---------------+-------+-------+\n";
    cout << "| FlightID   | Airline       | From       | To         | Date       | Departure Time| Arrival Time  | Seats | Price |\n";
    cout << "+------------+---------------+------------+------------+------------+---------------+---------------+-------+-------+\n";

    // Skip CSV header
    getline(file, line);

    // Read and print each flight
    while (getline(file, line)) {
        stringstream ss(line);
        string flightID, airline, from, to, date, depTime, arrTime, seats, price;

        getline(ss, flightID, ',');
        getline(ss, airline, ',');
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, date, ',');
        getline(ss, depTime, ',');
        getline(ss, arrTime, ',');
        getline(ss, seats, ',');
        getline(ss, price, '\n');

        cout << "| " << left << setw(10) << flightID
             << " | " << setw(13) << airline
             << " | " << setw(10) << from
             << " | " << setw(10) << to
             << " | " << setw(10) << date
             << " | " << setw(13) << depTime
             << " | " << setw(13) << arrTime
             << " | " << setw(5) << seats
             << " | " << setw(6) << price
             << " |\n";
    }

    // Bottom border
    cout << "+------------+---------------+------------+------------+------------+---------------+---------------+-------+-------+\n";

    file.close();
}

//book ticket
void temp::bookTicket() {
    system("cls");
    cout << "\n=== Book Flight Tickets ===\n";

    // Show flights
    ifstream flightFile("flights.txt");
    if (!flightFile) {
        cout << "No flights found! Ask admin to add flights.\n";
        return;
    }

    string line;
    while (getline(flightFile, line)) {
        cout << line << endl;
    }
    flightFile.close();

    // Select flight
    string selectedFlightNo;
    cout << "\nEnter Flight No to book: ";
    cin >> selectedFlightNo;

    flightFile.open("flights.txt");
    bool found = false;
    string data;

    while (getline(flightFile, line)) {
        stringstream ss(line);
        string fno;
        getline(ss, fno, ',');
        if (fno == selectedFlightNo) {
            data = line;
            found = true;
            break;
        }
    }
    flightFile.close();

    if (!found) {
        cout << "\nInvalid Flight No!\n";
        return;
    }

    // Parse flight
    string flightNo, airline, from, to, date, dep, arr, seatsStr, priceStr;
    stringstream fs(data);

    getline(fs, flightNo, ',');
    getline(fs, airline, ',');
    getline(fs, from, ',');
    getline(fs, to, ',');
    getline(fs, date, ',');
    getline(fs, dep, ',');
    getline(fs, arr, ',');
    getline(fs, seatsStr, ',');
    getline(fs, priceStr, '\n');

    double price = atof(priceStr.c_str());

    // How many tickets
    int numTickets;
    cout << "\nHow many tickets to book? ";
    cin >> numTickets;

    cin.ignore();

    ofstream fout("bookings.txt", ios::app);
    srand(time(0));

    double grandTotal = 0;

    for (int i = 1; i <= numTickets; i++) {

        string name, age, gender, travelDate;

        cout << "\nPassenger " << i << " Name: ";
        getline(cin, name);

        cout << "Age: ";
        getline(cin, age);

        cout << "Gender (M/F): ";
        getline(cin, gender);

        cout << "Travel Date (DD/MM/YYYY): ";
        getline(cin, travelDate);

        // Booking ID
        stringstream b;
        b << "B" << (rand() % 9000 + 1000);
        string bookingID = b.str();

        double passengerCost = price;
        grandTotal += passengerCost;  // ? Used ONLY for final print

        // ? SAVE ONLY INDIVIDUAL COST (NOT cumulative)
        fout << bookingID << ","
             << name << ","
             << flightNo << ","
             << airline << ","
             << age << ","
             << gender << ","
             << from << ","
             << to << ","
             << travelDate << ","
             << fixed << setprecision(2) << passengerCost << ","  // ? EXACT PRICE ONLY
             << fixed << setprecision(2) << passengerCost          // ? NOT cumulative
             << "\n";

        cout << "\nTicket Booked!";
        cout << "\nBooking ID: " << bookingID;
        cout << "\nFare: " << passengerCost << "\n";
    }

    fout.close();

    cout << "\n--------------------------------------";
    cout << "\nTOTAL COST for " << numTickets << " ticket(s): Rs. " << grandTotal;
    cout << "\n--------------------------------------\n";
}

// Cancel Booking
void temp::cancelbooking() {
    system("cls");

    ifstream inFile("bookings.txt");
    if (!inFile) {
        cout << "\n\t\t\t\t\tNo bookings found!\n";
        return;
    }

    string lines[500];   // store up to 500 bookings
    int count = 0;
    string line;

    // ---- Read all bookings ----
    while (getline(inFile, line)) {
        if (line.empty()) continue;   // skip blank lines
        lines[count++] = line;
    }
    inFile.close();

    if (count == 0) {
        cout << "\n\t\t\t\t\tNo bookings found!\n";
        return;
    }

    // ---- Display bookings ----
    cout << "\n\t\t\t\t=========== Select Booking to Cancel ===========\n";
    for (int i = 0; i < count; i++) {
        cout << " " << i + 1 << ". " << lines[i] << endl;
    }

    int choice;
    cout << "\nEnter booking number to cancel: ";
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > count) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid choice!\n";
        return;
    }

    // ---- Confirm cancellation ----
    char confirm;
    cout << "Are you sure? (y/n): ";
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\nCancellation aborted.\n";
        return;
    }

    // ---- Rewrite file without cancelled record ----
    ofstream outFile("temp.txt");
    for (int i = 0; i < count; i++) {
        if (i != choice - 1) {
            outFile << lines[i] << "\n";
        }
    }
    outFile.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    cout << "\n\t\t\t\t\tBooking cancelled successfully!\n";
}


//view booking
void temp::viewBookings() {
    system("cls");

    ifstream file("bookings.txt");
    if (!file) {
        cout << "\n\t\t\t\t\tNo bookings found!\n";
        return;
    }

    cout << "\n=====================================================================================================================\n";
    cout << "                                                   VIEW ALL BOOKINGS\n";
    cout << "=====================================================================================================================\n";

    cout << left
         << setw(12) << "BookingID"
         << setw(22) << "Passenger Name"
         << setw(12) << "Flight No"
         << setw(15) << "Airline"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(12) << "From"
         << setw(12) << "To"
         << setw(14) << "Travel Date"
         << setw(10) << "Price"
         << setw(10) << "Total"
         << "\n";

    cout << "---------------------------------------------------------------------------------------------------------------------\n";

    string line;
    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);

        string bookingID, passengerName, flightNo, airline;
        string age, gender, from, to, travelDate, price, totalCost;

        getline(ss, bookingID, ',');
        getline(ss, passengerName, ',');
        getline(ss, flightNo, ',');
        getline(ss, airline, ',');
        getline(ss, age, ',');
        getline(ss, gender, ',');
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, travelDate, ',');
        getline(ss, price, ',');
        getline(ss, totalCost, '\n');

        cout << left
             << setw(12) << bookingID
             << setw(22) << passengerName
             << setw(12) << flightNo
             << setw(15) << airline
             << setw(6)  << age
             << setw(8)  << gender
             << setw(12) << from
             << setw(12) << to
             << setw(14) << travelDate
             << setw(10) << price
             << setw(10) << totalCost
             << "\n";
    }

    cout << "=====================================================================================================================\n";

    file.close();
}


//forgot Password
void temp::forgotPassword() {
    system("cls");
    cout << "\n\t\t\t\t\t+------------------------------------------------+";
    cout << "\n\t\t\t\t\t|                 FORGOT PASSWORD!               |";
    cout << "\n\t\t\t\t\t+------------------------------------------------+";
    cout << "\n\t\t\t\t\tEnter your registered Username or Email: ";
    string search;
    cin >> search;

    ifstream file("userloginData.txt");
    ofstream tempFile("temp.txt");

    if (!file) {
        cout << "\t\t\t\t\tError: User data file not found!\n";
        return;
    }

    bool found = false;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string fileUsername, fileEmail, filePassword;
        getline(ss, fileUsername, ',');
        getline(ss, fileEmail, ',');
        getline(ss, filePassword, ',');

        if (fileUsername == search || fileEmail == search) {
            found = true;
            cout << "\n\t\t\t\t\tAccount found!";
            
            // Call getHiddenPassword() directly
            string newPassword = getHiddenPassword();

            tempFile << fileUsername << "," << fileEmail << "," << newPassword << "\n";
            cout << "\n\t\t\t\t\tPassword changed successfully!\n";
        } else {
            tempFile << line << "\n";
        }
    }

    file.close();
    tempFile.close();

    remove("userloginData.txt");
    rename("temp.txt", "userloginData.txt");

    if (!found)
        cout << "\t\t\t\t\tNo account found with that Username/Email.\n";
}

//main menu
int main(){
	temp obj;
	int mainchoice;
	do{
		cout << "\n\t\t\t\t\t=================================================";
		cout << "\n\t\t\t\t\t|                 MAIN MENU                     |";
		cout << "\n\t\t\t\t\t=================================================";
		cout << "\n\t\t\t\t\t|  1. Manager                                   |";
		cout << "\n\t\t\t\t\t|  2. Visitor                                   |";
		cout << "\n\t\t\t\t\t|  3. Exit                                      |";
		cout << "\n\t\t\t\t\t=================================================";
		cout << "\n\t\t\t\t\tSelect Your Role to Board the System : ";
		cin >> mainchoice;
		
		switch(mainchoice){
			case 1:
				obj.managerlogin();
				
				break;
				
			case 2:
				obj.visitormenu();
				break;
				
			case 3:
				cout << "\t\t\t\t\tExciting Goodbye!! Visit again!!";
				break;
				
			default:
				cout << "Invalid Choice...!";
				break;
		}
		
	}while(mainchoice!=3);
	
	return 0;
}
