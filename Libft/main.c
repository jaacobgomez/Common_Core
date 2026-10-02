#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	print_char(unsigned int i, char *c)
{
	printf("[%u]=%c ", i, *c);
}

char	to_upper(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

void	print_content(void *content)
{
	printf("%s -> ", (char *)content);
}

void	free_content(void *content)
{
	free(content);
}

int	main(void)
{
	char	*s;
	t_list	*lst;
	t_list	*lst2;
	t_list	*node;
	char	**split;
	int		i;

	printf("=== PARTE 1: libc ===\n");
	printf("ft_atoi(\"  -42abc\") = %d\n", ft_atoi("  -42abc"));
	printf("ft_isalpha('a') = %d\n", ft_isalpha('a'));
	printf("ft_isdigit('5') = %d\n", ft_isdigit('5'));
	printf("ft_isalnum('!') = %d\n", ft_isalnum('!'));
	printf("ft_isascii(200) = %d\n", ft_isascii(200));
	printf("ft_isprint('\\n') = %d\n", ft_isprint('\n'));
	printf("ft_toupper('b') = %c\n", ft_toupper('b'));
	printf("ft_tolower('B') = %c\n", ft_tolower('B'));
	printf("ft_strlen(\"hola\") = %zu\n", ft_strlen("hola"));

	s = calloc(16, 1);
	ft_memset(s, 'x', 5);
	s[5] = '\0';
	printf("ft_memset -> %s\n", s);
	ft_bzero(s, 5);
	printf("ft_bzero -> [%d %d %d %d %d]\n", s[0], s[1], s[2], s[3], s[4]);
	free(s);

	s = calloc(16, 1);
	ft_memcpy(s, "copia", 6);
	printf("ft_memcpy -> %s\n", s);
	ft_memmove(s + 1, s, 5);
	printf("ft_memmove -> %s\n", s);
	free(s);

	s = calloc(16, 1);
	printf("ft_strlcpy ret = %zu, s = %s\n", ft_strlcpy(s, "hola", 16), s);
	printf("ft_strlcat ret = %zu, s = %s\n", ft_strlcat(s, "!!", 16), s);
	free(s);

	printf("ft_strchr(\"hello\", 'l') = %s\n", ft_strchr("hello", 'l'));
	printf("ft_strrchr(\"hello\", 'l') = %s\n", ft_strrchr("hello", 'l'));
	printf("ft_strncmp(\"abc\", \"abd\", 3) = %d\n", ft_strncmp("abc", "abd", 3));
	printf("ft_memchr(\"hello\", 'e', 5) = %s\n", (char *)ft_memchr("hello", 'e', 5));
	printf("ft_memcmp(\"abc\", \"abd\", 3) = %d\n", ft_memcmp("abc", "abd", 3));
	printf("ft_strnstr(\"hello world\", \"world\", 11) = %s\n",
		ft_strnstr("hello world", "world", 11));

	s = ft_calloc(5, sizeof(char));
	printf("ft_calloc -> [%d %d %d %d %d]\n", s[0], s[1], s[2], s[3], s[4]);
	free(s);

	s = ft_strdup("duplicado");
	printf("ft_strdup -> %s\n", s);
	free(s);

	printf("\n=== PARTE 2: funciones adicionales ===\n");
	s = ft_substr("hello world", 6, 5);
	printf("ft_substr -> %s\n", s);
	free(s);

	s = ft_strjoin("foo", "bar");
	printf("ft_strjoin -> %s\n", s);
	free(s);

	s = ft_strtrim("  hola  ", " ");
	printf("ft_strtrim -> [%s]\n", s);
	free(s);

	split = ft_split("uno,dos,tres", ',');
	printf("ft_split ->");
	i = 0;
	while (split[i] != NULL)
	{
		printf(" %s", split[i]);
		free(split[i]);
		i++;
	}
	printf("\n");
	free(split);

	s = ft_itoa(-4567);
	printf("ft_itoa(-4567) -> %s\n", s);
	free(s);

	s = ft_strmapi("hola", to_upper);
	printf("ft_strmapi -> %s\n", s);
	free(s);

	s = ft_strdup("hola");
	ft_striteri(s, print_char);
	printf("\n");
	free(s);

	ft_putstr_fd("ft_putstr_fd funciona\n", 1);
	ft_putendl_fd("ft_putendl_fd funciona", 1);
	ft_putnbr_fd(-123, 1);
	ft_putchar_fd('\n', 1);

	printf("\n=== PARTE 3: listas enlazadas ===\n");
	lst = ft_lstnew(ft_strdup("A"));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("B")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("C")));
	ft_lstadd_front(&lst, ft_lstnew(ft_strdup("Z")));

	printf("ft_lstsize = %u\n", ft_lstsize(lst));
	printf("ft_lstlast = %s\n", (char *)ft_lstlast(lst)->content);

	printf("ft_lstiter -> ");
	ft_lstiter(lst, print_content);
	printf("NULL\n");

	lst2 = ft_lstmap(lst, (void *(*)(void *))ft_strdup, free_content);
	printf("ft_lstmap (copia) -> ");
	ft_lstiter(lst2, print_content);
	printf("NULL\n");

	node = lst;
	lst = lst->next;
	ft_lstdelone(node, free_content);
	printf("ft_lstdelone -> nuevo size = %u\n", ft_lstsize(lst));

	ft_lstclear(&lst, free_content);
	ft_lstclear(&lst2, free_content);
	printf("ft_lstclear -> lst es NULL: %d\n", lst == NULL);

	return (0);
}
