#include <iostream>
#include <functional>
#include <ctime>
using namespace std;

class MontiHallShow {
private:
    int mWins;
    int mLose;
    int mSize;
public:
    MontiHallShow(int size = 3)
    : mWins{ 0 }, mLose{ 0 }, mSize{ size } { srand(static_cast<unsigned int>(time(NULL)) * 1000); }
    
    void emulation(function<bool(int, int)> f = { [](int a, int b) {return a != b; } }) {
        if (f((rand() % mSize) + 1,(rand() % mSize) + 1)){
            mWins += 1;
        }
        else {
            mLose += 1;
        }
    }
    void printResults() {
        cout << "Win: " << 100 * static_cast<double>(mWins) / static_cast<double>(mWins + mLose) << "% | ";
        cout << "Loss: " << 100 * static_cast<double>(mLose) / static_cast<double>(mWins + mLose) << "%" << endl;
        mLose = mWins = 0;
    }
};
 
int main()
{
    function<bool(int, int)> winNoSwap{ [](int a, int b) {return a == b; } };
    function<bool(int, int)> winSwap{ [](int a, int b) {return a != b; } };
    
    MontiHallShow na = MontiHallShow(3);
    
    for (int i = 0; i < 100'000'000; i++) { na.emulation(winNoSwap); }
    cout << "Win and Loss (with no change): " << endl; na.printResults(); cout << endl;
    
    for (int i = 0; i < 100'000'000; i++) { na.emulation(winSwap); }
    cout << "Win and Loss (with change): " << endl; na.printResults(); cout << endl;
    
    return 0;
}
