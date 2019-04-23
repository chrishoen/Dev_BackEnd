cmake_minimum_required (VERSION 3.8)

project (BackEnd CXX)
my_find_src_files (src_files BackEnd)
add_executable (BackEnd ${src_files})
my_add_compile_options (BackEnd)
my_add_pch (BackEnd)

my_inc_import_RisLib(BackEnd)
my_lib_import_RisLib(BackEnd)

