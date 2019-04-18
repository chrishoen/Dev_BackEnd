cmake_minimum_required (VERSION 3.8)

project (BackEndLib CXX)

my_find_src_files (src_files BackEndLib)
my_find_inc_files (inc_files)
add_library (BackEndLib STATIC ${src_files})
my_add_compile_options (BackEndLib)
my_add_pch (BackEndLib)

target_include_directories(BackEndLib INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(BackEndLib)
my_lib_import_RisLib(BackEndLib)


if (MSVC)
   install(TARGETS BackEndLib DESTINATION "C:\\MyTools\\MyLib\\node")
   install(FILES backendExports.h DESTINATION "C:\\MyTools\\MyLib\\node")
else()
   install(FILES "/var/tmp/Dev_BackEnd/build/BackEndLib/libBackEndLib.so" DESTINATION "/opt/mylib")
   install(FILES backendExports.h DESTINATION "/usr/local/lib")
endif()
