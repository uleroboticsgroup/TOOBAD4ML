#include "CSVOutputFormatStrategy.h"
#include <llvm/Support/raw_ostream.h>
// ------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace IO;

// CLASS METHODS
// ------------------------------------------------------------------------
bool cCSVOutputFormatStrategy::Write(llvm::raw_ostream& stream, Descriptor descriptor) {
    for (std::string item: descriptor) {
        stream << item << "\n";
    }

    stream.flush();
    return true;
}
