#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// --- FUNCIONES AUXILIARES ---

// Función simple para intercambiar dos números en la memoria
#include <chrono>
#include <iomanip>

void intercambiar(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

int realizarParticion(std::vector<int>& lista_numeros, int indice_bajo, int indice_alto) {
    int valor_pivote = lista_numeros[indice_alto]; 
    int indice_del_menor = (indice_bajo - 1); 

    for (int j = indice_bajo; j <= indice_alto - 1; j++) {
        if (lista_numeros[j] < valor_pivote) {
            indice_del_menor++; 
            intercambiar(lista_numeros[indice_del_menor], lista_numeros[j]);
        }
    }
    intercambiar(lista_numeros[indice_del_menor + 1], lista_numeros[indice_alto]);
    return (indice_del_menor + 1);
}

void ordenarQuicksort(std::vector<int>& lista_numeros, int indice_bajo, int indice_alto) {
    if (indice_bajo < indice_alto) {
        int indice_particion = realizarParticion(lista_numeros, indice_bajo, indice_alto);
        ordenarQuicksort(lista_numeros, indice_bajo, indice_particion - 1);
        ordenarQuicksort(lista_numeros, indice_particion + 1, indice_alto);
    }
}

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
        
        ordenarQuicksort(lista_para_ordenar, 0, lista_para_ordenar.size() - 1);
        
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