#include "ControllerOfParall.h"

int ControllerOfParall::menu()
{
		Paralel paral_1(0), paral_2(1);//�������� ����� 2 ���-���, ������������� �� ���������
		char choice = '0';

		
		
		do
		{
			system("cls");
			cout << "Please, pick a figure:" << endl << "[1] -Left." << endl << "[2] -Right." << endl << "[0] Exit from the programm." << endl;
			choice = _getch();

			if (choice == '1')//���� ������� ���������������
				menu_par(par1, par2);
			
			if (choice == '2')//���� ������� ���������������
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
		case '6'://����� ������ �� � - 6
			obg.move(6);
			break;

		case '4'://����� ����� �� � - 4
			obg.move(4);
			break;

		case '2'://����� ����� ����� �� � - 2
			obg.move(2);
			break;

		case '8'://����� ���� �� � - 8
			obg.move(8);
			break;

		case '7'://����� �� ������ �� z - 7
			obg.move(7);
			break;

		case '9'://����� � ������ �� z - 9
			obg.move(9);
			break;

		case '-'://��������� - -
			obg.scale(1);
			break;

		case '+'://��������� -+
			obg.scale(3);
			break;

			//
		case 'w'://������� ������ � ������ �������
			obg.roat(1, 0);
			break;
		case 's'://������� ������ � �� �������
			obg.roat(1, 1);
			break;
		case 'a'://������� ������ y �� �������
			obg.roat(2, 0);
			break;
		case 'd'://������� ������ y ������ �������
			obg.roat(2, 1);
			break;
		case 'q'://������� ������ z ������ �������
			obg.roat(3, 0);
			break;
		case 'e'://������� ������ z �� �������
			obg.roat(3, 1);
			break;
		default: break;
		}

	} while (choice != '0');	
	
}
