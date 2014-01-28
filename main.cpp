#include "yaml-cpp/yaml.h"
#include "hdf5.h"

int main()
{
    //read in a YAML
    YAML::Node magEq = YAML::LoadFile("analytic.yaml");

    //do some parsing!

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
