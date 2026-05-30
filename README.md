  # Juego de Turnos por Consola
  
  ## ¿Por qué creamos este juego?
  
  Queremos que este juego sea una forma divertida de pasar el tiempo entre dos personas, sin necesidad de internet ni dispositivos externos. La idea es crear algo accesible y entretenido que se pueda jugar directamente desde la consola.
  
  ## Objetivos
  
  ### Objetivo General
  
  Crear un juego por turnos en lenguaje C++, jugable en consola, donde dos jugadores compiten tomando decisiones estratégicas hasta que uno de ellos sea derrotado o se rinda.
  
  ### Objetivos Específicos
  
  - Migrar el proyecto de C a C++ utilizando programación orientada a objetos.
  - Implementar clases con herencia, encapsulamiento y responsabilidades claras.
  - Agregar mecánicas avanzadas: golpe crítico, precisión, mejora de dados y modo muerte súbita.
  - Permitir la selección de personaje entre jugador normal y tanque.
  ## Integrantes y Roles
  
  | Nombre | Rol |
  | --- | --- |
  | Tomás Cea | Scrum Master |
  | Benja Gaete | Equipo |
  | Jorge Muñoz | Equipo |
  | Solange Azua | Product Owner |
  
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
  ### 6. Selección de personaje
  
  Al iniciar el juego, cada jugador elige entre dos tipos de personaje:
  - **Normal:** vida 100, ataque base 10, dado D6.
  - **Tanque:** vida 150, ataque base 10, dado D2 (más resistente pero menos ofensivo).
  
  ### 7. Golpe crítico
  Con una probabilidad configurable, el ataque puede ser un golpe crítico que multiplica el daño por 1.5 por defecto (valor configurable) al oponente.
  
  ### 8. Sistema de precisión
  Cada ataque tiene un 80% de probabilidad de impactar por defecto. Si el ataque falla, no se inflige daño y se consume el turno.
  
  ### 9. Mejora de dados
  Durante la partida, el jugador puede mejorar su tipo de dado (de D2 a D4, D6, D8, etc.), aumentando el daño potencial a costa de consumir el turno.
  
  ### 10. Modo muerte súbita
  Ronda final donde el primer jugador en fallar un ataque pierde automáticamente la partida.
  
  ### 11. Configuración y reglas
  Desde el menú principal se puede acceder a una sección de configuración para ajustar parámetros como rondas, precisión y golpe crítico, y una sección de reglas para consultar cómo funciona el juego.

  ### 12. Historial de partida (log)
Durante el juego, el jugador puede consultar el historial de acciones de la partida con la opción 5. Registra ataques, curaciones y rendiciones por ronda.
  
  ## Migración de C a C++
  
  En el Hito 2 se realizó una migración completa del código desde C a C++. Los principales cambios estructurales fueron:
  
  - **Organización en clases:** La lógica de jugadores y configuración, antes dispersa en funciones y structs, fue encapsulada en clases con responsabilidades claras.
  - **Separación de archivos:** Se adoptó la convención `.h`/`.cpp` para declaraciones e implementaciones.
  - **Uso de tipos C++:** Se reemplazaron arrays y strings de C por `std::string` y otros tipos de la biblioteca estándar.
  - **Herencia:** La clase `Tanque` hereda de `Jugador`, reutilizando lógica base y sobreescribiendo atributos específicos.
  
  ## Diseño de Clases
  
### `Jugador`
- **Responsabilidad:** Representar a un jugador genérico del juego.
- **Atributos (privados):** `vida`, `vida_t`, `atq_b`, `tipo_dado`, `turno`, `vida_c`
- **Métodos:** `ObtenerVida()`, `ModificarVida()`, `ObtenerTipoDado()`, `ModificarTipoDado()`, `ObtenerAtqB()`, `ModificarVidaC()`, `Modificar_Vida_c_pos()`
  
  ### `Tanque` *(hereda de Jugador)*
  - **Responsabilidad:** Personaje con mayor resistencia y dado reducido.
  - **Atributos propios:** `vida = 150`, `tipoDado = D2`
  - Hereda y reutiliza todos los métodos de `Jugador`.
  
### `Configuracion`
- **Responsabilidad:** Centralizar los parámetros globales de la partida.
- **Atributos (privados):** `rond_muerte_sub`, `modo_muerte_sub`, `golpe_critico`, `acierto`
- **Métodos:** `ObtenerRondMuerteSub()`, `ObtenerGolpeCritico()`, `ObtenerGolpeAcierto()`, `ModificarGolpeCritico()`, `ModificarGolpeAcierto()`, `ModificarEstadoMuerteSub()`
  
  ## Estado del Proyecto
  
  ### Hito 1
  
  | Tarea | Estado |
  | --- | --- |
  | Menú principal | [x] Hecho |
  | Ataque | [x] Hecho |
  | Curación | [x] Hecho |
  | Rendirse | [x] Hecho |
  | Barra de vida en consola | [x] Hecho  |
  
  ### Hito 2
  
  | Tarea | Estado |
  | --- | --- |
  | Opción de mejora de dados | ✅ Hecho |
  | Golpe crítico | ✅ Hecho |
  | Sistema de precisión | ✅ Hecho |
  | Sección de Configuración | ✅ Hecho |
  | Sección de Reglas | ✅ Hecho |
  | Selección de personaje (Normal/Tanque) | ✅ Hecho |
  | Modo muerte súbita | ✅ Hecho |
  | Traducción a C++ | ✅ Hecho |
  
  ### Hito 3 (próximos pasos)
  
  | Tarea | Estado |
  | --- | --- |
  | Agregar más tipos de personajes  | ⬜ Pendiente |
  | Implementar interfaz grafica con qt | ⬜ Pendiente |
  
  ## Compilación y Ejecución
  
  ### Requisitos
  - Sistema operativo Linux o macOS (o WSL en Windows)
  - Compilador G++ instalado (parte de GCC)
  
  ### Compilar
  ```bash
  g++ -std=c++23 src/main.cpp src/funciones.cpp -o juego
  ```
  
  ### Ejecutar
  ```bash
  ./juego
  ```
  
  ## Estructura del repositorio
  - `/src` → Carpeta donde se guarda todo el código fuente.
  - `IA_USAGE.md`→ Archivo con extensión de texto donde queda explícito que modelos de IA y Prompts se usaron para el proyecto.
  
  ## Dificultades Encontradas
  
- La migración se realizó como traducción directa del código C original, lo que permitió conservar gran parte de las funciones sin reescribirlas desde cero.
- Al encapsular los atributos de `Jugador` como privados, la barra de vida en consola dejó de poder modificarse carácter por carácter directamente, lo que requirió crear el método `Modificar_Vida_c_pos()` como solución.
- Se realizaron pequeñas modificaciones para usar `std::string` en lugar de arreglos de caracteres de C, adaptando el código al estilo C++.
- El sistema de log usa `sprintf` y `strcat` (funciones de C) ya que aún no se encontró una forma nativa en C++ que cumpla la misma función de manera simple. Se identificó como mejora pendiente.
  
 ## Ejemplos explicativos de Ejecución

**Caso: ataque normal exitoso**

    Turno de Jugador 1
    Ataque: éxito (precisión 80%) → daño: 15
    Vida de Jugador 2: 85/100 ████████░░

**Caso: golpe crítico**

    ¡GOLPE CRÍTICO! → daño: 30
    Vida de Jugador 2: 70/100 ███████░░░

**Caso: ataque fallido**

    Jugador 1 falló el ataque.
  
  ## Referencias
  - Funciones `stop_system` y `clean_buffer` adaptadas de: https://askubuntu.com/questions/980804/systempause-for-linux-in-gcc-c
