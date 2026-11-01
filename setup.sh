#!/bin/bash

set -x

if [[ "$(whoami)" != "root" ]]; then
    echo "ERROR: You must run this script with root permission!"
    exit 1
fi

# Build main.c
make

if [[ "$?" != 0 ]]; then
    exit 1
fi

cp -fv main /usr/local/bin/shutdown_timer

PLIST_FILE=/Library/LaunchDaemons/com.timer.shutdown.plist
cp -fv ./com.timer.shutdown.plist ${PLIST_FILE}

launchctl bootstrap system ${PLIST_FILE}
launchctl kickstart -k system/com.timer.shutdown

echo "SUCCESS"
