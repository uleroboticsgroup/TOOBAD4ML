#include "description/Declaration.h"
#include "description/BufferOverflow.h"
#include "iostream"
using namespace TOOBAD4ML;
using namespace description;

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cDeclaration::cDeclaration(IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};


std::string cDeclaration::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	std::string decoratedFeature =
			cDescriptorDecorator::ExtractFeature(cpg, bof);

	std::string feature = "-1";


    clang::DeclRefExpr* dstBuffer = bof.GetBuffer(BufferType::DST);
    
    //TODO
    
	return decoratedFeature.append(feature).append(cDescriptorDecorator::FEATURE_SEPARATOR);
}