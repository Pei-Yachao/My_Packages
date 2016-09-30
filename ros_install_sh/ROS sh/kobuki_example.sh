sudo apt-get install python-rosinstall -y
sudo apt-get install chrony -y
sudo ntpdate -q ntp.ubuntu.com

cd ~/catkin_ws/src
git clone https://github.com/irvs/rosbook_kobuki.git
cd ~/catkin_ws && catkin_make
