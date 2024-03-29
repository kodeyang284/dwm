#!/bin/bash

dwmblocks 2>&1 > /dev/null &
#fcitx5 & # I will not use it untill he fixed it
picom &
sleep 2
xset r rate 250 100
togglemon
