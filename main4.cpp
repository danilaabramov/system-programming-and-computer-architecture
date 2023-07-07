#include <iostream>
#include <algorithm>

//Найти минимальный элемент в массиве A={a[i]} и подсчитать количество его вхождений
using namespace std;
int main()
{
    int res = 1;
    int arr[5] = { 2, -5, -1, -5, 1};
    int n = 5;
    int A = *arr;
    for (int i = 1; i < n; ++i) {
        if (A == arr[i]) ++res;
        if (arr[i] < A) {
            A = arr[i];
            res = 1;
        }
    }
    cout << "res c++: " << A << " " << res << endl;
    int error;
    int res_asm;
    int res_asm2 = 1;
    __asm {
            xor esi, esi
            xor edi, edi
            mov ecx, n

            mov	ebx, arr[esi * 4]
            mov res_asm, ebx
            inc	esi
            dec ecx

            mov edx, res_asm2

            begin_loop :
            mov	eax, arr[esi * 4]
            cmp	eax, ebx
            je ravno
            jmp neravno;

            ravno:
            add edx, 1
            mov  res_asm2, edx

            neravno:
            cmp eax, ebx
            jge loop_end

            mov ebx, eax
            mov res_asm, eax

            mov edx, 1
            mov res_asm2, 1


            loop_end:
            inc	esi				// переходим к следующему элементу
            loop begin_loop		// повторяем цикл для всех элементов массива
    }

    cout << "res asm: " << res_asm << " " << res_asm2 << endl;
    system("pause");
    return 0;
}
