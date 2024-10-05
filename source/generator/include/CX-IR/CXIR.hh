//===------------------------------------------ C++ ------------------------------------------====//
//                                                                                                //
//  Part of the Helix Project, under the Attribution 4.0 International license (CC BY 4.0).       //
//  You are allowed to use, modify, redistribute, and create derivative works, even for           //
//  commercial purposes, provided that you give appropriate credit, and indicate if changes       //
//   were made. For more information, please visit: https://creativecommons.org/licenses/by/4.0/  //
//                                                                                                //
//  SPDX-License-Identifier: CC-BY-4.0                                                            //
//  Copyright (c) 2024 (CC BY 4.0)                                                                //
//                                                                                                //
//====----------------------------------------------------------------------------------------====//

#include <string>

#include "generator/include/CX-IR/tokens.def"
#include "generator/include/config/Gen_config.def"
#include "parser/ast/include/AST.hh"
#include "token/include/Token.hh"

GENERATE_CXIR_TOKENS_ENUM_AND_MAPPING;

__CXIR_CODEGEN_BEGIN {
    class CX_Token {
      private:
        u64         line;
        u64         column;
        u64         length;
        cxir_tokens type;
        std::string file_name;

      public:
        CX_Token() = default;
        CX_Token(const token::Token &tok, cxir_tokens set_type)
            : line(tok.line_number())
            , column(tok.column_number())
            , length(tok.length())
            , type(set_type)
            , file_name(tok.file_name()) {}
        explicit CX_Token(cxir_tokens type):
              line(0)
            , column(0)
            , length(1)
            , type(type)
            , file_name("_H1HJA9ZLO_17.helix-compiler.cxir") {}
        CX_Token(const CX_Token &)            = default;
        CX_Token(CX_Token &&)                 = delete;
        CX_Token &operator=(const CX_Token &) = default;
        CX_Token &operator=(CX_Token &&)      = delete;
        ~CX_Token()                           = default;

        [[nodiscard]] u64         get_line() const { return line; }
        [[nodiscard]] u64         get_column() const { return column; }
        [[nodiscard]] u64         get_length() const { return length; }
        [[nodiscard]] u64         get_offset() const { return offset; }
        [[nodiscard]] std::string get_value() const { return value; }
        [[nodiscard]] std::string get_file_name() const { return file_name; }
        [[nodiscard]] std::string get_comment() const { return comment; }
    };

    class CXIR : public parser::ast::visitor::Visitor {
      private:
        std::vector<__CXIR_N::Token> tokens;

      public:
        CXIR()                        = default;
        CXIR(const CXIR &)            = default;
        CXIR(CXIR &&)                 = delete;
        CXIR &operator=(const CXIR &) = default;
        CXIR &operator=(CXIR &&)      = delete;
        ~CXIR() override              = default;

        GENERATE_VISIT_EXTENDS;
    };
}