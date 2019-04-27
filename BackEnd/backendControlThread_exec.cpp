/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "backendControlThread.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ControlThread::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Command"))
   {
      if (aCmd->isArgString(1, "Command1"))  executeCommand1(aCmd);
      if (aCmd->isArgString(1, "Command2"))  executeCommand2(aCmd);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ControlThread::executeCommand1(Ris::CmdLineCmd* aCmd)
{
   // Guard.
   if (mCommand1CountZero)
   {
      mStringThread->sendString("Completion,Command1,nak,already running");
      return;
   }

   // Ack the command.
   mStringThread->sendString("Completion,Command1,ack");

   // Execute the command.
   mCommand1CountZero = 4;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ControlThread::executeCommand2(Ris::CmdLineCmd* aCmd)
{
   // Guard.
   if (mCommand2CountZero)
   {
      mStringThread->sendString("Completion,Command2,nak,already running");
      return;
   }

   // Send completion message.
   mStringThread->sendString("Completion,Command2,ack");

   // Execute the command.
   mCommand2CountZero = 10;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer. It
// sends an echo request message.

void ControlThread::executeOnTimer(int aTimerCount)
{
   // Send status message.
   char tString[100];
   sprintf(tString, "Status,%d", aTimerCount);
   mStringThread->sendString(tString);

   // Execute command1.
   if (mCommand1CountZero)
   {
      // Decrement the count to zero.
      if (--mCommand1CountZero == 0)
      {
         // Send completion message.
         mStringThread->sendString("Completion,Command1,done");
      }
   }

   // Execute command2.
   if (mCommand2CountZero)
   {
      // Send completion message.
      char tString[100];
      sprintf(tString, "Completion,Command2,progress,working %d", mCommand2CountZero);
      mStringThread->sendString(tString);

      // Decrement the count to zero.
      if (--mCommand2CountZero == 0)
      {
         // Send completion message.
         mStringThread->sendString("Completion,Command2,done");
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace