/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:55:17 by aalkaisi          #+#    #+#             */
/*   Updated: 2023/10/09 13:23:13 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct execution
{
	char	***cmds;
	char	***infile;
	char	***here_doc;
	char	***outfile;
	char	***append_file;
}	t_execution;

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

int	inside_qut(char *str, int i, int qut_num[])
{
	if (str[i] == '\'' && qut_num[0] == 1)
		qut_num[0] = 0;
	else if (str[i] == '\'' && qut_num[1] == 0)
		qut_num[0] = 1;
	if (str[i] == '"' && qut_num[1] == 1)
		qut_num[1] = 0;
	else if (str[i] == '"' && qut_num[0] == 0)
		qut_num[1] = 1;
	return (qut_num[0] | qut_num[1]);
}

void	check_qut_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				exit(1);//exiting 
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				exit(1);
		}
		i++;
	}
}

int	skip_qut(char *str, int *i)
{
	int	i_init;

	i_init = *i;
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"')
			(*i)++;
		(*i)++;
	}
	return (*i - i_init);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	tab_to_space(char *str)
{
	int	i;
	// int	qut_num[2];

	i = 0;
	// qut_num[0] = 0;
	// qut_num[1] = 0;
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int	size_after_trim(char *str)
{
	int		i;
	int		size;
	char	flag;
	int		qut_num[2];

	i = 0;
	size = 0;
	flag = 'N';
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0' && flag == 'Y')
			size++;
		while (inside_qut(str, i, qut_num) == 1 || 
			(str[i] != ' ' && str[i] != '\0'))
		{
			size++;
			i++;
			flag = 'Y';
		}
	}
	printf("4>size: %d\n", size);
	return (size);
}

void	ft_strtrim2(char *res, char *str, int size)
{
	int		i;
	char	flag;
	int		qut_num[2];

	i = 0;
	flag = 'N';
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0' && flag == 'Y')
		{
			res[size] = ' ';
			size++;
		}
		while (inside_qut(str, i, qut_num) == 1 || 
			(str[i] != ' ' && str[i] != '\0'))
		{
			res[size] = str[i];
			size++;
			i++;
			flag = 'Y';
		}
	}
	// printf("--->%s\n", str);
	free(str);
	res[size] = '\0';
}

char	*ft_strtrim(char *str)
{
	int		size;
	char	*res;

	if (str == NULL)
		return (NULL);
	size = size_after_trim(str);
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	size = 0;
	ft_strtrim2(res, str, size);
	return (res);
}

// void	find_qut_error(char *str)
// {
// 	int	i;
// 	int	qut_num[2];

// 	qut_num[0] = 0;
// 	qut_num[1] = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		inside_qut(str, i, qut_num);
// 		i++;
// 	}
// 	if (qut_num[0] == 1 || qut_num[1] == 1)
// 		exit(1);
// }

void	double_pipe_error(char *str)
{
	int	i;
	int	symbol;
	int	qut_num[2];

	i = 0;
	symbol = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		if (inside_qut(str, i, qut_num) == 0)
		{
			if (str[i] == '|' && symbol == 1)
				exit(1);
			if (str[i] != ' ' && symbol == 1)
				symbol = 0;
			if (str[i] == '|' && symbol == 0)
				symbol = 1;
		}
		i++;
	}
}

// void	put_zero(int symbol[])
// {
// 	symbol[0] = 0;
// 	symbol[1] = 0;
// 	symbol[2] = 0;
// 	symbol[3] = 0;
// }

// int	are_all_zeros(int symbol[])
// {
// 	if ()
// }

void	double_symbol_error(char *str)
{
	int	i;
	int	symbol;
	int	qut_num[2];

	i = 0;
	symbol = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	while (str[i] != '\0')
	{
		if (inside_qut(str, i, qut_num) == 0 && str[i] == '<' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num) == 0 && str[i] == '<')
			{
				symbol = 2;
				i++;
			}
			else
				symbol = 1;
		}
		if (inside_qut(str, i, qut_num) == 0 && str[i] == '>' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num) == 0 && str[i] == '>')
			{
				symbol = 4;
				i++;
			}
			else
				symbol = 3;
		}
		if (inside_qut(str, i, qut_num) == 0 && (str[i] == '|' || str[i] == '<' 
				|| str[i] == '>') && symbol != 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", str[i]);
			exit(1);
		}
		if (str[i] != ' ')
			symbol = 0;
		i++;
	}
}

void	find_syntax_error(char	*str)
{
	int	i;

	i = 0;
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		exit(1);
	double_pipe_error(str);
	double_symbol_error(str);
}

// void	re_order(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
		
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	char	*str;
	// char	*res;

	str = ft_strdup(" \td'   hellck|l|d \t  nsknx \"  <<<<< '      >    l  |      \" \"c\t\t   ");
	if (str == NULL)
		return (1);
	check_qut_error(str);
	printf("--->%s.\n", str);
	tab_to_space(str);
	printf("--->%s.\n", str);
	printf("--->%zu.\n", ft_strlen(str));
	str = ft_strtrim(str);
	printf("--->%s.%zu\n", str, ft_strlen(str));
	if (str == NULL)
		return (1);
	find_syntax_error(str);
	printf("%s.\n", str);
	re_order(str);
	free(str);
}
