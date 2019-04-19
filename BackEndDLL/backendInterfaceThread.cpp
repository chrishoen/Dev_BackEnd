/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#define  _BACKENDINTERFACETHREAD_CPP_
#include "backendInterfaceThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

InterfaceThread::InterfaceThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Timer");
   BaseClass::setThreadPrintLevel(TS::PrintLevel(3, 3));
   BaseClass::mTimerPeriod = 1000;

   // Initialize qcalls.
   mSetTimerCallbackQCall.bind(this, &InterfaceThread::executeSetTimerCallback);

   // Members
   mTPFlag = true;
   mTimerCallbackFlag = false;
}

InterfaceThread::~InterfaceThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It starts the child thread.

void InterfaceThread::threadInitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It shuts down the child thread.

void  InterfaceThread::threadExitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// QCall registered to the mTcpMsgThread child thread. It is invoked when
// a session is established or disestablished (when a client connects or
// disconnects). It maintains session state variables.

// Set the timer calllback. This is bound to the qcall.
void InterfaceThread::executeSetTimerCallback(TimerCallback_T aCallback)
{     
   if (aCallback)
   {
      mTimerCallback = aCallback;
      mTimerCallbackFlag = true;
   }
   else
   {
      mTimerCallback = aCallback;
      mTimerCallbackFlag = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer. It
// sends an echo request message.

void InterfaceThread::executeOnTimer(int aTimerCount)
{
   if (!mTPFlag) return;

   Prn::print(Prn::View21, "TIMER %5d", aTimerCount);

   // If the timer callback is valid then call it.
   if (mTimerCallback)
   {
      mTimerCallback(aTimerCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
