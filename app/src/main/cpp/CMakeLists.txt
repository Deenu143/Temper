cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             app-integrity-checker

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/jni/app_integrity_checker.cpp )

target_link_libraries( # Specifies the target library.
                       app-integrity-checker

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
