#include "advios.hpp"

Advios::Advios(sc_module_name name) : sc_module(name)
{
    SC_CTHREAD(generatePulse, clk.pos());
    reset_signal_is(reset, true);

    SC_CTHREAD(switchControl, clk.pos());
    reset_signal_is(reset, true);
}

void Advios::generatePulse()
{
    while (true)
    {
        if (reset.read())
        {
            this->pulse.write(false);
        }
        else
        {
            wait(1, SC_SEC);
            this->pulse.write(true);
            wait();
            this->pulse.write(false);
        }
        wait();  // Synchronize to clock
    }
}

void Advios::switchControl()
{
    while (true)
    {
        if (reset.read())
        {
            this->outLeds.write(0);
        }
        else
        {
            sc_uint<NUM_BITS> switch_state = inSwitch.read();
            sc_uint<NUM_BITS> control_state = ctrl.read();

            if (control_state == 0x0)
            {
                if (switch_state == 0x8)
                {
                    outLeds.write(0x0);
                }
                else if (pulse.read())
                {
                    outLeds.write(outLeds.read() + 1);
                }
            }
            else
            {
                outLeds.write(switch_state & control_state);
            }
        }
        wait();  // Wait for the next clock cycle
    }
}
