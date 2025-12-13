#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <windows.h>
#include <cstdlib> 
#include <ctime>
#include <algorithm>

using namespace std;

string centerText(string text);
bool changeResolution(int width, int height);
void loadResoltions();

vector<string> resolutions = {};

int main()
{
	loadResoltions();

	int counter = 0, current = 0;
	
	// Random Number Generation
	srand(static_cast<unsigned>(time(0)));
	int random = rand() % ((resolutions.size() * 2) - (resolutions.size() / 2) + 1) + (resolutions.size() / 2);

	// Start Screen
	cout << " " << endl;
	cout << "+------------- Random Resolution -------------+" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "| " << centerText("Start? ") << " |" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "+---------------------------------------------+" << endl;
	cout << "[Y]es [N]o\n";

	string input;
	cin >> input;
	if(input != "Y" && input != "y")
		exit(0);

	// Second Step
	bool loop = true;
	while(loop){
		system("cls");

		// Second Screen
		cout << " " << endl;
		cout << "+------------- Random Resolution -------------+" << endl;
		cout << "|                                             |" << endl;

		for (int i = 0; i < resolutions.size() - 1; i++) {
			cout << "| " << centerText((current == i ? "> " : "") + resolutions[i] + (current == i ? " <" : "")) << " |" << endl;
		}

		cout << "|                                             |" << endl;
		cout << "+---------------------------------------------+" << endl;
		
		if(counter == random){
			loop = false;
		}
		else{
			if (current < resolutions.size() - 2) {
				current++;
			}
			else {
				current = 0;
			}

			counter++;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	// Third Step
	this_thread::sleep_for(chrono::milliseconds(2000));
	system("cls");

	// Third Screen
	cout << " " << endl;
	cout << "+------------ Changing Resolution ------------+" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "| " << centerText(resolutions[current]) << " |" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "+---------------------------------------------+" << endl;

	// Fourt Step
	this_thread::sleep_for(chrono::milliseconds(3000));

	string resolution = resolutions[current];
	int xPos = resolution.find("x");
	int width = stoi(resolution.substr(0, xPos));
	int height = stoi(resolution.substr(xPos + 1));

	int oldWidth = GetSystemMetrics(SM_CXSCREEN);
	int oldHeight = GetSystemMetrics(SM_CYSCREEN);

	bool response = changeResolution(width, height);

	// Fourth Screen
	system("cls");
	cout << " " << endl;
	cout << "+------------- Current Resolution ------------+" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "| " << centerText(response ? resolutions[current] : "Unable to change resolution!") << " |" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "+---------------------------------------------+" << endl;
	system("pause");
	return 0;
}

void loadResoltions(){
	DEVMODE dm = {};
	dm.dmSize = sizeof(dm);

	for (int i = 0; EnumDisplaySettings(NULL, i, &dm); i++) {
		string res = to_string(dm.dmPelsWidth) + "x" + to_string(dm.dmPelsHeight);
		resolutions.push_back(res);
	}

	resolutions.erase(unique(resolutions.begin(), resolutions.end()), resolutions.end());
}

bool changeResolution(int width, int height){
	DEVMODE dm = {};
	dm.dmSize = sizeof(dm);
	dm.dmPelsWidth = width;
	dm.dmPelsHeight = height;
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	return ChangeDisplaySettings(&dm, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
}

string centerText(string text){
	int width = 43;
	int left = (width - text.length()) / 2;
	int right = width - text.length() - left;

    string finalString(left, ' ');
    finalString += text;
    finalString += string(right, ' ');

    return finalString;
}