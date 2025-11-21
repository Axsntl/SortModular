#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// --- ALGORITMO PRINCIPAL ---

void ordenarInsercion(std::vector<int>& lista_numeros) {
    int n = lista_numeros.size();

    // Comenzamos desde el segundo elemento (índice 1)
    for (int i = 1; i < n; i++) {
        int valor_actual = lista_numeros[i];
        int indice_anterior = i - 1;

        // Mover los elementos del segmento ordenado [0...i-1]
        // que sean mayores al valor_actual, a una posición adelante
        while (indice_anterior >= 0 && lista_numeros[indice_anterior] > valor_actual) {
            lista_numeros[indice_anterior + 1] = lista_numeros[indice_anterior];
            indice_anterior = indice_anterior - 1;
        }
        
        // Colocamos el valor actual en su posición correcta
        lista_numeros[indice_anterior + 1] = valor_actual;
    }
}

// --- BLOQUE DE COMPATIBILIDAD CON PYTHON (ESTÁNDAR) ---

int main(int argc, char* argv[]) {
    // Verificamos seguridad
    if (argc < 2) {
        return 1;
    }

    // 1. LECTURA DE DATOS
    std::string cadena_entrada = argv[1]; 
    std::vector<int> lista_para_ordenar;
    std::stringstream ss(cadena_entrada);
    std::string segmento;

    while (std::getline(ss, segmento, ',')) {
        lista_para_ordenar.push_back(std::stoi(segmento));
    }

    // 2. EJECUCIÓN DEL ALGORITMO
    if (!lista_para_ordenar.empty()) {
        ordenarInsercion(lista_para_ordenar);
    }

    // 3. SALIDA DE DATOS
    std::cout << "Resultado (Insercion): ";
    for (size_t i = 0; i < lista_para_ordenar.size(); i++) {
        std::cout << lista_para_ordenar[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}