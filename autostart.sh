#!/bin/bash

#fcitx5 & # I will not use it untill he fixed it
xset r rate 250 100

autostart="dwmblocks dunst picom"
for prog in $autostart; do
  pidof -sx prog || "$prog" &
done >/dev/null 2>&1

#togglemon
[[ -f ${XDG_DATE_HOME:-$HOME/.local/share}/bg ]] &&
  setbg ${XDG_DATE_HOME:-$HOME/.local/share}/bg &
