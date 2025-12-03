#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

// Función para mezclar dos sub-listas ordenadas
void mezclar(std::vector<int>& lista, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    // Vectores temporales
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = lista[izquierda + i];
    for (int j = 0; j < n2; j++)
        R[j] = lista[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            lista[k] = L[i];
            i++;
        } else {
            lista[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes si quedan
    while (i < n1) {
        lista[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        lista[k] = R[j];
        j++;
        k++;
    }
}

// Función principal recursiva
void ordenarMergeSort(std::vector<int>& lista, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        ordenarMergeSort(lista, izquierda, medio);
        ordenarMergeSort(lista, medio + 1, derecha);

        mezclar(lista, izquierda, medio, derecha);
    }
}

// --- MAIN ESTÁNDAR (PLANTILLA) ---
int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    std::string cadena_entrada = argv[1]; 
    std::vector<int> lista_para_ordenar;
    std::stringstream ss(cadena_entrada);
    std::string segmento;

    while (std::getline(ss, segmento, ',')) {
        lista_para_ordenar.push_back(std::stoi(segmento));
    }

    if (!lista_para_ordenar.empty()) {
        auto tiempo_inicio = std::chrono::high_resolution_clock::now();

        // Llamada inicial (desde índice 0 hasta el final)
        ordenarMergeSort(lista_para_ordenar, 0, lista_para_ordenar.size() - 1);

        auto tiempo_fin = std::chrono::high_resolution_clock::now();

        // CÁLCULOS PRECISOS
        std::chrono::duration<double, std::nano> duracion_nano = tiempo_fin - tiempo_inicio;
        double nanosegundos = duracion_nano.count();
        double microsegundos = nanosegundos / 1000.0;
        double segundos = nanosegundos / 1000000000.0;

        std::cout << "Resultado: ";
        for (size_t i = 0; i < lista_para_ordenar.size(); i++) {
            std::cout << lista_para_ordenar[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "\n--- ESTADISTICAS DE TIEMPO ---" << std::endl;
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Nanosegundos:  " << nanosegundos << " ns" << std::endl;
        std::cout << "Microsegundos: " << microsegundos << " us" << std::endl;
        std::cout << std::setprecision(9);
        std::cout << "Segundos:      " << segundos << " s" << std::endl;
    }
    return 0;
}