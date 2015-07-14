#include "nmf.hpp"

using namespace std;
using namespace arma;
int main(){
	int rank = 1;
    mat coordlist;
    coordlist << 1 << 2 << 3 <<endr << 3 << 4 << 5 << endr << 6 << 7 << 8<< endr;
	std:pair<sp_mat,sp_mat> mats = sNMF(coordlist,rank);
	return 0;
}
