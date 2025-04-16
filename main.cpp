#include <iostream>
#include <mysql.h>
#include <cstring>
#include <ctime>
using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "Ramya@2128";
int search() {
	system("cls");
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    if (!conn || !mysql_real_connect(conn, HOST, USER, PASS, "clinic", 3306, NULL, 0)) {
        cout << "Connection Failed!" << endl;
        return 1;
    }

    int opt;
    cout << "\nSearch by:\n1. ID\n2. Name\nChoice: ";
    cin >> opt;
    cin.ignore();

    char query[500];
    if (opt == 1) {
        int id;
        cout << "Enter Patient ID: ";
        cin >> id;
        sprintf(query, "SELECT * FROM patient_details WHERE id = %d", id);
    } else {
        char name[100];
        cout << "Enter Patient Name: ";
        cin.getline(name, 100);
        sprintf(query, "SELECT * FROM patient_details WHERE name LIKE '%%%s%%'", name);
    }

    if (mysql_query(conn, query)) {
        cout << "Search failed: " << mysql_error(conn) << endl;
        return 1;
    }

    res = mysql_store_result(conn);
    cout << "\n+----+----------------+-----+--------+--------+-------------+----------------+------------+---------------+\n";
	cout << "| ID | Name           | Age | Height | Weight | Last Visit  | Blood Pressure | Heart Rate | Address       |\n";
	cout << "+----+----------------+-----+--------+--------+-------------+----------------+------------+---------------+\n";
    while ((row = mysql_fetch_row(res))) {
        printf("| %-2s | %-14s | %-3s | %-6s | %-6s | %-11s | %-14s | %-10s | %-13s |\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8]);
        cout << "+----+----------------+-----+--------+--------+-------------+----------------+------------+---------------+\n";
    }

    mysql_free_result(res);
    mysql_close(conn);

    int choice;
    cout << "Enter 0 to return: ";
    cin >> choice;
    return 0;
}
int viewTodayAppointments() {
	system("cls");
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    if (!conn || !mysql_real_connect(conn, HOST, USER, PASS, "clinic", 3306, NULL, 0)) {
        cout << "Connection Failed!" << endl;
        return 1;
    }

    time_t t = time(0);
    struct tm* now = localtime(&t);
    char today[20];
    strftime(today, 20, "%Y-%m-%d", now);

    char query[500];
    sprintf(query, "SELECT * FROM appointments WHERE date = '%s'", today);

    if (mysql_query(conn, query)) {
        cout << "Query failed: " << mysql_error(conn) << endl;
        return 1;
    }

    res = mysql_store_result(conn);
    cout << "\nToday's Appointments:\n";
    cout << "+----+----------------+------------+----------+\n";
    cout << "| ID | Name           | Date       | Time     |\n";
    cout << "+----+----------------+------------+----------+\n";

    while ((row = mysql_fetch_row(res))) {
        printf("| %-2s | %-14s | %-10s | %-8s |\n", row[0], row[1], row[2], row[3]);
        cout << "+----+----------------+------------+----------+\n";
    }

    mysql_free_result(res);
    mysql_close(conn);
    int choice;
    cout << "Enter 0 to return: ";
    cin >> choice;
    return 0;
}
int bookAppointment() {
	system("cls");
    MYSQL* conn;
    conn = mysql_init(0);
    if (!conn || !mysql_real_connect(conn, HOST, USER, PASS, "clinic", 3306, NULL, 0)) {
        cout << "Connection Failed!" << endl;
        return 1;
    }

    int id;
    char name[100], date[20], time[10];
    cout << "Enter Patient ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(name, 100);
    cout << "Enter Appointment Date (YYYY-MM-DD): ";
    cin.getline(date, 20);
    cout << "Enter Time (HH:MM): ";
    cin.getline(time, 10);

    char query[500];
    sprintf(query, "INSERT INTO appointments (id, name, date, time) VALUES (%d, '%s', '%s', '%s')", id, name, date, time);

    if (mysql_query(conn, query)) {
        cout << "Insert failed: " << mysql_error(conn) << endl;
    } else {
        cout << "Appointment booked successfully!" << endl;
    }

    mysql_close(conn);
    int choice;
    cout << "Enter 0 to return: ";
    cin >> choice;
    return 0;
}

void centerText(string text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (columns - text.length()) / 2;
    for (int i = 0; i < padding; ++i) cout << " ";
    cout << text << endl;
}

void printLine() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding =columns;
    for(int i=0;i<padding;i++){
        cout<<"-";
    }
    cout<<endl;
}

int print(){
	printLine();
    centerText("RAMYA'S PhysioCare");
    printLine();
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int choice;
	do{
	system("cls");
	printLine();
    centerText("RAMYA'S PhysioCare");
    printLine();
    // Initialize connection
    conn = mysql_init(0);
    if (!conn) {
        cout << "MySQL initialization failed!" << endl;
        return 1;
    }

    // Connect to database
    if (!mysql_real_connect(conn, HOST, USER, PASS, "clinic", 3306, NULL, 0)) {
        cout << "Connection Failed: " << mysql_error(conn) << endl;
        return 1;
    }
    cout<<"\nRamya PhysioCare\n\n";
    cout << "Patient Record" << endl;
    // SQL SELECT Query
    const char* query = "SELECT * FROM patient_details";

    // Execute Query
    if (mysql_query(conn, query)) {
        cout << "Query Execution Failed: " << mysql_error(conn) << endl;
        return 1;
    }

    res = mysql_store_result(conn);
//    int num_fields = mysql_num_fields(res);

    cout << "\n+----+----------------+-----+--------+--------+-------------+----------------+------------+---------------+\n";
	cout << "| ID | Name           | Age | Height | Weight | Last Visit  | Blood Pressure | Heart Rate | Address       |\n";
	cout << "+----+----------------+-----+--------+--------+-------------+----------------+------------+---------------+\n";

	while ((row = mysql_fetch_row(res))) {
    	printf("| %-2s | %-14s | %-3s | %-6s | %-6s | %-11s | %-14s | %-10s | %-13s |\n",row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8]);
    	cout << "+----+----------------+-----+--------+--------+-------------+----------------+------------+---------------+\n";
	}
	cout<<"Enter \"0\" to exit :";
	cin>>choice;
    }while(choice!=0);
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
int update(){
	 MYSQL* obj;
    int ID, age, heartRate;
    float height, weight;
    char Name[100], lastVisit[20], bloodPressure[10], Address[200];

    obj = mysql_init(0);

    if (!obj) {
        cout << "MySQL initialization failed!" << endl;
        return 1;
    }

    if (!mysql_real_connect(obj, HOST, USER, PASS, "clinic", 3306, NULL, 0)) {
        cout << "Connection Failed!" << endl;
        cout << mysql_error(obj) << endl;
        return 1;
    }

//    cout << "Logged into MySQL successfully!" << endl;

    char choice;
    do {
        cout << "\nEnter Patient Details:\n";

        cout << "Patient ID: ";
        cin >> ID;
        cin.ignore(100, '\n');

        cout << "Name: ";
        cin.getline(Name, 100, '\n');

        cout << "Age: ";
        cin >> age;
        cin.ignore(100, '\n');

        cout << "Height (in cm): ";
        cin >> height;
        cin.ignore(100, '\n');

        cout << "Weight (in kg): ";
        cin >> weight;
        cin.ignore(100, '\n');

        cout << "Last Visit (YYYY-MM-DD): ";
        cin.getline(lastVisit, 20, '\n');

        cout << "Blood Pressure (e.g. 120/80): ";
        cin.getline(bloodPressure, 10, '\n');

        cout << "Heart Rate (bpm): ";
        cin >> heartRate;
        cin.ignore(100, '\n');

        cout << "Address: ";
        cin.getline(Address, 200, '\n');

        // Build SQL query
        char query[1000];
        sprintf(query,
            "INSERT INTO patient_details ( id,name, age, height, weight, last_visit, blood_pressure, heart_rate, address) "
            "VALUES ( %d,'%s', %d, %.2f, %.2f, '%s', '%s', %d, '%s');",
            ID, Name, age, height, weight, lastVisit, bloodPressure, heartRate, Address);

        // Execute the query
        if (mysql_query(obj, query)) {
            cout << "Insert failed: " << mysql_error(obj) << endl;
        } else {
            cout << "Patient record inserted successfully!" << endl;
        }

        // Ask if the user wants to continue
        cout << "Do you want to insert another record? (y/n): ";
        cin >> choice;
        cin.ignore(100, '\n');
    } while (choice == 'y' || choice == 'Y');

    mysql_close(obj);
    return 0;
}

int delete_rec(){
//	system("cls");
//	cout<<"podi";
    system("cls");
    printLine();
    centerText("RAMYA'S PhysioCare");
    printLine();
    system("cls");
	MYSQL* obj;
	obj=mysql_init(0);
	cout<<"Enter Patient id :";
	int id;
	cin>>id;
	if(!obj){
		cout<<"try again ,some error occured";
		return 1;
	}
	if(!mysql_real_connect(obj,HOST,USER,PASS,"clinic",3306,NULL,0)){
		cout<<"try again ,some error occured";
		return 1;
	}
	char a[100];
	sprintf(a,"SELECT * FROM patient_details WHERE id=%d",id);
	if(mysql_query(obj,a)){
		cout<<"try again ,an error occured"<<mysql_error(obj);
		return 0;
	}
    MYSQL_RES* res;
    MYSQL_ROW row;
    res=mysql_store_result(obj);
    if(row=mysql_fetch_row(res)){
    	// name, age, height, weight, last_visit, blood_pressure, heart_rate, address
    	cout<<"Patient ID : "<<row[0]<<endl;
    	cout<<"Name       : "<<row[1]<<endl;
    	cout<<"Age        : "<<row[2]<<endl;
    	cout<<"Height     : "<<row[3]<<endl;
    	cout<<"Weight	   : "<<row[4]<<endl;
    	cout<<"last_visit : "<<row[5]<<endl;
    	cout<<"BP         : "<<row[6]<<endl;
    	cout<<"Heart rate : "<<row[7]<<endl;
    	cout<<"address    : "<<row[8]<<endl;
	}
    mysql_free_result(res);
    char ch;
    cout<<"do you want to delete this patient record ? (y/n):";
    cin>>ch;
    if(ch=='y'){
    char b[100];
    sprintf(b, "DELETE FROM patient_details WHERE id=%d", id);
    
    if(mysql_query(obj, b)) {
        cout << "Deletion failed: " << mysql_error(obj);
    } else {
        cout << "Patient record deleted successfully.\n";
    }
	}
	mysql_close(obj);
    int choice;
    do{
    	cout<<"Enter 0 to Exit :";
    	cin>>choice;
    }while(choice!=0);
	return 0;
	
}
int main() {
	system("color e4");
   int choice;
    printLine();
    do{
        system("cls");
        printLine();
        centerText("RAMYA'S PhysioCare");
        printLine();
        time_t now = time(0); // current time
    	char* dt = ctime(&now); // convert to string format
    	
    	cout << "\nDate & Time  : " << dt<<"\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| View Patient Records      |   1  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| Update Patient Record     |   2  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| Delete Patient Record     |   3  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| Search by Name or ID      |   4  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| View Today's Appointments |   5  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| Book an Appointments      |   6  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"| Exit                      |   0  |\n";
        cout<<"+---------------------------+------+\n";
        cout<<"Please Enter :";
        cin>>choice;
        if(choice==1){
        	print();
		}
		else if(choice==2){
			update();
		}
		else if(choice==3){
			delete_rec();
		}
		else if(choice==4){
    	search();
		}
		else if(choice==5){
    		viewTodayAppointments();
		}
		else if(choice==6){
    		bookAppointment();
		}
    }while(choice!=0);
    return 0;
}

