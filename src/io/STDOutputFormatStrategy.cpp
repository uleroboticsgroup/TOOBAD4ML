#include "STDOutputFormatStrategy.h"

using namespace TOOBAD4ML;
using namespace IO;

bool cSTDOutputFormatStrategy::Write(llvm::raw_ostream& stream, Descriptor descriptor) {
    for (std::string item: descriptor) {
        stream << item << "\n";
    }

    return true;
}
