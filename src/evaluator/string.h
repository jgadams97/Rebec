typedef struct _String {
	char* data;
	int length;

} String;
typedef struct _Substring {
	char* parent;
	int position;
	int length;
} Substring;

String NewString();
void FreeString(String* s);
void StringPush(String* s, char c);
String CStringToString(char* cs);
void StringConcat(String* s1, String s2);
int StringCompare(String s1, String s2);
char StringCharAt(String s, int position);
void PrintString(String s);
String SubstringToString(Substring ss);
Substring NewSubstring(String s, int position, int length);
char SubstringCharAt(Substring ss, int i);
void PrintSubstring(Substring ss);
void StringRemoveWhitespace(String* s);
double StringToDouble(String s);
int StringToInteger(String s);
void StringReverse(String* s);
String IntegerToString(int val);
int StringFind(String s, char c);

#include "string.c"
