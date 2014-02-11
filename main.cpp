#include <iostream>
#include "yaml-cpp/yaml.h"
#include <H5Cpp.h>

int main( int argcount, char *argvec[] )
{
    //declare *default* input file, output file, and length of radial profiles
    std::string inFile = "analytic.yaml";
    std::string outFile = "gtcInputEq.h5";
    const int radialProfileLength = 101;

   //declare YAML nodes to work with input file
    YAML::Node magEq;
    YAML::Node oneDim;
    YAML::Node twoDim;

    //declare variables to hold and manipulate intermediate data
    int i; //loop index
    double psi[radialProfileLength] = {0.0};
    double dat[radialProfileLength] = {0.0};

    //declare vars to manipulate HDF5 output file
    H5::H5File outfile( outFile, H5F_ACC_TRUNC );
    hsize_t dim[1] = { (unsigned int)radialProfileLength };
    H5::DataSpace datspace1D( 1, dim );
    H5::IntType dattype( H5::PredType::NATIVE_DOUBLE );
    H5::DataSet datset; 

    //read in the YAML eq file
    magEq = YAML::LoadFile( inFile );

    //generate radial coords
    for ( i=0; i<radialProfileLength; i++ )
        psi[i] = i/(radialProfileLength - 1.0);

    //do some parsing
    //first check for 1D and 2D data in the eq file
    //if the exist, generate profiles from polynomial coefficients
    if(magEq["1D profiles"]){
        oneDim = magEq["1D profiles"];
        for(YAML::const_iterator iter=oneDim.begin(); iter!=oneDim.end(); ++iter){
            for( i=0; i<radialProfileLength; i++)
                dat[i] = iter->second[0].as<double>() 
                        + iter->second[1].as<double>()*psi[i] 
                        + iter->second[2].as<double>()*psi[i]*psi[i];
            datset = outfile.createDataSet( iter->first.as<std::string>(), dattype, datspace1D );
            datset.write( dat, H5::PredType::NATIVE_DOUBLE );
        }
    }
    if(magEq["2d profiles"]){
        twoDim = magEq["2D profiles"];
        // do some more parsing if we need this part...
    }

    return 0;
}
