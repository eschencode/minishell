/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:57:14 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/10 10:37:48 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		tilde_counter(t_shell *shell)
{
	int i;
	int n_tilde;

	i = -1;
	n_tilde = 0;
	while (shell->input_str[++i])
	{
		if (shell->input_str[i] == '~')
		{
			n_tilde++;
		}
	}
	return (n_tilde);	
}

int		tilde_validator(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->input_str[++i])
	{
		if (shell->input_str[i] == '~' && shell->input_str[i + 1])
		{
			if (shell->input_str[i + 1] == '~')
				return (0);
		}
	}
	return (1);	
}

void tilde_expander(t_shell *shell)
{
	int y;
	int n_tilde;
	int home_len;
	char *home;
	char **split;
	char *new_str;
	
	n_tilde = tilde_counter(shell);
	if (n_tilde > 1)
	{
		if (tilde_validator(shell) == 0)
			return ;
	}
	if (n_tilde == 0)
		return ;
	home = env_get_val(shell, "HOME");
	if (home == NULL)
		return ;
	home_len = ft_strlen(home);
	split = ft_split(shell->input_str, '~');
	new_str = malloc(sizeof(char) * (ft_strlen(shell->input_str) + (n_tilde * home_len) + 1));
	strcpy(new_str, split[0]);
	y = 0;
	while (split[++y])
	{
		strcat(new_str, home);
		n_tilde--;
		strcat(new_str,  split[y]);
	}
	if (n_tilde)
		strcat(new_str, home);
	free_double_str(split);
	free(split);
	free(shell->input_str);
	shell->input_str = new_str;
}

void shift_tokens_up(t_shell *shell, int index, int size) {
    
	int i;

	i = index;
	free(shell->tokens[index].token);

    while (i < size) {
        shell->tokens[i].token = shell->tokens[i + 1].token;
		i++;
    }

    shell->tokens[size - 1].token = NULL;
}



int		get_tokens_len(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->tokens[i].token)
		i++;
	return (i);
}

void	expander_single_quotes(t_shell *shell)
{
	int i;
	int first_i;
	int first_flag;
	char *first_string;
	char *token_str;
	char *new_str;

	i = -1;
	first_flag = 0;
	first_string = NULL;
	while (shell->tokens[++i].token)
	{
		token_str = shell->tokens[i].token;
		if (first_flag == 0 && (ft_strchr(token_str, '\'') != NULL))
		{
			first_string = token_str;
			first_i = i;
			shell->tokens[i].type = WORD;
			first_flag = 1;
		}
		else if (first_flag == 1)
		{
			new_str = malloc(sizeof(char) * (ft_strlen(first_string) + ft_strlen(token_str) + 2));
			strcpy(new_str, first_string);
			strcat(new_str, " ");
			strcat(new_str, token_str);
			free(shell->tokens[first_i].token);
			shell->tokens[first_i].token = new_str;
			first_string = shell->tokens[first_i].token;
			if ((ft_strchr(token_str, '\'') != NULL))
				first_flag = 0;
			shift_tokens_up(shell, i, get_tokens_len(shell));
			i--;
		}
	}
}

char *get_word_from_token(char *str, int start)
{
	int end;
	int x;
	char *env;
	
	start = start + 1;
	end = start;
	while (str[end] && str[end] != ' ' && str[end] != '\"' && str[end] != '\'')
		end++;
	env = malloc(sizeof(char) * ((end - start) + 1));
	x = 0;
	while (start < end)
	{
		env[x] = str[start];
		start++;
		x++;
	}
	env[x] = '\0';
	return (env);
}

void push_val_into_str(char *str, char *val, char *var, int pos)
{
	int x;
	int new_len;
	char *new_str;
	
	x = -1;
	new_len = ft_strlen(str) - ft_strlen(var) + ft_strlen(val);
	new_str = malloc(sizeof(char) * (new_len + 1));
	while (++x < pos)
		new_str[x] = str[x];
	while (str[pos] && str[pos] != ' ' && str[pos] != '\"' && str[pos] != '\'')
		pos++;
	new_str[x] = '\0';
	strcat(new_str, val);
	x = x + ft_strlen(val);
	while (str[pos])
	{
		new_str[x] = str[pos];
		x++;
		pos++;
	}
	new_str[x] = '\0';
	strcpy(str, new_str);
	free(new_str);
}

void get_rid_of_quotes(char *str)
{
    int x = 0;
    int y = 0;

    while (str[x])
    {
        if (str[x] != '\'' && str[x] != '\"')
        {
            str[y] = str[x];
            y++;
        }
        x++;
    }
    str[y] = '\0';
}


void token_str_expander(t_shell *shell, char *str)
{
	int x;
	int sq_flag;
	char *env;
	char *val;

	x = 0;
	sq_flag = 0;
	while (str[x])
	{
		if (sq_flag == 1 && str[x] == '\'')
			sq_flag = 0;
		if (str[x] == '\'')
			sq_flag = 1;
		if (str[x] == '$' && sq_flag != 1)
		{
			env = get_word_from_token(str, x);
			if (is_in_env(shell, env) == 1)
			{
				val = env_get_val(shell, env);
				push_val_into_str(str, val, env, x);
			}
			free(env);
		}
		x++;
	}
	get_rid_of_quotes(str);
}


void value_expander(t_shell *shell)
{
	int i;
	char *token_str;

	i = -1;
	while (shell->tokens[++i].token)
	{
		token_str = shell->tokens[i].token;
		if (ft_strchr(token_str, '\"') != NULL || ft_strchr(token_str, '\'') != NULL)
			token_str_expander(shell, token_str);
	}
	
}

void	expander_quotes(t_shell *shell)
{
	int i;
	int first_i;
	int first_flag;
	char *first_string;
	char *token_str;
	char *new_str;

	i = -1;
	first_flag = 0;
	first_string = NULL;
	while (shell->tokens[++i].token)
	{
		token_str = shell->tokens[i].token;
		if (first_flag == 0 && (ft_strchr(token_str, '\"') != NULL))
		{
			first_string = token_str;
			first_i = i;
			shell->tokens[i].type = WORD;
			first_flag = 1;
		}
		else if (first_flag == 1)
		{
			new_str = malloc(sizeof(char) * (ft_strlen(first_string) + ft_strlen(token_str) + 2));
			strcpy(new_str, first_string);
			strcat(new_str, " ");
			strcat(new_str, token_str);
			free(shell->tokens[first_i].token);
			shell->tokens[first_i].token = new_str;
			first_string = shell->tokens[first_i].token;
			if ((ft_strchr(token_str, '\"') != NULL))
				first_flag = 0;
			shift_tokens_up(shell, i, get_tokens_len(shell));
			i--;
		}
	}
	expander_single_quotes(shell);
	value_expander(shell);
}