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
   // Guard.
   if (mCommand1CountZero)
   {
      mStringThread->sendString("Command1,nak,already running");
      return;
   }

   // Ack the command.
   mStringThread->sendString("Command1,ack");

   // Execute the command.
   mCommand1CountZero = 4;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CommandThread::executeCommand2(Ris::CmdLineCmd* aCmd)
{
   // Guard.
   if (mCommand2CountZero)
   {
      mStringThread->sendString("Command2,nak,already running");
      return;
   }

   // Ack the command.
   mStringThread->sendString("Command2,ack");

   // Execute the command.
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
         mStringThread->sendString("Command1,done");
      }
   }

   // Execute command2.
   if (mCommand2CountZero)
   {
      // Call the progress callback.
      char tString[100];
      sprintf(tString, "Command2,progress,working %d", mCommand2CountZero);
      mStringThread->sendString(tString);

      // Decrement the count to zero.
      if (--mCommand2CountZero == 0)
      {
         // Call the completion callback.
         mStringThread->sendString("Command2,done");
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace