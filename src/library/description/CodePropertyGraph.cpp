#include "description/CodePropertyGraph.h"
#include "clang/Basic/LangOptions.h"
#include "ASTTraversal/FindStmtVisitor.h"

// ----------------------------------------------------------------------------
using namespace TOOBAD4ML;
using namespace description;
// ----------------------------------------------------------------------------

// CONSTRUCTORS & DESTRUCTORS
// ----------------------------------------------------------------------------

cCodePropertyGraph::cCodePropertyGraph(clang::FunctionDecl& functionDecl)
    : m_AST(functionDecl) {

    // prevent building the CFG of undefined functions
    assert(m_AST.doesThisDeclarationHaveABody() == true);
    m_CFG = clang::CFG::buildCFG(&m_AST, m_AST.getBody(),
				&m_AST.getASTContext(), clang::CFG::BuildOptions());

    //m_CFG.get()->dump(*(new clang::LangOptions()), true);
}

cCodePropertyGraph::~cCodePropertyGraph() {
    m_CFG.reset();
    // clang will take care of freeing the AST reference
}

// CLASS METHODS
// ----------------------------------------------------------------------------

SinkPathGraph cCodePropertyGraph::GetSPG(clang::Expr& sink) {
    SinkPathGraph SPG;
    clang::CFGBlock* sinkBlock;
    std::vector<clang::CFGBlock*> affectedBlocks;

    for(clang::CFG::iterator it = m_CFG->begin(); it != m_CFG->end() - 1; ++it) {
        if (affectedBlocks.size() > 0) {
            // Does this block affect our sink?
            for(auto succ_iterator = (*it)->succ_begin(); succ_iterator != (*it)->succ_end(); ++succ_iterator) {
                if ((*succ_iterator).isReachable()) {
                    if(std::find(affectedBlocks.begin(), affectedBlocks.end(), (*succ_iterator).getReachableBlock()) != affectedBlocks.end()) {
                        affectedBlocks.push_back(*it);
                        break;
                    }
                }
                else {
                    if(std::find(affectedBlocks.begin(), affectedBlocks.end(), (*succ_iterator).getPossiblyUnreachableBlock()) != affectedBlocks.end()) {
                        affectedBlocks.clear();
                        affectedBlocks.push_back(sinkBlock);
                        it = m_CFG->end() - 2;
                        break;
                    }
                }
                
            }
        }
        else {
            // Is this block the one which contains our sink?
            for (clang::CFGBlock::iterator elementIt = (*it)->begin(); elementIt != (*it)->end(); ++elementIt) {
                if((*elementIt).getKind() == clang::CFGElement::Kind::Statement) {
                    clang::CFGStmt currentStmt = (*elementIt).castAs<clang::CFGStmt>(); 
                    if (currentStmt.getStmt() == &sink) {
                        sinkBlock = *it;
                        affectedBlocks.push_back(*it);
                        break;
                    }
                }
            }
        }        
    }

    // Get all the instructions from the blocks which affect the sink
    std::vector<clang::CFGStmt> stmtCallExprs;
    for (clang::CFGBlock* block: affectedBlocks) {
        stmtCallExprs.clear();
        for (clang::CFGBlock::iterator instruction = block->begin(); instruction != block->end(); ++instruction) {
            if((*instruction).getKind() == clang::CFGElement::Kind::Statement) {
                clang::CFGStmt currentStmt = (*instruction).castAs<clang::CFGStmt>();

                if (currentStmt.getStmt()->getStmtClass() == clang::Stmt::StmtClass::CallExprClass) {
                    stmtCallExprs.push_back(currentStmt);
                }   
                else {
                    ASTTraversal::cFindStmtVisitor visitor(stmtCallExprs);
                    visitor.TraverseStmt(const_cast<clang::Stmt*>(currentStmt.getStmt()));

                    if (visitor.CallExprFound()) {
                        for(std::vector<clang::CFGStmt>::iterator it = stmtCallExprs.begin(); it != stmtCallExprs.end(); ++it) {
                            if ((*it).getStmt() == visitor.CallExprFound()) {
                                stmtCallExprs.erase(it);
                                break;
                            }
                        }    
                    }
    
                    SPG.push_back(currentStmt);
                }
                
                if (currentStmt.getStmt() == &sink) {
                    // Any further instruction does not affect our sink
                    break;
                }

            }
        }

        // Remaining CallExprs do not belong to any of the already added statements -> we add them
        for(clang::CFGStmt stmt: stmtCallExprs) {
            SPG.push_back(stmt);
        }    
    }

    return SPG;
    }


// ACCESSOR METHODS
// ----------------------------------------------------------------------------

const clang::FunctionDecl& cCodePropertyGraph::GetAST() {
	return m_AST;
}

const clang::CFG& cCodePropertyGraph::GetCFG(){
	return *m_CFG;
}
