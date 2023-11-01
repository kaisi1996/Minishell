/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:35:34 by mohammoh          #+#    #+#             */
/*   Updated: 2023/10/10 17:11:02 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//after finishing the execution we can implement the signals 
void	handle_ctrl_c(int signo)
{
	//global variable
	//display a new prompt on the terminal
}

void	handle_ctrl_d(int signo)
{
	//global variable
	//exits the shell
}

void	handle_ctrl_backslash(int signo)
{
	//global variable
	//does nothing
}
int	main()
{
	struct sigaction	sa;

	sa.sa_handler = handle_ctrl_c;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = handle_ctrl_d;
	sigaction(SIGQUIT, &sa, NULL);

	sa.sa_handler = handle_ctrl_backslash;
	sigaction(SIGQUIT, &sa, NULL);
}