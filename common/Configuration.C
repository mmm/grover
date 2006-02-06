// Configuration.C

#include <iostream>
#include <unistd.h> // getopt
#include <cmath> // pow

#include "Configuration.h"


const std::string Configuration::getUsageString( void ) const {
    std::cout << "Usage: stepper [options]" << std::endl
         << "Where options are:" << std::endl
         << "-d prob-output-datafile " << std::endl
         << "-n num-steps"  << std::endl
         << "-o bures-distances-output-datafile" << std::endl
         << "-q num-qubits"  << std::endl
         << "-s step-size"  << std::endl
         << "-u noise-threshold" << std::endl;
    return "";
}



Configuration::Configuration() {
    configurationOk = true;
    numQubits = 4;
    numSteps = 500; 
    stepSize = 0.0001;
    buresDistanceOutputFilename = "output/BuresDistances.out";
    targetCoefficientsOutputFilename = "output/targetCoeff.out";
    noiseUpperBound = 0.005; // biggest noise can get... kinda
                               // works between 0.001 and 0.01
}

void Configuration::applyOptions( const int argc, char *const argv[] ) {
    int opt = 0;
    while ( (opt = getopt( argc, argv, "d:n:o:q:s:u:" )) != -1 ) {
        switch ( opt ) {
        case 'd':
            targetCoefficientsOutputFilename = optarg;
            break;
        case 'n':
            numSteps = atoi(optarg);
            break;
        case 'o':
            buresDistanceOutputFilename = optarg;
            break;
        case 'q':
            numQubits = atoi(optarg);
            break;
        case 's':
            stepSize = atof(optarg);
            break;
        case 'u':
            noiseUpperBound = atof(optarg);
            break;
        default:
            configurationOk = false;
        }
    }

    dimension = int( pow( 2, numQubits ) );




}

const std::string& Configuration::decorateFilename(const std::string& baseName)  const {
    // outputfile stuff
    std::string returnBuffer(baseName);
    char filenameExtras[5 + sizeof(int) + 2*sizeof(double)] = ""; //mmm
    sprintf( filenameExtras, "-%d-n%f-s%f", numQubits, noiseUpperBound, stepSize );
    return returnBuffer += filenameExtras;

//    buresDistanceOutputFilename += filenameExtras;
//    targetCoefficientsOutputFilename += filenameExtras;
//    buresDistanceOutputFileStream = new std::ofstream( buresDistanceOutputFilename.c_str() );
//    targetCoefficientsOutputFileStream = new std::ofstream( targetCoefficientsOutputFilename.c_str() );
//    if ( !buresDistanceOutputFileStream || !targetCoefficientsOutputFileStream ) {
//        std::cerr << "Oops!  An output file stream is bad." << std::endl;
//        exit(1);
//    }

}

const std::string& Configuration::getBuresDistanceOutputFilename() const {
    return decorateFilename( buresDistanceOutputFilename );
}
const std::string& Configuration::getTargetCoefficientsOutputFilename() const {
    return decorateFilename( targetCoefficientsOutputFilename );
}

const bool Configuration::isConfigurationOk() const {
    return true;
}

const std::string Configuration::toString() const {

// tell me about the configuration
    std::cout << "Bures distance -v- time to " 
         <<  buresDistanceOutputFilename << std::endl;
    std::cout << "target state prob -v- time to " 
         <<  targetCoefficientsOutputFilename << std::endl;
    std::cout << "numQubits = " << numQubits << std::endl;
    std::cout << "numSteps = " << numSteps << std::endl;
    std::cout << "step size = " << stepSize << std::endl;
    std::cout << "upper bound = " << noiseUpperBound << std::endl;

    return "";

}
