/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:55:17 by aalkaisi          #+#    #+#             */
/*   Updated: 2023/10/31 15:50:47 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_qut(char *str, int i, int qut_num[], int time)
{
	if (time == 1)
	{
		if (str[i] == '\'' && qut_num[0] == 1)
			qut_num[0] = 0;
		else if (str[i] == '\'' && qut_num[1] == 0)
			qut_num[0] = 1;
		if (str[i] == '"' && qut_num[1] == 1)
			qut_num[1] = 0;
		else if (str[i] == '"' && qut_num[0] == 0)
			qut_num[1] = 1;
	}
	// printf(">>>%d, %d, %c\n", time, qut_num[0] | qut_num[1], str[i]);
	return (qut_num[0] | qut_num[1]);
}

int	check_qut_error(char *str)
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
			{
				write(2, "Error\n", 6);
				return (1);
			}
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
			{
				write(2, "Error\n", 6);
				return (1);
			}
		}
		i++;
	}
	return (0);
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
		if (str[i] != '\'' && str[i] != '"')
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
		while (inside_qut(str, i, qut_num, 1) == 1 || 
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
		while (inside_qut(str, i, qut_num, 1) == 1 || 
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

char	*ft_strtrim_all(char *str)
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

int	double_pipe_error(char *str)
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
		if (inside_qut(str, i, qut_num, 1) == 0)
		{
			if (str[i] == '|' && symbol == 1)
				return (1);
			if (str[i] != ' ' && symbol == 1)
				symbol = 0;
			if (str[i] == '|' && symbol == 0)
				symbol = 1;
		}
		i++;
	}
	return (0);
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

int	double_symbol_error(char *str)
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
		if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '<' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '<')
			{
				symbol = 2;
				i++;
			}
			else
				symbol = 1;
		}
		else if (inside_qut(str, i, qut_num, 2) == 0 && str[i] == '>' && symbol == 0)
		{
			i++;
			if (inside_qut(str, i, qut_num, 1) == 0 && str[i] == '>')
			{
				symbol = 4;
				i++;
			}
			else
				symbol = 3;
		}
		else if (inside_qut(str, i, qut_num, 2) == 0 && (str[i] == '|' || 
				str[i] == '<' || str[i] == '>') && symbol != 0)
		{
			printf("bash: syntax error near unexpected token `%c'\n", str[i]);
			return (1);
		}
		if (str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '|')
			symbol = 0;
		i++;
	}
	return (0);
}

int	find_syntax_error(char	*str)
{
	int	i;

	i = 0;
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|' || 
		str[ft_strlen(str) - 1] == '<' || 
		str[ft_strlen(str) - 1] == '>')
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (double_pipe_error(str) == 1 || double_symbol_error(str) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	know_symbol(char c)
{
	int	symbol;

	if (c == '<')
		symbol = 1;
	else
		symbol = 3;
	return (symbol);
}

// int	know_qut_symbol(char c)
// {
// 	int	symbol;

// 	if (c == '\'')
// 		symbol = 1;
// 	else
// 		symbol = 2;
// 	return (symbol);
// }

void	size_of_all_redirections(char *str, t_execution *z)
{
	int		i;
	int		symbol;
	int		size[2];

	i = 0;
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if ((str[i] == '<' || str[i] == '>') && str[i] != '\'' && str[i] != '"')
		{
			symbol = know_symbol(str[i]);
			i++;
			if (str[i] == '<' || str[i] == '>')
			{
				symbol++;
				i++;
			}
			if (str[i] == ' ')
				i++;
			if (symbol == 1 || symbol == 2)
				size[0]++;
			else
				size[1]++;
		}
		if (str[i] != '<' && str[i] != '>' && str[i] != '\'' && str[i] != '"')
			i++;
	}
	z->is_file_or_here_doc = malloc(sizeof(int) * (size[0] + 1));
	z->is_file_or_append = malloc(sizeof(int) * (size[1] + 1));
	z->fd_infile = malloc(sizeof(int) * size[0]);
	z->fd_outfile = malloc(sizeof(int) * size[1]);
	if (z->is_file_or_here_doc == NULL || z->is_file_or_append == NULL || 
		z->fd_infile == NULL || z->fd_outfile == NULL)
		exit(1);
}

void	identify_file_type(char	*str, t_execution *z)
{
	int		i;
	int		symbol;
	int		size[2];

	i = 0;
	size[0] = 0;
	size[1] = 0;
	while (str[i] != '\0')
	{
		skip_qut(str, &i);
		if ((str[i] == '<' || str[i] == '>') && str[i] != '\'' && str[i] != '"')
		{
			symbol = know_symbol(str[i]);
			i++;
			if (str[i] == '<' || str[i] == '>')
			{
				symbol++;
				i++;
			}
			if (str[i] == ' ')
				i++;
			if (symbol == 1)
				z->is_file_or_here_doc[size[0]] = 0;
			else if (symbol == 2)
				z->is_file_or_here_doc[size[0]] = 1;
			else if (symbol == 3)
				z->is_file_or_append[size[1]] = 0;
			else if (symbol == 4)
				z->is_file_or_append[size[1]] = 1;
			if (symbol == 1 || symbol == 2)
				size[0]++;
			else
				size[1]++;
		}
		if (str[i] != '<' && str[i] != '>' && str[i] != '\'' && str[i] != '"')
			i++;
	}
	z->is_file_or_here_doc[size[0]] = -1;
	z->is_file_or_append[size[1]] = -1;
}

void	redirections(char *str, t_execution *z)
{
	int		i;
	int		qut_num[2];
	// int		symbol;
	// char	qut_symbol;
	int		size;

	qut_num[0] = 0;
	qut_num[1] = 0;
	i = 0;
	size = 0;
	size_of_all_redirections(str, z);
	identify_file_type(str, z);
	// while (str[i] != '\0')
	// {
	// 	if (inside_qut(str, i, qut_num, 1) == 0 && 
	// 		(str[i] == '<' || str[i] == '>'))
	// 	{
	// 		symbol = know_symbol(str[i]);
	// 		i++;
	// 		if (str[i] == '<' || str[i] == '>')
	// 		{
	// 			symbol++;
	// 			i++;
	// 		}
	// 		if (str[i] == ' ')
	// 			i++;
	// 		size++;
	// 		while (inside_qut(str, i, qut_num, 1) == 1 || (inside_qut(str
	// 					, i, qut_num, 2) == 0 && str[i] != ' ' && 
	// 			str[i] != '<' && str[i] != '>'))
	// 		{
	// 			i++;
	// 		}
	// 		printf(">>>>>> %d\n", size);
	// 	}
	// 	i++;
	// }
}

void	many_malloc(t_execution *z)
{
	z->cmds_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->infile_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	z->outfile_name = malloc(sizeof(char **) * (z->cmds_num + 1));
	if (z->cmds_name == NULL || z->infile_name == NULL || 
		z->outfile_name == NULL)
		exit(1);
}

void	num_of_files_in_each_part(char **str, t_execution *z)
{
	int	i;
	int	j;
	int	symbol;
	int	size[2];

	j = 0;
	while (str[j] != NULL)
	{
		i = 0;
		size[0] = 0;
		size[1] = 0;
		while (str[j][i] != '\0')
		{
			skip_qut(str[j], &i);
			// printf("8: %c\n", str[j][i]);
			if ((str[j][i] == '<' || str[j][i] == '>') && str[j][i] != '\'' 
				&& str[j][i] != '"')
			{
				symbol = know_symbol(str[j][i]);
				i++;
				if (str[j][i] == '<' || str[j][i] == '>')
				{
					symbol++;
					i++;
				}
				if (str[j][i] == ' ')
					i++;
				if (symbol == 1 || symbol == 2)
					size[0]++;
				else
					size[1]++;
			}
			if (str[j][i] != '<' && str[j][i] != '>' && str[j][i] != '\'' 
				&& str[j][i] != '"')
				i++;
		}
		// printf(">>>>>%d, %d\n", size[0], size[1]);
		z->infile_name[j] = malloc(sizeof(char *) * (size[0] + 1));
		z->outfile_name[j] = malloc(sizeof(char *) * (size[1] + 1));
		if (z->infile_name[j] == NULL || z->outfile_name[j] == NULL)
			exit(0);
		j++;
	}
	z->infile_name[j] = NULL;
	z->outfile_name[j] = NULL;
}

void	num_of_chars_in_each_file(char **str, t_execution *z)
{
	int			i;
	int			j;
	int			qut_num[2];
	int			symbol;
	int			num_of_chars;
	int			size[2];
	char		qut_symbol;

	j = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	qut_symbol = 'N';
	while (str[j] != NULL)
	{
		i = 0;
		size[0] = 0;
		size[1] = 0;
		while (str[j][i] != '\0')
		{
			if (inside_qut(str[j], i, qut_num, 1) == 0 && 
				(str[j][i] == '<' || str[j][i] == '>'))
			{
				symbol = know_symbol(str[j][i]);
				i++;
				if (str[j][i] == '<' || str[j][i] == '>')
				{
					symbol++;
					i++;
				}
				if (str[j][i] == ' ')
					i++;
				num_of_chars = 0;
				while (inside_qut(str[j], i, qut_num, 1) == 1 || (inside_qut(str[j]
							, i, qut_num, 2) == 0 && str[j][i] != ' ' && 
					str[j][i] != '<' && str[j][i] != '>' && str[j][i] != '\0'))
				{
					// printf("1>>>%c, %i, %i\n", str[j][i], i, inside_qut(str[j], i, qut_num, 2));
					if (inside_qut(str[j], i, qut_num, 2) == 1 && (str[j][i] == '\'' || str[j][i] == '"') && (qut_symbol == str[j][i] || qut_symbol == 'N'))
					{
						qut_symbol = str[j][i];
					}
					else if (inside_qut(str[j], i, qut_num, 2) == 0 && qut_symbol == str[j][i])
					{
						qut_symbol = 'N';
					}
					else
						num_of_chars++;
					i++;
				}
				printf("---------------------------------------------- %d, %d\n", num_of_chars, j);
				if (symbol == 1 || symbol == 2)
					z->infile_name[j][size[0]] = malloc(num_of_chars + 1);
				else
					z->outfile_name[j][size[1]] = malloc(num_of_chars + 1);
				if (symbol == 1 || symbol == 2)
					size[0]++;
				else
					size[1]++;
				printf("num_of_chars: %d\n", num_of_chars);
			}
			if (inside_qut(str[j], i, qut_num, 2) == 1 || (str[j][i] != '<' && str[j][i] != '>'))
				i++;
			if (str[j][i] == '\0')
				continue ;
			printf("%d\n", i);
		}
		z->infile_name[j][size[0]] = NULL;
		z->outfile_name[j][size[1]] = NULL;
		printf("z->infile_name[%d][%d]\n", j, size[0]);
		j++;
	}
}

void	put_chars_in_each_file(char **str, t_execution *z)
{
	int		i;
	int		j;
	int		qut_num[2];
	int		symbol;
	int		num_of_chars;
	int		size[2];
	char	qut_symbol;

	j = 0;
	qut_num[0] = 0;
	qut_num[1] = 0;
	qut_symbol = 'N';
	while (str[j] != NULL)
	{
		i = 0;
		size[0] = 0;
		size[1] = 0;
		while (str[j][i] != '\0')
		{
			printf("i: %i\n", i);
			if (inside_qut(str[j], i, qut_num, 1) == 0 && 
				(str[j][i] == '<' || str[j][i] == '>'))
			{
				symbol = know_symbol(str[j][i]);
				str[j][i] = ' ';
				i++;
				if (str[j][i] == '<' || str[j][i] == '>')
				{
					symbol++;
					str[j][i] = ' ';
					i++;
				}
				if (str[j][i] == ' ')
					i++;
				num_of_chars = 0;
				while (inside_qut(str[j], i, qut_num, 1) == 1 || (inside_qut(str[j]
							, i, qut_num, 2) == 0 && str[j][i] != ' ' && 
					str[j][i] != '<' && str[j][i] != '>' && str[j][i] != '\0'))
				{
					if (inside_qut(str[j], i, qut_num, 2) == 1 && (str[j][i] == '\'' || str[j][i] == '"') && (qut_symbol == str[j][i] || qut_symbol == 'N'))
					{
						qut_symbol = str[j][i];
						str[j][i] = ' ';
					}
					else if (inside_qut(str[j], i, qut_num, 2) == 0 && qut_symbol == str[j][i])
					{
						qut_symbol = 'N';
						str[j][i] = ' ';
					}
					else
					{
						if (symbol == 1 || symbol == 2)
							z->infile_name[j][size[0]][num_of_chars] = str[j][i];
						else
							z->outfile_name[j][size[1]][num_of_chars] = str[j][i];
						num_of_chars++;
						str[j][i] = ' ';
					}
					i++;
				}
				if (symbol == 1 || symbol == 2)
					z->infile_name[j][size[0]][num_of_chars] = '\0';
				else
					z->outfile_name[j][size[1]][num_of_chars] = '\0';
				if (symbol == 1 || symbol == 2)
					printf("111 %s\n", z->infile_name[j][size[0]]);
				else
					printf("222 %s\n", z->outfile_name[j][size[1]]);
				if (symbol == 1 || symbol == 2)
					size[0]++;
				else
					size[1]++;
			}
			if (inside_qut(str[j], i, qut_num, 2) == 1 || (str[j][i] != '<' && str[j][i] != '>'))
				i++;
			if (str[j][i] == '\0')
				continue ;
		}
		printf("-------------------------------------%s\n", str[j]);
		j++;
	}
}

void	num_of_commands_in_each_part(char **str, t_execution *z)
{
	int		j;

	j = 0;
	while (str[j] != NULL)
	{
		z->cmds_name[j] = ft_split(str[j], ' ', z);
		// if (z->cmds_name[j][0][0] != '\0')
		j++;
	}
	z->cmds_name[j] = NULL;
}

void	put_commands(char **str, t_execution *z)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		z->cmds_name[i] = ft_split(str[i], ' ', z);
		i++;
	}
	z->cmds_name[i] = NULL;
}

void	shift(int i, int j, int skip, t_execution *z)
{
	int	k;

	k = 0;
	while (z->cmds_name[i][j][k + skip + 1] != '\0')
	{
		z->cmds_name[i][j][k + skip] = z->cmds_name[i][j][k + skip + 1];
		k++;
	}
	z->cmds_name[i][j][k + skip] = '\0';
}

void	remove_qut(t_execution *z)
{
	int	i;
	int	j;
	int	k;
	int	qut_symbol;
	int	skip;
	int	flag;

	i = 0;
	qut_symbol = 0;
	skip = 0;
	flag = 0;
	while (z->cmds_name[i] != NULL)
	{
		j = 0;
		while (z->cmds_name[i][j] != NULL)
		{
			k = 0;
			while (z->cmds_name[i][j][k] != '\0')
			{
				if (z->cmds_name[i][j][k] == '\'' && qut_symbol == 1)
				{
					// skip++;
					qut_symbol = 0;
					flag = 1;
				}
				else if (z->cmds_name[i][j][k] == '"' && qut_symbol == 2)
				{
					// skip++;
					qut_symbol = 0;
					flag = 1;
				}
				else if (z->cmds_name[i][j][k] == '\'' && qut_symbol == 0)
				{
					// skip++;
					qut_symbol = 1;
					flag = 1;
				}
				else if (z->cmds_name[i][j][k] == '"' && qut_symbol == 0)
				{
					// skip++;
					qut_symbol = 2;
					flag = 1;
				}
				printf("%c, %s\n", z->cmds_name[i][j][k], z->cmds_name[i][j]);
				if (flag == 1)
					shift(i, j, k, z);
				// if (z->cmds_name[i][j][k + skip] == '\0')
				// {
				// 	while (z->cmds_name[i][j][k] != '\0')
				// 	{
				// 		z->cmds_name[i][j][k] = '\0';
				// 		k++;
				// 	}
				// 	break ;
				// }
				if (flag == 0)
					k++;
				flag = 0;
			}
			j++;
		}
		i++;
	}
}

void	check_solution(t_execution *z)
{
	int i = 0;
	int j = 0;

	while (z->infile_name[i] != NULL)
	{
		j = 0;
		while (z->infile_name[i][j] != NULL)
		{
			printf("z->infile_name[%d][%d]: %s,\n", i, j, z->infile_name[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (z->outfile_name[i] != NULL)
	{
		j = 0;
		while (z->outfile_name[i][j] != NULL)
		{
			printf("z->outfile_name[%d][%d]: %s,\n", i, j, z->outfile_name[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (z->is_file_or_here_doc[i] != -1)
	{
		printf("z->is_file_or_here_doc[%d]: %d\n", i, z->is_file_or_here_doc[i]);
		i++;
	}
	i = 0;
	while (z->is_file_or_append[i] != -1)
	{
		printf("z->is_file_or_append[%d]: %d\n", i, z->is_file_or_append[i]);
		i++;
	}
	i = 0;
	j = 0;
	while (z->cmds_name[i] != NULL)
	{
		j = 0;
		while (z->cmds_name[i][j] != NULL)
		{
			printf("z->cmds_name[%d][%d]: %s,\n", i, j, z->cmds_name[i][j]);
			j++;
		}
		i++;
	}
}

int	main(void)
{
	char		*str;
	char		**res;
	int			i;
	// char		*dollar_var;
	// char		*dollar_value;
	t_execution	z;

	while (1)
	{
		str = readline(">");
		if (str == NULL || str[0] == '\0')
			continue ;
		// dollar(str);
		if (str_cmp(str, "exit") == 1)
			break ;
		printf("lol--->%s.\n", str);
		// str[ft_strlen(str) - 1] = '\0';
		if (check_qut_error(str) == 1)
			continue ;
		printf("1--->%s.\n", str);
		tab_to_space(str);
		printf("2--->%s.\n", str);
		printf("3--->%zu.\n", ft_strlen(str));
		str = ft_strtrim_all(str);
		printf("--->%s.%zu\n", str, ft_strlen(str));
		if (str == NULL)
			continue ;
		printf("11111.\n");
		if (find_syntax_error(str) == 1)
			continue ;
		printf("%s...\n", str);
		printf("11111.\n");
		redirections(str, &z);
		printf("%s..\n", str);
		printf("11111.\n");
		res = ft_split(str, '|', &z);
		printf("77777.\n");
		i = -1;
		while (res[++i] != NULL)
			res[i] = ft_strtrim(res[i], " ");
		many_malloc(&z);
		printf("%s, %s.\n", res[0], res[1]);
		printf("11111.\n");
		num_of_files_in_each_part(res, &z);
		printf("11111.\n");
		num_of_chars_in_each_file(res, &z);
		printf("11111.\n");
		put_chars_in_each_file(res, &z);
		put_commands(res, &z);
		remove_qut(&z);
		check_solution(&z);
		// re_order(res, &z);
		free(str);
	}
}
