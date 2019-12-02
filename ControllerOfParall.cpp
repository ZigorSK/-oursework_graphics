#include "ControllerOfParall.h"

int ControllerOfParall::menu()
{
		Paralel paral_1(0), paral_2(1);//Создание обёкта 2 пар-дов, инициализация по умолчанию
		char choice = '0';

		
		
		do
		{
			system("cls");
			cout << "Please, pick a figure:" << endl << "[1] -Left." << endl << "[2] -Right." << endl << "[0] Exit from the programm." << endl;
			choice = _getch();

			if (choice == '1')//Меню первого параллелепипеда
				menu_par(par1, par2);
			
			if (choice == '2')//Меню второго параллелепипеда
				menu_par(par2, par1);

		} while (choice != '0');
		return 0;
}

void ControllerOfParall::menu_par(Paralel & obg, Paralel &par)
{

	system("chcp 1251");
	char choice = '0';
	do
	{
		system("cls");
		par.drow();
		obg.drow();
		
		
		choice = _getch();

		switch (choice)
		{
		case '6'://сдвиг вправо по х - 6
			obg.move(6);
			break;

		case '4'://Сдвиг влево по х - 4
			obg.move(4);
			break;

		case '2'://Сдвиг сдвиг вверх по у - 2
			obg.move(2);
			break;

		case '8'://Сдвиг вних по у - 8
			obg.move(8);
			break;

		case '7'://сдвиг от экрана по z - 7
			obg.move(7);
			break;

		case '9'://сдвиг к экрану по z - 9
			obg.move(9);
			break;

		case '-'://Уменьшить - -
			obg.scale(1);
			break;

		case '+'://увеличить -+
			obg.scale(3);
			break;

			//
		case 'w'://Вращать вокруг х против часовой
			obg.roat(1, 0);
			break;
		case 's'://Вращать вокруг х по часовой
			obg.roat(1, 1);
			break;
		case 'a'://Вращать вокруг y по часовой
			obg.roat(2, 0);
			break;
		case 'd'://Вращать вокруг y против часовой
			obg.roat(2, 1);
			break;
		case 'q'://Вращать вокруг z против часовой
			obg.roat(3, 0);
			break;
		case 'e'://Вращать вокруг z по часовой
			obg.roat(3, 1);
			break;
		default: break;
		}

	} while (choice != '0');	
	
}
