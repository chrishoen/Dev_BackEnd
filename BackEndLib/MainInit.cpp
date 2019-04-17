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
   Prn::useConsole(2);
   Prn::initializePrint();
   
   // Initialize print filters
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  true);

   Prn::setFilter(Prn::View21, true, 2);
   Prn::setFilter(Prn::View22, true, 2);
   Prn::setFilter(Prn::View23, true, 2);
   Prn::setFilter(Prn::View24, true, 2);

   Prn::print(Prn::View21,"BackEndDLL****************************************BEGIN");

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize

void main_finalize()
{
   Prn::print(Prn::View21, "BackEndDLL****************************************END");

   // Close print
   Prn::finalizePrint();

   // Exit process
   Ris::Threads::exitProcess();
}

