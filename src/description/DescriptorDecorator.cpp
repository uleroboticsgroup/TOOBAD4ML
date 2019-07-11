// ----------------------------------------------------------------------------
#include "description/DescriptorDecorator.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cDescriptorDecorator::cDescriptorDecorator(IDescriptor* decoratedComponent) :
		m_decoratedComponent(decoratedComponent) {
}

cDescriptorDecorator::~cDescriptorDecorator() {
    delete m_decoratedComponent;
}


// IDESCRIPTOR INHERITED METHODS
// ----------------------------------------------------------------------------

std::string cDescriptorDecorator::ExtractFeature(
        cCodePropertyGraph& cpg, cBufferOverflow& bof) {

	return m_decoratedComponent->ExtractFeature(cpg, bof);

}
