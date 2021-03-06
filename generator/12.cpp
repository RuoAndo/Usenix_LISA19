#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <random>
#include <vector>
#include <bitset>
#include<fstream>

#include <functional> //for std::function
#include <algorithm>  //for std::generate_n
 
typedef std::vector<char> char_array;
char_array charset()
{
    //Change this to suit
    return char_array( 
	{'0','1','2','3','4',
	'5','6','7','8','9',
	'A','B','C','D','E','F',
	'G','H','I','J','K',
	'L','M','N','O','P',
	'Q','R','S','T','U',
	'V','W','X','Y','Z',
	'a','b','c','d','e','f',
	'g','h','i','j','k',
	'l','m','n','o','p',
	'q','r','s','t','u',
	'v','w','x','y','z'
	});
};    
 
std::string random_string( size_t length, std::function<char(void)> rand_char )
{
    std::string str(length,0);
    std::generate_n( str.begin(), length, rand_char );
    return str;
}

int GetRandom(int min,int max);

using namespace std;

std::vector<std::string> split_string_2(std::string str, char del) {
  int first = 0;
  int last = str.find_first_of(del);

  std::vector<std::string> result;

  while (first < str.size()) {
    std::string subStr(str, first, last - first);

    result.push_back(subStr);

    first = last + 1;
    last = str.find_first_of(del, first);

    if (last == std::string::npos) {
      last = str.size();
    }
  }

  return result;
}

int main( int argc, char* argv[] )
{
  int i;
  int N = atoi(argv[1]);  

  if (argc != 2){
    printf("usage: ./9 LINE_NUMBER");
    exit(1);
  }
  
  /*
  for (i = 0;i < 10;i++) {
		printf("%d\n",GetRandom(1,6));
  }
  */

  std::random_device rnd;
  std::mt19937 mt(rnd());
  std::uniform_int_distribution<long> randD(20190702, 20190702);
  std::uniform_int_distribution<long> randH(0, 1);
  std::uniform_int_distribution<long> randM(0, 59);
  std::uniform_int_distribution<long> randS(0, 59);
  std::uniform_int_distribution<long> randMS(0, 1000);

  long date;
  long hour;
  long minute;
  long second;
  long msec;
  
  std::vector<long> tms;

  string tmpstring;
  string tmp_hour;
  string tmp_minute;
  string tmp_second;
  string tmp_msec;
  
  long long r;
  
  for (int i = 0; i < N; ++i) {
    date = randD(mt);
    hour = randH(mt);
    minute = randM(mt);
    second = randS(mt);
    msec = randMS(mt);

    if(hour < 10)
      tmp_hour = "0" + to_string(hour);
    else
      tmp_hour = to_string(hour);

    if(minute < 10)
      tmp_minute = "0" + to_string(minute);
    else
      tmp_minute = to_string(minute);

    if(second < 10)
      tmp_second = "0" + to_string(second);
    else
      tmp_second = to_string(second);

    if(msec < 10)
      tmp_msec = "00" + to_string(msec);
    else if(msec < 100)
      tmp_msec = "0" + to_string(msec);
    else
      tmp_msec = to_string(msec);

    // cout << tmp_msec << endl;
    
    tmpstring = to_string(date) + tmp_hour + tmp_hour + tmp_minute + tmp_msec;
    // cout << tmpstring << endl;
    r = stoll(tmpstring);
    tms.push_back(r);
  }

  std::sort(tms.begin(), tms.end());

  ofstream outputfile("random_data.txt");
  
  for (int i = 0; i < N; ++i) {    

    tmpstring = to_string(tms[i]);

    outputfile << "\"" << tmpstring.substr( 0, 4 )
	       << "/"
	       << tmpstring.substr( 4, 2 ) 
	       << "/"
	       << tmpstring.substr( 6, 2 )
	       << " "
	       << tmpstring.substr( 8, 2 )
	       << ":"
	       << tmpstring.substr( 10, 2 )
	       << ":"
	       << tmpstring.substr( 12, 2 )
	       << "."
	       << tmpstring.substr( 14, 3 )
	       << "\"" << "," ;

    outputfile << "\"" << GetRandom(1,1000) << "\"" << endl;
  }

  outputfile.close();
  
  return 0;
}

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}


