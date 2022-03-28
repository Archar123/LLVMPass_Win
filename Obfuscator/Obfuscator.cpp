#include "Obfuscator.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/InitializePasses.h"
#include "llvm-c/Initialization.h"
#include "llvm/InitializePasses.h"
#include "llvm/PassRegistry.h"
using namespace llvm;

FunctionPass *llvm::createObfuscatorPasses(bool flag) {
	createFlatteningPass(flag);
	createStringObfuscationPass(flag);
	createSubstitutionPass(flag);
	createBogusPass(flag);
	createObjSymbolEncodePass(flag);
	return NULL;
}

void optAddCustomPass(legacy::PassManagerBase &MPM) {
	void *p = &MPM;
	if ( p != NULL ) 
	{
		MPM.add(createObjSymbolEncodePass(true));
	}
}