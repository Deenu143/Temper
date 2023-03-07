cmake_minimum_required(VERSION 3.18.1)

project(app-integrity-checker)

# Find OpenSSL library
find_package(OpenSSL REQUIRED)

# Add app_integrity_checker.cpp as a source file
add_library(app-integrity-checker SHARED app_integrity_checker.cpp)

# Link OpenSSL libraries
target_link_libraries(app-integrity-checker OpenSSL::Crypto OpenSSL::SSL)

# Link log library
find_library(log-lib log)
target_link_libraries(app-integrity-checker ${log-lib})
