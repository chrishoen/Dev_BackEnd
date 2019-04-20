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
   mCommand2QCall.bind(this, &InterfaceThread::executeCommand2);

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

void InterfaceThread::executeCommand1(std::string* aArg0, Command1Callback_T aCompletionCallback)
{
   Prn::print(Prn::View21, "Execute Command1 %s", aArg0);

   // Guard.
   if (mCommand1CountZero)
   {
      aCompletionCallback(666, new std::string("command2_already_running"));
      return;
   }
   // Store the callback.
   mCommand1Callback = aCompletionCallback;

   // Execute the command.
   mCommand1CountZero = 4;

   // Done.
   delete aArg0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute the command. This is bound to the qcall.
// Execute the command and call the callback upon completion.
// Periodically call the progress callback until completion.

void InterfaceThread::executeCommand2(
   std::string* aArg0,
   Command2CompletionCallback_T aCompletionCallback,
   Command2ProgressCallback_T aProgressCallback)
{
   Prn::print(Prn::View21, "Execute Command2 %s", aArg0);

   // Guard.
   if (mCommand2CountZero)
   {
      aCompletionCallback(666, new std::string("command2_already_running"));
      return;
   }

   // Store the callback.
   mCommand2CompletionCallback = aCompletionCallback;
   mCommand2ProgressCallback = aProgressCallback;

   // Execute the command.
   mCommand2CountZero = 10;

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

   // Execute command2.
   if (mCommand2CountZero)
   {
      // Call the progress callback.
      mCommand2ProgressCallback(new std::string("command2_progress"));

      // Decrement the count to zero.
      if (--mCommand2CountZero == 0)
      {
         // Call the completion callback.
         mCommand2CompletionCallback(201, new std::string("command2_completion"));
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
