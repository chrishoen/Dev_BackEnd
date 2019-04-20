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
   typedef std::function<void(int)> TimerCallback_T;
   TimerCallback_T mTimerCallback;

   // Command1 callback.
   int  mCommand1CountZero;
   typedef std::function<void(int,std::string*)> Command1CompletionCallback_T;
   Command1CompletionCallback_T mCommand1CompletionCallback;

   // Command2 callback.
   int  mCommand2CountZero;
   typedef std::function<void(int, std::string*)> Command2CompletionCallback_T;
   Command2CompletionCallback_T mCommand2CompletionCallback;
   typedef std::function<void(std::string*)> Command2ProgressCallback_T;
   Command2ProgressCallback_T mCommand2ProgressCallback;

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Command1.

   // qcall to execute the command.
   Ris::Threads::QCall2<
      std::string*,
      Command1CompletionCallback_T> mCommand1QCall;

   // Execute the command. This is bound to the qcall.
   // Execute the command and call the callback upon completion.
   void executeCommand1(
      std::string* aArg0,
      Command1CompletionCallback_T aCompletionCallback);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Command2.

   // qcall to execute the command.
   Ris::Threads::QCall3<
      std::string*, 
      Command2CompletionCallback_T, 
      Command2ProgressCallback_T> mCommand2QCall;

   // Execute the command. This is bound to the qcall.
   // Execute the command and call the callback upon completion.
   // Periodically call the progress callback until completion.
   void executeCommand2(
      std::string* aArg0, 
      Command2CompletionCallback_T aCompletionCallback,
      Command2ProgressCallback_T aProgressCallback);
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

