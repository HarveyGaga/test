/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年08月08日 星期二 16时53分49秒
 ************************************************************************/

#include<iostream>
using namespace std;

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
	START_EASYLOGGINGPP(argc, argv);

	// Load configuration from file
	el::Configurations conf("./default.conf");

	// Reconfigure single logger
	el::Loggers::reconfigureLogger("default", conf);

	// Actually reconfigure all loggers instead
	el::Loggers::reconfigureAllLoggers(conf);

	// Now all the loggers will use configuration from file
	LOG(INFO) << "My first info log using default logger";

	return 0;
}
