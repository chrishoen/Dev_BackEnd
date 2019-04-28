cmake_minimum_required (VERSION 3.8)

project (Json CXX)
my_find_src_files (src_files Json)
add_executable (Json ${src_files})
my_add_compile_options (Json)
my_add_pch (Json)

my_inc_import_RisLib(Json)
my_lib_import_RisLib(Json)

return()


find_package(RisLib CONFIG REQUIRED PATHS ${MyRisLibConfigPath} NO_DEFAULT_PATH)
target_include_directories(Json PRIVATE RisLib)
target_link_libraries(Json RisLib)

