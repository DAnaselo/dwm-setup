#!/bin/sh

userresources=$HOME/.Xresources

# merge in defaults and keymaps

if [ -f "$userresources" ]; then
    xrdb -merge "$userresources"
fi

exec xclip &
exec flameshot &
exec /usr/lib/polkit-kde-authentication-agent-1 &
exec dwm
