/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:01:41 by rnakai            #+#    #+#             */
/*   Updated: 2020/07/13 22:02:00 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** count words always return int value, more than 1
*/

static int	count_words(char const *str, char ch)
{
	int		count;
	int		flag;
	int		idx;

	count = 0;
	flag = 0;
	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] != ch)
			flag = 0;
		else if (flag == 1)
		{
			idx++;
			continue;
		}
		else if (str[idx] == ch)
		{
			count++;
			flag = 1;
		}
		idx++;
	}
	return (count + 1);
}

static int	skip_wd_or_delim(char *str, int idx, char ch)
{
	if (str[idx] != ch)
	{
		while (str[idx] != ch && str[idx] != '\0')
			idx++;
		return (idx - 1);
	}
	else
	{
		while (str[idx] == ch && str[idx] != '\0')
			idx++;
		return (idx);
	}
}

static void	all_free(char **db_ptr, int idx)
{
	int i;

	i = 0;
	while (i < idx)
		free(db_ptr[idx]);
	free(db_ptr);
	db_ptr = NULL;
}

static void	create_word_array(int words, char ch, char *str, char **db_ptr)
{
	int		idx;
	int		head;
	int		tail;

	idx = 0;
	head = 0;
	while (idx < words)
	{
		tail = skip_wd_or_delim(str, head, ch);
		if (!(db_ptr[idx] = ft_substr(str, head, tail - head + 1)))
		{
			all_free(db_ptr, idx);
			return ;
		}
		head = skip_wd_or_delim(str, tail + 1, ch);
		idx++;
	}
	db_ptr[idx] = NULL;
}

char		**ft_split(char const *str, char ch)
{
	char	*ptr;
	int		words;
	char	**ret_db_ptr;
	char	divider_set[2];

	ft_strlcpy(divider_set, &ch, 2);
	if (!(ptr = ft_strtrim(str, divider_set)))
		return (NULL);
	words = count_words(ptr, ch);
	if (ptr[0] == '\0')
		words = 0;
	if (!(ret_db_ptr = (char **)malloc(sizeof(char *) * (words + 1))))
	{
		free(ptr);
		return (NULL);
	}
	if (words == 0)
	{
		ret_db_ptr[0] = NULL;
		free(ptr);
		return (ret_db_ptr);
	}
	create_word_array(words, ch, ptr, ret_db_ptr);
	free(ptr);
	return (ret_db_ptr);
}


#include <stdio.h>
int		main(void)
{
	// char str[] = "hello  my name is hoge ";
	// char str[] = "hello  my  name i hogehgoegjasklfjeaijl;kj;jklfjalastIBDDS";
	char str[] = "J4bGs se3QNymWjK 0wnuHeUDYJx z2qeFNkgYnICaB0di 2crs 2waS3O UijQE3LAcVoPyreRp EMjf2ASxyr5gvTD8 GqU07FxQjZKIB8";
	// char str[] = "hello  my  name i ";
	// char str[] = "    ";
	// char str[] = "   hello  ";
	// char str[] = "";
	// char str[] = NULL;
	// char str[] = "      split       this for   me  !       ";
	// char str[] = "\0aaa\0bbb";
	char ch = ' ';
	// char ch = '\0';
	char **result;
	result = ft_split(str, ch);
	for (int i = 0; result[i] != NULL; i++)
	{
		ft_putstr_fd(result[i], 1);
		printf("\n");
	}
	return (0);
}

