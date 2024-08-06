//===--- clang/Basic/CharInfo.h - Classifying ASCII Characters --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_BASIC_CHARINFO_H
#define LLVM_CLANG_BASIC_CHARINFO_H

#include "clang/Basic/LLVM.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/DataTypes.h"

namespace clang {
namespace charinfo {
enum charinfo_t : uint16_t {
  CHAR_NONE     = 0x0000,
  CHAR_HORZ_WS  = 0x0001,  // '\t', '\f', '\v'.  Note, no '\0'
  CHAR_VERT_WS  = 0x0002,  // '\r', '\n'
  CHAR_SPACE    = 0x0004,  // ' '
  CHAR_DIGIT    = 0x0008,  // 0-9
  CHAR_XLETTER  = 0x0010,  // a-f,A-F
  CHAR_UPPER    = 0x0020,  // A-Z
  CHAR_LOWER    = 0x0040,  // a-z
  CHAR_UNDER    = 0x0080,  // _
  CHAR_PERIOD   = 0x0100,  // .
  CHAR_PUNCT    = 0x0200,  // {}[]#<>%:;?*+-/^&|~!=,"'`$@()

  CHAR_XUPPER = CHAR_XLETTER | CHAR_UPPER,
  CHAR_XLOWER = CHAR_XLETTER | CHAR_LOWER,
};

// Initialize CharInfo table based on ASCII character set
// Reference: FreeBSD 7.2 /usr/share/misc/ascii
inline constexpr charinfo_t InfoTable[256] = {
  // 0 NUL         1 SOH         2 STX         3 ETX
  // 4 EOT         5 ENQ         6 ACK         7 BEL
  CHAR_NONE   , CHAR_NONE   , CHAR_NONE   , CHAR_NONE   ,
  CHAR_NONE   , CHAR_NONE   , CHAR_NONE   , CHAR_NONE   ,
  // 8 BS          9 HT         10 NL         11 VT
  //12 NP         13 CR         14 SO         15 SI
  CHAR_NONE   , CHAR_HORZ_WS, CHAR_VERT_WS, CHAR_HORZ_WS,
  CHAR_HORZ_WS, CHAR_VERT_WS, CHAR_NONE   , CHAR_NONE   ,
  //16 DLE        17 DC1        18 DC2        19 DC3
  //20 DC4        21 NAK        22 SYN        23 ETB
  CHAR_NONE   , CHAR_NONE   , CHAR_NONE   , CHAR_NONE   ,
  CHAR_NONE   , CHAR_NONE   , CHAR_NONE   , CHAR_NONE   ,
  //24 CAN        25 EM         26 SUB        27 ESC
  //28 FS         29 GS         30 RS         31 US
  CHAR_NONE   , CHAR_NONE   , CHAR_NONE   , CHAR_NONE   ,
  CHAR_NONE   , CHAR_NONE   , CHAR_NONE   , CHAR_NONE   ,
  //32 SP         33  !         34  "         35  #
  //36  $         37  %         38  &         39  '
  CHAR_SPACE  , CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  ,
  CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  ,
  //40  (         41  )         42  *         43  +
  //44  ,         45  -         46  .         47  /
  CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  ,
  CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PERIOD , CHAR_PUNCT  ,
  //48  0         49  1         50  2         51  3
  //52  4         53  5         54  6         55  7
  CHAR_DIGIT  , CHAR_DIGIT  , CHAR_DIGIT  , CHAR_DIGIT  ,
  CHAR_DIGIT  , CHAR_DIGIT  , CHAR_DIGIT  , CHAR_DIGIT  ,
  //56  8         57  9         58  :         59  ;
  //60  <         61  =         62  >         63  ?
  CHAR_DIGIT  , CHAR_DIGIT  , CHAR_PUNCT  , CHAR_PUNCT  ,
  CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  ,
  //64  @         65  A         66  B         67  C
  //68  D         69  E         70  F         71  G
  CHAR_PUNCT  , CHAR_XUPPER , CHAR_XUPPER , CHAR_XUPPER ,
  CHAR_XUPPER , CHAR_XUPPER , CHAR_XUPPER , CHAR_UPPER  ,
  //72  H         73  I         74  J         75  K
  //76  L         77  M         78  N         79  O
  CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  ,
  CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  ,
  //80  P         81  Q         82  R         83  S
  //84  T         85  U         86  V         87  W
  CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  ,
  CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  ,
  //88  X         89  Y         90  Z         91  [
  //92  \         93  ]         94  ^         95  _
  CHAR_UPPER  , CHAR_UPPER  , CHAR_UPPER  , CHAR_PUNCT  ,
  CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  , CHAR_UNDER  ,
  //96  `         97  a         98  b         99  c
  //100  d       101  e        102  f        103  g
  CHAR_PUNCT  , CHAR_XLOWER , CHAR_XLOWER , CHAR_XLOWER ,
  CHAR_XLOWER , CHAR_XLOWER , CHAR_XLOWER , CHAR_LOWER  ,
  //104  h       105  i        106  j        107  k
  //108  l       109  m        110  n        111  o
  CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  ,
  CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  ,
  //112  p       113  q        114  r        115  s
  //116  t       117  u        118  v        119  w
  CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  ,
  CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  ,
  //120  x       121  y        122  z        123  {
  //124  |       125  }        126  ~        127 DEL
  CHAR_LOWER  , CHAR_LOWER  , CHAR_LOWER  , CHAR_PUNCT  ,
  CHAR_PUNCT  , CHAR_PUNCT  , CHAR_PUNCT  , CHAR_NONE   ,
};
} // end namespace charinfo

/// Returns true if a byte is an ASCII character.
constexpr bool isASCII(char c) { return static_cast<unsigned char>(c) <= 127; }

constexpr bool isASCII(unsigned char c) { return c <= 127; }

template <class T>
bool isASCII(T) =
    delete; // Please use isASCIICodePoint if this is a code point or ensure
            // your bytes are typed as char or unsigned char

/// Returns true if a codepoint is an ASCII character.
constexpr bool isASCIICodePoint(uint32_t c) { return c <= 127; }
constexpr bool isASCIICodePoint(int64_t c) { return 0 <= c && c <= 127; }

/// Returns true if this is a valid first character of a C identifier,
/// which is [a-zA-Z_].
constexpr bool isAsciiIdentifierStart(unsigned char c,
                                      bool AllowDollar = false) {
  using namespace charinfo;
  if (InfoTable[c] & (CHAR_UPPER|CHAR_LOWER|CHAR_UNDER))
    return true;
  return AllowDollar && c == '$';
}

namespace charinfo {
// Precomputed CHAR_UPPER|CHAR_LOWER|CHAR_DIGIT|CHAR_UNDER
inline constexpr bool IDContinue[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
} // end namespace charinfo

constexpr bool isAsciiIdentifierContinue(unsigned char c) {
  return charinfo::IDContinue[c];
}

/// Returns true if this is a body character of a C identifier,
/// which is [a-zA-Z0-9_].
constexpr bool isAsciiIdentifierContinue(unsigned char c, bool AllowDollar) {
  if (isAsciiIdentifierContinue(c))
    return true;
  return AllowDollar && c == '$';
}

/// Returns true if this character is horizontal ASCII whitespace:
/// ' ', '\\t', '\\f', '\\v'.
///
/// Note that this returns false for '\\0'.
constexpr bool isHorizontalWhitespace(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_HORZ_WS|CHAR_SPACE)) != 0;
}

/// Returns true if this character is vertical ASCII whitespace: '\\n', '\\r'.
///
/// Note that this returns false for '\\0'.
constexpr bool isVerticalWhitespace(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & CHAR_VERT_WS) != 0;
}

/// Return true if this character is horizontal or vertical ASCII whitespace:
/// ' ', '\\t', '\\f', '\\v', '\\n', '\\r'.
///
/// Note that this returns false for '\\0'.
constexpr bool isWhitespace(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_HORZ_WS|CHAR_VERT_WS|CHAR_SPACE)) != 0;
}

/// Return true if this character is an ASCII digit: [0-9]
constexpr bool isDigit(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & CHAR_DIGIT) != 0;
}

/// Return true if this character is a lowercase ASCII letter: [a-z]
constexpr bool isLowercase(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & CHAR_LOWER) != 0;
}

/// Return true if this character is an uppercase ASCII letter: [A-Z]
constexpr bool isUppercase(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & CHAR_UPPER) != 0;
}

/// Return true if this character is an ASCII letter: [a-zA-Z]
constexpr bool isLetter(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_UPPER|CHAR_LOWER)) != 0;
}

/// Return true if this character is an ASCII letter or digit: [a-zA-Z0-9]
constexpr bool isAlphanumeric(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_DIGIT|CHAR_UPPER|CHAR_LOWER)) != 0;
}

/// Return true if this character is an ASCII hex digit: [0-9a-fA-F]
constexpr bool isHexDigit(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_DIGIT|CHAR_XLETTER)) != 0;
}

/// Return true if this character is an ASCII punctuation character.
///
/// Note that '_' is both a punctuation character and an identifier character!
constexpr bool isPunctuation(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_UNDER | CHAR_PERIOD | CHAR_PUNCT)) != 0;
}

/// Return true if this character is an ASCII printable character; that is, a
/// character that should take exactly one column to print in a fixed-width
/// terminal.
constexpr bool isPrintable(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_UPPER | CHAR_LOWER | CHAR_PERIOD | CHAR_PUNCT |
                          CHAR_DIGIT | CHAR_UNDER | CHAR_SPACE)) != 0;
}

/// Return true if this is the body character of a C preprocessing number,
/// which is [a-zA-Z0-9_.].
constexpr bool isPreprocessingNumberBody(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] &
          (CHAR_UPPER|CHAR_LOWER|CHAR_DIGIT|CHAR_UNDER|CHAR_PERIOD)) != 0;
}

/// Return true if this is the body character of a C++ raw string delimiter.
constexpr bool isRawStringDelimBody(unsigned char c) {
  using namespace charinfo;
  return (InfoTable[c] & (CHAR_UPPER | CHAR_LOWER | CHAR_PERIOD | CHAR_DIGIT |
                          CHAR_UNDER | CHAR_PUNCT)) != 0 &&
         c != '(' && c != ')' && c != '\\';
}

enum class EscapeChar {
  Single = 1,
  Double = 2,
  SingleAndDouble = static_cast<int>(Single) | static_cast<int>(Double),
};

/// Return C-style escaped string for special characters, or an empty string if
/// there is no such mapping.
template <EscapeChar Opt, class CharT>
constexpr auto escapeCStyle(CharT Ch) -> StringRef {
  switch (Ch) {
  case '\\':
    return "\\\\";
  case '\'':
    if constexpr ((static_cast<int>(Opt) &
                   static_cast<int>(EscapeChar::Single)) == 0)
      break;
    return "\\'";
  case '"':
    if constexpr ((static_cast<int>(Opt) &
                   static_cast<int>(EscapeChar::Double)) == 0)
      break;
    return "\\\"";
  case '\a':
    return "\\a";
  case '\b':
    return "\\b";
  case '\f':
    return "\\f";
  case '\n':
    return "\\n";
  case '\r':
    return "\\r";
  case '\t':
    return "\\t";
  case '\v':
    return "\\v";
  }
  return {};
}

/// Converts the given ASCII character to its lowercase equivalent.
///
/// If the character is not an uppercase character, it is returned as is.
constexpr char toLowercase(char c) {
  if (isUppercase(c))
    return c + 'a' - 'A';
  return c;
}

/// Converts the given ASCII character to its uppercase equivalent.
///
/// If the character is not a lowercase character, it is returned as is.
constexpr char toUppercase(char c) {
  if (isLowercase(c))
    return c + 'A' - 'a';
  return c;
}

/// Return true if this is a valid ASCII identifier.
///
/// Note that this is a very simple check; it does not accept UCNs as valid
/// identifier characters.
constexpr bool isValidAsciiIdentifier(StringRef S, bool AllowDollar = false) {
  if (S.empty() || !isAsciiIdentifierStart(S[0], AllowDollar))
    return false;

  for (StringRef::iterator I = S.begin(), E = S.end(); I != E; ++I)
    if (!isAsciiIdentifierContinue(*I, AllowDollar))
      return false;

  return true;
}

} // end namespace clang

#endif
