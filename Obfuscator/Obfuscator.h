#pragma once
#include "Utils.h"
#include "Substitution.h"
#include "StringObfuscation.h"
#include "Flattening.h"
#include "BogusControlFlow.h"
#include "ObjSymbolEncode.h"
#include "llvm/IR/LegacyPassManager.h"

namespace llvm {
	FunctionPass *createObfuscatorPasses(bool flag);
}

extern "C" {
	// 在clang里根据配置创建自定义pass，called by PassManagerBuilder::populateModulePassManager
	__declspec(dllexport)  void __stdcall optAddCustomPass(legacy::PassManagerBase &MPM);
}
