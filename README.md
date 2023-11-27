Overview
* [Notes](#Note)
* [Installation](#Installation)
## Note , I Use Noto Nerd Fonts That Can Be Downloaded From [Here](https://nerdfonts.com)
## Installation
* To Install Them On Your, System You Need To Go In These Files And Do a

```
sudo make install
```

* E.g , Build dwm

```
cd dwm-6.4 && sudo make install
```

* After You've Built The Suckless apps , We Need To Install Some Dependencies

```
sudo pacman -S xorg xorg-apps
```

* After Installing them , Then you need to add 'exec dwm' to your ~/.xinitrc , or if you don't have it then copy mine to ~/

```
cp xinitrc ~/
```

* After finishing the xinitrc, you need to close any 'XWindowManager'
* this Means to stop sddm/gdm/lightdm (Whatever Your using)

```
sudo systemctl stop sddm / gdm / lightdm
```
* Or To Disable Them permanently
```
sudo systemctl disable sddm / gdm / lightdm
```
* Finally when your in the tty , execute

```
startx
```

* It Should Drop you in dwm , Done
