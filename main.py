import subprocess
import os
import platform
import random
import re
import sys
def limpiar_consola():
    sistema = platform.system()
    if sistema == "Windows":
        os.system('cls')
    else:
        os.system('clear')

def resolver_ruta_recurso(ruta_relativa):
    try:
        ruta_base=sys._MEIPASS
    except Exception:
        ruta_base=os.path.abspath(".")
    return os.path.join(ruta_base,ruta_relativa)
#-------------------------------------------------------------------------------------------------------------
# Funciones para ejecutar algoritmos y obtener tiempos
#-------------------------------------------------------------------------------------------------------------
def ejecutar_algoritmo_cpp(nombre_algoritmo, lista_numeros):
    cadena_argumentos = ",".join(str(num) for num in lista_numeros)
    
    sistema = platform.system()
    nombre_ejecutable = f"{nombre_algoritmo}.exe" if sistema == "Windows" else nombre_algoritmo
    #ruta_ejecutable = os.path.join("algoritmos", nombre_ejecutable)
    ruta_ejecutable = resolver_ruta_recurso(os.path.join("algoritmos",nombre_ejecutable))
    
    if not os.path.exists(ruta_ejecutable):
        print(f"\n[ERROR] No se encontró: {ruta_ejecutable}")
        print(f" -> Compila con: g++ algoritmos/{nombre_algoritmo}.cpp -o algoritmos/{nombre_algoritmo}")
        return

    print(f"\n--- Ejecutando {nombre_algoritmo} en C++ ---")
    
    try:
        subprocess.run([ruta_ejecutable, cadena_argumentos], check=True)
    except Exception as e:
        print(f"Error: {e}")

def obtener_tiempo_ejecucion(nombre_algoritmo, lista_numeros):
    """
    Ejecuta el algoritmo, captura su salida oculta y extrae el tiempo en nanosegundos.
    """
    cadena_argumentos = ",".join(str(num) for num in lista_numeros)
    
    sistema = platform.system()
    nombre_ejecutable = f"{nombre_algoritmo}.exe" if sistema == "Windows" else nombre_algoritmo
    ruta_ejecutable = os.path.join("algoritmos", nombre_ejecutable)
    
    if not os.path.exists(ruta_ejecutable):
        return None

    try:
        # capture_output=True hace que NO se imprima en consola, Python lo guarda en memoria
        proceso = subprocess.run(
            [ruta_ejecutable, cadena_argumentos], 
            capture_output=True, 
            text=True, 
            check=True
        )
        
        # Buscamos la línea que dice "Nanosegundos:  XXXX.XX ns"
        # Usamos Expresiones Regulares para encontrar el número
        salida = proceso.stdout
        patron = r"Nanosegundos:\s+([0-9\.]+)"
        resultado = re.search(patron, salida)
        
        if resultado:
            return float(resultado.group(1)) # Retornamos el número como float
        else:
            return -1 # Error al leer
            
    except Exception:
        return -1
    
def modo_competencia(lista_numeros):
    if not lista_numeros:
        print("\n[!] Error: Necesitas una lista para competir.")
        return

    print("\n" + "█"*50)
    print("      INICIANDO MODO COMPETENCIA      ")
    print("█"*50)
    print(f"Procesando {len(lista_numeros)} números...\n")

    algoritmos = ["burbuja", "insercion", "quicksort","mergesort","radix","selection","shellsort"]
    resultados = {}

    # 1. EJECUCIÓN SECUENCIAL
    for alg in algoritmos:
        print(f" -> Ejecutando {alg.upper()}...", end="\r") # \r permite sobreescribir la linea
        tiempo = obtener_tiempo_ejecucion(alg, lista_numeros)
        
        if tiempo is not None and tiempo != -1:
            resultados[alg] = tiempo
            print(f" -> {alg.upper()}: Completado ({tiempo:.2f} ns)      ")
        else:
            print(f" -> {alg.upper()}: FALLÓ (No compilado o error)")

    if not resultados:
        return

    # 2. CÁLCULOS
    # Encontramos el tiempo máximo (el más lento) para usarlo de base
    tiempo_peor = max(resultados.values())
    tiempo_mejor = min(resultados.values())
    
    # Ordenamos los resultados del más rápido al más lento
    ranking = sorted(resultados.items(), key=lambda x: x[1])

    # 3. MOSTRAR TABLA
    print("\n" + "-"*65)
    print(f"{'POS':<5} {'ALGORITMO':<15} {'TIEMPO (ns)':<20} {'RENDIMIENTO':<20}")
    print("-"*65)

    for i, (nombre, tiempo) in enumerate(ranking, 1):
        # Calculamos porcentaje "más rápido que el peor"
        if tiempo == tiempo_peor:
            etiqueta = "LENTO (Base)"
            barra = "🟥"
        else:
            porcentaje_mejora = ((tiempo_peor - tiempo) / tiempo_peor) * 100
            etiqueta = f"{porcentaje_mejora:.2f}% más rápido"
            if tiempo == tiempo_mejor:
                barra = "🟩 🏆"
            else:
                barra = "🟨"

        print(f"{i:<5} {nombre.upper():<15} {tiempo:<20.4f} {barra} {etiqueta}")
    print("-"*65 + "\n")
#-------------------------------------------------------------------------------------------------------------
#   Función 
def generar_lista_aleatoria():
    """Genera una lista grande para pruebas de estrés"""
    print("\n--- GENERADOR ALEATORIO ---")
    try:
        cantidad = int(input("¿Cuántos números quieres generar? (Recomendado que el digito ronde 5000, 6000<x da error): "))
        # Generamos números entre 1 y 10000
        lista_nueva = [random.randint(1, 10000) for _ in range(cantidad)]
        print(f"¡Lista de {cantidad} números generada exitosamente!")
        return lista_nueva
    except ValueError:
        print("Error: Debes ingresar un número entero.")
        return []

def mostrar_menu():
    print("\n" + "="*40)
    print("   SISTEMA GESTOR DE ORDENAMIENTO")
    print("="*40)
    print(" [1] Definir lista manual")
    print(" [2] Generar lista ALEATORIA")
    print(" [3] Ordenar con BURBUJA")
    print(" [4] Ordenar con QUICKSORT")
    print(" [5] Ordenar con INSERCION")
    print(" [6] Ordenar con SELECTION SORT")
    print(" [7] Ordenar con MERGESORT")
    print(" [8] Ordenar con SHELLSORT")
    print(" [9] Ordenar con RADIX")
    print(" [10] MODO COMPETENCIA (Comparar todos)")
    print(" [11] Salir")
    print("-" * 40)
    
    return input("Selecciona una opción (1-11): ")

# --- INICIO ---
if __name__ == "__main__":
    limpiar_consola()
    lista_actual = []
    
    while True:
        opcion = mostrar_menu()
        
        if opcion == '1':
            entrada = input("\nEscribe los números (Ej: 9,1,5): ")
            try:
                lista_actual = [int(x.strip()) for x in entrada.split(',')]
                print(f" -> Lista guardada: {lista_actual}")
            except ValueError:
                print("\n[!] Error: Solo números enteros.")
        
        elif opcion == '2':

            nueva_lista = generar_lista_aleatoria()
            if nueva_lista:
                lista_actual = nueva_lista

        elif opcion == '3':
            if lista_actual: ejecutar_algoritmo_cpp("burbuja", lista_actual)
            else: print("\n[!] Lista vacía.")

        elif opcion == '4':
            if lista_actual: ejecutar_algoritmo_cpp("quicksort", lista_actual)
            else: print("\n[!] Lista vacía.")
            
        elif opcion == '5':
            if lista_actual: ejecutar_algoritmo_cpp("insercion", lista_actual)
            else: print("\n[!] Lista vacía.")
            
        elif opcion == '6':
            if lista_actual: ejecutar_algoritmo_cpp("seleccion", lista_actual)
            else: print("\n[!] Lista vacía.")
            
        elif opcion == '7':
            if lista_actual: ejecutar_algoritmo_cpp("mergesort", lista_actual)
            else: print("\n[!] Lista vacía.")

        elif opcion == '8':
            if lista_actual: ejecutar_algoritmo_cpp("shellsort", lista_actual)
            else: print("\n[!] Lista vacía.")
            
        elif opcion == '9':
            if lista_actual: ejecutar_algoritmo_cpp("radix", lista_actual)
            else: print("\n[!] Lista vacía.")

        elif opcion == '10':
            modo_competencia(lista_actual)
                
        elif opcion == '11':
            print("\nCerrando sistema...")
            break
        else:
            print("\nOpción inválida.")