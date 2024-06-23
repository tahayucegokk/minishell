/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyucego <muyucego@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:35:26 by fpolycar          #+#    #+#             */
/*   Updated: 2024/06/24 00:00:51 by muyucego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	replace_dollar(t_global *g, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (g->envp[k])
	{
		if (ft_strncmp(str + j + 1, g->envp[k], chr_sign(g->envp[k]) - 1) == 0 && chr_dol(str, j) - j == (int)chr_sign(g->envp[k]))
		{
			tmp2 = ft_strdup(g->envp[k] + chr_sign(g->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = chr_sign(g->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = chr_dol(str, j) - j;
	return (ret);
}

int	skip_if_number(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			j += 2;
		}
	}
	return (j - i);
}

char	*detect_dollar_sign(t_global *g, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += skip_if_number(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += qm(&tmp);
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
					|| str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += replace_dollar(g, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

char	**expander(t_global *g, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (str[i][dollar_sign(str[i]) - 2] != '\'' && dollar_sign(str[i]) != 0
			&& str[i][dollar_sign(str[i])])
		{
			tmp = detect_dollar_sign(g, str[i]);
			free(str[i]);
			str[i] = tmp;
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
		{
			str[i] = replace_q(str[i], '\"');
			str[i] = replace_q(str[i], '\'');
		}
		i++;
	}
	return (str);
}

char	*expander_str(t_global *g, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[dollar_sign(str) - 2] != '\'' && dollar_sign(str) != 0
		&& str[dollar_sign(str)] != '\0')
	{
		tmp = detect_dollar_sign(g, str);
		free(str);
		str = tmp;
	}
	str = replace_q(str, '\"');
	str = replace_q(str, '\'');
	return (str);
}
