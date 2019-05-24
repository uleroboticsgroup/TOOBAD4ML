#ifndef TOOBAD4ML_DESCRIPTION_FORMATSTRINGPRECISIONWITHINBOUNDS_H_
#define TOOBAD4ML_DESCRIPTION_FORMATSTRINGPRECISIONWITHINBOUNDS_H_

#include "description/DescriptorDecorator.h"
#include <clang/AST/Expr.h>

namespace TOOBAD4ML {

namespace description {

/*!
 * \class cFormatStringPrecisionWithinBounds
 *
 * \brief
 * Checks if the size of elements to be copied
 * is not greater than the destination buffer size.
 *
 * \details
 * This is applicable for sink types 4 and 6. (format string)
 * It can have one of the three values:
 * (=1) True
 * (=0) False
 * (=-1) Not applicable
 *
 */
class cFormatStringPrecisionWithinBounds: public cDescriptorDecorator {
public:
	// CONSTRUCTORS & DESTRUCTORS
	// ------------------------------------------------------------------------

	cFormatStringPrecisionWithinBounds(IDescriptor*);


	// INHERITED METHODS
	// ------------------------------------------------------------------------

	std::string ExtractFeature(cCodePropertyGraph&, cBufferOverflow&);

	/*!
	 *	Gets the size to be copied into buffer from format string.
	 *
	 * @param formatString, StringLiteral of AST node
	 * @param name of function to be parsed
	 * @param sink
	 * @return limit to be copied
	 */
	int FormatStringParser(llvm::StringRef, std::string, clang::Expr*);

}; /*cFormatStringPrecisionWithinBounds*/

} /* description */

} /* namespace TOOBAD4ML */

#endif /* SRC_DESCRIPTION_FORMATSTRINGPRECISIONWITHINBOUNDS_H_ */
