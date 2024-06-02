#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <map>
#include <string>
#include <array>
#include <utility>

#include "../inttypes.hh"

using std::string;

template<typename Enum, int N>
struct Mapping {
    std::array<std::pair<Enum, std::string_view>, N> data;

    constexpr std::optional<Enum> at(std::string_view x) const noexcept {
        for(const auto& [key, value] : data)
            if(value == x) return key;
        return std::nullopt;
    }

    constexpr std::optional<std::string_view> at(Enum x) const noexcept {
        for(const auto& [key, value] : data)
            if(key == x) return value;
        return std::nullopt;
    }
};

namespace token {
enum keywords {
    /* ==-------- control flow -------== */
    IF,                        //        if
    ELSE,                      //      else
    UNLESS,                    //    unless
    /* ==----------- macros ----------== */
    MACRO,                     //     macro
    DEFINE,                    //    define
    /* ==--------- functions ---------== */
    FUNCTION,                  //        fn
    OPERATOR,                  //        op
    INLINE,                    //    inline
    RETURN,                    //    return
    ENCLOSING,                 // enclosing
    /* ==-------- concurrency --------== */
    ASYNC,                     //     async
    SPAWN,                     //     spawn
    AWAIT,                     //     await
    THREAD,                    //    thread
    /* ==----------- loops -----------== */
    FOR,                       //       for
    WHILE,                     //     while
    BREAK,                     //     break
    CONTINUE,                  //  continue
    /* ==---- control  structures ----== */
    CASE,                      //      case
    MATCH,                     //     match
    SWITCH,                    //    switch
    DEFAULT,                   //   default
    /* ==------ data structures ------== */
    ENUM,                      //      enum
    TYPE,                      //      type
    CLASS,                     //     class
    UNION,                     //     union
    STRUCT,                    //    struct
    ABSTRACT,                  //  abstract
    INTERFACE,                 // interface
    /* ==------- type checking -------== */
    IS,                        //        is
    /* ==------ error  handling ------== */
    TRY,                       //       try
    PANIC,                     //     panic
    CATCH,                     //     catch
    FINALLY,                   //   finally
    /* ==--- variable  declaration ---== */
    LET,                       //       let
    PRIVATE,                   //      priv
    AUTO,                      //      auto
    CONST,                     //     const
    GLOBAL,                    //    global
    /* ==------- module system -------== */
    FROM,                      //      from
    USING,                     //     using
    IMPORT,                    //    import
    EXTERN,                    //    extern
    /* ==--------- generators --------== */
    YIELD                      //     yield
    /* ==--------- end of list -------== */
};

constexpr Mapping<keywords, 44> keywords_map{{
    std::pair{IF, "if"},             std::pair{ELSE, "else"},           std::pair{UNLESS, "unless"},     std::pair{MACRO, "macro"},
    std::pair{DEFINE, "define"},     std::pair{FUNCTION, "fn"},         std::pair{OPERATOR, "op"},       std::pair{INLINE, "inline"},
    std::pair{RETURN, "return"},     std::pair{ENCLOSING, "enclosing"}, std::pair{ASYNC, "async"},
    std::pair{SPAWN, "spawn"},       std::pair{AWAIT, "await"},         std::pair{THREAD, "thread"},     std::pair{FOR, "for"},
    std::pair{WHILE, "while"},       std::pair{BREAK, "break"},         std::pair{CONTINUE, "continue"}, std::pair{CASE, "case"},
    std::pair{MATCH, "match"},       std::pair{SWITCH, "switch"},       std::pair{DEFAULT, "default"},   std::pair{ENUM, "enum"},
    std::pair{TYPE, "type"},         std::pair{CLASS, "class"},         std::pair{UNION, "union"},       std::pair{STRUCT, "struct"},
    std::pair{ABSTRACT, "abstract"}, std::pair{INTERFACE, "interface"}, std::pair{IS, "is"},             std::pair{TRY, "try"},
    std::pair{PANIC, "panic"},       std::pair{CATCH, "catch"},         std::pair{FINALLY, "finally"},   std::pair{LET, "let"},
    std::pair{PRIVATE, "priv"},      std::pair{AUTO, "auto"},           std::pair{CONST, "const"},       std::pair{GLOBAL, "global"},
    std::pair{FROM, "from"},         std::pair{USING, "using"},         std::pair{IMPORT, "import"},     std::pair{EXTERN, "extern"},
    std::pair{YIELD, "yield"}
}};

enum primitives {
    /* ==---------- 1 byte -----------== */
    VOID,                    //        void
    BOOL,                    //        bool
    BYTE,                    //        byte
    /* ==---------- 4 bytes ----------== */
    CHAR,                    //        char
    POINTER,                 //         ptr
    /* ==---------- 8 bytes ----------== */
    I8,                      //          i8
    U8,                      //          u8
    /* ==---------- 16 bytes ---------== */
    I16,                     //         i16
    U16,                     //         u16
    /* ==---------- 32 bytes ---------== */
    I32,                     //         i32
    U32,                     //         u32
    F32,                     //         f32
    /* ==---------- 64 bytes ---------== */
    I64,                     //         i64
    U64,                     //         u64
    F64,                     //         f64
    /* ==--------- 128 bytes ---------== */
    FLOAT,                   //       float
    I128,                    //        i128
    U128,                    //        u128
    /* ==---- 4 + infinite bytes -----== */
    INT,                     //         int
    DECIMAL,                 //     decimal
    STRING,                  //      string
    LIST,                    //        list
    TUPLE,                   //       tuple
    SET,                     //         set
    MAP,                     //         map
    ANY,                     //         any
    /* ==--------- end of list -------== */
};

constexpr Mapping<primitives, 26> primitives_map{{
    std::pair{VOID, "void"}, std::pair{BOOL, "bool"}, std::pair{BYTE, "byte"}, std::pair{CHAR, "char"}, std::pair{POINTER, "ptr"},
    std::pair{I8, "i8"}, std::pair{U8, "u8"}, std::pair{I16, "i16"}, std::pair{U16, "u16"}, std::pair{I32, "i32"},
    std::pair{U32, "u32"}, std::pair{F32, "f32"}, std::pair{I64, "i64"}, std::pair{U64, "u64"}, std::pair{F64, "f64"},
    std::pair{FLOAT, "float"}, std::pair{I128, "i128"}, std::pair{U128, "u128"}, std::pair{INT, "int"}, std::pair{DECIMAL, "decimal"},
    std::pair{STRING, "string"}, std::pair{LIST, "list"}, std::pair{TUPLE, "tuple"}, std::pair{SET, "set"}, std::pair{MAP, "map"},
    std::pair{ANY, "any"}
}};

enum operators {
    /* ==--------- arithmetic --------== */
    ADD,                        //       +
    SUB,                        //       -
    MUL,                        //       *
    DIV,                        //       /
    MOD,                        //       %
    MAT,                        //       @
    POW,                        //       **
    ABS,                        //       +-
    /* ==---------- bitwise ----------== */
    BITWISE_AND,                //       &
    BITWISE_NAND,               //       ~&
    BITWISE_OR,                 //       |
    BITWISE_NOR,                //       ~|
    BITWISE_XOR,                //       ^
    BITWISE_NOT,                //       ~
    BITWISE_L_SHIFT,            //       <<
    BITWISE_R_SHIFT,            //       >>
    /* ==--------- relational --------== */
    EQUAL,                      //      ==
    NOT_EQUAL,                  //      !=
    GREATER_THAN,               //      >
    LESS_THAN,                  //      <
    GREATER_THAN_EQUALS,        //      >=
    LESS_THAN_EQUALS,           //      <=
    REF_EQUAL,                  //      ===
    /* ==--------- assignment --------== */
    ASSIGN,                     //      =
    ADD_ASSIGN,                 //      +=
    SUB_ASSIGN,                 //      -=
    MUL_ASSIGN,                 //      *=
    DIV_ASSIGN,                 //      /=
    MOD_ASSIGN,                 //      %=
    MAT_ASSIGN,                 //      @=
    NOT_ASSIGN,                 //      ~=
    POWER_ASSIGN,               //      **=
    /* ==------ logic assignment -----== */
    AND_ASSIGN,                 //      &&=
    NAND_ASSIGN,                //      !&=
    OR_ASSIGN,                  //      ||=
    NOR_ASSIGN,                 //      !|=
    XOR_ASSIGN,                 //      ^^=
    /* ==----- bitwise assignment ----== */
    BITWISE_AND_ASSIGN,         //      &=
    BITWISE_NAND_ASSIGN,        //      ~&=
    BITWISE_OR_ASSIGN,          //      |=
    BITWISE_NOR_ASSIGN,         //      ~|=
    BITWISE_XOR_ASSIGN,         //      ^=
    BITWISE_NOT_ASSIGN,         //      ~=
    BITWISE_L_SHIFT_ASSIGN,     //      <<=
    BITWISE_R_SHIFT_ASSIGN,     //      >>=
    /* ==---------- increment --------== */
    INC,                        //       ++
    DEC,                        //       --
    /* ==---------- logical ----------== */
    LOGICAL_NOT,                //       !
    LOGICAL_AND,                //       &&
    LOGICAL_NAND,               //       !&
    LOGICAL_OR,                 //       ||
    LOGICAL_NOR,                //       !|
    LOGICAL_XOR,                //       ^^
    /* ==----------- range -----------== */
    RANGE,                      //      ..
    RANGE_INCLUSIVE,            //      ..=
    /* ==----------- member ----------== */
    ARROW,                      //       ->
    /* ==----------- scope -----------== */
    SCOPE,                      //       ::
    /* ==-------- end of list --------== */
};

constexpr Mapping<operators, 57> operators_map{{
    std::pair{ADD, "+"},                 std::pair{SUB, "-"},                 std::pair{MUL, "*"},                 std::pair{DIV, "/"},
    std::pair{MOD, "%"},                 std::pair{MAT, "@"},                 std::pair{POW, "**"},                std::pair{ABS, "+-"},
    std::pair{BITWISE_AND, "&"},         std::pair{BITWISE_NAND, "~&"},       std::pair{BITWISE_OR, "|"},          std::pair{BITWISE_NOR, "~|"},
    std::pair{BITWISE_XOR, "^"},         std::pair{BITWISE_NOT, "~"},         std::pair{BITWISE_L_SHIFT, "<<"},    std::pair{BITWISE_R_SHIFT, ">>"},
    std::pair{EQUAL, "=="},              std::pair{NOT_EQUAL, "!="},          std::pair{GREATER_THAN, ">"},        std::pair{LESS_THAN, "<"},
    std::pair{GREATER_THAN_EQUALS, ">="},std::pair{LESS_THAN_EQUALS, "<="},   std::pair{REF_EQUAL, "==="},         std::pair{ASSIGN, "="},
    std::pair{ADD_ASSIGN, "+="},         std::pair{SUB_ASSIGN, "-="},         std::pair{MUL_ASSIGN, "*="},         std::pair{DIV_ASSIGN, "/="},
    std::pair{MOD_ASSIGN, "%="},         std::pair{MAT_ASSIGN, "@="},         std::pair{NOT_ASSIGN, "~="},         std::pair{POWER_ASSIGN, "**="},
    std::pair{AND_ASSIGN, "&&="},        std::pair{NAND_ASSIGN, "!&="},       std::pair{OR_ASSIGN, "||="},         std::pair{NOR_ASSIGN, "!|="},
    std::pair{XOR_ASSIGN, "^^="},        std::pair{BITWISE_AND_ASSIGN, "&="}, std::pair{BITWISE_NAND_ASSIGN, "~&="},std::pair{BITWISE_OR_ASSIGN, "|="},
    std::pair{BITWISE_NOR_ASSIGN, "~|"}, std::pair{BITWISE_XOR_ASSIGN, "^="}, std::pair{BITWISE_NOT_ASSIGN, "~="}, std::pair{BITWISE_L_SHIFT_ASSIGN, "<<="},
    std::pair{BITWISE_R_SHIFT_ASSIGN, ">>="},std::pair{INC, "++"},            std::pair{DEC, "--"},                std::pair{LOGICAL_NOT, "!"},
    std::pair{LOGICAL_AND, "&&"},        std::pair{LOGICAL_NAND, "!&"},       std::pair{LOGICAL_OR, "||"},         std::pair{LOGICAL_NOR, "!|"},
    std::pair{LOGICAL_XOR, "^^"},        std::pair{RANGE, ".."},              std::pair{RANGE_INCLUSIVE, "..="},   std::pair{ARROW, "->"},
    std::pair{SCOPE, "::"}
}};

enum literals {
    /* ==---------- boolean ----------== */
    TRUE,                       //     true
    FALSE,                      //    false
    /* ==---------- integer ----------== */
    INTEGER,                    //        0
    COMPLIER_DIRECTIVE,         //      #[]
    /* ==---------- floating ---------== */
    FLOATING,                   //      0.0
    /* ==----- character / string ----== */
    STRING_LITERAL,             //       ""
    CHAR_LITERAL,               //       ''
    /* ==-------- end of list --------== */
};

constexpr Mapping<literals, 7> literals_map{{
    std::pair{TRUE, "true"}, std::pair{FALSE, "false"}, std::pair{INTEGER, "0"}, std::pair{FLOATING, "0.0"},
    std::pair{STRING_LITERAL, "\"\""}, std::pair{CHAR_LITERAL, "''"}, std::pair{COMPLIER_DIRECTIVE, "#[]"}
}};

enum punctuation {
    /* ==--------- brackets ----------== */
    OPEN_PAREN,                 //       (
    CLOSE_PAREN,                //       )
    OPEN_BRACE,                 //       {
    CLOSE_BRACE,                //       }
    OPEN_BRACKET,               //       [
    CLOSE_BRACKET,              //       ]
    OPEN_ANGLE,                 //       <
    CLOSE_ANGLE,                //       >
    /* ==--------- operators ---------== */
    COMMA,                      //       ,
    SEMICOLON,                  //       ;
    COLON,                      //       :
    QUESTION_MARK,              //       ?
    DOT,                        //       .
    HASH,                       //       #
    /* ==---------- comments ---------== */
    SINGLE_LINE_COMMENT,        //       //
    MULTI_LINE_COMMENT,         //       /*
    /* ==--------- end of list -------== */
};

constexpr Mapping<punctuation, 16> punctuation_map{{
    std::pair{OPEN_PAREN, "("},         std::pair{CLOSE_PAREN, ")"},       std::pair{OPEN_BRACE, "{"},         std::pair{CLOSE_BRACE, "}"},
    std::pair{OPEN_BRACKET, "["},       std::pair{CLOSE_BRACKET, "]"},     std::pair{OPEN_ANGLE, "<"},        std::pair{CLOSE_ANGLE, ">"},
    std::pair{COMMA, ","},               std::pair{SEMICOLON, ";"},         std::pair{COLON, ":"},             std::pair{QUESTION_MARK, "?"},
    std::pair{DOT, "."},                 std::pair{SINGLE_LINE_COMMENT, "//"},std::pair{MULTI_LINE_COMMENT, "/*"}, std::pair{HASH, "#"}
}};


enum delimiters {
    /* ==-------- whitespace ---------== */
    TAB,                         //     \t
    NEWLINE,                     //     \n
    SPACE,                       //     ' '
    /* ==-------- end of list --------== */
};

constexpr Mapping<delimiters, 3> delimiters_map{{
    std::pair{TAB, "\t"}, std::pair{NEWLINE, "\n"}, std::pair{SPACE, " "}
}};

enum identifiers {
    /* ==--------- identifiers -------== */
    IDENTIFIER,                  //      id
    /* ==--------- end of list -------== */
};

enum discriminant {
    KEYWORDS, PRIMITIVES, OPERATORS, LITERALS, PUNCTUATION, DELIMITERS, IDENTIFIERS
};
} // namespace token

#endif // __DEFINE_H__