#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ctime>
using namespace std;

void create()
{
    ofstream hashDatabase;
    string hash_value;
    string usernameInput;
    string passwordInput;
    string hash_input; 

    //user input
    cout << "\nCreate your username" << endl;
    cout << "----------------------" << endl;
    cin >> usernameInput;
    cout << "\nCreate your password" << endl;
    cout << "----------------------" << endl;
    cin >> passwordInput;

    //hash
    hash_input = usernameInput+passwordInput;
    hash<string> hasher;
    hash_value = hash_input;
    size_t hash = hasher(hash_value);

    //writing database
    hashDatabase.open("hashDatabase.txt", std::ios_base::app);
    hashDatabase << hasher(hash_value) << "\n";
    hashDatabase.close();

    cout << "\nYour account has been created.\n" << endl;



}

bool login() //testing a theory
{
    ifstream hashDatabase;
    string hash_value;
    string usernameInput;
    string passwordInput;
    string hash_input;
    string fileinfo;
    bool result;

    //user input
    cout << "\nEnter your username" << endl;
    cout << "----------------------" << endl;
    cin >> usernameInput;
    cout << "\nEnter your Password" << endl;
    cout << "----------------------" << endl;
    cin >> passwordInput;

    //hash
    hash_input = usernameInput+passwordInput;
    hash<string> hasher;
    hash_value = hash_input;
    size_t hash = hasher(hash_value);
    string hashT = to_string(hasher(hash_value));

   //reading database
    hashDatabase.open("hashDatabase.txt");
    if (hashDatabase.is_open())
    {
        while (getline (hashDatabase,fileinfo))
        if (hashT == fileinfo)
        {
            result = true;
            break;
        } else {
            result = false;
        }
        if (result == true)
        {
            cout << "\nAccess Granted." << endl;
        } else {
            cout << "\nAccess Denied." << endl;
        }
        hashDatabase.close();
    }
    if (result == true)
    {
        return(1);
    }else {
        return(0);
    }
}

void appData()
{
    ofstream timeLog;

    //writing log to database
    cout << "\nLogging entry to software..." << endl;
    timeLog.open("log.txt", std::ios_base::app);
    time_t * rawtime = new time_t;
    struct tm * timeinfo;
    time(rawtime);
    timeinfo = localtime(rawtime);
    timeLog << asctime(timeinfo) << "\n";
    timeLog.close();

    // Opening software
    cout << "\nOpening code propmt..." << endl;
    system("python");

}

void welcomeScreen()
{
    int userChoice;
    cout << "Would you like to: \n1. Sign-in\n2. Sign-up" << endl;
    cin >> userChoice;
    if (userChoice == 1)
    {
        if (login() == 1)
        {
            appData();
        } else {
            cout << "Exiting software..." << endl;
        }
    }else if (userChoice == 2)
    {
        create();
    } else {
        cout << "Not a valid option." << endl;
    }
}

int main()
{
    welcomeScreen();
    return 0;
}
