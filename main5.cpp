#include <iostream>
#include <iostream>

using namespace std;
// (5*c + 6*a – b*2)/(c + a/d);
int main()
{
    int error;
    double a, b, c, d;
    cout << "Please, enter a:\n";
    cin >> a;

    cout << "Please, enter b:\n";
    cin >> b;
    cout << "Please, enter c:\n";
    cin >> c;
    cout << "Please, enter d:\n";
    cin >> d;
    if (!d) {
        cout << "Do not try to divide by zero\n";
        system("pause");
        return -1;
    }
    if (c + a / d == 0) {
        cout << "Do not try to divide by zero\n";
        system("pause");
        return -1;
    }
    cout << "Result in integers (C++): " << (5 * c + 6 * a - b * 2) / (c + a / d) << endl;

    const double  c2 = 2.0, c5 = 5.0, c6 = 6.0;
    double chisl, del, res_asm;
    __asm {
            finit
            fld		qword ptr[c]	   //c
            fmul	qword ptr[c5]	   //st(1) = 5*a

            fld     qword ptr[a]	   //a
            fmul	qword ptr[c6]	   //st = 6*a

            faddp	st(1), st          //st(1) = 5*a + 6*a

            fld     qword ptr[b]       //b
            fmul	qword ptr[c2]	   //st = b*2

            fsubp	st(1), st          //st = 5*c + 6*a – b*2
            fstp    chisl              //числитель, освободили стек

            fld		qword ptr[c]		//c

            fld		qword ptr[a]		//a
            fld		qword ptr[d]		//d
            fldz						//Загрузка 0
            fucompp						//Вещественное сравнение с выталкиванием
            fnstsw ax					//Считать слово состояния сопроцессора в память
            sahf						//Записать содержимое AH в регистр FLAGS
            jz error_0					//Обработка ошибки "знаменатель равен 0"
            fdiv	qword ptr[d]		//st = a/d
            faddp	st(1), st			//st = c + a/d , st(1)-пусто
            fstp	del					// делитель, очистили стек

            fld		qword ptr[chisl]	//st(1) = 5*c + 6*a – b*2 -числитель
            fld		qword ptr[del]		//st = c + a/d - знаменатель
            fldz
            fucomp
            fnstsw ax
            sahf
            jz error_0
            fdivp	st(1), st			//st = (5*c + 6*a – b*2)/(c + a/d)

            fstp res_asm 				// res_asm = eax

            jmp EndOfCode				// move to перепрыгиваем по флагу

            error_0 :
            mov error, 1
            jmp EndOfCode

            EndOfCode :
    };

    if (error == 1) {		//errror_zf
        cout << "Do not try to divide by zero\n";
        system("pause»null");
        return 0;
    }

    cout << "Result in integers (asm): " << res_asm << endl;
    return 0;
}
