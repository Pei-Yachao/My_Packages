echo "[Update & upgrade the package]"
sudo apt-get update -qq
sudo apt-get upgrade -qq

sudo update-locale LANG=C LANGUAGE=C LC_ALL=C LC_MESSAGES=POSIX

echo "[Installing chrony and setting the ntpdate]"
sudo apt-get install -y chrony
sudo ntpdate ntp.ubuntu.com

sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu trusty main" > /etc/apt/sources.list.d/ros-latest.list'

echo "[Set up your ROS keys]"
wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add -

echo "[Update & upgrade the package]"
sudo apt-get update -qq
sudo apt-get upgrade -qq

echo "[Installing ROS]"
sudo apt-get install ros-indigo-ros-base -y

echo "[rosdep init and python-rosinstall]"
sudo apt-get install python-rosdep -qq 
sudo sh -c "rosdep init"
rosdep update
. /opt/ros/indigo/setup.sh
sudo apt-get install -y python-rosinstall 

echo "[Making the catkin workspace and testing the catkin_make]"
sudo apt-get install build-essential -y
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ~/catkin_ws/
catkin_make

echo "[Setting the ROS evironment]"
sh -c "echo \"source /opt/ros/indigo/setup.bash\" >> ~/.bashrc"
sh -c "echo \"source ~/catkin_ws/devel/setup.bash\" >> ~/.bashrc"

echo "[Complete!!!]"

sudo apt-get install ros-indigo-urg-node -y
sudo apt-get install ros-indigo-hokuyo-node -y
sudo apt-get install ros-indigo-kobuki ros-indigo-kobuki-core -y
sudo apt-get install ssh -y
sudo apt-get install ros-indigo-openni2-launch ros-indigo-openni2-camera -y

exec bash

exit 0

