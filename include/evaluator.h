#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "token.h"
#include "tokenqueue.h"

Token* evaluate_rpn(Queue* rpn);

#endif
