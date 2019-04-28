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

   mFrontEndIpAddress[0];
   mBackEndControlPort = 0;
   mFrontEndControlPort = 0;
   mFrontEndIsochPort = 0;
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
   printf("FrontEndIpAddress          %-10s\n", mFrontEndIpAddress);
   printf("BackEndControlPort         %-10d\n", mBackEndControlPort);
   printf("FrontEndControlPort        %-10d\n", mFrontEndControlPort);
   printf("FrontEndIsochPort          %-10d\n", mFrontEndIsochPort);

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

   if (aCmd->isCmd("FrontEndIpAddress"))        aCmd->copyArgString(1, mFrontEndIpAddress, cMaxStringSize);
   if (aCmd->isCmd("BackEndControlPort"))       mBackEndControlPort = aCmd->argInt(1);
   if (aCmd->isCmd("FrontEndControlPort"))      mFrontEndControlPort = aCmd->argInt(1);
   if (aCmd->isCmd("FrontEndIsochPort"))        mFrontEndIsochPort = aCmd->argInt(1);

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