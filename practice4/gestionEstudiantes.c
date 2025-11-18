#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Definición de la estructura Estudiante
typedef struct {
    char nombre[50];
	int matricula;
	double calificaciones[4];
	double promedio;

} Estudiante;

// Prototipos de funciones
void capturarEstudiante(Estudiante *est);
void calcularPromedio(Estudiante *est);
void mostrarEstudiante(Estudiante est);
void mostrarMejorPromedio(Estudiante *grupo, int numEstudiantes);
void limpiarBuffer();
void liberarMemoria(Estudiante *grupo);

// Función principal
int main(){
    Estudiante *grupo= NULL;
	int numEstudiantes = 0;
	int n_nuevos;

	int opcion;

	printf("=== SISTEMA DE GESTIÓN ACADÉMICA ===\n");
	
	do{

		printf("1. Capturar datos de estudiantes\n");
		printf("2. Mostrar estudiante con mejor promedio\n");
		printf("3. Mostrar todos los estudiantes\n");
		printf("4. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);

		switch (opcion){
			
			case 1:

			printf("Cuantos estudiantes desea capturar? ");
			scanf("%d", &n_nuevos);

			limpiarBuffer(); // Limpiar el buffer de entrada
			
			int estudiantes_antes= numEstudiantes;
			numEstudiantes += n_nuevos;
			
			//NO hay estudiantes aún, calloc para asignar memoria
			if (estudiantes_antes == 0) {
                
                grupo = (Estudiante *)calloc(numEstudiantes, sizeof(Estudiante));
                
				if (grupo == NULL) {
                    printf("Error al asignar memoria con calloc.\n");
                    return 1;
                }

            } else {
                //Ya hay estudiantes, realloc para redimensionar memoria
                Estudiante *temp = (Estudiante *)realloc(grupo,numEstudiantes * sizeof(Estudiante));

                if (temp == NULL) {
                    printf("Error al redimensionar memoria con realloc.\n");
                    // no liberamos grupo porque puede seguir siendo válido
                    break;
                }
                grupo = temp;
                
			}

			// Capturar datos de los nuevos estudiantes
			for(int i = estudiantes_antes; i < numEstudiantes; i++){
                    printf("\n--- Capturando datos del estudiante %d ---\n", i + 1);
                    
                    /**
					 * Usando aritmética de punteros para pasar la dirección del estudiante actual
					 * (grupo + i) obtiene la dirección del i-ésimo estudiante en el arreglo dinámico
					 * luego se pasa esa dirección a las funciones capturarEstudiante y calcularPromedio
					 * 
					 */
                    capturarEstudiante(grupo + i);
                    calcularPromedio(grupo + i);
            }

			break;

			case 2:
				// Mostrar el estudiante con el mejor promedio
				mostrarMejorPromedio(grupo, numEstudiantes);
			
				break;

			case 3:
				
				printf("\n--- Lista de Estudiantes ---\n");

				// Verificar si hay estudiantes registrados
				if (numEstudiantes == 0) {
                    printf("No hay estudiantes registrados.\n");
            	}
				
				// Mostrar todos los estudiantes usando aritmética de punteros
				for (int i = 0; i < numEstudiantes; i++) {
					
					// Llamar a mostrarEstudiante desreferenciando el puntero
                    mostrarEstudiante(*(grupo + i));
				}
				break;
			
			case 4:
				
				liberarMemoria(grupo);// Liberar la memoria asignada dinámicamente
				
				printf("Saliendo del programa...\n");
				break;

		default:

			printf("Opcion invalida. Por favor, intente de nuevo.\n");
			break;
		}
		
	} while (opcion != 4);
	
	return 0;
}

// Función para capturar los datos de un estudiante
void capturarEstudiante(Estudiante *est) {

    printf("Nombre: ");
    fgets(est->nombre, sizeof(est->nombre), stdin);// Usar fgets para capturar cadenas con espacios
    est->nombre[strcspn(est->nombre, "\n")] = 0; // Eliminar el salto de línea si existe 
    
    // Capturar matrícula
	printf("Matricula: ");
	scanf("%d", &est->matricula);//
	limpiarBuffer(); // Limpiar el buffer de entrada
    
    // Capturar 4 calificaciones
	printf("Ingresa las 4 calificaciones:\n");
	for (int i = 0; i < 4;i++){
		printf("Calificaicon %d: ", i + 1);

		//scanf("%lf", &est->calificaciones[i]);
		scanf("%lf", (est->calificaciones+i));// Usando aritmética de punteros 
		
		limpiarBuffer(); // Limpiar el buffer de entrada
	}
	
}

// Función para calcular el promedio de un estudiante
void calcularPromedio(Estudiante *est) {

	double suma = 0.0;
	
	for (int i = 0; i < 4; i++){
		
		//suma += est->calificaciones[i];
		suma += *(est->calificaciones + i);// Usando aritmética de punteros
	}

	est->promedio = suma / 4.0;

}

// Función para mostrar la información de un estudiante
void mostrarEstudiante(Estudiante est) {
	printf("\n--- Informacion del Estudiante ---\n");
	//nombre del estudiante
	printf("Nombre: %s\n", est.nombre);

	//matricula del estudiante
	printf("Matricula: %d\n",est.matricula);
	limpiarBuffer();

	//calificaciones del estudiante
	printf("Calificaciones: \n");
	for (int i = 0; i < 4; i++){

		//printf("Calificacion %d: %.3f \n",(i+1), est.calificaciones[i]);
		printf("Calificacion %d: %.3f \n",(i+1), *(est.calificaciones + i));
	}

	//promedio del estudiante
	printf("\nPromedio: %.2lf\n", est.promedio);
}

// Función para mostrar el estudiante con el mejor promedio
void mostrarMejorPromedio(Estudiante *grupo, int numEstudiantes) {

	// Verificar si hay estudiantes registrados
	if (numEstudiantes==0){
		
		printf("No hay estudiantes registrados.\n");
		return;
	}

	int mejorIndex = 0;// Índice del estudiante con mejor promedio

	for (int i = 0; i < numEstudiantes; i++){

		// Comparar promedios usando aritmética de punteros
		if ((grupo+i)->promedio > (grupo+ mejorIndex)->promedio){
			
			mejorIndex = i;// Actualizar el índice del mejor promedio
		}
	}
	printf("\n--- Estudiante con Mejor Promedio ---\n");
	
	/**
	 * Desreferencia el puntero para pasar la estructura a la función mostrarEstudiante
	 * 	Usando aritmética de punteros
	 * 	(grupo + mejorIndex) obtiene la dirección del estudiante con mejor promedio
	 * 	*(grupo + mejorIndex) desreferencia esa dirección para obtener la estructura Estudiante
	 * 	que luego se pasa a la función mostrarEstudiante
	 * 	
	 */
	mostrarEstudiante(*(grupo + mejorIndex));
	
}

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) ;// Limpiar el buffer de entrada
}

// Función para liberar la memoria asignada dinámicamente
void liberarMemoria(Estudiante *grupo) {
	
	free(grupo);// Liberar la memoria asignada dinámicamente

}