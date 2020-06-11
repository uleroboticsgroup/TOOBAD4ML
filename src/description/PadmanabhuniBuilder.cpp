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
#include "description/DataBufferDeclaration.h"
#include "description/NumberOfElementsCopiedWithinBounds.h"
#include "description/ArrayWriteIndexWithinBounds.h"
#include "description/FormatStringPrecisionWithinBounds.h"
#include "description/NumberOfElementsCopiedWithinBounds.h"
#include "description/StringCopyWithinBounds.h"
#include "description/DataDependentOnDestinationBufferSize.h"
#include "description/DataDependentOnDestinationBufferSizeVariant.h"
#include "description/IsCharacterCaseConversionSink.h"
#include "description/ResetsInControlPredicates.h"
#include "description/StringLengthSourceBuffer.h"
#include "description/NULLCheck.h"
#include "description/SizeSourceBuffer.h"
#include "description/EOFCheck.h"
#include "description/CharacterCheck.h"
#include "description/CharacterOccurrenceStringCheck.h"
#include "description/StringComparison.h"
#include "description/SizeDestinationBuffer.h"
#include "description/SizeDestinationBufferMinusOne.h"
#include "description/SizeDestinationBufferMinusX.h"
#include "description/StringLengthDestinationBuffer.h"
#include "description/ContainerType.h"
#include "description/IndexType.h"
#include "description/LengthType.h"
#include "description/AddressType.h"
#include "description/PointerDeference.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------


// IDESCRIPTORBUILDER INHERITED METHODS
// ------------------------------------------------------------------------

IDescriptor* cPadmanabhuniBuilder::CreateDescriptor() {

	// the comments characteristics are not implemented

    return // new cResetsInControlPredicates(
		new cPointerDeference(
		new cAddressType(
		new cLengthType(
		new cIndexType(
		new cContainerType(
		new cStringLengthDestinationBuffer(
		new cSizeDestinationBufferMinusX(
		new cSizeDestinationBufferMinusOne(
		new cSizeDestinationBuffer(
		new cStringComparison(
		new cCharacterOccurrenceStringCheck(
		new cCharacterCheck(
		new cEOFCheck(
		new cSizeSourceBuffer(
		new cNULLCheck(
		new cStringLengthSourceBuffer(
		new cIsCharacterCaseConversionSink(
		// new cDataDependentOnDestinationBufferSizeVariant(
		// new cDataDependentOnDestinationBufferSize(
		new cStringCopyWithinBounds(
		new cFormatStringPrecisionWithinBounds(
		new cArrayWriteIndexWithinBounds(
		new cNumberOfElementsCopiedWithinBounds(
		// new cDataBufferDeclaration(
		// new cBufferSizePredicateClassification(
		// new cInputValidationClassification(
		new cNetwork(
		new cFile(
		new cEnvironmentVariable(
		new cCommandLine(
		new cSinkClassification(
		new cMockDescriptor)
	)))))))))))))))))))))))));

}
