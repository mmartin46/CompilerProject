#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{
  ostringstream outputstring;

  int num = 50;

  outputstring.str("");
  outputstring << "num = " << num << endl;
  outputstring << "num in hex = " << hex << num << endl;
  outputstring << "(num + 13) in hex = " << hex << num + 13 << endl;
  outputstring << "(num + 13) in uppercase hex = " << uppercase
               << num + 13 << endl;
  cout << outputstring.str() << endl;

  outputstring.str("");
  outputstring << "after reinitialization";
  outputstring << " " << num+13 << endl;
  cout << outputstring.str() << endl;
  cout << "length as C++ string = " << outputstring.str().length() << endl;
  cout << "length as C string = " << strlen(outputstring.str().c_str()) 
       << endl;

  return EXIT_SUCCESS;
}
