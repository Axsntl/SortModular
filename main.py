#El proyecto se divide en dos codigos por el momento, uno en python, y otro en c++
# Python servira para servir como interfaz para poder hacer mas facil el proceso de entender el menu
# Cpp para la eficiencia
# Aunque pss, se supone que igual asi son algunos paquetes en python
# Igual seria bueno ver como funcionan en conjunto
# Esto es para mi, luego lo quito o lo mejoro, se supone que hay que hacer entretenido el proceso
# aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
# Buscar luego lo de Modularización, Principios Solid y arquitectura distribuida
# Para poder hacer bien proyectos grandes
# Lo de modularización es precisamente de lo que va este proyecto
# El codigo se divide segun que hace cada parte
# Lo que es la division de responsabilidades
import subprocess #Esto es para que ejecute el executable de c++ para hacer el proceso normal
# No es el unico para hacer tal cosa existe pybind11, ctypes, sockets y webassembly
# WebAssembly solo seria necesario para hacer una aplicación web, tambien seria verlo para ver lo del backend, que obvio no se resume a javascrip
import os
import platform

def limpiar_consola():
    """Limpia la pantalla dependiendo del sistema operativo"""
    sistema = platform.system()
    if sistema == "Windows":
        os.system('cls')
    else:
        os.system('clear')

def ejecutar_algoritmo_cpp(nombre_algoritmo, lista_numeros):
    """
    Llama al ejecutable de C++ y le pasa los números
    """
    # Convertimos la lista [5, 3, 1] a una cadena "5,3,1" por ejemplo
    cadena_argumentos = ",".join(str(num) for num in lista_numeros)
    
    # Definimos la ruta del ejecutable (asumiendo Windows .exe, ajustar para Linux/Mac en el improbable caso de que sea necesario por que nadie de mi grupo lo tiene, a menos que de la nada salga un profe con una mac que lo quiera probar, asumiendo que sea probable igual que eso ocurra)
    ruta_ejecutable = os.path.join("algoritmos", f"{nombre_algoritmo}.exe")
    
    # Aqui se verifica si existe el compilado
    if not os.path.exists(ruta_ejecutable):
        print(f"ERROR: No se encontró el archivo {ruta_ejecutable}")
        print("Por favor, asegúrate de compilar el código C++ primero.")
        return

    print(f"\n--- Ejecutando {nombre_algoritmo} en C++ ---")
    
    try:
        # Se llama al proceso externo
        subprocess.run([ruta_ejecutable, cadena_argumentos], check=True)
    except Exception as error:
        print(f"Ocurrió un error al ejecutar el algoritmo: {error}")

def mostrar_menu():
    while True:
        # limpiar_consola() # Solo se quita el comentario a la linea de codigo para limpiar la consola en cada proceso
        print("\n" + "="*30)
        print("VISUALIZADOR DE ORDENAMIENTO")
        print("="*30)
        print("1. Configurar lista de números")
        print("2. Ordenar usando Burbuja ")
        print("3. Ordenar usando Quicksort ") # (Nuevo) Para indicar si lo es, no se si sea necesario
        print("4. Salir")
        print("="*30)
        
        opcion = input("\nSelecciona una opción: ")
        
        return opcion

# :::--- BLOQUE PRINCIPAL ---::: #
if __name__ == "__main__":
    
    lista_actual = []
    
    while True:
        opcion_usuario = mostrar_menu()
        
        if opcion_usuario == '1':
            entrada = input("\nIngresa los números separados por coma (ej: 5,10,2,8): ")
            try:
                # Convertimos la entrada a una lista de enteros
                lista_actual = [int(x.strip()) for x in entrada.split(',')]
                print(f"Lista guardada: {lista_actual}")
            except ValueError:
                print("Error: Asegúrate de ingresar solo números y comas.")
                
        elif opcion_usuario == '2':
            if not lista_actual:
                print("\n¡Primero debes configurar una lista de números (Opción 1)!")
            else:
                ejecutar_algoritmo_cpp("burbuja", lista_actual)

        elif opcion_usuario == '3': 
            if lista_actual: 
                
                ejecutar_algoritmo_cpp("quicksort", lista_actual)
            else: 
                print("¡Configura la lista primero!")
                
        elif opcion_usuario == '4':
            print("\nSaliendo del programa...")
            break
            
        else:
            print("\nOpción no válida, intenta de nuevo.")