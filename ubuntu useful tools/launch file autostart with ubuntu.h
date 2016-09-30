ros/ubuntu开机自启动节点

1.首先安装robot_upstart工具（以indigo版本为例）  
    sudo apt-get install ros-indigo-robot-upstart  

2. 把要启动打节点放入start.launch（自命名）内,如navigation/launch/start.launch
   然后运行以下命令
    rosrun robot_upstart install navigation/launch/start.launch  

 3. 启动服务

    sudo service robot start   

电脑重启即可

--若出现问题，可以查看日志
    sudo gedit /var/log/upstart/robot.log   

---服务停止

    sudo service robot stop   


---卸载自启动

    rosrun robot_upstart uninstall robot  