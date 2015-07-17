/*
    spproc.cpp
    Processes a coordinate list from a graph into a sparse matrix and its transpose
    Transpose saved so that operations are efficient with mmap

    @author: Ryan Birmingham
    @version: 1.0 07 July 2015
*/



using namespace std;
using namespace arma;
std::pair<sp_mat,sp_mat> spproc(mat coordList){

    /* 
    input: 
        coordlist - 3xn matrix, in form x position, y position, value
    output:
        pair of ...
        xMajor - sparse matrix construction with x position major sorting
        yMajor - sparse matrix construction with y position major sorting
        mappIn - vector such that where the matrix is n, the label is nth elem
    */

    // step 1, create contigious values
    vec xv1=coordList.col(0);
    vec xv2=coordList.col(1);
    vec xv3=coordList.col(2);

    vec mapIn=unique(join_rows(xv1,xv2)); // TODO Save this value
    int m_unique = mapIn.n_elem;
    // use the unique values as a mapping for all labels
    for (int i=0; i<mapIn.n_elem; i++){
        int uvI = mapIn(i);
        xv1(find(xv1==uvI)).fill(i);
        xv2(find(xv2==uvI)).fill(i);

    }
    cout << "M unique is : " << m_unique << "\n";
    // now x and y values are assured to be continious
    //step 2 generate sparse matricies
    // spmat needs our list transposed
    umat locations = conv_to<umat>::from(join_rows(xv1,xv2));
    locations = locations.t();
    cout << "Locations : " << locations << "\n"; 
    sp_mat xMajor(locations,xv3,m_unique,m_unique);
    cout << "Got first! \n";
    locations.swap_rows(1,0);
    sp_mat yMajor(locations,xv3,m_unique,m_unique);


    // step 3 package into a pair type
    return std::make_pair(xMajor,yMajor);


}
