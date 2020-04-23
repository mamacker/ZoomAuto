#!/bin/bash
export DISPLAY=:0.0
export XAUTHORITY=/run/user/1001/gdm/Xauthority
window=$(wmctrl -l | grep "Meet -" | awk '{print $1}')
wmctrl -i -a $window
window=$(wmctrl -l | grep "Zoom Meeting" | awk '{print $1}')
wmctrl -i -a $window
