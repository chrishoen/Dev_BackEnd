#pragma once
/*==============================================================================
Export definitions for the backed DLL. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#if defined (_MSC_VER)
#define DllExport   __declspec(dllexport) __stdcall
#else
#define DllExport
#endif
//******************************************************************************
//******************************************************************************
//******************************************************************************
#ifdef __cplusplus
extern "C" {
#endif
  
namespace BackEnd
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize the dll. Read a settings file, initialize resources, and
// launch threads. This must be called before any other functions in
// the dll can be called. Return true if successful.
// 

bool DllExport initializeBackEnd();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize  the dll. Finalize resources and terminate threads. This
// must be called before the process termination section force
// terminates any running threads. Return true if successful.

bool DllExport finalizeBackEnd();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the current status. This is passed in a status record which
// is filled with the current status. The record must first be
// created by the caller. 

int DllExport getBackEndStatus();


}//namespace 

#ifdef __cplusplus
}
#endif

