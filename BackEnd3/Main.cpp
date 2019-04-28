#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "tsPrintThread.h"
#include "backendIsochThread.h"
#include "backendControlThread.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program.

   main_initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Launch program threads.

   BackEnd::gIsochThread = new BackEnd::IsochThread;
   BackEnd::gIsochThread->launchThread();

   BackEnd::gControlThread = new BackEnd::ControlThread;
   BackEnd::gControlThread->launchThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   TS::gPrintThread->showThreadInfo();
   BackEnd::gIsochThread->showThreadInfo();
   BackEnd::gControlThread->showThreadInfo();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Start user command line executive, wait for user to exit.

   CmdLineExec* exec = new CmdLineExec;
   Ris::executeCmdLineConsole(exec);
   delete exec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Shutdown program Threads.

   BackEnd::gIsochThread->shutdownThread();
   BackEnd::gControlThread->shutdownThread();

   delete BackEnd::gIsochThread;
   delete BackEnd::gControlThread;
   BackEnd::gIsochThread = 0;
   BackEnd::gControlThread = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize program.

   main_finalize();
   return 0;

   printf("press enter\n");
   getchar();

   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
