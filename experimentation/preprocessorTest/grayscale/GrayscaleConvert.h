#include <iostream>
#include <sstream>

using namespace std;

struct rgbValue{
	int r;
	int g;
	int b;
};

class gsConvert{
private:
	/*const string hexCols[8][16] = {
		{"#000000", "#444400", "#702800", "#841800", "#880000", "#78005C", "#480078", "#140084", "#000088", "#00187C", "#002C5C", "#003C2C", "#003C00", "#143800", "#2C3000", "#442800"},
		{"#404040", "#646410", "#844414", "#983418", "#9C2020", "#8C2074", "#602090", "#302098", "#1C209C", "#1C3890", "#1C4C78", "#1C5C48", "#205C20", "#345C1C", "#4C501C", "#644818"},
		{"#6C6C6C", "#848424", "#985C28", "#AC5030", "#B03C3C", "#A03C88", "#783CA4", "#4C3CAC", "#3840B0", "#3854A8", "#386890", "#387C64", "#407C40", "#507C38", "#687034", "#846830"},
		{"#909090", "#A0A034", "#AC783C", "#C06848", "#C05858", "#B0589C", "#8C58B8", "#6858C0", "#505CC0", "#5070BC", "#5084AC", "#509C80", "#5C9C5C", "#6C9850", "#848C4C", "#A08444"},
		{"#B0B0B0", "#B8B840", "#BC8C4C", "#D0805C", "#D07070", "#C070B0", "#A070CC", "#7C70D0", "#6874D0", "#6888CC", "#689CC0", "#68B494", "#74B474", "#84B468", "#9CA864", "#B89C58"},
		{"#C8C8C8", "#D0D050", "#CCA05C", "#E09470", "#E08888", "#D084C0", "#B484DC", "#9488E0", "#7C8CE0", "#7C9CDC", "#7CB4D4", "#7CD0AC", "#8CD08C", "#9CCC7C", "#B4C078", "#D0B46C"},
		{"#DCDCDC", "#E8E85C", "#DCB468", "#ECA880", "#ECA0A0", "#DC9CD0", "#C49CEC", "#A8A0EC", "#90A4EC", "#90B4EC", "#90CCE8", "#90E4C0", "#A4E4A4", "#B4E490", "#CCD488", "#E8CC7C"},
		{"#ECECEC", "#FCFC68", "#ECC878", "#FCBC94", "#FCB4B4", "#ECB0E0", "#D4B0FC", "#BCB4FC", "#A4B8FC", "#A4C8FC", "#A4E0FC", "#A4FCD4", "#B8FCB8", "#C8FCA4", "#E0EC9C", "#FCE08C"}
	};*/

	const string hexCols[8][16];
	
	string hexColsCorrected[128];
	int grayscale[256];

	void correctHexCols();

	rgbValue hextorgb(string hex);

	int colToGray(rgbValue colour);

	void createGSTable();

	

public:
	gsConvert();
	int getGrayscale(int val);

protected:

};
