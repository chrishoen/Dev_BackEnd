#include "stdafx.h"

#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

#include "backendExports.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the program.

   BackEnd::initializeBackEnd();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Run the user command line executive, it returns when the user exits.

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize the program.

   BackEnd::finalizeBackEnd();
   return 0;
}