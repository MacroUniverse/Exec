#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include "SLISC/time.h"
#include "SLISC/file.h"

using namespace slisc;

Bool killed;

void *caller(void *pfname)
{
	Str fname(*(Str*)pfname);
	ifstream fin(fname);
	Str str;
	getline(fin, str);
	fin.close();
	if (str.empty()) {
		cout << "script file is empty!" << endl;
		remove(fname.c_str());
		return NULL;
	}
	cout << "running: `" << str << "` ..." << endl;
	Int ret = system(str.c_str()); ++ret;
	remove(fname.c_str());
	killed = false;
	return NULL;
}

// return -1 if no child
int get_child_pid(int pid)
{
	string pid_file = "pid" + to_string(pid) + ".tmp";
	string cmd  = "pgrep -P " + to_string(pid) + " > " + pid_file;
	int ret = system(cmd.c_str()); ++ret;
	ifstream fin(pid_file);
	string pid_str; getline(fin, pid_str); fin.close(); remove(pid_file.c_str());
	if (pid_str.empty())
		return -1;
	int child_pid = stoi(pid_str);
	return child_pid;
}

int main(int argc, char *argv[])
{
	Timer timer;
	pthread_t pth;
	if (argc != 2) {
		cout << "usage: exec.x <script_file>";
		return 0;
	}

	Str fname(argv[1]);
	cout << "script file: " << fname << "\n" << endl;
	while (true) {
		if (!file_exist(fname.c_str())) {
			pause(2);
			continue;
		}
		
		timer.tic();
		killed = true;
		pthread_create(&pth, NULL, caller, &fname);
		
		while (true) {
			sleep(5);
			if (!file_exist(fname)) {
				if (killed) {
					kill(get_child_pid(get_child_pid(getpid())), SIGKILL);
					cout << "killed, time used: " << timer.toc() << "\n" << endl;
				}
				else
					cout << "returned, time used: " << timer.toc() << "\n" << endl;
				pthread_join(pth, NULL);
				break;
			}
		}
	}
}
