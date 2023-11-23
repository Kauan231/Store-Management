# Store-Management
https://github.com/Kauan231/Store-Management/assets/63317471/60509131-8274-4008-b775-e1752a95ae4c

This project was developed using C++, [Mysql connector](https://dev.mysql.com/doc/dev/connector-cpp/latest/) and [Boost Libraries](https://www.boost.org/).

The Store Management system operates on a structured division of responsibilities between the Manager and the Dealer, each equipped with specific options tailored to their roles.

Manager's Capabilities:

- View a comprehensive list of all employees.
- Add or Remove an Employee:
- During employee addition, the Manager can assign a name and role (either dealer or manager). Subsequently, the system generates a unique username-password pair for the employee's system login.
- When removing an employee, the Manager can search by first name or full name. The system provides query results with compatible matches, and if multiple employees share the same first name, the Manager can select the intended option.
- Access a log of all employee actions, detailing product sales, additions, removals, or refills. This information is logged in the database with timestamps for each action.
- 
Dealer's Capabilities:

- View a comprehensive list of all products.
- Add or Remove a product.
- Sell products: Items selected for sale are added to the cart. Upon completion, all items in the cart are marked as sold, and transaction details are logged.
- Refill items.

The login system employs a username-password pair, checked against the login table. After successful authentication, the system cross-references the user UUID with the employees' table to retrieve the logged employee's name and role. The employee's profile is then stored in a session, allowing the system to present the appropriate Dealer or Manager options. Each subsequent action is logged using the UUID, noting the action type (Sell, Add, Refill, Remove), the amount involved, and the timestamp.

Database Structure:

Tables:

employees: idEmployee (Primary Key), nameEmployee, roleEmployee.

products: idProduct (Primary Key), nameProduct, AmountProduct.

login: idUser (Primary Key), username, password.

log: idUser (Primary Key), Action, Amount, Time.
