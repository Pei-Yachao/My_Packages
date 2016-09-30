echo "install ros-indigo-desktop-full"
sudo apt-get install ros-indigo-desktop-full -y

sudo sh -c "rosdep init"
rosdep update
. /opt/ros/indigo/setup.sh

echo "[rosdep init and python-rosinstall]"
sudo apt-get install python-rosinstall

echo "[Making the catkin workspace and testing the catkin_make]"
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ~/catkin_ws/
catkin_make

echo "[Setting the ROS evironment]"
sh -c "echo \"source /opt/ros/indigo/setup.bash\" >> ~/.bashrc"
sh -c "echo \"source ~/catkin_ws/devel/setup.bash\" >> ~/.bashrc"
sh -c "echo \"export ROS_MASTER_URI=http://localhost:11311\" >> ~/.bashrc"
sh -c "echo \"export ROS_HOSTNAME=localhost\" >> ~/.bashrc"


sudo apt-get install ssh -y
sudo apt-get install ros-indigo-urg-node -y
sudo apt-get install ros-indigo-hokuyo-node -y

sudo apt-get install ros-indigo-gmapping -y
sudo apt-get install ros-indigo-navigation -y
sudo apt-get install ros-indigo-kobuki* -y
sudo apt-get install ros-indigo-openni2* -y
sudo apt-get install ros-indigo-freenect* -y

sudo apt-get install chrony -y
sudo ntpdate -q ntp.ubuntu.com


sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/colomboem/xUbuntu_14.04/ /' >> /etc/apt/sources.list.d/dukto.list"
sudo apt-get update
sudo apt-get install dukto

echo "[Complete!!!]"

exec bash

exit 0

