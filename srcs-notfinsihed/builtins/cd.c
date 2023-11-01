/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:21:46 by mohammoh          #+#    #+#             */
/*   Updated: 2023/11/01 22:13:07 by mohammoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_path(t_env *env, char *var, int len)
{
	char	*oldpath;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next)
	{
		if (strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			if (!(oldpath = ft_calloc(s_alloc + 1, 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i])
			{
				if (i > len)
				{
					oldpath[j] = env->value[i];
					j++;
				}
				i++;
			}
			oldpath[j] = '\0';
			return (oldpath);
		}
		env = env->next;
	}
	return (NULL);
}

int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX]; // current working directory
	char	*oldpwd;

	if (!getcwd(cwd, PATH_MAX))
		return (ERROR);
	if (!(oldpwd = ft_strjoin("OLDPATH=", cwd)))
		return (ERROR);
	if (is_in_env(env, oldpwd) == 0) //exporting
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);//get enviroment path
		if (!env_path)
			return(ft_putendl_fd("home not set", 2), ERROR);
		else if (option == 1)
		{
			env_path = get_env_path(env, "OLDPWD", 6);
			if (!env_path)
				return(ft_putendl_fd("OLDPWD not set", 2), ERROR);
			update_oldpwd(env);
		}
		ret = chdir(env_path);
	}
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;

	if (!args[1])
		return(go_to_path(0, env)); // go to home path
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret != 0)
			;//print_error;
	}
	return(cd_ret);
}