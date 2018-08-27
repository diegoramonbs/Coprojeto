#include "systemc.h"
#include "swap.h"

int sc_main(int argc, char **argv)
{
	swap top("top");
	sc_start(500000, SC_NS);
	return 0;
}
