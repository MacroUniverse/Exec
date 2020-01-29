#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include "SLISC/time.h"
#include "SLISC/file.h"
#include "SLISC/linux.h"

using namespace slisc;

Bool killed;

void *caller(void *pfname)
{
	Str fname(*(Str*)pfname);
	ifstream fin(fname);
	Str cmd;
	getline(fin, cmd);
	fin.close();
	if (cmd.empty()) {
		cout << "script file is empty!" << endl;
		return NULL;
	}
	cout << "running: `" << cmd << "` ..." << endl;
	Int ret = system(cmd.c_str()); ++ret;
	remove(fname.c_str());
	killed = false;
	return NULL;
}

// sleep while keeping all threads used
void sleep_all(Doub_I sec)
{
	Timer timer; timer.tic();
#pragma omp parallel for schedule(dynamic)
	for (Long i = 0; i < 2000 ; ++i) {
		if (timer.toc() > sec)
			continue;
		sleep(0.2);
	}
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
			sleep_all(2);
			continue;
		}
		else {
			ifstream fin(fname);
			string str; getline(fin, str); fin.close();
			if (str.empty()) {
				sleep_all(2);
				continue;
			}
		}
		
		timer.tic();
		killed = true;
		pthread_create(&pth, NULL, caller, &fname);
		vector<Int> ch_pid;
		while (true) {
			sleep(5);
			if (!file_exist(fname)) {
				child_pid(ch_pid, getpid());
				child_pid(ch_pid, ch_pid[0]);
				if (killed) {
					kill(ch_pid[0], SIGKILL);
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
