
#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include "isingLattice.h"
#include "filewriter.h"
int main(int argc, char* argv[]){
    uint32_t N(20);
    uint32_t nSamples(10000);
    double B(0.0);
    
    if(!(argc==3 || argc==4 )|| (argc==2 && strcmp(argv[1],"--help")==0 ))
	{
		std::string errormessage;
		errormessage="usage: ./isingMagnet numberOfSamples sizeOfLattice magneticFieldStrength \n";
		throw std::runtime_error(errormessage);
	}
	else
	{
		nSamples=atoi(argv[1]);
        N=atoi(argv[2]);
		if(argc==4) B=atof(argv[3]);
	}
    //implement lattice 
    IsingLattice lattice(N,1,B); 
    lattice.fillLattice(); 
    lattice.printLattice();
    std::cout << "Magnetization=" << lattice.getMagnetization () << std::endl;
    std::cout << "Energy=       " << lattice.getEnergy () << std::endl;
    std::cout << "Lattice(2,3)  " <<lattice.getLatticeEntry(2,3) << std::endl;
    

};