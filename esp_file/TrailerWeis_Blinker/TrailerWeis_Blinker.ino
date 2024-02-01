#include <micro_ros_arduino.h>

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <geometry_msgs/msg/twist.h>

rcl_subscription_t subscriber;
geometry_msgs__msg__Twist msg;
rclc_executor_t executor;
rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;


#define RH_RGB_ROT_PIN 19
#define RH_RGB_GRUEN_PIN 18
#define RH_RGB_BLAU_PIN 5

#define LH_RGB_ROT_PIN 0
#define LH_RGB_GRUEN_PIN 2
#define LH_RGB_BLAU_PIN 15

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}

void error_loop() {
  while (1) {
    digitalWrite(RH_RGB_BLAU_PIN, !digitalRead(RH_RGB_BLAU_PIN));
    digitalWrite(LH_RGB_BLAU_PIN, !digitalRead(LH_RGB_BLAU_PIN));
    delay(100);
  }
}

//twist message cb
void subscription_callback(const void *msgin) {
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
  // if velocity in x direction is 0 turn off LED, if 1 turn on LEDl
  // digitalWrite(LED_PIN, (msg->angular.z == 0) ? LOW : HIGH);

  // if (msg->angular.z < 0.2)

  int8_t value = 0;

  if (msg->angular.z == 0.0 )
  {
    value = 0;
  }

  else if (msg->angular.z <= 0.2)
  {
    value = 10; // leuchte Rechts
  }
  else if (msg->angular.z >= -0.2)
  {
    value = 11; // leuchte Links
  }

  // else if (msg->linear.x <= 0.2)
  // {
  //   value = 3; // Vorwärts
  // }
  // else if (msg->linear.x >= -0.2)
  // {
  //   value = 13; // Rückwärts
  // }


  switch (value) {
    case 0: // Alle Aus
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 1: // Rot Rechts
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 2:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 3: // Alle Rot
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 4: // Gruen Rechts
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 5:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 6: // Alle Gruen
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 7: // Blau Rechts
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, HIGH);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 8:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, HIGH);
      break;
    case 9: // Alle Blau
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, HIGH);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, HIGH);
      break;
    case 10: // Gelb Rechts
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      
      delay(100);
      
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      
      delay(100);      
      break;
    case 11: // Gelb Links
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);

      delay(100);

      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);

      delay(100);      
      break;
    case 12: // Alle Gelb
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 13: // Alle Weiss
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, HIGH);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, HIGH);
      break;
    default:
      break;
  }
}

void setup() {
  // set_microros_transports();
  set_microros_wifi_transports("FRITZ!Box 7490", "XXX", "192.168.178.86", 8888);
  pinMode(RH_RGB_ROT_PIN, OUTPUT);
  pinMode(RH_RGB_GRUEN_PIN, OUTPUT);
  pinMode(RH_RGB_BLAU_PIN, OUTPUT);

  pinMode(LH_RGB_ROT_PIN, OUTPUT);
  pinMode(LH_RGB_GRUEN_PIN, OUTPUT);
  pinMode(LH_RGB_BLAU_PIN, OUTPUT);


  digitalWrite(RH_RGB_ROT_PIN, LOW);
  digitalWrite(RH_RGB_GRUEN_PIN, LOW);
  digitalWrite(RH_RGB_BLAU_PIN, LOW);

  digitalWrite(LH_RGB_ROT_PIN, LOW);
  digitalWrite(LH_RGB_GRUEN_PIN, LOW);
  digitalWrite(LH_RGB_BLAU_PIN, LOW);

  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "trailer_blinker", "", &support));

  // create subscriber
  RCCHECK(rclc_subscription_init_default(
            &subscriber,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
            "leo_driver/cmd_vel_unstamped"));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));

}

void loop() {
  delay(100);
  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}
