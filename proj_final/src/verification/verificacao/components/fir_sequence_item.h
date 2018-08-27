// interface definitions for VIP

#ifndef _SQI_ITEM_H_
#define _SQI_ITEM_H_

#include <systemc>

class fir_sequence_item
{
 public:
 
  //+-----------------------------------------
  //| Data Members
  //+-----------------------------------------
  bool   data_enable;
  double sample; 

  //Output
  double result;
  bool   data_valid;  

  //+-----------------------------------------
  //| Data No Members
  //+-----------------------------------------
  
  fir_sequence_item(const std::string& name = "fir_sequence_item"){ }

};
std::ostream & operator << (std::ostream &os, const fir_sequence_item &item){
  return os << "instance item of fir block";
}
#endif /* _SQI_ITEM_H_ */
