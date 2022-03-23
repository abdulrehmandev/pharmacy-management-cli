#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

using namespace std;

int id_ = NULL;
string title_ = "";

// used to take integers where ever needed
int takeInt()
{
    int integer;
    cin >> integer;

    while (!cin)
    {
        cin.clear();
        cin.ignore(256, '\n');

        cout << "Wrong Input! Try Again.\n->";
        cin >> integer;
    }

    return integer;
}

// Medicine Node
class Node
{
private:
    int qty;
    int id;
    float price;
    string name;
    string exp;
    Node* link;

public:
    // getters and setters
    void setId(int id)
    {
        this->id = id;
    }
    int getId()
    {
        return id;
    }
    void setQty(int qty)
    {
        this->qty = qty;
    }
    int getQty()
    {
        return qty;
    }
    void setPrice(float price)
    {
        this->price = price;
    }
    float getPrice()
    {
        return price;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }
    void setExp(string exp)
    {
        this->exp = exp;
    }
    string getExp()
    {
        return exp;
    }
    void setLink(Node* link)
    {
        this->link = link;
    }
    Node* getLink()
    {
        return link;
    }
};

// Medicine Class includes all the functions that can be applied to the medicines
class Medicine
{
private:
    Node* start;
    Node* current;
    Node* next;
    Node* temp;

public:
    // medicine constructor
    Medicine()
    {
        start = current = next = temp = NULL;
    }

    // takes the id inthe integer data type
    int takeId()
    {
        int id;

        cout << "Enter ID : ";
        cin >> id;

        // as long as cin is not in good state
        while (!cin)
        {
            // clears the input stream
            cin.clear();
            cin.ignore(256, '\n');

            // and takes the id again
            cout << "Invalid ID!" << endl;
            cout << "Enter ID: ";
            cin >> id;
        }

        // at the end returns the id
        return id;
    }

    // takes the date in the right format
    string takeDate()
    {
        string date, word = "";
        int count = 0;
        int day = NULL, month = NULL, year = NULL;
        bool right = false;

        // takes date unless entered right
        do
        {

            // takes date
            cout << "Expiration Date [dd/mm/yy]: ";
            cin >> date;

            // delimits the date and seperates it into the days, months and years
            for (auto x : date)
            {

                // when / comes, it stores it into the variables according to the count
                if (x == '/')
                {
                    if (count == 0)
                    {
                        day = stoi(word);
                        count++;
                        word = "";
                    }
                    else if (count == 1)
                    {
                        month = stoi(word);
                        count++;
                        word = "";
                    }
                }
                // otherwise store each characters into the word
                else
                {
                    word = word + x;
                }
            }
            year = stoi(word);

            // after the process reinitializing null values for the repetition of process
            count = 0;
            word = "";

            // applies the rules for the right date
            if (day > 0 && day < 32)
            {
                if (month > 0 && month < 13)
                {
                    if (year >= 22 && year <= 24)
                    {
                        right = true;
                        return date;
                    }
                }
            }

            // if date is wrong
            if (!right)
            {
                cout << "Invalid Date! Follow the pattern." << endl;
            }
            else
            {
                return date;
            }

            // clearing the instream
            cin.clear();
            cin.ignore(256, '\n');

        } while (!right);
    }

    // inserts new medicine into the files using linkedlinst
    void insert()
    {
        int id;
        string name, date;
        float price = 0.0;
        int qty, day, mon, year;
        day = mon = year = NULL;

        // if the list is empty
        if (start == NULL)
        {
            next = new Node;

            id = takeId();

            cin.clear();
            cin.ignore(256, '\n');

            // takes the name of the medicine
            cout << "Name of Medicine: ";
            getline(cin, name);

            // takes price aslong as user enters a valid price, price validity is that it should be greater than zero
            while (price <= 0.0)
            {
                cout << "Price: ";
                cin >> price;

                if (price <= 0)
                {
                    cout << "Invalid Price!" << endl;
                }
            }

            cout << "Quantity  Available: ";
            cin >> qty;
            // takes the date in the valid format using takeDate Function
            date = takeDate();

            // sets the node with data
            next->setId(id);
            next->setName(name);
            next->setPrice(price);
            next->setQty(qty);
            next->setExp(date);
            next->setLink(NULL);

            current = next;

            // makes it the first node of the list
            start = next;
        }
        else
        {
            next = new Node;

            // clears the input stream
            /*cin.clear();
            cin.ignore(0);*/

            id = takeId();

            cin.clear();
            cin.ignore(256, '\n');

            cout << "Name of Medicine: ";
            getline(cin, name);

            // takes price aslong as user enters a valid price, price validity is that it should be greater than zero
            while (price <= 0.0)
            {
                cout << "Price: ";
                cin >> price;

                if (price <= 0)
                {
                    cout << "Invalid Price!" << endl;
                }
            }

            cout << "Quantity  Available: ";
            cin >> qty;
            // takes the date in the valid format using takeDate Function
            date = takeDate();

            // sets the node with data
            next->setId(id);
            next->setName(name);
            next->setPrice(price);
            next->setQty(qty);
            next->setExp(date);
            next->setLink(NULL);
            current->setLink(next);

            current = next;
        }

        // opens the stock file and writes the data into it
        ofstream stockFile;
        stockFile.open("Stocks.csv", ios::app);

        stockFile << "\n"
            << id << "," << name << "," << price << "," << qty << "," << date;
        stockFile.close();
    }

    // displays all the medcines in the file
    void display()
    {
        string temp = "";

        string name, exp, word = "";
        int id, qty, count = 0;
        float price;

        // opens up the stocks file
        ifstream stockFile;
        stockFile.open("Stocks.csv");

        cout << "\n-------------------\n";

        if (stockFile.peek() != '\0')
        {

            while (stockFile.good())
            {
                // reads the file line by line
                getline(stockFile, temp);

                // delimits the line by ',' and saves it into the variables
                for (auto x : temp)
                {
                    if (x == ',')
                    {
                        if (count == 0)
                        {
                            id = stoi(word);
                            word = "";
                            count++;
                        }
                        else if (count == 1)
                        {
                            name = word;
                            word = "";
                            count++;
                        }
                        else if (count == 2)
                        {
                            price = stoi(word);
                            word = "";
                            count++;
                        }
                        else if (count == 3)
                        {
                            qty = stoi(word);
                            word = "";
                            count++;
                        }
                    }
                    else
                    {
                        word = word + x;
                    }
                }
                exp = word;

                // prints the variables
                if (temp != "")
                {
                    cout << "ID : " << id << endl;
                    cout << "Name : " << name << endl;
                    cout << "Price : " << price << endl;
                    cout << "Quantity : " << qty << endl;
                    cout << "EXP Date : " << exp << endl
                        << endl;
                }
                // re declare the values to NULL and zero for again processing
                word = "";
                count = 0;
            }
        }
        else
        {
            cout << "No Medicines available!" << endl;
        }

        stockFile.close();
    }

    // searches for a perticular medicine by name
    int search()
    {
        string temp = "", word = "", search = "";
        string name = "", toLowerName, exp;
        int searchId;
        int choice, id, count = 0, qty = NULL;
        float price = NULL;
        bool found = false;
        bool isId = false;

        // open up the stock file to read from
        ifstream stocks;
        stocks.open("Stocks.csv");

        do
        {
            cout << "Search by\n1 - ID\n2 - Name\n3 - Exit\n->";
            choice = takeInt();

            system("cls");

            if (choice == 1)
            {
                // cout << endl << "Enter ID: ";
                searchId = takeId();
                isId = found = true;
                break;
            }
            else if (choice == 2)
            {
                cin.clear();
                cin.ignore(256, '\n');

                cout << endl
                    << "Enter Name of Medicine: ";
                getline(cin, search);

                for (int i = 0; i < search.length(); i++)
                {
                    search[i] = tolower(search[i]);
                }

                found = true;
                break;
            }
            else if (choice == 3)
            {
                return 0;
            }
            else
            {
                cout << "Invalid Input!" << endl;
            }
        } while (!found);

        found = false;

        while (stocks.good())
        {

            // reads the file line by line
            getline(stocks, temp);

            // delimits it by ',' and stores it into the variables
            for (auto a : temp)
            {
                if (a == ',')
                {
                    switch (count)
                    {
                    case 0:
                        id = stoi(word);
                        word = "";
                        count++;
                        break;
                    case 1:
                        name = word;
                        word = "";
                        count++;
                        break;
                    case 2:
                        price = stoi(word);
                        word = "";
                        count++;
                        break;
                    case 3:
                        qty = stoi(word);
                        word = "";
                        count++;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    word = word + a;
                }
            }
            exp = word;
            count = 0;
            word = "";

            // to not change the actual case of the name
            toLowerName = name;

            for (int i = 0; i < toLowerName.length(); i++)
            {
                toLowerName[i] = tolower(toLowerName[i]);
            }

            if (isId)
            {
                if (searchId == id)
                {
                    found = true;
                    break;
                }
            }
            else
            {
                if (search == toLowerName)
                {
                    found = true;
                    break;
                }
            }
            // prints when the search term is found in the file it breaks
        }

        // prints the searched item
        if (found)
        {
            system("cls");
            cout << endl
                << "Medicine Found!" << endl
                << endl;
            cout << "ID : " << id << endl;
            cout << "Name : " << name << endl;
            cout << "Quantity : " << qty << endl;
            cout << "Price : " << price << endl;
            cout << "Expiration Date : " << exp << endl
                << endl;
        }
        // if the searched item is not found
        else
        {
            cout << endl
                << "Medicine Not Found!" << endl;
        }

        stocks.close();

        return 0;
    }

    // updates the already existing medicine
    bool update()
    {
        string temp = "", word = "", search = "";
        string name = "", loweredName, exp;
        int id = NULL, searchId, choice, count = 0, qty = NULL;
        float price = NULL;
        bool isId = false, found = false;

        // opens up stocks file to read from
        ifstream stocks;
        stocks.open("Stocks.csv");

        do
        {
            cout << "Search by\n1 - ID\n2 - Name\n->";
            choice = takeInt();

            system("cls");

            switch (choice)
            {
            case 1:
                // cout << "Enter ID: ";
                searchId = takeId();
                isId = true;
                choice = 3;
                break;
            case 2:
                cin.clear();
                cin.ignore(256, '\n');

                cout << "Enter Name: ";
                getline(cin, search);

                // to lowercase the string
                for (int i = 0; i < search.length(); i++)
                {
                    search[i] = tolower(search[i]);
                }
                choice = 3;
                break;
            case 3:
                return 0;
                break;
            default:
                cout << "Invalid Input!" << endl;
            }
        } while (choice != 3);

        system("cls");

        // to read the file
        while (stocks.good())
        {
            getline(stocks, temp);

            // delimits each line by ',' and saves it into the variables
            for (auto a : temp)
            {
                if (a == ',')
                {
                    switch (count)
                    {
                    case 0:
                        id = stoi(word);
                        word = "";
                        count++;
                        break;
                    case 1:
                        name = word;
                        word = "";
                        count++;
                        break;
                    case 2:
                        price = stoi(word);
                        word = "";
                        count++;
                        break;
                    case 3:
                        qty = stoi(word);
                        word = "";
                        count++;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    word = word + a;
                }
            }
            exp = word;

            count = 0;
            word = "";

            // to not change the actual case of the name
            loweredName = name;

            // lowecasing the name
            for (int i = 0; i < loweredName.length(); i++)
            {
                loweredName[i] = tolower(loweredName[i]);
            }

            if (isId)
            {
                if (id == searchId)
                {
                    found = true;
                    break;
                }
            }
            else
            {
                if (search == loweredName)
                {
                    found = true;
                    break;
                }
            }
            // if medicine is found it breaks out of loops
        }

        stocks.close();

        // prints the medicine
        if (found)
        {
            cout << endl
                << "Medicine Found!" << endl
                << endl;
            cout << "ID : " << id << endl;
            cout << "Name : " << name << endl;
            cout << "Price : " << price << endl;
            cout << "Quantity : " << qty << endl;
            cout << "Expiration Date : " << exp << endl;
        }
        else
        {
            cout << "Medicine Not Found!" << endl;
            stocks.close();
            return 0;
        }

        string newName, newExp;
        int newId, newQty;
        float newPrice;

        // takes the new attributes of the medicine to be updates
        cout << endl
            << "-- Updation --" << endl
            << endl;
        // cout << "ID : ";
        newId = takeId();

        cin.clear();
        cin.ignore(256, '\n');

        cout << "Name : ";
        getline(cin, newName);

        cout << "Price : ";
        cin >> newPrice;
        cout << "Quantity: ";
        newQty = takeInt();
        newExp = takeDate();

        // opens the stocks file to read from
        ifstream stocksIn;
        stocksIn.open("Stocks.csv");

        // makes a new temp file to write all of the data into
        ofstream stocksOut;
        stocksOut.open("temp.csv");

        word = "";
        count = 0;

        int checkId = NULL;
        bool done = false;

        while (stocksIn.good())
        {
            // reads file line by line
            getline(stocksIn, temp);

            // delimits each line to get the names of medicine
            for (auto a : temp)
            {
                if (a == ',')
                {
                    switch (count)
                    {
                    case 0:
                        checkId = stoi(word);
                        word = "";
                        count++;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    word = word + a;
                }
            }

            count = 0;
            word = "";

            // if comes the updated medicine, it writes the new attributes
            if (checkId == id && !done)
            {
                stocksOut << newId << "," << newName << "," << newPrice << "," << newQty << "," << newExp << "\n";
                cout << endl
                    << "Medicine Updated Successfully!" << endl;
                done = true;
            }
            // otherwise writes the line same as before
            else
            {
                stocksOut << temp << "\n";
            }
        }

        // closes both files
        stocksIn.close();
        stocksOut.close();

        // removes the previous stocks file and rename the temp by original stocks file name
        remove("Stocks.csv");
        rename("temp.csv", "Stocks.csv");

        return 0;
    }
};

// Login class carrying all of the methods handling with accounts
class Login
{
private:
    int id;
    string password;
    string title;

public:
    // Login Constructor
    Login()
    {
        id = NULL;
        password = title = "";
    }

    // takes the id inthe integer data type
    int takeId()
    {
        int id;

        cout << "Enter ID: ";
        cin >> id;

        // as long as cin is not in good state
        while (!cin)
        {
            // clears the input stream
            cin.clear();
            cin.ignore(256, '\n');

            // and takes the id again
            cout << "Invalid ID!" << endl;
            cout << "Enter ID: ";
            cin >> id;
        }

        // at the end returns the id
        return id;
    }

    // to take a password in the hidden form
    string takePass()
    {
        string pass;
        char ch;

        // takes a charachter
        ch = _getch();
        while (ch != 13)
        {
            // pushes each character into the string and then prints a * and repeats
            // we could also use : pass = pass + ch;
            pass.push_back(ch);
            cout << "*";
            ch = _getch();
        }
        // returns a password as a string
        return pass;
    }

    // method to create a account for a new user
    bool create_account()
    {
        int tempId, checkId, tries = 0;
        string tempPass, confirmPass;
        string tempTitle;
        string temp, word;

        // reads the accounts file to check if the user already exists or not
        ifstream accountsFile;
        accountsFile.open("Accounts.csv");

        // takes the id of the user
        cout << endl;
        tempId = takeId();

        while (accountsFile.good())
        {
            getline(accountsFile, temp);

            // delimits each line and stores them in variables
            for (auto a : temp)
            {
                if (a == ',')
                {
                    checkId = stoi(word);
                    break;
                }
                else
                {
                    word = word + a;
                }
            }

            word = "";

            // checks the user entered id with already existing id's
            if (tempId == checkId)
            {
                cout << "Account already exists!\nTry to Log In" << endl;
                return 0;
            }
        }
        accountsFile.close();

        // takes a password
        do
        {
            // gets the password
            cout << "Enter the password: ";
            password = takePass();
            cout << endl;

            // confirms password
            cout << "Confirm Password: ";
            confirmPass = takePass();
            cout << endl;

            // checks if confirm pass and pass are same and continues
            if (password == confirmPass)
            {
                cout << "Account Created Successfully!" << endl;
                // enters the data of the new user into the file of accounts and saves it
                ofstream accountsWrite;
                accountsWrite.open("Accounts.csv", ios_base::app);

                accountsWrite << tempId << "," << password << "\n";
                accountsWrite.close();

                // ends the program after every thing is successfull
                return 1;
            }
            else
            {
                cout << "Passwords does not match! Try Again." << endl;
            }

            // counts the tries to enter password and gives a user maximum of 3 tries
            tries++;
        } while (tries < 3);

        return 0;
    }

    // to log user into already existing account
    bool login()
    {
        int id, tempId;
        int count = 0, tries = 0;
        string password, tempPass;
        int title;
        string temp, word;
        bool found = false;

        do
        {
            cout << endl;
            // takes the id and the password from the user
            id = takeId();
            cout << "Enter Password: ";
            password = takePass();
            cout << endl;

            // open up the accounts file for validation
            ifstream accountsFile;
            accountsFile.open("Accounts.csv");

            while (accountsFile.good())
            {
                getline(accountsFile, temp);

                // delimits each line from the file and stores them into the variables
                for (auto a : temp)
                {
                    if (a == ',')
                    {
                        if (count == 0)
                        {
                            // to store string to a int type variable
                            tempId = stoi(word);
                        }
                        word = "";
                        count++;
                    }
                    else
                    {
                        word = word + a;
                    }
                }
                tempPass = word;
                word = "";
                count = 0;

                // validates the login id's from the user to the existing account
                if (id == tempId)
                {
                    if (password == tempPass)
                    {
                        system("cls");
                        cout << "Login as\n1 - Buyer\n2 - Seller\n->";
                        cin >> title;

                        if (title == 1)
                        {
                            title_ = "Buyer";
                            found = true;
                        }
                        else if (title == 2)
                        {
                            title_ = "Seller";
                            found = true;
                        }
                        else
                        {
                            cout << "Invalid Input!" << endl;
                        }
                    }
                }
            }
            accountsFile.close();

            // to get the exact time of the login
            time_t t = time(0);
            tm* timenow = localtime(&t);

            // if id and password does not match
            if (found)
            {
                cout << endl
                    << "Login as " << title_ << "!" << endl;

                // makes time and date into string
                string timestr = to_string(timenow->tm_hour) + ':' + to_string(timenow->tm_min) + ':' + to_string(timenow->tm_sec);
                string datestr = to_string(timenow->tm_mday) + '/' + to_string(timenow->tm_mon + 1) + '/' + to_string(timenow->tm_year + 1900);

                // stores the history of any login happening
                ofstream logins;
                logins.open("LoginHistory.csv", ios_base::app);

                logins << id << "," << title_ << "," << timestr << "," << datestr << "\n";
                id_ = id;

                logins.close();

                return true;
            }
            else
            {
                cout << "Wrong Id or Password!" << endl;
            }

            // user will be given 3 tries
            tries++;
        } while (tries < 3);

        cout << "Try Again Later!" << endl;

        return false;
    }
};

// Order class carrying all the methods for orders and requests
class Order
{
public:
    // creates a new order for the user from the available stocks
    void makeOrder()
    {
        string temp, word;
        string name, exp;
        int searchId;
        int id = NULL, qty = NULL, askQty = 0;
        float price = NULL;
        int count = 0, tries = 0;
        bool found = false;
        float total = 0.0, subTotal = 0.0;
        int userChoice;

        // makes a new order file
        ofstream order;
        order.open("Order.csv");

        time_t t = time(0);
        tm* timenow = localtime(&t);

        string timestr = to_string(timenow->tm_hour) + ':' + to_string(timenow->tm_min) + ':' + to_string(timenow->tm_sec);
        string datestr = to_string(timenow->tm_mday) + '/' + to_string(timenow->tm_mon + 1) + '/' + to_string(timenow->tm_year + 1900);

        // puts attributes heading on the top
        order << "Time: " << timestr << "\n";
        order << "Date: " << datestr << "\n\n";
        order << "Name,Quantity,Price,Cost\n";

        do
        {
            userChoice = NULL;

            // takes medicine name and searches for it
            cout << endl
                << "Enter Medicine ID: ";
            searchId = takeInt();

            // opens a temp file and a stock file to read from
            ofstream newStocks;
            newStocks.open("temp.csv");

            ifstream stocks;
            stocks.open("Stocks.csv");

            // reads the file line by line
            while (stocks.good())
            {
                getline(stocks, temp);

                // delimits the line and saves into the variables
                for (auto a : temp)
                {
                    if (a == ',')
                    {
                        switch (count)
                        {
                        case 0:
                            id = stoi(word);
                            word = "";
                            count++;
                            break;
                        case 1:
                            name = word;
                            word = "";
                            count++;
                            break;
                        case 2:
                            price = stoi(word);
                            word = "";
                            count++;
                            break;
                        case 3:
                            qty = stoi(word);
                            word = "";
                            count++;
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        word = word + a;
                    }
                }

                exp = word;
                word = "";
                count = 0;

                // if the name is found
                if (searchId == id)
                {
                    found = true;

                    // prints the medicine
                    cout << endl
                        << "ID : " << id << endl;
                    cout << "Name : " << name << endl;
                    cout << "Price : " << price << endl;
                    cout << "Quantity : " << qty << endl;
                    cout << "Expiration : " << exp << endl
                        << endl;

                    // takes the quantity of the medicine till the max amount available
                    cout << "Quantity you want [" << qty << " max] : ";
                    cin >> askQty;

                    // if user asks more than what we have
                    if (askQty > qty)
                    {
                        cout << "Maximum quantity available is " << qty << endl;
                        newStocks << temp << "\n";
                    }
                    // other wise it adds the price into subtotals and totals
                    else
                    {
                        subTotal = (askQty * price);
                        total += subTotal;

                        // writes it into the reciept
                        order << name << "," << askQty << "," << price << "," << subTotal << "\n";

                        cout << "Medicine Added Successfully!" << endl
                            << endl;
                        qty = qty - askQty;
                        newStocks << id << "," << name << "," << price << "," << qty << "," << exp << "\n";

                        askQty = 0;
                    }

                    // newStocks << name << "," << price << "," << qty << "," << exp << "\n";
                }
                // if medicine is not found it simply appends the line into the file
                else
                {
                    newStocks << temp << "\n";
                }

                id = NULL;
                name = "";
                qty = NULL;
                price = NULL;
                exp = "";
            }

            // after the overall reading procedure, it will check whether the med is found or not
            if (!found)
            {
                cout << "Medicine Not Found!" << endl
                    << endl;
            }

            // asks if user wants to add any other medicine
            cout << "Do You want to Enter another Medicine?\n1 - Yes\n2 - No\n3 - Exit\n->";
            userChoice = takeInt();

            if (userChoice < 1 || userChoice > 3)
            {
                cout << "Invalid Input!";
                break;
            }
            else if (userChoice == 2)
            {
                remove("Stocks.csv");
                rename("temp.csv", "Stocks.csv");
                break;
            }

            found = false;
            count = 0;
            word = "";
            searchId = NULL;

            stocks.close();
            newStocks.close();

            // removes the previous stock file and renames temp file with updated quantities with the original stocks file naem
            remove("Stocks.csv");
            rename("temp.csv", "Stocks.csv");

            // loops till user enters no
        } while (userChoice != 3);

        cout << "Order Places Successfully!\nYou can see your reciept named 'Order.csv'" << endl;

        // adds the total price at the end of the reciept
        order << "\nTotal: " << total;
        order.close();
    }

    // gets a request from a user to add in the medical store
    void requestMed()
    {
        string name;
        int qty;

        // takes the name and quantity
        cout << endl
            << "Enter Medicine Name: ";
        getline(cin, name);

        cout << "Enter Quantity: ";
        qty = takeInt();

        // opens the requests file and add it in
        ofstream requests;
        requests.open("Requests.csv", ios::app);

        cout << endl
            << "Request Added to the Queue Successfully!" << endl;

        requests << name << "," << qty << "\n";
        requests.close();
    }
};

// Menu class containing all the methods for user interface
class Menu
{
public:
    // when seller is logged in
    static void sellerMenu()
    {
        int choice;
        Medicine med;

        do
        {
            cout << endl
                << "-------------------";
            cout << endl
                << "Display All - 1\nSearch Medicine - 2\nUpdate Medicine - 3\nInsert Medicine - 4\nExit - 5\n\n->";
            choice = takeInt();

            // clears the input stream
            cin.clear();
            cin.ignore(256, '\n');

            switch (choice)
            {
            case 1:
                system("cls");
                med.display();
                break;
            case 2:
                system("cls");
                med.search();
                break;
            case 3:
                system("cls");
                med.update();
                break;
            case 4:
                system("cls");
                med.insert();
                break;
            case 5:
                system("cls");
                break;
            default:
                system("cls");
                cout << "Ivalid Input!" << endl;
                break;
            }

        } while (choice != 5);
    }

    // when the buyer is logged in
    static void buyerMenu()
    {

        int choice;
        Medicine med;
        Order order;

        do
        {
            cout << endl
                << "-------------------";
            cout << endl
                << "Display All - 1\nSearch Medicine - 2\nOrder Medicine - 3\nRequest Medicine - 4\nExit - 5\n\n->";
            choice = takeInt();

            // clears the input stream
            cin.clear();
            cin.ignore(256, '\n');

            switch (choice)
            {
            case 1:
                system("cls");
                med.display();
                break;
            case 2:
                system("cls");
                med.search();
                break;
            case 3:
                system("cls");
                order.makeOrder();
                break;
            case 4:
                system("cls");
                order.requestMed();
                break;
            case 5:
                system("cls");
                break;
            default:
                system("cls");
                cout << "Ivalid Input!" << endl;
                break;
            }
        } while (choice != 5);
    }

    // for the main menu to call other functions
    static int mainMenu()
    {
        Login login;
        int choice;
        bool active = false;

        do
        {
            cout << "Sign-In - 1\nSign-Up - 2\nExit - 3\n->";
            choice = takeInt();

            // clears the input stream
            cin.clear();
            cin.ignore(256, '\n');

            switch (choice)
            {
            case 1:
                active = login.login();
                system("cls");

                if (active)
                {
                    if (title_ == "Buyer")
                    {
                        system("cls");
                        buyerMenu();
                    }
                    else
                    {
                        system("cls");
                        sellerMenu();
                    }
                }
                else
                {
                    return 0;
                }
                break;
            case 2:
                active = login.create_account();
                system("cls");

                if (active)
                {
                    active = false;
                    cout << "Login -- " << endl;
                    active = login.login();
                    system("cls");

                    if (active)
                    {
                        if (title_ == "Buyer")
                        {
                            system("cls");
                            buyerMenu();
                        }
                        else
                        {
                            system("cls");
                            sellerMenu();
                        }
                    }
                }
                break;
            case 3:
                break;
            default:
                cout << "Invalid Input!" << endl;
                break;
            }
        } while (choice != 3);

        return 0;
    }
};

int main()
{
    // calling the main menu function to interact with user
    Menu::mainMenu();
    return 0;
}