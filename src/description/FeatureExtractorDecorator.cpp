#include "description/FeatureExtractorDecorator.h"

using namespace TOOBAD4ML;
using namespace description;

cFeatureExtractorDecorator::cFeatureExtractorDecorator(IFeatureExtractor *decoratedComponent) :
		m_DecoratedComponent(decoratedComponent) {
}

llvm::StringRef cFeatureExtractorDecorator::ExtractFeature(cCodePseudoPropertyGraph &cppg,
		cBufferOverflow &bufferOverflow) {

	return m_DecoratedComponent->ExtractFeature(cppg, bufferOverflow);

}
