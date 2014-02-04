#include <iostream>
#include "yaml-cpp/yaml.h"
#include "hdf5.h"

int main()
{
    //declare YAML nodes to work with
    YAML::Node magEq;
    YAML::Node oneDim;
    YAML::Node twoDim;

    //read in the YAML eq file
    magEq = YAML::LoadFile("analytic.yaml");

    //do some parsing
    //first check for 1D and 2D data in the eq file
    if(magEq["1D profiles"])
       oneDim = magEq["1D profiles"];
    if(magEq["2d profiles"])
       twoDim = magEq["2D profiles"];

    //parse 1D profiles
    if(oneDim["q"])
       std::cout << oneDim["q"][0].as<double>() << "\n";
    //convert some formats
    //...

    //create HDF5 to read out to
    hid_t fileID;
    herr_t stat;
    
    fileID = H5Fcreate("SampleInputEq.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    //now write data to HDF5 file
    //...

    //close file
    stat = H5Fclose(fileID);

    return 0;
}
