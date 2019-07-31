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

// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------


// IDESCRIPTORBUILDER INHERITED METHODS
// ------------------------------------------------------------------------

IDescriptor* cPadmanabhuniBuilder::CreateDescriptor() {

	// the comments characteristics are not implemented

    return // new cResetsInControlPredicates(
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
																	new cSinkClassification(new cMockDescriptor)))))))))));

}
