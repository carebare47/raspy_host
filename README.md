# raspy_host
Test on raspberry pi OS lite - Linux raspberrypi 5.4.83+
clone to ~/
run script in setup folder
resulting executable is "raspy_host/src/raspy_host" 
add something to /etc/rc.local (before "exit 0") that does something like:
```
cur_dir=$(pwd)
cd /home/pi/raspy_host/src
sudo ./raspy_host &
cd $cur_dir
```
