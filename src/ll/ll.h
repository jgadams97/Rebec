/*
	This is essentially a library for building symbol tables. 
	I simply refer to "symbols" as "labels" and the "table" as a "list".
*/


typedef struct _Label {
	char* name;
	int location;
} Label;
typedef struct _LabelList {
	Label* list;
	int size;
} LabelList;

//Creates a new label 
Label NewLabel(char* name, int location) {

	Label lbl;

	int line_len = strlen(name);
	char* name_copy = malloc(line_len + 1);
	int i;
	for (i = 0; i < line_len; i++) {
		name_copy[i] = name[i];
	}
	name_copy[i] = 0;
	lbl.name = name_copy;
	lbl.location = location;

	return lbl;
}

//Frees a label
void FreeLabel(Label* lbl) {
	free(lbl->name);
	lbl->location = -1;
}

//Creates a new label list
LabelList NewLabelList() {
	LabelList ll;
	ll.size = 0;
	ll.list = malloc(0);
	return ll;
}

//Frees the label list
void FreeLabelList(LabelList* ll) {
	int i;
	for (i = 0; i < ll->size; i++)
		FreeLabel(&ll->list[i]);
	free(ll->list);
	ll->size = 0;
}

//Checks to see if the string "name" is inside the label list
//Does not work unless this is sorted by size first
int LabelLookup(LabelList ll, char* name) {
	int i;
	for (i = 0; i < ll.size; i++) {
		if (strcmp(name, ll.list[i].name) == 0) {
			return ll.list[i].location;
		}
	}
	return -1;
}

//Adds a label to the label list, "name" is copied inside of 
//  "NewLabel" thus is not freed internally.
void LabelListAddLabel(LabelList* ll, char* name, int location) {
	Label l = NewLabel(name, location);
	ll->size += 1;
	ll->list = realloc(ll->list, (ll->size) * sizeof(Label));
	ll->list[ ll->size - 1 ] = l;
}

//Sorts the label list by size
void LabelListSortBySize(LabelList* label_list) {
	int max_size = -1;
	int i;
	for (i = 0; i < label_list->size; i++) {
		int size = strlen(label_list->list[i].name);
		if (size > max_size) {
			max_size = size;
		}
	}
	LabelList new_label_list = NewLabelList();
	for (i = max_size; i >= 0; i--) {
		int j;
		for (j = 0; j < label_list->size; j++) {
			int size = strlen(label_list->list[j].name);
			if (size == i) {
				LabelListAddLabel(&new_label_list, 
					label_list->list[j].name, 
					label_list->list[j].location);
			}
		}
	}
	FreeLabelList(label_list);
	label_list->size = 0;
	label_list->list = malloc(0);
	
	for (i = 0; i < new_label_list.size; i++) {
		LabelListAddLabel(label_list, 
				new_label_list.list[i].name, 
				new_label_list.list[i].location);
	}

	FreeLabelList(&new_label_list);
}

//Replaces all labels found in a string with their value
//from the label list.
void ReplaceWithLabel(char** pline, LabelList label_list) {
	char* line = *pline;

	int line_len = strlen(line);
	//Loop through every character in the line
	int i;
	for (i = 0; i < line_len; i++) {
		//Loop through every label 
		int j;
		for (j = 0; j < label_list.size; j++) {
			
			//We are going to use this to test if the label
			// label_test exists at i
			char* label_test = label_list.list[j].name;
			int label_len = strlen(label_test); 

			//If our current position in the line plus the length of the label is
			//  is greater than the length of the line, then we know the label
			//  doesn't fit and can't exist here. 
			if (i + label_len <= line_len) {

				//We need to add 1 to account for the null terminator
				char label_check[label_len + 1];
				//Copy the contents of the line at i
				memcpy(label_check, line + i, label_len);
				//Add in the null terminator at the end
				label_check[label_len] = 0;
				//Check to see if the label we're testing equals the line at the
				//  the current position 
				if (strcmp(label_check, label_test) == 0) {
					//We are going to replace the label with its value. The line needs to
					//  be first broken up into 3 parts: the left-hand-side of the label
					//  that we are replacing (LHS), the right-hand-side (RHS), and the
					//  label itself.

					//LHS will start at 0 and have a length of where we found the label, 
					//  if we found the label at index X then there will be X characters
					//  to the LHS of it. 
					int start1 = 0;
					int len1 = i;

					//Convert the label's value to a string
					int label_val_size = snprintf(NULL, 0, "%i", label_list.list[j].location);
					char label_val[label_val_size];
					sprintf(label_val, "%i", label_list.list[j].location);
					
					//The starting position of the second part is just going to be the
					//  the starting position of the first part (0) plus its length (len1) 
					int start2 = start1 + len1;
					int len2 = label_val_size;

					//The RHS will will start at the starting position of the middle part
					//  plus its length. The length of the RHS will be the length of the
					//  entire line minus lebel_len. Notice we subtract label_len and
					//  not len2.
					int start3 = start2 + len2;
					int len3 = (line_len - len1 - label_len);

					//printf("\tlhs[%i,%i]/label[%i,%i]/rhs[%i,%i]: %s\n", 
					//	start1, len1, start2, len2, start3, len3, label_check);

					//Copy the data into lhs and rhs
					char lhs[len1];
					memcpy(lhs, line, len1);
					char rhs[len3];
					memcpy(rhs, line + len1 + label_len, len3);

					//printf("line: %s\n\tlhs[%i,%i]: %s\n\tlabel[%i,%i]: %s\n\trhs[%i,%i]: %s\n", 
					//	line, start1, len1, lhs, start2, len2, label_val, start3, len3, rhs);

					
					int new_line_len = len1 + len2 + len3;
					char new_line[new_line_len + 1];
					memcpy(new_line + 0, lhs, sizeof(char) * len1);
					memcpy(new_line + len1, label_val, sizeof(char) * len2);
					memcpy(new_line + len1 + len2, rhs, sizeof(char) * len3);
					new_line[new_line_len] = 0;

					
					line = realloc(line, sizeof(char) * (new_line_len + 1));
					memcpy(line, new_line, sizeof(char) * new_line_len);
					line[new_line_len] = 0;
					line_len = strlen(line);
				
					break; 
				}
			}
		}
	}
	*pline = line;
}


