/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "backendCommandThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CommandThread::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("command1"))  executeCommand1(aCmd);
   if (aCmd->isCmd("command2"))  executeCommand2(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CommandThread::executeCommand1(Ris::CmdLineCmd* aCmd)
{
   mStringThread->sendString("command1: ack"); 
   mCommand1CountZero = 4;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CommandThread::executeCommand2(Ris::CmdLineCmd* aCmd)
{
   mStringThread->sendString("command2: ack");
   mCommand2CountZero = 10;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer. It
// sends an echo request message.

void CommandThread::executeOnTimer(int aTimerCount)
{
   // Execute command1.
   if (mCommand1CountZero)
   {
      // Decrement the count to zero.
      if (--mCommand1CountZero == 0)
      {
         // Call the completion callback.
         mStringThread->sendString("command1: done");
      }
   }

   // Execute command2.
   if (mCommand2CountZero)
   {
      // Call the progress callback.
      char tString[100];
      sprintf(tString, "command2: progress %d", mCommand2CountZero);
      mStringThread->sendString(tString);

      // Decrement the count to zero.
      if (--mCommand2CountZero == 0)
      {
         // Call the completion callback.
         mStringThread->sendString("command2: done");
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace