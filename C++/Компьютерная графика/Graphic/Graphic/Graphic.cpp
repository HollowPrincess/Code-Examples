#include "tgaimage.h"
#include "math.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

//границы поля вывода
const int borderTop = 200;
const int borderBottom = 100;
const int borderLeft = 100;
const int borderRight = 200;
//отсечения отрезков
int code(int x, int y) {
	int code = 0;
	if (x<borderLeft) { code += 1; }
	else if (x>borderRight) { code += 2; };

	if (y<borderBottom) { code += 4; }
	else if (y>borderTop) { code += 8; };

	return code;
}
void changeAB(int* A, int* B, const int len = 2) {
	int buff[2];
	for (int i = 0; i<len; i++) {
		buff[i] = A[i];
	};

	for (int i = 0; i<len; i++) {
		A[i] = B[i];
	};
	for (int i = 0; i<len; i++) {
		B[i] = buff[i];
	};

}
void CohenSutherland(int& x1, int& y1, int& x2, int& y2) {
	int A[2] = { x1,y1 };
	int B[2] = { x2,y2 };
	int codeA = code(x1, y1);
	int codeB = code(x2, y2);
	while ((codeA | codeB) && (!(codeA&codeB))) {
		if (codeA == 0) {
			changeAB(A, B);
			codeA += codeB;
			codeB = abs(codeA - codeB);
			codeA += codeB;
		};

		if (codeA & 1) {
			A[1] += ceil((B[1] - A[1])*(borderLeft - A[0]) / (B[0] - A[0]));
			A[0] = borderLeft;
			codeA -= 1;
		}
		else if (codeA & 2) {
			A[1] += ceil((B[1] - A[1])*(borderRight - A[0]) / (B[0] - A[0]));
			A[0] = borderRight;
			codeA -= 2;
		}
		else if (codeA & 4) {
			A[0] += (B[0] - A[0])*(borderBottom - A[1]) / (B[1] - A[1]);
			A[1] = borderBottom;
			codeA -= 4;
		}
		else if (codeA & 8) {
			A[0] += (B[0] - A[0])*(borderTop - A[1]) / (B[1] - A[1]);
			A[1] = borderTop;
			codeA -= 8;
		}
	}

	x2 = A[0];
	y2 = A[1];
	x1 = B[0];
	y1 = B[1];
}

//отрисовка отрезка

void BrezenghemLineI(int d1, int d2, int some1, int some2, int limit, TGAImage &image, TGAColor somecolor) {
	int d = 2 * d2 - d1;
	do {
		image.set(some1, some2, somecolor);
		if (d<0)
			d += 2 * d2;
		else {
			d += 2 * (d2 - d1);
			some2++;
		}
		++some1;
	} while (some1 <= limit);

}
void BrezenghemLineIy(int d1, int d2, int some1, int some2, int limit, TGAImage &image, TGAColor somecolor) {
	int d = 2 * d2 - d1;
	do {
		image.set(some2, some1, somecolor);
		if (d<0)
			d += 2 * d2;
		else {
			d += 2 * (d2 - d1);
			some2++;
		}
		++some1;
	} while (some1 <= limit);

}
void BrezenghemLineIV(int d1, int d2, int some1, int some2, int limit, TGAImage &image, TGAColor somecolor) {
	int d = 2 * d2 - d1;
	do {
		image.set(some1, some2, somecolor);
		if (d<0)
			d += 2 * d2;
		else {
			d += 2 * (d2 - d1);
			some2--;
		}
		++some1;
	} while (some1 <= limit);

}
void BrezenghemLineIVy(int d1, int d2, int some1, int some2, int limit, TGAImage &image, TGAColor somecolor) {
	int d = 2 * d2 - d1;
	do {
		image.set(some2, some1, somecolor);
		if (d<0)
			d += 2 * d2;
		else {
			d += 2 * (d2 - d1);
			some2--;
		}
		++some1;
	} while (some1 <= limit);

}
void checkLine(int &dx, int & dy, int &x1, int &x2, int &y1, int &y2) {
	int  buff;
	if (dx >= dy) {
		if (x2<x1) {
			buff = x1;
			x1 = x2;
			x2 = buff;
			buff = y1;
			y1 = y2;
			y2 = buff;
		};
	}
	else {
		if (y2<y1) {
			buff = y1;
			y1 = y2;
			y2 = buff;
			buff = x1;
			x1 = x2;
			x2 = buff;
		};
	};
}
void  line(int x1, int y1, int x2, int y2, TGAImage& image, TGAColor somecolor) {

	CohenSutherland(x1, y1, x2, y2);

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	checkLine(dx, dy, x1, x2, y1, y2);
	int x = x1;
	int y = y1;
	if (y1 <= y2 && x1 >= x2) {
		if (dx >= dy) {
			BrezenghemLineIV(dx, dy, x, y, x2, image, somecolor);
		}
		else {
			BrezenghemLineIVy(dy, dx, y, x, y2, image, somecolor);
		};
	}
	else if (y1 <= y2 && x1 < x2) {
		if (dx>dy) {
			BrezenghemLineI(dx, dy, x, y, x2, image, somecolor);
		}
		else {
			BrezenghemLineIy(dy, dx, y, x, y2, image, somecolor);
		};
	}
	else {
		if (dx >= dy) {
			BrezenghemLineIV(dx, dy, x, y, x2, image, somecolor);
		}
		else {
			BrezenghemLineIVy(dy, dx, y, x, y2, image, somecolor);
		};
	}

}


void borders(TGAImage &image) {
	line(borderLeft, borderBottom, borderRight, borderBottom, image, red);
	line(borderLeft, borderBottom, borderLeft, borderTop, image, red);
	line(borderLeft, borderTop, borderRight, borderTop, image, red);
	line(borderRight, borderTop, borderRight, borderBottom, image, red);
}


//отрисовка окружности
void circle_Pixel(int x0, int y0, int x, int y, TGAImage& image, TGAColor somecolor) {
	image.set(x0 + x, y0 + y, somecolor);
	image.set(x0 + x, y0 + y, somecolor);
	image.set(x0 + y, y0 + x, somecolor);
	image.set(x0 + y, y0 - x, somecolor);
	image.set(x0 + x, y0 - y, somecolor);
	image.set(x0 - x, y0 - y, somecolor);
	image.set(x0 - y, y0 - x, somecolor);
	image.set(x0 - y, y0 + x, somecolor);
	image.set(x0 - x, y0 + y, somecolor);
}
void circle(int x0, int y0, int R, TGAImage& image, TGAColor somecolor) {
	for (int x = 0; x <= R / sqrt(2); x++)
	{
		int y = (int)(sqrt(abs(R*R - x*x)));
		circle_Pixel(x0, y0, x, y, image, somecolor);
	};

}

//отрисовка треугольника
void tringle(TGAImage &image, TGAColor somecolor, int *arrayX, int *arrayY, const int len = 3) {
	int num1X;
	int num1Y;
	int num2X;
	int num2Y;
	for (int count = 0; count < 3; count++) {
		num1X = arrayX[count];
		num2X = arrayX[(count + 1) % 3];
		num1Y = arrayY[count];
		num2Y = arrayY[(count + 1) % 3];

		line(num1X, num1Y, num2X, num2Y, image, somecolor);
	}
}

//тесты
void approveLine(TGAImage &image) {
	//первая четверть dx>dy
	line(50, 50, 100, 75, image, red);
	//первая четверть dx<dy
	line(50, 50, 75, 100, image, red);
	//первая четверть dx=dy
	line(50, 50, 100, 100, image, white);

	//вторая четверть dx>dy
	line(0, 75, 50, 50, image, red);
	//вторая четверть dx<dy
	line(25, 100, 50, 50, image, red);
	//вторая четверть dx=dy
	line(0, 100, 50, 50, image, white);

	//третья четверть dx>dy
	line(0, 25, 50, 50, image, red);
	//третья четверть dx<dy
	line(25, 0, 50, 50, image, red);
	//третья четверть dx=dy
	line(0, 0, 50, 50, image, white);

	//четвертая четверть dx>dy
	line(100, 25, 50, 50, image, red);
	//четвертая четверть dx<dy
	line(50, 50, 75, 0, image, red);
	//четвертая четверть dx=dy
	line(100, 0, 50, 50, image, white);

	//границы четвертей
	line(0, 50, 50, 50, image, white);
	line(50, 0, 50, 50, image, white);
	line(50, 100, 50, 50, image, white);
	line(100, 50, 50, 50, image, white);
}

void testCutLine(TGAImage &image) {
	//line(150, 150, 50, 150, image, white); //0001
	//line(150, 150, 250, 150, image, red); //0010
	//line(150, 150, 150, 50, image, white); //0100
	//line(150, 150, 150, 250, image, red); //1000
	//line(150, 150, 50, 50, image, white); //0101
	//line(150, 150, 50, 250, image, red); //1001
	//line(150, 150, 250, 50, image, white); //0110
	//line(150, 150, 250, 250, image, red); //1010

	line(50, 50, 250, 250, image, white);
	line(75, 150, 150, 250, image, white);
	line(100, 225, 225, 125, image, white);

	borders(image);
}



int main(int argc, char** argv) {
	TGAImage image(300, 300, TGAImage::RGB);

	//line(31,30,15,10, image,red);
	//circle(50,50,49,image, red);	
	/*int arrayX[3]={15, 2, 31};
	int arrayY[3]={10, 20, 30};
	tringle(image, red, arrayX, arrayY);*/

	//approveLine(image);

	testCutLine(image);
	image.flip_vertically();
	image.write_tga_file("output.tga");

	return 0;
}