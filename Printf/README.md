*Este proyecto ha sido creado como parte del currículo de 42 por jacgomez.*

# ft_printf

**Common Core — 42 Madrid**

## Descripción

`ft_printf` es una reimplementación propia de la función `printf` de la `libc`: una función variádica que escribe en la salida estándar un texto con formato y devuelve el número de caracteres impresos. El resultado (tanto lo que se escribe como el valor de retorno) se compara con el del `printf` real.

El proyecto se empaqueta como una librería estática, `libftprintf.a`, que incluye también mi `libft`, de modo que quien la enlace dispone de ambas.

Conversiones soportadas:

| Conversión | Qué imprime | Tipo que se lee con `va_arg` |
|---|---|---|
| `%c` | Un carácter | `int` (un `char` se promociona a `int` en una función variádica) |
| `%s` | Una cadena. Si es `NULL`, imprime `(null)` | `char *` |
| `%p` | Un puntero en hexadecimal, con prefijo `0x`. Si es `NULL`, imprime `(nil)` | `void *` |
| `%d` / `%i` | Un entero decimal con signo | `int` |
| `%u` | Un entero decimal sin signo | `unsigned int` |
| `%x` | Un entero sin signo en hexadecimal, minúsculas | `unsigned int` |
| `%X` | Un entero sin signo en hexadecimal, mayúsculas | `unsigned int` |
| `%%` | Un símbolo `%` literal (no consume ningún argumento) | — |

Todo el código cumple la Norma de 42: máximo 5 funciones por archivo, 4 parámetros por función, 5 variables por función y 25 líneas por función.

## Instrucciones

### Compilación

```bash
make        # compila libft y genera libftprintf.a en la raíz del repositorio
make clean  # elimina los .o (también los de libft)
make fclean # elimina los .o y las librerías (libftprintf.a y libft.a)
make re     # fclean + all
```

El `Makefile` compila primero `libft` con su propio `Makefile` (en `libft/`), copia `libft.a` como base de `libftprintf.a` y le añade con `ar rcs` los objetos de `ft_printf` (no se usa `libtool`). Todo se compila con `cc -Wall -Wextra -Werror`, y no hay relink si no ha cambiado nada.

> Si se modifica algún fichero de `libft`, conviene ejecutar `make re`, ya que el `Makefile` raíz solo comprueba si existe `libft.a`.

### Uso en otro proyecto

```bash
cc -Wall -Wextra -Werror tu_programa.c libftprintf.a -o tu_programa
```

```c
#include "ft_printf.h"

int	main(void)
{
	int	n;

	n = ft_printf("Hola %s, tienes %d años (0x%x)\n", "Ana", 30, 255);
	ft_printf("Se han impreso %d caracteres\n", n);
	return (0);
}
```

### Estructura de ficheros

| Fichero | Contenido |
|---|---|
| `ft_printf.h` | Prototipos de todas las funciones |
| `ft_printf.c` | `ft_printf` (recorre el formato) y `manejar_conversion` (reparte cada conversión a su función) |
| `ft_print_csuid.c` | `ft_print_char`, `ft_print_string`, `ft_print_uint` y `ft_print_int` (`%c`, `%s`, `%u`, `%d`, `%i`) |
| `ft_print_hexp.c` | `ft_print_hexp` y `ft_print_ptr` (`%x`, `%X`, `%p`) |
| `libft/` | Mi `libft`, con su propio `Makefile` (solo se usa `ft_strlen`) |

## Algoritmo y decisiones de diseño

### Recorrido del formato y reparto

`ft_printf` recorre la cadena de formato una sola vez, de izquierda a derecha. Si el carácter actual no es `%`, se escribe tal cual con `write`. Si lo es, se avanza una posición y se llama a `manejar_conversion` con la letra de la conversión. Esta función, mediante una cadena de `if`/`else if` (la Norma prohíbe `switch`), llama a la función correspondiente a cada tipo.

### Lista de argumentos: `va_list *`

`ft_printf` obtiene los argumentos con `va_start`, `va_arg` y `va_end`. A `manejar_conversion` se le pasa un **puntero** a la `va_list` (`va_list *`), no una copia, de manera que cada `va_arg(*args, tipo)` avanza la lista real y la siguiente conversión lee el argumento que le corresponde. Cada conversión ejecuta `va_arg` exactamente una vez, con el tipo que corresponde (por eso `%x` lee `unsigned int` y no `int`: así `-1` se imprime como `ffffffff`).

### Valor de retorno: cada función devuelve lo que escribe

Todas las funciones de impresión devuelven el número de caracteres que han escrito, y `ft_printf` los va sumando en un contador. Así no hace falta calcular longitudes aparte ni llevar estado global: el retorno de `ft_printf` sale directamente de la suma de lo que se ha impreso.

### Números: recursión en lugar de `malloc`

Para imprimir un número en cualquier base se usa una recursión: si el número es mayor o igual que la base, primero se imprime el número dividido entre la base (las cifras de la izquierda) y después la última cifra (`n % base`).

```
ft_print_uint(42)
  └─ ft_print_uint(4)  → imprime '4'  (devuelve 1)
  imprime '2' (suma 1)               → devuelve 2
```

Se eligió esta solución, frente a construir una cadena con un `ft_itoa` o un buffer propio, por estas razones:

- **No usa memoria dinámica:** no hay `malloc`, por lo que no puede haber fugas ni un camino de error por fallo de asignación.
- **Un mismo esquema para todo:** `%u`, `%x`, `%X` y `%p` comparten la lógica (solo cambia la base y los dígitos). `ft_itoa` solo sirve para enteros con signo.
- **Cuenta los caracteres de forma natural**, porque cada llamada devuelve las cifras que ha impreso ella más las de las llamadas internas.
- **La profundidad de recursión está acotada** (como mucho 20 llamadas para un `unsigned long` en decimal), así que no hay riesgo de desbordar la pila.

El inconveniente es que se hace una llamada a `write` por carácter, más lenta que acumular en un buffer, pero el enunciado no pide gestionar un buffer y se prefiere la simplicidad y la ausencia de memoria dinámica.

### Tipos elegidos

- **`unsigned long` como tipo común** de `ft_print_uint` y `ft_print_hexp`. Cabe cualquier `unsigned int` (para `%u`, `%x`, `%X`) y cualquier puntero (para `%p`), de modo que la misma función sirve para todos.
- **`INT_MIN`:** para un entero negativo se escribe `-` y luego se imprime su valor absoluto. Calcular `-n` sobre un `int` desborda con `INT_MIN` (`2147483648` no cabe en un `int`), así que la conversión a `long` se hace **antes** de cambiar el signo. Con esto no hace falta un caso especial.
- **`%d` y `%i` comparten función:** al imprimir son idénticos (la diferencia entre ambos solo existe en `scanf`).

### Por qué no hay una estructura de datos

La parte obligatoria no necesita almacenar nada entre una conversión y la siguiente: no hay flags, anchura ni precisión que recordar. Basta con la `va_list` y el contador de caracteres. Una estructura que guarde las opciones de cada conversión tendría sentido para una parte con flags (`-0.# +`, anchura y precisión), pero no para esta.

### Casos límite (comportamiento igual que el `printf` de Linux/glibc)

| Caso | Resultado |
|---|---|
| `%s` con `NULL` | `(null)` (6 caracteres) |
| `%p` con `NULL` | `(nil)` (5 caracteres) |
| `%c` con `0` | Escribe un byte nulo y cuenta 1 |
| `%d` con `INT_MIN` / `INT_MAX` | `-2147483648` / `2147483647` |
| `%u`, `%x`, `%X` con un negativo | Se interpreta como `unsigned int` (`-1` → `4294967295`, `ffffffff`) |
| `%%` | `%`, sin consumir ningún argumento |

Una `%` final sin carácter detrás y los especificadores no soportados tienen comportamiento indefinido en `printf`; aquí no producen ningún fallo del programa.

## Pruebas

Se ha comprobado cada conversión comparando con el `printf` real **la salida y el valor de retorno**, con programas de prueba propios (no incluidos en el repositorio):

- `%c`: letras, `0`, `%%`.
- `%s`: cadena normal, vacía y `NULL`.
- `%d`, `%i`: `0`, positivos, negativos, `INT_MIN`, `INT_MAX`.
- `%u`: `0`, `-1`, `UINT_MAX`.
- `%x`, `%X`: `0`, `255`, `-1`, `UINT_MAX`.
- `%p`: `NULL` y direcciones de variables locales.

Además se ha pasado `norminette` a todos los ficheros y `valgrind` para comprobar que no hay errores ni fugas de memoria.

## Recursos

- [`printf(3)` — Linux man-pages](https://man7.org/linux/man-pages/man3/printf.3.html) — comportamiento y valores de retorno de referencia.
- [`stdarg(3)` — Linux man-pages](https://man7.org/linux/man-pages/man3/stdarg.3.html) — `va_list`, `va_start`, `va_arg`, `va_end`.
- [`write(2)` — Linux man-pages](https://man7.org/linux/man-pages/man2/write.2.html) — escritura en un descriptor de archivo.
- [42 Norm v4](https://github.com/42School/norminette) — reglas de estilo comprobadas con `norminette`.
- El enunciado del proyecto y mi propia `libft`.

### Uso de IA

Se ha usado Claude como apoyo de **explicación, guía y revisión**, a medida que iba escribiendo el proyecto paso a paso:

- **Explicación de conceptos:** cómo funcionan `va_list`, `va_start`, `va_arg` y `va_end`; por qué `%c` se lee como `int` (promoción de argumentos); por qué los manejadores reciben un `va_list *`; y cómo evitar el desbordamiento con `INT_MIN`.
- **Diseño:** la convención de que cada función de impresión devuelva el número de caracteres escritos y la idea de imprimir números por recursión sin `malloc`.
- **Revisión de mi código**, que encontró y me permitió corregir:
  - `%s` leído con `va_arg(*args, int)` en lugar de `char *`, un `return` ausente en `manejar_conversion` y un contador `i` sin inicializar ni incrementar.
  - `%s` con `NULL`, que no imprimía `(null)` ni contaba 6 caracteres.
  - En la versión inicial de la impresión de enteros: una comparación `unsigned < 0` que nunca se cumple.
  - En `ft_print_hexp`, en `%p`, el caso `NULL` mal resuelto y con una errata en `(nil)`.
  - `%x` leído como `int` en lugar de `unsigned int`, que imprimía 16 `f` para `-1`.
- **Revisión del `Makefile`** (encadenar la compilación de `libft`, sin relink) y del modo de compilar y enlazar para las pruebas.
- **Guía de pruebas:** comparación con el `printf` real de salida y valor de retorno, y comprobación de la Norma (`norminette`).

El código lo he escrito yo, apoyándome en esas explicaciones, y soy capaz de explicar cada una de sus líneas. La IA se ha usado para entender conceptos, revisar y señalar errores concretos, no como sustituto del razonamiento propio.
