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
#include "parser/ast/include/nodes.hh"

namespace parser::ast {

/* ----------------------------- NumericLiteral ---------------------------- */
NumericLiteral::NumericLiteral(Token token)
    : value(std::move(token)) {}

string NumericLiteral::to_string(u16 depth) const {
    return get_indent(depth) + "NumericLiteral(" + '\n' + get_indent(depth + 1) +
           "value: " + value.value() + '\n' + get_indent(depth) + ")";
}

ParseResult<NumericLiteral> NumericLiteral::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void NumericLiteral::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ----------------------------- StringLiteral ----------------------------- */
StringLiteral::StringLiteral(Token token)
    : value(std::move(token)) {}

string StringLiteral::to_string(u16 depth) const {
    return get_indent(depth) + "StringLiteral(" + '\n' + get_indent(depth + 1) +
           "value: " + value.value() + '\n' + get_indent(depth) + ")";
}

ParseResult<StringLiteral> StringLiteral::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void StringLiteral::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ----------------------------- BooleanLiteral ---------------------------- */
BooleanLiteral::BooleanLiteral(Token token)
    : value(std::move(token)) {}

string BooleanLiteral::to_string(u16 depth) const {
    return get_indent(depth) + "BooleanLiteral(" + '\n' + get_indent(depth + 1) +
           "value: " + value.value() + '\n' + get_indent(depth) + ")";
}

ParseResult<BooleanLiteral> BooleanLiteral::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void BooleanLiteral::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ------------------------------ NullLiteral ------------------------------ */
NullLiteral::NullLiteral(Token token)
    : value(std::move(token)) {}

string NullLiteral::to_string(u16 depth) const {
    return get_indent(depth) + "NullLiteral(" + '\n' + get_indent(depth + 1) +
           "value: " + value.value() + '\n' + get_indent(depth) + ")";
}

ParseResult<NullLiteral> NullLiteral::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void NullLiteral::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ----------------------------- Identifier ----------------------------- */
Identifier::Identifier(Token token)
    : value(std::move(token)) {}

string Identifier::to_string(u16 depth) const {
    return get_indent(depth) + "Identifier(" + '\n' + get_indent(depth + 1) +
           "value: " + value.value() + '\n' + get_indent(depth) + ")";
}

ParseResult<Identifier> Identifier::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void Identifier::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ---------------------------- GenericArgument ---------------------------- */
GenericArgument::GenericArgument(AstNodeList<> arguments)
    : arguments(std::move(arguments)) {}

string GenericArgument::to_string(u16 depth) const {
    string result =
        get_indent(depth) + "GenericArgument(" + '\n' + get_indent(depth + 1) + "arguments: [";

    for (const auto &arg : arguments) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!arguments.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    result += "]\n" + get_indent(depth) + ")";

    return result;
}

ParseResult<GenericArgument> GenericArgument::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void GenericArgument::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* --------------------------- GenericInvocation --------------------------- */
GenericInvocation::GenericInvocation(Token token, AstNodeList<GenericArgument> arguments)
    : value(std::move(token))
    , arguments(std::move(arguments)) {}

string GenericInvocation::to_string(u16 depth) const {
    string result = get_indent(depth) + "GenericInvocation(" + '\n' + get_indent(depth + 1) +
                    "value: " + value.value() + '\n' + get_indent(depth + 1) + "arguments: [";

    for (const auto &arg : arguments) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!arguments.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    result += "]\n" + get_indent(depth) + ")";
    return result;
}

ParseResult<GenericInvocation> GenericInvocation::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void GenericInvocation::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ------------------------------- Variable -------------------------------- */
Variable::Variable(AstNodeRef<Identifier> name, AstNodeRef<GenericArgument> type, AstNodePtr value,
                   bool is_nullable, Token reference, Token pointer)
    : name(std::move(name))
    , type(std::move(type))
    , value(std::move(value))
    , is_nullable(is_nullable)
    , reference(std::move(reference))
    , pointer(std::move(pointer)) {}

string Variable::to_string(u16 depth) const {
    return get_indent(depth) + "Variable(" + '\n' + get_indent(depth + 1) +
           "name: " + name->to_string(depth + 1) + '\n' + get_indent(depth + 1) +
           "type: " + (type ? type->to_string(depth + 1) : "null") + '\n' + get_indent(depth + 1) +
           "value: " + (value ? value->to_string(depth + 1) : "null") + '\n' +
           get_indent(depth + 1) + "is_nullable: " + (is_nullable ? "true" : "false") + '\n' +
           get_indent(depth + 1) + "reference: " + reference.value() + '\n' +
           get_indent(depth + 1) + "pointer: " + pointer.value() + '\n' + get_indent(depth) + ")";
}

ParseResult<Variable> Variable::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void Variable::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* -------------------------------- Return --------------------------------- */
Return::Return(AstNodePtr value)
    : value(std::move(value)) {}

string Return::to_string(u16 depth) const {
    return get_indent(depth) + "Return(" + '\n' + get_indent(depth + 1) +
           "value: " + (value ? value->to_string(depth + 1) : "null") + '\n' + get_indent(depth) +
           ")";
}

ParseResult<Return> Return::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void Return::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* -------------------------- BinaryOperation ----------------------------- */
BinaryOperation::BinaryOperation(Token op, AstNodePtr left, AstNodePtr right)
    : op(std::move(op))
    , left(std::move(left))
    , right(std::move(right)) {}

string BinaryOperation::to_string(u16 depth) const {
    return get_indent(depth) + "BinaryOperation(" + '\n' + get_indent(depth + 1) +
           "op: " + op.value() + '\n' + get_indent(depth + 1) +
           "left: " + left->to_string(depth + 1) + '\n' + get_indent(depth + 1) +
           "right: " + right->to_string(depth + 1) + '\n' + get_indent(depth) + ")";
}

ParseResult<BinaryOperation> BinaryOperation::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void BinaryOperation::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* --------------------------- ObjectInvocation ---------------------------- */
ObjectInvocation::ObjectInvocation(Token name, AstNodeList<> arguments,
                                   AstNodeList<GenericArgument> generics,
                                   AstNodeList<> named_arguments)
    : name(std::move(name))
    , arguments(std::move(arguments))
    , generics(std::move(generics))
    , named_arguments(std::move(named_arguments)) {}

string ObjectInvocation::to_string(u16 depth) const {
    string result = get_indent(depth) + "ObjectInvocation(" + '\n' + get_indent(depth + 1) +
                    "name: " + name.value() + '\n' + get_indent(depth + 1) + "arguments: [";

    for (const auto &arg : arguments) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!arguments.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    result += std::string("]") + "\n" + get_indent(depth + 1) + "generics: [";

    for (const auto &arg : generics) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!generics.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    result += std::string("]") + "\n" + get_indent(depth + 1) + "named_arguments: [";

    for (const auto &arg : named_arguments) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!named_arguments.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    return result + "\n" + get_indent(depth) + ")";
}

ParseResult<ObjectInvocation> ObjectInvocation::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void ObjectInvocation::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

/* ------------------------- StructureInvocation -------------------------- */
StructureInvocation::StructureInvocation(Token name, AstNodeList<> arguments,
                                         AstNodeList<GenericArgument> generics,
                                         AstNodeList<> named_arguments)
    : name(std::move(name))
    , arguments(std::move(arguments))
    , generics(std::move(generics)) {
        // prase named_arguments into arguments
    }

string StructureInvocation::to_string(u16 depth) const {
    string result = get_indent(depth) + "ObjectInvocation(" + '\n' + get_indent(depth + 1) +
                    "name: " + name.value() + '\n' + get_indent(depth + 1) + "arguments: [";

    for (const auto &arg : arguments) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!arguments.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    result += std::string("]") + "\n" + get_indent(depth + 1) + "generics: [";

    for (const auto &arg : generics) {
        result += arg->to_string(depth + 1) + ", ";
    }

    if (!generics.empty()) {
        result = result.substr(0, result.size() - 2);
    }

    result += std::string("]");

    return result + "\n" + get_indent(depth) + ")";
}

ParseResult<StructureInvocation> StructureInvocation::validate(TokenList tokens) {
    // Add validation logic here
    return {};
}

void StructureInvocation::accept(class Visitor &visitor) {
    // Add visitor pattern logic here
}

}  // namespace parser::ast