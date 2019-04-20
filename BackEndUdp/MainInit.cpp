#include "stdafx.h"


#include "tsThreadServices.h"
#include "risThreadsProcess.h"
#include "backendSettings.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void main_initialize()
{
   printf("BackEndUpd Program*********************************************BEGIN\n");
   printf("BackEndUpd Program*********************************************BEGIN\n");
   printf("BackEndUpd Program*********************************************BEGIN\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("Status");
   TS::setProgramPrintLevel(TS::PrintLevel(3, 3));
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::useConsole(2);
   Prn::initializePrint();
   
   // Initialize print filters.
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  true);

   Prn::setFilter(Prn::View01, true);
   Prn::setFilter(Prn::View02, true);
   Prn::setFilter(Prn::View03, true);
   Prn::setFilter(Prn::View04, true);

   Prn::setFilter(Prn::View21, true, 2);
   Prn::setFilter(Prn::View22, true, 2);
   Prn::setFilter(Prn::View23, true, 2);
   Prn::setFilter(Prn::View24, true, 2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   // Read parameters files.
   BackEnd::gSettings.reset();
   BackEnd::gSettings.readSection("default");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize

void main_finalize()
{

   // Close print
   Prn::finalizePrint();

   // Exit process
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // Done.
   printf("\n");
   printf("BackEndUdp Program*********************************************END\n\n");
}

