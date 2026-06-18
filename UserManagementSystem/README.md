UserManagementSystem/
├── CMakeLists.txt              # Build configuration
├── README.md                   # Repository documentation
├── db/
│   └── schema.sql              # Database initialization script
├── include/
│   ├── DatabaseManager.hpp     # Database connection wrapper
│   └── UserManager.hpp         # User business logic definitions
└── src/
    ├── DatabaseManager.cpp     # Database implementation (SQLite3)
    ├── UserManager.cpp         # User operations implementation
    └── main.cpp                # Application entry point
