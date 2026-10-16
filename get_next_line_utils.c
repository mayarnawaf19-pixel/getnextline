/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabani-h <mabani-h@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:31:57 by mabani-h          #+#    #+#             */
/*   Updated: 2026/10/16 14:32:11 by mabani-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_has_newline(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_line(t_buffer *state)
{
	char	*line;
	size_t	size;
	size_t	i;

	if (state->length == 0)
		return (NULL);
	size = 0;
	while (size < state->length && state->data[size] != '\n')
		size++;
	if (size < state->length && state->data[size] == '\n')
		size++;
	line = malloc(size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < size)
	{
		line[i] = state->data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	consume_line(t_buffer *state)
{
	size_t	size;
	size_t	i;

	size = 0;
	while (size < state->length && state->data[size] != '\n')
		size++;
	if (size < state->length && state->data[size] == '\n')
		size++;
	i = 0;
	while (size + i < state->length)
	{
		state->data[i] = state->data[size + i];
		i++;
	}
	state->length = i;
	if (state->data)
		state->data[i] = '\0';
}

void	clear_state(t_buffer *state)
{
	free(state->data);
	state->data = NULL;
	state->length = 0;
	state->capacity = 0;
}
