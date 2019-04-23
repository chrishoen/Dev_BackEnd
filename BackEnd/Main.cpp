#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "tsPrintThread.h"
#include "backendStatusThread.h"
#include "backendCommandThread.h"

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

   BackEnd::gCommandThread = new BackEnd::CommandThread;
   BackEnd::gCommandThread->launchThread();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show program threads.

   Ris::Threads::showCurrentThreadInfo();
   TS::gPrintThread->showThreadInfo();
   BackEnd::gStatusThread->showThreadInfo();
   BackEnd::gCommandThread->showThreadInfo();

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
   BackEnd::gCommandThread->shutdownThread();

   delete BackEnd::gStatusThread;
   delete BackEnd::gCommandThread;
   BackEnd::gStatusThread = 0;
   BackEnd::gCommandThread = 0;

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
