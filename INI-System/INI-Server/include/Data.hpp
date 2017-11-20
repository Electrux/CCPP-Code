#pragma once

const int SERVER_PORT = 8080;

const int MAX_PACKET_TRIES = 1000;

const std::string DEFAULT_DB_DIR = "Databases/",
					EXTENSION = ".ini";

const std::string MSGS[6] = {

	"SERVER",
	"CONSOLEINPUT",
	"ERROR",
	"NETWORK",
	"INIDB",
	"INIMGR"

};

std::mutex ConsoleInputMutex;

std::string ConsoleInputStr;

