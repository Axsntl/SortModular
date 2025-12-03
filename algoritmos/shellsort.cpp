#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

// --- LÓGICA DE SHELL SORT ---
void ordenarShell(std::vector<int>& lista_numeros) {
    int n = lista_numeros.size();

    // Empezamos con una brecha grande y la vamos reduciendo a la mitad
    for (int brecha = n / 2; brecha > 0; brecha /= 2) {
        
        // Hacemos un "Insertion Sort" pero con saltos de tamaño 'brecha'
        for (int i = brecha; i < n; i += 1) {
            int temporal = lista_numeros[i];
            int j;
            
            for (j = i; j >= brecha && lista_numeros[j - brecha] > temporal; j -= brecha) {
                lista_numeros[j] = lista_numeros[j - brecha];
            }
            lista_numeros[j] = temporal;
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

        ordenarShell(lista_para_ordenar);

        auto tiempo_fin = std::chrono::high_resolution_clock::now();

        // CÁLCULOS
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