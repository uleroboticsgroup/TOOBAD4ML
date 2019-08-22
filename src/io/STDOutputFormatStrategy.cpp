#include "STDOutputFormatStrategy.h"
// ------------------------------------------------------------------------
#include <iostream>
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace IO;

// CLASS METHODS
// ------------------------------------------------------------------------
bool cSTDOutputFormatStrategy::Write(llvm::raw_ostream& stream, Descriptor descriptor) {
    stream << "Results:" << "\n";
    
    for (std::string item: descriptor) {
        stream << item << "\n";
    }

    return true;
}
