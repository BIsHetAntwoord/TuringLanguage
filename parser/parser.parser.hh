/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_PARSER_YY_D_BESTANDEN_DATA_CODES_PROGRAMEREN_C_PROJECTEN_TURINGLANGUAGE_PARSER_PARSER_PARSER_HH_INCLUDED
# define YY_PARSER_YY_D_BESTANDEN_DATA_CODES_PROGRAMEREN_C_PROJECTEN_TURINGLANGUAGE_PARSER_PARSER_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef PARSER_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PARSER_YYDEBUG 1
#  else
#   define PARSER_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PARSER_YYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PARSER_YYDEBUG */
#if PARSER_YYDEBUG
extern int parser_yydebug;
#endif

/* Token type.  */
#ifndef PARSER_YYTOKENTYPE
# define PARSER_YYTOKENTYPE
  enum parser_yytokentype
  {
    KEYW_FALSE = 258,
    KEYW_TRUE = 259,
    KEYW_U32 = 260,
    KEYW_VOID = 261,
    SEMICOLON = 262,
    ASSIGN = 263,
    PLUS = 264,
    MIN = 265,
    MUL = 266,
    DIV = 267,
    MOD = 268,
    BITAND = 269,
    BITOR = 270,
    BITXOR = 271,
    BITNOT = 272,
    CONCAT = 273,
    OPEN_PAR = 274,
    CLOSE_PAR = 275,
    OPEN_CB = 276,
    CLOSE_CB = 277,
    INTEGER = 278,
    ID = 279,
    STRING = 280,
    ERROR_TOKEN = 281,
    UPLUS = 282,
    UMIN = 283,
    TRY = 284
  };
#endif

/* Value type.  */



int parser_yyparse (parse_info* x);

#endif /* !YY_PARSER_YY_D_BESTANDEN_DATA_CODES_PROGRAMEREN_C_PROJECTEN_TURINGLANGUAGE_PARSER_PARSER_PARSER_HH_INCLUDED  */
