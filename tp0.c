/*
* @Author: juanzaragoza
* @Date:   2016-03-21 21:09:04
* @Last Modified by:   juanzaragoza
* @Last Modified time: 2016-03-24 16:28:04
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes */
const char *cmdmsg[] = {
	"-V, --version 	Print version and quit.\n",
	"-h, --help 	Print this information and quit.\n",
	"tp0 v0.0.1\n"};

/* Estructura de matriz */
typedef struct matrix {
    size_t rows;
    size_t cols;
    float* array;
} matrix_t;

/* Enumerados */
typedef enum {PRINTHELP_VERSION, PRINTHELP_HELP, PRINT_VERSION} message_t;
typedef enum {SUCCESS,ERROR,CONTINUE} status_t;

/* Prototipos */
status_t handleParam(int, char *[], FILE **);
void print_message(message_t );

matrix_t* create_matrix(size_t ,size_t);
void destroy_matrix(matrix_t* );
int print_matrix(FILE* , matrix_t* );
matrix_t* matrix_multiply(matrix_t* , matrix_t* );

int main(int argc, char* argv[])
{

	matrix_t *matrix1, *matrix2, *matrix_result;
	status_t status;
	FILE *fp_in;
	char ch;
	int num_rows = 0, i = 0;
	float element;

	fp_in = stdin;
    status = handleParam(argc,argv,&fp_in);

    if(status == SUCCESS){

    	return EXIT_SUCCESS;

    } else if(status == ERROR){

    	fprintf(stderr, "%s\n", "Error al procesar los parámetros de entrada");
    	return EXIT_FAILURE;

    } else{

    	while(!feof(fp_in)){

	    	if(fscanf(fp_in, "%d", &num_rows) == 1){

	    		matrix1 = create_matrix(num_rows,num_rows);
				matrix2 = create_matrix(num_rows,num_rows);

				i = 0;
	    		while (i<num_rows*num_rows && fscanf(fp_in, "%g", &element) == 1){
	    			matrix1->array[i] = element;
	    			i++;
	    		}

	    		while (i >= (num_rows*num_rows) && (i<num_rows*num_rows*2) && fscanf(fp_in, "%g", &element) == 1){
	    			matrix2->array[i-num_rows*num_rows] = element;
	    			i++;
	    		}

	    		if(fscanf(fp_in, "%c", &ch)==1 && ch!='\n'){
					fprintf(stderr, "%s\n", "Mal formato de linea.");
					return EXIT_FAILURE;
	    		}

	    		matrix_result = matrix_multiply(matrix1, matrix2);
	    		print_matrix(stdout, matrix_result);

	    		destroy_matrix(matrix1);
				destroy_matrix(matrix2);
				destroy_matrix(matrix_result);

	    	}

	    }



    }

    fclose(fp_in);

    return EXIT_SUCCESS;
}

status_t handleParam(int argc, char* argv[], FILE **fp_in)
{
	size_t i;
	FILE *f;
	
	for(i=1; i<argc; i++) {

		if (strcmp(argv[i], "-h") == 0){

			print_message(PRINTHELP_VERSION);
			print_message(PRINTHELP_HELP);
			return SUCCESS;

		} else if (strcmp(argv[i], "-V") == 0){

			print_message(PRINT_VERSION);
			return SUCCESS;

		} else {
			
			f = fopen(argv[i], "r");

			if(f != NULL) {
			    *fp_in = f;
			    return CONTINUE;
			}
			
		}
	}

	return CONTINUE;
}

/* Imprimir mensajes */
void print_message(message_t message){
	printf("%s", cmdmsg[message]);
}

/* Construir matriz */
matrix_t *create_matrix(size_t rows,size_t cols){

	matrix_t *matrix = (matrix_t *)calloc(1, sizeof(matrix_t));

	matrix->rows = rows;
	matrix->cols = cols;
	matrix->array = (float *)malloc((rows*cols)*sizeof(float));

	return matrix;
}

/* Destruir matriz */
void destroy_matrix(matrix_t *m){

	free(m->array);
	free(m);

}

/* Imprimir matriz */
int print_matrix(FILE* fp, matrix_t* m){

	size_t i;

	fprintf(fp, "%zu ", m->rows);

	for(i=0; i< (m->rows)*(m->cols); i++){
		fprintf(fp, "%g ", m->array[i]);
	}

	fprintf(fp, "\n");

	return i;

}

/* Multiplica dos matrices */
matrix_t* matrix_multiply(matrix_t* m1, matrix_t* m2){

	size_t i, j, k;
	matrix_t *m_res = create_matrix(m1->rows,m2->cols);

    for (i = 0; i < m1->rows; i++) {

        for (j = 0; j < m2->cols; j++) {

        	/* con j recorro la fila y con i voy saltando de columnas */
            m_res->array[j + i*m2->cols] = 0;

            for (k = 0; k < m1->cols; k++) {/* recorro la fila de m1 y la columna de m2 */
                m_res->array[j + i*m2->cols] += m1->array[k + i*m1->cols] * m2->array[j + k*m2->cols];
            }
            /* m1->array[k + i*m1->cols] fijo la fila y recorro las columnas */
            /* m2->array[j + k*m2->cols] fijo la columna y recorro las filas */

        }

    }

    return m_res;
}