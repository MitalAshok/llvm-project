//===--- CharInfo.cpp - Static Data for Classifying ASCII Characters ------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "clang/Basic/CharInfo.h"
#include "llvm/ADT/STLFunctionalExtras.h"

using namespace clang::charinfo;

#ifdef EXPENSIVE_CHECKS
static bool CheckForAllChars(llvm::function_ref<bool(unsigned char)> f) {
  if (!f(0))
    return false;
  for (unsigned char c = 0; ++c;)
    if (!f(c))
      return false;
  return true;
}

static void CheckIsAsciiIdentifierContinue() {
  assert(CheckForAllChars([](unsigned char c) -> bool {
           bool Expected = InfoTable[c] &
                           (CHAR_UPPER | CHAR_LOWER | CHAR_DIGIT | CHAR_UNDER);
           return clang::isAsciiIdentifierContinue(c) == Expected;
         }) &&
         "Precomputed table is wrong");
}

static int RunAllChecks() {
  CheckIsAsciiIdentifierContinue();
  return 0;
}

static int Runner = RunAllChecks();
#endif
