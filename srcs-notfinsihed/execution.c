/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:54:51 by mohammoh          #+#    #+#             */
/*   Updated: 2023/10/29 21:34:00 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*return true if all is ready for execution*/
int	prep_for_execution(t_data *data)
{
	
}
/*execute the given commands by creating children processes and waiting for them to terminates
*/
int	execute(t_execution *data)
{
	int	ret;

	ret = prep_for_execution(data);
}

int	execute_external_cmd(t_execution *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		//handle error fork
	else if (pid == 0)
	{
		execve(data->cmds_name[0][0], data->cmds_name);
	}
	
}