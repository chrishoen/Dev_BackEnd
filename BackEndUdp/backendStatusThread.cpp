/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "backendSettings.h"
#include "risThreadsPriorities.h"

#define  _BACKENDSTATUSTHREAD_CPP_
#include "backendStatusThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StatusThread::StatusThread()
{
   // Set base class thread variables.
   BaseClass::setThreadName("Status");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mNormal);
   BaseClass::setThreadPrintLevel(gSettings.mStatusPrintLevel);
   BaseClass::mTimerPeriod = 1000;

   // Initialize variables.
   mStringThread = 0;
   mShowCode = 0;
}

StatusThread::~StatusThread()
{
   delete mStringThread;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It starts the child thread.

void StatusThread::threadInitFunction()
{
   // Instance of network socket settings.
   Ris::Net::Settings tSettings;

   tSettings.setLocalIp("127.0.0.1", gSettings.mStatusPort);
   tSettings.setRemoteIp("127.0.0.1", gSettings.mStatusPort);
   tSettings.mPrintLevel = gSettings.mStatusWriterPrintLevel;
   tSettings.mThreadPriority = Ris::Threads::gPriorities.mUdp;

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

void  StatusThread::threadExitFunction()
{
   // Shutdown the child threads.
   mStringThread->shutdownThread();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show thread state info, base class overload.

void StatusThread::showThreadInfo()
{
   BaseClass::showThreadInfo();
   mStringThread->showThreadInfo();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer.

void StatusThread::executeOnTimer(int aCount)
{
   // Send .
   char tString[200];
   sprintf(tString, "status_update %d", aCount);
   mStringThread->sendString(new std::string(tString));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace