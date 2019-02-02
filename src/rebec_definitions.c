rebec_line_t RebecMakeLineWith3Arguments(char *str1, char *str2, char *str3) {
	rebec_line_t tline;
	rebec_arg_t arg0, arg1, arg2;
	arg0.data = str1;
	arg1.data = str2;
	arg2.data = str3;
	tline.argc = 3;
	tline.args = malloc(sizeof(rebec_arg_t) * 3);
	tline.args[0] = arg0;
	tline.args[1] = arg1;
	tline.args[2] = arg2;
	return tline;
}
rebec_line_t RebecMakeLineWith2Arguments(char *str1, char *str2) {
	rebec_line_t tline;
	rebec_arg_t arg0, arg1;
	arg0.data = str1;
	arg1.data = str2;
	tline.argc = 2;
	tline.args = malloc(sizeof(rebec_arg_t) * 2);
	tline.args[0] = arg0;
	tline.args[1] = arg1;
	return tline;
}
rebec_line_t RebecMakeLineWith1Argument(char *str1) {
	rebec_line_t tline;
	rebec_arg_t arg0;
	arg0.data = str1;
	tline.argc = 1;
	tline.args = malloc(sizeof(rebec_arg_t) * 1);
	tline.args[0] = arg0;
	return tline;
}

//handle the "fct" (function) command
void RebecFCT(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: Too many arguments.\n", line.line_no);
		exit(1);
	}
	if (line.args[0].type != DT_FCT) {
		printf("Error on line %i: Missing semicolon.\n", line.line_no);
		exit(1);
	}

	//Append the string onto the output
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, ":\n");

	*poutput = output;
}

//handle the "def" (define) command
void RebecDEF(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc == 0) {
		printf("Error on line %i: DEF statement requires at least 1 argument.\n", line.line_no);
		exit(1);
	}

	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, ":\n");
	for (int i = 1; i < line.argc; i++) {
		if (line.args[i].type == DT_FCT) {
			printf("Error on line %i: Function types are only allowed after FCT or LBL statements.\n", line.line_no);
			exit(1);		
		} else if (line.args[i].type == DT_LIT) {
			RebecAppendOutput(&output, "\trssb ");
			RebecAppendOutput(&output, line.args[i].data);
			RebecAppendOutput(&output, "\n");
		} else if (line.args[i].type == DT_STR) {
			for (int j = 0; j < strlen(line.args[i].data); j++) {
				char c[2];
				c[0] = line.args[i].data[j];
				c[1] = 0;
				RebecAppendOutput(&output, "\trssb '");
				RebecAppendOutput(&output, c);
				RebecAppendOutput(&output, "'\n");
			}
		}
	}
	*poutput = output;
}



//handle the "lwo" (load with offset) command
void RebecLWO(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 3) {
		printf("Error on line %i: `LWO` expects 3 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; LoadWithOffset(A, B, C) {                           ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Apply our offset \n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+5\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output,  "\n");
	if (verbose) RebecAppendOutput(&output, ";Load the data\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output,  "\n");
	if (verbose) RebecAppendOutput(&output, ";Reset offset if >= 0\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb $-7\n");
	if (verbose) RebecAppendOutput(&output, ";Reset offset if < 0\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output,  "\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb $-12\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "swo" (store with offset) command
void RebecSWO(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 3) {
		printf("Error on line %i: `SWO` expects 3 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; StoreWithOffset(A, B, C) {                           ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Apply our offset \n");
	}		
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+39\n");
	if (verbose) RebecAppendOutput(&output, ";Clear the clear values.\n");
	RebecAppendOutput(&output, "	rssb $+32\n");
	RebecAppendOutput(&output, "	rssb $+31\n");
	RebecAppendOutput(&output, "	rssb $+30\n");
	RebecAppendOutput(&output, "	rssb $+29\n");
	RebecAppendOutput(&output, "	rssb $+29\n");
	RebecAppendOutput(&output, "	rssb $+28\n");
	RebecAppendOutput(&output, "	rssb $+27\n");
	RebecAppendOutput(&output, "	rssb $+26\n");
	RebecAppendOutput(&output, "	rssb $+26\n");
	RebecAppendOutput(&output, "	rssb $+25\n");
	RebecAppendOutput(&output, "	rssb $+24\n");
	RebecAppendOutput(&output, "	rssb $+23\n");
	if (verbose) RebecAppendOutput(&output, ";Copy the new clear values over.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+24\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+15\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+18\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+10\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+12\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+5\n");
	if (verbose) RebecAppendOutput(&output, ";Clear our store location.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Load our byte from the location.\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Undo our offset.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb $-4\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb $-9\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//handle the "neg" (negation) command
void RebecNEG(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `NEG` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Negation(A) {                                       ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_1___\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_1___\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_1___\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_1___\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_1___\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_1___\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//handle the "ldi" (load immidiate) command
void RebecLDI(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `LDI` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; LoadImmidiate(A, B) {                               ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb $+7\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "lbr" (load by reference) command
void RebecLBR(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `LBR` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; LoadByReference(A, B) {                             ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	if (verbose) RebecAppendOutput(&output, ";Load the location to store the data.\n");
	RebecAppendOutput(&output, "	rssb $+12\n");
	RebecAppendOutput(&output, "	rssb $+11\n");
	RebecAppendOutput(&output, "	rssb $+10\n");
	RebecAppendOutput(&output, "	rssb $+9\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+5\n");
	if (verbose) RebecAppendOutput(&output, ";Store the data.\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb 0\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//handle the "add" (addition) command
void RebecADD(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `ADD` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Addition(A, B) {                                    ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//handle the "sub" (subtraction) command
void RebecSUB(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `SUB` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Subtraction(A, B) {                                 ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Subtract if subtrahend >= 0\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Subtract if subtrahend < 0\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "inc" (incrementation) command
void RebecINC(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `INC` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Incrementation(A) {                                 ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb pos\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "dec" (decrementation) command
void RebecDEC(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `DEC` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Decrementation(A) {                                 ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "clr" (clear) command
void RebecCLR(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `CLR` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Clear(A) {                                          ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");;
	}
	*poutput = output;
}

//handle the "end" (end) command
void RebecEND(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 0) {
		printf("Error on line %i: `END` expects 0 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Exit() {                                            ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}


//handle the "lod" (load) command
void RebecLOD(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `LOD` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Load(A, B) {                                        ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}

//handle the "sto" (store) command
void RebecSTO(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `STO` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Store(A, B) {                                       ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}

//handle the "sbr" (store by reference) command
void RebecSBR(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `SBR` expects 2 arguments.\n", line.line_no);
		exit(1);
	}
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; StoreByReference(A, B) {                            ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	RebecAppendOutput(&output, "	rssb $+34\n");
	RebecAppendOutput(&output, "	rssb $+33\n");
	RebecAppendOutput(&output, "	rssb $+32\n");
	RebecAppendOutput(&output, "	rssb $+31\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+27\n");
	RebecAppendOutput(&output, "	rssb $+27\n");
	RebecAppendOutput(&output, "	rssb $+26\n");
	RebecAppendOutput(&output, "	rssb $+25\n");
	RebecAppendOutput(&output, "	rssb $+24\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+20\n");
	RebecAppendOutput(&output, "	rssb $+20\n");
	RebecAppendOutput(&output, "	rssb $+19\n");
	RebecAppendOutput(&output, "	rssb $+18\n");
	RebecAppendOutput(&output, "	rssb $+17\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+13\n");
	RebecAppendOutput(&output, "	rssb $+18\n");
	RebecAppendOutput(&output, "	rssb $+17\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb $+15\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+11\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb 0\n");
	RebecAppendOutput(&output, "	rssb 0\n");
	RebecAppendOutput(&output, "	rssb 0\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb 0\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}

//handle the "get" (get) command
void RebecGET(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `GET` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Get(A) {                                            ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb in\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}

//handle the "jmp" (jump) command
void RebecJMP(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `JMP` expects 1 argument.\n", line.line_no);
		exit(1);
	}
	
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Jump(A) {                                           ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+7\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "-$+3\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}

//handle the "ret" (return) command
void RebecRET(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 0) {
		printf("Error on line %i: `RET` expects 0 arguments.\n", line.line_no);
		exit(1);
	}

	rebec_line_t tline;
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Return() {                                          ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Decrement the stack pointer\n");
	}	
	tline = RebecMakeLineWith1Argument("___REBEC_STACK_POINTER___"); RebecDEC(tline, &output, 0); free(tline.args);
	if (verbose) RebecAppendOutput(&output, ";Load the stack pointer\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", "___REBEC_STACK_POINTER___"); RebecLBR(tline, &output, 0); free(tline.args);
	//if (verbose) RebecAppendOutput(&output, ";Negate the address\n");
	//tline = RebecMakeLineWith1Argument("___REBEC_TEMP_2___"); RebecNEG(tline, &output, 0); free(tline.args);
	if (verbose) RebecAppendOutput(&output, ";Subtract from here\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+10\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+6\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");

	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb $+7\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the address.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");

	//fromhere += backhere - fromhere

	/*acc[0] = to
	acc[1] = from - to
	acc[2] = to - from
	acc[3] = pc - to - from*/


	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	//acc[0] = pc - 0 = pc 
	//acc[1] = -pc 
	//acc[2] = addr + pc
	//acc[3] = pc - (addr + pc) = addr
	*poutput = output;
}

//handle the "cal" (call) command
void RebecCAL(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `CAL` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	rebec_line_t tline;
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Call() {                                            ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	if (verbose) RebecAppendOutput(&output, ";Store our location in the stack.\n");
	tline = RebecMakeLineWith2Arguments("$+7", "___REBEC_STACK_POINTER___"); RebecSBR(tline, &output, 0); free(tline.args);
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb $+17\n");
	if (verbose) RebecAppendOutput(&output, ";Increment the stack pointer.\n");
	tline = RebecMakeLineWith1Argument("___REBEC_STACK_POINTER___"); RebecINC(tline, &output, 0); free(tline.args);
	if (verbose) RebecAppendOutput(&output, ";Jump to the call.\n");
	RebecJMP(line, &output, 0);
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}

	*poutput = output;
}


//handle the "set" (set) command
void RebecSET(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;
	rebec_line_t tline;

	if (line.argc != 1) {
		printf("Error on line %i: `SET` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; Set(A) {                                            ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}
	if (verbose) RebecAppendOutput(&output, ";Store the set character.\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[0].data); RebecLOD(tline, &output, 0); free(tline.args);
	if (verbose) RebecAppendOutput(&output, ";Negate the input.\n");
	RebecNEG(line, &output, 0);
	if (verbose) RebecAppendOutput(&output, ";Add our previous output to the input.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_PREVIOUS_OUTPUT___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Subtract the input from the previous output.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_PREVIOUS_OUTPUT___\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_PREVIOUS_OUTPUT___\n");
	if (verbose) RebecAppendOutput(&output, ";Subtract the input from the output\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb out\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb out\n");
	if (verbose) RebecAppendOutput(&output, ";Negate the input.\n");
	RebecNEG(line, &output, 0);
	if (verbose) RebecAppendOutput(&output, ";Restore the set character.\n");
	tline = RebecMakeLineWith2Arguments(line.args[0].data, "___REBEC_TEMP_2___"); RebecLOD(tline, &output, 0); free(tline.args);

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "jup" (jump up if positive) command
void RebecJUP(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `JUP` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpUpIfPositive(A, B) {                            ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Mathematically, these next three sections do nothing\n");
		RebecAppendOutput(&output, ";  if the input is positive, but if it is negative then\n");
		RebecAppendOutput(&output, ";  its value is changed to be -1\n");
		RebecAppendOutput(&output, ";Add 1 to the input.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb pos\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";If the input is negative, clear it.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Decrement the input.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+4\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+7\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Restore the removed `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb $-1\n");
	RebecAppendOutput(&output, "	rssb $-2\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ($-5)-");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "jdp" (jump down if positive) command
void RebecJDP(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `JDP` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpDownIfPositive(A, B) {                          ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Mathematically, these next three sections do nothing\n");
		RebecAppendOutput(&output, ";  if the input is positive, but if it is negative then\n");
		RebecAppendOutput(&output, ";  its value is changed to be -1\n");
		RebecAppendOutput(&output, ";Add 1 to the input.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb pos\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";If the input is negative, clear it.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Decrement the input.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+5\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+7\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Restore the removed `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb $-1\n");
	RebecAppendOutput(&output, "	rssb $-2\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ($-5)-");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//handle the "jnn" (jump up if not negative) command
void RebecJNN(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 2) {
		printf("Error on line %i: `JNN` expects 2 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpIfNotNegative(A, B) {                           ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Mathematically, these next three sections do nothing\n");
		RebecAppendOutput(&output, ";  if the input is positive, but if it is negative then\n");
		RebecAppendOutput(&output, ";  its value is changed to be -1\n");
		RebecAppendOutput(&output, ";Add 1 to the input.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb pos\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";If the input is negative, clear it.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Decrement the input.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+9\n");
	if (verbose) RebecAppendOutput(&output, ";Repeat this for the other `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+9\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address if it is positive.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address if negative.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Restore the two removed `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $-3\n");
	RebecAppendOutput(&output, "	rssb $-4\n");
	RebecAppendOutput(&output, "	rssb $-10\n");
	RebecAppendOutput(&output, "	rssb $-11\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to if positive.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ($-15)-");//XX
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to if negative.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ($-14)-");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//If a value is negative, make it -1
void RebecN1N(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;

	if (line.argc != 1) {
		printf("Error on line %i: `N1N` expects 1 argument.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";Mathematically, these next three sections do nothing\n");
		RebecAppendOutput(&output, ";  if the input is positive, but if it is negative then\n");
		RebecAppendOutput(&output, ";  its value is changed to be -1\n");
		RebecAppendOutput(&output, ";Add 1 to the input.\n");
	}

	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb pos\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";If the input is negative, clear it.\n");
	RebecAppendOutput(&output, "	rssb acc\n"); //These lines
 	RebecAppendOutput(&output, "	rssb acc\n"); //  are not
	RebecAppendOutput(&output, "	rssb ");      //  really necessary.
	RebecAppendOutput(&output, line.args[0].data);//  They will
	RebecAppendOutput(&output, "\n");             //  be removed.
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Decrement the input.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	
	*poutput = output;
}
//handle the "jpe" (jump if equal) command
void RebecSSB(rebec_line_t line, char **poutput, int verbose) {}

//handle the "jpe" (jump if equal) command
void RebecJPE(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;
	rebec_line_t tline;

	if (line.argc != 3) {
		printf("Error on line %i: `JPE` expects 3 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpIfEqual(A, B) {                           ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Clear the temporary register..\n");
	}	

	if (verbose) RebecAppendOutput(&output, ";Subtract the second value from the first.\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[1].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[2].data); RebecSUB(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_2___"); RebecN1N(tline, &output, 0); free(tline.args);

	
	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+53\n");
	if (verbose) RebecAppendOutput(&output, ";Repeat this for the other `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+53\n");


	if (verbose) RebecAppendOutput(&output, ";Subtract the first value from the second.\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[2].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[1].data); RebecSUB(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_2___"); RebecN1N(tline, &output, 0); free(tline.args);

	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+9\n");
	if (verbose) RebecAppendOutput(&output, ";Repeat this for the other `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+9\n");

	if (verbose) RebecAppendOutput(&output, ";Jump to the given address if it is positive.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address if negative.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Restore the two removed `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $-3\n");
	RebecAppendOutput(&output, "	rssb $-4\n");
	RebecAppendOutput(&output, "	rssb $-10\n");
	RebecAppendOutput(&output, "	rssb $-11\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to if positive.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ($-15)-");//XX
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to if negative.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ($-14)-");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "\n");

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}


//handle the "jne" (jump if not equal) command
void RebecJNE(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;
	rebec_line_t tline;

	if (line.argc != 3) {
		printf("Error on line %i: `JNE` expects 3 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpIfNotEqual(A, B) {                           ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, ";Clear the temporary register..\n");
	}

	if (verbose) RebecAppendOutput(&output, ";Subtract the second value from the first.\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[1].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[2].data); RebecSUB(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_2___"); RebecN1N(tline, &output, 0); free(tline.args);

	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+53\n");
	if (verbose) RebecAppendOutput(&output, ";Repeat this for the other `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+53\n");


	if (verbose) RebecAppendOutput(&output, ";Subtract the first value from the second.\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[2].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_2___", line.args[1].data); RebecSUB(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_2___"); RebecN1N(tline, &output, 0); free(tline.args);

	if (verbose) {
		RebecAppendOutput(&output, ";If the input is negative then replace `rssb pc` within\n");
		RebecAppendOutput(&output, ";  this segment with the negation of the input. Since\n");
		RebecAppendOutput(&output, ";  the negation of the input is always -1 if it is \n");
		RebecAppendOutput(&output, ";  negative, then `rssb pc` will always be overwritten\n");
		RebecAppendOutput(&output, ";  with the value 1, which is the same as `rssb acc`.\n");
	}	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+9\n");
	if (verbose) RebecAppendOutput(&output, ";Repeat this for the other `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_2___\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb $+9\n");

	if (verbose) RebecAppendOutput(&output, ";Jump to the given address if it is positive.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address if negative.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+16\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	if (verbose) RebecAppendOutput(&output, ";Restore the two removed `rssb pc`.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $-3\n");
	RebecAppendOutput(&output, "	rssb $-4\n");
	RebecAppendOutput(&output, "	rssb $-10\n");
	RebecAppendOutput(&output, "	rssb $-11\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to if positive.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb -30\n");
	if (verbose) RebecAppendOutput(&output, ";Storage for the address to jump to if negative.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb -25\n");
	if (verbose) RebecAppendOutput(&output, ";Jump to the given address.\n");	
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb $+7\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb zero\n");
	RebecAppendOutput(&output, "	rssb pc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[0].data);
	RebecAppendOutput(&output, "-$+3\n");
	
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; }                                                   ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n\n");
	}
	*poutput = output;
}

//handle the "jge" (jump if greater than or equal to) command
void RebecJGE(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;
	rebec_line_t tline;

	if (line.argc != 3) {
		printf("Error on line %i: `JGE` expects 3 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpIfGreaterThanOrEqualTo(A, B, C) {               ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	
	if (verbose) RebecAppendOutput(&output, ";Preserve inputs.\n");
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_5___", line.args[1].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_6___", line.args[2].data); RebecLOD(tline, &output, 0); free(tline.args);
	
	if (verbose) RebecAppendOutput(&output, ";Clear some temporary space.\n");
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_3___"); RebecCLR(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_4___"); RebecCLR(tline, &output, 0); free(tline.args);
	//if (verbose) RebecAppendOutput(&output, ";TEMP3 is 0 if A >= B.\n");
	RebecAppendOutput(&output, "	rssb pos\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_3___\n");
	//if (verbose) RebecAppendOutput(&output, ";Load B into the accumulator.\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[2].data);
	RebecAppendOutput(&output, "\n");
	//if (verbose) RebecAppendOutput(&output, ";...\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_3___\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_3___\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ");
	RebecAppendOutput(&output, line.args[1].data);
	RebecAppendOutput(&output, "\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb neg\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_3___\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb ___REBEC_TEMP_4___\n");
	
	if (verbose) RebecAppendOutput(&output, ";Reset TEMP3 to 0.\n");
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_3___"); RebecCLR(tline, &output, 0); free(tline.args);
	
	if (verbose) RebecAppendOutput(&output, ";Restore inputs.\n");
	tline = RebecMakeLineWith2Arguments(line.args[1].data, "___REBEC_TEMP_5___"); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments(line.args[2].data, "___REBEC_TEMP_6___"); RebecLOD(tline, &output, 0); free(tline.args);
	
	if (verbose) RebecAppendOutput(&output, ";Jump if TEMP4 is zero.\n");
	tline = RebecMakeLineWith3Arguments(line.args[0].data, "___REBEC_TEMP_3___", "___REBEC_TEMP_4___"); RebecJPE(tline, &output, 0); free(tline.args);
	
	*poutput = output;

}

//handle the "jle" (jump if less than or equal to) command
void RebecJLE(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;
	rebec_line_t tline;

	if (line.argc != 3) {
		printf("Error on line %i: `JLE` expects 3 arguments.\n", line.line_no);
		exit(1);
	}

	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpIfLessThanOrEqualTo(A, B, C) {               ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	
	tline = RebecMakeLineWith3Arguments(line.args[0].data, line.args[2].data, line.args[1].data); RebecJGE(tline, &output, 0); free(tline.args);
	
	*poutput = output;
	
}
//handle the "jpl" (jump if less than) command
void RebecJPL(rebec_line_t line, char **poutput, int verbose) {
	char *output = *poutput;
	rebec_line_t tline;

	if (line.argc != 3) {
		printf("Error on line %i: `JPL` expects 3 arguments.\n", line.line_no);
		exit(1);
	}
	
	if (verbose) {
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
		RebecAppendOutput(&output, "; JumpIfLessThan(A, B, C) {               ;\n");
		RebecAppendOutput(&output, ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
	}	

	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_6___", "-32768"); RebecLDI(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_7___", line.args[2].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith3Arguments("($+192)", "___REBEC_TEMP_6___", "___REBEC_TEMP_7___"); RebecJPE(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith2Arguments("___REBEC_TEMP_7___", line.args[2].data); RebecLOD(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith1Argument("___REBEC_TEMP_7___"); RebecDEC(tline, &output, 0); free(tline.args);
	tline = RebecMakeLineWith3Arguments(line.args[0].data, line.args[1].data, "___REBEC_TEMP_7___"); RebecJLE(tline, &output, 0); free(tline.args);
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, "	rssb acc\n");
	RebecAppendOutput(&output, ";here\n");
	
	*poutput = output;
	
}
