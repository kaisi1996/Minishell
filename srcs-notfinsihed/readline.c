/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:42:18 by mohammoh          #+#    #+#             */
/*   Updated: 2023/10/27 16:55:45 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int main (int ac, char **av)
{
	char *str;
	char cwd[PATH_MAX];
	
	printf("Minishell>$ ");
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
// 	while (1)
// 	{
// 		str = readline(av[1]);
// 		add_history(str);
// 		printf("%s\n", getenv(av[1]));
// 	}
}