#include "DatabaseManager.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void initSchema(DatabaseManager& db) {
    std::ifstream file("db/schema.sql");
    if (!file.is_open()) return;
    std::stringstream buffer;
    buffer << file.rdbuf();
    db.executeQuery(buffer.str());
}

int main() {
    DatabaseManager db("users.db");
    if (!db.connect()) return 1;
    
    initSchema(db); // Initialize database layout tables
    UserManager userApp(db);

    int choice;
    std::string user, pass, email;

    std::cout << "1. Register User\n2. Login\n3. List Users\nChoose option: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Username: "; std::cin >> user;
        std::cout << "Password: "; std::cin >> pass;
        std::cout << "Email: "; std::cin >> email;
        if (userApp.registerUser(user, pass, email)) {
            std::cout << "Registration successful!\n";
        }
    } else if (choice == 2) {
        std::cout << "Username: "; std::cin >> user;
        std::cout << "Password: "; std::cin >> pass;
        if (userApp.authenticateUser(user, pass)) {
            std::cout << "Access Granted!\n";
        } else {
            std::cout << "Invalid credentials.\n";
        }
    } else if (choice == 3) {
        userApp.listUsers();
    }

    db.disconnect();
    return 0;
}
