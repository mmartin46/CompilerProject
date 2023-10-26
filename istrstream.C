#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
  string input("input test 123 4.7 A");
  istringstream inputString(input.c_str());
  string string1, string2;
  int i;
  double d;
  char c;

  inputString >> string1 >> string2 >> i >> d >> c;

  cout << "The following items were extracted" << endl
       << "from the istringstream object:" << endl
       << "string: " << string1 << endl
       << "string: " << string2 << endl
       << "   int: " << i << endl
       << "double: " << d << endl
       << "  char: " << c << endl;

  long x;
  inputString >> x;
  if (inputString)
    cout << "  long: " << x << endl;
  else
  {
    cout << "inputString is empty" << endl;
    inputString.clear(); // since it's in a fail state, clear it
  }

  input = "2147483647";
  inputString.str(input.c_str());
  cout << "before: x = " << x << endl;
  inputString >> x;
  cout << "after: x = " << x << endl;

  input = "bad";
  inputString.clear(); // since it's in a fail state, clear it
  inputString.str(input.c_str());
  cout << "before: x = " << x << endl;
  inputString >> hex >> x;
  cout << "after: x = " << x << endl;
  cout << "after: x = " << hex << x << endl;

  return EXIT_SUCCESS;
}       
