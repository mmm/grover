// Configuration.h

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <string>

namespace SimTools {

    class Configuration {
      public:
        Configuration();
        void applyOptions( const int argc, char *const argv[] );
        const bool isConfigurationOk() const;
        const std::string& getBuresDistanceOutputFilename() const;
        const std::string& getTargetCoefficientsOutputFilename() const;
        const std::string toString() const;
        const std::string getUsageString() const;
    
        //mmm move these
        int numQubits;
        int numSteps;
        double stepSize;
        double noiseUpperBound;
        int dimension;
    
      private:
        bool configurationOk;
        std::string buresDistanceOutputFilename;
        std::string targetCoefficientsOutputFilename;
        const std::string& decorateFilename(const std::string& baseName) const;
    };
    
} 
    
#endif // _CONFIGURATION_H_
