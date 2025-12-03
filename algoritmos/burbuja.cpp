#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

// --- FUNCIONES AUXILIARES ---
void intercambiar(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

// --- Algoritmo Principal ---
void ordenarBurbuja(std::vector<int>& lista_numeros) {
    int n = lista_numeros.size();
    bool hubo_intercambio;
    for (int i = 0; i < n - 1; i++) {
        hubo_intercambio = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (lista_numeros[j] > lista_numeros[j + 1]) {
                intercambiar(lista_numeros[j], lista_numeros[j + 1]);
                hubo_intercambio = true;
            }
        }
        if (!hubo_intercambio) break;
    }
}
// Compatibilidad en Python
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
        // 1. INICIO RELOJ
        auto tiempo_inicio = std::chrono::high_resolution_clock::now();

        ordenarBurbuja(lista_para_ordenar);

        // 2. FIN RELOJ
        auto tiempo_fin = std::chrono::high_resolution_clock::now();

        // 3. CÁLCULOS
        // Obtenemos la duración en nanosegundos como número decimal (double) para no perder precisión
        std::chrono::duration<double, std::nano> duracion_nano = tiempo_fin - tiempo_inicio;
        
        double nanosegundos = duracion_nano.count();
        double microsegundos = nanosegundos / 1000.0;
        double segundos = nanosegundos / 1000000000.0;

        // IMPRESIÓN DE RESULTADOS
        std::cout << "Resultado: ";
        for (size_t i = 0; i < lista_para_ordenar.size(); i++) {
            std::cout << lista_para_ordenar[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "\n--- ESTADISTICAS DE TIEMPO ---" << std::endl;
        std::cout << std::fixed << std::setprecision(4); // Fija 4 decimales
        std::cout << "Nanosegundos:  " << nanosegundos << " ns" << std::endl;
        std::cout << "Microsegundos: " << microsegundos << " us" << std::endl;
        std::cout << std::setprecision(9); // Más precisión para segundos
        std::cout << "Segundos:      " << segundos << " s" << std::endl;
    }
    return 0;
}