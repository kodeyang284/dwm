#!/bin/bash

dwmblocks 2>&1 > /dev/null &
fcitx5 &
picom &
xset r rate 250 100
togglemon1
