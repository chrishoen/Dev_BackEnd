cmake_minimum_required (VERSION 3.8)

project (BackEnd3 CXX)
my_find_src_files (src_files BackEnd3)
add_executable (BackEnd3 ${src_files})
my_add_compile_options (BackEnd3)
my_add_pch (BackEnd3)

my_inc_import_RisLib(BackEnd3)
my_lib_import_RisLib(BackEnd3)

