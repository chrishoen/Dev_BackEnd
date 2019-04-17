#pragma once

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Create and launch threads. This is called at dll initialization.
void proc_initialize();
// Shutdown and delete threads. This is called at dll finalization.
void proc_finalize();


