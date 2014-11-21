/* Tests exceptions */

#include <iostream>

using namespace std;

int main () {
  try
  {
    throw 20;
  }
  catch (int e)
  {
    cout << "Exception caught: " << e << endl;
  }
  return 0;
}

