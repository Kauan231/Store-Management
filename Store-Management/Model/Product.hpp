#pragma once
#include <string>
#include <vector>

namespace Model {
	class Product {
	private:
		std::string Uuid;
	public:
		std::string name;
		int amount;
		Product(std::string name, int amount);
		std::string getID() const;
	};
}
