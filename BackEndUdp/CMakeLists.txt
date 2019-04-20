cmake_minimum_required (VERSION 3.8)

project (BackEndUdp CXX)
my_find_src_files (src_files BackEndUdp)
add_executable (BackEndUdp ${src_files})
my_add_compile_options (BackEndUdp)
my_add_pch (BackEndUdp)

my_inc_import_RisLib(BackEndUdp)
my_lib_import_RisLib(BackEndUdp)

