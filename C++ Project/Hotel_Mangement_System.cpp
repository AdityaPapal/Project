#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;

class Hotel
{
private:
    int room_num;
    char name[30];
    char address[50];
    char phone[10];

public:
    void add_coustomer()
    {
        cout << "\nEnter the Room Number: ";
        cin >> room_num;

        cout << "\nEnter Client Name: ";
        cin.ignore();
        cin.getline(name, 30);

        cout << "\nEnter Client Address: ";
        cin.ignore();
        cin.getline(address, 50);

        cout << "\nEnter the Client Mobile Number: ";
        cin.ignore();
        cin.getline(phone, 10);

        cout << "\t\t\n\nEntries has been Done...!";
    }

    void Display_data()
    {
        cout << endl
             << "Room Number: " << room_num << endl;

        cout << "Client Name: " << name << endl;
        cout << "Client Address: " << address << endl;
        cout << "Client Mobile Number: " << phone << endl;
    }

    void updte_coustomer()
    {
        cout << "\nUpdate the Room Number: ";
        cin >> room_num;

        cout << "\nUpdateClient Name: ";
        cin.ignore();
        cin.getline(name, 30);

        cout << "\nUpdate Client Address: ";
        cin.ignore();
        cin.getline(address, 50);

        cout << "\nUpdate the Client Mobile Number: ";
        cin.ignore();
        cin.getline(phone, 10);

        cout << "\t\t\n\nEntries Update Successfully...!";
    }

    int getRoom()
    {
        return room_num;
    }

    char *getName()
    {
        return name;
    }

    char *getAddress()
    {
        return address;
    }

    char *getPhone()
    {
        return phone;
    }

    void report()
    {
        cout << "\t\t" << room_num << setw(10) << name << setw(20) << address << setw(20) << phone << endl;
    }
};

fstream fp;
Hotel h;

void save_info()
{
    system("cls");
    int option;
    fp.open("Hotel.dat", ios::out | ios::app);

    do
    {
        h.add_coustomer();
        fp.write((char *)&h, sizeof(Hotel));

        cout << endl
             << "Press 1 to add more Client." << endl;
        cout << endl
             << "Press 2 to return in main menu." << endl;

        cout << "Option: " << endl;
        cin >> option;

    } while (option == 1);

    fp.close();
}

void clientntdetails(int r_number)
{
    system("cls");

    cout << endl
         << "Client Details" << endl;
    int check = 0;

    fp.open("hotel.dat", ios::in);

    while (fp.read((char *)&h, sizeof(Hotel)))
    {

        if (h.getRoom() == r_number)
        {
            h.Display_data();
            check = 1;
        }
    }
    fp.close();
    if (check == 0)
    {
        cout << "\n\nClient Data does not Exist" << endl;
    }
    getch();
}

void modify_client()
{
    system("cls");
    int r_number;
    int found = 0;
    cout << "\n\nUpdate Client's Record";
    cout << "Enter the Room Number: ";
    cin >> r_number;

    fp.open("Hotel.dat", ios::in | ios::out);

    while (fp.read((char *)&h, sizeof(Hotel)) && found == 0)
    {

        if (h.getRoom() == r_number)
        {
            h.Display_data();
            cout << "\nEnter the client new Information" << endl;
            h.updte_coustomer();
            int pos = -1 * sizeof(h);
            fp.seekg(pos, ios::cur);
            fp.write((char *)&h, sizeof(Hotel));
            cout << "\n\n\t Record Updated Successfully";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\nRecord not Found" << endl;
    getch();
}

void delete_client()
{

    system("cls");
    int r_number;
    int flag = 0;
    cout << "\n\nDelete Clients";
    cout << endl
         << "Enter the Room Number you wont to Delete: ";
    cin >> r_number;

    fp.open("Hotel.dat", ios::in | ios::out);

    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);

    while (fp.read((char *)&h, sizeof(Hotel)))
    {
        if (h.getRoom() == r_number)
        {
            fp.write((char *)&h, sizeof(Hotel));
        }
        else
        {
            flag = 1;
        }
        fp2.close();
        fp.close();

        remove("hotel.dat");
        rename("Temp.dat", "hotel.dat");

        if (flag == 1)
            cout << "\n\nRecord Deleted";
        else
            cout << "\n\nRecord not Found";
        getch();
    }
}

void display_all_client()
{

    system("cls");
    fp.open("hotel.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR! : File Could not be Open";
        getch();
        return;
    }
    cout << "\n\nClient List\n\n";
    cout << "===================================================================\n";
    cout << "\tRoom Number." << setw(10) << "Name" << setw(20) << "Address" << setw(20) << "Phone" << endl;
    cout << "===================================================================\n";

    while (fp.read((char *)&h, sizeof(Hotel)))
    {
        h.report();
    }
    fp.close();
    getch();
}

void main_menu()
{
    int option;
    for (;;)
    {
        cout << "\t\tHotel Mangement System" << endl;
        cout << "\t\t==========================================" << endl;
        cout << "\t\tPress 1 to book a Room" << endl;
        cout << "\t\tPress 2 to Display all Room Allotted" << endl;
        cout << "\t\tPress 3 to Display Specific Client Record" << endl;
        cout << "\t\tPress 4 to Update Client Record" << endl;
        cout << "\t\tPress 5 to Delete Client Record" << endl;
        cout << "\t\tPress 6 to Exit" << endl;
        cout << "\t\t==========================================" << endl;

        cout << "\n\t\tOption: ";
        cin >> option;

        switch (option)
        {
        case 1:
            save_info();
            break;
        case 2:
            display_all_client();
            system("cls");
            break;

        case 3:
            int r_number;
            system("cls");
            cout << "\n\n\tPlease Enter the Client's Room Number: ";
            cin >> r_number;

            clientntdetails(r_number);
            break;

        case 4:
            modify_client();
            system("cls");
            break;
        case 5:
            delete_client();
            system("cls");
            break;
        case 6:
            exit(0);
            break;

        default:
            cout << "\a";
        }
    }
}
void intro()
{
    system("white");
    system("cls"); // cls stand for clear screen
}

int main(int argc, char *argv[])
{
    intro();
    main_menu();
}