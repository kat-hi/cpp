// Testtreiber für Aufgabe 2: my::vector
// Autor: Hartmut Schirmacher

#include <iostream>

using namespace std;

void test_22();
void test_21();

int main()
{
    cout << "Starting tests (2.1) ------------------------------------------- START" << endl;
    test_21();


#if 1
    cout << "Starting tests (2.2) ------------------------------------------- START" << endl;
    test_22();
#endif

    cout << "End of tests --------------------------------------------------- END" << endl;

    return 0;
}
