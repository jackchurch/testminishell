/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:46:42 by jmarks            #+#    #+#             */
/*   Updated: 2023/05/01 15:58:11 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	int		execFlag;
	char	input[MAXCOM];
	char	*parsedArgs[MAXLIST];

	execFlag = 0;
	(void)ac;
	(void)av;
	while (1)
	{
		takeInput(input);
		execFlag = process_input(input, parsedArgs);
		if (execFlag == 1)
			execmd(parsedArgs);
	}
	return (EXIT_SUCCESS);
}
