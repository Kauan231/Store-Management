#pragma once 
#include <iostream>
#include <stdlib.h>
#include "../Model/Model.hpp"

#include <thread>
#include <chrono>

namespace View {
	void OptionsDealer();
	void OptionsManager();
	void Modify();
	void ModifyEmployees();
	void AddEmployee();
	void ShowEmployees();
	void DeleteEmployee();
	void SearchEmployeeLog();

	void AddProduct();
	void DeleteProduct();
	void Sell();
	void ShowProducts();
	void Refill();

	static void Login() {
		system("cls");

		std::cout << "Store Management system" << std::endl;
		std::cout << " Username: " << std::endl;
		std::cout << " >> ";
		std::string username;
		std::cin >> username;

		system("cls");

		std::cout << " Username: " << username << std::endl;
		std::cout << " Password: " << std::endl;
		std::cout << " >> ";
		std::string password;
		std::cin >> password;

		try {
			Model::Employee CurrentEmployee = Model::Login(username, password);

			system("cls");
			std::cout << "Welcome " << CurrentEmployee.Username << " !";
			this_thread::sleep_for(chrono::seconds(1));

			if (Model::CurrentEmployee->Role == "Dealer") {
				OptionsDealer();
			}
			if (Model::CurrentEmployee->Role == "Manager") {
				OptionsManager();
			}
		}
		catch (const std::invalid_argument& e) {
			system("cls");
			std::cerr << e.what();
			this_thread::sleep_for(chrono::seconds(1));
			Login();
		}
	}

	static void Start() {
		system("cls");

		std::cout << "Store Management system" << std::endl;
		std::cout << " Select your role: " << std::endl;
		std::cout << "\t (0) Dealer \n\t (1) Manager  \n" << std::endl;
		std::cout << " >> ";

		switch (std::cin.get()) {
		case '0':
			OptionsDealer();
			break;
		case '1':
			OptionsManager();
			break;
		default:
			break;
		}
	}

	void OptionsDealer() {
		system("cls");

		std::cout << "Choose a Option:" << std::endl;
		std::cout << "\t (0) Sell \n\t (1) Search Storage \n\t (2) Modify Itens \n\t (3) Exit" << std::endl;
		std::cout << " >> ";

		std::cin.ignore();
		switch (std::cin.get()) {
		case '0':
			Sell();
			break;
		case '1':
			ShowProducts();
			break;
		case '2':
			Modify();
			break;
		case '3':
			std::cin.ignore();
			Login();
			break;
		default:
			break;
		}
	}

	void Modify() {
		system("cls");

		std::cout << "Choose a Option:" << std::endl;
		std::cout << "\t (0) Refill Item \n\t (1) Add new Item \n\t (2) Remove Item" << std::endl;
		std::cout << " >> ";

		std::cin.ignore();
		switch (std::cin.get()) {
		case '0':
			Refill();
			break;
		case '1':
			AddProduct();
			break;
		case '2':
			DeleteProduct();
			break;
		default:
			Modify();
			break;
		}
	}

	void OptionsManager() {
		system("cls");

		std::cout << "Choose a Option:" << std::endl;
		std::cout << "\t (0) Show Employees \n\t (1) Search Employee Logs \n\t (2) Modify Employees  \n\t (3) Exit" << std::endl;
		std::cout << " >> ";

		switch (std::cin.get())
		{
		case '0':
			ShowEmployees();
			break;
		case '1':
			SearchEmployeeLog();
			break;
		case '2':
			ModifyEmployees();
			break;
		case '3':
			std::cin.ignore();
			Login();
			break;
		default:
			OptionsManager();
			break;
		}
	}

	void ModifyEmployees() {
		system("cls");

		std::cout << "Choose a Option:" << std::endl;
		std::cout << "\t (0) Add Employee \n\t (1) Remove Employee \n\t (2) Return" << std::endl;
		std::cout << " >> ";

		std::cin.ignore();
		switch (std::cin.get()) {
		case '0':
			AddEmployee();
			break;
		case '1':
			DeleteEmployee();
			break;
		case '2':
			OptionsManager();
			break;
		default:
			OptionsManager();
			break;
		}
	}

	static void SelectFromSearchEmployees(vector<Model::Employee> QueriedEmployees) {
		int option = 0;
		for (auto it = begin(QueriedEmployees); it != end(QueriedEmployees); it++) {
			cout << "(" << option << ") Name: " << it->Username << " | Role: " << it->Role << endl;
			option++;
		}

		std::cout << "Select the employee:" << std::endl;
		std::cout << " >> ";

		int index;
		std::cin >> index;
		Model::Employee SelectedEmployee = QueriedEmployees.at(index);
		std::string SelectedEmployeeID = SelectedEmployee.getID();

		Model::SelectEmployeeLog(SelectedEmployeeID);
	}

	void SearchEmployeeLog() {
		system("cls");

		std::cout << "Employee Name: " << std::endl;
		std::cout << " >> ";
		std::string EmployeeName;
		std::cin.ignore();
		std::getline(std::cin, EmployeeName);

		SelectFromSearchEmployees(Model::SearchEmployeeLog(EmployeeName));

		std::cout << "Press (0) to return" << std::endl;
		std::cout << " >> ";
		std::cin.ignore();
		if (std::cin.get() == '0') {
			OptionsManager();
		}
	}

	void AddEmployee() {
		system("cls");

		std::cout << "Employee Name: " << std::endl;
		std::cout << " >> ";
		std::string EmployeeName;
		std::cin.ignore();
		std::getline(std::cin, EmployeeName);

		std::cout << "Select Role: " << std::endl;
		std::cout << "\t (0) Dealer \n\t (1) Manager " << std::endl;
		std::cout << " >> ";
		std::string EmployeeRole;
		std::cin >> EmployeeRole;

		if (EmployeeRole == "0") {
			EmployeeRole = "Dealer";
		}
		else if (EmployeeRole == "1") {
			EmployeeRole = "Manager";
		}
		else {
			EmployeeRole = "None";
		}

		Model::Employee employee_to_add = Model::Employee(EmployeeName, EmployeeRole);
		Model::AddEmployee(employee_to_add);

		cout << "Employee Registered" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		OptionsManager();
	}

	static void DeleteFromSearchEmployees(vector<Model::Employee> QueriedEmployees) {
		int option = 0;
		for (auto it = begin(QueriedEmployees); it != end(QueriedEmployees); it++) {
			cout << "(" << option << ") Name: " << it->Username << " | Role: " << it->Role << endl;
			option++;
		}

		std::cout << "Select the employee:" << std::endl;
		std::cout << " >> ";

		int index;
		std::cin >> index;
		Model::Employee SelectedEmployee = QueriedEmployees.at(index);
		std::string SelectedEmployeeID = SelectedEmployee.getID();

		Model::DeleteEmployee(SelectedEmployeeID);
	}

	void DeleteEmployee() {
		system("cls");

		std::cout << "Employee Name: " << std::endl;
		std::cout << " >> ";
		std::string EmployeeName;
		std::cin.ignore();
		std::getline(std::cin, EmployeeName);

		DeleteFromSearchEmployees(Model::SearchEmployeeToRemove(EmployeeName));

		cout << "Employee Removed" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		OptionsManager();
	}

	void ShowEmployees() {
		system("cls");
		Model::ShowEmployees();

		std::cout << "Press (0) to return" << std::endl;
		std::cout << " >> ";
		std::cin.ignore();
		if (std::cin.get() == '0') {
			OptionsManager();
		}
	}

	void AddProduct() {
		vector<Model::Product> Products_To_add;

		while (true) {
			system("cls");

			std::cout << "Product Name: " << std::endl;
			std::cout << " >> ";
			std::string ProductName;
			std::cin.ignore();
			std::cin >> ProductName;

			std::cout << "Select Amount: " << std::endl;
			std::cout << " >> ";
			int Amount;
			std::cin.ignore();
			std::cin >> Amount;

			Products_To_add.push_back(Model::Product(ProductName, Amount));

			std::cout << "Add More ?" << std::endl;
			std::cout << "\t (0) No \n\t (1) Yes " << std::endl;
			std::cout << " >> ";
			int Option;
			std::cin.ignore();
			std::cin >> Option;

			if (Option == 0) {
				break;
			}
		}

		for (Model::Product i : Products_To_add) {
			Model::AddProduct(i);
			Model::Log("Added: ", i);
		}

		cout << "Products Registered" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		OptionsDealer();
	}

	void ShowProducts() {
		system("cls");
		Model::ShowProducts();

		std::cout << "Press (0) to return" << std::endl;
		std::cout << " >> ";
		std::cin.ignore();
		if (std::cin.get() == '0') {
			OptionsDealer();
		}
	}

	void DeleteProduct() {
		system("cls");

		std::cout << "Product Name: " << std::endl;
		std::cout << " >> ";
		std::string ProductName;
		std::cin.ignore();
		std::cin >> ProductName;

		Model::DeleteProduct(ProductName);

		cout << "Product Removed" << endl;
		this_thread::sleep_for(chrono::seconds(1));
		Model::Log("Removed: ", Model::Product(ProductName, 0));
		OptionsDealer();
	}

	void Sell() {
		std::map<std::string, std::string> Products_To_Sell;

		while (true) {
			system("cls");

			std::cout << "Products in Cart: " << std::endl;
			for (std::pair<std::string, std::string> i : Products_To_Sell) {
				std::cout << i.first << setw(5) << i.second << std::endl;
			}

			std::cout << "Product Name: " << std::endl;
			std::cout << " >> ";
			std::string ProductName;
			std::cin.ignore();
			std::cin >> ProductName;

			std::cout << "Amount: " << std::endl;
			std::cout << " >> ";
			std::string Amount;
			std::cin.ignore();
			std::cin >> Amount;

			Products_To_Sell.insert(std::make_pair(ProductName, Amount));

			std::cout << "Add More ?" << std::endl;
			std::cout << "\t (0) No \n\t (1) Yes " << std::endl;
			std::cout << " >> ";
			int Option;
			std::cin.ignore();
			std::cin >> Option;

			if (Option == 0) {
				break;
			}
		}

		for (std::pair<std::string, std::string> i : Products_To_Sell) {
			Model::Sell(i.first, i.second);
			Model::Log("Sold: ", Model::Product(i.first, stoi(i.second)));
		}

		cout << "Products Sold" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		OptionsDealer();
	}

	void Refill() {
		system("cls");
		std::cout << "Product Name: " << std::endl;
		std::cout << " >> ";
		std::string ProductName;
		std::cin.ignore();
		std::cin >> ProductName;

		std::cout << "Amount: " << std::endl;
		std::cout << " >> ";
		std::string Amount;
		std::cin.ignore();
		std::cin >> Amount;
		Model::Refill(ProductName, Amount);
		Model::Log("Refilled: ", Model::Product(ProductName, stoi(Amount)));
		cout << "Products Refilled" << endl;
		this_thread::sleep_for(chrono::seconds(1));

		OptionsDealer();
	}

}

