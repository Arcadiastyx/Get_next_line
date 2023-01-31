/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:27:17 by inaranjo          #+#    #+#             */
/*   Updated: 2022/11/28 14:46:05 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*extract_line(char *reserve)
{
	int		i;
	char	*str_line;

	/*si aucune info trouver dans reserve alors out=NULL*/
	i = 0;
	if (!reserve[i])
		return (NULL);
	/* tant que tu es dans reserve et que index de reserve
	 * n est pas equivalant a un retour a la ligne
	 * alors verifie son contenu*/
	while (reserve[i] && reserve[i] != '\n')
		i++;
	/* allocation de memoire pour line qui va prendre le contenue
	 * dans la reserve
	 * si probleme d-allocation alors error = null*/
	str_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!str_line)
		return (NULL);
	/* tant que tu es dans reserve[index] et que tu n-est aps
	 * equivalant a retour a la ligne..continue la loop
	 * la memoire reserver par line va prendre la valeur de reserver*/
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
	{
		str_line[i] = reserve[i];
		i++;
	}
	/*si l info dans reserve[index] et egal a retour a la ligne
	 * alors cree une nouvelle ligne avec les valeur de reserve*/
	if (reserve[i] == '\n')
	{
		str_line[i] = reserve[i];
		i++;
	}
	/*si tu as tout lu la str alors donne sa valeur*/
	str_line[i] = '\0';
	return (str_line);
}

char	*m_reserve(char *reserve)
{
	int	i;
	int	nbytes;
	char	*str_res;

	/*tant que tu es dans reserve et reserve nest pas equivalant a '\n'
	 * verifie son contenue
	 * si tu ne trouves rien alors sort et libere l espace allouer*/
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i])
	{
		free(reserve);
		return (NULL);
	}
	/*espace allouer pour la reserve, si rien n a pu etre allouer Error=libere*/
	str_res = (char *)malloc(sizeof(char) * (ft_strlen(reserve) - i + 1));
	if (!str_res)
	{
		free(str_res);
		return (NULL);
	}
	i++;
	/*tant que tu est dans la reserve a l-index 0 :
	 * alors l espace allouer a la reserve
	 * prend la valeur du param entre dans la reserve
	 * si la valeur = '\0' alors :
	 *  libere la reserve
	 *  et donne moi le contenue du malloc str*/
	nbytes = 0;
	while (reserve[i])
		str_res[nbytes++] = reserve[i++];
	str_res[nbytes] = '\0';
	free(reserve);
	return (str_res);
}


char	*buff_read_add_to_res(int fd, char *reserve)
{
	char	*buff;
	int		nbyte_read;

	/* malloc buff,selon taille definie + gestion error*/
	buff = malloc((BUFFER_SIZE + 1 ) * sizeof(char));
	if (!buff)
		return (NULL);
	nbyte_read = 1;
	/*tant que tu n est pas = '\n' et si nbyte n est pas equivalant a 0
	 *(dans le cas contraire libere + return reserve)
	 * si non alors : read le fichier.
	 * si prob avec read alors libere l espace utilise
	 * si non et que tu te trouves a '\0'
	 * alor add to reserve*/
	while (!ft_strchr(reserve, '\n') && nbyte_read != 0)
	{
		nbyte_read = read(fd, buff, BUFFER_SIZE);
		if (nbyte_read == -1)
		{
			free(buff);
			free(reserve);
			return (NULL);
		}
		buff[nbyte_read] = '\0';
		reserve = ft_strjoin(reserve, buff);
	}
	free(buff);
	return (reserve);
}

char *get_next_line(int fd)
{
	char		*line;
	static char	*reserve;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	reserve = buff_read_add_to_res(fd, reserve);
	if (!reserve)
		return (NULL);
	line = extract_line(reserve);
	reserve = m_reserve(reserve);
	return (line);
}
