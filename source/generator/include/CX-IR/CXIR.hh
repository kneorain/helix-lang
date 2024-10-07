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

#include <clang/Format/Format.h>
#include <llvm/ADT/StringRef.h>

#include <cstdio>

using namespace clang;

#include <memory>
#include <string>
#include <vector>

#include "generator/include/CX-IR/tokens.def"
#include "generator/include/config/Gen_config.def"
#include "parser/ast/include/AST.hh"
#include "token/include/Token.hh"

inline consteval std::string get_neo_clang_format_config() {
    return R"(
Language:        Cpp
BasedOnStyle:  Google
AccessModifierOffset: -2
NamespaceIndentation: Inner
AlignAfterOpenBracket: Align
AlignConsecutiveAssignments: true
AlignConsecutiveDeclarations: true
AlignEscapedNewlines: Left
AlignOperands:   true
AlignTrailingComments: true
AllowAllParametersOfDeclarationOnNextLine: true
AllowShortBlocksOnASingleLine: true
AllowShortCaseLabelsOnASingleLine: false
AllowShortIfStatementsOnASingleLine: false
AllowShortLoopsOnASingleLine: false
AlwaysBreakAfterDefinitionReturnType: None
AlwaysBreakAfterReturnType: None
AlwaysBreakBeforeMultilineStrings: false
AlwaysBreakTemplateDeclarations: true
BinPackArguments: false
BinPackParameters: false
BraceWrapping:
    AfterClass:      false
    AfterControlStatement: false
    AfterEnum:       false
    AfterFunction:   false
    AfterNamespace:  false
    AfterObjCDeclaration: false
    AfterStruct:     false
    AfterUnion:      false
    AfterExternBlock: false
    BeforeCatch:     false
    BeforeElse:      false
    IndentBraces:    false
    SplitEmptyFunction: true
    SplitEmptyRecord: true
    SplitEmptyNamespace: true
AllowShortFunctionsOnASingleLine: All
BreakBeforeBinaryOperators: None
BreakBeforeBraces: Custom
BreakBeforeInheritanceComma: true
BreakInheritanceList: BeforeColon
BreakBeforeTernaryOperators: true
BreakConstructorInitializersBeforeComma: true
ColumnLimit:     100
CommentPragmas:  '^ IWYU pragma:'
CompactNamespaces: false
ConstructorInitializerAllOnOneLineOrOnePerLine: false
ConstructorInitializerIndentWidth: 4
ContinuationIndentWidth: 4
Cpp11BracedListStyle: true
DerivePointerAlignment: false
DisableFormat:   false
ExperimentalAutoDetectBinPacking: false
FixNamespaceComments: true
ForEachMacros:
  - foreach
  - Q_FOREACH
  - BOOST_FOREACH
IncludeCategories:
  - Regex:           '^<.*\.h>'
    Priority:        1
  - Regex:           '^<.*'
    Priority:        2
  - Regex:           '.*'
    Priority:        3
IndentCaseLabels: true
IndentWidth:     4
IndentWrappedFunctionNames: false
KeepEmptyLinesAtTheStartOfBlocks: true
MacroBlockBegin: ''
MacroBlockEnd:   ''
MaxEmptyLinesToKeep: 1
PenaltyBreakAssignment: 2
PenaltyBreakBeforeFirstCallParameter: 19
PenaltyBreakComment: 300
PenaltyBreakFirstLessLess: 120
PenaltyBreakString: 1000
PenaltyExcessCharacter: 1000000
PenaltyReturnTypeOnItsOwnLine: 60
PointerAlignment: Right
ReflowComments:  true
SortIncludes:    true
SpaceAfterCStyleCast: false
SpaceAfterTemplateKeyword: true
SpaceBeforeAssignmentOperators: true
SpaceBeforeParens: ControlStatements
SpaceInEmptyParentheses: false
SpacesBeforeTrailingComments: 2
SpacesInAngles:  false
SpacesInContainerLiterals: true
SpacesInCStyleCastParentheses: false
SpacesInParentheses: false
SpacesInSquareBrackets: false
Standard:        Latest
TabWidth:        4
UseTab:          Never
)";
}

GENERATE_CXIR_TOKENS_ENUM_AND_MAPPING;

__CXIR_CODEGEN_BEGIN {
    class CX_Token {
      private:
        u64         line{};
        u64         column{};
        u64         length{};
        cxir_tokens type{};
        std::string file_name;
        std::string value;

      public:
        CX_Token() = default;
        CX_Token(const token::Token &tok, cxir_tokens set_type)
            : line(tok.line_number())
            , column(tok.column_number())
            , length(tok.length())
            , type(set_type)
            , file_name(tok.file_name())
            , value(std::string(tok.value())) {}

        explicit CX_Token(cxir_tokens type)
            : length(1)
            , type(type)
            , file_name("_H1HJA9ZLO_17.helix-compiler.cxir")
            , value(cxir_tokens_map.at(type).has_value()
                        ? std::string(cxir_tokens_map.at(type).value())
                        : " /* Unknown Token */ ") {}

        CX_Token(cxir_tokens type, std::string value)
            : length(value.length())
            , type(type)
            , file_name("_H1HJA9ZLO_17.helix-compiler.cxir")
            , value(std::move(value)) {}

        CX_Token(const CX_Token &)            = default;
        CX_Token(CX_Token &&)                 = delete;
        CX_Token &operator=(const CX_Token &) = default;
        CX_Token &operator=(CX_Token &&)      = delete;
        ~CX_Token()                           = default;

        [[nodiscard]] u64         get_line() const { return line; }
        [[nodiscard]] u64         get_column() const { return column; }
        [[nodiscard]] u64         get_length() const { return length; }
        [[nodiscard]] cxir_tokens get_type() const { return type; }
        [[nodiscard]] std::string get_file_name() const { return file_name; }
        [[nodiscard]] std::string get_value() const { return value; }
        [[nodiscard]] std::string to_CXIR() const {
            if (line == 0) {
                return value + " ";
            }

            return "\n#line " + std::to_string(line) + " \"" + file_name + "\"\n" + value + "\n";
        }

        [[nodiscard]] std::string to_clean_CXIR() const { return value + " "; }
    };

    class CXIR : public __AST_VISITOR::Visitor {
      private:
        std::vector<std::unique_ptr<CX_Token>> tokens;

      public:
        CXIR()                        = default;
        CXIR(const CXIR &)            = default;
        CXIR(CXIR &&)                 = delete;
        CXIR &operator=(const CXIR &) = default;
        CXIR &operator=(CXIR &&)      = delete;
        ~CXIR() override              = default;

        [[nodiscard]] std::string to_CXIR() const {
            std::string cxir;

            // Build the CXIR string from tokens

            for (const auto &token : tokens) {
                cxir += token->to_CXIR();
            }

            // If cxir is empty, log and return early
            if (cxir.empty()) {
                printf("CXIR is empty after processing tokens.\n");
                return cxir;
            }

            return cxir;
        }

        [[nodiscard]] std::string to_readable_CXIR() const {
            std::string cxir;

            // Build the CXIR string from tokens

            for (const auto &token : tokens) {
                cxir += token->to_clean_CXIR();
            }

            // If cxir is empty, log and return early
            if (cxir.empty()) {
                printf("CXIR is empty after processing tokens.\n");
                return cxir;
            }

            // Get the configuration as a string
            std::string config = get_neo_clang_format_config();
            // printf("Format config: %s\n", config.c_str());  // Log the config

            // Use a basic clang format style to simplify testing
            clang::format::FormatStyle style =
                clang::format::getLLVMStyle(clang::format::FormatStyle::LanguageKind::LK_Cpp);

            // Parse the configuration string into the FormatStyle object
            auto error = clang::format::parseConfiguration(config, &style);
            if (error) {
                printf("Failed to parse the configuration: %s\n", error.message().c_str());
                throw std::runtime_error("Failed to parse configuration");
            }

            // Format the cxir code using the style
            llvm::StringRef              codeRef(cxir.c_str());
            clang::tooling::Range        range(0, cxir.size());
            clang::tooling::Replacements replacements =
                clang::format::reformat(style, codeRef, {range});

            // Check if replacements were generated
            printf("Number of replacements: %lu\n", replacements.size());
            for (const auto &replacement : replacements) {
                printf("Replacement: %s\n", replacement.toString().c_str());
            }

            // Apply the replacements to get the formatted code
            llvm::Expected<std::string> formattedCode =
                clang::tooling::applyAllReplacements(cxir, replacements);
            if (!formattedCode) {
                printf("Error formatting code: %s\n",
                       llvm::toString(formattedCode.takeError()).c_str());
                throw std::runtime_error("Error formatting code");
            }

            printf("Formatted CXIR: %s\n", formattedCode->c_str());  // Log the result
            return *formattedCode;
        }
        GENERATE_VISIT_EXTENDS;
    };

    // inline CXIR get_node_json(const __AST_VISITOR::NodeT<> &node) {
    //     auto visitor = CXIR();

    //     if (node == nullptr) {

    //     }

    //     node->accept(visitor);
    //     return visitor.json;
    // }
}