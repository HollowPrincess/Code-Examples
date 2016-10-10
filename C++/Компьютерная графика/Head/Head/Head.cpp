// Head.cpp: определяет точку входа для консольного приложения.
//

#include <fstream>
#include "tgaimage.h"
#include <iostream>
#include "string"
#include <vector>
using namespace std;
const TGAColor white = TGAColor(255, 255, 255, 255);

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
void line(vector <int> &xx, vector <int> &yy, int sizeXX, int sizeYY, int num1, int num2, TGAImage& image, TGAColor somecolor) {
	if (num1 <= sizeXX && num2 <= sizeXX && num1 <= sizeYY && num2 <= sizeYY) {
		if (xx[num1 - 1] >= 0 && xx[num2 - 1] >= 0 && xx[num1 - 1] <= 2500 && xx[num2 - 1] <= 2500, yy[num1 - 1] >= 0 && yy[num2 - 1] >= 0 && yy[num1 - 1] <= 2500 && yy[num2 - 1] <= 2500) {
			int x1 = xx[num1 - 1];
			int y1 = yy[num1 - 1];
			int x2 = xx[num2 - 1];
			int y2 = yy[num2 - 1];
			//newFile << endl << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
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
				if (dx > dy) {
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
			};
		};
	};
}

void tringle(vector <int> &x, vector <int> &y, int &sizeX, int &sizeY, TGAImage &image, TGAColor somecolor, int *array, const int len = 3) {
	int num1;
	int num2;
	for (int count = 0; count < 3; count++) {
		num1 = array[count];
		num2 = array[(count + 1) % 3];
		line(x, y, sizeX, sizeY, num1, num2, image, somecolor);
		//newFile << num1 << " " << num2;
	}

}


int main() {
	TGAImage image(2000, 2000, TGAImage::RGB);
	string someStr;
	string foundStr = "";
	vector <int> v1;
	vector <int> v2;
	int sizeX;
	int sizeY;
	int array[3];

	ifstream file;
	file.open("C:\\Users\\User\\Documents\\Visual Studio 2015\\Projects\\Head\\Head\\african_head.obj", ios::in);
	//ofstream newFile("output1.txt");
	if (file) {
		while (!file.eof()) {
			getline(file, someStr);

			if (someStr[0] == 'v') {
				int i = 2;
				while (someStr[i] != ' ') {
					foundStr += someStr[i];
					i++;
				};
				v1.push_back((int)1000 * (stof(foundStr)) + 1000);
				foundStr = "";
				i++;
				while (someStr[i] != ' ') {
					foundStr += someStr[i];
					i++;
				};
				v2.push_back((int)1000 * stof(foundStr) + 1000);
				i++;

			};
			foundStr = "";
			if (someStr[0] == 'f') {
				int i = 2;

				for (int count = 0; count < 3; count++) {
					while (someStr[i] != '/') {
						foundStr += someStr[i];
						i++;
					};
					array[count] = (int)(stof(foundStr));
					foundStr = "";
					if (count != 2) {
						while (someStr[i] != ' ') {
							i++;
						};
						i++;
					};
				};
				sizeX = v1.size();
				sizeY = v2.size();

				tringle(v1, v2, sizeX, sizeY, image, white, array);
			};
		};
	}




	image.flip_vertically();
	image.write_tga_file("output.tga");
	file.close();
	return 0;
}