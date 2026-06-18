#include "UserManager.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

UserManager::UserManager(DatabaseManager& mgr) : dbMgr(mgr) {}

// Basic mock hashing function for demonstration 
std::string UserManager::hashPassword(const std::string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.MakePath();
}

bool UserManager::registerUser(const std::string& username, const std::string& password, const std::string& email, const std::string& role) {
    std::string hashed = hashPassword(password);
    std::string query = "INSERT INTO users (username, password_hash, email, role) VALUES ('" 
                        + username + "', '" + hashed + "', '" + email + "', '" + role + "');";
    return dbMgr.executeQuery(query);
}

bool UserManager::authenticateUser(const std::string& username, const std::string& password) {
    std::string hashed = hashPassword(password);
    std::string query = "SELECT COUNT(*) FROM users WHERE username='" + username + "' AND password_hash='" + hashed + "';";
    
    sqlite3_stmt* stmt;
    bool success = false;
    
    if (sqlite3_prepare_v2(dbMgr.getDBInstance(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            if (sqlite3_column_int(stmt, 0) > 0) {
                success = true;
            }
        }
    }
    sqlite3_finalize(stmt);
    return success;
}

void UserManager::listUsers() {
    std::string query = "SELECT id, username, email, role FROM users;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(dbMgr.getDBInstance(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n--- SYSTEM USERS ---\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::cout << "ID: " << sqlite3_column_int(stmt, 0)
                      << " | User: " << sqlite3_column_text(stmt, 1)
                      << " | Email: " << sqlite3_column_text(stmt, 2)
                      << " | Role: " << sqlite3_column_text(stmt, 3) << "\n";
        }
        std::cout << "--------------------\n";
    }
    sqlite3_finalize(stmt);
}

bool UserManager::deleteUser(const std::string& username) {
    std::string query = "DELETE FROM users WHERE username='" + username + "';";
    return dbMgr.executeQuery(query);
}
