
#include "stdafx.h"

#include "MainInit.h"
#include "ProcInit.h"
#include "backendInterfaceThread.h"

#include "backendExports.h"
namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regional variables.

bool mValidFlag = false;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize the dll. Read a settings file, initialize resources, and
// launch threads. This must be called before any other functions in
// the dll can be called. Return true if successful.
// 
// The settings file contains sections of commands that are used to 
// set dll settings variables.
// 
// A filepath for the settings file and a section within the settings
// file are supplied as inputs.
// 
// First this reads the default section of the file and then reads the
// input section. This allows having default settings with overrides
// for some specific variables.

bool DllExport initializeBackEnd()
{
   // If already ininialized then exit.
   if (mValidFlag) return false;

   // Set invalid.
   mValidFlag = false;

   // Initialize resources.
   main_initialize();

   // Initialize threads.
   proc_initialize();

   // Set valid.
   mValidFlag = true;

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize  the dll. Finalize resources and terminate threads. This
// must be called before the process termination section force
// terminates any running threads. Return true if successful.

bool DllExport finalizeBackEnd()
{
   // Guard.
   if (!mValidFlag) return false;

   // Finalize resources.
   proc_finalize();

   // Finalize threads.
   main_finalize();

   // Set invalid.
   mValidFlag = false;

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the current status. This is passed in a status record which
// is filled with the current status. The record must first be
// created by the caller. 

int DllExport getBackEndStatus()
{
   // Guard.
   if (!mValidFlag) return -1;

   return 101;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set a string.

void DllExport setMyString(char* aString)
{
   Prn::print(Prn::View21, "MyString1 %s", aString);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set a string.

void DllExport getMyString(char* aString)
{
   strcpy(aString, "ABCDEFGH");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace