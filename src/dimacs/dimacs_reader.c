#include <stdio.h>
#include <string.h>

void read_dimacs(const char *filename,
	void (*init_function)(int numvars, int numclauses),
	void (*add_clause_function)(int numlits, int literals[]))
{
	int vars[10000];  // maximum vars per clause
	int nvars = 0;
	int n;
	FILE *in = fopen(filename, "r");
	char buff[1000];
	// ignore comments and look for "problem" definition line
	while (fgets(buff, sizeof(buff), in) != NULL) {
		if (buff[0] == 'p') {
			int nv, nc;
			sscanf(buff, "p cnf %d %d", &nv, &nc);
			init_function(nv, nc);
			break;
		}
	}
	// read the clauses
	while (fscanf(in, "%d", &n) == 1) {
		if (n == 0) {
			add_clause_function(nvars, vars);
			nvars = 0;
		}
		else
			vars[nvars++] = n;
	}
	if (nvars > 0)  // last line may not have ended with zero
		add_clause_function(nvars, vars);
	fclose(in);
}
