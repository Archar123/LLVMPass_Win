#include "ObjSymbolEncode.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Module.h" //for module, not function.
#include "llvm/Support/raw_ostream.h"
#include "CryptoUtils.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace llvm;

static std::string obfcharacters="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int seed = 0;
std::string encodeString(std::string org_str) {
    std::string new_str = org_str;
    for(int i=0; i < org_str.size(); i++) {
        new_str[i] = obfcharacters[int(org_str[i]) % 26];
        //new_str[i] = int(org_str[i]) + 1;
    }
    return new_str;
}

namespace {
    class ObjSymbolEncode : public ModulePass {
        public:
        static char ID;
        bool flag;
        ObjSymbolEncode() : ModulePass(ID) {}
        bool runOnModule(Module &M);
        ObjSymbolEncode(bool flag) : ModulePass(ID) { this->flag = flag; ObjSymbolEncode(); }
    };
}

bool ObjSymbolEncode::runOnModule(Module &M) {
    if (!flag)
    {
        outs() << "not run obj symbol encode. \n";
        return false;
    }
    outs() << "run obj symbol encode. \n";
    for(Module::iterator Fun=M.begin();Fun!=M.end();Fun++) {
        Function &F=*Fun;
        if (F.getName().str().compare("main")==0) {
            errs()<<"Skipping main\n";
        }
        else if(F.empty()==false) {
            errs()<<"Internal Function: "<<F.getName()<<"\n";
        }
        else {  //need ignore startwith llvm.
            errs()<<"External Function:"<< F.getName() <<"\n";
            if (F.getName().startswith_lower("llvm."))
            {
                errs()<<"llvm self, ignore\n";
                continue;
            }
            
            std::string new_name = encodeString(F.getName().str());
            errs()<<"(Org Function: "<< F.getName() <<")(New Function: "<< new_name <<")\n";
            F.setName(new_name);
        }
    }
    return true;
}

char ObjSymbolEncode::ID = 0;
static RegisterPass<ObjSymbolEncode> X("symbol_obf", "Encode Obj Symbol.");

Pass *llvm::createObjSymbolEncodePass(bool flag) {return new ObjSymbolEncode(flag);}