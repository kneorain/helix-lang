#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <string>

using std::string;

// 44 keywords total
//        if
//      else
//    unless
//     macro
//    define
//        fn
//        op
//    inline
//    return
// enclosing
//     async
//     spawn
//     await
//    thread
//       for
//     while
//     break
//  continue
//      case
//     match
//    switch
//   default
//      enum
//      type
//     class
//     union
//    struct
//  abstract
// interface
//        is
//       try
//     panic
//     catch
//   finally
//       let
//      priv
//      auto
//     const
//    global
//      from
//     using
//    import
//    extern
//     yield

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

enum primitives {
    /* ==---------- 1 byte -----------== */
    VOID,                      //      void
    BOOL,                      //      bool
    BYTE,                      //      byte
    /* ==---------- 4 bytes ----------== */
    CHAR,                      //      char
    POINTER,                   //   pointer
    /* ==--------- 128 bytes ---------== */
    FLOAT,                     //     float
    /* ==---------- infinite ---------== */
    INT,                       //       int
    DECIMAL,                   //   decimal
    STRING,                    //    string
    LIST,                      //      list
    TUPLE,                     //     tuple
    SET,                       //       set
    /* ==---- 4 + infinite bytes -----== */
    MAP,                       //       map
    ANY                        //       any
    /* ==--------- end of list -------== */
};

enum operators {
    /* ==--------- arithmetic --------== */
    ADD,                        //       +
    SUB,                        //       -
    MUL,                        //       *
    DIV,                        //       /
    MOD,                        //       %
    MAT,                        //       @
    POWER,                      //       **
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
    ASSIGN,                      //      =
    ADD_ASSIGN,                  //     +=
    SUB_ASSIGN,                  //     -=
    MUL_ASSIGN,                  //     *=
    DIV_ASSIGN,                  //     /=
    MOD_ASSIGN,                  //     %=
    MAT_ASSIGN,                  //     @=
    NOT_ASSIGN,                  //     ~=
    POWER_ASSIGN,                //     **=
    /* ==---------- increment --------== */
    INC,                         //      ++
    DEC,                         //      --
    MULTIPLY,                    //      **
    /* ==---------- logical ----------== */
    LOGICAL_AND,                 //      &&
    LOGICAL_NAND,                //      !&
    LOGICAL_OR,                  //      ||
    LOGICAL_NOR,                 //      !|
    LOGICAL_XOR,                 //      ^^
    LOGICAL_NOT,                 //      !!
    /* ==----------- range -----------== */
    RANGE,                       //     ..
    RANGE_INCLUSIVE,             //     ..=
    /* ==----------- member ----------== */
    DOT,                         //      .
    ARROW,                       //      ->
    /* ==----------- scope -----------== */
    SCOPE,                       //      ::
    /* ==--- dereference / pointer ---== */
    STAR,                        //      *
    /* ==-------- end of list --------== */
};

enum punctuation {
    /* ==--------- brackets ----------== */
    OPEN_PAREN,                  //      (
    CLOSE_PAREN,                 //      )
    OPEN_BRACE,                  //      {
    CLOSE_BRACE,                 //      }
    OPEN_BRACKET,                //      [
    CLOSE_BRACKET,               //      ]
    OPEN_ANGLE,                  //      <
    CLOSE_ANGLE,                 //      >
    /* ==--------- operators ---------== */
    COMMA,                       //      ,
    SEMICOLON,                   //      ;
    COLON,                       //      :
    QUESTION_MARK,               //      ?
    /* ==---------- literals ---------== */
    STRING_LITERAL,              //      ""
    CHAR_LITERAL,                //      ''
    /* ==---------- comments ---------== */
    SINGLE_LINE_COMMENT,         //      //
    MULTI_LINE_COMMENT,          //      /*
    /* ==--------- end of list -------== */
};

enum delimiters {
    /* ==-------- whitespace ---------== */
    SPACE,                       //    ' '
    TAB,                         //    '\t'
    NEWLINE,                     //    '\n'
    /* ==-------- end of list --------== */
};
} // namespace token

#endif // __DEFINE_H__