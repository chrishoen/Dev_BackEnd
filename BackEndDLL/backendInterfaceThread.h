#pragma once

/*==============================================================================
Prototype tcp server thread message thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <functional>

#include "risThreadsQCallThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an example backend interface thread.
// 
// It inherits from BaseQCallThread to obtain a call queue based thread
// functionality.

class InterfaceThread : public Ris::Threads::BaseQCallThread
{
public:
   typedef Ris::Threads::BaseQCallThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Timer flag.
   bool mTPFlag;

   // Timer callback.
   bool mTimerCallbackFlag;
   typedef std::function<void(int)> TimerCallback_T;
   TimerCallback_T mTimerCallback;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   InterfaceThread();
   ~InterfaceThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads:

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running. It starts the child thread.
   void threadInitFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated. It shuts down the child thread.
   void threadExitFunction() override;

   // Execute periodically. This is called by the base class timer. It
   // sends an echo request message.
   void executeOnTimer(int aTimerCount) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Set timer callback.

   // qcall to set the timer callback.
   Ris::Threads::QCall1<TimerCallback_T> mSetTimerCallbackQCall;

   // Set the timer calllback. This is bound to the qcall.
   void executeSetTimerCallback(TimerCallback_T aCallback);

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _BACKENDINTERFACETHREAD_CPP_
         InterfaceThread* gInterfaceThread;
#else
extern   InterfaceThread* gInterfaceThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

