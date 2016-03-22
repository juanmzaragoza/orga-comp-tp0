/*
* @Author: juanzaragoza
* @Date:   2016-03-21 21:09:04
* @Last Modified by:   juanzaragoza
* @Last Modified time: 2016-03-21 23:29:28
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */
const char *cmdmsg[] = {"-V, --version 	Print version and quit.\n",
                       "-h, --help 		Print this information and quit.\n",
                       "tp0 v0.0.1\n"};

/* Estructura de matriz */
typedef struct matrix {
    size_t rows;
    size_t cols;
    double* array;
} matrix_t;

/* Enumerados */
typedef enum {PRINTHELP_VERSION, PRINTHELP_HELP, PRINT_VERSION} message_t;
typedef enum {SUCESS,ERROR,CONTINUE} status_t;

/* Prototipos */
status_t handleParam(int, char *[], matrix_t **);
void print_message(message_t );
int is_a_int(char *);
int is_a_double(char *);

matrix_t *create_matrix(size_t ,size_t);
void destroy_matrix(matrix_t *);

int main(int argc, char *argv[])
{

	matrix_t **matrix;
	status_t status;

    status = handleParam(argc,argv,matrix);

    if(status == CONTINUE){

    } else if(status == ERROR){

    	return EXIT_FAILURE;

    }

    return EXIT_SUCCESS;
}

status_t handleParam(int argc, char *argv[], matrix_t **matrix)
{
	int i;
	size_t num_rows;
	
	for(i=1; i<argc; i++) {

		if (strcmp(argv[i], "-h") == 0){

			print_message(PRINTHELP_VERSION);
			print_message(PRINTHELP_HELP);
			return SUCESS;

		} else if (strcmp(argv[i], "-V") == 0){

			print_message(PRINT_VERSION);
			return SUCESS;

		} else {
			
			if(i>1){

				if(!is_a_double(argv[i])){
					destroy_matrix(*matrix);
					return ERROR;
				}

				

			} else{ /* if i=1 -> num of rows=cols*/

				if(!is_a_int(argv[i])){
					destroy_matrix(*matrix);
					return ERROR;
				}

				num_rows = atoi(argv[i]);
				*matrix = create_matrix(num_rows,num_rows);

			}
			
		}
	}

	return CONTINUE;
}

/* Check types */
int is_a_int(char * num){
	return 1;
}

int is_a_double(char * num){
	return 1;
}

/* Print messages */
void print_message(message_t message){
	printf("%s", cmdmsg[message]);
}

/* Construct matrix */
matrix_t *create_matrix(size_t rows,size_t cols){

	matrix_t *matrix = (matrix_t *)calloc(1, sizeof(matrix_t));

	matrix->rows = rows;
	matrix->cols = cols;
	matrix->array = (double *)malloc((rows+cols)*sizeof(double));

	return matrix;
}

/* Destroy matrix */
void destroy_matrix(matrix_t *m){

	free(m->array);
	free(m);

}