19. Trading Application

The trading application is a console application that will provide different trading operations such as, getting account info, depositing money, buying stocks, selling stocks, checking transactions, etc, which a person doing trade requires. This application will use a DBMS such as MySQL to store data.

Technologies: C++ programming languages, File I/O, MYSQL, and OOPs.

Here are the steps to set up the project:
1.)The first step is making sure that the database is set up already in your workbench.
2.) Go to https://dev.mysql.com/downloads/connector/net/ 
3.) After downloading the connector, set up the project in Visual Studio with all the additional files in this repository.
4.) Once the project is created and all the necessary files are added, right-click on the project in the solution explorer and then click properties.
5.) Add this directory path (C:\Program Files\MySQL\MySQL Connector C++ 9.0\include\jdbc; or whatever your local path is to the jdbc directory) to C/C++ additional include directories to be able to use the mysql headers.
6.) In Linker, under general, additional libraries directories, add (C:\Program Files\MySQL\MySQL Connector C++ 9.0\lib64\vs14, or whatever the path to your vs14 is, and then under, )
7.) Add STATIC_CONCPP; to the beginning of the preprocessor definitions under c/c++ preprocessor
8.) And then under input, under additional dependencies, add mysqlcppconn-static.lib or try
9.) You may also try using mysqlcppconn.lib instead of mysqlcppconn-static.lib
Make sure that the configuration is set to release when you open the properties tab of your project and make sure that the configuration is also set to release on the Visual Studio ribbon on the top of the page
10.)The code should run as long as all the MySQL dependencies are added to the 
