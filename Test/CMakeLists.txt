﻿cmake_minimum_required (VERSION 3.8)

project (Test CXX)
my_find_src_files (src_files Test)
add_executable (Test ${src_files})
my_add_compile_options (Test)
my_add_pch (Test)

my_inc_import_RisLib(Test)
my_lib_import_RisLib(Test)

my_inc_import_BackEndLib(Test)
my_lib_import_BackEndLib(Test)
return()


find_package(RisLib CONFIG REQUIRED PATHS ${MyRisLibConfigPath} NO_DEFAULT_PATH)
target_include_directories(Test PRIVATE RisLib)
target_link_libraries(Test RisLib)

