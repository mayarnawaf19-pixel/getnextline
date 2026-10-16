/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabani-h <mabani-h@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:39:18 by mabani-h          #+#    #+#             */
/*   Updated: 2026/10/16 14:39:27 by mabani-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	next_capacity(size_t current, size_t needed)
{
	if (current == 0)
		current = 64;
	while (current < needed)
	{
		if (current > (size_t)-1 / 2)
			return (needed);
		current *= 2;
	}
	return (current);
}

static int	reserve_buffer(t_buffer *state, size_t needed)
{
	char	*new_data;
	size_t	new_capacity;
	size_t	i;

	if (needed <= state->capacity)
		return (0);
	new_capacity = next_capacity(state->capacity, needed);
	new_data = malloc(new_capacity);
	if (!new_data)
		return (-1);
	i = 0;
	while (i < state->length)
	{
		new_data[i] = state->data[i];
		i++;
	}
	new_data[state->length] = '\0';
	free(state->data);
	state->data = new_data;
	state->capacity = new_capacity;
	return (0);
}

static int	append_data(t_buffer *state, char *src, size_t size)
{
	size_t	i;

	if (reserve_buffer(state, state->length + size + 1) < 0)
		return (-1);
	i = 0;
	while (i < size)
	{
		state->data[state->length + i] = src[i];
		i++;
	}
	state->length += size;
	state->data[state->length] = '\0';
	return (0);
}

static int	read_until_newline(int fd, t_buffer *state)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = 1;
	while (!ft_has_newline(state->data) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), -1);
		if (bytes > 0
			&& append_data(state, buffer, (size_t)bytes) < 0)
			return (free(buffer), -1);
	}
	free(buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer	state = {NULL, 0, 0};
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_until_newline(fd, &state) < 0)
		return (clear_state(&state), NULL);
	if (state.length == 0)
		return (clear_state(&state), NULL);
	line = extract_line(&state);
	if (!line)
		return (clear_state(&state), NULL);
	consume_line(&state);
	return (line);
}
