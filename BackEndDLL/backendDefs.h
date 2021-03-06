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
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace BackEnd
{
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Status record. this contains variables that reflect the backend status.

typedef struct
{
   // Sensor status. True if okay.
   bool    mCameraStatus;
   bool    mRemoteStatus;
} StatusRecord;

void initialize(StatusRecord* aRecord);

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace 

#ifdef __cplusplus
}
#endif

