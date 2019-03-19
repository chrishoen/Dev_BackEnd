cmake_minimum_required (VERSION 3.8)

include(MyCMake.cmake)
include(MyImports.cmake)

project ("Dev_BackEnd")
my_init_variables()
my_init_import_variables()


add_subdirectory ("BackEndDLL")
add_subdirectory ("Test")
return()


