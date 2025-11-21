#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// --- FUNCIONES AUXILIARES ---

// Función simple para intercambiar dos números en la memoria
void intercambiar(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

// Función que coloca el pivote en su lugar correcto
// Todos los menores al pivote van a la izquierda, los mayores a la derecha
int realizarParticion(std::vector<int>& lista_numeros, int indice_bajo, int indice_alto) {
    // Tomamos el último elemento como referencia (pivote)
    int valor_pivote = lista_numeros[indice_alto]; 
    int indice_del_menor = (indice_bajo - 1); 

    for (int j = indice_bajo; j <= indice_alto - 1; j++) {
        // Si el número actual es menor que el pivote
        if (lista_numeros[j] < valor_pivote) {
            indice_del_menor++; 
            intercambiar(lista_numeros[indice_del_menor], lista_numeros[j]);
        }
    }
    // Colocamos el pivote justo después del último número menor encontrado
    intercambiar(lista_numeros[indice_del_menor + 1], lista_numeros[indice_alto]);
    return (indice_del_menor + 1);
}

// --- ALGORITMO PRINCIPAL ---

void ordenarQuicksort(std::vector<int>& lista_numeros, int indice_bajo, int indice_alto) {
    if (indice_bajo < indice_alto) {
        // Obtenemos el índice donde el pivote quedó fijo
        int indice_particion = realizarParticion(lista_numeros, indice_bajo, indice_alto);

        // Ordenamos recursivamente la sub-lista izquierda y la derecha
        ordenarQuicksort(lista_numeros, indice_bajo, indice_particion - 1);
        ordenarQuicksort(lista_numeros, indice_particion + 1, indice_alto);
    }
}

// --- BLOQUE DE COMPATIBILIDAD CON PYTHON ---

int main(int argc, char* argv[]) {
    // Verificamos seguridad: Si no llegan argumentos, cerramos para no fallar
    if (argc < 2) {
        return 1;
    }

    // 1. LECTURA DE DATOS (Idéntica a burbuja.cpp)
    std::string cadena_entrada = argv[1]; 
    std::vector<int> lista_para_ordenar;
    std::stringstream ss(cadena_entrada);
    std::string segmento;

    while (std::getline(ss, segmento, ',')) {
        lista_para_ordenar.push_back(std::stoi(segmento));
    }

    // 2. EJECUCIÓN DEL ALGORITMO
    // Importante: Quicksort necesita saber el índice inicial (0) y el final (tamaño - 1)
    if (!lista_para_ordenar.empty()) {
        ordenarQuicksort(lista_para_ordenar, 0, lista_para_ordenar.size() - 1);
    }

    // 3. SALIDA DE DATOS (Idéntica a burbuja.cpp para que se vea igual)
    std::cout << "Resultado (QuickSort): ";
    for (size_t i = 0; i < lista_para_ordenar.size(); i++) {
        std::cout << lista_para_ordenar[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}