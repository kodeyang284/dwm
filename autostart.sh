#!/bin/bash

dwmblocks 2>&1 > /dev/null &
fcitx5 &
picom &
sleep 2
togglemon
xset r rate 250 100
