#include <ctime>
#include <iostream>

using namespace std;

int main()
{
  time_t now = time (NULL);

  cout << "Last Modified: " << ctime(&now) << endl;

  return 0;
}
