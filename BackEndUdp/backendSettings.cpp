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

   mCommandPort = 0;
   mCompletionPort = 0;
   mStatusPort = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Settings::show()
{
   char tBuffer[40];
   printf("\n");
   printf("Settings************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("CommandPrintLevel         %-10s\n", mCommandPrintLevel.asString(tBuffer));
   printf("CommandReaderPrintLevel   %-10s\n", mCommandReaderPrintLevel.asString(tBuffer));
   printf("CommandWriterPrintLevel   %-10s\n", mCommandWriterPrintLevel.asString(tBuffer));
   printf("StatusPrintLevel          %-10s\n", mStatusPrintLevel.asString(tBuffer));
   printf("StatusWriterPrintLevel    %-10s\n", mStatusPrintLevel.asString(tBuffer));

   printf("\n");
   printf("CommandPort                %10d\n", mCommandPort);
   printf("StatusPort                 %10d\n", mStatusPort);
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

   if (aCmd->isCmd("CommandPort"))              mCommandPort = aCmd->argInt(1);
   if (aCmd->isCmd("StatusPort"))               mStatusPort = aCmd->argInt(1);

   if (aCmd->isCmd("CommandPrintLevel"))        mCommandPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("CommandReaderPrintLevel"))  mCommandReaderPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("CommandWriterPrintLevel"))  mCommandWriterPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("StatusPrintLevel"))         mStatusPrintLevel.readArgs(aCmd);
   if (aCmd->isCmd("StatusWriterPrintLevel"))   mStatusWriterPrintLevel.readArgs(aCmd);
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