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
   mCommand1QCall.bind(this, &InterfaceThread::executeCommand1);

   // Members
   mTPFlag = true;
   mCommand1CountZero = 0;
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
   // Store the callback.
   mTimerCallback = aCallback;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute command1. This is bound to the qcall.

void InterfaceThread::executeCommand1(std::string* aArg0, Command1Callback_T aCallback)
{
   Prn::print(Prn::View21, "Execute Command1 %s", aArg0);

   // Store the callback.
   mCommand1Callback = aCallback;

   // Execute the command.
   mCommand1CountZero = 4;

   // Done.
   delete aArg0;
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

   // Execute command1.
   if (mCommand1CountZero)
   {
      // Decrement the count to zero.
      if (--mCommand1CountZero == 0)
      {
         // Call the completion callback.
         mCommand1Callback(101, new std::string("command1_completion"));
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
