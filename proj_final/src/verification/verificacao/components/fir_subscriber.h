#include "tlm.h"
using namespace tlm;

struct fir_subscriber : sc_object, tlm::tlm_analysis_if<fir_sequence_item> {

  //-----------------------------
  // TLM FIFO
  //-----------------------------
  tlm_fifo<fir_sequence_item>  fifo;
  
  //-----------------------------
  // Constructor
  //-----------------------------
  fir_subscriber ( const char* n ) : sc_object(n) , fifo("fifo", -1){ } 

  virtual void write( const fir_sequence_item& t ) {
    if(fifo.nb_put(t) == 0) {
      ERROR(name(), "[write]: It was not possible to put the item in the fifo");
    }
  }
};
