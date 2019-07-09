#!/bin/sh

# ----------------------------------------------
#    User Options
# ----------------------------------------------

# Head start to give the original manger
HEAD_START=20

# Head start to give the new manger
HEAD_START_GMARES=20

# Time given to enjoy the new mares
LIVE_TIME=30

# ----------------------------------------------
#    Initialization
# ----------------------------------------------

LIVE_TIME_SEQ=$(seq $LIVE_TIME)

# ----------------------------------------------
#    Start The original manger
# ----------------------------------------------

cp manger.orig manger
chmod +x manger
./manger &

# ----------------------------------------------
#    Give manger a head start and then kill it
# ----------------------------------------------

sleep $HEAD_START

# Kill the subprocesses to allow room for the top command
ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
fi

# Find all the main processes and kill them
ARGS=$(top -l 1 | grep manger | awk '{print $1}')
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
fi

# If the main processes started any new subprocesses in the meantime, kill them too
ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
fi

rm -f *.poo

# ----------------------------------------------
#    Transition
# ----------------------------------------------

echo ""
echo ""
echo ""
echo "Hercules has captured the horses!"
echo "These horses, however, are not good enough for Eurystheus."
echo "Hercules finds a new herd..."

# If this was started from the safe wrapper, signal step 1 completed successfully
PARENT_PROCESS=$(ps -a | grep -e "^$PPID" | cut -c 26-)
if [ "$PARENT_PROCESS" = "sh mares-safewrap.sh" ] || [ "$PARENT_PROCESS" = "./mares-safewrap.sh" ]
then
	kill -s USR1 $PPID
fi

sleep 2

# ----------------------------------------------
#    Run the new manger
# ----------------------------------------------

gcc -o manger gmanger.c
./manger &

# Wait a bit
sleep $HEAD_START_GMARES

# Tame the horses. ABRT is a core image dump signal, and as such, is food
ARGS=$(pgrep manger)
if ! [ -z "$ARGS" ]
then
	kill -s ABRT $ARGS
fi

# If this was started from the safe wrapper, signal step 2 completed successfully
PARENT_PROCESS=$(ps -a | grep -e "^$PPID" | cut -c 26-)
if [ "$PARENT_PROCESS" = "sh mares-safewrap.sh" ] || [ "$PARENT_PROCESS" = "./mares-safewrap.sh" ]
then
	kill -s USR2 $PPID
fi

# Feed the horses while we enjoy them
for i in $LIVE_TIME_SEQ
do
	ARGS=$(pgrep manger)
	if ! [ -z "$ARGS" ]
	then
		kill -s ABRT $ARGS
	fi
	sleep 1
done

# Send alarm signal to let horses know their time is up
echo ""
echo ""
echo "Eurystheus is pleased with the horses, and they have passed their time of magnificence."
echo ""
ARGS=$(pgrep manger)
if ! [ -z "$ARGS" ]
then
	kill -s ALRM $ARGS
fi
echo ""

# ----------------------------------------------
#    Cleanup in case anything was missed
# ----------------------------------------------

#Wait some more time and kill any remaining, just to be sure
#LIVE_TIME=10
#sleep $LIVE_TIME

if [ -z "$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)" ]
then
	if [ -z "$(top -l 1 | grep manger | awk '{print $1}')" ]
	then
		exit 0
	fi
fi

LIVE_TIME=5
echo "Something may be wrong. Waiting $LIVE_TIME seconds to make sure..."
sleep $LIVE_TIME

ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
	echo "1: There was some remaining to kill. You have some work to do."
fi
ARGS=$(top -l 1 | grep manger | awk '{print $1}')
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
	echo "2: There was some remaining to kill. You have some work to do."
fi
ARGS=$(pgrep manger crap lampon xanthos yes podargos deinos tame_lampon tame_xanthos tame_podargos)
if ! [ -z "$ARGS" ]
then
	kill -s KILL $ARGS
	echo "3: There was some remaining to kill. You have some work to do."
fi
