Overview
* [Notes](#Note)
* [Installation](#Installation)
## on Fedora Linux Install Said Packages , These Are Deps for compiling this repo , if their not met, the compile Will fail
```
sudo dnf install LibX11-devel LibXft-devel LibXinerama-devel LibXrandr-devel
```
## Samething On Arch Linux , Install this package To Be Able To Compile Things
```
sudo pacman -S base-devel
```
## Installation
* To Install Them On Your, System You Need To Go In These Files And Do a.
```
sudo make install
```
* E.g , Build dwm.
```
cd dwm-6.4 && sudo make install
```
* After You've Built The Suckless apps , We Need To Install Some Dependencies.
```
sudo pacman -S xorg xorg-apps xorg-xinit nitrogen xclip noto-fonts-extra rofi polkit-kde-agent
git clone https://aur.archlinux.org/paru-bin.git
makepkg -si
paru -S picom-git
```
* For Fedora Uses These.
```
sudo dnf install rofi xclip picom
```
* After Installing them , Then you need to add 'exec dwm' to your ~/.xinitrc , or if you don't have it then copy mine to ~/.
```
cp xinitrc ~/
```
* And You need to copy .Xresources to ~/ as well for the font size (you cant change it if you like , 128 works well for my screen).
```
cp .Xresources ~/
```
* And Copy the "eniornment" file to make every gtk3 app be in dark mode.
```
sudo cp environment /etc/
```
* After finishing them, you need to close any 'XWindowManager'.
* this Means to stop sddm/gdm/lightdm. (Whatever Your using)
```
sudo systemctl stop sddm / gdm / lightdm
```
* Or To Disable Them permanently.
```
sudo systemctl disable sddm / gdm / lightdm
```
* Finally when your in the tty , execute.

```
startx
```
* If you want to make dwm start every time you login into tty automaticly , then but this in your [.bashrc] if your using bash, or [.zshrc] if your using zsh.
* Credit to [Freedom Coder](https://www.youtube.com/@freedomcoder) for this script.
```
if [ -z "${DISPLAY}" ] && [ "${XDG_VTNR}" -eq 1 ]; then
  exec startx
fi
```
* It Should Drop you in dwm , Enjoy.
