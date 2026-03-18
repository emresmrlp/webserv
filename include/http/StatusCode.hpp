/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:39:52 by ysumeral          #+#    #+#             */
/*   Updated: 2026/03/18 15:05:08 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUSCODE_HPP
# define STATUSCODE_HPP

enum StatusCode
{
    OK = 200,
    NOT_FOUND = 404,
    BAD_REQUEST = 400,
    HTTP_VERSION_NOT_SUPPORTED = 505,
    INCOMPLETE = 0 // TODO: TEST DELETE THIS
};

#endif