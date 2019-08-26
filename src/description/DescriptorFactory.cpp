#include "description/DescriptorFactory.h"
#include "description/Descriptor.h"
#include "description/PadmanabhuniBuilder.h"
// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;

// CLASS METHODS
// ----------------------------------------------------------------------------
IDescriptor* cDescriptorFactory::CreateDescriptor(std::string descriptor) {
    eDescriptor descriptorType = getDescriptor(descriptor);
    
    if (descriptorType == eDescriptor::PADMANABHUNI) {
        cPadmanabhuniBuilder builder;
        return builder.CreateDescriptor();
    }
}

eDescriptor cDescriptorFactory::getDescriptor(std::string descriptor) {
    if (descriptor == "Padmanabhuni") {
        return eDescriptor::PADMANABHUNI;
    }
}