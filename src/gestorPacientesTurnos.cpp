#include<ios>
using namespace std;
#include "gestorPacientesTurnos.h"

void GestorPacientesTurnos::cargarPacientes() {

}

/* 1. Calcular el total de pacientes atendidos por hospital en un rango de fechas dado.
Recorrer los turnos del hospital dentro del rango de fechas.
Contar pacientes distintos (sin repetidos).
Si los turnos están ordenados por fecha puedo usar búsqueda binaria para la búsqueda.
*/

/*2. Detectar hospitales con sobrecarga 
-más de X ingresos en una semana o con ocupación 
-superior al 90% de su capacidad. 
????*/

/*3. Buscar todos los turnos de un paciente dado su DNI.  
buscar pasiente segun DNI
obtener id_paciente
recorrer los turnos, si el id_paciente coincide, agregar el turno a una lista 
*/ 

/* 4. Implementar una cola de prioridad (min-heap) para gestionar la lista de espera de 
pacientes según su nivel de prioridad y fecha de ingreso. 
Deben poder realizarse: 
-operaciones de inserción
-extracción del más prioritario  
-actualización de prioridad. 
Asumo que:
-insercion: insertaa ordenado por prioridad y fecha de ingreso
-extraccion: extrae el primero en la cola y corre el lugar de los siguientes
-actualizacion: buscar paciente por id, actualizar prioridad, reordenar la cola

*/

/*5. Dado un médico (por ID), listar todos sus turnos en orden cronológico. 
recorrer los turnos y si el id_medico coincide, agregar el turno a una lista 
ordenar lista por fecha*/ 