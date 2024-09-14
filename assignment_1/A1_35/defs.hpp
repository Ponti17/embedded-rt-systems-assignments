#pragma once
#include <systemc.h>

constexpr int CLOCK_PERIOD = 10;
constexpr enum sc_time_unit CLOCK_PERIOD_UNIT = SC_NS;

constexpr int MASTER_OUTPUT_PERIOD = 10;
constexpr enum sc_time_unit MASTER_OUTPUT_PERIOD_UNIT = SC_NS;

constexpr int CH_BITS = 2;
constexpr int ER_BITS = 1;
constexpr int D_BITS = 8;

using CHANNEL_BITS = sc_uint<CH_BITS>;
using ERROR_BITS = sc_uint<ER_BITS>;
using DATA_BITS = sc_uint<D_BITS>;