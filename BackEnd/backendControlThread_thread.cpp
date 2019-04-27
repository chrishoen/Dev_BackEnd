/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "backendSettings.h"
#include "risThreadsPriorities.h"

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

   tSettings.setLocalIp("0.0.0.0", gSettings.mCommandInputPort);
   tSettings.setRemoteIp(gSettings.mFrontEndIpAddress, gSettings.mCommandOutputPort);
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
// QCall registered to the pipe reader child thread. It is invoked when
// a string is received. It process the received string.

void ControlThread::executeRxString(std::string* aString)
{
   Prn::print(Prn::View21, "ControlThread RxString %s", aString->c_str());
   // Guard.
   if (aString == 0) return;
   if (aString->length() == 0) return;

   // Get command line command from input string, parse with csv.
   Ris::CmdLineCmd tCmd(aString->c_str(),true);
   delete aString;

   // Execute the command line command with the given executive.
   execute(&tCmd);

   // Test for bad command. This is true if the executive didn't
   // accept the command.
   if (tCmd.isBadCmd())
   {
      Prn::print(Prn::View21, "INVALID COMMAND\n");
      mStringThread->sendString("nak INVALID COMMAND\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace