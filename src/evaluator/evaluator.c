//The operator table is a table of operators for
//


void RemoveWhitespace(char** pline) {
	char* line = *pline;
	int new_line_len = 0;
	int line_len = strlen(line);
	int i;
	for (i = 0; i < line_len; i++) {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r') {
			new_line_len++;
		} 
	}
	char new_line[new_line_len];
	char new_line_pos = 0;
	for (i = 0; i < line_len; i++) {
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r') {
			new_line[new_line_pos++] = line[i];
		} 
	}
	line = realloc(line, new_line_len + 1);
	memcpy(line, new_line, new_line_len);
	line[new_line_len] = 0;
	*pline = line;
		
}

void FixDollarSign(char** pline, int pos) {
	
	char* line = *pline;
	int line_len = strlen(line);
	int i;
	for (i = 0; i < line_len; i++) {
		if (line[i] == '$') {
			char pos_string[100];
			sprintf(pos_string, "%i", pos);
			int pos_string_len = strlen(pos_string);

			int new_line_len = line_len + pos_string_len - 1;
			char new_line[new_line_len];

			memcpy(new_line, line, i);
			memcpy(new_line + i, pos_string, pos_string_len);
			memcpy(new_line + i + pos_string_len, line + i + 1, line_len - i - 1);


			line = realloc(line, new_line_len + 1);
			memcpy(line, new_line, new_line_len + 1);
			line[new_line_len] = 0;
			
			line_len = new_line_len + 1;
		}
	}
	*pline = line;
}

void FixNegatives(char** pline) {
	char* line = *pline;
	RemoveWhitespace(&line);

	int line_len = strlen(line);
	int i;
	for (i = 0; i < line_len; i++) {
		if (line[i] == '-') {
			int good = 1;
			if (i == 0) {
				good = 0;
			} else {
				if (	line[ i - 1 ] == '(' ||
					line[ i - 1 ] == '+' || 
					line[ i - 1 ] == '-' ||
					line[ i - 1 ] == '*' ||
					line[ i - 1 ] == '/'	) {
					good = 0;
				}
			}
			if (good == 0) {
				int new_line_len = line_len + 1;
				char new_line[new_line_len];
				memcpy(new_line, line, i);
				new_line[i] = '0';
				memcpy(new_line + i + 1, line + i, line_len - i);
				line = realloc(line, new_line_len + 1);
				memcpy(line, new_line, new_line_len + 1);
				line[new_line_len] = 0;
			}
		}
	}
	*pline = line;
}

void FixCharCode(char** pline) {
	char* line = *pline;
	int line_len = strlen(line);
	if (line_len == 3) {
		if (line[0] == '\'' && line[2] == '\'') {
			char new_line[100];
			int char_code = (int)line[1];
			sprintf(new_line, "%i", char_code);
			line_len = strlen(new_line);
			line = realloc(line, line_len + 1);
			memcpy(line, new_line, line_len + 1);			
		}
	} else if (line_len == 2) {
		if (line[0] == '\'' && line[1] == '\'') {
			char new_line[100];
			int char_code = 32;
			sprintf(new_line, "%i", char_code);
			line_len = strlen(new_line);
			line = realloc(line, line_len + 1);
			memcpy(line, new_line, line_len + 1);			
		}
	} else if (line_len == 4) {
		if (line[0] == '\'' && line[3] == '\'') {
			if (line[1] == '\\' && line[2] == 'n') {
				char new_line[100];
				int char_code = 10;
				sprintf(new_line, "%i", char_code);
				line_len = strlen(new_line);
				line = realloc(line, line_len + 1);
				memcpy(line, new_line, line_len + 1);
			}			
		}
	}
	*pline = line;
}


Evaluator NewEvaluator(double(*callback)(double, double, char)) {
	Evaluator ev;
	ev.map = malloc(0);
	ev.list = malloc(0);
	ev.depth = malloc(0);
	ev.callback = callback;
	ev.length = 0;
	ev.importance = 1;
	return ev;
}


int EvaluatorGetDepth(char op, Evaluator ev) {
	int ret = -1;

	int i = 0;
	for (i = 0; i < ev.length; i++) {
		if (ev.list[i] == op) {
			return ev.depth[i];
		}
	}
}

void FreeEvaluator(Evaluator* ev) {
	free(ev->map);
	free(ev->list);
	free(ev->depth);
	ev->callback = NULL;
}

void EvaluatorPush(Evaluator* ev, char c, int depth) {

	depth--;
	ev->length++;

	ev->list = realloc(ev->list, ev->length);
	ev->map = realloc(ev->map, (ev->length) * sizeof(int));
	ev->depth = realloc(ev->depth, (ev->length) * sizeof(int));

	ev->list[ ev->length - 1 ] = c;
	ev->map[ ev->length - 1 ] = depth == 1 ? ev->importance : ev->importance * 100;
	ev->depth[ ev->length - 1 ] = depth;

	ev->importance++;


}

int CharIsOperator(char c, Evaluator ev) {
	if (c == '(') return 1;
	else if (c == ')') return 1;

	int i;
	for (i = 0; i < ev.length; i++) {
		if (c == ev.list[i]) {
			return 1;
		}
	}

	return 0;
}


int EvaluatorVariableToIndex(String s) {
	Substring ss = NewSubstring(s, 1, s.length - 1);
	String tmp_str = SubstringToString(ss);
	int index = StringToInteger(tmp_str);
	FreeString(&tmp_str);
	return index;
}

Substring EvaluatorGetMostImportant(String s, Evaluator ev) {
	int i, j;
	int most_important_position = -1;
	int most_important = -1;
	int inherent_importance = 0;
	int relative_importance = 0;

	for (i = 0; i < s.length; i++) {
		inherent_importance = 0;

		char c = StringCharAt(s, i);
		if (c == '(') relative_importance += 10000;
		else if (c == ')') relative_importance -= 10000;
		for (j = 0; j < ev.length; j++) {
			if (c == ev.list[j]) {
				inherent_importance = ev.map[j];
			}
		}

		int true_importance = inherent_importance + relative_importance;
		if (true_importance > most_important) {
			most_important = true_importance;
			most_important_position = i;
		} 
	}
	while (StringCharAt(s, most_important_position) == '(') {
		most_important_position++;
	}

	if (CharIsOperator(StringCharAt(s, most_important_position), ev)) {
		if (most_important_position != 0) {
			most_important_position--;
		}
	}

	for (i = most_important_position; i >= 1; i--) {
		char c = StringCharAt(s, i);
		if (!CharIsOperator(c, ev)) {
			most_important_position--;
		} else {
			most_important_position++;
			break;
		}
	}

	if (StringCharAt(s, most_important_position) == '(') {
		most_important_position++;
	}

	int length = 0;
	int found_once = 0;
	for (i = most_important_position; i < s.length; i++) {
		length++;
		char c = StringCharAt(s, i);
		if (c == ')') {
			break;
		}
		if (CharIsOperator(c, ev)) {
			if (found_once) {
				break;
			} else {
				found_once++;
			}
		}
	}

	if (i != s.length) {
		length--;
	}

	Substring ss = NewSubstring(s, most_important_position, length);	
	return ss;
}

int EvaluatorGetType(Substring ss, Evaluator ev) {
	int i;
	int mid_operator = 0;
	for (i = 1; i < ss.length; i++) {
		if (CharIsOperator(SubstringCharAt(ss, i), ev)) {
			mid_operator = 1;
			break;
		}
	}
	int init_operator = CharIsOperator(SubstringCharAt(ss, 0), ev);

	int variables = 0;
	for (i = 0; i < ss.length; i++) {
		if (SubstringCharAt(ss, i) == '@') {
			variables++;
		}
	}


	//types:
	//	0:	[k]
	//	1:	[v]
	//	2:	DOESN'T EXIST
	//	3:	[ev][k]
	//	4:	[ev][v]
	//	5:	DOESN'T EXIST
	//	6:	[k][ev][k]
	//	7:	[v][ev][k] or [k][ev][v]
	//	8:	[v][ev][v]
	return mid_operator*2*3 + init_operator*3 + variables;
}

int EvaluatorValidate(String s) {
	if (s.length == 0) {
		return 0;
	}

	if (StringCharAt(s, 0) != '@') {
		if (!StringIsNumeric(s)) {
			return 0;
		}
	}
	return 1;
}
//Evaluate the substring and store the results onto the
//journal and return the index of those results.
int EvaluatorEvalSubtring(Substring ss, Evaluator ev, Journal* j) {
	int type = EvaluatorGetType(ss, ev);
	String lhs = NewString();
	String rhs = NewString();
	char operator;
	
	int i;

	//This part sets up lhs and rhs and identifies the operator
	if (type != 0 && type != 1) {
		for (i = 0; i < ss.length; i++) {
			char c = SubstringCharAt(ss, i);
			if (CharIsOperator(c, ev)) {
				i++;
				operator = c;
				break;
			} else {
				StringPush(&lhs, c);
			}
		}
		for (i = i; i < ss.length; i++) {
			char c = SubstringCharAt(ss, i);
			StringPush(&rhs, c);
		}
	}

	String tmp;

	//Check for errors
	int error = 0;
	switch (type) {
		case 0:
		case 1:
			tmp = SubstringToString(ss);
			if (!EvaluatorValidate(tmp)) {
				error = 1;
			}
			FreeString(&tmp);
			break;
		case 3:
		case 4:
			if (!EvaluatorValidate(rhs)) {
				error = 2;
			}
			if (EvaluatorGetDepth(operator, ev) != 0) {
				error = 2;
			}
			break;
		case 6:
		case 7:
		case 8:
			if (!EvaluatorValidate(rhs) || !EvaluatorValidate(lhs)) {
				error = 1;
			}
			if (EvaluatorGetDepth(operator, ev) != 1) {
				error = 2;
			}
			break;
	}
	if (error != 0) { 
		return -error;
	}

	//This part actually evaluates the string
	double val1, val2, ret;
	int index;

	//printf("Type: %i\n", type);
	switch (type) {
		case 0:
			tmp = SubstringToString(ss);
			ret = StringToDouble(tmp);
			index = JournalPush(j, ret);
			FreeString(&tmp);
			break;
		case 1:
			tmp = SubstringToString(ss);
			index = EvaluatorVariableToIndex(tmp);
			FreeString(&tmp);
			break;
		case 3:
			val1 = StringToDouble(rhs);
			ret = ev.callback(val1, -1, operator);
			index = JournalPush(j, ret);
			break;
		case 4:
			index = EvaluatorVariableToIndex(rhs);
			val1 = JournalPop(j, index);
			ret = ev.callback(val1, -1, operator);
			index = JournalPush(j, ret);
			break;
		case 6:
			val1 = StringToDouble(lhs);
			val2 = StringToDouble(rhs);
			ret = ev.callback(val1, val2, operator);
			index = JournalPush(j, ret);
			break;
		case 7:
			if (StringCharAt(lhs, 0) == '@') {
				index = EvaluatorVariableToIndex(lhs);
				val1 = JournalPop(j, index);
			} else {
				val1 = StringToDouble(lhs);
			}
			if (StringCharAt(rhs, 0) == '@') {
				index = EvaluatorVariableToIndex(rhs);
				val2 = JournalPop(j, index);
			} else {
				val2 = StringToDouble(rhs);
			}
			ret = ev.callback(val1, val2, operator);
			index = JournalPush(j, ret);
			break;
		case 8:
			index = EvaluatorVariableToIndex(lhs);
			val1 = JournalPop(j, index);
			index = EvaluatorVariableToIndex(rhs);
			val2 = JournalPop(j, index);
			ret = ev.callback(val1, val2, operator);
			index = JournalPush(j, ret);
			break;
	}
	
	//printf("Values: %lf, %lf (Case %i)\n", val1, val2, type);
	FreeString(&lhs);
	FreeString(&rhs);

	return index;
}

//Updates a string by replacing the substring with the index
//of where the results of it are located in the journal
void EvaluatorUpdateString(String* s, Substring ss, int index) {
	Substring lhs = NewSubstring(*s, 0, ss.position);
	Substring rhs = NewSubstring(*s, ss.position + ss.length, 
					s->length - ss.length - ss.position);
	if (lhs.length != 0) {
		if (StringCharAt(*s, lhs.length - 1) == '(') {
			if (rhs.length != 0) {
				if (SubstringCharAt(rhs, 0) == ')') {
					lhs.length--;
					rhs.position++;
					rhs.length--;
				}
			}
		}
	}

	String builder = NewString();
	String tmp1 = SubstringToString(lhs);
	String tmp2 = CStringToString("@");
	String tmp3 = IntegerToString(index);
	String tmp4 = SubstringToString(rhs);

	StringConcat(&builder, tmp1);
	StringConcat(&builder, tmp2);
	StringConcat(&builder, tmp3);
	StringConcat(&builder, tmp4);

	FreeString(&tmp1);
	FreeString(&tmp2);
	FreeString(&tmp3);
	FreeString(&tmp4);
	FreeString(s);

	s->length = builder.length;
	s->data = builder.data;

}

int EvaluatorBracketsCheck(String s) {
	int i;
	int brackets = 0;
	for (i = 0; i < s.length; i++) {
		char c = StringCharAt(s, i);
		if (c == '(') {
			brackets++;
		} else if (c == ')') {
			brackets--;
		}
	}
	if (brackets != 0) {
		return 0;
	}
	
	return 1;
}

void EvaluatorError(int e) {
	/*
	switch (e) {
		case 0:
			fprintf(stderr,"Syntax error: Unmatched brackets.\n");
			break;
		case 1:
			fprintf(stderr,"Syntax error: Improper use of operators.\n");
			break;
		case 2:
			fprintf(stderr,"Syntax error: Operator used with incorrect depth.\n");
			break;
		case 3:
			fprintf(stderr,"Syntax error: Symbols used that are not in the language!\n");
			break;
		case 4:
			fprintf(stderr,"Syntax error: You cannot have two operators right next to each other!\n");
			break;
		
	}
	*/
	if (ERROR_CODE != 4)
		ERROR_CODE = e + 5;
}

int EvaluatorOperatorCheck(String str, Evaluator ev) {
	int i, j;
	int previous = 0;
	for (i = 0; i < str.length; i++) {

		int found = 0;
		char c = StringCharAt(str, i);
		for (j = 0; j < ev.length; j++) {
			if (ev.list[j] == c) {
				found = 1;
				break;
			}
		}

		if (found && previous) {
			return 0;
		} else if (found) {
			previous = 1;
		} else {
			previous = 0;
		}
	}
	return 1;
}

int EvaluatorLanguageCheck(String str, Evaluator ev) {
	int i;
	for (i = 0; i < str.length; i++) {
		int found = 0;
		char c = StringCharAt(str, i);
		
		if (c >= '0' && c <= '9') {
			found = 1;
			continue;
		}
		if (c == '(' || c == ')' || c == '.') {
			found = 1;
			continue;
		}
		int j;
		for (j = 0; j < ev.length; j++) {
			if (c == ev.list[j]) {
				found = 1;
				break;
			}
		}
		
		if (found == 0) {
			//printf("|%c|\n", c);
			return 0;
		}
		

	}
	return 1;
}

double eval(char* exp, Evaluator ev) {
	int i;
	int error = 0;
	double ret;
	
	String str = CStringToString(exp);
	StringRemoveWhitespace(&str);
	if (str.length == 0) {
		return 0;
	}

	if (!EvaluatorBracketsCheck(str)) {
		FreeString(&str);
		error = 1;
	}
	if (!EvaluatorLanguageCheck(str, ev)) {
		FreeString(&str);
		error = 3;
	}
	if (!EvaluatorOperatorCheck(str, ev)) {
		FreeString(&str);
		error = 4;
	}

	if (error == 0) {
		Journal j = NewJournal();

		//printf("Initial string: "); PrintString(str); printf("\n");
	
		Substring ss;
		String final = CStringToString("@0");

		while (!StringCompare(str, final)) {
			//printf("-----------------------------------------\n");
	
			ss = EvaluatorGetMostImportant(str, ev);
			//printf("Substring chosen (%i,%i): ", ss.position, ss.length); PrintSubstring(ss); printf("\n");
	
			int index = EvaluatorEvalSubtring(ss, ev, &j);
			if (index < 0) {
				error = -index;
				break;
			}
			//printf("Results stored: list[%i] = %lf\n", index, j.list[index]);
		
			EvaluatorUpdateString(&str, ss, index);
			//printf("Updated string: "); PrintString(str); printf("\n");
		}
	
		if (error == 0) {
			ret = JournalPop(&j, 0);
		}
		
		FreeString(&final);
		FreeString(&str);
		FreeJournal(&j);
	}

	if (error != 0) {
		EvaluatorError(error);
		return -1;
	}
		
	return ret;
}

