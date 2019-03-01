#include "description/InputClassification.h"
#include "description/BufferOverflow.h"


// ----------------------------------------------------------------------------

using namespace TOOBAD4ML;
using namespace description;


// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cInputClassification::cInputClassification(
		IDescriptor* decoratedComponent) :
		cDescriptorDecorator(decoratedComponent) {
};

// INHERITED METHODS
// ----------------------------------------------------------------------------

llvm::StringRef cInputClassification::ExtractFeature(
        cCodePropertyGraph &cpg, cBufferOverflow &bof) {

	llvm::outs() << "Al extractFeature llega.\n";

	const int ARRAYLENGTH = 4;
	// This array represents features counter
	int featuresArray[ARRAYLENGTH];

	//Initialize it to zero
	for(int i = 0 ; i < ARRAYLENGTH; i++)
		featuresArray[i] = 0;


	//TODO cambiar los std::string por llvm::SmallString
	std::string decoratedFeature = cDescriptorDecorator::ExtractFeature(
			cpg, bof);

	llvm::outs() << "Después de decoratedFeature llega.\n";


	std::map<llvm::StringRef, llvm::StringRef> inputClassificationtypes {
			{ "scanf", "1" }, { "gets", "1" }, // Command line
			{ "getwd", "2" }, { "getcwd", "2" }, // Environment
			{ "fscanf", "3" }, { "fgetc", "3" }, // File
			{ "recv", "4" }, { "recvfrom", "4" }, { "recvmsg", "4" }, // Network
	};


	// TODO: replace the ; with a constant
	std::string feature;


	//bufferOverflow.SetInput(cppg);

	std::vector<clang::CallExpr*> input = bof.GetInput();
	llvm::outs() << "Input size from InputClassi: " << input.size() << "\n";

	int index = 0;
	for (std::vector<clang::CallExpr*>::iterator it = input.begin();
			it != input.end(); it++) {




		llvm::outs() << "THAT'S THE GETDIRECTCALLE!!!!: " << (*it)->getDirectCallee()->getNameAsString() << "\n";
		inputClassificationtypes.find(
						(*it)->getDirectCallee()->getNameAsString())->second.getAsInteger(0, index);
		llvm::outs() << "THAT'S THE INDEX!!!!: " << index << "\n";

		featuresArray[index-1] +=1;
		llvm::outs() << "THAT'S THE SUM!!!!: " << featuresArray[index-1] << "\n";

	}

	for(int i = 0; i < ARRAYLENGTH; i++){
		feature += std::to_string(featuresArray[i]) + cDescriptorDecorator::FEATURE_SEPARATOR;
	}

	llvm::outs() << "InputClassification: " <<  feature << "\n";
	return decoratedFeature + feature.append(cDescriptorDecorator::FEATURE_SEPARATOR);
}
