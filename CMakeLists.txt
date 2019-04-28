cmake_minimum_required (VERSION 3.8)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_BackEnd")
my_init_global_import_variables()

add_subdirectory ("BackEnd2")
return()

add_subdirectory ("BackEndDLL")
add_subdirectory ("FrontEnd")
add_subdirectory ("Test")

return()


