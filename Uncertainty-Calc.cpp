#include "Uncertainty-Calc.h"

using namespace std;

vector<string> input_sorted;
float ires[4] = { 0, 0, 0, 0 };
float maxsize = 0;
float minsize = 0;
float midvalue = 0;
float range = 0;

int main(int argc, char** agv){
	string input;

	cout << "Enter decimals as 0.05 not .05. No need to use plus/minus sign, any delimiter works.\n";

	for (int k = 0; k < 1; k++) {
		_setmode(_fileno(stdout), _O_TEXT);

		cout << "Enter a uncertainty operation: ";
		getline(cin, input);
		cout << "\n";

		input_sorted.clear();
		istringstream sort(input);

		for (string input; sort >> input;) { //sort string into parts
			input_sorted.push_back(input);
		}

		/*
			Array indices 0,2,4,6 are integers. Indices 1, 5
			are filler. Indice 3 is the operation index.
		*/

		for (int i = 0; i < 4; i++) {
		//ires[i] = stof(input_sorted[2 * i]);

			istringstream stemp(input_sorted[2 * i]);
			stemp >> ires[i];
		}

		cout << ires[2];

		if (input_sorted[3] == "+") {
			UncAdd();
		}
		if (input_sorted[3] == "-") {
			UncSub();
		}
		if (input_sorted[3] == "*") {
			UncMul();
		}
		if (input_sorted[3] == "/") {
			UncDiv();
		}

		cout << "Press any key to continue. Press x to exit.\n\n";

		_getch(); //prevent autoexit
		if (GetKeyState(88) != false) {
			break;
		}
		else {
			k--;
		}
	}

	return 0;
}

void UncAdd() {
	maxsize = ires[0] + ires[1] + ires[2] + ires[3];
	minsize = ires[0] - ires[1] + ires[2] - ires[3];
	
	midvalue = (minsize + maxsize) / 2;
	range = ires[1] + ires[3];
	
	_setmode(_fileno(stdout), _O_U16TEXT);

	cout << "Result: " << midvalue << "±" << range << "\n\n";

	// 4.1232 ± 0.001 + 3.734 ± 0.0035
}

void UncSub() {
	maxsize = ires[0] + ires[1] - ires[2] - ires[3];
	minsize = ires[0] - ires[1] - ires[2] + ires[3];

	midvalue = (minsize + maxsize) / 2;
	range = ires[1] + ires[3];

	_setmode(_fileno(stdout), _O_U16TEXT);

	cout << "Result:" << midvalue << "±" << range << "\n\n";

	// 4.12 ± 0.05 - 3.7 ± 0.1
}

void UncMul() {
	maxsize = (ires[0] + ires[1]) * (ires[2] + ires[3]);
	minsize = (ires[0] - ires[1]) * (ires[2] - ires[3]);

	midvalue = (minsize + maxsize) / 2;
	range = midvalue - minsize;

	_setmode(_fileno(stdout), _O_U16TEXT);

	cout << "Result:" << midvalue << "±" << range << "\n\n";

	// 2 ± 1 * 5 ± 1
}

void UncDiv(){
	maxsize = (ires[0] + ires[1]) / (ires[2] - ires[3]);
	minsize = (ires[0] - ires[1]) / (ires[2] + ires[3]);

	midvalue = (minsize + maxsize) / 2;
	range = midvalue - minsize;

	_setmode(_fileno(stdout), _O_U16TEXT);

	cout << "Result:" << midvalue << "±" << range << "\n\n";

	// 15 ± 0.21 / 8 ± 0.1
}