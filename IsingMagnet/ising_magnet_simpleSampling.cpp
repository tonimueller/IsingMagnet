
#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include "isingLattice.h"
#include "filewriter.h"
int main(int argc, char* argv[]){
    uint32_t N(20);
    uint32_t nSamples(1000000);
    uint32_t steps(500);
    double B(0.0);
    
    if(!(argc==3 || argc==4 )|| (argc==2 && strcmp(argv[1],"--help")==0 ))
	{
		std::string errormessage;
		errormessage="usage: ./isingMagnet_SS numberOfSamples sizeOfLattice magneticFieldStrength \n";
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
    


    
    //parameter
    std::string outputM("TempMagnet_SimpleSampling.dat");
    std::string outputE("TempEnergy_SimpleSampling.dat");
    std::vector<double> temperature{5,4,3,2.5,2.27,2.2,2.1,2,1.5,1,0.5,0.2};
    auto nTemps(temperature.size());
    std::vector<double> magnetization(nTemps,0.);
    std::vector<double> energy(nTemps,0.);
    std::vector<double> norm(nTemps,0.);

    //simple sampling
    for (auto t=0; t<temperature.size();t++){
        std::cout << "Temperature= " << temperature[t] << std::endl; 
        for(auto n=0;n<nSamples;n++){
            lattice.fillLattice();
            double E(lattice.getEnergy());
            double M((lattice.getMagnetization()));
            auto bweight(exp(-1.0*E/temperature[t])); //Boltzmann weight
            // std::cout << M << " " << E << " "<< bweight<< std::endl;
            magnetization[t]+=M*bweight;
            energy[t]+=E*bweight;
            norm[t]+=bweight;
        }
        // magnetization[t]/=static_cast<double>(nSamples)/norm[t];
        // energy[t]/=static_cast<double>(nSamples)/norm[t];
        magnetization[t]/=norm[t];
        energy[t]/=norm[t];
    }
    FileWriter writer(outputM);
    std::vector<std::vector<double> > data;
    data.insert(data.begin(),magnetization); 
    data.insert(data.begin(),temperature);
    writer.writeData(data,"T M\n");

    data.resize(0);
    writer.setFilename(outputE);
    data.insert(data.begin(),energy); 
    data.insert(data.begin(),temperature);
    writer.writeData(data,"T E\n");

};