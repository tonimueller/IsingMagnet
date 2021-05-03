
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
   
    nSamples=10;
    auto nIterations=200;
    auto nSteps=20;
    std::string outputM_IS("TempMagnet_ImportanceSampling.dat");
    std::string outputE_IS("TempEnergy_ImportanceSampling.dat");
    std::vector<double> temperature_IS{10,5,4,3,2.5,2.27,2.2,2.1,2,1.5,1,0.5,0.2};
    auto nTemps_IS(temperature_IS.size());
    std::vector<double> magnetization_IS(nTemps_IS,0.);
    std::vector<double> energy_IS(nTemps_IS,0.);


    //Metropolis
    for (auto t=0; t<temperature_IS.size();t++){
        std::cout << "Temperature= " << temperature_IS[t] << std::endl; 
        for(auto n=0;n<nSamples;n++){
            lattice.fillLattice();
            for(auto it=0;it<nIterations;it++){
                auto check= lattice.MCStep(temperature_IS[t],nSteps);
                if(it <3 && check==0) {n--; break;}
                //equilibrate for 10 iterations
                if(it>10){
                    double E(lattice.getEnergy());
                    double M((lattice.getMagnetization()));
                    magnetization_IS[t]+=M;
                    energy_IS[t]+=E;
                }
            }
        }
        // magnetization[t]/=static_cast<double>(nSamples)/norm[t];
        // energy[t]/=static_cast<double>(nSamples)/norm[t];
        magnetization_IS[t]/=((nIterations-10)*nSamples);
        energy_IS[t]/=((nIterations-10)*nSamples);
    }

    FileWriter writer_IS(outputM_IS);
    std::vector<std::vector<double> > data_IS;
    data_IS.insert(data_IS.begin(),magnetization_IS); 
    data_IS.insert(data_IS.begin(),temperature_IS);
    writer_IS.writeData(data_IS,"T M\n");

    data_IS.resize(0);
    writer_IS.setFilename(outputE_IS);
    data_IS.insert(data_IS.begin(),energy_IS); 
    data_IS.insert(data_IS.begin(),temperature_IS);
    writer_IS.writeData(data_IS,"T E\n");

};