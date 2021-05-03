
#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include "isingLattice.h"
#include "filewriter.h"
#include <chrono>
int main(int argc, char* argv[]){
    ////////////////////////////////////////////////////////////////////////////////
    //parameter
    uint32_t N(20);
    uint32_t nSamples(1000000);
    uint32_t steps(500);
    double B(0.0);
    auto nIterations=200;
    auto nSteps=20;
    std::string outputM("TempMagnet_ImportanceSampling.dat");
    std::string outputE("TempEnergy_ImportanceSampling.dat");
    std::string outputE2("TempEnergy2_ImportanceSampling.dat");
    std::vector<double> temperature{5,4,3,2.5,2.2,2,1.7,1.5,1.4,1.35,1.3,1.25,1.2,1.15,1.1,1.05,1,0.9,0.7,0.5};
    ////////////////////////////////////////////////////////////////////////////////
    //command line parser 
    if(!(argc==5 || argc==6 )|| (argc==2 && strcmp(argv[1],"--help")==0 ))
	{
		std::string errormessage;
		errormessage="usage: ./isingMagnet numberOfSamples sizeOfLattice  nIterations nSteps magneticFieldStrength \n";
		throw std::runtime_error(errormessage);
	}
	else
	{
		nSamples=atoi(argv[1]);
        N=atoi(argv[2]);
        nIterations=atoi(argv[3]);
        nSteps=atoi(argv[4]);
		if(argc==6) B=atof(argv[5]);
	}
    ////////////////////////////////////////////////////////////////////////////////
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //implement lattice 
    IsingLattice lattice(N,1,B); 
    ////////////////////////////////////////////////////////////////////////////////   
    auto nTemps(temperature.size());
    std::vector<double> magnetization(nTemps,0.);
    std::vector<double> energy(nTemps,0.);
    std::vector<double> energy2(nTemps,0.);
    uint32_t eqIterations(10);
    //Metropolis
    for (auto t=0; t<temperature.size();t++){
        std::cout << "Temperature= " << temperature[t] << std::endl; 
        for(auto n=0;n<nSamples;n++){
            lattice.fillLattice();
            for(auto it=0;it<nIterations;it++){
                auto check= lattice.MCStep(temperature[t],nSteps);
                // if(it <3 && check==0) {n--; break;}
                //equilibrate for 10 iterations
                if(it>eqIterations){
                    double E(lattice.getEnergy());
                    double M((lattice.getMagnetization()));
                    magnetization[t]+=abs(M);
                    energy[t]+=E;
                    energy2[t]+=E*E;
                }
            }
        }
        magnetization[t]/=((nIterations-eqIterations)*nSamples);
        energy[t]/=((nIterations-eqIterations)*nSamples);
        energy[t]/=((nIterations-eqIterations)*nSamples);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> duration(end - begin);
    std::cout << "Time difference = " << std::chrono::duration<double> (end - begin).count() << "s" << std::endl;
    std::cout << "time/(MCS*Sample) = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count()/(static_cast<double>(nTemps*nSamples*nIterations*nSteps)) << "us" << std::endl;
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

    data.resize(0);
    writer.setFilename(outputE2);
    data.insert(data.begin(),energy2); 
    data.insert(data.begin(),temperature);
    writer.writeData(data,"T E2\n");

};