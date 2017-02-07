#pragma once 

#include <string>
#include <iostream>

struct Params
{

	int m_minCountChar;
	int m_maxCountChar;

	//range
	int m_minCodeRange1;
	int m_maxCodeRange1;

	int m_minCodeRange2;
	int m_maxCodeRange2;

	std::string m_hashToCheck;

};


static bool ParseRange (const std::string& ranges, int& low1, int& hi1, int& low2, int& hi2)
{
	using namespace std;

	size_t end = ranges.find_first_of ("-:");
	if (end==string::npos)
	{
		return false;
	}

	low1  = stoi(ranges.substr(0,end));
	cout << "low range param " << low1 << endl;

	size_t begin = end+1;
	end = ranges.find_first_of ("-:", begin);
	if (end==string::npos)
	{
		return false;
	}

	hi1 = stoi (ranges.substr(begin, begin-end));

	cout << "hi range param " << hi1 << endl;

	begin = end+1;

	end = ranges.find_first_of ("-:", begin);
	if (end==string::npos)
		return false;

	low2 = stoi (ranges.substr(begin, end-begin));
	cout << "low2 " << low2 << endl;

	begin = end+1;
	hi2 = stoi (ranges.substr(begin, ranges.size()-begin));

	cout << "hi2 " << hi2 << endl;
}

static bool ParseCommandLine (int count, char* params[], Params& p)
{	

	using namespace std;

	cout << endl;
	if (count==1)
	{
		cout << "Params were not defined" << endl;
		return false;
	}

	const unsigned int maxCountParams  = 5;
	
	if (count< maxCountParams)
	{
		cout << "params are not defined" << endl;
		return false;
	}
	
	p.m_minCountChar = stoi( string(params[1]) );
	cout << "minimum count char " << p.m_minCountChar << endl;
	p.m_maxCountChar = stoi( string(params[2]) );
	cout << "maximum count char " << p.m_maxCountChar << endl;

	//parse range 23-123:34-67
	cout << "Parse ranges " << endl;
	string ranges = string(params[3]);

	ParseRange(ranges, p.m_minCodeRange1, p.m_maxCodeRange1, p.m_minCodeRange2, p.m_maxCodeRange2);

	p.m_hashToCheck = string(params[4]);

	cout << "hash to check " << hex << p.m_hashToCheck << endl;

}
