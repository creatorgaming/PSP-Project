#include <iostream>
using namespace std;
class Test {
    public :
        Test() {
            cout << "Default" << endl;
        }
        Test(int x) {
            cout << "Pra" << x << endl;
        }
};

class Example {
    private :
        Test t1;
    public :
        Example()
            {
                // Test t;
                // t1 = Test(3);
        }
};

int main() {
    Example e;
}