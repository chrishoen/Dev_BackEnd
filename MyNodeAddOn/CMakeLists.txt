cmake_minimum_required (VERSION 3.8)

project (MyNodeAddOn CXX)

my_find_src_files (src_files MyNodeAddOn)
my_find_inc_files (inc_files)
add_library (MyNodeAddOn SHARED ${src_files})
my_add_compile_options (MyNodeAddOn)
my_add_pch (MyNodeAddOn)

target_include_directories(MyNodeAddOn INTERFACE ${PROJECT_SOURCE_DIR})

my_inc_import_Node(MyNodeAddOn)
my_lib_import_Node(MyNodeAddOn)


