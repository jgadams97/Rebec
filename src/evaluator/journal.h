typedef struct _Journal {
	int* log;
	double* list;
	int log_size;
	int list_size;
} Journal;

Journal NewJournal();
void FreeJournal(Journal* j);
void JournalLogPush(Journal* j, int val);
int JournalLogPop(Journal* j);
int JournalPush(Journal* j, float val);
double JournalPop(Journal* j, int index);
double JournalPeek(Journal* j, int index);
void PrintJournal(Journal j);

#include "journal.c"
