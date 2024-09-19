#ifndef __TEST_HH__
#define __TEST_HH__

#include "PEGTL/include/tao/pegtl.hpp"  // Include PEGTL, scoped only to this header
#include "token/include/token.hh"
#include "token/include/token_list.hh"

#include <memory>
#include <vector>
#include <iostream>

namespace my_parser {

// Base class for AST Nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// AST Node for Variable Declaration
class VarDeclNode : public ASTNode {
public:
    token::Token let_token;
    token::Token identifier_token;
    token::Token assign_token;
    token::Token expr_token;

    VarDeclNode(const token::Token& let_token,
                const token::Token& identifier_token,
                const token::Token& assign_token,
                const token::Token& expr_token)
        : let_token(let_token),
          identifier_token(identifier_token),
          assign_token(assign_token),
          expr_token(expr_token) {}
};

// Custom PEGTL input class for TokenList
class TokenInput {
public:
    using iterator = token::TokenList::TokenListIter;

private:
    iterator current;
    iterator end;

public:
    explicit TokenInput(token::TokenList tokens)
        : current(tokens.begin()), end(tokens.end()) {}

    bool empty() const { return current == end; }

    const token::Token& peek() const {
        if (empty()) {
            throw std::runtime_error("Attempt to peek at an empty TokenInput.");
        }
        return *current;
    }

    void bump() {
        if (!empty()) {
            ++current;
        }
    }

    const std::string& source() const {
        static std::string dummy_source = "source";
        return dummy_source;
    }
};

// Custom rule to match a specific token kind
template <token::tokens ExpectedKind>
struct match_token {
    template <typename Input>
    static bool match(Input& in) {
        auto& token_in = static_cast<TokenInput&>(in);
        if (!token_in.empty() && token_in.peek().token_kind() == ExpectedKind) {
            token_in.bump();
            return true;
        }
        return false;
    }
};


// Grammar Rules
struct keyword_let : match_token<token::tokens::KEYWORD_LET> {};
struct identifier : match_token<token::tokens::IDENTIFIER> {};
struct assign_op : match_token<token::tokens::OPERATOR_ASSIGN> {};
struct literal_expr : match_token<token::tokens::LITERAL_INTEGER> {};
struct semicolon : match_token<token::tokens::PUNCTUATION_SEMICOLON> {};

// Grammar for variable declaration: let identifier = expr ;
struct var_decl : tao::pegtl::seq<keyword_let, identifier, assign_op, literal_expr, semicolon> {};

// Actions for PEGTL to emit AST nodes
template <typename Rule>
struct action {};

template <>
struct action<var_decl> {
    template <typename Input>
    static void apply(const Input& in, std::vector<std::shared_ptr<ASTNode>>& ast, const token::TokenList& tokens) {
        auto let_token = tokens[0];          // 'let' token
        auto identifier_token = tokens[1];   // Identifier token
        auto assign_token = tokens[2];       // '=' token
        auto expr_token = tokens[3];         // Expression token (literal)

        ast.push_back(std::make_shared<VarDeclNode>(let_token, identifier_token, assign_token, expr_token));
    }
};

// Parsing function
bool parse_var_decl(const token::TokenList& tokens, std::vector<std::shared_ptr<ASTNode>>& ast) {
    TokenInput in(tokens);
    try {
        return tao::pegtl::parse<var_decl, action>(in, ast, tokens);
    } catch (const tao::pegtl::parse_error& e) {
        std::cerr << "Parsing failed: " << e.what() << std::endl;
        return false;
    }
}

}  // namespace my_parser

#endif // __TEST_HH__
