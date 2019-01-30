#include "description/BufferSizePredicateClassification.h"
#include "description/SinkCharacteristicsClassification.h"
#include "description/InputValidationClassification.h"
#include "description/InputClassification.h"
#include "description/PadmanabhuniBuilder.h"
#include "description/SinkClassification.h"
#include "description/Descriptor.h"

using namespace TOOBAD4ML;
using namespace description;

IFeatureExtractor* cPadmanabhuniBuilder::CreateDescriptor() {

	return new cInputValidationClassification(
			new cSinkCharacteristicsClassification(
					new cInputClassification(
							new cBufferSizePredicateClassification(
									new cSinkClassification(new cDescriptor)))));
}
