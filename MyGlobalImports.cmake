#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_init_global_import_variables)

   if(MSVC)
      set (MyRisLibIncludePath "C:\\MyTools\\MyLib\\include\\RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "C:\\MyTools\\MyLib\\lib\\RisLib.lib" PARENT_SCOPE)
      set (MyDspLibIncludePath "C:\\MyTools\\MyLib\\include\\DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "C:\\MyTools\\MyLib\\lib\\DspLib.lib" PARENT_SCOPE)
      set (MyCPrintLibIncludePath "C:\\MyTools\\MyLib\\include\\CPrintLib" PARENT_SCOPE)
      set (MyCPrintLibImportPath  "C:\\MyTools\\MyLib\\lib\\CPrintLib.lib" PARENT_SCOPE)
      set (MyEigenIncludePath  "C:\\MyTools\\Eigen" PARENT_SCOPE)
      set (MyOpenCVIncludePath "C:\\MyTools\\opencv\\build\\include" PARENT_SCOPE)
      set (MyOpenCVImportPath  "C:\\MyTools\\opencv\\build\\x64\\vc15\\lib\\opencv_world401.lib" PARENT_SCOPE)
      set (MySDL2IncludePath   "C:\\MyTools\\SDL2\\include" PARENT_SCOPE)
      set (MySDL2ImportPath        "C:\\MyTools\\SDL2\\lib\\SDL2.lib" PARENT_SCOPE)
      set (MySDL2mainImportPath    "C:\\MyTools\\SDL2\\lib\\SDL2main.lib" PARENT_SCOPE)
      set (MySDL2_imageImportPath  "C:\\MyTools\\SDL2\\lib\\SDL2_image.lib" PARENT_SCOPE)
     #set (MyNodeIncludePath "C:\\MyTools\\Node\\sdk\\src" PARENT_SCOPE)
     #set (MyNodeImportPath  "C:\\MyTools\\Node\\sdk\\Release\\node.lib" PARENT_SCOPE)
      set (MyNodeIncludePath "C:\\MyTools\\node_10_2\\include" PARENT_SCOPE)
      set (MyNodeImportPath  "C:\\MyTools\\node_10_2\\node.lib" PARENT_SCOPE)
      set (MyBackEndLibIncludePath "C:\\MyTools\\MyLib\\node" PARENT_SCOPE)
      set (MyBackEndLibImportPath  "C:\\MyTools\\MyLib\\node\\BackEndLib.lib" PARENT_SCOPE)
   else()
      set (MyRisLibIncludePath "/usr/local/include/RisLib" PARENT_SCOPE)
      set (MyRisLibImportPath  "/usr/local/lib/libRisLib.so" PARENT_SCOPE)
      set (MyDspLibIncludePath "/usr/local/include/DspLib" PARENT_SCOPE)
      set (MyDspLibImportPath  "/usr/local/lib/libDspLib.a" PARENT_SCOPE)
      set (MyCPrintLibIncludePath "/usr/local/include/CPrintLib" PARENT_SCOPE)
      set (MyCPrintLibImportPath  "/usr/local/lib/libCPrintLib.a" PARENT_SCOPE)
      set (MyEigenIncludePath "/usr/include/eigen3" PARENT_SCOPE)
      set (MyOpenCVIncludePath "/usr/local/include/opencv4" PARENT_SCOPE)
      set (MySDL2IncludePath   "/usr/local/include/SDL2" PARENT_SCOPE)
      set (MyGPIOIncludePath "/usr/local/include" PARENT_SCOPE)
      set (MyGPIOImportPath  "/usr/local/lib/libwiringPi.so" PARENT_SCOPE)
      set (MyNodeIncludePath "/usr/local/include/node" PARENT_SCOPE)
      set (MyNodeImportPath  "/usr/local/lib/libnode.a" PARENT_SCOPE)
   endif()
endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_RisLib _target)

   if (MSVC)
      add_library(RisLib STATIC IMPORTED)
   else()
      add_library(RisLib SHARED IMPORTED)
   endif()

   set_target_properties(RisLib PROPERTIES IMPORTED_LOCATION ${MyRisLibImportPath})

   if (MSVC)
      target_link_libraries(RisLib INTERFACE ws2_32)
      target_link_libraries(RisLib INTERFACE winmm)
   else()
      set(THREADS_PREFER_PTHREAD_FLAG ON)
      find_package(Threads REQUIRED)
      target_link_libraries(RisLib INTERFACE Threads::Threads)
   endif()

   target_link_libraries(${_target} RisLib)

endfunction()

function(my_inc_import_RisLib _target)

   target_include_directories(${_target} PUBLIC ${MyRisLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_DspLib _target)

   add_library(DspLib STATIC IMPORTED)
   set_target_properties(DspLib PROPERTIES IMPORTED_LOCATION ${MyDspLibImportPath})

   target_link_libraries(${_target} DspLib)

endfunction()

function(my_inc_import_DspLib _target)

   target_include_directories(${_target} PUBLIC ${MyDspLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_CPrintLib _target)

   add_library(CPrintLib STATIC IMPORTED)
   set_target_properties(CPrintLib PROPERTIES IMPORTED_LOCATION ${MyCPrintLibImportPath})

   target_link_libraries(${_target} CPrintLib)

endfunction()

function(my_inc_import_CPrintLib _target)

   target_include_directories(${_target} PUBLIC ${MyCPrintLibIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_OpenCV _target)

   if(MSVC)
      add_library(OpenCV STATIC IMPORTED)
      set_target_properties(OpenCV PROPERTIES IMPORTED_LOCATION ${MyOpenCVImportPath})
      target_link_libraries(${_target} OpenCV)
   else()
      find_package(OpenCV CONFIG REQUIRED)
      target_link_libraries(${_target} ${OpenCV_LIBRARIES})
   endif()

endfunction()

function(my_inc_import_OpenCV _target)

   target_include_directories(${_target} PUBLIC ${MyOpenCVIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_SDL2 _target)

   if(MSVC)
      add_library(SDL2 STATIC IMPORTED)
      add_library(SDL2main STATIC IMPORTED)
      add_library(SDL2_image STATIC IMPORTED)
      set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${MySDL2ImportPath})
      set_target_properties(SDL2main PROPERTIES IMPORTED_LOCATION ${MySDL2mainImportPath})
      set_target_properties(SDL2_image PROPERTIES IMPORTED_LOCATION ${MySDL2_imageImportPath})

      target_link_libraries(${_target} SDL2)
      target_link_libraries(${_target} SDL2main)
      target_link_libraries(${_target} SDL2_image)
   else()
      find_package(SDL2 CONFIG REQUIRED)
      target_link_libraries(${_target} ${SDL2_LIBRARIES})
   endif()

endfunction()

function(my_inc_import_SDL2 _target)

   target_include_directories(${_target} PUBLIC ${MySDL2IncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_GPIO _target)

   if(MSVC)
   else()
      add_library(wiringPi SHARED IMPORTED)
      set_target_properties(wiringPi PROPERTIES IMPORTED_LOCATION ${MyGPIOImportPath})
      target_link_libraries(${_target} wiringPi)
   endif()

endfunction()

function(my_inc_import_GPIO _target)

   if(MSVC)
   else()
      target_include_directories(${_target} PUBLIC ${MyGPIOIncludePath})
   endif()

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_Node _target)

   add_library(Node STATIC IMPORTED)
   set_target_properties(Node PROPERTIES IMPORTED_LOCATION ${MyNodeImportPath})

   target_link_libraries(${_target} Node)

endfunction()

function(my_inc_import_Node _target)

   target_include_directories(${_target} PUBLIC ${MyNodeIncludePath})

endfunction()

#*******************************************************************************
#*******************************************************************************
#*******************************************************************************

function(my_lib_import_BackEndLib _target)

   add_library(ExtraBackEndLib STATIC IMPORTED)
   set_target_properties(ExtraBackEndLib PROPERTIES IMPORTED_LOCATION ${MyBackEndLibImportPath})

   target_link_libraries(${_target} ExtraBackEndLib)

endfunction()

function(my_inc_import_BackEndLib _target)

   target_include_directories(${_target} PUBLIC ${MyBackEndLibIncludePath})

endfunction()

