// ----------------------------------------------------------------------------
#include "description/CPGExplorer.h"
#include "description/Descriptor.h"
#include "description/CodePropertyGraph.h"
#include "description/BufferOverflow.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cCPGExplorer::cCPGExplorer(IDescriptor* descriptor)
    : m_descriptor(descriptor) {
}

cCPGExplorer::~cCPGExplorer() {
    delete m_descriptor;
}


// CLASS METHODS
// ----------------------------------------------------------------------------

std::string cCPGExplorer::Inspect(cCodePropertyGraph &cpg, cBufferOverflow &bof) {
	return m_descriptor->ExtractFeature(cpg, bof);
}


// ACCESSOR METHODS
// ----------------------------------------------------------------------------

void cCPGExplorer::SetDescriptor(IDescriptor* descriptor) {
	m_descriptor = descriptor;
}
