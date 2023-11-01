/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:58:45 by mohammoh          #+#    #+#             */
/*   Updated: 2023/11/01 22:15:20 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int		print_error(int error, char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", 2);
	else if (error == 0 || error == -42)
		ft_putstr_fd("export not a valid identifier: ", 2);
	i = 0; 
	while (arg[i] && (arg[i] != '=' || error == -42))
	{
		ft_putchar_fd(arg[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
	return (0);
}

int		is_valid_env(const char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

int		env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;
	
	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (1);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (1);
}

char	*get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int		new_env;
	int		error_ret;
	int		i = 0;
	
	new_env = 0;
	if (!args[1])
	{
		print_sorted_env(secret);
		return (1);
		
	}
	else
	{
		error_ret = is_valid_env(args[i]);
		if (args[1][0])
			error_ret = -42;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1])); //error msg need to be written
		new_env; 
	}
}