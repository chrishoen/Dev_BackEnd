#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "risProgramTime.h"
#include "json.h"

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
   if (aCmd->isCmd("RESET"))   reset();
   if (aCmd->isCmd("GO1"))     executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))     executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))     executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))     executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))     executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))     executeGo6(aCmd);
   if (aCmd->isCmd("GO7"))     executeGo7(aCmd);
   if (aCmd->isCmd("GO8"))     executeGo8(aCmd);
   if (aCmd->isCmd("GO9"))     executeGo9(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   std::string line;
   std::ifstream tFile("C:\\MyJson\\input101.json");
   if (tFile.is_open())
   {
      while (getline(tFile, line))
      {
         std::cout << line << '\n';
      }
      tFile.close();
   }

   else std::cout << "Unable to open file";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   std::ifstream tFile("C:\\MyJson\\input101.json");
   Json::Value tRoot;
   tFile >> tRoot;
   std::cout << tRoot << std::endl;

   std::string tMsgId = tRoot["msg-id"].asString();
   std::cout << "msg-id  " << tMsgId << std::endl;

   tRoot["msg-id"] = "test2_msg";
   std::cout << tRoot << std::endl;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   std::ofstream tFile("C:\\MyJson\\output101.json", std::ofstream::out);

   Json::Value tRoot;
   tRoot["msg-id"] = "test3_msg";
   tRoot["payload"] = "some_payload";

   std::cout << tRoot << std::endl;

   tFile << tRoot << std::endl;
   tFile.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   std::ofstream tFile("C:\\MyJson\\output101.json", std::ofstream::out);
   std::stringstream tStream;
   std::string tString;

   Json::Value tRoot;
   tRoot["msg-id"] = "test4_msg";
   tRoot["payload"] = "some_payload";

   tStream << tRoot << std::endl;
   std::cout << tStream.str();

   tString = tStream.str();
   std::cout << tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   std::stringstream tStream1;
   std::stringstream tStream2;
   std::string tString;
   Json::Value tRoot1;
   Json::Value tRoot2;

   std::cout << "LINE101" << std::endl;
   tRoot1["msg-id"] = "test4_msg";
   tRoot1["payload"] = "some_payload";

   tRoot1.

   std::cout << "LINE102" << std::endl;
   tStream1 << tRoot1 << std::endl;
   tString = tStream1.str();
   std::cout << tString;

   std::cout << "LINE103" << std::endl;
   tStream2.str(tString);
   std::cout << tStream2.str();

   std::cout << "LINE104" << std::endl;
   tStream2 >> tRoot2;
   std::cout << tRoot2;
   std::cout << "LINE105" << std::endl;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   std::string tString;
   Json::Value tRoot1;
   Json::Value tRoot2;
   Json::FastWriter tWriter;
   Json::Reader tReader;

   std::cout << "LINE101" << std::endl;
   tRoot1["msg-id"] = "test6_msg";
   tRoot1["payload"] = "some_payload";

   tString = tWriter.write(tRoot1);
   std::cout << "LINE102" << std::endl;
   std::cout << tString << std::endl;

   tReader.parse(tString, tRoot2);
   std::cout << tRoot2 << std::endl;

   std::cout << "LINE103" << std::endl;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   std::string tString;
   Json::Value tRoot1;
   Json::FastWriter tWriter;
   Json::Reader tReader;

   std::cout << "LINE101" << std::endl;
   tRoot1["MsgId"] = "Test7Msg";
   tRoot1["Payload"] = "some_payload";

   std::cout << "LINE102" << std::endl;
   tString = tWriter.write(tRoot1);
   std::cout << tString;
   std::cout << "LINE103" << std::endl;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
   Prn::print(Prn::View11, "TESTING11");
   Prn::print(Prn::View21, "TESTING21");
}

