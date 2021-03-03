#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;








int main() {
    double  x,y;
    ifstream input_file;
    int index;
    string s = "../locs_demo.txt";
    input_file.open(s.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file"<< endl;
    }
    for (int row = 0;!input_file.eof();row++){
        input_file >> index >> x >> y;
        cout<< index<<": "<< x <<","<< y << endl;
        if(index == 1000)
            break;
    }
    input_file.close();
    return 0;
}


