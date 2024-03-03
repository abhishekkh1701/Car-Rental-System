Introduction:
This program implements a basic car rental system where customers, employees, and managers can perform various tasks related to renting cars, managing customer and employee data, and managing the fleet of available cars. Users interact with the system through a console-based interface.

Key Features:

User Authentication:
Customers and employees can log in using their usernames and passwords. New users can register.
The system verifies user credentials before granting access to the functionalities.

Customer Functions:
Customers can view available cars, rent cars, return rented cars, clear fines.
Customers can rent multiple cars for a specified duration.

Employee Functions:
Employees have similar functionalities as customers but with additional privileges like discount of 15% on fine and rented cost.
Employees can rent cars, return rented cars, clear fines, and update their information.

Manager Functions:
Managers have administrative privileges to manage customers, employees, and the fleet of cars.
Managers can register new customers and employees, update customer and employee information, delete customers and employees, view car database details, add new cars, update car properties, and delete cars.

Data Persistence:
User, car, customer, and employee data are stored in external text files (car.txt, customer.txt, employee.txt) to maintain persistence between program executions.

Error Handling:
The program provides error messages and handles invalid inputs gracefully.
Users are prompted with clear instructions throughout the interaction.
Usage:

Compilation:
Compile the program using a C++ compiler, such as g++: g++ car_rental_system.cpp -o car_rental_system
Execution:
Run the compiled executable: ./car_rental_system
Follow the prompts on the console to navigate through different functionalities.
Enter '4' to exit the program.

File Structure:

car_rental_system.cpp: Contains the main code implementing the car rental system.
car.txt: Stores information about cars.
information in a row contains these things in the sequential manner
car modelid,car reg. number ,condition of the car in stars ,rented cost ,availability status ,present renter , booked number of days
customer.txt: Stores information about registered customers.
employee.txt: Stores information about registered employees.
In both customer and employee databases, information are stored in the following sequential manner in a row
username(unique for each user) ,password,an id(which may be same for multiple users),user rating, fine due


Assumptions and Limitations:


This car rental system is a basic implementation and may lack certain advanced features found in commercial systems.
It assumes a single-user environment and does not handle concurrent access or data integrity issues.
The program relies on text files for data storage, which may not scale well for large datasets.

Further Assumptions - 
The unique attribute of each user is their user name, not their id.
The unique attribute of each car is its modelid/ (it is written by name "carname" in the program), not their reg. number.
There is only one manager as there is no difference in the system with 1 manager or with multiple managers - as essentially the working in both the cases are same so there is no database for managers.
the customer/employee pays the amount of rent(not including fine) of a particular car whenever he/she returns the corresponding car. So, clear dues function is for fine only.
The customer and employee will honestly tell the number of days for which they have rented the car and the condition in which they are returning while returning a car. Based on the change in condition of car, the customer/employee rating will be updated.
The customer will never pay the extra fine as that will make the fine attribute negative - a negative fine attribute woul essentially mean that he has paid more fine so in future, he needs to pay less.

Future Enhancements:

Implement a graphical user interface (GUI) for a more user-friendly experience.
Add support for multiple locations and branches.
Incorporate a database management system for better data handling and scalability.
Enhance security measures such as encryption for sensitive user information.
Contributors:

This program was developed by Abhishek Khandelwal  as part of CS253 course assignment.
