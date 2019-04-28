cmake_minimum_required (VERSION 3.8)

project (BackEnd2 CXX)
my_find_src_files (src_files BackEnd2)
add_executable (BackEnd2 ${src_files})
my_add_compile_options (BackEnd2)
my_add_pch (BackEnd2)

my_inc_import_RisLib(BackEnd2)
my_lib_import_RisLib(BackEnd2)

