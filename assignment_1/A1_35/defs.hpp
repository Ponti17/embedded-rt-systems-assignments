#pragma once
#include <systemc.h>

constexpr int MASTER_OUTPUT_PERIOD = 10;
constexpr enum sc_time_unit MASTER_OUTPUT_PERIOD_UNIT = SC_NS;

constexpr int CHANNEL_BITS = 8;
constexpr int ERROR_BITS = 1;
constexpr int DATA_BITS = 8;