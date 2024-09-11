/*
 * top.hpp
 * Date Created: 08/09/24
*/

#ifndef TOP_HPP
#define TOP_HPP

#include "systemc.h"
#include "monitor.hpp"
#include "AvalonConf.hpp"
#include "AvalonMaster.hpp"
#include "AvalonSlave.hpp"
#include "monitor.hpp"

#define CLK_PERIOD 10000 /* Clock period in us */

class Top : public sc_module
{
public:
    sc_clock clk;

    sc_signal<bool>                 ready;
    sc_signal<bool>                 valid;
    sc_signal<sc_int<DATA_BITS>>    data;
    sc_signal<sc_int<CHANNEL_BITS>> channel;
    sc_signal<sc_int<ERROR_BITS>>   error;

    AvalonMaster    *pMaster;
    AvalonSlave     *pSlave;
    Monitor         *pMonitor;

    /* Constructor */
    Top(sc_module_name name);

    // Destructor
    ~Top();
};

#endif // TOP_HPP