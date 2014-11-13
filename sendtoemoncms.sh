	
#!/bin/sh
 
### BEGIN INIT INFO
# Provides:          sendtoemoncms
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Put a short description of the service here
# Description:       Put a long description of the service here
### END INIT INFO
 
# Change the next 3 lines to suit where you install your script and what you want to call it
DIR=/var/www/RaspiRF24Pyton
DAEMON=$DIR/sendtoemoncms.py
DAEMON_NAME=sendtoemoncms
 
# Add any command line options for your daemon here
DAEMON_OPTS=""

 
# This next line determines what user the script runs as.
# Root generally not recommended but necessary if you are using the Raspberry Pi GPIO from Python.
DAEMON_USER="pi"

# Exit if the package is not installed
[ -x "$DAEMON" ] || echo "Not starting - cannot find $DAEMON" || exit 1
 
# The process ID of the script when it runs is stored here:
PIDFILE=/var/run/$DAEMON_NAME.pid

SCRIPTNAME=/etc/init.d/$DEMON_NAME 

. /lib/lsb/init-functions
. /lib/init/vars.sh
VERBOSE=yes
 
do_start() {
	do_status
	case "$?" in
		0)	return 1 ;;
		1) 	rm -f $PIDFILE;;
		3)	;;
		4)	PID=`ps -ef | grep '[p]ython '$DAEMON | awk '{ print $2 }'`
			echo "$PID" > $PIDFILE;;
		*)	return "$?" ;;
	esac
	start-stop-daemon --start --quiet --background --make-pidfile --chuid=$DAEMONUSER --pidfile $PIDFILE --startas $DAEMON --test > /dev/null \
		|| return 1
	start-stop-daemon --start --quiet --background --no-close --make-pidfile --chuid=$DAEMONUSER --pidfile $PIDFILE --startas $DAEMON -- \
		$DAEMON_ARGS \
		|| return 2
	# Add code here, if necessary, that waits for the process to be ready
	# to handle requests from services started subsequently which depend
	# on this one.  As a last resort, sleep for some time.
}


# Function that stops the daemon/service
#
do_stop() {
	do_status
	case "$?" in
		0)	;;
		1) 	rm -f $PIDFILE;;
		3) 	return 1 ;;
		4)	PID=`ps -ef | grep '[p]ython '$DAEMON | awk '{ print $2 }'`
			echo "$PID" > $PIDFILE;;
		*)	return "$?" ;;
	esac
	start-stop-daemon --stop --quiet --retry=INT/30/KILL/5 --pidfile $PIDFILE >/dev/null || RETVAL="$?"
	[ "$RETVAL" = 2 ] && return 2
	rm -f $PIDFILE
	return "$?"
}


do_status() {
	status="0"
    	pidofproc -p $PIDFILE $DAEMON >/dev/null || status="$?"
	if [ "$status" = 3 ]; then
		pid=`ps -ef | grep '[p]ython '$DAEMON | awk '{ print $2 }'`
		[ "$pid" != "" ] && return 4
	fi
	return $status
}
 
case "$1" in
 
    start|stop)
        do_${1}
        ;;
 
    restart|reload|force-reload)
        do_stop
        do_start
        ;;
 
    status)
        status_of_proc "$DAEMON_NAME" "$DAEMON" && exit 0 || exit $?
        ;;
    *)
        echo "Usage: /etc/init.d/$DAEMON_NAME {start|stop|restart|status}"
        exit 1
        ;;
esac
exit 0
