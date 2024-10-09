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
        cout << "Enter your old username: ";
        cin >> username;
        cout << "Enter your old password: ";
        cin >> passwordd;

        string newUsername;
        string newPassword;

        cout << "Enter your new username: ";
        cin >> newUsername; 

        cout << "Enter your new password: ";
        cin >> newPassword;

        try {
            // Use a prepared statement to update the username
            sql::PreparedStatement* pstmt = globalConnection->prepareStatement(
                "UPDATE userInfo SET username = ?, password = ? WHERE username = ? AND password = ?");
           
            // Bind the new username and password
            pstmt->setString(1, newUsername);  // New username
            pstmt->setString(2, newPassword);  // New password

            // Bind the old username and password to identify the user
            pstmt->setString(3, username);     // Old username
            pstmt->setString(4, passwordd);    // Old password

            // Execute the update
            int rowsAffected = pstmt->executeUpdate();

            if (rowsAffected > 0) {
                std::cout << "Username '" << username << "' was successfully replaced with '" << newUsername << "'." << std::endl;
                std::cout << "Password '" << passwordd << "' was successfully replaced with '" << newPassword << "'." << std::endl;

            }
            else {
                std::cout << "Username '" << username << "' was not found." << std::endl;
            }

            // Clean up
            delete pstmt; // Avoid memory leaks
        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
        }
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
    string stock_action;
    string stock_id;
    string stock_symbol;
    string stock_name;
    int price;
    string user_id;
    string transaction_date;

    stock() {}

    void addStockInfo() {
        
        cout << "Enter the stock_id:";
        cin >> stock_id;
        cout << "Enter the stock_symbol:";
        cin >> stock_symbol;
        cout << "Enter the stock_name:";
        cin >> stock_name;
        cout << "Enter the price:";
        cin >> price;

        try {
            // Use a prepared statement for safer SQL execution
            sql::PreparedStatement* pstmt = globalConnection->prepareStatement("INSERT INTO stocksInfo (stock_id, stock_symbol, stock_name, price) VALUES (?, ?, ?, ?)");
            // Bind the fullname parameter
            pstmt->setString(1, stock_id); // Bind stock_id 
            pstmt->setString(2, stock_symbol); // Bind stock_symbol 
            pstmt->setString(3, stock_name); // Bind stock_name  
            pstmt->setInt(4, price); // Bind stock_price             

            // Execute the statement
            pstmt->executeUpdate();

            // Clean up
            delete pstmt; // Important to avoid memory leaks
        }
        catch (sql::SQLException& e) {
            cerr << "SQL error: " << e.what() << endl; // Error handling
        }

    }
    void sellStock() {
        cout << "Enter the user_id: ";
        cin >> user_id;
        cout << "Enter the stock_id: ";
        cin >> stock_id;
        cout << "Enter the stock_action: Enter 'Sold' or 'Bought'  ";
        cin >> stock_action;
        cout << "Enter the date of transaction in this format: ??/??/???? ";
        cin >> transaction_date;
            try {
                // Use a prepared statement for safer SQL execution
                sql::PreparedStatement* pstmt = globalConnection->prepareStatement("INSERT INTO transactionHistory (user_id, stock_id, stock_action, transaction_date) VALUES (?, ?, ?, ?)");
                // Bind the fullname parameter

                pstmt->setString(1, user_id); // Bind user_id 
                pstmt->setString(2, stock_id); // Bind stock_id 
                pstmt->setString(3, stock_action); // Bind stock_action 
                pstmt->setString(4, transaction_date); // Bind transaction_date 
                // Execute the statement
                pstmt->executeUpdate();

                // Clean up
                delete pstmt; // Important to avoid memory leaks
            }
            catch (sql::SQLException& e) {
                cerr << "SQL error: " << e.what() << endl; // Error handling
            }
    }
    void buyStock() {
        cout << "Enter the user_id: ";
        cin >> user_id;
        cout << "Enter the stock_id: ";
        cin >> stock_id;
        cout << "Enter the stock_action: Enter 'Sold' or 'Bought' ";
        cin >> stock_action;
        cout << "Enter the date of transaction in this format: ??/??/???? ";
        cin >> transaction_date;
        
        try {
            // Use a prepared statement for safer SQL execution
            sql::PreparedStatement* pstmt = globalConnection->prepareStatement("INSERT INTO transactionHistory (user_id, stock_id, stock_action, transaction_date) VALUES (?, ?, ?, ?)");
            // Bind the fullname parameter

            pstmt->setString(1, user_id); // Bind user_id 
            pstmt->setString(2, stock_id); // Bind stock_id 
            pstmt->setString(3, stock_action); // Bind stock_action 
            pstmt->setString(4, transaction_date); // Bind transaction_date 

            // Execute the statement
            pstmt->executeUpdate();

            // Clean up
            delete pstmt; // Important to avoid memory leaks
        }
        catch (sql::SQLException& e) {
            cerr << "SQL error: " << e.what() << endl; // Error handling
        }
    }

};

class transactions {
public:
   
   string transaction_date;
    
    transactions() {}

    void getTransaction() {
       // cout << "Enter the user_id: ";
       // cin >> user_id;
       // cout << "Enter the stock_id: ";
       // cin >> stock_id;
        //cout << "Enter the stock_action: ";
       // cin >> stock_action;
        cout << "Enter the transaction_date: ";
        cin >> transaction_date;

        try {
            // Use a prepared statement for safer SQL execution
            sql::PreparedStatement* pstmt = globalConnection->prepareStatement(
                "SELECT user_id, stock_id, stock_action, transaction_date FROM transactionHistory WHERE transaction_date = ?");

            pstmt->setString(1, transaction_date); // Bind transaction_date to the first placeholder

            // Execute the query and get the result set
            sql::ResultSet* res = pstmt->executeQuery();

            // Iterate over the result set and process the data
            while (res->next()) {
                std::string user_id = res->getString("user_id");
                std::string stock_id = res->getString("stock_id");
                std::string stock_action = res->getString("stock_action");
                std::string transaction_date = res->getString("transaction_date");

                ofstream file_;
                file_.open("TradingInterfaceTransactionInfo.txt");
                file_ << "Hi, here is the transaction information for the selected stock: " << endl;

                file_ << "User_id: " << endl;
                file_ << user_id << endl;

                file_ << "The stock_id is: " << endl;
                file_ << stock_id << endl;

                file_ << "The stock_action is: " << endl;
                file_ << stock_action << endl;

                file_ << "The transaction_date is: " << endl;
                file_ << transaction_date << endl;
                file_.close();
                cin.ignore();
            }

            // Clean up
            delete res;    // Clean up the result set to avoid memory leaks
            delete pstmt;  // Clean up the prepared statement to avoid memory leaks
        }
        catch (sql::SQLException& e) {
            cerr << "SQL error: " << e.what() << endl; // Error handling
        }

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
        "stock_id VARCHAR(50) NOT NULL, "
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
        "stock_id  VARCHAR(50) NOT NULL, "
        "stock_action  VARCHAR(50) NOT NULL, "
        "transaction_date VARCHAR(50) NOT NULL) ";

    // Execute the query
    stmt = globalConnection->createStatement();
    stmt->execute(createTableQuery3);
    stmt->close();
    cout << "Table 'transactionHistory' created successfully." << endl;

   //std::string query = "DROP TABLE stocksInfo;";
   //stmt = globalConnection->createStatement();
   //stmt->execute(query);
   //stmt->close();


    string fullname;
    string username;
    string passwordd;

    bool continuee = true;

   // cout << "Enter your fullname" << endl;
   // getline(std::cin, fullname);
    //cout << "Enter a username" << endl;
   // getline(std::cin, username);
   // cout << "Enter a password" << endl;
   // getline(std::cin, passwordd);
   // userinfo userinfo(fullname, username, passwordd);
    stock stockInstance;
    transactions transactionInstance;

  //  userinfo.addToDataBase();
    
    while (continuee == true) {
        cout << "Enter a number 1 - 4: " << endl;
        cout << "1. Create a new account" << endl;
        cout << "2. Buy a stock" << endl;
        cout << "3. Sell a stock" << endl;
        cout << "4. Add stock information" << endl;
        cout << "5. Get account information" << endl;
        cout << "6. Get transaction History" << endl;
        cout << "7. Change Log In Info" << endl;
        cout << "8. Exit" << endl;
        int value;
        cin >> value;
        switch (value) {
        case 1: {
            getline(std::cin, fullname);
            cout << "Enter your fullname" << endl;
            getline(std::cin, fullname); 

            cout << "Enter a username" << endl;
            getline(std::cin, username);

            cout << "Enter a password" << endl;
            getline(std::cin, passwordd);
            userinfo userinfo(fullname, username, passwordd); 
            userinfo.addToDataBase();
            break;
        }
        case 2: {
            stock stockInstance;
            stockInstance.buyStock();
            break;
        }
        case 3: {
            stock stockInstance;
            stockInstance.sellStock();
            break;
        }
        case 4: {
            stock stockInstance;
            stockInstance.addStockInfo();
            break;
        }
        case 5: {
            userinfo userinfo(fullname, username, passwordd);
            userinfo.getAccountInfo();
            break;
        }
        case 6: {
            transactions transactionInstance;
            transactionInstance.getTransaction();
            break;
        }
        case 7: {
            userinfo userinfo(fullname, username, passwordd);
            userinfo.changeLoginInfo();
            break;
        }
        case 8: {
            continuee = false;
            break;

        }
        }
    }
    return 0;
}