#!/bin/bash

WALL_PAPER=~/Pictures/Wallpaper/banner.png

dwmblocks 2>&1 > /dev/null &
fcitx5 &
picom &
togglemon
feh --bg-scale $WALL_PAPER &
