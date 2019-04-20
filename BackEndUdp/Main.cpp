#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "tsPrintThread.h"
#include "backendStatusThread.h"

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

   BackEnd::gStatusThread = new BackEnd::StatusThread;
   BackEnd::gStatusThread->launchThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   TS::gPrintThread->showThreadInfo();
   BackEnd::gStatusThread->showThreadInfo();

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

   BackEnd::gStatusThread->shutdownThread();

   delete BackEnd::gStatusThread;

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
