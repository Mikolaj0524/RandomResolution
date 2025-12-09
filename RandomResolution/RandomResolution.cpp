#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <windows.h>
#include <cstdlib> 
#include <ctime> 

using namespace std;

string centerText(string text);
bool changeResolution(int width, int height);

int main()
{
	vector<string> resolutions = { "2560x1440", "1920x1080", "1366x768", "1600x900", "1024x768", "1280x960", "1280x720", "3840x2160", "3440x1440", "2560x1080", "2560x1600", "1920x1200", "1680x1050", "1440x900", "1280x1024", "1024x600", "800x600", "640x480"};

	int counter = 0, current = 0;
	
	// Random Number Generation
	srand(static_cast<unsigned>(time(0)));
	int random = rand() % (30 - 10 + 1) + 10;

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