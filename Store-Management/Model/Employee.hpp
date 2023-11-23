#pragma once 
#include <string>
#include <vector>

namespace Model {
	class Employee {
	private:
		std::string Uuid;
	public:
		std::string Username;
		std::string Role;
		Employee(std::string username, std::string role);
		Employee(std::string UUID, std::string username, std::string role);
		std::string getID() const;
	};
}
