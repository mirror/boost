/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    The definition of a default set of token identifiers and related 
    functions.
    
    http://www.boost.org/

    Copyright (c) 2001-2007 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_WAVE_SOURCE 1
#include <string>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

#include <boost/wave/wave_config.hpp>
#include <boost/wave/token_ids.hpp>

// this must occur after all of the includes and before any code appears
#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_PREFIX
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {

///////////////////////////////////////////////////////////////////////////////
//  return a token name
BOOST_WAVE_STRINGTYPE
get_token_name(token_id tokid)
{
//  Table of token names
//
//      Please note that the sequence of token names must match the sequence of
//      token id's defined in then enum token_id above.
static char const *tok_names[] = {
    /* 256 */   "AND",
    /* 257 */   "ANDAND",
    /* 258 */   "ASSIGN",
    /* 259 */   "ANDASSIGN",
    /* 260 */   "OR",
    /* 261 */   "ORASSIGN",
    /* 262 */   "XOR",
    /* 263 */   "XORASSIGN",
    /* 264 */   "COMMA",
    /* 265 */   "COLON",
    /* 266 */   "DIVIDE",
    /* 267 */   "DIVIDEASSIGN",
    /* 268 */   "DOT",
    /* 269 */   "DOTSTAR",
    /* 270 */   "ELLIPSIS",
    /* 271 */   "EQUAL",
    /* 272 */   "GREATER",
    /* 273 */   "GREATEREQUAL",
    /* 274 */   "LEFTBRACE",
    /* 275 */   "LESS",
    /* 276 */   "LESSEQUAL",
    /* 277 */   "LEFTPAREN",
    /* 278 */   "LEFTBRACKET",
    /* 279 */   "MINUS",
    /* 280 */   "MINUSASSIGN",
    /* 281 */   "MINUSMINUS",
    /* 282 */   "PERCENT",
    /* 283 */   "PERCENTASSIGN",
    /* 284 */   "NOT",
    /* 285 */   "NOTEQUAL",
    /* 286 */   "OROR",
    /* 287 */   "PLUS",
    /* 288 */   "PLUSASSIGN",
    /* 289 */   "PLUSPLUS",
    /* 290 */   "ARROW",
    /* 291 */   "ARROWSTAR",
    /* 292 */   "QUESTION_MARK",
    /* 293 */   "RIGHTBRACE",
    /* 294 */   "RIGHTPAREN",
    /* 295 */   "RIGHTBRACKET",
    /* 296 */   "COLON_COLON",
    /* 297 */   "SEMICOLON",
    /* 298 */   "SHIFTLEFT",
    /* 299 */   "SHIFTLEFTASSIGN",
    /* 300 */   "SHIFTRIGHT",
    /* 301 */   "SHIFTRIGHTASSIGN",
    /* 302 */   "STAR",
    /* 303 */   "COMPL",
    /* 304 */   "STARASSIGN",
    /* 305 */   "ASM",
    /* 306 */   "AUTO",
    /* 307 */   "BOOL",
    /* 308 */   "FALSE",
    /* 309 */   "TRUE",
    /* 310 */   "BREAK",
    /* 311 */   "CASE",
    /* 312 */   "CATCH",
    /* 313 */   "CHAR",
    /* 314 */   "CLASS",
    /* 315 */   "CONST",
    /* 316 */   "CONSTCAST",
    /* 317 */   "CONTINUE",
    /* 318 */   "DEFAULT",
    /* 319 */   "DEFINED",
    /* 320 */   "DELETE",
    /* 321 */   "DO",
    /* 322 */   "DOUBLE",
    /* 323 */   "DYNAMICCAST",
    /* 324 */   "ELSE",
    /* 325 */   "ENUM",
    /* 326 */   "EXPLICIT",
    /* 327 */   "EXPORT",
    /* 328 */   "EXTERN",
    /* 329 */   "FLOAT",
    /* 330 */   "FOR",
    /* 331 */   "FRIEND",
    /* 332 */   "GOTO",
    /* 333 */   "IF",
    /* 334 */   "INLINE",
    /* 335 */   "INT",
    /* 336 */   "LONG",
    /* 337 */   "MUTABLE",
    /* 338 */   "NAMESPACE",
    /* 339 */   "NEW",
    /* 340 */   "OPERATOR",
    /* 341 */   "PRIVATE",
    /* 342 */   "PROTECTED",
    /* 343 */   "PUBLIC",
    /* 344 */   "REGISTER",
    /* 345 */   "REINTERPRETCAST",
    /* 346 */   "RETURN",
    /* 347 */   "SHORT",
    /* 348 */   "SIGNED",
    /* 349 */   "SIZEOF",
    /* 350 */   "STATIC",
    /* 351 */   "STATICCAST",
    /* 352 */   "STRUCT",
    /* 353 */   "SWITCH",
    /* 354 */   "TEMPLATE",
    /* 355 */   "THIS",
    /* 356 */   "THROW",
    /* 357 */   "TRY",
    /* 358 */   "TYPEDEF",
    /* 359 */   "TYPEID",
    /* 360 */   "TYPENAME",
    /* 361 */   "UNION",
    /* 362 */   "UNSIGNED",
    /* 363 */   "USING",
    /* 364 */   "VIRTUAL",
    /* 365 */   "VOID",
    /* 366 */   "VOLATILE",
    /* 367 */   "WCHART",
    /* 368 */   "WHILE",
    /* 369 */   "PP_DEFINE",
    /* 370 */   "PP_IF",
    /* 371 */   "PP_IFDEF",
    /* 372 */   "PP_IFNDEF",
    /* 373 */   "PP_ELSE",
    /* 374 */   "PP_ELIF",
    /* 375 */   "PP_ENDIF",
    /* 376 */   "PP_ERROR",
    /* 377 */   "PP_LINE",
    /* 378 */   "PP_PRAGMA",
    /* 379 */   "PP_UNDEF",
    /* 380 */   "PP_WARNING",
    /* 381 */   "IDENTIFIER",
    /* 382 */   "OCTALINT",
    /* 383 */   "DECIMALINT",
    /* 384 */   "HEXAINT",
    /* 385 */   "INTLIT",
    /* 386 */   "LONGINTLIT",
    /* 387 */   "FLOATLIT",
    /* 388 */   "CCOMMENT",
    /* 389 */   "CPPCOMMENT",
    /* 390 */   "CHARLIT",
    /* 391 */   "STRINGLIT",
    /* 392 */   "CONTLINE",
    /* 393 */   "SPACE",
    /* 394 */   "SPACE2",
    /* 395 */   "NEWLINE",
    /* 396 */   "POUND_POUND",
    /* 397 */   "POUND",
    /* 398 */   "ANY",
    /* 399 */   "PP_INCLUDE",
    /* 400 */   "PP_QHEADER",
    /* 401 */   "PP_HHEADER",
    /* 402 */   "EOF",
    /* 403 */   "EOI",
    /* 404 */   "PP_NUMBER",

              // MS extensions
    /* 405 */   "MSEXT_INT8",
    /* 406 */   "MSEXT_INT16",
    /* 407 */   "MSEXT_INT32",
    /* 408 */   "MSEXT_INT64",
    /* 409 */   "MSEXT_BASED",
    /* 410 */   "MSEXT_DECLSPEC",
    /* 411 */   "MSEXT_CDECL",
    /* 412 */   "MSEXT_FASTCALL",
    /* 413 */   "MSEXT_STDCALL",
    /* 414 */   "MSEXT_TRY",
    /* 415 */   "MSEXT_EXCEPT",
    /* 416 */   "MSEXT_FINALLY",
    /* 417 */   "MSEXT_LEAVE",
    /* 418 */   "MSEXT_INLINE",
    /* 419 */   "MSEXT_ASM",
    /* 420 */   "MSEXT_REGION",
    /* 421 */   "MSEXT_ENDREGION",
    };

    // make sure, I have not forgotten any commas (as I did more than once)
    BOOST_STATIC_ASSERT(
        sizeof(tok_names)/sizeof(tok_names[0]) == T_LAST_TOKEN-T_FIRST_TOKEN
    );
    
    unsigned int id = BASEID_FROM_TOKEN(tokid)-T_FIRST_TOKEN;
    return (id < T_LAST_TOKEN-T_FIRST_TOKEN) ? tok_names[id] : "<UnknownToken>";
}

///////////////////////////////////////////////////////////////////////////////
//  return a token name
char const *
get_token_value(token_id tokid)
{
//  Table of token values
//
//      Please note that the sequence of token names must match the sequence of
//      token id's defined in then enum token_id above.
static char const *tok_values[] = {
    /* 256 */   "&",
    /* 257 */   "&&",
    /* 258 */   "=",
    /* 259 */   "&=",
    /* 260 */   "|",
    /* 261 */   "|=",
    /* 262 */   "^",
    /* 263 */   "^=",
    /* 264 */   ",",
    /* 265 */   ":",
    /* 266 */   "/",
    /* 267 */   "/=",
    /* 268 */   ".",
    /* 269 */   ".*",
    /* 270 */   "...",
    /* 271 */   "==",
    /* 272 */   ">",
    /* 273 */   ">=",
    /* 274 */   "{",
    /* 275 */   "<",
    /* 276 */   "<=",
    /* 277 */   "(",
    /* 278 */   "[",
    /* 279 */   "-",
    /* 280 */   "-=",
    /* 281 */   "--",
    /* 282 */   "%",
    /* 283 */   "%=",
    /* 284 */   "!",
    /* 285 */   "!=",
    /* 286 */   "||",
    /* 287 */   "+",
    /* 288 */   "+=",
    /* 289 */   "++",
    /* 290 */   "->",
    /* 291 */   "->*",
    /* 292 */   "?",
    /* 293 */   "}",
    /* 294 */   ")",
    /* 295 */   "]",
    /* 296 */   "::",
    /* 297 */   ";",
    /* 298 */   "<<",
    /* 299 */   "<<=",
    /* 300 */   ">>",
    /* 301 */   ">>=",
    /* 302 */   "*",
    /* 303 */   "~",
    /* 304 */   "*=",
    /* 305 */   "asm",
    /* 306 */   "auto",
    /* 307 */   "bool",
    /* 308 */   "false",
    /* 309 */   "true",
    /* 310 */   "break",
    /* 311 */   "case",
    /* 312 */   "catch",
    /* 313 */   "char",
    /* 314 */   "class",
    /* 315 */   "const",
    /* 316 */   "const_cast",
    /* 317 */   "continue",
    /* 318 */   "default",
    /* 319 */   "defined",
    /* 320 */   "delete",
    /* 321 */   "do",
    /* 322 */   "double",
    /* 323 */   "dynamic_cast",
    /* 324 */   "else",
    /* 325 */   "enum",
    /* 326 */   "explicit",
    /* 327 */   "export",
    /* 328 */   "extern",
    /* 329 */   "float",
    /* 330 */   "for",
    /* 331 */   "friend",
    /* 332 */   "goto",
    /* 333 */   "if",
    /* 334 */   "inline",
    /* 335 */   "int",
    /* 336 */   "long",
    /* 337 */   "mutable",
    /* 338 */   "namespace",
    /* 339 */   "new",
    /* 340 */   "operator",
    /* 341 */   "private",
    /* 342 */   "protected",
    /* 343 */   "public",
    /* 344 */   "register",
    /* 345 */   "reinterpret_cast",
    /* 346 */   "return",
    /* 347 */   "short",
    /* 348 */   "signed",
    /* 349 */   "sizeof",
    /* 350 */   "static",
    /* 351 */   "static_cast",
    /* 352 */   "struct",
    /* 353 */   "switch",
    /* 354 */   "template",
    /* 355 */   "this",
    /* 356 */   "throw",
    /* 357 */   "try",
    /* 358 */   "typedef",
    /* 359 */   "typeid",
    /* 360 */   "typename",
    /* 361 */   "union",
    /* 362 */   "unsigned",
    /* 363 */   "using",
    /* 364 */   "virtual",
    /* 365 */   "void",
    /* 366 */   "volatile",
    /* 367 */   "wchar_t",
    /* 368 */   "while",
    /* 369 */   "#define",
    /* 370 */   "#if",
    /* 371 */   "#ifdef",
    /* 372 */   "#ifndef",
    /* 373 */   "#else",
    /* 374 */   "#elif",
    /* 375 */   "#endif",
    /* 376 */   "#error",
    /* 377 */   "#line",
    /* 378 */   "#pragma",
    /* 379 */   "#undef",
    /* 380 */   "#warning",
    /* 381 */   "",   // identifier
    /* 382 */   "",   // octalint
    /* 383 */   "",   // decimalint
    /* 384 */   "",   // hexlit
    /* 385 */   "",   // intlit
    /* 386 */   "",   // longintlit
    /* 387 */   "",   // floatlit
    /* 388 */   "",   // ccomment
    /* 389 */   "",   // cppcomment
    /* 390 */   "",   // charlit
    /* 391 */   "",   // stringlit
    /* 392 */   "",   // contline
    /* 393 */   "",   // space
    /* 394 */   "",   // space2
    /* 395 */   "\n",
    /* 396 */   "##",
    /* 397 */   "#",
    /* 398 */   "",   // any
    /* 399 */   "#include",
    /* 400 */   "#include",
    /* 401 */   "#include",
    /* 402 */   "",   // eof
    /* 403 */   "",   // eoi
    /* 404 */   "",   // pp-number

              // MS extensions
    /* 405 */   "__int8",
    /* 406 */   "__int16",
    /* 407 */   "__int32",
    /* 408 */   "__int64",
    /* 409 */   "__based",
    /* 410 */   "__declspec",
    /* 411 */   "__cdecl",
    /* 412 */   "__fastcall",
    /* 413 */   "__stdcall",
    /* 414 */   "__try",
    /* 415 */   "__except",
    /* 416 */   "__finally",
    /* 417 */   "__leave",
    /* 418 */   "__inline",
    /* 419 */   "__asm",
    /* 420 */   "#region",
    /* 421 */   "#endregion",
    };   
     
    // make sure, I have not forgotten any commas (as I did more than once)
    BOOST_STATIC_ASSERT(
        sizeof(tok_values)/sizeof(tok_values[0]) == T_LAST_TOKEN-T_FIRST_TOKEN
    );

    unsigned int id = BASEID_FROM_TOKEN(tokid)-T_FIRST_TOKEN;
    return (id < T_LAST_TOKEN-T_FIRST_TOKEN) ? tok_values[id] : "<UnknownToken>";
}

///////////////////////////////////////////////////////////////////////////////
}   // namespace wave
}   // namespace boost

// the suffix header occurs after all of the code
#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif


