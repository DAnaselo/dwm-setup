# This Is An Overview Of My dwm Setup
Note , I Use Noto Nerd Fonts That Can Be Downloaded From [Here](https://nerdfonts.com)
# Installation
To Install Them On Your, System You Need To Go In These Files And Do a 'sudo make install'.
E.g , If you want to build dwm you go inside of "dwm-6.4" and do a 'sudo make install' in dwm-6.4 folder.
After You've Built The Suckless apps you need to add 'exec dwm' to your ~/.xinitrc , or if you don't have it (Then you probably don't have the Dependinces for it so 'sudo pacman -S xorg xorg-apps' *That command runs only runs in archlinux) then copy mine to $HOME so you do 'cp xinitrc $HOME'.
After finishing the xinitrc, you need to close any 'XWindowManager' this Means to stop sddm/gdm/lightdm (Whatever Your using) You Do that by doing 'sudo systemctl stop sddm/gdm/lightdm, then do 'startx'.
