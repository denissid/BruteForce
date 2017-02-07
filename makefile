all:
	g++ -std=c++11 -pthread -g main.cpp CommandLineParser.h PasswordGenerator.h md5.h -o brute
