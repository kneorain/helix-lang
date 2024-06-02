#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/ASTDiff/ASTDiff.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include <iostream>
#include <string>

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

class FunctionSignatureVisitor : public RecursiveASTVisitor<FunctionSignatureVisitor> {
  public:
    explicit FunctionSignatureVisitor(ASTContext *Context)
        : Context(Context) {}

    bool VisitFunctionDecl(FunctionDecl *Func) {
        if (Context->getSourceManager().isInMainFile(Func->getLocation())) {
            std::string const ReturnType = Func->getReturnType().getAsString();
            std::string const FuncName = Func->getNameInfo().getName().getAsString();

            std::string Signature = ReturnType + " " + FuncName + "(";
            for (unsigned int i = 0; i < Func->getNumParams(); ++i) {
                if (i > 0) {
                    Signature += ", ";
                }
                Signature += Func->getParamDecl(i)->getType().getAsString();
            }
            Signature += ")";

            std::cout << Signature << std::endl;
        }
        return true;
    }

  private:
    ASTContext *Context;
};

class FunctionSignatureConsumer : public ASTConsumer {
  public:
    explicit FunctionSignatureConsumer(ASTContext *Context)
        : Visitor(Context) {}

    void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

  private:
    FunctionSignatureVisitor Visitor;
};

class FunctionSignatureAction : public ASTFrontendAction {
  public:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &compilerInstance,
                                                   StringRef file) override {
        return std::make_unique<FunctionSignatureConsumer>(&compilerInstance.getASTContext());
    }
};

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

int main(int argc, const char **argv) {
    auto OptionsParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
    if (!OptionsParser) {
        llvm::errs() << OptionsParser.takeError();
        return 1;
    }
    ClangTool Tool(OptionsParser->getCompilations(), OptionsParser->getSourcePathList());

    return Tool.run(newFrontendActionFactory<FunctionSignatureAction>().get());
}

// use case: ./main src/main.cc