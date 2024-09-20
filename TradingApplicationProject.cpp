#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
using namespace sql;

sql::Connection* globalConnection = nullptr;

void initializeConnection() {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    globalConnection = driver->connect("tcp://127.0.0.1:3306", "root", "Scroller_034");
    globalConnection->setSchema("Parks_and_Recreation");
}

class userinfo {
public:
    string fullname;
    string username;
    string passwordd;

    userinfo(string Fullname, string Username, string Password) : fullname(Fullname), username(Username), passwordd(Password) {}

    void addToDataBase() {
        try {
            // Use a prepared statement for safer SQL execution
            sql::PreparedStatement* pstmt = globalConnection->prepareStatement("INSERT INTO userInfo (fullname, username, password) VALUES (?, ?, ?)");
            // Bind the fullname parameter
            pstmt->setString(1, fullname); // Bind fullname 
            pstmt->setString(2, username); // Bind username 
            pstmt->setString(3, passwordd); // Bind password            
            // Execute the statement
            pstmt->executeUpdate();

            // Clean up
            delete pstmt; // Important to avoid memory leaks
        }
        catch (sql::SQLException& e) {
            cerr << "SQL error: " << e.what() << endl; // Error handling
        }
    
    }

    void changeLoginInfo() {
        cout << "Enter the fullname: ";
        cin >> fullname;
        cout << "Enter the username: ";
        cin >> username;
        cout << "Enter the password: ";
        cin >> passwordd;
    }

    void getAccountInfo() {
        ofstream file_;
        file_.open("TradingInterface.txt");
        file_ << "Hi " << fullname << ". Here is your log in Info: " << endl;
        file_ << username << endl;
        file_ << passwordd << endl;
        file_.close();
        cin.ignore();
    }
};

class stock {
public:
    int stock_id;
    string stock_symbol;
    string stock_name;
    int stock_price;

    stock() {}

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

class transactions {
public:
    string date;
    string user_id;
    int amount;

    transactions() {}

    void getTransaction() {
        cout << "Enter the user_id: ";
        cin >> user_id;
        cout << "Enter the date: ";
        cin >> date;
        cout << "Enter the amount: ";
        cin >> amount;
    }
};

int main() {
    initializeConnection();

    // SQL query to create the userInfo table
    string createTableQuery =
        "CREATE TABLE IF NOT EXISTS userInfo ("
        "fullname VARCHAR(50) NOT NULL, "
        "username VARCHAR(50) NOT NULL, "
        "password VARCHAR(50) NOT NULL, "
        "account_balance DECIMAL(10, 2) DEFAULT 0.00)";

    // Execute the query
    sql::Statement* stmt = globalConnection->createStatement();
    stmt->execute(createTableQuery);
    stmt->close();
    cout << "Table 'userInfo' created successfully." << endl;

    // SQL query to create the stocksInfo table
    string createTableQuery2 =
        "CREATE TABLE IF NOT EXISTS stocksInfo ("
        "stock_id DECIMAL(10, 2) DEFAULT 0.00, "
        "stock_symbol VARCHAR(50) NOT NULL, "
        "stock_name VARCHAR(50) NOT NULL, "
        "price DECIMAL(10, 2) DEFAULT 0.00)";

    // Execute the query
    stmt = globalConnection->createStatement();
    stmt->execute(createTableQuery2);
    stmt->close();
    cout << "Table 'stocksInfo' created successfully." << endl;

    string createTableQuery3 =
        "CREATE TABLE IF NOT EXISTS transactionHistory ("
        "user_id VARCHAR(50) NOT NULL, "
        "date VARCHAR(50) NOT NULL, "
        "amount DECIMAL(10, 2) DEFAULT 0.00)";

    // Execute the query
    stmt = globalConnection->createStatement();
    stmt->execute(createTableQuery3);
    stmt->close();
    cout << "Table 'transactionHistory' created successfully." << endl;

    string fullname;
    string username;
    string passwordd;
    bool continuee = true;

    cout << "Enter your fullname" << endl;
    getline(std::cin, fullname);
    cout << "Enter a username" << endl;
    getline(std::cin, username);
    cout << "Enter a password" << endl;
    getline(std::cin, passwordd);

    userinfo userinfo(fullname, username, passwordd);
    cout << "Enter a number 1 - 4: " << endl;
    cout << "1. Buy a stock" << endl;
    cout << "2. Sell a stock" << endl;
    cout << "3. Get stock information" << endl;
    cout << "4. Get account information" << endl;
    cout << "5. Get transaction History" << endl;
    cout << "6. Change Log In Info" << endl;
    cout << "7. Exit" << endl;
    int value;
    cin >> value;
    while (continuee == true) {
        switch (value) {
        case 1:
            // Implement buy stock logic
            break;
        case 2:
            // Implement sell stock logic
            break;
        case 3: {
            stock stock1;
            stock1.getStockInfo();
            break;
        }
        case 4:
            userinfo.addToDataBase();
            userinfo.getAccountInfo();
            break;
        case 5: {
            transactions transactionInstance;
            transactionInstance.getTransaction();
            break;
        }
        case 6: {
            userinfo.changeLoginInfo();
            break;
        }
        case 7: {
            continuee = false;
            break;
        }
        }
        break;
    }
    return 0;
}