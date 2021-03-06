/*
    sNMF.cpp
    NMF for sparse matricies. 
    Two different constructors depending if already processed

    @author: Ryan Birmingham
    @version: 1.0 07 July 2015
*/


using namespace std;
using namespace arma;

std::pair<sp_mat,sp_mat> sNMF(mat coordlist, int rank, float tol = 1e-5){

    /* 
    input: 
        filename - coordinate list (in form x, y ,z per row)
        rank to two sp_mat, xMajor and yMajor
        tol to one vec for the mapping

    output:
 //     pair containing W and H
    */

	//Iteration cap; mostly for testing
	int itmax = 1;

    mat W;
    mat H;

	//run preprocessing

    std:pair<sp_mat,sp_mat> mats = spproc(coordlist);
    sp_mat xMajor = mats.first;
    sp_mat yMajor = mats.second;


	// get size to use
    int xs = xMajor.n_rows;

	// create initial W and H
	//since V is positive, set W to 0 and H randomly
    // smallest nonzero start using eps (smallest float diff)
    W.randu(xs,rank);
    H.randu(rank,xs);
	// okay, let's go 
	float eucDist=1e9; //big initial value 
	int itcount= 0;
        mat eta;
	while ((eucDist>tol)&&(itcount<itmax)){
	    // update H; sparse optimized
        mat WTranspose = W.t();	    
        // TODO Fix this mess
        eta = (H/(WTranspose*W*H));
	    H = H + eta %(xMajor*WTranspose- WTranspose*W*H);
// H stays positive for sure so long as initial guess for WH<V.

	    // update W (expensive as of now) TODO Fix this mess
        mat tmpWdivisior = (W*H)*(H.t());
        mat WNS =(W*xMajor);
        W = (WNS/tmpWdivisior);
	    // TODO, find better way to do WH
	    mat WH = H*W;
        eucDist=sum(sum((WH-xMajor)%(WH-xMajor)));
		itcount++;
	    // maybe implement some sparse WH assurance update?
	}
    return std::make_pair(xMajor,yMajor);

}
