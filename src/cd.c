/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:07:48 by mucabrin          #+#    #+#             */
/*   Updated: 2024/11/23 16:01:49 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_findnode(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, INT_MAX) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// static int	cd_error(t_env **env, t_built *var)
// {
// 	DIR *dir;
// 	dir = opendir(path);
// 	// env_oldpwd = ft_findnode(*env, "OLDPWD");
// 	// var->env_pwd = ft_findnode(*env, "PWD");
// 	// var->env_home = ft_findnode(*env, "HOME");
// 	if (var->path && !var->dir && !diff_dir(var->path))
// 	{
// 		ft_printf_fd(2, "bash: cd: %s: %s\n", var->path, strerror(errno));
// 		//g_exitcode = 1;
// 		return (0);
// 	}
// 	if (var->dir)
// 		closedir(var->dir);
// 	return (1);
// }

int	diff_dir(const char *path)
{
	return (NULL || ft_strncmp(path, "~", INT_MAX) == 0 || ft_strncmp(path, "#",
			INT_MAX) == 0 || ft_strncmp(path, "-", INT_MAX) == 0);
}

void	cd(char **token)
{
	//t_built	var;
	char *path;
	DIR *dir;

	printf("lici");
	path = token[1];
	// if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
	// 	var.path = token[2];
	if (path && token[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		////g_exitcode = 1;
		return ;
	}
	if (path)
		dir = opendir(path);
	if (path && !dir && !diff_dir(path))
	{
		printf("bash: cd : %s: %s\n", path, strerror(errno));
		//g_exitcode = 1;
		return ;
	}
	printf("le path : %s\n", path);
	if (path)
		closedir(dir);
	if (!token[1] || ft_strncmp(path, "~", INT_MAX) == 0
		|| ft_strncmp(path, "#", INT_MAX) == 0)
		chdir(getenv("HOME"));
	else
		chdir(path);
}
