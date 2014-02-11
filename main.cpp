#include <iostream>
#include "yaml-cpp/yaml.h"
#include <H5Cpp.h>

using namespace H5;

int main()
{
    //declare YAML nodes to work with input file
    YAML::Node magEq;
    YAML::Node oneDim;
    YAML::Node twoDim;

    //declare variables to hold and manipulate intermediate data
    int i; //loop index
    double psi[101] = {0.0};
    double ycoeff[3] = {0.0};
    double dat[101] = {0.0};

    //declare vars to manipulate HDF5 output file
    H5::H5File outfile( "gtcInputEq.h5", H5F_ACC_TRUNC );
    hsize_t dim[1] = {101};
    H5::DataSpace datspace1D( 1, dim );
    H5::IntType dattype( H5::PredType::NATIVE_DOUBLE );
    H5::DataSet datset = outfile.createDataSet( "qProfile", dattype, datspace1D );

    //read in the YAML eq file
    magEq = YAML::LoadFile("analytic.yaml");

    //do some parsing
    //first check for 1D and 2D data in the eq file
    if(magEq["1D profiles"])
        oneDim = magEq["1D profiles"];
    if(magEq["2d profiles"])
        twoDim = magEq["2D profiles"];
    
    //generate coords
    for ( i=0; i<101; i++ )
        psi[i] = i/100.0;

    //parse 1D profiles
    if(oneDim["q"]){
        for ( i=0; i<3; i++ )
            ycoeff[i] = oneDim["q"][i].as<double>();
        for ( i=0; i<101; i++ )
            dat[i] = ycoeff[0] + ycoeff[1]*psi[i] + ycoeff[2]*psi[i]*psi[i];
    }

    //now write data to HDF5 file
    datset.write( dat, H5::PredType::NATIVE_DOUBLE );

    return 0;
}
