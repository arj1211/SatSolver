// Definition for the read_dimacs function

// The read_dimacs function parses a file in DIMACS CNF format
// It calls the user-provided callback function init_function, passing it the
// number of variables in the expression and the number of clauses
// It then calls the user-provided callback function add_clause_function
// for each clause, passing the number of variables in the clauses and an
// array of the variable indices (which are negatie for negated variables).

void read_dimacs(const char *filename,
	void (*init_function)(int numvars, int numclauses),
	void (*add_clause_function)(int numlits, int literals[]));

// maximum number of variables references by an expression
#define MAXVARS 32
// maximum number of clauses in an expression
#define MAXCLAUSES 100

