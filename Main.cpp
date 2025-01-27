/*
Welcome to NeuralDB
*/

#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;  // Pointer to SQLite database
    int exit;     // Status code

    // Open or create the SQLite database
    exit = sqlite3_open("example.db", &db);
    if (exit) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }
    std::cout << "Connected to SQLite database successfully!" << std::endl;

    // Execute a simple SQL query
    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT);";
    char* errorMessage = nullptr; // Pointer to hold error messages
    exit = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);

    if (exit != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage); // Free the error message memory
    } else {
        std::cout << "Table created successfully!" << std::endl;
    }

    // Close the SQLite database connection
    sqlite3_close(db);
    std::cout << "Database connection closed." << std::endl;

    return 0;
}
