#pragma once

/*==============================================================================
Timer thead example
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreadsTimerThread.h"

namespace BackEnd
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class InterfaceThread : public Ris::Threads::BaseTimerThread
{
public:
   typedef Ris::Threads::BaseTimerThread BaseClass;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Members.

   bool mTPFlag;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   InterfaceThread();

   // Base class overloads.
   void threadInitFunction() override;
   void threadExitFunction() override;
   void executeOnTimer(int aTimeCount) override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _BACKENDINTERFACETHREAD_CPP_
          InterfaceThread* gInterfaceThread;
#else
   extern InterfaceThread* gInterfaceThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace