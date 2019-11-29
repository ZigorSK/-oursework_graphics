 #include "Paralel.h"


Paralel::Paralel(int flag)//Конструктор для инициализации вершин паралелипипедов(Инициализируется константными значениями)
{
	array_of_paint_pixel = new bool *[770];
	for (int i = 0; i < 770; i++)
	{
		array_of_paint_pixel[i] = new bool[1370];
		for (int j = 0; j < 1370; j++)
			array_of_paint_pixel[i][j] = false;//Изначатьно все не закрашены*/
	}

	for (int i = 0; i < 6; i++)
	{
		mull_equ_and_light[i] = 0;
		mull_equ_and_observer[i] = 0;
	}

	if (flag == 0)
	{
		A[0][0] = 100;
		A[0][1] = 150;
		A[0][2] = 10;
		A[0][3] = 1;

		A[1][0] = 200;
		A[1][1] = 150;
		A[1][2] = 10;
		A[1][3] = 1;

		A[2][0] = 200;
		A[2][1] = 250;
		A[2][2] = 10;
		A[2][3] = 1;

		A[3][0] = 0 + 100;
		A[3][1] = 100 + 150;
		A[3][2] = 10;
		A[3][3] = 1;

		A[4][0] = 0 + 150;
		A[4][1] = 0 + 200;
		A[4][2] = 150;
		A[4][3] = 1;

		A[5][0] = 100 + 150;
		A[5][1] = 0 + 200;
		A[5][2] = 150;
		A[5][3] = 1;

		A[6][0] = 100 + 150;
		A[6][1] = 100 + 200;
		A[6][2] = 150;
		A[6][3] = 1;

		A[7][0] = 0 + 150;
		A[7][1] = 100 + 200;
		A[7][2] = 150;
		A[7][3] = 1;
	}
	else
	{
		A[0][0] = 0 + 100 + 300;
		A[0][1] = 0 + 150;
		A[0][2] = 0;
		A[0][3] = 1;

		A[1][0] = 100 + 100 + 300;
		A[1][1] = 0 + 150;
		A[1][2] = 0;
		A[1][3] = 1;

		A[2][0] = 100 + 100 + 300;
		A[2][1] = 100 + 150;
		A[2][2] = 0;
		A[2][3] = 1;

		A[3][0] = 0 + 100 + 300;
		A[3][1] = 100 + 150;
		A[3][2] = 0;
		A[3][3] = 1;

		A[4][0] = 0 + 150 + 300;
		A[4][1] = 0 + 200;
		A[4][2] = 150;
		A[4][3] = 1;

		A[5][0] = 100 + 150 + 300;
		A[5][1] = 0 + 200;
		A[5][2] = 150;
		A[5][3] = 1;

		A[6][0] = 100 + 150 + 300;
		A[6][1] = 100 + 200;
		A[6][2] = 150;
		A[6][3] = 1;

		A[7][0] = 0 + 150 + 300;
		A[7][1] = 100 + 200;
		A[7][2] = 150;
		A[7][3] = 1;
	}
	float a = 0, b = 0, c = 0;
	for (int i = 0; i < 7; i++)
	{
		a += A[i][0];
		b += A[i][1];
		c += A[i][2];
	}
	a /= 8;
	b /= 8;
	c /= 8;

	center[0] = a;
	center[1] = b;
	center[2] = c;

	//vector of observer in infinity
	observer[0] = 0 ;//x
	observer[1] = 0 ;//y
	observer[2] = 2000  ;//z
	observer[3] = 0;

	//vector of light in infinity
	light[0] = 0 ;//x
	light[1] = 10000;//y
	light[2] = 0;//z
	light[3] = 0;

	//set_floor
	y_floor = 500;
}

Paralel::Paralel(const Paralel & F)
{
	for (int i = 0; i < 8; i++)
		for(int j = 0; j < 4; j++)
			A[i][0] = F.A[i][0];
}

Paralel & Paralel::operator=(Paralel & f)
{
	for (int i = 0; i < 8; i++)
		for(int j = 0; j < 4; j++)
		A[i][j] = f.A[i][j];

	return *this;
}

Paralel & Paralel::operator*(Cmat & Bb)
{
	// mull of matrix of A[8][4] to matrix of Bb.b[4][4]

	double tmp[8][4];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = (A[i][0] * Bb.B[j][0] + A[i][1] * Bb.B[j][1] + A[i][2] * Bb.B[j][2] + A[i][3] * Bb.B[j][3]);
		
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			A[i][j] = tmp[i][j];
	
	return *this;
}

Paralel::~Paralel()
{
	for (int i = 0; i < 770; i++)
		delete[] array_of_paint_pixel[i];

	delete[] array_of_paint_pixel;
}

void Paralel::drow_line(float x1, float y1, float x2, float y2, int color_1, int color_2, int color_3)
{
	HWND sHwnd = GetForegroundWindow();
	HDC hdc = GetDC(sHwnd);
	
	int B[2][3] = { {round(x1),round(y1),1} ,{round(x2),round(y2), 1} };

	int dx = abs(B[0][0] - B[1][0]);
	int dy = abs(B[0][1] - B[1][1]);
	int sx = B[0][0] < B[1][0] ? 1 : -1;
	int sy = B[0][1] < B[1][1] ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	double e2 = err;

	while (1)
	{
		SetPixel(hdc, B[0][0], B[0][1], RGB(color_1, color_2, color_3));
		if ((color_1 || color_2 || color_3) == 0)
		{
			array_of_paint_pixel[B[0][1]][B[0][0]] = false;
		}
		else
		{
			array_of_paint_pixel[B[0][1]][B[0][0]] = true;
		}

		if (B[0][0] == B[1][0] && B[0][1] == B[1][1]) break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy; B[0][0] += sx;
		}

		if (e2 < dy)
		{
			err += dx; B[0][1] += sy;
		}
	}

	ReleaseDC(sHwnd, hdc);
}

void Paralel::del_invisible_line()
{
	//получим матрицу уравнений плоскостей граней
	equation_of_flat(0, 0, 1, 3);// грань из точек 0-1-2-3
	equation_of_flat(1, 6, 5, 7);// грань из точек 4-5-6-7
	equation_of_flat(2, 0, 4, 1);// грань из точек 0-1-5-4
	equation_of_flat(3, 1, 5, 2);// грань из точек 5-1-2-6
	equation_of_flat(4, 2, 6, 3);// грань из точек 6-2-3-7
	equation_of_flat(5, 3, 7, 0);// грань из точек 7-3-0-4
	//Проверка через точку, лежащую в центре параллелепипеда
	float try_arr[4] = { center[0], center[1], center[2], 1 };
	float sum = 0;
	for (int i = 0; i < 6; i++)
	{
		sum = 0;
		for (int j = 0; j < 4; j++)
		{
			sum += try_arr[j] * Matr_of_flat_equation[j][i];
		}
		if (sum > 0)// Следует домножить всё уравнение на -1
		{
			for (int j = 0; j <4; j++)
			{
				Matr_of_flat_equation[j][i] *= -1;
			}
		}
	}
	

	//

	
	for (int i = 0; i < 6; i++)
	{
		mull_equ_and_light[i] = 0;
		mull_equ_and_observer[i] = 0;

		for (int j = 0; j < 4; j++)
		{
			mull_equ_and_observer[i] += Matr_of_flat_equation[j][i] * observer[j];
			mull_equ_and_light[i] += Matr_of_flat_equation[j][i] * light[j];
		}
	}

	
/*	for (int i = 0; i < 4; i++)
	{
		cout << "  " << observer[i] << "   "<< light[i]<<endl;
	}
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << "  " << Matr_of_flat_equation[j][i] << "   ";
		}
		cout << endl;
	}
	system("pause");
	for (int i = 0; i < 6; i++)
	{
		cout << i << "  " << mull_equ_and_observer[i] <<"   "<< mull_equ_and_light[i]<<endl;
	}
	system("pause");
	*/
}

void Paralel::equation_of_flat(int num_of_flat, int T1, int T2, int T3)
{
	float x1 = A[T1][0], x2 = A[T2][0], x3 = A[T3][0], y1 = A[T1][1], y2 = A[T2][1], y3 = A[T3][1], z1 = A[T1][2], z2 = A[T2][2], z3 = A[T3][2];

	float v[3] = {x2 - x1, y2 - y1, z2 - z1};
	float w[3] = {x3 - x1, y3 - y1, z3 - z1};
	Matr_of_flat_equation[0][num_of_flat] = (v[1] * w[2] - v[2] * w[1]);   //Находим коэфф А
	Matr_of_flat_equation[1][num_of_flat] = (v[2] * w[0] - v[0] * w[2]);   //Находим коэфф B
	Matr_of_flat_equation[2][num_of_flat] = (v[0] * w[1] - v[1] * w[0]);   //Находим коэфф C
	Matr_of_flat_equation[3][num_of_flat] = -x1 * Matr_of_flat_equation[0][num_of_flat] - y1 * Matr_of_flat_equation[1][num_of_flat] - z1 * Matr_of_flat_equation[2][num_of_flat]; //Находим коэфф C
	
	for (int i = 0; i < 4; i++)
	{
		Matr_of_flat_equation[i][num_of_flat] = Matr_of_flat_equation[i][num_of_flat] / Matr_of_flat_equation[3][num_of_flat];
	}
}

void Paralel::drow(int flag)// flag = 1 -рисуем flag = -1 -стираем
{
	int color1 = 0, color2 = 0, color3 = 0;
	// грань из точек 0-1-2-3
	del_invisible_line();// Вычисление удаляемых и теневых плоскостей

	//Рисование основной фигуры:

	//Цвет  не затенённой грани  - 0   200 0
	//Цвет не затенённой заливки - 200 200 0
	//Цвет  затенённой грани -     50  50  50
	//Цвет затенённой заливки -    128 128 128

	//Центральная проекция
	float L[8][2], zk = observer[2], zm = 500;//Задание данных кординат подобрано вручную zk - расстояние до глаза в пикселях ^_^ zm расстояние от 3-х ерного объекта до монитора

	for (int i = 0; i < 8; i++)
	{
		L[i][0] = A[i][0] * (zk - zm) / (zk - A[i][2]);
		L[i][1] = A[i][1] * (zk - zm) / (zk - A[i][2]);
	}

	//Сделать заливку
	// грань из точек 0-1-2-3-0
	if (mull_equ_and_observer[0] >= 0)
	{
		if (flag != -1)
		{
			if (mull_equ_and_light[0] >= 0)//Не в тени
			{
				color1 = 0;
				color2 = 200;
				color3 = 0;
				flag = 1;
			}
			else
			{
				color1 = 50;
				color2 = 50;
				color3 = 50;
				flag = 0;
			}
		}

		drow_line(L[0][0], L[0][1], L[1][0], L[1][1], color1, color2, color3);//0 - 1
		drow_line(L[1][0], L[1][1], L[2][0], L[2][1], color1, color2, color3);//1 - 2
		drow_line(L[2][0], L[2][1], L[3][0], L[3][1], color1, color2, color3);//2 - 3
		drow_line(L[3][0], L[3][1], L[0][0], L[0][1], color1, color2, color3);//3 - 0

		fill((L[0][0] + L[1][0] + L[2][0] + L[3][0]) / 4, (L[0][1] + L[1][1] + L[2][1] + L[3][1] / 4), flag);
	}

	// грань из точек 4-5-6-7
	if (mull_equ_and_observer[1] >= 0)
	{
		if (flag != -1)
		{
			if (mull_equ_and_light[1] >= 0)//Не в тени
			{
				color1 = 0;
				color2 = 200;
				color3 = 0;
				flag = 1;
			}
			else
			{
				color1 = 50;
				color2 = 50;
				color3 = 50;
				flag = 0;
			}
		}

		drow_line(L[4][0], L[4][1], L[5][0], L[5][1], color1, color2, color3);//4 - 5
		drow_line(L[5][0], L[5][1], L[6][0], L[6][1], color1, color2, color3);//5 - 6
		drow_line(L[6][0], L[6][1], L[7][0], L[7][1], color1, color2, color3);//6 - 7
		drow_line(L[7][0], L[7][1], L[4][0], L[4][1], color1, color2, color3);//7 - 4
		
		fill((L[4][0] + L[5][0] + L[6][0] + L[7][0]) / 4, (L[4][1] + L[5][1] + L[6][1] + L[7][1] / 4), flag);
	}

	// грань из точек 0-1-5-4
	if (mull_equ_and_observer[2] >= 0)
	{
		if (flag != -1)
		{
			if (mull_equ_and_light[2] >= 0)//Не в тени
			{
				color1 = 0;
				color2 = 200;
				color3 = 0;
				flag = 1;
			}
			else
			{
				color1 = 50;
				color2 = 50;
				color3 = 50;
				flag = 0;
			}
		}

		drow_line(L[0][0], L[0][1], L[1][0], L[1][1], color1, color2, color3);//0 - 1
		drow_line(L[1][0], L[1][1], L[5][0], L[5][1], color1, color2, color3);//1 - 5
		drow_line(L[5][0], L[5][1], L[4][0], L[4][1], color1, color2, color3);//5 - 3
		drow_line(L[4][0], L[4][1], L[0][0], L[0][1], color1, color2, color3);//4 - 0
		
		fill((L[0][0] + L[1][0] + L[5][0] + L[4][0]) / 4, (L[0][1] + L[1][1] + L[5][1] + L[4][1] / 4), flag);
	}

	// грань из точек 5-1-2-6
	if (mull_equ_and_observer[3] >= 0)
	{
		if (flag != -1)
		{
			if (mull_equ_and_light[3] >= 0)//Не в тени
			{
				color1 = 0;
				color2 = 200;
				color3 = 0;
				flag = 1;
			}
			else
			{
				color1 = 50;
				color2 = 50;
				color3 = 50;
				flag = 0;
			}
		}

		drow_line(L[5][0], L[5][1], L[1][0], L[1][1], color1, color2, color3);//5 - 1
		drow_line(L[1][0], L[1][1], L[2][0], L[2][1], color1, color2, color3);//1 - 2
		drow_line(L[2][0], L[2][1], L[6][0], L[6][1], color1, color2, color3);//2 - 6
		drow_line(L[6][0], L[6][1], L[5][0], L[5][1], color1, color2, color3);//6 - 5
		
		fill((L[5][0] + L[1][0] + L[2][0] + L[6][0]) / 4, (L[5][1] + L[1][1] + L[2][1] + L[6][1] / 4), flag);
	}

	// грань из точек 6-2-3-7
	if (mull_equ_and_observer[4] >= 0)
	{
		if (flag != -1)
		{
			if (mull_equ_and_light[4] >= 0)//Не в тени
			{
				color1 = 0;
				color2 = 200;
				color3 = 0;
				flag = 1;
			}
			else
			{
				color1 = 50;
				color2 = 50;
				color3 = 50;
				flag = 0;
			}
		}

		drow_line(L[6][0], L[6][1], L[2][0], L[2][1], color1, color2, color3);//6 - 2
		drow_line(L[2][0], L[2][1], L[3][0], L[3][1], color1, color2, color3);//2 - 3 
		drow_line(L[3][0], L[3][1], L[7][0], L[7][1], color1, color2, color3);//3 - 7
		drow_line(L[7][0], L[7][1], L[6][0], L[6][1], color1, color2, color3);//7 - 6

		fill((L[6][0] + L[2][0] + L[3][0] + L[7][0]) / 4, (L[6][1] + L[2][1] + L[3][1] + L[7][1] / 4), flag);
	}

	// грань из точек 7-3-0-4
	if (mull_equ_and_observer[5] >= 0)
	{
		if (flag != -1)
		{
			if (mull_equ_and_light[5] >= 0)//Не в тени
			{
				color1 = 0;
				color2 = 200;
				color3 = 0;
				flag = 1;
			}
			else
			{
				color1 = 50;
				color2 = 50;
				color3 = 50;
				flag = 0;
			}
		}

		drow_line(L[7][0], L[7][1], L[3][0], L[3][1], color1, color2, color3);//7 - 3
		drow_line(L[3][0], L[3][1], L[0][0], L[0][1], color1, color2, color3);//3 - 0
		drow_line(L[0][0], L[0][1], L[4][0], L[4][1], color1, color2, color3);//0 - 4
		drow_line(L[4][0], L[4][1], L[7][0], L[7][1], color1, color2, color3);//4 - 7

		fill((L[7][0] + L[3][0] + L[0][0] + L[4][0]) / 4, (L[7][1] + L[3][1] + L[0][1] + L[4][1] / 4), flag);
	}

	drow_shadow(flag);//Рисуем тень
}

void Paralel::fill(int x_pixel, int y_pixel, int flag)// Алгоритм построчного заполнения с затравкой (x_pixel, y_pixel) - ЗАтравочный пиксель
{
	stack <int> stack_obg;
	int color1 = 0, color2 = 0, color3 = 0;
	int x_left = 0, x_right = 0, x_now, y_now;
	bool choice_flag = true;

	if (flag == -1)
		choice_flag = false;
	
	if (flag ==  0)
	{
		color1 = color2 = color3 = 128;// color of shadow
	}
	else
	{
		if (flag == 1)
		{
			color1 = 200;
			color2 = 200;
			color3 = 0;
		}
	}

	stack_obg.push(x_pixel);// Помещаем в стек затравочный x_pixel
	stack_obg.push(y_pixel);//Помещаем в стек затравочный y_pixel

	HWND sHwnd = GetForegroundWindow();
	HDC hdc = GetDC(sHwnd);

	while (stack_obg.empty() != true)
	{
		//Извлекаем x и y с верхушки стэка
		y_now = stack_obg.top();
		stack_obg.pop();
		x_now = stack_obg.top();
		stack_obg.pop();

		//Для x_right
		x_right = x_now;

		while ((array_of_paint_pixel[y_now][x_right] != choice_flag) || (x_right == x_now))
		{

			array_of_paint_pixel[y_now][x_right] = choice_flag;
			SetPixel(hdc, x_right, y_now, RGB(color1, color2, color3));

			x_right++;
		}
		//Для x _left
		x_left = x_now;

		while ((array_of_paint_pixel[y_now][x_left] != choice_flag) || (x_left == x_now))
		{
			array_of_paint_pixel[y_now][x_left] = choice_flag;
			SetPixel(hdc, x_left, y_now, RGB(color1, color2, color3));
			x_left--;
		}
		x_left++;
		x_right--;

		//Проверка строки выше
		bool flag_1 = 0;
		int y = y_now + 1;

		for (int x = x_left; x < x_right; x++)
		{
			if (array_of_paint_pixel[y][x] != choice_flag)
			{
				flag_1 = 1;
			}

			if ((flag_1 == 1) && (array_of_paint_pixel[y][x + 1] == choice_flag))
			{
				//Помещаем данный пиксель в стэк
				stack_obg.push(x);// Помещаем в стек затравочный x_pixel
				stack_obg.push(y);//Помещаем в стек затравочный y_pixel

				flag_1 = 0;
			}
		}

		//Проверка строки ниже 
		y = y_now - 1;

		for (int x = x_left; x < x_right; x++)
		{
			if (array_of_paint_pixel[y][x] != choice_flag)
			{
				flag_1 = 1;
			}

			if ((flag_1 == 1) && (array_of_paint_pixel[y][x + 1] == choice_flag))
			{
				//Помещаем данный пиксель в стэк
				stack_obg.push(x);// Помещаем в стек затравочный x_pixel
				stack_obg.push(y);//Помещаем в стек затравочный y_pixel

				flag_1 = 0;
			}
		}
	}

	ReleaseDC(sHwnd, hdc);
}

void Paralel::drow_shadow(int flag)
{
	int color1 = 0, color2 = 0, color3 = 0;

	if (flag != -1)
	{
		color1 = color2 = color3 = 128;
	}
	else
	{
		flag = 0;
	}


	int xl = light[0], yl = light[1], zl = light[2];
	int xp = 0, yp = 0, zp = 0;
	//dot_of_shadow[8][4]
	//Взять проекцую  точек на плоскость пола
	for (int i = 0; i < 8; i++)
	{
		xp = A[i][0];
		yp = A[i][1];
		zp = A[i][2];

		dot_of_shadow[i][0] = (xl*yp - xp*yl)/(yp-yl);//xs
		dot_of_shadow[i][1] = y_floor;//ys
		dot_of_shadow[i][2] = (zl*yp -zp*yl)/(yp - yl);//zs
		dot_of_shadow[i][3] = 1;
	}

	//Рисование и заливка тени
	//Цвет  128 128 128

	float L[8][2], zk = observer[2], zm = 500;//Задание данных кординат подобрано вручную zk - расстояние до глаза в пикселях ^_^ zm расстояние от 3-х ерного объекта до монитора
	
	for (int i = 0; i < 8; i++)
	{
		L[i][0] = dot_of_shadow[i][0] * (zk - zm) / (zk - dot_of_shadow[i][2]);
		L[i][1] = dot_of_shadow[i][1] * (zk - zm) / (zk - dot_of_shadow[i][2]);

	}
	//Сделать заливку
	// грань из точек 0-1-2-3-0
	drow_line(L[0][0], L[0][1], L[1][0], L[1][1], color1, color2, color3);//0 - 1
	drow_line(L[1][0], L[1][1], L[2][0], L[2][1], color1, color2, color3);//1 - 2
	drow_line(L[2][0], L[2][1], L[3][0], L[3][1], color1, color2, color3);//2 - 3
	drow_line(L[3][0], L[3][1], L[0][0], L[0][1], color1, color2, color3);//3 - 0

	// грань из точек 4-5-6-7
	drow_line(L[4][0], L[4][1], L[5][0], L[5][1], color1, color2, color3);//4 - 5
	drow_line(L[5][0], L[5][1], L[6][0], L[6][1], color1, color2, color3);//5 - 6
	drow_line(L[6][0], L[6][1], L[7][0], L[7][1], color1, color2, color3);//6 - 7
	drow_line(L[7][0], L[7][1], L[4][0], L[4][1], color1, color2, color3);//7 - 4

	// грань из точек 0-1-5-4
	drow_line(L[0][0], L[0][1], L[1][0], L[1][1], color1, color2, color3);//0 - 1
	drow_line(L[1][0], L[1][1], L[5][0], L[5][1], color1, color2, color3);//1 - 5
	drow_line(L[5][0], L[5][1], L[4][0], L[4][1], color1, color2, color3);//5 - 3
	drow_line(L[4][0], L[4][1], L[0][0], L[0][1], color1, color2, color3);//4 - 0

	// грань из точек 5-1-2-6
	drow_line(L[5][0], L[5][1], L[1][0], L[1][1], color1, color2, color3);//5 - 1
	drow_line(L[1][0], L[1][1], L[2][0], L[2][1], color1, color2, color3);//1 - 2
	drow_line(L[2][0], L[2][1], L[6][0], L[6][1], color1, color2, color3);//2 - 6
	drow_line(L[6][0], L[6][1], L[5][0], L[5][1], color1, color2, color3);//6 - 5

	// грань из точек 6-2-3-7
	drow_line(L[6][0], L[6][1], L[2][0], L[2][1], color1, color2, color3);//6 - 2
	drow_line(L[2][0], L[2][1], L[3][0], L[3][1], color1, color2, color3);//2 - 3 
	drow_line(L[3][0], L[3][1], L[7][0], L[7][1], color1, color2, color3);//3 - 7
	drow_line(L[7][0], L[7][1], L[6][0], L[6][1], color1, color2, color3);//7 - 6

	// грань из точек 7-3-0-4
	drow_line(L[7][0], L[7][1], L[3][0], L[3][1], color1, color2, color3);//7 - 4
	drow_line(L[3][0], L[3][1], L[0][0], L[0][1], color1, color2, color3);//4 - 0
	drow_line(L[0][0], L[0][1], L[4][0], L[4][1], color1, color2, color3);//0 - 4
	drow_line(L[4][0], L[4][1], L[7][0], L[7][1], color1, color2, color3);//4 - 7

	fill((L[0][0] + L[1][0] + L[2][0] + L[3][0]) / 4, (L[0][1] + L[1][1] + L[2][1] + L[3][1] / 4), flag);
	fill((L[4][0] + L[5][0] + L[6][0] + L[7][0]) / 4, (L[4][1] + L[5][1] + L[6][1] + L[7][1] / 4), flag);
	fill((L[0][0] + L[1][0] + L[5][0] + L[4][0]) / 4, (L[0][1] + L[1][1] + L[5][1] + L[4][1] / 4), flag);
	fill((L[5][0] + L[1][0] + L[2][0] + L[6][0]) / 4, (L[5][1] + L[1][1] + L[2][1] + L[6][1] / 4), flag);
	fill((L[6][0] + L[2][0] + L[3][0] + L[7][0]) / 4, (L[6][1] + L[2][1] + L[3][1] + L[7][1] / 4), flag);
	fill((L[7][0] + L[3][0] + L[0][0] + L[4][0]) / 4, (L[7][1] + L[3][1] + L[0][1] + L[4][1] / 4), flag);

}

int Paralel::menu()
{
	return 0;
}
