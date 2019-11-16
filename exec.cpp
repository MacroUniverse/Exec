#include <iostream>
#include <fstream>
#include "SLISC/time.h"
#include "SLISC/file.h"

using namespace slisc;

int main()
{
	Str fname, str;
	ifstream fin;
	Timer timer;
	cin >> fname;
	cout << "script file: " << fname << "\n" << endl;
	while (true) {
		if (!file_exist(fname.c_str())) {
			pause(2);
			continue;
		}
		fin.open(fname);
		getline(fin, str);
		fin.close();
		if (str.empty())
			continue;
		cout << "running: `" << str << "` ..." << endl;
		timer.tic();
		Int ret = system(str.c_str()); ++ret;
		cout << "returned, time used: " << timer.toc() << "\n" << endl;
		remove(fname.c_str());
	}
}
