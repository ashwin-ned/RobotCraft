#!/usr/bin/env bash

rostopic pub /Jeff/cmd_vel geometry_msgs/Twist "linear:
  x: 50.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0" 
