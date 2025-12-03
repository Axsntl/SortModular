#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm> // Necesario para encontrar el máximo

// Función auxiliar para obtener el valor máximo de la lista
int obtenerMaximo(std::vector<int>& lista, int n) {
    int max = lista[0];
    for (int i = 1; i < n; i++)
        if (lista[i] > max)
            max = lista[i];
    return max;
}

// Hacemos un Counting Sort para cada dígito (exp = 1, 10, 100...)
void contarYOrdenar(std::vector<int>& lista, int n, int exponente) {
    std::vector<int> salida(n);
    int conteo[10] = {0};

    // Almacenar conteo de ocurrencias en 'conteo[]'
    for (int i = 0; i < n; i++)
        conteo[(lista[i] / exponente) % 10]++;

    // Cambiar conteo[i] para que contenga la posición real
    for (int i = 1; i < 10; i++)
        conteo[i] += conteo[i - 1];

    // Construir el array de salida
    for (int i = n - 1; i >= 0; i--) {
        salida[conteo[(lista[i] / exponente) % 10] - 1] = lista[i];
        conteo[(lista[i] / exponente) % 10]--;
    }

    // Copiar el array de salida al original
    for (int i = 0; i < n; i++)
        lista[i] = salida[i];
}

// --- LÓGICA DE RADIX SORT ---
void ordenarRadix(std::vector<int>& lista_numeros) {
    int n = lista_numeros.size();
    if (n == 0) return;

    // Buscar el número más grande para saber cuántos dígitos tiene
    int maximo = obtenerMaximo(lista_numeros, n);

    // Aplicar counting sort para cada dígito.
    // exponente es 10^i donde i es el número de dígito actual
    for (int exponente = 1; maximo / exponente > 0; exponente *= 10)
        contarYOrdenar(lista_numeros, n, exponente);
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

        ordenarRadix(lista_para_ordenar);

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