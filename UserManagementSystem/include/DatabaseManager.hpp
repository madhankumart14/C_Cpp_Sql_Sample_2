#pragma once
#include <sqlite3.h>
#include <string>

class DatabaseManager {
private:
    sqlite3* db;
    std::string dbPath;

public:
    DatabaseManager(const std::string& path);
    ~DatabaseManager();
    bool connect();
    void disconnect();
    bool executeQuery(const std::string& query);
    sqlite3* getDBInstance() const;
};
