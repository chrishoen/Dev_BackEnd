#pragma once

/*==============================================================================
backend command execution thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include "risNetUdpStringThread.h"
#include "risThreadsQCallThread.h"
#include "risCmdLineCmd.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This thread connects to a client two udp sockets. It receives commands
// from a client, executes them, and sends responses to the client.
// 
// It inherits from BaseQCallThread to obtain a call queue based thread
// functionality.

class CommandThread : public Ris::Threads::BaseQCallThread
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
   // Methods.

   // Constructor.
   CommandThread();
   ~CommandThread();

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Receive message qcall.

   // qcall registered to the mTcpStringThread child thread. It is invoked when
   // a message is received. It process the received messages.
   Ris::Net::UdpStringThread::RxStringQCall mRxStringQCall;

   // Call one of the specific receive message handlers. This is bound to the
   // qcall.
   void executeRxString(std::string* aString);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Send a string via the string thread
   void send(const char* aString);
   void send(std::string* aString);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Execute commands.

   // Execute a command line command that is received from the read pipe.
   // It calls one of the following specific command execution functions.
   void execute(Ris::CmdLineCmd* aCmd);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Execute commands.

   void executeCommand1(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _BACKENDCOMMANDTHREAD_CPP_
       CommandThread* gCommandThread = 0;
#else
extern CommandThread* gCommandThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
