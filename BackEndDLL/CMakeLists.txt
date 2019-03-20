cmake_minimum_required (VERSION 3.8)

project (BackEndDLL CXX)

my_find_src_files (src_files BackEndDLL)
my_find_inc_files (inc_files)
add_library (BackEndDLL SHARED ${src_files})
my_add_compile_options (BackEndDLL)
my_add_pch (BackEndDLL)

target_include_directories(BackEndDLL INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_RisLib(BackEndDLL)
my_lib_import_RisLib(BackEndDLL)


if (MSVC)
   install(TARGETS BackEndDLL DESTINATION "C:\\aaa_cprint\\mono")
else()
   install(FILES "/var/tmp/Dev_BackEnd/build/BackEndDLL/libBackEndDLL.so" DESTINATION "/opt/mono")
endif()
