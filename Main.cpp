/*
Welcome to NeuralDB
*/

#include <iostream>
#include <sqlite3.h>
#include <string>

void executeSQL(sqlite3* db, const char* sql) {
    char* errorMessage = nullptr;
    int exit = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

void add_user(sqlite3* db){
    std::string userName;
    std::cout << "Enter a name to insert into the database: ";
    std::getline(std::cin, userName);

    // Convert std::string to const char* using .c_str()
    std::string insertSQL = "INSERT INTO users (name) VALUES ('" + userName + "');";
    executeSQL(db, insertSQL.c_str());
    std::cout << "Inserted user: " << userName << " into the database." << std::endl;
}

int main() {
    sqlite3* db;  // SQLite database pointer
    int exit;     // Status code

    // Open or create the SQLite database
    exit = sqlite3_open("example.db", &db);
    if (exit) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }
    std::cout << "Connected to SQLite database successfully!" << std::endl;

    // Create the 'users' table if it doesn't exist
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT);";
    executeSQL(db, createTableSQL);

    // Start of user input:

    add_user(db);

    // End of user input

    // Query the 'users' table and display results
    const char* selectSQL = "SELECT * FROM users;";
    sqlite3_stmt* stmt; // SQLite statement object
    exit = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        std::cerr << "Error preparing SELECT statement: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "\nID | Name" << std::endl;
        std::cout << "------------" << std::endl;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0); // Get the first column (id)
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); // Get the second column (name)
            std::cout << id << " | " << name << std::endl;
        }
    }
    sqlite3_finalize(stmt); // Finalize the prepared statement

    // Close the SQLite database connection
    sqlite3_close(db);
    std::cout << "Database connection closed." << std::endl;

    return 0;
}

/* To compile, use:
gcc -c src/sqlite3.c -o sqlite3.o

g++ Main.cpp sqlite3.o -o output/app.exe -I. -std=c++17

./output/app.exe
in directory folder
*/