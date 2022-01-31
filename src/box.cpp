#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>

#include <pcl/filters/crop_box.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
pcl::CropBox<pcl::PointXYZ> box;
PointCloud cloud_out;

ros::Publisher pub;

void callback(const PointCloud::ConstPtr& msg)
{
    printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);
    // BOOST_FOREACH (const pcl::PointXYZ& pt, msg->points)
    //     printf ("\t(%f, %f, %f)\n", pt.x, pt.y, pt.z);

    box.setInputCloud(msg);
    box.filter(cloud_out);

    pub.publish(cloud_out);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sub_pcl");
  ros::NodeHandle nh;
  box = pcl::CropBox<pcl::PointXYZ>(true);

  Eigen::Vector4f min_pt (1.0f, 1.0f, 1.0f, 1.0f);
  Eigen::Vector4f max_pt (2.0f, 2.0f, 2.0f, 1.0f);
  box.setMin (min_pt);
  box.setMax (max_pt);
  
  pub = nh.advertise<PointCloud>("filtered", 1);
  ros::Subscriber sub = nh.subscribe<PointCloud>("points2", 1, callback);
  ros::spin();
}