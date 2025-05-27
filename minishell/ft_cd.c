/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/05/27 15:50:07 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args)
{
    if (!args[1] || strcmp(args[1], "~") == 0)
    {
        char *home = getenv("HOME");
        if (home && chdir(home) != 0)
        {
            perror("cd");
            return -1;
        }
    }
    else if (chdir(args[1]) != 0)
    {
        perror("cd");
        return -1;
    }
    return 0;
}
