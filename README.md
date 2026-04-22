# Juego de Turnos por Consola

## ¿Por qué creamos este juego?

Queremos que este juego sea una forma divertida de pasar el tiempo entre dos personas, sin necesidad de internet ni dispositivos externos. La idea es crear algo accesible y entretenido que se pueda jugar directamente desde la consola.

## Objetivos

### Objetivo General

Crear un juego por turnos en lenguaje C, jugable en consola, donde dos jugadores compiten tomando decisiones estratégicas hasta que uno de ellos sea derrotado o se rinda.

### Objetivos Específicos

- Implementar un sistema de turnos alternados entre dos jugadores.
- Desarrollar mecánicas de combate basadas en dados aleatorios.
- Agregar opciones de curación para añadir decisiones estratégicas al juego.
- Permitir que los jugadores se rindan en cualquier momento.
- Implementar un menú principal con opciones de juego, reglas y configuración.

## Integrantes y Roles

| Nombre | Rol |
| --- | --- |
| Tomás Cea |  |
| Benja Gaete |  |
| Jorge Muñoz |  |
| Solange Azua |  |

## Funcionalidades Implementadas

### 1. Menú principal
El programa inicia con un menú que ofrece cuatro opciones: Jugar, Configuración, Reglas y Salir. El usuario navega usando el teclado.

### 2. Sistema de turnos
El juego alterna el turno entre el Jugador 1 y el Jugador 2. En cada turno, el jugador activo elige una acción. Los stats iniciales de cada jugador son vida 100, ataque base 10 y tipo de dado D6 (valores del 1 al 6).

### 3. Atacar
El jugador lanza un dado con valor aleatorio entre 1 y 6. El daño se calcula como (ataque_base / 2) * valor_dado y se resta a la vida del oponente.

### 4. Curar
El jugador lanza un dado. La curación se calcula como ((100 - vida_actual) / 14) * valor_dado. Si el jugador ya tiene 100 de vida, el sistema avisa que no es necesario curar. Usar curación consume el turno.

### 5. Rendirse
El jugador puede rendirse en cualquier momento. El sistema pide confirmación antes de terminar. Si confirma, el oponente es declarado ganador.

## Estado del Proyecto

### Hito 1

| Tarea | Estado |
| --- | --- |
| Menú principal | [x] Hecho |
| Ataque | [x] Hecho |
| Curación | [x] Hecho |
| Rendirse | [x] Hecho |
| Barra de vida en consola | [x] Pendiente |

### Hito 2 (próximos pasos)

| Tarea | Estado |
| --- | --- |
| Opción de mejora | ⬜ Pendiente |
| Golpe crítico | ⬜ Pendiente |
| Sección de Configuración | ⬜ Pendiente |
| Sección de Reglas | ⬜ Pendiente |
| Victoria automática al llegar a 0 de vida | ⬜ Pendiente |
| Traducción a C++ | ⬜ Pendiente |

## Compilación y Ejecución

### Requisitos
- Sistema operativo Linux o macOS (o WSL en Windows)
- Compilador GCC instalado

### Compilar
```bash
gcc src/main.c src/funciones.c -o juego
```

### Ejecutar
```bash
./juego
```

## Estructura del repositorio
- `/src` → Carpeta donde se guarda todo el código fuente.
- `IA_USAGE.md`→ Archivo con extensión de texto donde queda explícito que modelos de IA y Prompts se usaron para el proyecto.

## Referencias
- Funciones `stop_system` y `clean_buffer` adaptadas de: https://askubuntu.com/questions/980804/systempause-for-linux-in-gcc-c
