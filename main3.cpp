#include <iostream>
#include <windows.h>
#include <tchar.h>
using namespace std;

/*
	(b + 5)/a + 2, a>b
x = -b,		 a=b
	(a-b)/3, a<b
*/


int main()
{

    int error;
    int a, b, res, res_asm;
    cout << "Please, enter a: ";
    cin >> a;
    cout << "Please, enter b: ";
    cin >> b;
    if (a > b && a == 0) {
        cout << "Do not try to divide by zero\n";
        system("pause");
        return -1;
    }

    if (a > b) {
        res = (b + 5) / a + 2;
    }
    else if (a == b) {
        res = -b;
    }
    else {
        res = (a - b) / 3;
    }

    __asm {

            mov	eax, a;		 eax = a
            mov	ebx, b;		 ebx = b
            cmp	eax, ebx;	 сравнение a и b
            jg	l_bigger;	 переход если a > b
            jl	l_smaller;	 переход если a < b
            neg ebx;         ebx = -b
            mov res_asm, ebx; res_asm = -b
            jmp EndOfCode; переход на конец программы

            l_bigger :
            mov	eax, b;      eax = b
            mov	ebx, a;      ebx = a
            jo error_of
            add eax, 5;      eax = b + 5
            cmp ebx, 0; сравнение a и 0

            cdq;
            je error_zf; ошибка деление на ноль
            idiv ebx;    eax = (b + 5) / a
            jo error_of
            add eax, 2;  eax = (b + 5) / a + 2
            mov res_asm, eax; res_asm = (b + 5) / a + 2
            jmp EndOfCode; переход на конец программы

            l_smaller :
            sub eax, ebx; eax = a - b
            mov ebx, 3; ebx = 3
            cdq
            je error_zf; ошибка деление на ноль
            idiv ebx; eax = (a - b) / 3
            mov res_asm, eax; res_asm = (a - b) / 3
            jmp EndOfCode

            error_zf :
            mov error, 1
            jmp EndOfCode

            error_of :
            mov error, 2
            jmp EndOfCode

            EndOfCode :
    }

    if (error == 1) {		//errror_zf
        cout << "Do not try to divide by zero\n";
        system("pause");
        return 0;
    }

    if (error == 2) {			//error_of
        cout << "Too big quotient\n";
        system("pause");
        return 0;
    }

    cout << "res c++ : " << res << endl;
    cout << "res asm : " << res_asm << endl;
    system("pause");
    return 0;
}