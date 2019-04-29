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

namespace Json
{
   class Value;
}

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This thread receives json formatted control messages sent by the frontend 
// on a udp datagram socket. The messages consist of commands and requests.
// The control messages are processed and json formatted response messages
// are sent to the frontend on another udp datagram socket. Periodic jason
// formatted messages are also sent to the frontend.
// 
// It inherits from BaseQCallThread to obtain a call queue based thread
// functionality.

class ControlThread : public Ris::Threads::BaseQCallThread
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

   // Command completion counters.
   int  mCommand1CountZero;
   int  mCommand2CountZero;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ControlThread();
   ~ControlThread();

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
   // sends command completion and status messages.
   void executeOnTimer(int aTimerCount) override;

   // Show thread state info.
   void showThreadInfo() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Receive message qcall.

   // qcall registered to the mStringThread child thread. It is invoked when
   // a string is received from the frontend.
   Ris::Net::UdpStringThread::RxStringQCall mRxStringQCall;

   // Convert the received string to a json value and call the main message
   // handler. This is bound to the qcall.
   void executeRxString(std::string* aString);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Message handlers. These process received json messages and
   // transmit json response messages.

   // Main message handler. This calls one of the specific message handlers.
   void processRxMsg(Json::Value& aMsg);

   // Specific message handlers.
   void processRxMsg_Command1(Json::Value& aMsg);
   void processRxMsg_Command2(Json::Value& aMsg);
   void processRxMsg_DataRequest(Json::Value& aMsg);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Send a json message to the frontend via the child string thread.
   void sendMsg(const Json::Value& aMsg);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _BACKENDCONTROLTHREAD_CPP_
       ControlThread* gControlThread = 0;
#else
extern ControlThread* gControlThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
