#include "LocalOpts.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"


// ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);

using namespace llvm;

bool runOnBasicBlock(BasicBlock &B) {
    return false;
  }

  bool runOnFunction(Function &F) {
    bool Transformed = false;

    for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
      if (runOnBasicBlock(*Iter)) {
        Transformed = true;
      }
    }

    return Transformed;
  }


bool areBlocksAdjacent(const llvm::BasicBlock* block1, const llvm::BasicBlock* block2) {

    const llvm::Instruction* terminator = block1->getTerminator();
 
        // Verifica se il ramo non condizionale punta al secondo basic block
        if (terminator->getSuccessor(0) == block2) {
            return true;
        }

    return false;
}


PreservedAnalyses LoopFusionPass::run([[maybe_unused]] Function &F, FunctionAnalysisManager &AM) {

  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
  int l = 0;
  int BID = 0;

  SmallVector<Loop*> PreOrderLoops = LI.getLoopsInPreorder();
  Loop *LP = nullptr;
  for(Loop *L: PreOrderLoops){
    outs() << "PROCESSING LOOP> " << ++l << "\n";
    if(LP == nullptr)
    {
      LP = L;
      continue;
    }
    if (!areBlocksAdjacent(LP->getExitBlock(),L->getHeader()))
      continue;
    else {
      outs() << LP << " è un loop adiacente a " << L << "\n";
      /*const SCEV *TripCountSCEV = SE.getBackedgeTakenCount(L);
      const APInt TripCount = dyn_cast<SCEVConstant>(TripCountSCEV)->getAPInt();
      errs() << "Loop has " << TripCount.toString(10) << " iterations.\n";*/
    }
  }

  return PreservedAnalyses::none();
}
