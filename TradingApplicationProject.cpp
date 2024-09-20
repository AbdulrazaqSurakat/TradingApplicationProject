#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class userinfo {
public:
    string fullname;
    string username;
    string password;

    userinfo(string Fullname, string Username, string Password): fullname(Fullname), username(Username), password(Password){}
    
    void changeLoginInfo() {
        cout << "Enter the fullname: ";
        cin >> fullname;
        cout << "Enter the username: ";
        cin >> username;
        cout << "Enter the password: ";
        cin >> password;
    }
    void getAccountInfo()
    {
        ofstream file_;
        file_.open("TradingInterface.txt");
        file_ << "Hi " << fullname << ". Here is your log in Info: " << endl;
        file_ << username << endl;
        file_ << password << endl;
        file_.close();
        cin.get();

    }

};
class stock {
public:
    int stock_id;
    string stock_symbol;
    string stock_name;
    int stock_price;
    stock(){}

    void getStockInfo() {
        cout << "Enter the stock_id: ";
        cin >> stock_id;
        cout << "Enter the stock_symbol: ";
        cin >> stock_symbol;
        cout << "Enter the stock_name: ";
        cin >> stock_name;
        cout << "Enter the price: ";
        cin >> stock_price;
    }

};
class  {
public:


};

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con = nullptr;

    // Connection details
    std::string host = "127.0.0.1";
    std::string port = "3306";
    std::string user = "root";
    std::string password = "Scroller_034";
    std::string database = "Parks_and_Recreation";

    try {
        // Get MySQL driver instance and connect to the database
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://" + host + ":" + port, user, password);
        con->setSchema(database);

        // Create a statement object
        sql::Statement* stmt = con->createStatement();

        // SQL query to create the userInfo table
        string createTableQuery =
            "CREATE TABLE IF NOT EXISTS userInfo ("
            "user_name VARCHAR(50) NOT NULL, "
            "password VARCHAR(50) NOT NULL, "
            "account_balance DECIMAL(10, 2) DEFAULT 0.00)";
       
        // Execute the query
        stmt->execute(createTableQuery);
        cout << "Table 'userInfo' created successfully." << endl;

        // SQL query to create the userInfo table
        string createTableQuery2 =
            "CREATE TABLE IF NOT EXISTS stocksInfo ("
            "stock_id DECIMAL(10, 2) DEFAULT 0.00, "
            "stock_symbol VARCHAR(50) NOT NULL, "
            "stock_name VARCHAR(50) NOT NULL, "
            "price DECIMAL(10, 2) DEFAULT 0.00)";
        // Execute the query
        stmt->execute(createTableQuery2);
        cout << "Table 'stocksInfo' created successfully." << endl;

        string createTableQuery3 =
            "CREATE TABLE IF NOT EXISTS transactionHistory ("
            "user_id VARCHAR(50) NOT NULL, "
            "amount VARCHAR(50) NOT NULL, "
            "transaction_id VARCHAR(50) NOT NULL )";
        // Execute the query
        stmt->execute(createTableQuery3);

        cout << "Table 'transactionHistory' created successfully." << endl;
        //string alterTableQuery =
         //   "ALTER TABLE userInfo ADD COLUMN email VARCHAR(100)";

        // Execute the query
       // stmt->execute(alterTableQuery);
        //cout << "Column 'email' added successfully." << endl;

        // Clean up
       // string dropTableQuery = "DROP TABLE IF EXISTS transactionHistory";

        // Execute the query
       // stmt->execute(dropTableQuery);
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }

    // Clean up connection
    if (con != nullptr) {
        delete con;
    }
    string fullname;
    string username;
    string password;

    cout << "Enter the fullname: ";
    cin >> fullname;
    cout << "Enter the username: ";
    cin >> username;
    cout << "Enter the password: ";
    cin >> password;

    userinfo userinfo(fullname, username, password);
    cout << "Enter a number 1 - 4: " << endl;
    cout << "1. Buy a stock" << endl;
    cout << "2. Sell a stock" << endl;
    cout << "3. Get stock information" << endl;
    cout << "4. Get account information" << endl;
    cout << "5. Get transaction History" << endl;
    cout << "6. Change Log In Info" << endl;
    int value;
    cin >> value;

    switch (value) {
    case 1:

        break;
    case 2:

        break;
    case 3: {
        stock stock1;
        stock1.getStockInfo();
        break;
    }
    case 4:
        userinfo.getAccountInfo();

        break;
    case 5:
        userinfo.changeLoginInfo();
        break;
    }
    return 0;
}