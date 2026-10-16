/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabani-h <mabani-h@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:40:03 by mabani-h          #+#    #+#             */
/*   Updated: 2026/10/16 15:38:33 by mabani-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char	*data;
	size_t	length;
	size_t	capacity;
}	t_buffer;

char	*get_next_line(int fd);
int		ft_has_newline(const char *str);
char	*extract_line(t_buffer *state);
void	consume_line(t_buffer *state);
void	clear_state(t_buffer *state);

#endif
