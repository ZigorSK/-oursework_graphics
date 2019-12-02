#pragma once
#include"Paralel.h"
class ControllerOfParall
{
	Paralel par1, par2;

public:
	ControllerOfParall() : par1(0), par2(1) {};

	int menu();
	void menu_par(Paralel &par, Paralel &par2);
};