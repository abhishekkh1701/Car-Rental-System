#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

int id = 6;
int id_employee = 6;
int fineRate = 100;
int totalfine = 0;
double discount = 0.15;
int countLinesInFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return -1; // Return -1 to indicate an error
    }

    int lineCount = 0;
    string line;
    while (getline(file, line))
    {
        lineCount++;
    }

    file.close();
    return lineCount;
}
class Car
{
private:
    string model;
    string registrationNumber;
    int condition;
    int rentCost;
    bool isAvailable;
    int returnDays;
    string towhom;

public:
    // Public constructor to initialize Car object
    Car(const string &model, const string &regNum, int cond, int cost, bool available, const string &whom, int days)
        : model(model), registrationNumber(regNum), condition(cond), rentCost(cost), isAvailable(available), towhom(whom), returnDays(days) {}
    void changecondition(int cond)
    {

        condition = cond;
        towhom = "None";
        isAvailable = 1;
    }

    int getRentCost()
    {
        return rentCost;
    }

    void displayDetailsIfAvailable() const
    {
        // cout<<isAvailable;
        if (isAvailable == 1)
        {
            cout << "Model: " << model << "\n";
            cout << "Registration Number: " << registrationNumber << "\n";
            cout << "Condition in number of stars: " << condition << "\n";
            cout << "Rent Cost: $" << rentCost << "\n";
            cout << "Is Available: Yes\n";
            cout << "-------------------------\n";
        }
    }
    void displayDetailsofRentedCar(const string &renter) const
    {
        // cout<<isAvailable;
        if (towhom == renter)
        {
            cout << "Model: " << model << "\n";
            cout << "Registration Number: " << registrationNumber << "\n";
            cout << "Condition in number of stars: " << condition << "\n";
            cout << "Rent Cost: $" << rentCost << "\n";
            cout << "Renter: " << renter << "\n";
            cout << "Number of days for which you have booked the car: " << returnDays << "\n";
            cout << "-------------------------\n";
        }
    }
    static void displayDetails()
    {
        ifstream file("car.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string model, regNum, towhom;
            int cost, available, days, condition;

            getline(ss, model, ',');
            getline(ss, regNum, ',');

            char comma;
            ss >> condition >> comma >> cost >> comma >> available >> comma;
            getline(ss, towhom, ',');
            ss >> days;
            // cout<<days<<" ";
            cout << "modelid : " << model << endl;
            cout << "regnum: " << regNum << endl;
            cout << "condition in stars: " << condition << endl;
            cout << "cost: $" << cost << endl;
            cout << "available(1 for yes and 0 for no)" << available << endl;
            cout << "rented to : " << towhom << endl;
            cout << "--------------\n";
            // car.rentCar();  // Assume the car is being rented when reading from file
            // car.displayDetailsIfAvailable();
        }

        file.close();
        return;
    }

    bool checkAvailability() const
    {
        return isAvailable;
    }
    string getRegistrationNumber()
    {
        return registrationNumber;
    }
    string gettowhom() const
    {
        return towhom;
    }
    int getreturnday() const
    {
        return returnDays;
    }
    int getCondition()
    {
        return condition;
    }
    string getModel()
    {
        return model;
    }
};
class user
{
protected:
    string username;
    string password;
    string ID;

public:
    user() {}
    user(const std::string &uname, const std::string &pwd, const std::string &id)
        : username(uname), password(pwd), ID(id) {}
};

class Manager : public user
{
public:
    Manager(const std::string &uname, const std::string &pwd, const std::string &id)
        : user(uname, pwd, id) {}

    Manager() {}

    void registerNewCustomer() const;
    void registerNewEmployee() const;
    void DeleteCar(const string &filename, const string &carname);
    void deleteCustomer(const string &filename, const string &username);
    void SearchCustomer(const string &filename, const string &username);
    void deleteEmployee(const string &filename, const string &username);
    void SearchEmployee(const string &filename, const string &username);
};
void Manager::DeleteCar(const string &filename, const string &carname)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNum, towhom;
        int cost, available, days, condition;

        getline(ss, model, ',');
        getline(ss, regNum, ',');

        char comma;
        ss >> condition >> comma >> cost >> comma >> available >> comma;
        getline(ss, towhom, ',');
        ss >> days;

        if (model == carname)
        {
            // Update the line with new information
            if (available == 0)
            {
                cout << "Car is rented so not possible to delete!";
            }
            else
                updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

class Customer : private user
{
private:
    int fineDue;
    int customerRecord;

    // vector<Car> carsRented;

public:
    Customer(const string &uname, const string &pwd, const string &id,
             int fine, int record)
        : user(uname, pwd, id), fineDue(fine), customerRecord(record) {}

    Customer() {}
    // int customerRec()const
    // {
    //     return customerRecord;
    // }
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    int getFineDue()
    {
        return fineDue;
    }
    int getCustomerRecord()
    {
        return customerRecord;
    }
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<Customer> readCustomerData()
    {
        vector<Customer> customers;
        ifstream file("customer.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            Customer customer;
            getline(ss, customer.username, ',');
            getline(ss, customer.password, ',');
            getline(ss, customer.ID, ',');
            char comma;
            ss >> customer.customerRecord >> comma >> customer.fineDue;

            customers.push_back(customer);
        }

        file.close();
        return customers;
    }

    static void writeCustomerData(const vector<Customer> &customers)
    {
        ofstream file("customer.txt");
        for (size_t i = 0; i < customers.size(); ++i)
        {
            const auto &customer = customers[i];
            file << customer.username << ","
                 << customer.password << ","
                 << customer.ID << ","
                 << customer.customerRecord << ","
                 << customer.fineDue;

            // Do not write a newline character if it's the last entry
            if (i != customers.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};
class Employee : private user
{
private:
    int fineDue;
    int employeeRecord;

    // vector<Car> carsRented;

public:
    Employee(const string &uname, const string &pwd, const string &id,
             int fine, int record)
        : user(uname, pwd, id), fineDue(fine), employeeRecord(record) {}

    Employee() {}
    // int employeeRec()const
    // {
    //     return employeeRecord;
    // }
    string getUsername() const
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getID()
    {
        return ID;
    }
    int getFineDue()
    {
        return fineDue;
    }
    int getemployeeRecord()
    {
        return employeeRecord;
    }
    bool authenticate(const string &enteredPassword) const
    {
        return (password == enteredPassword);
    }
    static vector<Employee> reademployeeData()
    {
        vector<Employee> employees;
        ifstream file("employee.txt");
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            Employee employee;
            getline(ss, employee.username, ',');
            getline(ss, employee.password, ',');
            getline(ss, employee.ID, ',');
            char comma;
            ss >> employee.employeeRecord >> comma >> employee.fineDue;

            employees.push_back(employee);
        }

        file.close();
        return employees;
    }

    static void writeemployeeData(const vector<Employee> &employees)
    {
        ofstream file("employee.txt");
        for (size_t i = 0; i < employees.size(); ++i)
        {
            const auto &employee = employees[i];
            file << employee.username << ","
                 << employee.password << ","
                 << employee.ID << ","
                 << employee.employeeRecord << ","
                 << employee.fineDue;

            // Do not write a newline character if it's the last entry
            if (i != employees.size() - 1)
            {
                file << "\n";
            }
        }
        file.close();
    }
};
void Manager::registerNewCustomer() const
{
    vector<Customer> customers = Customer::readCustomerData();
    cout << "Enter username(without spaces): ";
    string username;
    cin >> username;

    auto it = find_if(customers.begin(), customers.end(),
                      [username](const Customer &c)
                      { return c.getUsername() == username; });

    if (it != customers.end())
    {
        cout << "This username already exists. Try Again.\n";
    }
    else
    {
        string password;
        cout << "Enter password: ";
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password == confirmPassword)
        {
            Customer newCustomer(username, password, to_string(id), 0, 5);
            customers.push_back(newCustomer);
            Customer::writeCustomerData(customers);
            cout << "Registration successful! Please log in again.\n";
        }
        else
        {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}
void Manager::registerNewEmployee() const
{
    vector<Employee> Employees = Employee::reademployeeData();
    cout << "Enter username(without spaces): ";
    string username;
    cin >> username;

    auto it = find_if(Employees.begin(), Employees.end(),
                      [username](const Employee &c)
                      { return c.getUsername() == username; });

    if (it != Employees.end())
    {
        cout << "This username already exists. Try Again.\n";
    }
    else
    {
        string password;
        cout << "Enter password: ";
        cin >> password;

        string confirmPassword;
        cout << "Confirm password: ";
        cin >> confirmPassword;

        if (password == confirmPassword)
        {
            Employee newEmployee(username, password, to_string(id_employee), 0, 5);
            Employees.push_back(newEmployee);
            Employee::writeemployeeData(Employees);
            cout << "Registration successful! Please log in again.\n";
        }
        else
        {
            cout << "Password and Confirm Password do not match. Registration failed.\n";
        }
    }
}

static vector<Car> readCarData()
{
    vector<Car> cars;
    ifstream file("car.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string model, regNum, towhom;
        int cost, available, days, condition;

        getline(ss, model, ',');
        getline(ss, regNum, ',');

        char comma;
        ss >> condition >> comma >> cost >> comma >> available >> comma;
        getline(ss, towhom, ',');
        ss >> days;
        // cout<<days<<" ";
        Car car(model, regNum, condition, cost, available, towhom, days);

        // car.rentCar();  // Assume the car is being rented when reading from file
        // car.displayDetailsIfAvailable();
        cars.push_back(car);
    }

    file.close();
    return cars;
}
int hasUserRentedCar(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return false; // Error condition or default value
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNum, towhom;
        int cost, available, days, condition;

        getline(ss, model, ',');
        getline(ss, regNum, ',');

        char comma;
        ss >> condition >> comma >> cost >> comma >> available >> comma;
        getline(ss, towhom, ',');
        ss >> days;

        if (towhom == username)
        {
            inFile.close();
            return 1;
        }
    }

    inFile.close();
    return 0;
}
void updateCarInfo(const string &filename, const string &carname, int newCondition, bool newAvailability, int returndays, const string &newToWhom)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNum, towhom;
        int cost, available, days, condition;

        getline(ss, model, ',');
        getline(ss, regNum, ',');

        char comma;
        ss >> condition >> comma >> cost >> comma >> available >> comma;
        getline(ss, towhom, ',');
        ss >> days;

        // Print the values to check if they are read correctly
        // cout << "Model: " << model << ", Registration Number: " << regNum << ", Condition in stars: " << condition
        //      << ", Cost: " << cost << ", Available: " << available << ", To Whom: " << towhom
        //      << ", Days: " << days <<  endl;

        if (model == carname)
        {
            // Update the line with new information
            tempFile << model << "," << regNum << "," << newCondition << "," << cost << ","
                     << newAvailability << "," << newToWhom << "," << returndays;
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

void updateCustomerInfo(const string &filename, const string &username, int newCustomerRecord, int days)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int customerRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> customerRecord >> comma >> fineDue;

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", CustomerRecord: " << customerRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," << customerRecord + newCustomerRecord << "," << fineDue + fineRate * days;
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

void clearfinedue(const string &filename, const string &username, int amount)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int customerRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> customerRecord >> comma >> fineDue;

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", CustomerRecord: " << customerRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," << customerRecord << "," << fineDue - amount << endl;
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void Manager ::deleteCustomer(const string &filename, const string &username)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int customerRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> customerRecord >> comma >> fineDue;

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", CustomerRecord: " << customerRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void Manager ::SearchCustomer(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return; // Error condition or default value
    }
    int flag = 0;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int CustomerRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> CustomerRecord >> comma >> fineDue;
        if (uname == username)
        {
            cout << "username: " << username << endl;
            cout << "Customer record: " << CustomerRecord << endl;
            cout << "fine Due: " << fineDue << endl;
            flag = 1;
            break;
        }
        if (flag == 0)
            cout << "User doesn't exist \n";
        inFile.close();
        return;
    }
}
void updateEmployeeInfo(const string &filename, const string &username, int newEmployeeRecord, int days)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int EmployeeRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> EmployeeRecord >> comma >> fineDue;

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", EmployeeRecord: " << EmployeeRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information
            tempFile << uname << "," << password << "," << id << "," << EmployeeRecord + newEmployeeRecord << "," << (int)((double)fineDue + (double)fineRate * days * (1 - discount));
            updated = true;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line;
        }
        if (!inFile.eof())
        {
            tempFile << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}

void Manager ::deleteEmployee(const string &filename, const string &username)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile)
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    bool updated = false;

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int EmployeeRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> EmployeeRecord >> comma >> fineDue;

        // Print the values to check if they are read correctly
        // cout << "Username: " << uname << ", Password: " << password << ", ID: " << id
        //<< ", EmployeeRecord: " << EmployeeRecord << ", FineDue: " << fineDue << endl;
        if (uname == username)
        {
            // Update the line with new information

            updated = true;
            continue;
        }
        else
        {
            // Write the original line to the temporary file
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // If the line was updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    else
    {
        remove("temp.txt"); // Delete the temporary file if no update was made
    }
}
void Manager ::SearchEmployee(const string &filename, const string &username)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return; // Error condition or default value
    }
    int flag = 0;
    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string uname, password, id;
        int EmployeeRecord, fineDue;
        char comma;

        // Read each field separated by commas
        getline(ss, uname, ',');
        getline(ss, password, ',');
        getline(ss, id, ',');
        ss >> EmployeeRecord >> comma >> fineDue;
        if (uname == username)
        {
            cout << "username: " << username << endl;
            cout << "Rating value: " << EmployeeRecord << endl;
            cout << "fine Due: " << fineDue << endl;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "User doesn't exist \n";
    inFile.close();
    return;
}
int getCarCondition(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return -1; // Error condition or default value
    }

    string line;
    int condition = -1; // Default condition value

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNumFromFile, towhom;
        int conditionFromFile, cost, available, days;

        getline(ss, model, ',');
        getline(ss, regNumFromFile, ',');

        char comma;
        ss >> conditionFromFile >> comma >> cost >> comma >> available >> comma;

        getline(ss, towhom, ',');
        ss >> days;

        if (model_entering == model)
        {
            condition = conditionFromFile; // Found the car, set the condition
            break;                         // No need to search further
        }
    }

    inFile.close();
    return condition; // Return the condition of the car
}
int getCarAvailability(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return -1; // Error condition or default value
    }

    string line;
    int availability = 1; // Default condition value

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNumFromFile, towhom;
        int conditionFromFile, cost, available, days;

        getline(ss, model, ',');
        getline(ss, regNumFromFile, ',');

        char comma;
        ss >> conditionFromFile >> comma >> cost >> comma >> available >> comma;

        getline(ss, towhom, ',');
        ss >> days;

        if (model_entering == model)
        {
            availability = available; // Found the car, set the condition
            break;                    // No need to search further
        }
    }

    inFile.close();
    return availability; // Return the condition of the car
}
string getCarOwner(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return "\n"; // Error condition or default value
    }

    string line;
    string owner; // Default condition value

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNumFromFile, towhom;
        int conditionFromFile, cost, available, days;

        getline(ss, model, ',');
        getline(ss, regNumFromFile, ',');

        char comma;
        ss >> conditionFromFile >> comma >> cost >> comma >> available >> comma;

        getline(ss, towhom, ',');
        ss >> days;

        if (model_entering == model)
        {
            owner = towhom; // Found the car, set the condition
            break;          // No need to search further
        }
    }

    inFile.close();
    return owner; // Return the condition of the car
}
int getCardays(const string &filename, const string &model_entering)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cerr << "Error opening file." << endl;
        return -1; // Error condition or default value
    }

    string line;
    int returndays = 0; // Default return days

    // Read each line from the original file
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string model, regNumFromFile, towhom;
        int conditionFromFile, cost, available, days;

        getline(ss, model, ',');
        getline(ss, regNumFromFile, ',');

        char comma;
        ss >> conditionFromFile >> comma >> cost >> comma >> available >> comma;

        getline(ss, towhom, ',');
        ss >> days;

        if (model == model_entering)
        {
            returndays = days; // Found the car, set the  return days
            break;             // No need to search further
        }
    }

    inFile.close();
    return returndays; // Return the days
}
void addCarToFile(const string &filename, const string &model, const string &regNum, int condition, int rentCost, bool isAvailable, const string &towhom, int days)
{
    ofstream file(filename, ios::app); // Open the file in append mode
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << model << "," << regNum << "," << condition << "," << rentCost << "," << isAvailable << "," << towhom << "," << days;

    file.close();
}
int main()
{
    vector<Car> cars = readCarData();
    vector<Customer> customers = Customer::readCustomerData();
    vector<Employee> employees = Employee::reademployeeData();
    id = customers.size() + 1;
    id_employee = employees.size() + 1;
    while (1)
    {
        cout << "Enter 1 for customer, 2 for employee, and 3 for manager and any other number for ending ";
        int verification;
        if (!(cin >> verification))
        {
            cout << "Invalid input. Please enter an integer.\n";

            // Clear the error state and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Restart the loop
        }
        if (verification != 1 && verification != 2 && verification != 3)
        {
            cout << "Good bye";
            return 0;
        }
        string username;
        if (verification == 1)
        {
            cout << "Are you already registered? (Type YES if already registered or NO) ";
            string answer;
            while (true)
            {

                cin >> answer;
                transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
                if (answer == "YES" || answer == "NO")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type YES or NO.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (answer == "YES")
            {
                cout << "Enter username : ";

                cin >> username;

                vector<Customer> customers = Customer::readCustomerData();

                auto it = find_if(customers.begin(), customers.end(),
                                  [username](const Customer &c)
                                  { return c.getUsername() == username; });

                if (it != customers.end())
                {
                    cout << "Enter password: ";
                    string password;
                    cin >> password;
                    cars = readCarData();

                    if (it->authenticate(password))
                    {
                        cout << "Login successful! Welcome, " << it->getUsername() << "!\n";
                        cout << "Available Cars:\n";
                        for (auto &car : cars)
                        {
                            if (car.checkAvailability())
                                car.displayDetailsIfAvailable();
                        }
                        cout << "Your rented Cars:\n";
                        for (auto &car : cars)
                        {

                            car.displayDetailsofRentedCar(username);
                        }
                        cout << "-------------------\n";
                        cout << "Enter the number of cars you want to return ";
                        int carreturno;
                        while (true)
                        {
                            cin >> carreturno;

                            // Check if input is valid
                            if (cin.fail())
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                            else
                            {
                                // Input is valid, exit the loop
                                break;
                            }
                        }
                        /*Returunung a rented Car*/
                        for (int a = 0; a < carreturno; a++)
                        {
                            cout << "Enter Carname " << endl;
                            string carname;
                            cin >> carname;
                            int prev_condition = getCarCondition("Car.txt", carname);
                            string user;
                            user = getCarOwner("car.txt", carname);
                            if (username != user)
                            {
                                cout << "You have not rented this car \n";
                                continue;
                            }

                            cout << "Condition of returning the car(in stars) " << endl;
                            int condition;

                            while (true)
                            {

                                cin >> condition;
                                // Check if input is valid
                                if (cin.fail())
                                {
                                    cout << "Invalid input. Please enter a valid integer." << endl;
                                    cin.clear();                                         // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                }
                                else
                                {
                                    // Input is valid, exit the loop
                                    break;
                                }
                            }
                            int change = condition - prev_condition;
                            cout << "Duration in number of days after which you are returning the car " << endl;
                            int days;

                            while (true)
                            {

                                cin >> days;
                                // Check if input is valid
                                if (cin.fail())
                                {
                                    cout << "Invalid input. Please enter a valid integer." << endl;
                                    cin.clear();                                         // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                }
                                else
                                {
                                    // Input is valid, exit the loop
                                    break;
                                }
                            }

                            int rdays = getCardays("car.txt", carname);
                            int change_days = max(0, days - rdays);
                            // change required

                            updateCustomerInfo("customer.txt", username, change, change_days);
                            updateCarInfo("car.txt", carname, condition, 1, 0, "None");
                            cout << "Successfully returned" << endl;
                        }

                        /*Asking to rent Car*/
                        vector<Customer> customers = Customer::readCustomerData();
                        int customercheck;
                        for (auto &customer : customers)
                        {
                            if (username == customer.getUsername())
                            {
                                customercheck = customer.getCustomerRecord();
                            }
                        }
                        cars = readCarData();
                        cout << "You can rent "
                             << " " << customercheck << "  no of cars" << endl;
                        cout << "Number of Cars to rent ";
                        int carrent;

                        while (true)
                        {

                            cin >> carrent;
                            // Check if input is valid
                            if (cin.fail())
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                            else
                            {
                                // Input is valid, exit the loop
                                break;
                            }
                        }
                        for (int a = 0; a < carrent; a++)
                        {
                            cout << "Enter CarName ";
                            string carname;
                            cin >> carname;
                            if (!(getCarAvailability("car.txt", carname)))
                            {
                                cout << "Car is not available to get rented" << endl;
                                continue;
                            }
                            int days;
                            cout << "Enter number of days for which you want to rent the car ";

                            while (true)
                            {

                                cin >> days;
                                // Check if input is valid
                                if (cin.fail())
                                {
                                    cout << "Invalid input. Please enter a valid integer." << endl;
                                    cin.clear();                                         // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                }
                                else
                                {
                                    // Input is valid, exit the loop
                                    break;
                                }
                            }

                            int cost = 0;
                            int condition = getCarCondition("Car.txt", carname);
                            cout << "condition : " << condition << endl;
                            updateCarInfo("car.txt", carname, condition, 0, days, username);
                            cout << "Successfully rented" << endl;
                            for (auto &car : cars)
                            {
                                if (carname == car.getModel())
                                {

                                    cost += days * car.getRentCost();
                                }
                            }
                            cout << "Payable Cost is " << cost << endl;
                        }
                        int fine = 0;
                        auto it = find_if(customers.begin(), customers.end(),
                                          [username](const Customer &c)
                                          { return c.getUsername() == username; });

                        // If customer with username is found, return their fine attribute
                        if (it != customers.end())
                        {
                            fine = it->getFineDue();
                        }
                        cout << "Your fine dues: " << fine << endl;
                        cout << "Enter amount by which you want to clear your fine : " << endl;
                        int amount;

                        while (true)
                        {
                            cin >> amount;
                            // Check if input is valid
                            if (cin.fail())
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                            else
                            {
                                // Input is valid, exit the loop
                                break;
                            }
                        }
                        clearfinedue("customer.txt", username, amount);
                        cout << "Successfully updated" << endl;
                    }

                    else
                    {
                        cout << "Incorrect password. Please try again.\n";
                    }
                }
                else
                {
                    cout << "Username not found. Please register.\n";
                }
            }
            else
            {
                Manager manager;
                manager.registerNewCustomer();
            }
        }
        else if (verification == 3)
        {
            Manager manager;
            cout << "Press 1 to see the car database details : ";
            int inp;

            while (true)
            {
                cin >> inp;
                // Check if input is valid
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a valid integer." << endl;
                    cin.clear();                                         // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
                else
                {
                    // Input is valid, exit the loop
                    break;
                }
            }
            if (inp == 1)
                Car::displayDetails();

            string input;
            cout << "Do you want to register new customer[yes/No] " << endl;

            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
                manager.registerNewCustomer();

            cout << "Do you want to update the fields of an existing customer[yes/No] " << endl;

            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "Provide username " << endl;
                string username;
                cin >> username;
                cout << "provide integer value of change in customer record " << endl;
                int crecord;

                while (true)
                {
                    cin >> crecord;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }

                cout << "provide number of days equivalent for which fine is to be imposed on customer " << endl;
                int days;

                while (true)
                {
                    cin >> days;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                updateCustomerInfo("customer.txt", username, crecord, days);
                cout << "Successfully updated" << endl;
            }

            cout << "Do you want to delete a customer[yes/No] " << endl;
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "provide user name ";
                string username;
                cin >> username;
                if (hasUserRentedCar("car.txt", username))
                {
                    cout << "can't delete because user is renting a car." << endl;
                }
                else
                    manager.deleteCustomer("customer.txt", username);
                cout << "Successfully updated" << endl;
            }

            cout << "Do you want to get the info of a specific customer[yes/No] " << endl;
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "provide user name ";
                string username;
                cin >> username;
                manager.SearchEmployee("customer.txt", username);
            }
            cout << "Do you want to register new employee[yes/No] " << endl;
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
                manager.registerNewEmployee();
            cout << "Do you want to update the fields of an existing employee[yes/No] " << endl;
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "Provide username " << endl;
                string username;
                cin >> username;
                cout << "provide integer value of change in employee record " << endl;
                int crecord;

                while (true)
                {
                    cin >> crecord;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                cout << "provide number of days equivalent for which fine is to be imposed on employee " << endl;
                int days;

                while (true)
                {
                    cin >> days;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                updateEmployeeInfo("employee.txt", username, crecord, days);
                cout << "Successfully updated" << endl;
            }
            cout << "Do you want to delete an employee[yes/No] " << endl;
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "provide user name ";
                string username;
                cin >> username;
                if (hasUserRentedCar("car.txt", username))
                {
                    cout << "can't delete because user is renting a car." << endl;
                }
                else
                    manager.deleteEmployee("employee.txt", username);
                cout << "Successfully updated" << endl;
            }
            cout << "Do you want to get the info of a specific employee[yes/No] " << endl;
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "provide user name ";
                string username;
                cin >> username;
                manager.SearchEmployee("employee.txt", username);
            }
            cout << "Do you want to add a car[yes/no]: ";
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "Enter carname : ";
                string model, regNum;
                int rentCost, condition;
                cin >> model;
                cout << "Enter Registration number : ";
                cin >> regNum;
                cout << "Enter car condition in stars : ";

                while (true)
                {
                    cin >> condition;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                cout << "Enter rent cost : ";

                while (true)
                {
                    cin >> rentCost;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                addCarToFile("car.txt", model, regNum, condition, rentCost, 1, "None", 0);
                cout << "Successfully updated" << endl;
            }
            cout << "Do you want to update any car property[yes/no]: ";
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                cout << "Enter carname : ";
                string carname;
                cin >> carname;
                cout << "Enter new condition : ";
                int condition;

                while (true)
                {
                    cin >> condition;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                // cout << "Enter rentcost : ";
                // int rentCost;
                // cin >> rentCost;
                cout << "Enter newAvailability[0/1] : ";
                int available;

                while (true)
                {
                    cin >> available;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                cout << "Number of days for which car is rented : ";
                int days;

                while (true)
                {
                    cin >> days;
                    // Check if input is valid
                    if (cin.fail())
                    {
                        cout << "Invalid input. Please enter a valid integer." << endl;
                        cin.clear();                                         // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                    else
                    {
                        // Input is valid, exit the loop
                        break;
                    }
                }
                cout << "Enter new renter: ";
                string newwhom;
                cin >> newwhom;
                updateCarInfo("car.txt", carname, condition, available, days, newwhom);
                cout << "Successfully updated" << endl;
            }
            cout << "Do you want to delete any car[yes/no]: ";
            while (true)
            {

                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "yes" || input == "no")
                {
                    // Valid input, exit the loop
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type yes or no.\n";
                    // Clear the input buffer to prevent infinite loop
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            if (input == "yes")
            {
                string carname;
                cout << "Enter carname : ";
                cin >> carname;
                manager.DeleteCar("car.txt", carname);
                cout << "Successfully updated" << endl;
                cout << endl;
            }
        }
        else if (verification == 2)
        {
            cout << "Are you already registered? (Type YES if already registered or NO) ";
            string answer;
            cin >> answer;

            if (answer == "YES")
            {
                cout << "Enter username(without spaces): ";

                cin >> username;

                vector<Employee> Employees = Employee::reademployeeData();

                auto it = find_if(Employees.begin(), Employees.end(),
                                  [username](const Employee &c)
                                  { return c.getUsername() == username; });

                if (it != Employees.end())
                {
                    cout << "Enter password: ";
                    string password;
                    cin >> password;
                    cars = readCarData();
                    if (it->authenticate(password))
                    {
                        cout << "Login successful! Welcome, " << it->getUsername() << "!\n";
                        cout << "Available Cars:\n";
                        for (auto &car : cars)
                        {
                            if (car.checkAvailability())
                                car.displayDetailsIfAvailable();
                        }
                        cout << "Your rented Cars:\n";
                        for (auto &car : cars)
                        {

                            car.displayDetailsofRentedCar(username);
                        }
                        cout << "Enter the number of cars you want to return ";
                        int carreturno;

                        while (true)
                        {

                            cin >> carreturno;
                            // Check if input is valid
                            if (cin.fail())
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                            else
                            {
                                // Input is valid, exit the loop
                                break;
                            }
                        }

                        /*Returunung a rented Car*/
                        for (int a = 0; a < carreturno; a++)
                        {
                            cout << " Enter Carname " << endl;
                            string carname;
                            cin >> carname;
                            int prev_condition = getCarCondition("Car.txt", carname);
                            string user;
                            user = getCarOwner("car.txt", carname);
                            if (username != user)
                            {
                                cout << "You have not rented this car \n";
                                continue;
                            }

                            cout << "Condition of returning the car(in stars) " << endl;
                            int condition;

                            while (true)
                            {

                                cin >> condition;
                                // Check if input is valid
                                if (cin.fail())
                                {
                                    cout << "Invalid input. Please enter a valid integer." << endl;
                                    cin.clear();                                         // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                }
                                else
                                {
                                    // Input is valid, exit the loop
                                    break;
                                }
                            }
                            int change = condition - prev_condition;
                            cout << "Duration in number of days after which you are returning the car " << endl;
                            int days;

                            while (true)
                            {

                                cin >> days;
                                // Check if input is valid
                                if (cin.fail())
                                {
                                    cout << "Invalid input. Please enter a valid integer." << endl;
                                    cin.clear();                                         // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                }
                                else
                                {
                                    // Input is valid, exit the loop
                                    break;
                                }
                            }
                            int rdays = getCardays("car.txt", carname);
                            int change_days = max(0, days - rdays);
                            // change required

                            updateEmployeeInfo("Employee.txt", username, change, change_days);
                            updateCarInfo("car.txt", carname, condition, 1, 0, "None");
                            cout << "Successfully returned" << endl;
                        }

                        /*Asking to rent Car*/
                        vector<Employee> Employees = Employee::reademployeeData();
                        int Employeecheck;
                        for (auto &Employee : Employees)
                        {
                            if (username == Employee.getUsername())
                            {
                                Employeecheck = Employee.getemployeeRecord();
                            }
                        }
                        cars = readCarData();
                        cout << "Employee can rent "
                             << " " << Employeecheck << "  no of cars" << endl;
                        cout << "Number of Cars to rent ";
                        int carrent;

                        while (true)
                        {

                            cin >> carrent;
                            // Check if input is valid
                            if (cin.fail())
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                            else
                            {
                                // Input is valid, exit the loop
                                break;
                            }
                        }
                        for (int a = 0; a < carrent; a++)
                        {
                            cout << "Enter CarName ";
                            string carname;
                            cin >> carname;
                            if (!(getCarAvailability("car.txt", carname)))
                            {
                                cout << "Car is not available to get rented" << endl;
                                continue;
                            }
                            int days;
                            cout << "Enter number of days for which you want to rent the car ";

                            while (true)
                            {

                                cin >> days;
                                // Check if input is valid
                                if (cin.fail())
                                {
                                    cout << "Invalid input. Please enter a valid integer." << endl;
                                    cin.clear();                                         // Clear the error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                }
                                else
                                {
                                    // Input is valid, exit the loop
                                    break;
                                }
                            }
                            int cost = 0;
                            int condition = getCarCondition("Car.txt", carname);
                            cout << "condition : " << condition << endl;
                            updateCarInfo("car.txt", carname, condition, 0, days, username);
                            cout << "Successfully rented" << endl;
                            for (auto &car : cars)
                            {
                                if (carname == car.getModel())
                                {

                                    cost += (int)((double)(1 - discount) * days * car.getRentCost());
                                }
                            }
                            cout << "Payable Cost is " << cost << endl;
                        }
                        int fine = 0;
                        auto it = find_if(Employees.begin(), Employees.end(),
                                          [username](const Employee &c)
                                          { return c.getUsername() == username; });

                        if (it != Employees.end())
                        {
                            fine = it->getFineDue();
                        }
                        cout << "Your fine due: " << fine << endl;
                        cout << "Enter amount by which you want to clear your fine : " << endl;
                        int amount;

                        while (true)
                        {

                            cin >> amount;
                            // Check if input is valid
                            if (cin.fail())
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                cin.clear();                                         // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            }
                            else
                            {
                                // Input is valid, exit the loop
                                break;
                            }
                        }
                        clearfinedue("Employee.txt", username, amount);
                        cout << "Successfully updated" << endl;
                    }

                    else
                    {
                        cout << "Incorrect password. Please try again.\n";
                    }
                }
                else
                {
                    cout << "Username not found. Please register.\n";
                }
            }
            else
            {
                Manager manager;
                manager.registerNewEmployee();
            }
        }
    }

    return 0;
}
