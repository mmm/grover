// Configuration.h

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <string>
#include <fstream>

class Configuration {
  public:
    Configuration();
    void applyOptions( const int argc, char *const argv[] );
    const bool areOptionsOk();
    const std::string& getBuresDistanceOutputFilename() const;
    const std::string& getTargetCoefficientsOutputFilename() const;
    const std::string print() const;

    //mmm move these
    int numQubits;
    int numSteps;
    double stepSize;
    double noiseUpperBound;
    int dimension;

  private:
    std::string buresDistanceOutputFilename;
    std::string targetCoefficientsOutputFilename;
    void usage();
    const std::string& decorateFilename(const std::string& baseName) const;
};


#endif // _CONFIGURATION_H_
