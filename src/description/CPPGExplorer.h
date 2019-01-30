#ifndef SRC_MODELLING_CPPGEXPLORER_H_
#define SRC_MODELLING_CPPGEXPLORER_H_

#include "description/BufferOverflow.h"
#include "description/CodePseudoPropertyGraph.h"
#include "description/FeatureExtractor.h"

namespace TOOBAD4ML {

namespace description {

class cCPPGExplorer {

public:

	/*!
	 *
	 */
	cCPPGExplorer(IFeatureExtractor*);

	/*!
	 *
	 * @param
	 * @param
	 * @return
	 */
	llvm::StringRef Inspect(cCodePseudoPropertyGraph&,
			cBufferOverflow&);

	/*!
	 *
	 * @param
	 */
	void SetDescriptor(IFeatureExtractor*);

private:

	IFeatureExtractor* m_descriptor;

};
/* cCPPGExplorer */

} /* namespace description  */

} /* namespace TOOBAD4ML */

#endif /* SRC_MODELLING_CPPGEXPLORER_H_ */
