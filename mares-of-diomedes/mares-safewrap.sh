#!/bin/sh

# --------------------------------------------
#    User Options
# --------------------------------------------

# Seconds to timeout
TIMEOUT=30

# Seconds to wait for the new mares to be tamed
TIMEOUT_GMARES=30

# --------------------------------------------
#    Initialize
# --------------------------------------------

# Set up signal handling in case mares.sh completed its task
sigusr1_received=false
catch_sigusr1 () { sigusr1_received=true ;}
trap catch_sigusr1 USR1

sigusr2_received=false
catch_sigusr2 () { sigusr2_received=true ;}
trap catch_sigusr2 USR2

TIMEOUT_SEQ=$(seq $TIMEOUT)
TIMEOUT_SEQ_GMARES=$(seq $TIMEOUT_GMARES)

# --------------------------------------------
#    Start Script and Wait
# --------------------------------------------

echo "Running mares.sh quietly. Will force kill after $TIMEOUT seconds."

sh mares.sh > /dev/null 2>&1 &

for i in $TIMEOUT_SEQ
do
	echo "    $i"
	echo "\033[2A"
	sleep 1
done

# --------------------------------------------
#    Determine if script was successful
# --------------------------------------------

if $sigusr1_received
then
	echo "mares.sh successfully captured the horses."
else
	echo "mares.sh has not completed its task. Killing now."
	ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
	if ! [ -z "$ARGS" ]
	then
		kill -s KILL $ARGS
	fi
	
	ARGS=$(top -l 1 | grep manger | awk '{print $1}')
	if ! [ -z "$ARGS" ]
	then
		kill -s KILL $ARGS
	fi
	
	ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
	if ! [ -z "$ARGS" ]
	then
		kill -s KILL $ARGS
	fi

	kill $! 2>/dev/null

	rm -f *.poo
	
	exit 0
fi

# --------------------------------------------
#    Wait for the new mares to be tamed
# --------------------------------------------

echo "Waiting an additional $TIMEOUT_GMARES seconds for the new mares to be tamed."

for i in $TIMEOUT_SEQ_GMARES
do
	echo "    $i"
	echo "\033[2A"
	sleep 1
done

if $sigusr2_received
then
	echo "mares.sh successfully tamed the new horses."
else
	echo "mares.sh has not completed its task. Killing now."
	ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
	if ! [ -z "$ARGS" ]
	then
		kill -s KILL $ARGS
	fi
	
	ARGS=$(top -l 1 | grep manger | awk '{print $1}')
	if ! [ -z "$ARGS" ]
	then
		kill -s KILL $ARGS
	fi
	
	ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
	if ! [ -z "$ARGS" ]
	then
		kill -s KILL $ARGS
	fi

	kill $! 2>/dev/null

	rm -f *.poo
	
	exit 0
fi

# --------------------------------------------
#    Perform final flush of all processes
# --------------------------------------------

ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
fi

ARGS=$(top -l 1 | grep manger | awk '{print $1}')
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
fi

ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
fi

kill $! 2>/dev/null

rm -f *.poo
