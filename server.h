/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 12:36:29 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/05/28 12:37:29 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include <stddef.h>

typedef struct	s_message
{
	unsigned char	bits;
	size_t			bitcounter;
}				t_message;

#endif
