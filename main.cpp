#include <iostream>
#include <string>
#include <cassert>
#include <thread>
#include <string>
#include <vector>
#include <functional>
#include <memory>

#include "CommandLineParser.h"
#include "PasswordGenerator.h"
#include "md5.h"

void testParseRange()
{	
	using namespace std;

	string str = "12-45:34-22";

	int l = 0, h = 0, l1 = 0, h1 = 0;
	ParseRange (str, l, h, l1, h1);
	assert(l==12);
	assert(h==45);
	assert(l1==34);
	assert(h1==22);

	
}

void testPasswordGenerator()
{
	PasswordGenerator<char> pg(0,4,'A','Z','a','z');

	do
	{
		MD5 md5;

		std::string d(pg.get());
		d.push_back(0);
		
	        std::cout << &d[0] << " " << md5.digestString (&d[0]) << std::endl;
	}
	while(pg.generateNext());
}

int calculateStep(int begin, int end, int countThreads)
{
	int countRanges = end - begin;
	int step = countRanges/countThreads;
	return step;
}

void testRangesOnThread()
{
	std::cout << "Step " << calculateStep (3,10,5) << std::endl;
	std::cout << "Step " << calculateStep (3,10,1) << std::endl;
	std::cout << "Step " << calculateStep (3,10,3) << std::endl;
	std::cout << "Step " << calculateStep (3,10,2) << std::endl;
}

void separateRanges (int min, int max, std::vector< std::pair<int,int> >& pairs, int step)
{
	using namespace std;


	cout << "step" << step << endl;

	for (int i = min; i <= max; ++i)
	{
		int b = i;
		int e = i + step;

		if (e>max)
			e = max;

		cout << "rangeA " << dec << b << " " << e << endl;
		pairs.push_back( make_pair(b, e) );
		i=e;
	}

}

void Worker(int beg, int end, int lSym, int hSym, int l1Sym, int h1Sym, const std::string&  hash)
{
	using namespace std;

	cout << "Start thread" << endl;
	PasswordGenerator<char> pg( beg, end, lSym, hSym, l1Sym, h1Sym);

	do
	{
		MD5 md5;

		string d(pg.get());
		d.push_back(0);

		string digest =  md5.digestString (&d[0]);
		//cout << digest << endl;
		if (digest==hash)
		{
	        	cout << digest << " " << hash << endl;
			break;
		}
	}
	while(pg.generateNext());

}


int main (int count, char* params[] )
{

	//testParseRange();
	//atestPasswordGenerator();
	//testRangesOnThread();

	using namespace std;

	Params pParams;

	if (ParseCommandLine (count, params, pParams))
	{

		int countThreads = std::thread::hardware_concurrency();
		std::cout <<"Number of concurrent threads  "<< countThreads << " " << std::endl;

		int step = calculateStep (pParams.m_minCountChar, pParams.m_maxCountChar, countThreads);

		vector< pair<int,int> > pairs;

		separateRanges (pParams.m_minCountChar, pParams.m_maxCountChar, pairs, step);

		vector <shared_ptr<thread> > threads;	

		for (auto p: pairs)
		{
				
			shared_ptr<thread> p1 = make_shared<thread> (bind(Worker, p.first, p.second, pParams.m_minCodeRange1, pParams.m_maxCodeRange1, 
							           pParams.m_minCodeRange2, pParams.m_maxCodeRange2, pParams.m_hashToCheck) );
			threads.push_back(p1);
		}
		
		for (auto thr:threads)
		{
			thr->join();
		}
 
		
		
	}
	
	return 0;
}
