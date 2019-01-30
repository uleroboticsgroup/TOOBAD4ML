#include "description/CPPGExplorer.h"

using namespace TOOBAD4ML;
using namespace description;

cCPPGExplorer::cCPPGExplorer(IFeatureExtractor* descriptorDecorator) :
		m_descriptor(descriptorDecorator) {
}

llvm::StringRef cCPPGExplorer::Inspect(cCodePseudoPropertyGraph &cppg,
		cBufferOverflow &bufferOverflow) {
	return m_descriptor->ExtractFeature(cppg, bufferOverflow);
}

void cCPPGExplorer::SetDescriptor(IFeatureExtractor* descriptorDecorator) {
	m_descriptor = descriptorDecorator;
}
