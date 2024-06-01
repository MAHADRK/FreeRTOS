#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
#define LED_BUILTIN 2

static const int led_pin = LED_BUILTIN;

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
static uint32_t  UserDelay= 500 ;


void startTask1(void *parameter){
  while(1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(UserDelay / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(UserDelay / portTICK_PERIOD_MS);
  }
}

void startTask2(void *parameter) {
  while (1) {
    if (Serial.available() > 0) {
        UserDelay = Serial.parseInt();
        Serial.print("Update Value of Delay: ");
        Serial.println(UserDelay);
        }
    }
}

void setup() {

  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Multi-task LED Demo");
  Serial.println("Enter a number in milliseconds to change the LED delay.");
  pinMode(led_pin, OUTPUT);
    xTaskCreatePinnedToCore(startTask1,
                          "Task 1",
                          1024,
                          NULL,
                          1,
                          &task_1,
                          app_cpu);

  // Task to run once with higher priority
  xTaskCreatePinnedToCore(startTask2,
                          "Task 2",
                          1024,
                          NULL,
                          1,
                          &task_2,
                          app_cpu);

  // Delete "setup and loop" task
 // vTaskDelete(NULL);
}

void loop() {
   }
