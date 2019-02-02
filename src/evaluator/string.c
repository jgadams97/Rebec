String NewString() {
	String s;
	s.data = malloc(0);
	s.length = 0;
	return s;
}

void FreeString(String* s) {
	free(s->data);
	s->length = -1;
}

void StringPush(String* s, char c) {
	s->length++;
	s->data = realloc(s->data, s->length);
	s->data[ s->length - 1 ] = c;
}

String CStringToString(char* cs) {
	String s;
	int i = 0;
	while (cs[i] != 0) i++;
	s.data = malloc(i);
	s.length = i;
	for (i = 0; i < s.length; i++) {
		s.data[i] = cs[i];
	}
	return s;
}
void StringConcat(String* s1, String s2) {
	int l = s1->length;
	s1->length += s2.length;
	s1->data = realloc(s1->data, s1->length);
	int i;
	for (i = 0; i < s2.length; i++) {
		s1->data[ i + l ] = s2.data[i];
	}
}

int StringCompare(String s1, String s2) {
	if (s1.length != s2.length)
		return 0;
	int i;
	for (i = 0; i < s1.length; ++i) {
		if (s1.data[i] != s2.data[i]) {
			return 0;
		}
	}
	return 1;

}

char StringCharAt(String s, int position) {
	return s.data[position];
}

void PrintString(String s) {
	int i;
	for (i = 0; i < s.length; ++i) {
		printf("%c", s.data[i]);
	}
}

String SubstringToString(Substring ss) {
	String s;
	s.data = malloc(ss.length);
	s.length = ss.length;
	int p = ss.position;

	int i;
	for (i = 0; i < ss.length; i++) {
		s.data[i] = ss.parent[ i + p ];
	}

	return s;
}


Substring NewSubstring(String s, int position, int length) {
	Substring ss;
	ss.position = position;
	ss.length = length;
	ss.parent = s.data;
	return ss;
}

char SubstringCharAt(Substring ss, int i) {
	return ss.parent[ ss.position + i ];
}

void PrintSubstring(Substring ss) {
	int start = ss.position;
	int end = ss.position + ss.length;
	int i;
	for (i = start; i < end; ++i) {
		printf("%c", ss.parent[i]);
	}
	
}

void StringRemoveWhitespace(String* s) {
	String sr = NewString();
	int i;
	for (i = 0; i < s->length; i++) {
		char c = s->data[i];
		if (c != ' ' && c != '\n' && c != '\r' && c != '\t') {
			StringPush(&sr, s->data[i]);
		}
	}
	free(s->data);
	s->data = sr.data;
	s->length = sr.length;
}

double StringToDouble(String s) {
	int i;
	int divisor = 0;
	for (i = 0; i < s.length; i++) {
		if (StringCharAt(s, i) == '.') {
			divisor = s.length - i - 1;
			break;
		}
	}

	double multiplier = 1;
	while (divisor != 0) {
		multiplier /= 10;
		divisor--;
	}

	double d = 0;
	for (i = s.length - 1; i >= 0; i--) {
		char c = StringCharAt(s, i);
		if (c != '.') {
			d += (c - '0') * multiplier;
			multiplier *= 10;
		}
	}

	return d;
}

int StringToInteger(String s) {
	int i;
	int val = 0;
	int multiplier = 1;

	for (i = s.length - 1; i >= 0; i--) {
		char c = StringCharAt(s, i);
		if (c != '.') {
			val += (c - '0') * multiplier;
			multiplier *= 10;
		}
	}

	return val;
}

void StringReverse(String* s) {
	char* new_data = malloc(s->length);
	int i;
	for (i = 0; i < s->length; i++) {
		new_data[i] = s->data[ s->length - i-1 ];
	}
	free(s->data);
	s->data = new_data;

}

int StringIsNumeric(String s) {
	int i;
	for (i = 0; i < s.length; i++) {
		char c = s.data[i];
		if (c < '0' && c >= '9' && c != '.') {
			return 0;
		}
	}
	return 1;
}

int StringFind(String s, char c) {
	int i;
	for (i = 0; i < s.length; i++) {
		if (s.data[i] == c) {
			return i;
		}
	}
	return -1;
}

String IntegerToString(int val) {
	String ret = NewString();
	while (val > 0) {
		StringPush(&ret, (val % 10) + '0');
		val = (val - (val % 10)) / 10;
	}
	if (ret.length == 0) {
		StringPush(&ret, '0');
	}
	StringReverse(&ret);
	return ret;
}
