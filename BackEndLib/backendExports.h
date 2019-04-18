#pragma once
/*==============================================================================
Export definitions for the backed DLL. 
==============================================================================*/

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

bool  initializeBackEnd();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize  the dll. Finalize resources and terminate threads. This
// must be called before the process termination section force
// terminates any running threads. Return true if successful.

bool  finalizeBackEnd();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the current status.

int  getBackEndStatus();


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set a string.

void  setMyString(char* aString);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set a string.

void  getMyString(char* aString);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the current count.

int   getCount();
void  setCount(int aCount);
void  sleep(int aTicks);


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace 

#ifdef __cplusplus
}
#endif

