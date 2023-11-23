# Store-Management
https://github.com/Kauan231/Store-Management/assets/63317471/68a8cfb9-114c-4c4e-82ae-96905de63780

This project was developed using C++, [Mysql connector](https://dev.mysql.com/doc/dev/connector-cpp/latest/) and Boost Libraries.

The Store Management system is based on the division of responsability of the Manager and the Dealer, each one of then have their own options. 
The Manager can:
- See a list of all employees.
- Add or Remove a Employee:
  - When adding a employee the manager can assign a name and a role to the employee, that can be dealer or manager, after that the system will generate a pair of username and password so that the employee can log into the system.
  - When removing a employee you can type the first name or the full name, and the system will return the query with compatible results. If multiple employees have the same first name you can select by typing the option intended.
- List all Employee actions, such as which product they sold, added, removed or refilled, This information are logged in the database with the datetime of the action.

The Dealer can:
- See a list of all products.
- Add or Remove a product.
- Sell products, when selling products, the products will be added to the cart and when the dealer finishes, all the itens in the cart will be sold and the info will be logged.
- Refill itens.

