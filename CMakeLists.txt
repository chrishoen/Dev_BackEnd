cmake_minimum_required (VERSION 3.8)

include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)

project ("Dev_BackEnd")
my_init_global_import_variables()

add_subdirectory ("MyNodeAddOn")
return()

add_subdirectory ("BackEndDLL")
add_subdirectory ("Test")
return()


