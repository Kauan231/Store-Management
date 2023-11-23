#pragma once
#include "Model/Employee.hpp"
#include <iostream>
#include <cassert>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

namespace Model {
	Employee::Employee(std::string name, std::string role)
	{
		Username = name;
		Role = role;

		boost::uuids::random_generator generator;
		boost::uuids::uuid uuid1 = generator();
		const std::string tmp = boost::uuids::to_string(uuid1);

		const char* value = tmp.c_str();
		Uuid = value;
	}
	Employee::Employee(std::string UUID, std::string username, std::string role) {
		Uuid = UUID;
		Username = username;
		Role = role;
	}
	std::string Employee::getID() const {
		return Uuid;
	}

}
