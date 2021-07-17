#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int main() {

    // Output a specific number of digits past the decimal point,
    // in this case 5    
    cout.setf(ios::fixed);
    cout << setprecision(5);
    cout << 100.0 / 7.0 << " " << 10.0 << endl; // 14.28571 10.00000
    cout.unsetf(ios::fixed);

    // Output a '+' before positive values
    cout.setf(ios::showpos);
    cout << 100 << " " << -100 << endl; // +100 -100
    cout.unsetf(ios::showpos);

    // Output numerical values in hexadecimal. Also works for oct
    cout << hex << 500 << dec << endl; // 1f4 (1*256 + 15*16 + 4*1)
    // Output numerical values in binary
    std::bitset<10> bs(500);
    cout << bs << endl; // 0111110100

    // Read until end of file.
    string line;
    getline(cin, line);
    while (!line.empty()) { // Input in CP problems always ends with an empty line.
        int intV; string stringV;
        stringstream line_stream(line);
        line_stream >> stringV >> intV; // Just read like usual from the stream
        getline(cin, line);
    }
}
