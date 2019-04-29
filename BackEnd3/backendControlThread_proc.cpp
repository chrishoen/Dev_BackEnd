/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "backendControlThread.h"
#include "json.h"

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Main message handler. This calls one of the specific message handlers.

void ControlThread::processRxMsg(Json::Value& aMsg)
{
   // Execute a jump table on the message identifier to call
   // a specific message handler.
   std::string tMsgId = aMsg["MsgId"].asString();
   if      (tMsgId == "Command1")    processRxMsg_Command1(aMsg);
   else if (tMsgId == "Command2")    processRxMsg_Command2(aMsg);
   else if (tMsgId == "DataRequest") processRxMsg_DataRequest(aMsg);
   else
   {
      Prn::print(Prn::View21, "ControlThread processRxMsg UNKNOWN MsgId");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Specific message handler.

void ControlThread::processRxMsg_Command1(Json::Value& aRxMsg)
{
   Prn::print(Prn::View21, "ControlThread processRxMsg_Command1");

   // Guard.
   if (mCommand1CountZero)
   {
      // Send completion message for Nak.
      Json::Value tTxMsg;
      tTxMsg["MsgId"]   = "Completion";
      tTxMsg["Command"] = "Command1";
      tTxMsg["Code"]    = "Nak";
      tTxMsg["Info"] = "already running";
      sendMsg(tTxMsg);
      return;
   }

   // Send completion message for Ack.
   Json::Value tTxMsg;
   tTxMsg["MsgId"]   = "Completion";
   tTxMsg["Command"] = "Command1";
   tTxMsg["Code"]    = "Ack";
   sendMsg(tTxMsg);

   // Execute the command.
   mCommand1CountZero = 4;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Specific message handler.

void ControlThread::processRxMsg_Command2(Json::Value& aRxMsg)
{
   Prn::print(Prn::View21, "ControlThread processRxMsg_Command2");

   // Guard.
   if (mCommand2CountZero)
   {
      // Send completion message for Nak.
      Json::Value tTxMsg;
      tTxMsg["MsgId"] = "Completion";
      tTxMsg["Command"] = "Command2";
      tTxMsg["Code"] = "Nak";
      tTxMsg["Info"] = "already running";
      sendMsg(tTxMsg);
      return;
   }

   // Send completion message for Ack.
   Json::Value tTxMsg;
   tTxMsg["MsgId"] = "Completion";
   tTxMsg["Command"] = "Command2";
   tTxMsg["Code"] = "Ack";
   sendMsg(tTxMsg);

   // Execute the command.
   mCommand2CountZero = 10;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Specific message handler.

void ControlThread::processRxMsg_DataRequest(Json::Value& aRxMsg)
{
   Prn::print(Prn::View21, "ControlThread processRxMsg_DataRequest");

   // Compose data response transmit message.
   Json::Value tTxMsg;
   tTxMsg["MsgId"] = "DataResponse";
   tTxMsg["DataType"] = "DataAmber";
   tTxMsg["Item0"] = "some_item0";
   tTxMsg["Item1"] = "some_item1";
   tTxMsg["Item2"] = "some_item2";
   tTxMsg["Item3"] = "some_item3";

   // Send the message.
   sendMsg(tTxMsg);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute periodically. This is called by the base class timer. It
// sends an echo request message.

void ControlThread::executeOnTimer(int aTimerCount)
{
   Prn::print(Prn::View21, "STATUS TIMER %5d", aTimerCount);

   // Send periodic status message.
   char tString[100];
   sprintf(tString, "%d", aTimerCount);

   Json::Value tTxMsg;
   tTxMsg["MsgId"] = "Status";
   tTxMsg["Count"] = tString;
   sendMsg(tTxMsg);

   // Execute command1.
   if (mCommand1CountZero)
   {
      // Decrement the count to zero.
      if (--mCommand1CountZero == 0)
      {
         // Send completion message for done.
         Json::Value tTxMsg;
         tTxMsg["MsgId"] = "Completion";
         tTxMsg["Command"] = "Command1";
         tTxMsg["Code"] = "Done";
         sendMsg(tTxMsg);
      }
   }

   // Execute command2.
   if (mCommand2CountZero)
   {
      // Send completion message for progress.
      char tString[100];
      sprintf(tString, "working %d", mCommand2CountZero);

      Json::Value tTxMsg;
      tTxMsg["MsgId"] = "Completion";
      tTxMsg["Command"] = "Command2";
      tTxMsg["Code"] = "Progress";
      tTxMsg["Info"] = tString;
      sendMsg(tTxMsg);

      // Decrement the count to zero.
      if (--mCommand2CountZero == 0)
      {
         // Send completion message for done.
         Json::Value tTxMsg;
         tTxMsg["MsgId"] = "Completion";
         tTxMsg["Command"] = "Command2";
         tTxMsg["Code"] = "Done";
         sendMsg(tTxMsg);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace