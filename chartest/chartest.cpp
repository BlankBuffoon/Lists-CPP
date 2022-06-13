#include <iostream>
#include <Windows.h>
#include <cstdio>

using namespace std;

int main()
{
    //setlocale(0, "");
    /*for (int i = 0; i <= 255; i++) {
        cout << "Код: " << i << " Символ: " << (char)i << endl;
    }*/

    //SetConsoleCP(65001);
    //SetConsoleOutputCP(65001);

    SetConsoleCP(1251);
    SetConsoleOutputCP(65001);

    const string str = u8"\u250C\u2500";
    const string ch_ver_spa = u8"\u2502 ", ch_udia_hor = u8"\u2514\u2500", ch_ver_hor = u8"\u251C\u2500";

    cout << "Привет РУС!\n";

    cout << "|\t" << endl;
    cout << str << endl;
    cout << ch_ver_spa << endl;
    cout << ch_udia_hor << endl;
    cout << ch_ver_hor << endl;
}
