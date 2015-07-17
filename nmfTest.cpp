#include "nmf.hpp"
#include <sys/time.h>
#include <iostream>

using namespace std;
using namespace arma;
int main(int argc,char* argv[]){
    int rank = 1;
    int dim  = 9;
    if (argc >= 2){
        rank = atoi(argv[2]);
        dim = atoi(argv[1]);
    }
       /** mat coordlist = randu<mat>(3,dim);
        coordlist = coordlist * 100;
        coordlist = round(coordlist);
        coordlist = coordlist + 1;**/
        mat coordlist;
        coordlist.load("test.csv");
        cout << " Mat is: " << coordlist;
        timespec tS;
        tS.tv_sec = 0;
        tS.tv_nsec = 0;
        clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
	std:pair<sp_mat,sp_mat> mats = sNMF(coordlist,rank);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
        cout << "Time Taken, sNMF: " << tS.tv_sec <<'\n';
	return 0;
}
