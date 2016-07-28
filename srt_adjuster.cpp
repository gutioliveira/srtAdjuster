#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

void operation_positive(long long seconds, long long precision, long long *h, long long *m, long long *s, long long *p){

	long long hours_time = *h;
	long long minutes_time = *m;
	long long seconds_time = *s;
	long long precision_time = *p;

	precision_time += precision;
// printf("seconds %lf\n", seconds);
// printf("precision %lld -- %d\n", precision_time, (int)(( seconds - (long long) seconds )*1000));

	int rem = 0;

	if ( precision_time >= 1000 ){

		rem++;	

		precision_time -= 1000;
	}

	seconds_time += rem;

	seconds_time += seconds;

	int min = 0;

	while ( seconds_time >= 60 ){

		min++;
		seconds_time -= 60;
	}

	minutes_time += min;

	int hou = 0;

	while ( minutes_time >= 60 ){

		hou++;
		minutes_time -= 60;
	}

	hours_time += hou;

	*h = hours_time;
	*m = minutes_time;
	*s = seconds_time;
	*p = precision_time;	
}

void operation_negative(long long seconds, long long precision, long long *h, long long *m, long long *s, long long *p){

	long long hours_time = *h;
	long long minutes_time = *m;
	long long seconds_time = *s;
	long long precision_time = *p;

	precision_time += precision;

	int seg = 0;

	if ( precision_time < 0 ){

		precision_time = 1000 + precision_time;
		seg--;
	}

	seconds_time += seg;
	seconds_time += seconds;

	while ( seconds_time < 0 ){

		if ( minutes_time <= 0 && hours_time <= 0 )
			break;
		else if ( minutes_time >= 0 ){

			minutes_time--;
			seconds_time += 60;
		}else{

			hours_time--;
			minutes_time += 60;
		}
	}

	*h = hours_time;
	*m = minutes_time;
	*s = seconds_time;
	*p = precision_time;	
}

void formatedTime(long long h, long long m, long long s, long long p){

	// 00:00:43,726
	printf("%02lld:%02lld:%02lld,%03lld", h, m, s, p);
}

vector<string> split(string str, char delimiter) {

  vector<string> internal;

  stringstream ss(str); // Turn the string into a stream.

  string tok;
  
  while(getline(ss, tok, delimiter)) {

    internal.push_back(tok);
  }
  
  return internal;
}

int main(int argc, char *argv[]){
	
	double delay_time;

	// printf("Escreva o tempo para atrasar as legendas.\n");

	// scanf("%lf", &delay_time);

	// char *delay;

	// delay = strtok(argv[1], ".");

	vector<string> delay = split(string(argv[1]), '.');

	// printf("teste %s\n", argv[1]);

	// delay_time = atof(argv[1]);

	// printf("tempo legenda %s %s\n", delay[0].c_str(), delay[1].c_str());

	long long delay_seconds = atoi(delay[0].c_str());
	long long delay_precision;

	if ( delay.size() > 1 ){
	
		delay_precision = atoi(delay[1].c_str());
	}else
		delay_precision = 0;

	int delay_size = 1;

	switch ( delay[1].size() ){

		case 1:
			delay_size = 100;
			break;
		case 2:
			delay_size = 10;
			break;
		default:
			delay_size = 1;
	}

	string line;

	while ( getline(cin, line) ){

		// cout << " t " << line << endl;

		string word[3];

		int aux = 0;

		istringstream spliter(line);

		while( true ){

			if ( aux > 2 )
				break;

			spliter >> word[aux++];
		}

		if ( word[1] == "-->" ){

			istringstream test(word[0]);
			istringstream test2(word[2]);

			long long hour1, hour2;
			long long minute1, minute2;
			long long seconds1, seconds2;
			long long seconds_precision1, seconds_precision2;

			char comma; // ','
			string arrow; // "-->""

			test >> hour1 >> comma >> minute1 >> comma >> seconds1 >> comma >> seconds_precision1;
			test2 >> hour2 >> comma >> minute2 >> comma >> seconds2 >> comma >> seconds_precision2;

			// seconds_precision1 = seconds_precision1/1000.0;
			// seconds_precision2 = seconds_precision2/1000.0;

			if ( delay_seconds >= 0 ){

				operation_positive(delay_seconds, delay_precision*delay_size, &hour1, &minute1, &seconds1, &seconds_precision1);
				operation_positive(delay_seconds, delay_precision*delay_size, &hour2, &minute2, &seconds2, &seconds_precision2);
			}else{

				operation_negative(delay_seconds, -delay_precision*delay_size, &hour1, &minute1, &seconds1, &seconds_precision1);
				operation_negative(delay_seconds, -delay_precision*delay_size, &hour2, &minute2, &seconds2, &seconds_precision2);
			}

			if ( hour1 < 0 || minute1 < 0 || seconds1 < 0 || seconds_precision1 < 0 ){

				hour1 = abs(hour1);
				minute1 = abs(minute1);
				seconds1 = abs(seconds1);
				seconds_precision1 = abs(seconds_precision1);

				printf("-");
			}

			formatedTime(hour1, minute1, seconds1, seconds_precision1 );

			printf(" --> ");

			if ( hour2 < 0 || minute2 < 0 || seconds2 < 0 || seconds_precision2 < 0 ){

				hour2 = abs(hour2);
				minute2 = abs(minute2);
				seconds2 = abs(seconds2);
				seconds_precision2 = abs(seconds_precision2);

				printf("-");
			}

			formatedTime(hour2, minute2, seconds2, seconds_precision2 );

			printf("\n");
		}else{

			cout << line << endl;
		}


	}

	return 0;
}