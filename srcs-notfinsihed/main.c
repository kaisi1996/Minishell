/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:36:23 by mohammoh          #+#    #+#             */
/*   Updated: 2023/10/18 20:17:03 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*parser user input
* Tokenizes and parses user input into a structure for execution
*/

int		parse_user_input(t_execution *data)
{
	//check if user input is null then exit_builtins
	//check if input is spaces only'//
	//user input-> is yet to be there 
	add_history(data->);
	//check tokenization
	tokenization(data, data->user_input);
	
}
int		create_children(t_execution *data)
{
	char *cmd;

	cmd = data->cmds_name[ ]
}

int	main (int ac, char **av, char **envp)
{
	// to execute a command, first we will check the parsing 
	// the words that are not variable assignments or redirections are expanded, if any word remain after expansion
	// the first word is taken to be the name of the command and the remaining words are the arguments
	// redirections 
	
	printf("%s\n", PROMPT);
}