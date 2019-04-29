/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "backendSettings.h"
#include "risThreadsPriorities.h"
#include "json.h"

#define  _BACKENDCONTROLTHREAD_CPP_
#include "backendControlThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ControlThread::ControlThread()
{
   // Set base class thread variables.
   BaseClass::setThreadName("Command");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mNormal);
   BaseClass::setThreadPrintLevel(gSettings.mStatusPrintLevel);
   BaseClass::mTimerPeriod = 1000;

   // Bind qcalls.
   mRxStringQCall.bind(this, &ControlThread::executeRxString);

   // Initialize variables.
   mStringThread = 0;
   mCommand1CountZero = 0;
   mCommand2CountZero = 0;
}

ControlThread::~ControlThread()
{
   delete mStringThread;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It starts the child thread.

void ControlThread::threadInitFunction()
{
   // Instance of network socket settings.
   Ris::Net::Settings tSettings;

   tSettings.setLocalIp("0.0.0.0", gSettings.mBackEndControlPort);
   tSettings.setRemoteIp(gSettings.mFrontEndIpAddress, gSettings.mFrontEndControlPort);
   tSettings.mPrintLevel = gSettings.mCommandUdpPrintLevel;
   tSettings.mThreadPriority = Ris::Threads::gPriorities.mUdp;
   tSettings.mRxStringQCall = mRxStringQCall;

   // Create the child thread with the settings.
   mStringThread = new Ris::Net::UdpStringThread(tSettings);

   // Launch the child thread.
   mStringThread->launchThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It shuts down the child thread.

void  ControlThread::threadExitFunction()
{
   // Shutdown the child threads.
   mStringThread->shutdownThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show thread state info, base class overload.

void ControlThread::showThreadInfo()
{
   BaseClass::showThreadInfo();
   mStringThread->showThreadInfo();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert the received string to a json value and call one of the 
// message handlers. This is bound to the qcall.

void ControlThread::executeRxString(std::string* aString)
{
   Prn::print(Prn::View21, "ControlThread RxString %s", aString->c_str());

   // Guard.
   if (aString == 0 || aString->length() == 0)
   {
      Prn::print(Prn::View21, "ControlThread RxString string ERROR");
      return;
   }

   // Json variables.
   Json::Value tMsg;
   Json::Reader tReader;

   // Parse the received string into json message
   tReader.parse(*aString, tMsg);

   // Delete the received string.
   delete aString;
   
   // Guard.
   if (tMsg.isNull() || !tMsg.isMember("MsgId"))
   {
      Prn::print(Prn::View21, "ControlThread RxString message ERROR");
      return;
   }

   // Process the message.
   processRxMsg(tMsg);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Send a json message via the string thread.

void ControlThread::sendMsg(const Json::Value& aMsg)
{
   // Write the message to a string.
   Json::FastWriter tWriter;
   std::string tString;
   tWriter.omitEndingLineFeed();
   tString = tWriter.write(aMsg);

   // Send the string via the string thread.
   mStringThread->sendString(tString.c_str());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace