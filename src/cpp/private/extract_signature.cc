#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/ASTDiff/ASTDiff.h>

#include <iostream>
#include <string>

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

class FunctionSignatureVisitor : public RecursiveASTVisitor<FunctionSignatureVisitor> {
public:
    explicit FunctionSignatureVisitor(ASTContext *Context) : Context(Context) {}

    bool VisitFunctionDecl(FunctionDecl *Func) {
        if (Context->getSourceManager().isInMainFile(Func->getLocation())) {
            std::string ReturnType = Func->getReturnType().getAsString();
            std::string FuncName = Func->getNameInfo().getName().getAsString();

            std::string Signature = ReturnType + " " + FuncName + "(";
            for (unsigned int i = 0; i < Func->getNumParams(); ++i) {
                if (i > 0)
                    Signature += ", ";
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

    virtual void HandleTranslationUnit(ASTContext &Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

private:
    FunctionSignatureVisitor Visitor;
};

class FunctionSignatureAction : public ASTFrontendAction {
public:
    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override {
        return std::make_unique<FunctionSignatureConsumer>(&CI.getASTContext());
    }
};

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

int main(int argc, const char **argv) {
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    return Tool.run(newFrontendActionFactory<FunctionSignatureAction>().get());
}
