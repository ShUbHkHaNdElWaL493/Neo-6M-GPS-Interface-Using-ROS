#include <ros.h>
#include <sensor_msgs/NavSatFix.h>
// #include <std_msgs/Float64.h>
#include <TinyGPS++.h>

/*
  Connect RX pin to PA2.
  Connect TX pin to PA3.
*/

ros::NodeHandle nh_gps;

sensor_msgs::NavSatFix msg;
// std_msgs::Float64 latitude;
// std_msgs::Float64 longitude;
// std_msgs::Float64 altitude;
ros::Publisher gps_data_publisher("gps_data", &msg);
// ros::Publisher latitude_publisher("gps_data_latitude", &latitude);
// ros::Publisher longitude_publisher("gps_data_longitude", &longitude);
// ros::Publisher altitude_publisher("gps_data_altitude", &altitude);

TinyGPSPlus gps;

void setup()
{
  Serial2.begin(9600);
  nh_gps.initNode();
  nh_gps.advertise(gps_data_publisher);
  // nh_gps.advertise(latitude_publisher);
  // nh_gps.advertise(longitude_publisher);
  // nh_gps.advertise(altitude_publisher);
}

void loop()
{
  if (Serial2.available())
  {
    gps.encode(Serial2.read());
    if (gps.location.isValid())
    {
      // Serial.write(Serial2.read());
      // Serial.print("Latitude: ");
      // Serial.println(gps.location.lat());
      // Serial.print("Longitude: ");
      // Serial.println(gps.location.lng());
      // Serial.print("Altitude: ");
      // Serial.println(gps.altitude.meters());
      msg.latitude = gps.location.lat();
      msg.longitude = gps.location.lng();
      msg.altitude = gps.altitude.meters();
      // latitude.data = gps.location.lat();
      // longitude.data = gps.location.lng();
      // altitude.data = gps.altitude.meters();
      gps_data_publisher.publish(&msg);
      // latitude_publisher.publish(&latitude);
      // longitude_publisher.publish(&longitude);
      // altitude_publisher.publish(&altitude);
    }
  }
  nh_gps.spinOnce();
}