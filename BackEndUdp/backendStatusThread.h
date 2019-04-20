#pragma once

/*==============================================================================
named pipe command execution thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include "risNetUdpStringThread.h"
#include "risThreadsQCallThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This thread connects to a client via a named pipes. It sends status
// to the client.
// 
// It inherits from BaseQCallThread to obtain a call queue based thread
// functionality.

class StatusThread : public Ris::Threads::BaseQCallThread
{
public:
   typedef Ris::Threads::BaseQCallThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Udp string socket child thread. It provides the thread execution
   // context for a udp string socket and uses it to provide string
   // communication. It interfaces to this thread via the receive string
   // qcall callback.
   Ris::Net::UdpStringThread* mStringThread;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // This determines which status is shown.
   int mShowCode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StatusThread();
   ~StatusThread();

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

   // Show thread state info.
   void showThreadInfo() override;

   // Execute periodically. This is called by the base class timer.
   void executeOnTimer(int aCurrentTimeCount) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Show status periodically.

   // Show status.
   void show2(int aCount);

   // Send status to the pipe client.
   void send(int aCount);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _BACKENDSTATUSTHREAD_CPP_
       StatusThread* gStatusThread;
#else
extern StatusThread* gStatusThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
