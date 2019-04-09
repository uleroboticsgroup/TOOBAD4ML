// ----------------------------------------------------------------------------
#include "description/PadmanabhuniBuilder.h"
#include "description/MockDescriptor.h"
#include "description/SinkClassification.h"
#include "description/CommandLine.h"
#include "description/EnvironmentVariable.h"
#include "description/File.h"
#include "description/Network.h"
#include "description/InputValidationClassification.h"
#include "description/BufferSizePredicateClassification.h"
#include "description/SinkCharacteristicsClassification.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------


// IDESCRIPTORBUILDER INHERITED METHODS
// ------------------------------------------------------------------------

IDescriptor* cPadmanabhuniBuilder::CreateDescriptor() {

    return new cSinkCharacteristicsClassification(
            new cBufferSizePredicateClassification(
                new cInputValidationClassification(
                	new cNetwork(
                		new cFile(
                			new cEnvironmentVariable(
                				new cCommandLine(
                					new cSinkClassification(new cMockDescriptor))))))));

}
