//
#include <iostream>
#include <string>
#include <time.h> // time

#include "Logger.h"
#include "Configuration.h"
#include "FileStreamDataLogger.h"
#include "PureState.h"
#include "MixedState.h"
#include "display.h"


void log(const std::string& message) {
    Logger* logger = Logger::getInstance();
    logger->log(message);
}

int main( int argc, char* argv[] ) {

    Configuration config;
    config.applyOptions( argc, argv );
    if ( ! config.isConfigurationOk() ) {
        log( config.getUsageString() );
        exit(1);
    }

    log(config.toString());
    
    //mmm create any data loggers
    FileStreamDataLogger buresOut(config.getBuresDistanceOutputFilename());
    std::ofstream& buresDataStream = buresOut.getDataStream();
    FileStreamDataLogger targetOut(config.getTargetCoefficientsOutputFilename());
    std::ofstream& targetDataStream = targetOut.getDataStream();

    //mmm create states to test
    State* rho1 = new PureState(config.dimension);
    State* rho2 = new MixedState(config.dimension);

    //mmm set initial conditions
    // initial conditions
    double t = 0.0;
    rho1->init();
    rho2->init();

    try{

        Uniform<double> uniformGenerator;
        //uniformGenerator.seed( static_cast<unsigned int>( time(0) ) );

//        rho1->print(t);
//        rho2->print(t);
        writeDiffs(buresDataStream,t,rho1,rho2);
        writeLeadingEVals(targetDataStream,t,rho1,rho2);

        int aHundredth = config.numSteps/100;
        for ( int i = 0; i < config.numSteps; i++ ){


            rho1->step( t, config.stepSize );
            rho2->step( t, config.stepSize );
            rho2->perturb( uniformGenerator, config.noiseUpperBound );
            t += config.stepSize;

            if ( 0 == i%aHundredth ) {
                //rho1->print(t);
                //rho2->print(t);
                writeLeadingEVals(targetDataStream,t,rho1,rho2);
                writeDiffs(buresDataStream,t,rho1,rho2);
            }
            showProgress(Logger::getInstance()->getStream(),i,config.numSteps,config.numQubits);
            if ( i == config.numSteps - 1 ) {
//                rho1->print(t);
//                rho2->print(t);
                writeDiffs(buresDataStream,t,rho1,rho2);
                writeLeadingEVals(targetDataStream,t,rho1,rho2);
            }

        }

    }
    catch( const std::exception& ex ) {
        std::cerr << "exception " << ex.what() << std::endl;
    }

    delete rho1;
    delete rho2;

}

