#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

// Función auxiliar estándar
void intercambiar(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

// Lógica de Selection Sort
void ordenarSeleccion(std::vector<int>& lista_numeros) {
    int n = lista_numeros.size();

    for (int i = 0; i < n - 1; i++) {
        // Asumimos que el primero es el menor
        int indice_minimo = i;
        
        // Buscamos si hay alguien menor en el resto de la lista
        for (int j = i + 1; j < n; j++) {
            if (lista_numeros[j] < lista_numeros[indice_minimo]) {
                indice_minimo = j;
            }
        }

        // Si encontramos uno menor, lo traemos al principio
        if (indice_minimo != i) {
            intercambiar(lista_numeros[i], lista_numeros[indice_minimo]);
        }
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

        ordenarSeleccion(lista_para_ordenar);

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