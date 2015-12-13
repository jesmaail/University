// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>

using namespace std;

struct rgbValue{
	int r;
	int g;
	int b;
};

rgbValue rgbTable[255];
int grayscale[255];

rgbValue hextorgb(string hex){
	rgbValue rgb;
	int* rgbTemp = new int[3];
	std::stringstream ss;
	string str;

	if (hex[0] == '#'){
		hex.erase(0, 1);
	}
	int size = hex.size();

	for (int i = 0; i < 3; i++){
		str = hex.substr(i * 2, 2);

		ss << std::hex << str;
		ss >> rgbTemp[i];
		ss.clear();
	}
	rgb.r = rgbTemp[0];
	rgb.g = rgbTemp[1];
	rgb.b = rgbTemp[2];

	return rgb;
}

int colToGray(rgbValue colour){
	int red, green, blue, gray;
	red = 0.21 * colour.r;
	green = 0.72 * colour.g;
	blue = 0.07 * colour.b;
	gray = red + green + blue;

	return gray;
}

void createTable(){
	string hexCols [8][16] = {
		{"#000000", "#444400", "#702800", "#841800", "#880000", "#78005C", "#480078", "#140084", "#000088", "#00187C", "#002C5C", "#003C2C", "#003C00", "#143800", "#2C3000", "#442800"},
		{"#404040", "#646410", "#844414", "#983418", "#9C2020", "#8C2074", "#602090", "#302098", "#1C209C", "#1C3890", "#1C4C78", "#1C5C48", "#205C20", "#345C1C", "#4C501C", "#644818"},
		{"#6C6C6C", "#848424", "#985C28", "#AC5030", "#B03C3C", "#A03C88", "#783CA4", "#4C3CAC", "#3840B0", "#3854A8", "#386890", "#387C64", "#407C40", "#507C38", "#687034", "#846830"},
		{"#909090", "#A0A034", "#AC783C", "#C06848", "#C05858", "#B0589C", "#8C58B8", "#6858C0", "#505CC0", "#5070BC", "#5084AC", "#509C80", "#5C9C5C", "#6C9850", "#848C4C", "#A08444"},
		{"#B0B0B0", "#B8B840", "#BC8C4C", "#D0805C", "#D07070", "#C070B0", "#A070CC", "#7C70D0", "#6874D0", "#6888CC", "#689CC0", "#68B494", "#74B474", "#84B468", "#9CA864", "#B89C58"},
		{"#C8C8C8", "#D0D050", "#CCA05C", "#E09470", "#E08888", "#D084C0", "#B484DC", "#9488E0", "#7C8CE0", "#7C9CDC", "#7CB4D4", "#7CD0AC", "#8CD08C", "#9CCC7C", "#B4C078", "#D0B46C"},
		{"#DCDCDC", "#E8E85C", "#DCB468", "#ECA880", "#ECA0A0", "#DC9CD0", "#C49CEC", "#A8A0EC", "#90A4EC", "#90B4EC", "#90CCE8", "#90E4C0", "#A4E4A4", "#B4E490", "#CCD488", "#E8CC7C"},
		{"#ECECEC", "#FCFC68", "#ECC878", "#FCBC94", "#FCB4B4", "#ECB0E0", "#D4B0FC", "#BCB4FC", "#A4B8FC", "#A4C8FC", "#A4E0FC", "#A4FCD4", "#B8FCB8", "#C8FCA4", "#E0EC9C", "#FCE08C"}
	};

	string hexColsCorrected[128];
	int c = 0;
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 8; j++){
			hexColsCorrected[c] = hexCols[j][i];
			c++;
		}
	}

	//this loop redundant, code below does it without needing rbgTable
	int x = 0;
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 8; j++){
			string hexToPass = hexColsCorrected[x / 2];
			rgbTable[x] = hextorgb(hexToPass);
			rgbTable[x+1] = hextorgb(hexToPass);
			x += 2;
		}
	}

	x = 0;
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 8; j++){
			string hexToPass = hexColsCorrected[x / 2];
			rgbValue tempCol = hextorgb(hexToPass);
			int grayVal = colToGray(tempCol);

			grayscale[x] = grayVal;
			grayscale[x + 1] = grayVal;
			x += 2;
		}
	}

}

int main(){
	int  x;
	createTable();
	rgbValue test = rgbTable[220];
	int gray = grayscale[220];
	cout << test.r << " " << test.g << " " << test.b << endl;
	cout << gray;
	cin >> x;
	return 0;
}