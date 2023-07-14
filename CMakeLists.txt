cmake_minimum_required(VERSION 3.25)
project(Aplikacja_Linii_kolejowychX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Aplikacja_Linii_kolejowychX main.cpp Definicja_Class.h Metody_Definiji_Class.cpp Defnicja_Class_2.h Metody_Definicji_Class_3.cpp Metoda_Definicji_Class_3.cpp Metods_Definicji_Class_2.cpp Definicja_Class_3.h)
include_directories(/usr/local/mysql-connector-c++/include)
target_link_libraries(Aplikacja_Linii_kolejowychX -L/usr/local/mysql-connector-c++/lib64/)
target_link_libraries(Aplikacja_Linii_kolejowychX libmysqlcppconn.dylib)
