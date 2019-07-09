#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    boar.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/22 13:56:46 by gfielder          #+#    #+#              #
#    Updated: 2019/03/22 13:56:46 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TOTAL_LINES=38
LINE_START=19
LINE_END=19

the_code() {
touch helloworld.txt
}

# Make sure the user is root
EFFECTIVE_USER=`id -u | tr -d ' '`
if [ $EFFECTIVE_USER -ne 0 ]
then
	echo "This script must be run as root."
	exit 1
fi

# install, using -y to automatically answer yes to any prompt
# If at is already installed, this won't do anything
# We don't need to see the output, so redirect to /dev/null
apt-get install -y at > /dev/null

TAIL_LINES=$(($TOTAL_LINES - $LINE_START + 1))
HEAD_LINES=$(($LINE_END - $LINE_START + 1))
cat $0 | tail -n $TAIL_LINES | head -n $HEAD_LINES > "$(dirname $0)/scheduled"
at -f "$(dirname $0)/scheduled" 08:42 AM 12/21/2019
