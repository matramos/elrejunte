#include <sstream>
string num_to_str(int x){
  ostringstream convert;
  convert << x;
  return convert.str();
}

int str_to_num(string x){
  int ret;
  istringstream (x) >> ret;
  return ret;
}