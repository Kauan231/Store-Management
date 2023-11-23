#pragma once
#include "Employee.hpp"
#include "Product.hpp"
#include "../View/View.hpp"

#include <iomanip>
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include <thread>
#include <chrono>
#include <stdexcept>

using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "";

std::string random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

namespace Model {
    sql::Connection* Connect_To_DB();
    Employee* CurrentEmployee;

    static void Log(std::string Action, Product product_to_log) {
        sql::PreparedStatement* pstmt;
        sql::Connection* connection = Connect_To_DB();

        pstmt = connection->prepareStatement("INSERT INTO log(idUser,Action,Amount) VALUES(?,?,?)");
        pstmt->setString(1, CurrentEmployee->getID());
        pstmt->setString(2, Action + " " + product_to_log.name);
        pstmt->setInt(3, product_to_log.amount);
        pstmt->execute();

        delete pstmt;
        delete connection;
    }

    static void ShowEmployeeLog(std::string UUID) {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;
        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery("SELECT * FROM log INNER JOIN employees ON idEmployee = idUser WHERE idUser = '" + UUID + "'");

        while (res->next()) {
            cout << res->getString("Action") << " | " << res->getInt("Amount") << " | " << res->getString("Time") << endl;
        }

        delete stmt;
        delete res;
        delete connection;
    }

    static void SelectEmployeeLog(std::string UUID) {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;
        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery("SELECT * FROM log WHERE idUser = '" + UUID + "' ");

        while (res->next()) {
            cout << res->getString("Action") << " | " << res->getInt("Amount") << " | " << res->getString("Time") << endl;
        }

        delete stmt;
        delete res;
        delete connection;
    }

    static vector<Employee> SearchEmployeeLog(std::string employee_name) {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;
        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery("SELECT * FROM employees WHERE nameEmployee LIKE'%" + employee_name + "%'");

        vector<Employee> QueriedEmployees;

        while (res->next()) {
            QueriedEmployees.push_back(Employee(res->getString("idEmployee").c_str(), res->getString("nameEmployee").c_str(), res->getString("roleEmployee").c_str()));
        }

        delete stmt;
        delete res;
        delete connection;

        return QueriedEmployees;
    }

    static vector<Employee> SearchEmployeeToRemove(std::string employee_name) {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;
        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery("SELECT * FROM employees WHERE nameEmployee LIKE'%" + employee_name + "%'");

        vector<Employee> QueriedEmployees;

        while (res->next()) {
            QueriedEmployees.push_back(Employee(res->getString("idEmployee").c_str(), res->getString("nameEmployee").c_str(), res->getString("roleEmployee").c_str()));
        }

        delete stmt;
        delete res;
        delete connection;

        return QueriedEmployees;
    }

    void AddLoginData(std::string UUID, std::string Username) {
        std::string UserLogin = Username.substr(0, Username.find(' ')) + random_string(4);
        std::string UserPass  = random_string(6);

        sql::PreparedStatement* pstmt;
        sql::Connection* connection = Connect_To_DB();

        pstmt = connection->prepareStatement("INSERT INTO login(idUser,username,password) VALUES(?,?,?)");
        pstmt->setString(1, UUID);
        pstmt->setString(2, UserLogin);
        pstmt->setString(3, UserPass);
        pstmt->execute();

        delete pstmt;
        delete connection;

        std::cout << "User Login: " << UserLogin << " | " << "User Pass: " << UserPass << std::endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

	static void AddEmployee(Employee &employee_to_add) {
        sql::PreparedStatement* pstmt;
        sql::Connection* connection = Connect_To_DB();

        pstmt = connection->prepareStatement("INSERT INTO employees(idEmployee,nameEmployee,roleEmployee) VALUES(?,?,?)");
        pstmt->setString(1, employee_to_add.getID());
        pstmt->setString(2, employee_to_add.Username);
        pstmt->setString(3, employee_to_add.Role);
        pstmt->execute();

        delete pstmt;
        delete connection;

        AddLoginData(employee_to_add.getID(), employee_to_add.Username);
	}

    static void ShowEmployees(){
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;
        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery("SELECT * FROM employees");

        string LongestWord;
        std::map<std::string, std::string> Employees;

        while (res->next()) {
            string StringSQL = res->getString("nameEmployee").c_str();

            if (StringSQL.length() > LongestWord.length()) {
                LongestWord = StringSQL;
            }

            Employees.insert(std::make_pair(StringSQL, res->getString("roleEmployee")));
        }

        cout << "NAME" << std::setw(LongestWord.length() - 4 + 5) << "|" << std::setw(8) << "ROLE" << endl;
        for (std::pair<std::string, std::string> i : Employees) {
            cout << i.first << std::setw(LongestWord.length() - i.first.length() + 5) << "|" << std::setw(8) << i.second << endl;
        }

        delete stmt;
        delete res;
        delete connection;
    }

    static void DeleteEmployee(std::string id) {
        sql::PreparedStatement* pstmt;
        sql::Connection* connection = Connect_To_DB();

        string query = "DELETE FROM employees WHERE idEmployee='" + id + "' ";

;       pstmt = connection->prepareStatement(query);
        pstmt->execute();

        query = "DELETE FROM login WHERE idUser='" + id + "' ";

        pstmt = connection->prepareStatement(query);
        pstmt->execute();

        delete pstmt;
        delete connection;
    }

    sql::Connection* Connect_To_DB() {
        sql::Driver* driver;
        sql::Connection* con;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        con->setSchema("store");

        return con;
	}

    static void AddProduct(Product product_to_add) {
        sql::PreparedStatement* pstmt;
        sql::Connection* connection = Connect_To_DB();

        pstmt = connection->prepareStatement("INSERT INTO products(idProduct,nameProduct,amountProduct) VALUES(?,?,?)");
        pstmt->setString(1, product_to_add.getID());
        pstmt->setString(2, product_to_add.name);
        pstmt->setInt(3, product_to_add.amount);
        pstmt->execute();

        delete pstmt;
        delete connection;
    }

    static void DeleteProduct(std::string Name) {
        sql::PreparedStatement* pstmt;
        sql::Connection* connection = Connect_To_DB();

        string query = "DELETE FROM products WHERE nameProduct= '" + Name + "' ";

        pstmt = connection->prepareStatement(query);
        pstmt->execute();
        
        delete pstmt;
        delete connection;
    }

    static void ShowProducts() {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;
        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery("SELECT * FROM products");

        string LongestWord;
        std::map<std::string, int> Products;

        while (res->next()) {
            string StringSQL = res->getString("nameProduct").c_str();

            if (StringSQL.length() > LongestWord.length()) {
                LongestWord = StringSQL;
            }

            Products.insert(std::make_pair(StringSQL, res->getInt("amountProduct")));
        }

        cout << "NAME" << std::setw(LongestWord.length() - 4 + 5) << "|" << std::setw(7) << "AMOUNT" << endl;
        for (std::pair<std::string, int> i : Products) {
            cout << i.first << std::setw(LongestWord.length() - i.first.length() + 5) << "|" << std::setw(5) << i.second << endl;
        }

        delete stmt;
        delete res;
        delete connection;
    }

    static void Sell(std::string Name, std::string amount) {
        sql::Connection* connection = Connect_To_DB();
        sql::PreparedStatement* pstmt;

        string query = "UPDATE products SET amountProduct = (amountProduct-"+ amount + ") WHERE nameProduct='" + Name + "'";

        pstmt = connection->prepareStatement(query);
        pstmt->execute();

        delete pstmt;
        delete connection;
    }

    static void Refill(std::string Name, std::string amount) {
        sql::Connection* connection = Connect_To_DB();
        sql::PreparedStatement* pstmt;

        string query = "UPDATE products SET amountProduct = (amountProduct+" + amount + ") WHERE nameProduct='" + Name + "'";

        pstmt = connection->prepareStatement(query);
        pstmt->execute();

        delete pstmt;
        delete connection;
    }

    static void GetEmployeeData(std::string UUID) {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;

        string query = "SELECT * FROM employees WHERE idEmployee='" + UUID + "'";

        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery(query);

        if (res->next()) {
            Employee* EmployeeQuery = new Employee(res->getString("idEmployee").c_str(), res->getString("nameEmployee").c_str(), res->getString("roleEmployee").c_str());    
            CurrentEmployee = EmployeeQuery;
        }
        else {
            cout << "FAILED" << endl;
        }

        delete stmt;
        delete res;
        delete connection;
    }

    static Employee Login(std::string Username, std::string Password) {
        sql::Connection* connection = Connect_To_DB();
        sql::Statement* stmt;

        string query = "SELECT * FROM login WHERE username='" + Username + "' AND password='" + Password + "'";

        sql::ResultSet* res;

        stmt = connection->createStatement();
        res = stmt->executeQuery(query);

        if (res->next()) {
            string StringSQL = res->getString("idUser").c_str();
           
            GetEmployeeData(res->getString("idUser").c_str());

            return *CurrentEmployee;
        }
        else {
            throw std::invalid_argument("Wrong username or password");
        }

        delete stmt;
        delete res;
        delete connection;
    }

    static void Start() {
        sql::Connection* connection = Connect_To_DB();
        sql::PreparedStatement* pstmt;

        pstmt = connection->prepareStatement("INSERT IGNORE INTO employees(idEmployee, nameEmployee, roleEmployee) VALUES(?,?,?)");
        pstmt->setString(1, "1");
        pstmt->setString(2, "manager");
        pstmt->setString(3, "Manager");
        pstmt->execute();

        pstmt = connection->prepareStatement("INSERT IGNORE INTO login(idUser, username, password) VALUES(?,?,?)");
        pstmt->setString(1, "1");
        pstmt->setString(2, "manager");
        pstmt->setString(3, "manager");
        pstmt->execute();

        delete pstmt;
        delete connection;
    }
}