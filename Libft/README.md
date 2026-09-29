*This project has been created as part of the 42 curriculum by jacgomez.*

# Libft

**Common Core — 42 Madrid**

## Descripción

`libft` es la primera librería en C que se construye durante el Common Core de 42: una recopilación de reimplementaciones propias de funciones estándar de la `libc` (gestión de cadenas, memoria, conversión de tipos), un conjunto de funciones adicionales no presentes en la `libc` (`ft_split`, `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_itoa`, `ft_strmapi`, `ft_striteri`...) y un módulo completo de listas enlazadas (`t_list`), con sus operaciones de creación, inserción, recorrido, transformación y liberación de memoria.

El objetivo del proyecto es entender, a base de reimplementarlas desde cero, cómo funcionan realmente las funciones que normalmente se dan por hechas en C: gestión manual de memoria con `malloc`/`free`, punteros, recursividad, punteros a función y estructuras de datos enlazadas — todo ello cumpliendo estrictamente la Norma de 42 (máximo 5 funciones por archivo, 4 parámetros por función, 5 variables por función y 25 líneas por función).

## Instrucciones

### Compilación

```bash
make        # compila todos los .c y genera libft.a en la raíz del repositorio
make clean  # elimina los .o generados
make fclean # elimina los .o y libft.a
make re     # fclean + all
```

El `Makefile` compila cada `.c` con `-Wall -Wextra -Werror` usando `cc`, y empaqueta los `.o` en `libft.a` con `ar rcs` (no usa `libtool`).

### Uso en otro proyecto

```bash
cc -Wall -Wextra -Werror tu_programa.c libft.a -o tu_programa
```

Incluye `libft.h` en tus fuentes para tener acceso a los prototipos y al `typedef struct s_list` (`t_list`) usado por el módulo de listas.

```c
#include "libft.h"
```

## Descripción detallada de la librería

### Parte 1 — Funciones de la libc reimplementadas

Mismo prototipo y comportamiento que sus equivalentes de la `libc`, con el prefijo `ft_`.

| Función | Descripción |
|---|---|
| `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint` | Clasificación de caracteres (devuelven `1`/`0`) |
| `ft_toupper`, `ft_tolower` | Conversión de mayúsculas/minúsculas |
| `ft_strlen` | Longitud de una cadena |
| `ft_memset`, `ft_bzero` | Rellenado de un bloque de memoria |
| `ft_memcpy`, `ft_memmove` | Copia de memoria (con y sin solapamiento) |
| `ft_strlcpy`, `ft_strlcat` | Copia y concatenación de cadenas con límite de tamaño |
| `ft_strchr`, `ft_strrchr` | Búsqueda de un carácter desde el principio / desde el final |
| `ft_strncmp`, `ft_memcmp` | Comparación de cadenas / bloques de memoria |
| `ft_memchr` | Búsqueda de un byte en un bloque de memoria |
| `ft_strnstr` | Búsqueda de una subcadena acotada a `n` caracteres |
| `ft_atoi` | Conversión de cadena a entero |
| `ft_calloc` | `malloc` con memoria inicializada a cero y protección contra overflow |
| `ft_strdup` | Duplicado de una cadena en memoria reservada dinámicamente |

### Parte 2 — Funciones adicionales

| Función | Descripción |
|---|---|
| `ft_substr` | Extrae una subcadena de `s` a partir de `start` y de longitud máxima `len` |
| `ft_strjoin` | Concatena dos cadenas en una nueva reservada dinámicamente |
| `ft_strtrim` | Devuelve una copia de `s1` sin los caracteres de `set` al principio y al final |
| `ft_split` | Divide `s` en un array de cadenas (`char **`) según el delimitador `c` |
| `ft_itoa` | Convierte un entero (incluido `INT_MIN`) a su representación en cadena |
| `ft_strmapi` | Aplica `f` a cada carácter de `s` (con su índice) y devuelve una cadena nueva |
| `ft_striteri` | Aplica `f` a cada carácter de `s` in-place, pasando su dirección |
| `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd` | Escritura de un carácter / cadena / cadena+salto de línea / entero en un file descriptor dado |

### Parte 3 — Listas enlazadas (`t_list`)

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
```

| Función | Descripción |
|---|---|
| `ft_lstnew` | Crea un nuevo nodo con el contenido dado |
| `ft_lstadd_front` | Inserta un nodo al principio de la lista |
| `ft_lstadd_back` | Inserta un nodo al final de la lista |
| `ft_lstsize` | Cuenta el número de nodos de la lista |
| `ft_lstlast` | Devuelve el último nodo de la lista |
| `ft_lstdelone` | Libera el contenido (con `del`) y el nodo de un único elemento |
| `ft_lstclear` | Libera todos los nodos de la lista y pone el puntero a `NULL` |
| `ft_lstiter` | Aplica `f` al contenido de cada nodo, sin crear una lista nueva |
| `ft_lstmap` | Crea una lista nueva aplicando `f` al contenido de cada nodo de la original; libera lo ya construido con `del` si falla algún `malloc`, sin tocar la lista original |

## Recursos

- [man7.org — Linux man-pages](https://man7.org/linux/man-pages/) — referencia de comportamiento y prototipos exactos de las funciones de la `libc`.
- [42 Norm v4](https://github.com/42School/norminette) — reglas de estilo comprobadas con `norminette`.
- Apuntes propios y ejercicios de C del Common Core (piscina) sobre gestión de memoria y listas enlazadas.

### Uso de IA

Se ha usado Claude como apoyo puntual de **revisión y depuración**, nunca para generar la implementación desde cero:

- **Revisión de norma** del `.h` y de los `.c`: detección de una línea de prototipo que superaba las 80 columnas y de un error de indentación con tabs en la línea de continuación (`ft_lstmap`).
- **Revisión de lógica función a función** sobre la librería ya implementada por mí, que encontró y me permitió corregir:
  - Un bug real en `ft_strchr` que hacía que la función devolviera siempre `NULL` (la condición de éxito estaba dentro del propio `while` que la excluía).
  - Un bug en el camino de error de `ft_lstmap`, que en caso de fallo de `malloc` liberaba la lista original (`&lst`) en lugar de la lista nueva construida hasta ese punto (`&new`).
  - Confirmación de que el resto de funciones (`ft_split`, `ft_strtrim`, `ft_itoa`, `ft_substr`, `ft_strjoin`, funciones de memoria y de listas) estaban correctamente implementadas, compilando sin warnings con `-Wall -Wextra -Werror`.
- **Corrección del `Makefile`**: el `SRCS` estaba vacío y la regla de compilación enlazaba un ejecutable con `cc` en vez de generar `libft.a` con `ar rcs`.
- **Guía para verificar el build**: batería de comprobaciones manuales (`make`/`clean`/`fclean`/`re`, no relinkado innecesario, `ar -t`, `nm`, enlazado con un programa externo y `valgrind`) para confirmar que la librería compila y no tiene fugas de memoria.

Todo el código de `libft` ha sido escrito por mí; la IA se ha usado para revisar, señalar errores concretos y explicar por qué fallaban, no para redactar las funciones.
