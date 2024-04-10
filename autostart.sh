#!/bin/bash

dwmblocks 2>&1 > /dev/null &
#fcitx5 & # I will not use it untill he fixed it
picom &
dunst &
xset r rate 250 100
#togglemon
[[ -f ${XDG_DATE_HOME:-$HOME/.local/share}/bg ]] &&
  setbg ${XDG_DATE_HOME:-$HOME/.local/share}/bg &
