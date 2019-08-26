#ifndef TOOBAD4ML_DESCRIPTION_DESCRIPTORFACTORY_H_
#define TOOBAD4ML_DESCRIPTION_DESCRIPTORFACTORY_H_
// ----------------------------------------------------------------------------
#include <string>
// ----------------------------------------------------------------------------

namespace TOOBAD4ML {

namespace description {

// CLASS FORWARDING
// ----------------------------------------------------------------------------
class IDescriptor;

enum eDescriptor {
    PADMANABHUNI
};

/*!
 * \class cDescriptorFactory
 *
 * \brief
 * A factory to produce the different types of descriptors.
 *
 * \details
 * This class is an implementation of the abstract factory pattern 
 * to generate the different types of descriptors implemented
 * 
 * Currently it supports 
 *  - Padmanabhuni
 */
class cDescriptorFactory {

    // CLASS METHODS
    // ------------------------------------------------------------------------
public:
    IDescriptor* CreateDescriptor(std::string);

private:
    eDescriptor getDescriptor(std::string);
};

} /* DESCRIPTION */

} /* TOOBAD4ML */

#endif /* TOOBAD4ML_DESCRIPTION_DESCRIPTORFACTORY_H_ */
