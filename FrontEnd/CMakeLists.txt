cmake_minimum_required (VERSION 3.8)

project (FrontEnd CXX)
my_find_src_files (src_files FrontEnd)
add_executable (FrontEnd ${src_files})
my_add_compile_options (FrontEnd)
my_add_pch (FrontEnd)

my_inc_import_RisLib(FrontEnd)
my_inc_import_BackEndDLL(FrontEnd)

my_lib_import_BackEndDLL(FrontEnd)
my_lib_import_RisLib(FrontEnd)


