// #include <ros/ros.h>
// #include <pcl_ros/CropBoxConfig.h>
// #include <sensor_msgs/PointCloud2.h>
// #include <pcl/point_types.h>
// #include <pcl/point_cloud.h>
// #include <pcl_conversions/pcl_conversions.h>

// pcl::PointCloud<pcl::PointXYZ> my_cloud;
// ros::Publisher pub;
// void callback(const sensor_msgs::PointCloud2::ConstPtr &msg)
// {
//     pcl::PCLPointCloud2 pcl_pc2;
//     pcl_conversions::toPCL(*msg, pcl_pc2);
//     pcl::fromPCLPointCloud2(pcl_pc2, my_cloud);
//     ROS_INFO("Converted");
//     pub.publish(my_cloud);
// }

// int main(int argc, char **argv)
// {
//     ros::init (argc, argv, "sub_pcl");
//     ros::NodeHandle nh;
//     pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ>>("new_points", 1);
//     ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2>("points2", 1, callback);

//     ros::spin();

//     // sensor_msgs::PointCloud2 test;
// }

#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

int main(int argc, char** argv)
{
  ros::init (argc, argv, "pub_pcl");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<PointCloud> ("points2", 1);

  PointCloud::Ptr msg (new PointCloud);
  msg->header.frame_id = "map";
  msg->height = 3;
  msg->width = 100;


  for (float i=-5.0f; i< 5.0f; i+=1.0f)
  {
      for (float j=-5.0f; j< 5.0f; j+=1.0f)
      {
          for (float k=0.0f; k< 3.0f; k+=1.0f)
          {
            msg->points.push_back (pcl::PointXYZ(i, j, k));
          }
      }
  }

  ros::Rate loop_rate(4);
  while (nh.ok())
  {
    pcl_conversions::toPCL(ros::Time::now(), msg->header.stamp);
    pub.publish (msg);
    ros::spinOnce ();
    loop_rate.sleep ();
  }
}