#!/bin/bash

dwmblocks 2>&1 > /dev/null &
#fcitx5 & # I will not use it untill he fixed it
picom &
xset r rate 250 100
togglemon
