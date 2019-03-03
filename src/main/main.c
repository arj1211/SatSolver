// ECE 108 Lab 2 -- Sat Solver
//
// Read logical expressions in DIMACS format from files specified on the
// command line, and for each one print its name and one of "satisfiable",
// "unsatisfiable" or "tautology".

#include <stdio.h>
#include "dimacs_reader.h"

int total_combos = 0;
int varvals[100];
int vars_per_clause[100]; // value is the length of literal[] for each line(clause) in file
int arr[100][100]; // x: numOfClauses, y: number of variables per clause, value: literal[i] for j-th clause

int count = 0;
int numOfClauses = 0;
int numOfVars = 0;
int clauses_so_far = 0;

int flg = 0;

void init(int numvars, int numclauses) {
	// Callback function that gets passed to read_dimacs().
	// Indicates start of a new expression with up to numvars variables
	// and numclauses clauses.
	total_combos=0;
	count=0;
	numOfVars=numvars;
	flg=0;
	//printf("numvars: %d", numvars);

	numOfClauses=numclauses;
	clauses_so_far= 0;
	//varvals = new int[numvars+1];
	total_combos = 1 << numvars;
	//printf("total combos: %d\n",total_combos);
	//vars_per_clause = new int[numclauses];
	int i;
	for (i=0;i<100;i++)
	{
		varvals[i]=0;
		vars_per_clause[i]=0;
		int j;
		for (j=0;j<100;j++)
			arr[i][j]=0;
	}
	
}

void add_clause(int numlits, int literals[]) {
	// Callback function that gets passed to read_dimacs().
	// The literals argument is an array of ints, numlits is its length.
	// Each literal is the index (starting from 1) of a variable.
	// Negative integers represent logical negations of variables.
	//arr[][] = new int[numOfClauses][numlits];
	int i;
	// printf("In add_clause...\n");
	for ( i = 0; i < numlits ; i++)
	{
		arr[clauses_so_far][i] = literals[i];
		// printf("arr[%d][%d]=literals[%d]=%d\n", clauses_so_far, i, i, literals[i]);
	}
	if (clauses_so_far>0 && numlits==1 && (arr[clauses_so_far-1][0]/arr[clauses_so_far][0])==-1)
	{
		flg=1;
	}
	vars_per_clause[clauses_so_far]=numlits;
	clauses_so_far++;
}

char *classify() {
	// Evaluate the current expression and return one of
	// "satisfiable", "unsatisfiable" or "tautology".
	// printf("In classify...\n");
	
	if (flg) return "unsatisfiable";

	int C;
	for ( C = 0; C < total_combos ; C++)
	{
		//printf("Combo: %d\n", C);
		int var;
		int c = C;
		for ( var = numOfVars; var > 0 ; var--)
		{
			varvals[var]=c&1;
			// printf("varvals[%d]=%d\n",var,C&1);
			c=c>>1;
		}
		int cl,clause_result=0;
		for ( cl = 0; cl < numOfClauses; cl++)
		{
			int length = vars_per_clause[cl];
			// printf("Clause %d has %d variables..\n", cl, length);
			//result = 0;
			int i;
			clause_result=0;
			for ( i = 0; i < length; i++)
			{
				//printf("arr[cl: %d][i: %d]=%d\n", cl,i,arr[cl][i]);
				if (arr[cl][i]<0)
				{
					//varvals[(-1*arr[cl][i])]=!varvals[(-1*arr[cl][i])];
					//arr[cl][i]*=-1;
					clause_result+=!varvals[-1*arr[cl][i]];
				}
				else clause_result+=varvals[arr[cl][i]];
				//printf("\tresult+=varvals[arr[%d][%d]]=%d\n", cl, i, result);
			}
			if (clause_result==0)
			{
				if (count>1)
				{
					// this means that there has been a previous combo that worked but the current one doesnt, hence its satisfiable
					return "satisfiable";
				}
				//count=0;
				//printf("count: %d\n", count);
				//printf("total_combos: %d\n", total_combos);
				break;
			}
		}// went through all clauses for current combo
		if (clause_result>0)
		{
			count++;
			//printf("\t\tCount so far: %d", count);
		}
		//else if (clause_result==0) count=0;
		//printf("\t\tCount so far: %d\n", count);
	}// end combos
	if (count==total_combos)
	        return "tautology";
        else if (count>0)
        	return "satisfiable";
        else return "unsatisfiable";

}

int main(int argc, char *argv[]) {
	int i;
	//int s=0,un=0,t=0;
	char *c="";
	for (i = 1; i < argc; ++i) 
	{
		read_dimacs(argv[i], init, add_clause);
		c = classify();
		printf("%s: %s\n", argv[i], c);
		//if (c=="satisfiable")s++;
		//else if (c=="unsatisfiable") un++;
		//else t++;
	}
	
	//printf("\nsatisfiable:%d\nunsatisfiable:%d\ntautology:%d\n", s,un,t);

	return 0;
}

