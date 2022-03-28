#pragma once
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Module.h" //for module, not function.
#include "llvm/Support/raw_ostream.h"

namespace llvm {
	Pass *createObjSymbolEncodePass(bool flag);
}