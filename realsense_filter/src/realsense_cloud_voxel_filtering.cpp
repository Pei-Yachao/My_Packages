/*
Purpose of node: subscribe to a point cloud, use a VoxelGrid filter on it with a setting that
clobbers voxels with fewer than a threshold of points.
*/

#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <iostream>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
typedef pcl::PointXYZ PointXYZ;

class FilterAndPublish
{
    public:
        FilterAndPublish()
        {
            printf("Made object\n");
            pub = nh.advertise<PointCloud> ("filtered_points", 1);
            sub = nh.subscribe<PointCloud>("depth_points", 1, &FilterAndPublish::callback, this);
            this->thresh = 15; // This is the minimum number of points that have to occupy a voxel in order for it to survive the downsample.
        }

        void callback(const PointCloud::ConstPtr& msg)
        {
            PointCloud::Ptr cloud (new PointCloud);
            PointCloud::Ptr cloud_passThrough (new PointCloud);
            PointCloud::Ptr vox_cloud (new PointCloud);
            *cloud = *msg;

            // What to do here: 
            // 1. Take cloud and put it in a voxel grid while restricting the bounding box
            // 2. Go through the voxels and remove all points in a voxel that has less than this.thresh points
            // 3. Publish resulting cloud

            
            pcl::PassThrough<PointXYZ> pth;
            pth.setInputCloud(cloud);
            // The leaf size is the size of voxels pretty much. Note that this value affects what a good threshold value would be.
            
            // I limit the overall volume being considered so lots of "far away" data that is just terrible doesn't even have to be considered.
            pth.setFilterLimits(-1.0, 1.0);
            // The line below is perhaps the most important as it reduces ghost points.
           // pth.setMinimumPointsNumberPerVoxel(this->thresh);
            pth.filter(*cloud_passThrough);
            
            pcl::VoxelGrid<PointXYZ> vox;
            
            vox.setInputCloud(cloud_passThrough);
            vox.setLeafSize(0.01f, 0.1f, 0.01f);
            vox.setFilterLimits(-1.0, 1.0);
            vox.filter(*vox_cloud);
            
            pub.publish (vox_cloud);
        }

    private:
        ros::NodeHandle nh;
        ros::Publisher pub;
        ros::Subscriber sub;
        int thresh;

};


int main(int argc, char** argv)
{
    ros::init(argc, argv, "voxel_filter");
    FilterAndPublish f = FilterAndPublish();
    ros::spin();
    return 0;
}