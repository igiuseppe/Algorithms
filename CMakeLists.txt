cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(src main.cpp CharVal.hpp Col.hpp Data.hpp Database.hpp Date.hpp DateVal.hpp Empty.hpp FloatVal.hpp Functions.hpp IntVal.hpp Tab.hpp TextVal.hpp Time.hpp TimeVal.hpp AutoVal.hpp GenericException.hpp GrammarException.hpp Abort.hpp)