#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
// Para compilar: g++ algoritmos/burbuja.cpp -o algoritmos/burbuja
// --- FUNCIONES AUXILIARES (Estandarizadas) ---

// Usamos la misma función de ayuda que en Quicksort para mantener consistencia
void intercambiar(int& a, int& b) {
    int temporal = a;
    a = b;
    b = temporal;
}

// --- ALGORITMO PRINCIPAL ---

void ordenarBurbuja(std::vector<int>& lista_numeros) {
    int n = lista_numeros.size();
    bool hubo_intercambio;

    for (int i = 0; i < n - 1; i++) {
        hubo_intercambio = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            // Si el elemento actual es mayor al siguiente, intercambiamos
            if (lista_numeros[j] > lista_numeros[j + 1]) {
                intercambiar(lista_numeros[j], lista_numeros[j + 1]);
                hubo_intercambio = true;
            }
        }
        
        // Optimización: Si no hubo cambios en una pasada, ya está ordenado
        if (!hubo_intercambio) break;
    }
}

// --- BLOQUE DE COMPATIBILIDAD CON PYTHON ---
// (Este bloque ahora es idéntico al de Quicksort, solo cambia la llamada a la función)

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
        ordenarBurbuja(lista_para_ordenar);
    }

    // 3. SALIDA DE DATOS
    std::cout << "Resultado (Burbuja): ";
    for (size_t i = 0; i < lista_para_ordenar.size(); i++) {
        std::cout << lista_para_ordenar[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}