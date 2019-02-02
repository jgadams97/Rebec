//The journal is similar to a stack, however, items can be
//popped off at any given index. The journal keeps track of
//where empty memory indexes are after pops occur, and thus
//when a future item is pushed onto the stack, it will fill
//in empty memory locations first based on the journal log.

//Initializes a new journal
Journal NewJournal() {
	Journal j;
	j.log = malloc(0);
	j.list = malloc(0);
	j.log_size = 0;
	j.list_size = 0;
	return j;
}

//Frees a journal
void FreeJournal(Journal* j) {
	free(j->log);
	free(j->list);
	j->log_size = -1;
	j->list_size = -1;
}

//Pushes a log entry into the journal
void JournalLogPush(Journal* j, int val) {
	j->log_size++;
	j->log = realloc(j->log, (j->log_size) * sizeof(int));
	j->log[ j->log_size - 1 ] = val;
}

//Pops a log entry off the journal and returns its value
int JournalLogPop(Journal* j) {
	int ret = j->log[ j->log_size - 1 ];
	j->log_size--;
	j->log = realloc(j->log, (j->log_size) * sizeof(int));
	return ret;
}

//Pushes a new float into the journal and returns its index
//We return the index because the index is arbitrary!
int JournalPush(Journal* j, float val) {
	
	int index;
	if (j->log_size == 0) {
		index = j->list_size;
		j->list_size++;
		j->list = realloc(j->list, (j->list_size) * sizeof(double));
	} else {
		index = JournalLogPop(j);
	}
	j->list[index] = val;
	return index;
}

//Pops a value off the journal at a given index
double JournalPop(Journal* j, int index) {
	double ret = j->list[index];
	if (index == j->list_size - 1) {
		j->list_size--;
		j->list = realloc(j->list, (j->list_size) * sizeof(double));
	} else {
		JournalLogPush(j, index);
	}
	return ret;
}

//Returns a value from the journal at a given index
double JournalPeek(Journal* j, int index) {
	return j->list[index];
}

//Prints the journal's log and list of values
void PrintJournal(Journal j) {
	int i;

	printf("Log: {");
	for (i = 0; i < j.log_size; i++) {
		printf("%i", j.log[i]);
		if (i != j.log_size - 1) {
			printf(", ");
		}
	}
	printf("}\n");
	printf("List: {");
	for (i = 0; i < j.list_size; i++) {
		printf("%lf", j.list[i]);
		if (i != j.list_size - 1) {
			printf(", ");
		}
	}
	printf("}\n");

}
