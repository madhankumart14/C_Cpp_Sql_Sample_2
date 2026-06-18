#pragma once
#include "DatabaseManager.hpp"
#include <string>

class UserManager {
private:
    DatabaseManager& dbMgr;
    std::string hashPassword(const std::string& password); // Simple SHA-256 placeholder

public:
    UserManager(DatabaseManager& mgr);
    bool registerUser(const std::string& username, const std::string& password, const std::string& email, const std::string& role = "user");
    bool authenticateUser(const std::string& username, const std::string& password);
    void listUsers();
    bool deleteUser(const std::string& username);
};
