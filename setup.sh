#!/bin/bash

set -x

if [[ "$(whoami)" != "root" ]]; then
    echo "ERROR: You must run this script with root permission!"
    exit 1
fi

# Build main.c
make

cp -fv main /usr/local/bin/shutdown_timer

cp -fv ./com.timer.shutdown.plist /Library/LaunchDaemons/

launchctl bootstrap system /Library/LaunchDaemons/com.timer.shutdown.plist
