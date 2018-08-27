// interface definitions for VIP

#ifndef _SQI_ITEM_H_
#define _SQI_ITEM_H_

#include <systemc>

class ula_sequence_item
{
 public:
 
  //+-----------------------------------------
  //| Data Members
  //+-----------------------------------------
  bool   data_enable;
  double data_a;
  double data_b;
  int    sel;    

  //Output
  double data_out;
  bool   carryout;
  bool   data_valid;  

  //+-----------------------------------------
  //| Data No Members
  //+-----------------------------------------
  
  ula_sequence_item(const std::string& name = "ula_sequence_item"){ }

};
std::ostream & operator << (std::ostream &os, const ula_sequence_item &item){
  return os << "instance item of ULA block";
}
#endif /* _SQI_ITEM_H_ */
