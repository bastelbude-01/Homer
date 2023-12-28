#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int8.h>

rcl_subscription_t LEDs_subscriber;
std_msgs__msg__Int8 LEDs_msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// Define individual pins for each LED group
#define RH_RGB_ROT_PIN 19
#define RH_RGB_GRUEN_PIN 18
#define RH_RGB_BLAU_PIN 5

#define MID_RGB_ROT_PIN 17
#define MID_RGB_GRUEN_PIN 16
#define MID_RGB_BLAU_PIN 4

#define LH_RGB_ROT_PIN 0
#define LH_RGB_GRUEN_PIN 2
#define LH_RGB_BLAU_PIN 15

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

unsigned long previousMillis = 0;
const long interval = 100; // Milliseconds

bool flash_r_running = false;
bool flash_l_running = false;


void error_loop() {
  while (1) {
    digitalWrite(RH_RGB_BLAU_PIN, !digitalRead(RH_RGB_BLAU_PIN));
    digitalWrite(LH_RGB_BLAU_PIN, !digitalRead(LH_RGB_BLAU_PIN));
    delay(100);
  }
}

void flash_right()
{
  flash_r_running = true;
  unsigned long start_time = millis();

  while (millis() - start_time <= 500) {
    for (pos = 0; pos <= 10; pos += 1) {
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      delay(15);
    }
    for (pos = 10; pos >= 0; pos -= 1) {
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      delay(15);
      delay(15);
    }
  }
}

void flash_left()
{
  flash_l_running = true;
  unsigned long start_time = millis();

  while (millis() - start_time <= 500) {
    for (pos = 0; pos <= 10; pos += 1) {
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      delay(15);
    }
    for (pos = 10; pos >= 0; pos -= 1) {
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      delay(15);
    }
  }
}

void rgb(int value)
{
  switch (value) {
    case 0: // Alle Aus
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 1: // Rot Rechts
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 2:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, HIGH);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 3:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 4: // Alle Rot
      digitalWrite(RH_RGB_ROT_PIN, HIGH);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, HIGH);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, HIGH);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 5: // Gruen Rechts
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 6:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, HIGH);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 7:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 8: // Alle Gruen
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, HIGH);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, HIGH);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 9: // Blau Rechts
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, HIGH);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 10:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, HIGH);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, LOW);
      break;
    case 11:
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, LOW);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, LOW);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, HIGH);
      break;
    case 12: // Alle Blau
      digitalWrite(RH_RGB_ROT_PIN, LOW);
      digitalWrite(RH_RGB_GRUEN_PIN, LOW);
      digitalWrite(RH_RGB_BLAU_PIN, HIGH);

      digitalWrite(MID_RGB_ROT_PIN, LOW);
      digitalWrite(MID_RGB_GRUEN_PIN, LOW);
      digitalWrite(MID_RGB_BLAU_PIN, HIGH);

      digitalWrite(LH_RGB_ROT_PIN, LOW);
      digitalWrite(LH_RGB_GRUEN_PIN, LOW);
      digitalWrite(LH_RGB_BLAU_PIN, HIGH);
      break;
    case 13: // Gelb Rechts
      flash_right();
      break;
    case 14: // Gelb Links
      flash_left();
      break;
    default:
      break;
  }
}
void rgb_cmdvel_callback(const void *msgin) {
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;

  int8_t value = 0;

  if (msg->angular.z == 0.0 )
  {
    value = 0;
    rgb(value);
  }

  else if (msg->angular.z <= 0.2)
  {
    value = 13;
    rgb(value);
  }
  else if (msg->angular.z >= -0.2)
  {
    value = 14;
    rgb(value);
  }

}

void setup() {
  // set_microros_transports();
  set_microros_wifi_transports("FRITZ!Box 7490", "54908635459129454475", "192.168.178.45", 8888); // port 8888 is ip 79 - port 8889 is ip 82

  pinMode(RH_RGB_ROT_PIN, OUTPUT);
  pinMode(RH_RGB_GRUEN_PIN, OUTPUT);
  pinMode(RH_RGB_BLAU_PIN, OUTPUT);

  pinMode(MID_RGB_ROT_PIN, OUTPUT);
  pinMode(MID_RGB_GRUEN_PIN, OUTPUT);
  pinMode(MID_RGB_BLAU_PIN, OUTPUT);

  pinMode(LH_RGB_ROT_PIN, OUTPUT);
  pinMode(LH_RGB_GRUEN_PIN, OUTPUT);
  pinMode(LH_RGB_BLAU_PIN, OUTPUT);

  digitalWrite(RH_RGB_ROT_PIN, LOW);
  digitalWrite(RH_RGB_GRUEN_PIN, LOW);
  digitalWrite(RH_RGB_BLAU_PIN, LOW);

  digitalWrite(MID_RGB_ROT_PIN, LOW);
  digitalWrite(MID_RGB_GRUEN_PIN, LOW);
  digitalWrite(MID_RGB_BLAU_PIN, LOW);

  digitalWrite(LH_RGB_ROT_PIN, LOW);
  digitalWrite(LH_RGB_GRUEN_PIN, LOW);
  digitalWrite(LH_RGB_BLAU_PIN, LOW);

  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "led_subscriber", "", &support));

  // create subscriber
  RCCHECK(rclc_subscription_init_default(
            &LEDs_subscriber,
            &node,
            ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int8),
            "/LEDs"));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &LEDs_subscriber, &LEDs_msg, &LEDs_callback, ON_NEW_DATA));
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
  }
}
