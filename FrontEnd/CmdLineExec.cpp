#include "stdafx.h"

#include "backendExports.h"
#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"))  reset();

   if (aCmd->isCmd("GO1"))  executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))  executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))  executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))  executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))  executeGo5(aCmd);

   if (aCmd->isCmd("Timer"))   executeTimer(aCmd);
   if (aCmd->isCmd("cmd1"))    executeCommand1(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void myTimerCallback(int aCount)
{
   Prn::print(Prn::View01, "myTimerCallback %d", aCount);
}

void CmdLineExec::executeTimer(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, true);

   if (aCmd->argBool(1))
   {
      BackEnd::setTimerCallback(myTimerCallback);
   }
   else
   {
      BackEnd::resetTimerCallback();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void myCommand1Callback(int aCompletionCode,std::string* aCompletionString)
{
   Prn::print(Prn::View01, "myCommand1Callback %d %s", aCompletionCode, aCompletionString->c_str());
   delete aCompletionString;
}

void CmdLineExec::executeCommand1(Ris::CmdLineCmd* aCmd)
{
   BackEnd::doCommand1(new std::string("arg0"),myCommand1Callback);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "test %d", BackEnd::getCount());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

