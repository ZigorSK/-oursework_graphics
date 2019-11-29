#pragma once
#include"Cmat.h"
#include<windows.h>
#include<cmath>
#include<iostream>
#include<stack>

using namespace std;

class Paralel
{
	float A[8][4];//ћатрица с точками параллелипипида

	bool **array_of_paint_pixel;// ћатрица закрашенных пиксилей true - закрашен, false - не закрашен

	float Matr_of_flat_equation[4][6];//ћатрица уравнений плоскости

	int mull_equ_and_light[6];// ћатрица произведений уравнений плоскости на вектор источника света
	int mull_equ_and_observer[6];//ћатрица произведений уравнений плоскости на вектор наблюдател€

	float dot_of_shadow[8][4];

	int observer[4];//“очка наблюдени€, задаЄтс€ в конструкторе
	int light[4];//“очка источника света(в бесконечности,типа =))), задаЄтс€ в конструкторе

	float center[3];

	int y_floor;
public:

	Paralel(int flag);

	Paralel(const Paralel & F);
	Paralel & operator=(Paralel & f);
	Paralel & operator*(Cmat & Bb);
	~Paralel();

	void drow_line(float x1, float y1, float x2, float y2, int color_1 = 0, int color_2 = 0, int color_3 = 0);//flag = 1 закрашиваем, 0 - стираем
	void del_invisible_line();
	void equation_of_flat(int num_of_flat, int T1, int T2, int T3);//num_of_flat - номер плоскости, куда будет выводитс€ результат, t1 t2 t3 пор€док точек в матрице ј
	void drow(int flag);
	void fill(int x_pixel, int y_pixel, int flag);// flag = -1 стираетс€, flag = 0 в тени, flag = 1 в цвете
	void drow_shadow(int flag);

	int menu();
};