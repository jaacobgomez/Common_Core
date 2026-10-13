*Este proyecto ha sido creado como parte del curriculum de 42 por jacgomez.*

# get_next_line

**Common Core — 42 Madrid**

## Descripción

`get_next_line` es una función que, cada vez que se la llama con un descriptor de archivo, devuelve **la siguiente línea** leída de él: el contenido hasta el siguiente `\n` incluido (o hasta el final del archivo si la última línea no termina en salto de línea). Cuando no queda nada que leer, o si ocurre un error, devuelve `NULL`.

```c
char	*get_next_line(int fd);
```

Reglas del enunciado que se respetan:

- Solo se permiten `read`, `malloc` y `free`. No se usa `libft`, ni `lseek`, ni variables globales.
- El tamaño de lectura se define al compilar con `-D BUFFER_SIZE=n`; si no se define, el `.h` aplica un valor por defecto (42).
- Funciona con archivos y con la entrada estándar.
- Todo el código cumple la Norma de 42: máximo 5 funciones por archivo, 4 parámetros por función, 5 variables por función y 25 líneas por función.

Solo se ha hecho la parte obligatoria (un único descriptor a la vez); no se ha implementado el bonus.

## Instrucciones

### Compilación

El proyecto no lleva `Makefile`; los tres ficheros se compilan junto con el programa que los use:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` puede tomar cualquier valor positivo (1, 10, 42, 9999, 10000000...) y el resultado debe ser siempre el mismo.

### Uso

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("archivo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Quien llama es responsable de liberar con `free` cada línea devuelta.

### Estructura de ficheros

| Fichero | Contenido |
|---|---|
| `get_next_line.h` | Guarda de inclusión, `BUFFER_SIZE` por defecto y prototipos |
| `get_next_line.c` | `get_next_line` y sus auxiliares `extract_line`, `cut_stash`, `free_all` y `can_stash` (5 funciones) |
| `get_next_line_utils.c` | `ft_strlen`, `ft_strchr`, `ft_strjoin` y `ft_substr` |

## Algoritmo y decisiones de diseño

### Idea general: una `stash` estática

`read` devuelve bloques de `BUFFER_SIZE` bytes que no tienen por qué coincidir con las líneas: un bloque puede contener varias líneas, o una línea puede ocupar muchos bloques. Por eso se usa una variable `static char *stash`, que **conserva entre llamadas lo ya leído pero todavía no devuelto**. Cada llamada hace tres pasos:

1. **`can_stash`**: lee y añade a la `stash` hasta que contenga un `\n` o hasta que `read` devuelva 0 (fin de archivo).
2. **`extract_line`**: copia desde el principio de la `stash` hasta el `\n` incluido (o hasta el final, si no hay `\n`). La longitud sale de una resta de punteros, `len = newline - stash + 1`.
3. **`cut_stash`**: se queda con lo que hay después del `\n`, libera la `stash` anterior y deja `NULL` si no queda nada.

```
fichero: "ab\ncd\nef"        BUFFER_SIZE = 4

llamada 1: lee "ab\nc"   stash = "ab\nc"     → devuelve "ab\n"   stash = "c"
llamada 2: lee "d\nef"   stash = "cd\nef"    → devuelve "cd\n"   stash = "ef"
llamada 3: lee "" (EOF)  stash = "ef"        → devuelve "ef"     stash = NULL
llamada 4: lee "" (EOF)  stash = NULL        → devuelve NULL
```

### Gestión de memoria y de errores

- **El buffer de lectura va en el heap** (`malloc` de `BUFFER_SIZE + 1`), no en la pila: con `BUFFER_SIZE=10000000` un array local desbordaría la pila. El `+ 1` deja sitio para el `\0`, porque `read` no lo añade.
- **`ft_strjoin(char *s1, const char *s2)` libera `s1`**, incluso si falla el `malloc`. Así la `stash` se reemplaza por la versión ampliada sin que quede memoria perdida, y se resume en una sola función.
- **Las funciones de `utils` aceptan `NULL`**: la `stash` empieza en `NULL` y esto evita casos especiales para la primera llamada.
- **Si `read` devuelve -1**, se libera la `stash` y el buffer y se devuelve `NULL`. Es importante dejar la `stash` en `NULL`: si se conservara, la siguiente llamada devolvería datos que pertenecen a una lectura fallida.
- **Si falla cualquier `malloc`**, se libera todo lo reservado hasta ese momento, la `stash` queda en `NULL` y se devuelve `NULL`.
- Un `fd` negativo o un `BUFFER_SIZE <= 0` devuelven `NULL` directamente.

### Casos límite

| Caso | Resultado |
|---|---|
| Archivo vacío | `NULL` en la primera llamada |
| Archivo de un solo carácter, sin `\n` | Devuelve ese carácter y luego `NULL` |
| Última línea sin `\n` | Se devuelve sin `\n` |
| Líneas vacías (solo `\n`) | Cada una se devuelve como `"\n"` |
| Línea mucho mayor que `BUFFER_SIZE` | Se sigue leyendo y concatenando hasta encontrar `\n` |
| `BUFFER_SIZE = 1` | Funciona, pero lee byte a byte |
| `fd` inválido o cerrado | `NULL` |
| Entrada estándar | Funciona igual que con un archivo |

### Limitaciones conocidas

- Se usa una sola `stash`, por lo que solo se puede leer **un descriptor a la vez**; alternar entre varios `fd` mezclaría sus datos (el bonus resuelve esto, y no se ha hecho).
- Cada lectura se concatena a la `stash` con `ft_strjoin`, que copia todo lo acumulado. Para líneas gigantes con `BUFFER_SIZE` muy pequeño el coste es cuadrático. Para el uso normal es suficiente y mantiene el código simple.
- Si quien llama deja de leer antes de llegar al final del archivo, la `stash` conserva memoria que no se libera hasta el final del programa. Es inevitable con una variable estática y sin función de limpieza.

## Pruebas

- Archivos de prueba propios con `BUFFER_SIZE` 1, 10, 42 y 10000000: vacío, un carácter, una línea sin `\n`, solo `\n`, varios `\n` seguidos, líneas de longitud alrededor de `BUFFER_SIZE` y líneas gigantes (20 000 caracteres).
- Entrada estándar (`./gnl < archivo`).
- `valgrind --leak-check=full` para comprobar que no hay errores de memoria ni fugas.
- Simulación de fallos de `malloc` (se fuerza que cada reserva falle por turnos) para comprobar que ninguna ruta de error deja memoria sin liberar.
- Tester [Francinette](https://github.com/xicodomingues/francinette) con `paco --strict`.
- `norminette` sobre los tres ficheros.

## Recursos

- [`read(2)` — Linux man-pages](https://man7.org/linux/man-pages/man2/read.2.html) — valores de retorno (bytes leídos, 0 en EOF, -1 en error) y lecturas parciales.
- [`malloc(3)` — Linux man-pages](https://man7.org/linux/man-pages/man3/malloc.3.html) — reserva y liberación de memoria.
- [`static` y duración de almacenamiento en C](https://en.cppreference.com/w/c/language/storage_duration) — por qué una variable `static` conserva su valor entre llamadas.
- [Francinette](https://github.com/xicodomingues/francinette) — tester usado para validar el proyecto.
- [42 Norm v4](https://github.com/42School/norminette) — reglas de estilo comprobadas con `norminette`.
- El enunciado del proyecto.

### Uso de IA

Se ha usado Claude como apoyo de **explicación, guía y revisión**, mientras escribía el proyecto paso a paso. El código lo he escrito yo.

- **Explicación de conceptos:** cómo funciona `read` (no añade `\0`, puede devolver menos bytes de los pedidos, 0 en EOF y -1 en error), qué significa la resta de punteros `newline - stash + 1` y por qué el buffer debe ir en el heap.
- **Diseño:** el esquema de tres pasos (leer a la `stash`, extraer línea, recortar `stash`), y reducir `ft_strjoin` a una sola función que libera `s1`.
- **Revisión de mi código**, que encontró y me permitió corregir:
  - `extract_line` devolviendo siempre toda la `stash` en lugar de solo hasta el `\n`.
  - La `stash` declarada sin `static`, el buffer en la pila y un `while` con la condición invertida.
  - Una fuga de memoria en `get_next_line`: en el caso de que `extract_line` fallara se hacía `free(line)` (que es `NULL`) en lugar de `free(stash)`.
- **Guía de pruebas:** simulación de fallos de `malloc`, `valgrind` y funcionamiento del tester Francinette.

Soy capaz de explicar cada línea del código. La IA se ha usado para entender, revisar y señalar errores concretos, no para sustituir mi razonamiento.
