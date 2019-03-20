#include "stdafx.h"


#include "risThreadsProcess.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void main_initialize()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process

   Ris::Threads::enterProcessHigh();

   // Initialize print facility
   Prn::resetPrint();
   Prn::useConsole(1);
   Prn::initializePrint();
   
   // Initialize print filters
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  true);

   Prn::setFilter(Prn::View01, true, 1);
   Prn::setFilter(Prn::View02, true, 1);
   Prn::setFilter(Prn::View03, true, 1);
   Prn::setFilter(Prn::View04, true, 1);

   Prn::print(0,"Test*******************************************BEGIN");

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize

void main_finalize()
{
   Prn::print(0,"Test*******************************************END");

   // Close print
   Prn::finalizePrint();

   // Exit process
   Ris::Threads::exitProcess();
}

