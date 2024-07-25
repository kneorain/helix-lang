/**
 * @author Dhruvan Kartik
 * @copyright Copyright (c) 2024 (CC BY 4.0)
 *
 * @note This code is part of the Helix Language Project and is licensed under the Attribution 4.0
 * International license (CC BY 4.0). You are allowed to use, modify, redistribute, and create
 * derivative works, even for commercial purposes, provided that you give appropriate credit,
 * provide a link to the license, and indicate if changes were made. For more information, please
 * visit: https://creativecommons.org/licenses/by/4.0/ SPDX-License-Identifier: CC-BY-4.0
 *
 * @note This code is provided by the creators of Helix. Visit our website at:
 * https://helix-lang.com/ for more information.
 */
#ifndef __AST_NODES_HH__
#define __AST_NODES_HH__

#include "parser/ast/include/ast.hh"

namespace parser::ast::node {
using namespace token;
// Main Program Structure
struct Program final : ASTBase<Program> {
    AST_NODE_METHODS(Program);
    NodeList<NodePtr<>> statements;
};

struct UntypedParameter;
struct TypedParameter;
struct AnySeparatedID;
struct QualifiedNamespaceID;
struct Suite;
struct Identifier;
struct DefaultArgument;
struct BaseObjectDecl;
struct RequiresDeclaration;
struct AccessModifiers;
struct DerivesDecl;
struct EnumBody;
struct UnionBody;

// Modules and Imports
struct Module final : ASTBase<Module> {
    AST_NODE_METHODS(Module);
    NodePtr<QualifiedNamespaceID> namespaceID;
    NodePtr<Suite> suite;
};

struct ImportStatement final : ASTBase<ImportStatement> {
    AST_NODE_METHODS(ImportStatement);
    NodePtr<QualifiedNamespaceID> namespaceID;
    NodeList<QualifiedNamespaceID> importList;
    NodePtr<QualifiedNamespaceID> alias;
};

struct FFIImportStatement final : ASTBase<FFIImportStatement> {
    AST_NODE_METHODS(FFIImportStatement);
    Token ffiString;
    NodePtr<ImportStatement> importStatement;
};

// Preprocessor Directives
struct PreprocessorDirective : ASTBase<PreprocessorDirective> {};
struct DefineMacro final : PreprocessorDirective {
    AST_NODE_METHODS(DefineMacro);
    NodePtr<Identifier> identifier;
    NodeList<UntypedParameter> parameters;
    NodePtr<Suite> suite;
};

struct ProcMacro final : PreprocessorDirective {
    AST_NODE_METHODS(ProcMacro);
    NodePtr<Identifier> identifier;
    NodeList<TypedParameter> parameters;
    NodePtr<Type<void>> returnType;
    NodePtr<Suite> suite;
};

// Control Flow
struct ForLoop final : Statement<ForLoop> {
    AST_NODE_METHODS(ForLoop);
    NodePtr<> loopType; // Either CStyleForLoop or PyStyleForLoop
    NodePtr<Suite> suite;
};

struct WhileLoop final : Statement<WhileLoop> {
    AST_NODE_METHODS(WhileLoop);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct IfStatement final : Statement<IfStatement> {
    AST_NODE_METHODS(IfStatement);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct ElseIfStatement final : Statement<ElseIfStatement> {
    AST_NODE_METHODS(ElseIfStatement);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct ElseStatement final : Statement<ElseStatement> {
    AST_NODE_METHODS(ElseStatement);
    NodePtr<Suite> suite;
};

struct ContinueStatement final : Statement<ContinueStatement> {
    AST_NODE_METHODS(ContinueStatement);
};

struct BreakStatement final : Statement<BreakStatement> {
    AST_NODE_METHODS(BreakStatement);
};

struct SwitchStatement final : Statement<SwitchStatement> {
    AST_NODE_METHODS(SwitchStatement);
    NodeList<NodePtr<>> cases; // CaseStatement or DefaultCaseStatement
};

struct CaseStatement final : Statement<CaseStatement> {
    AST_NODE_METHODS(CaseStatement);
    NodePtr<Expression<void>> condition;
    NodePtr<Suite> suite;
};

struct DefaultCaseStatement final : Statement<DefaultCaseStatement> {
    AST_NODE_METHODS(DefaultCaseStatement);
    NodePtr<Suite> suite;
};

struct MatchExpression final : Expression<MatchExpression> {
    AST_NODE_METHODS(MatchExpression);
    NodeList<std::pair<NodePtr<Expression<void>>, NodePtr<>>> cases; // (Expression | '_') -> (CodeBlock | (':' Expression))
};

// Functions and Methods
struct FunctionDecl final : Declaration<FunctionDecl> {
    AST_NODE_METHODS(FunctionDecl);
    NodePtr<QualifiedNamespaceID> name;
    NodeList<TypedParameter> parameters;
    NodeList<DefaultArgument> defaultArguments;
    NodePtr<Type<void>> returnType;
};

struct FunctionDefinition final : Declaration<FunctionDefinition> {
    AST_NODE_METHODS(FunctionDefinition);
    bool isUnsafe = false;
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<FunctionDecl> functionDecl;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct OperatorDefinition final : Declaration<OperatorDefinition> {
    AST_NODE_METHODS(OperatorDefinition);
    Token op;
    NodePtr<FunctionDecl> functionDecl;
    NodePtr<Suite> suite;
};

struct ReturnExpression final : Expression<ReturnExpression> {
    AST_NODE_METHODS(ReturnExpression);
    NodePtr<Expression<void>> expression;
};

struct YieldExpression final : Expression<YieldExpression> {
    AST_NODE_METHODS(YieldExpression);
    NodePtr<Expression<void>> expression;
};

// Class and Struct
struct BaseObjectDecl : ASTBase<BaseObjectDecl> {
    AST_NODE_METHODS(BaseObjectDecl);
    NodePtr<AccessModifiers> accessModifiers;
    Token qualifier; // inline, async, static, eval, const, ffi
};

struct ClassDefinition final : Declaration<ClassDefinition> {
    AST_NODE_METHODS(ClassDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl> derives;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct EnumDefinition final : Declaration<EnumDefinition> {
    AST_NODE_METHODS(EnumDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<EnumBody> body;
};

struct EnumBody final : ASTBase<EnumBody> {
    AST_NODE_METHODS(EnumBody);
    NodeList<NodePtr<>> parameters; // TypedParameter or UntypedParameter with optional Expression
};

struct StructDefinition final : Declaration<StructDefinition> {
    AST_NODE_METHODS(StructDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct UnionDefinition final : Declaration<UnionDefinition> {
    AST_NODE_METHODS(UnionDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<UnionBody> body;
};

struct UnionBody final : ASTBase<UnionBody> {
    AST_NODE_METHODS(UnionBody);
    NodeList<NodePtr<>> parameters; // TypedParameter or UntypedParameter
};

struct TypeDefinition final : Declaration<TypeDefinition> {
    AST_NODE_METHODS(TypeDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Type<void>> type;
};

// Inheritance and Polymorphism
struct AbstractDefinition final : Declaration<AbstractDefinition> {
    AST_NODE_METHODS(AbstractDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl> derives;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct InterfaceDefinition final : Declaration<InterfaceDefinition> {
    AST_NODE_METHODS(InterfaceDefinition);
    NodePtr<BaseObjectDecl> baseObject;
    NodePtr<QualifiedNamespaceID> name;
    NodePtr<DerivesDecl> derives;
    NodePtr<RequiresDeclaration> _requires;
    NodePtr<Suite> suite;
};

struct DerivesDecl final : ASTBase<DerivesDecl> {
    AST_NODE_METHODS(DerivesDecl);
    NodeList<QualifiedNamespaceID> baseClasses;
};

struct TypeBound final : ASTBase<TypeBound> {
    AST_NODE_METHODS(TypeBound);
    NodePtr<UntypedParameter> parameter;
    NodeList<QualifiedNamespaceID> bounds;
};

struct GenericType final : ASTBase<GenericType> {
    AST_NODE_METHODS(GenericType);
    bool isEval = false;
    NodePtr<> parameter; // TypedParameter or UntypedParameter
    NodePtr<Expression<void>> expression;
};

struct RequiresDeclaration final : ASTBase<RequiresDeclaration> {
    AST_NODE_METHODS(RequiresDeclaration);
    NodeList<GenericType> genericTypes;
    NodeList<TypeBound> typeBounds;
};

// Error Handling
struct CatchDefinition final : ASTBase<CatchDefinition> {
    AST_NODE_METHODS(CatchDefinition);
    NodePtr<AnySeparatedID> identifier;
    NodePtr<QualifiedNamespaceID> alias;
    NodePtr<Suite> suite;
};

struct FinallyDefinition final : ASTBase<FinallyDefinition> {
    AST_NODE_METHODS(FinallyDefinition);
    NodePtr<Suite> suite;
};

struct PanicDefinition final : ASTBase<PanicDefinition> {
    AST_NODE_METHODS(PanicDefinition);
    NodePtr<Expression<void>> expression;
};

struct TryDefinition final : ASTBase<TryDefinition> {
    AST_NODE_METHODS(TryDefinition);
    NodePtr<Suite> suite;
    NodePtr<CatchDefinition> catchBlock;
    NodePtr<FinallyDefinition> finallyBlock;
};

struct TestDefinition final : ASTBase<TestDefinition> {
    AST_NODE_METHODS(TestDefinition);
    Token testName;
    NodePtr<Suite> suite;
};

// Access Specifiers
struct AccessModifiers final : ASTBase<AccessModifiers> {
    AST_NODE_METHODS(AccessModifiers);
    Token modifier; // priv, pub, prot, intl
};

// Concurrency
struct AwaitCall final : ASTBase<AwaitCall> {
    AST_NODE_METHODS(AwaitCall);
    NodePtr<Expression<void>> expression;
};

struct SpawnCall final : ASTBase<SpawnCall> {
    AST_NODE_METHODS(SpawnCall);
    NodePtr<Expression<void>> expression;
};

struct ThreadCall final : ASTBase<ThreadCall> {
    AST_NODE_METHODS(ThreadCall);
    NodePtr<Expression<void>> expression;
};

// Other
struct DeleteCall final : ASTBase<DeleteCall> {
    AST_NODE_METHODS(DeleteCall);
    NodePtr<Expression<void>> expression;
};

// Variable Declarations
struct VariableDeclaration final : Declaration<VariableDeclaration> {
    AST_NODE_METHODS(VariableDeclaration);
    NodePtr<AccessModifiers> accessModifiers;
    bool isUnsafe = false;
    Token qualifier; // const, atomic, shared, eval
    NodePtr<> parameter; // TypedParameter or UntypedParameter
    NodePtr<Expression<void>> initializer;
};

// Type Definitions
struct GenericAccess final : ASTBase<GenericAccess> {
    AST_NODE_METHODS(GenericAccess);
    NodeList<NodePtr<>> identifiers; // QualifiedNamespaceIDOrLiteral
};

struct TupleType final : Type<TupleType> {
    AST_NODE_METHODS(TupleType);
    NodeList<Type<void>> types;
};

// Operators
struct Operator final : ASTBase<Operator> {
    AST_NODE_METHODS(Operator);
    Token op;
};

struct BinaryOperation final : Expression<BinaryOperation> {
    AST_NODE_METHODS(BinaryOperation);
    NodePtr<Expression<void>> left;
    NodePtr<Operator> op;
    NodePtr<Expression<void>> right;
};

struct UnaryOperation final : Expression<UnaryOperation> {
    AST_NODE_METHODS(UnaryOperation);
    NodePtr<Operator> op;
    NodePtr<Expression<void>> expression;
};

// Expressions
struct FunctionCall final : Expression<FunctionCall> {
    AST_NODE_METHODS(FunctionCall);
    NodePtr<AnySeparatedID> function;
    NodePtr<GenericAccess> genericAccess;
    NodeList<Expression<void>> arguments;
};

struct ParenthesizedExpression final : Expression<ParenthesizedExpression> {
    AST_NODE_METHODS(ParenthesizedExpression);
    NodePtr<Expression<void>> expression;
};

struct ArrayAccess final : Expression<ArrayAccess> {
    AST_NODE_METHODS(ArrayAccess);
    NodePtr<AnySeparatedID> array;
    NodePtr<Expression<void>> index;
};

struct ObjectAccess final : Expression<ObjectAccess> {
    AST_NODE_METHODS(ObjectAccess);
    NodePtr<AnySeparatedID> object;
    NodePtr<Identifier> member;
};

struct ConditionalExpression final : Expression<ConditionalExpression> {
    AST_NODE_METHODS(ConditionalExpression);
    NodePtr<Expression<void>> condition;
    NodePtr<Expression<void>> trueExpression;
    NodePtr<Expression<void>> falseExpression;
};

struct Expressions final : ASTBase<Expressions> {
    AST_NODE_METHODS(Expressions);
    NodeList<Expression<void>> expressions;
};

// Statements
struct Assignment final : Statement<Assignment> {
    AST_NODE_METHODS(Assignment);
    NodePtr<AnySeparatedID> variable;
    NodePtr<Expression<void>> expression;
};

struct BlockStatement final : Statement<BlockStatement> {
    AST_NODE_METHODS(BlockStatement);
    NodePtr<Suite> suite;
};

struct Statements final : ASTBase<Statements> {
    AST_NODE_METHODS(Statements);
    NodeList<Statement<void>> statements;
};

// Code Structure
struct CodeBlock final : ASTBase<CodeBlock> {
    AST_NODE_METHODS(CodeBlock);
    NodeList<NodePtr<>> statementsOrExpressions;
};

struct CodeLine final : ASTBase<CodeLine> {
    AST_NODE_METHODS(CodeLine);
    NodePtr<> statementOrExpression;
};

// Base Elements
struct Literal final : Expression<Literal> {
    enum class LiteralType : u8 {
        INVALID,
        BOOL,
        CHAR,
        FLOAT,
        STRING,
        INTEGER,
        SCIENTIFIC,
        NONE
    };

    AST_NODE_METHODS(Literal);
    LiteralType type = LiteralType::INVALID;
    Token value;
};

struct Number final : ASTBase<Number> {
    AST_NODE_METHODS(Number);
    Token value;
};

struct String final : ASTBase<String> {
    AST_NODE_METHODS(String);
    Token value;
};

struct Identifier final : ASTBase<Identifier> {
    AST_NODE_METHODS(Identifier);
    Token value;
};

struct Digit final : ASTBase<Digit> {
    AST_NODE_METHODS(Digit);
    Token value;
};

struct UntypedParameter final : ASTBase<UntypedParameter> {
    AST_NODE_METHODS(UntypedParameter);
    NodePtr<Identifier> identifier;
};

struct TypedParameter final : ASTBase<TypedParameter> {
    AST_NODE_METHODS(TypedParameter);
    NodePtr<Identifier> identifier;
    NodePtr<Type<void>> type;
};

struct AnySeparatedID final : ASTBase<AnySeparatedID> {
    AST_NODE_METHODS(AnySeparatedID);
    NodeList<NodePtr<>> identifiers; // Can be a mix of DotSeparatedID or QualifiedNamespaceID
};

struct QualifiedNamespaceID final : ASTBase<QualifiedNamespaceID> {
    AST_NODE_METHODS(QualifiedNamespaceID);
    NodeList<Identifier> identifiers;
};

struct Suite final : ASTBase<Suite> {
    AST_NODE_METHODS(Suite);
    NodePtr<> content; // Either CodeLine or CodeBlock
};

// Default Argument
struct DefaultArgument final : ASTBase<DefaultArgument> {
    AST_NODE_METHODS(DefaultArgument);
    NodePtr<TypedParameter> parameter;
    NodePtr<Expression<void>> expression;
};

// Helper Functions
struct UntypedParameterList final : ASTBase<UntypedParameterList> {
    AST_NODE_METHODS(UntypedParameterList);
    NodeList<UntypedParameter> parameters;
};

struct TypedParameterList final : ASTBase<TypedParameterList> {
    AST_NODE_METHODS(TypedParameterList);
    NodeList<TypedParameter> parameters;
};

struct DefaultArgumentList final : ASTBase<DefaultArgumentList> {
    AST_NODE_METHODS(DefaultArgumentList);
    NodeList<DefaultArgument> arguments;
};

struct GenericTypeList final : ASTBase<GenericTypeList> {
    AST_NODE_METHODS(GenericTypeList);
    NodeList<GenericType> types;
};

struct TypeBoundList final : ASTBase<TypeBoundList> {
    AST_NODE_METHODS(TypeBoundList);
    NodeList<TypeBound> bounds;
};

struct QualifiedNamespaceIDOrLiteralList final : ASTBase<QualifiedNamespaceIDOrLiteralList> {
    AST_NODE_METHODS(QualifiedNamespaceIDOrLiteralList);
    NodeList<NodePtr<>> identifiersOrLiterals; // QualifiedNamespaceID or Literal
};

struct TypeList final : ASTBase<TypeList> {
    AST_NODE_METHODS(TypeList);
    NodeList<Type<void>> types;
};

struct ExpressionList final : ASTBase<ExpressionList> {
    AST_NODE_METHODS(ExpressionList);
    NodeList<Expression<void>> expressions;
};

}  // namespace parser::ast::node

#endif  // __AST_NODES_HH__