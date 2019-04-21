//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _BACKENDSETTINGS_CPP_
#include "backendSettings.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace BackEnd
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Settings::Settings()
{
   reset();
}

void Settings::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("/BackEnd/BackEnd_Settings.txt");

   mBackEndIpAddress[0];
   mFrontEndIpAddress[0];
   mCommandInputPort = 0;
   mCommandOutputPort = 0;
   mStatusOutputPort = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Settings::show()
{
   char tBuffer[40];
   printf("\n");
   printf("BackEnd Settings***************************************** %s\n", mTargetSection);

   printf("\n");
   printf("BackEndIpAddress           %10s\n", mBackEndIpAddress);
   printf("FrontEndIpAddress          %10s\n", mFrontEndIpAddress);
   printf("CommandInputPort           %10d\n", mCommandInputPort);
   printf("CommandOutputPort          %10d\n", mCommandOutputPort);
   printf("StatusOutputPort           %10d\n", mStatusOutputPort);

   printf("\n");
   printf("CommandPrintLevel          %-10s\n", mCommandPrintLevel.asString(tBuffer));
   printf("CommandUdpPrintLevel       %-10s\n", mCommandUdpPrintLevel.asString(tBuffer));
   printf("StatusPrintLevel           %-10s\n", mStatusPrintLevel.asString(tBuffer));
   printf("StatusUdpPrintLevel        %-10s\n", mStatusUdpPrintLevel.asString(tBuffer));

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void Settings::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("BackEndIpAddresss"))        aCmd->copyArgString(1, mBackEndIpAddress, cMaxStringSize);
   if (aCmd->isCmd("FrontEndIpAddresss"))       aCmd->copyArgString(1, mFrontEndIpAddress, cMaxStringSize);

   if (aCmd->isCmd("CommandInputPort"))         mCommandInputPort = aCmd->argInt(1);
   if (aCmd->isCmd("CommandOutputPort"))        mCommandInputPort = aCmd->argInt(1);
   if (aCmd->isCmd("StatusOutputPort"))         mStatusOutputPort = aCmd->argInt(1);


   if (aCmd->isCmd("CommandPrintLevel"))        mCommandPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("CommandUdpPrintLevel"))     mCommandUdpPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("StatusPrintLevel"))         mStatusPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("StatusUdpPrintLevel"))      mStatusUdpPrintLevel.readArgs(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Settings::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace