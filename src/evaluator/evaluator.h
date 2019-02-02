#include "string.h"
#include "journal.h"

typedef struct _Evaluator {
	int* map;
	char* list;
	int* depth;
	double(*callback)(double, double, char);
	int length, importance;
} Evaluator;

Evaluator NewEvaluator(double(*callback)(double, double, char));
void FreeEvaluator(Evaluator* ev);
void EvaluatorPush(Evaluator* ev, char c, int depth);
int CharIsOperator(char c, Evaluator ev);
int EvaluatorVariableToIndex(String s);
Substring EvaluatorGetMostImportant(String s, Evaluator ev);
int EvaluatorGetType(Substring ss, Evaluator ev);
int EvaluatorEvalSubtring(Substring ss, Evaluator ev, Journal* j);
void EvaluatorUpdateString(String* s, Substring ss, int index);
void EvaluatorError(int e);
int EvaluatorValidate(String s);
double eval(char* exp, Evaluator ev);

#include "evaluator.c"
