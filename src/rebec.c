#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMUM_LINE_WIDTH 3
#define COMMAND_WIDTH 3
#define DT_LIT 0
#define DT_STR 1
#define DT_FCT 2
#define PC 0
#define ACC 1
#define ZERO 2
#define POS 3
#define NEG 4
#define IN 5
#define OUT 6
#define ROM 7
#define OFFSET 8
#define CHIP_NO 313

int ERROR_CODE = 0;
#include "evaluator/evaluator.h"
#include "ll/ll.h"

/*#define DT_DEC 0
#define DT_HEX 1
#define DT_BIN 2
#define DT_CHR 3
#define DT_STR 4
#define DT_SYM 5
#define DT_FCT 6*/

//Lines of code
typedef struct _rebec_cmd_t {
	char* name;
} rebec_cmd_t;
typedef struct _rebec_arg_t {
	char* data;
	int type;
} rebec_arg_t;
typedef struct _rebec_line_t {
	rebec_cmd_t command;
	rebec_arg_t *args;
	int argc, line_no;
} rebec_line_t;

double evaluator_callback(double a, double b, char op) {
	switch (op) {
		case '+':
			return a + b;
			break;
		case '-':
			return a - b;
			break;
		case '*':
			return a * b;
			break;
		case '/':
			return a / b;
			break;
	}
	return -1;
}

//Cleanup for a rebec_line_t
void FreeRebecLine(rebec_line_t *rl) {
	for (int i = 0; i < rl->argc; i++) {
		free(rl->args[i].data);
	}
	free(rl->args);
	free(rl->command.name);

}

//Checks to see if the string is alphanumeric 
int IsAlphaNumeric(char* str) {
	int len = strlen(str);
	int i;
	for (i = 0; i < len; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') continue;
		if (str[i] >= 'A' && str[i] <= 'Z') continue;
		if (str[i] >= '0' && str[i] <= '9') continue;
		if (str[i] == '_') continue;
		return 0;
	}
	return 1;
}

//Checks to see if a character is numeric
int IsNumeric(char ch) {
	if (ch >= '0' && ch <= '9') return 1;
	return 0;
}

void RebecAppendOutput(char **poutput, char *str) {
	char *output = *poutput;

	//Append the string onto the output
	int len = snprintf(NULL, 0, "%s%s", output, str);
	char new_output[len + 1];
	sprintf(new_output, "%s%s", output, str);
	new_output[len] = 0;
	output = realloc(output, sizeof(char) * (len + 1));
	memcpy(output, new_output, sizeof(char) * (len + 1));

	*poutput = output;
}

#include "rebec_definitions.c"

void RebecCompile(rebec_line_t *lines, int line_count) {
	char *code = malloc(1); //the main code section
	char *data = malloc(1); //the data segment
	code[0] = 0;
	data[0] = 0;

	int verbose = 1;

	//Setup segment headers
	if (verbose) {
		RebecAppendOutput(&code,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&code,";               Start of Code Segment                 ;\n");
		RebecAppendOutput(&code,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&data,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&data,";               Start of Data Segment                 ;\n");
		RebecAppendOutput(&data,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}

	//Temporary registers for the compiler
	RebecAppendOutput(&data, "___REBEC_TEMP_1___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_TEMP_2___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_TEMP_3___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_TEMP_4___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_TEMP_5___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_TEMP_6___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_TEMP_7___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_PREVIOUS_OUTPUT___:\n\trssb 0\n");
	RebecAppendOutput(&data, "___REBEC_STACK_POINTER___:\n\trssb ___REBEC_STACK___\n");
	RebecAppendOutput(&data, "___REBEC_STACK___:\n");
	for (int i = 0; i < 10; i++) RebecAppendOutput(&data, "\trssb 0\n");

	//Handle the commands
	for (int i = 0; i < line_count; i++) {
		char *cmd = lines[i].command.name;
		if (strcmp(cmd, "fct") == 0 || strcmp(cmd, "lbl") == 0) {
			RebecFCT(lines[i], &code, verbose); 
		} else if (strcmp(cmd, "def") == 0) {
			RebecDEF(lines[i], &data, verbose); 
		} else {

			//Throw an error if user isn't using FCT or DEF but is attempting to use those data types
			for (int j = 0; j < lines[i].argc; j++) {
				if (lines[i].args[j].type == DT_FCT) {
					printf("Error on line %i: Function types can only be used with `FCT` or `LBL` statements.\n", lines[i].line_no);
					exit(1);
				}
				if (lines[i].args[j].type == DT_STR) {
					printf("Error on line %i: String types can only be used with `DEF` statements.\n", lines[i].line_no);
					exit(1);
				}
			}

			//Handle rest of commands
			if (strcmp(cmd, "lwo") == 0) {
				RebecLWO(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "neg") == 0) {
				RebecNEG(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "add") == 0) {
				RebecADD(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "ssb") == 0) {
				RebecSSB(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "sub") == 0) {
				RebecSUB(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "inc") == 0) {
				RebecINC(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "dec") == 0) {
				RebecDEC(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "clr") == 0) {
				RebecCLR(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "end") == 0) {
				RebecEND(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "jup") == 0) {
				RebecJUP(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "jdp") == 0) {
				RebecJDP(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "jnn") == 0) {
				RebecJNN(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "get") == 0) {
				RebecGET(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "set") == 0) {
				RebecSET(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "lod") == 0) {
				RebecLOD(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "ldi") == 0) {
				RebecLDI(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "lbr") == 0) {
				RebecLBR(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "sto") == 0) {
				RebecSTO(lines[i], &code, verbose); 
			} else if (strcmp(cmd, "sbr") == 0) {
				RebecSBR(lines[i], &code, verbose);
			} else if (strcmp(cmd, "jmp") == 0) {
				RebecJMP(lines[i], &code, verbose);
			} else if (strcmp(cmd, "cal") == 0) {
				RebecCAL(lines[i], &code, verbose);
			} else if (strcmp(cmd, "jpe") == 0) {
				RebecJPE(lines[i], &code, verbose);
			} else if (strcmp(cmd, "jne") == 0) {
				RebecJNE(lines[i], &code, verbose);
			} else if (strcmp(cmd, "jge") == 0) {
				RebecJGE(lines[i], &code, verbose);
			} else if (strcmp(cmd, "jle") == 0) {
				RebecJLE(lines[i], &code, verbose);
			} else if (strcmp(cmd, "jpl") == 0) {
				RebecJPL(lines[i], &code, verbose);
			} else if (strcmp(cmd, "ret") == 0) {
				RebecRET(lines[i], &code, verbose);
			//} else if (strcmp(cmd, "n1n") == 0) {
			//	RebecN1N(lines[i], &code, verbose);
			} else {
				printf("Error on line %i: Unknown command `%s`.\n", lines[i].line_no, lines[i].command.name); 
				exit(1);
			}
		}
	}

	//Setup footers 
	if (verbose) {
		RebecAppendOutput(&code,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&code,";                End of Code Segment                  ;\n");
		RebecAppendOutput(&code,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&data,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&data,";                End of Data Segment                  ;\n");
		RebecAppendOutput(&data,";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	printf("%s\n%s", code, data);

	free(code);
	free(data);
}

//Checks to see if the line contains any sort of symbol
//  definitions and returns that symbol as a pointer to
//  a string contained within the line we pass into it
//  (this means if we later free *rl then we do not need
//  to free the return char*
char* RebecLineGetSymbol(rebec_line_t *rl) {
		//Checks to see if the statement is a def or a fct statement
		if ((rl->command.name[0] == 'd' && rl->command.name[1] == 'e' && rl->command.name[2] == 'f') ||
			(rl->command.name[0] == 'f' && rl->command.name[1] == 'c' && rl->command.name[2] == 't') ||
			(rl->command.name[0] == 'l' && rl->command.name[1] == 'b' && rl->command.name[2] == 'l')) {
			//These statements needs at least 1 argument
			if (rl->argc == 0) {
				printf("Error on line %i: Too few arguments.\n", rl->line_no);
				exit(1);
			}
			if (!IsAlphaNumeric(rl->args[0].data) || IsNumeric(rl->args[0].data[0])) {
				printf("Error on line %i: Invalid symbol name.\n", rl->line_no);
				exit(1);
			}
			return rl->args[0].data;
		}
		return NULL;
}

//We use a mock symbol table to check to see if it's
//  possible to evaluate all of our statements with it.
//  If it is possible, the syntax is correct, if it is
//  impossible, the syntax is incorrect. The actual
//  resulting values do not matter, just whether or
//  not it can be evaluated with a random value.
void RebecLineValidate(rebec_line_t *rl, LabelList ll) {
	for (int i = 0; i < rl->argc; i++) {
		if (rl->args[i].type == DT_STR) continue;

		int len = strlen(rl->args[i].data) + 1;
		char* line_to_evaluate = malloc(sizeof(char) * len); 
		memcpy(line_to_evaluate, rl->args[i].data, len);
		ReplaceWithLabel(&line_to_evaluate, ll);
		FixNegatives(&line_to_evaluate);
		FixCharCode(&line_to_evaluate);

		Evaluator ev = NewEvaluator(&evaluator_callback);
		EvaluatorPush(&ev, '-', 2);
		EvaluatorPush(&ev, '+', 2);
		EvaluatorPush(&ev, '/', 2);
		EvaluatorPush(&ev, '*', 2);
		ev.map[0] = 1;
		ev.map[1] = 1;
		ev.map[2] = 2;	
		ev.map[3] = 2;

		int results = (int)eval(line_to_evaluate, ev);
		free(line_to_evaluate);
		FreeEvaluator(&ev);

		if (ERROR_CODE != 0) {
			printf("Error on line %i: Invalid expression.\n", rl->line_no); 
			exit(1);
		}
		if (strlen(rl->args[i].data) <= 0) {
			printf("Error on line %i: Argument left empty (trailing comma).\n", rl->line_no);
			exit(1); 
		}
	}
}
//Checks of a character is white space.
int isWhiteSpace(char c) {
	if (c == ' ' || c == '\t' || c == '\r') return 1;
	return 0;
}
//Converts "line" to a cleaned up version
//"Line" will not be freed in this function and
//the returned line must be freed.
//It expects a non-null terminated string with
//its length but returns a null-terminated string.
char* RebecCleanUpLine(char *line, int length) {

	//the processed line data
	char* pline = malloc(sizeof(char) * 1);
	pline[0] = 0;
	int pline_length = 0;
	//Don't process empty lines
	if (length == 0) {
		return pline;
	}
	//Trim off white space
	int left = 0;
	while (isWhiteSpace(line[left])) {
		left++;
		if (left == length - 1) break;
	} 
	int right = length - 1;
	while (isWhiteSpace(line[right])) {
		right--;
		if (right == 0) break;
	}
	pline_length = right - left + 1;
	//Don't process lines that are simply white space
	if (pline_length <= 0) {
		return pline;
	}
	pline = realloc(pline, sizeof(char) * (pline_length + 1));
    for (int i = 0; i < pline_length; i++) {
		pline[i] = line[i + left];
	}
	pline[pline_length] = 0;
	//Don't process comments
	if (pline[0] == ';') {
		pline = realloc(pline, sizeof(char) * 1);
		pline[0] = 0;
		return pline;
	}
	//Return our processed line
	return pline;
}

//Parses a processed char* line into a rebec_line_t
//The returned line must be freed using FreeRebecLine()
rebec_line_t RebecParseLine(const char *line, int line_no) {
	int len = strlen(line);
	//Check for quotation balance
	int balanced = 1;
	for (int i = 0; i < len; i++) {
		if (line[i] == '\"') {
			balanced = !balanced;
		}
	}
	if (!balanced) {
		printf("Error on line %i: Unmatched quotation marks.\n", line_no);
		exit(1); 
	}

	//Determine the size of the command
	int end = 0;
	while (line[end] != ' ') {
		end++;
		if (end == len) break;
	}
	//Load the command into cmd
	char *cmd = malloc(sizeof(char) * (end + 1)); 
	cmd[end] = 0;
	for (int i = 0; i < end; i++) {
		cmd[i] = line[i];
	}
	//If it's not the right size, it's definitely not valid!
	if (end != COMMAND_WIDTH) {
		printf("Error on line %i: Invalid command `%s`.\n", line_no, cmd);
		exit(1);
	}

	//Build our command
	rebec_cmd_t rcmd;
	rcmd.name = cmd;
	
	//Check how how many arguments there are...
	int argc = 0;
	if (len > 3) {
		int inside_quotation = 0;		
		for (int i = 0; i < len; i++) {
			if (line[i] == '\"') {
				inside_quotation = !inside_quotation;
			} else if (line[i] == ',' && !inside_quotation) {
				argc++;
			}
		}
		argc++;
	}
	
	//Declare our argument array
	rebec_arg_t *rargs = malloc(sizeof(rebec_arg_t) * argc);

	int pos = end;
	for (int i = 0; i < argc; i++) {
		//We will build this string into our command
		char* scmd = malloc(0);
		int scmd_size = 0;
		//skip over initial whitespace
		while (isWhiteSpace(line[pos])) {
			pos++;
		}
		int inside_quotations = 0;
		if (line[pos] == '\"') { 
			inside_quotations = !inside_quotations;
		}
		//loop until whitespace or comma is found
		while ((!isWhiteSpace(line[pos]) && line[pos] != ',') || inside_quotations) {
			//Append the current character onto scmd			
			scmd_size++;
			scmd = realloc(scmd, sizeof(char) * scmd_size);
			scmd[scmd_size - 1] = line[pos];
			pos++;
			if (pos == len) break;
			if (line[pos] == '\"') { 
				inside_quotations = !inside_quotations;
			}
		}
		//If white space is found, move until comma
		if (pos != len) {
			while (line[pos] != ',') {
				pos++;
			}
		}
		pos++;
		//Append a zero onto scmd 
		scmd_size++;
		scmd = realloc(scmd, sizeof(char) * scmd_size);
		scmd[scmd_size - 1] = 0;
		//Check the data type of the argument and remove
		//  that from the string
		int type = -1;
		if (scmd_size > 1) {
			if (scmd[0] == '\"') {
				type = DT_STR;
				//Remove quotation marks
				for (int j = 1; j < scmd_size; j++) {
					scmd[j-1] = scmd[j];
				}
				//Resize since we just removed 2 bytes
				scmd_size -= 2;
				scmd = realloc(scmd, sizeof(char) * scmd_size);
				scmd[scmd_size - 1] = 0;
			} else if (scmd[scmd_size - 2] == ':') {
				type = DT_FCT;
				//Remove the ending colon
				scmd_size -= 1;
				scmd = realloc(scmd, sizeof(char) * scmd_size);
				scmd[scmd_size - 1] = 0;
			} else {
				type = DT_LIT;
			}
		} else {
			printf("Error on line %i: Empty argument.\n", line_no);
			exit(1); 
		}
		//Build our argument array
		rargs[i].data = scmd;
		rargs[i].type = type;
	}
	
	//Build our final line
	rebec_line_t rl;
	rl.command = rcmd;
	rl.args = rargs;
	rl.argc = argc;
	rl.line_no = line_no;

	return rl;	
}


rebec_line_t* RebecLoadLines(const char *fname) {
	
	//Read raw ASCII text
	FILE *file = fopen(fname, "rb");
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file) + 1;
	char buffer[file_size];
	fseek(file, 0, SEEK_SET);
	fread(buffer, sizeof(char), file_size - 1, file);
	fclose(file);
	buffer[file_size - 1] = '\n';
	
	//Divide text into individual lines
	int line_no = 1;
	int last_pos = 0;
	int line_count = 0;
	rebec_line_t *rlines = malloc(0);
	for (int i = 0; i < file_size; i++) {
		if (buffer[i] == '\n') {
			char line[i - last_pos];
			for (int j = last_pos; j < i; j++) {
				line[j - last_pos] = buffer[j];
			}
			//process the line of text
			char *nl = RebecCleanUpLine(line, i - last_pos);
			if (strlen(nl) >= MINIMUM_LINE_WIDTH) {
				rebec_line_t rl = RebecParseLine(nl, line_no);
				line_count++;
				rlines = realloc(rlines, sizeof(rebec_line_t) * line_count);
				rlines[line_count - 1] = rl;
			}
			free(nl);
			last_pos = i + 1;
			line_no++;
		}
	}
	
	//Build our mock symbol table. We don't need a true
	//  table because it is the assembler's job to
	//  figure out the true final values of the symbols.
	LabelList ll = NewLabelList();
	for (int i = 0; i < line_count; i++) {
		char* symbol = RebecLineGetSymbol(&rlines[i]);
		if (symbol != NULL) {
			if (LabelLookup(ll, symbol) != -1) {
				printf("Error on line %i: Duplicate symbol.\n", rlines[i].line_no);
				exit(1);
			}
			LabelListAddLabel(&ll, symbol, 0);
		}
	}

	LabelListAddLabel(&ll, "PC", PC);
	LabelListAddLabel(&ll, "IP", PC);
	LabelListAddLabel(&ll, "ACC", ACC);
	LabelListAddLabel(&ll, "ZERO", ZERO);
	LabelListAddLabel(&ll, "POS", POS);
	LabelListAddLabel(&ll, "NEG", NEG);
	LabelListAddLabel(&ll, "IN", IN);
	LabelListAddLabel(&ll, "OUT", OUT);
	LabelListAddLabel(&ll, "ROM", ROM);

	LabelListAddLabel(&ll, "pc", PC);
	LabelListAddLabel(&ll, "ip", PC);
	LabelListAddLabel(&ll, "acc", ACC);
	LabelListAddLabel(&ll, "zero", ZERO);
	LabelListAddLabel(&ll, "pos", POS);
	LabelListAddLabel(&ll, "neg", NEG);
	LabelListAddLabel(&ll, "in", IN);
	LabelListAddLabel(&ll, "out", OUT);
	LabelListAddLabel(&ll, "rom", ROM);

	LabelListSortBySize(&ll);
	
	//Validate lines
	for (int i = 0; i < line_count; i++) {
		RebecLineValidate(&rlines[i], ll);
	}	
	FreeLabelList(&ll);

	//Compile
	RebecCompile(rlines, line_count);

	//Clean up lines
	for (int i = 0; i < line_count; i++) {
		FreeRebecLine(&rlines[i]);
	}
	free(rlines);

	return NULL;
}

int main(int argc, char** argv) {
	rebec_line_t* lines = RebecLoadLines(argv[1]);
}
