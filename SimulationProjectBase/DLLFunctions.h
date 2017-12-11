#pragma once
#include "IRunnable.h"
#include "Table.h"

sim::IRunnable* CreateSimulatorInstance(const table::RowHeader& row_header, const table::Table& tbl);