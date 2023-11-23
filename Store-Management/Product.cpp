#pragma once
#include "./Model/Product.hpp"
#include <iostream>
#include <cassert>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

namespace Model {
	Product::Product(std::string name, int Amount)
	{
		this->name = name;
		this->amount = Amount;

		boost::uuids::random_generator generator; 
		boost::uuids::uuid uuid1 = generator();
		const std::string tmp = boost::uuids::to_string(uuid1);

		const char* value = tmp.c_str();
		Uuid = value;
	}
	std::string Product::getID() const {
		return Uuid;
	}
}
