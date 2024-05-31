#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
#define LED_BUILTIN 2

static const int led_pin = LED_BUILTIN;

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
int UserDelay = 20;


void toggleLED(void *parameter)
{
  while(1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); // 500 ms
    digitalWrite(led_pin, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void startTask2(void *parameter) {
  while (1) {
    
    UserDelay = Serial.read(); 
     if (Serial.available() > 0){
    Serial.print('*');
    Serial.println(20);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
   xTaskCreatePinnedToCore(
            toggleLED,
            "Toggle LED",
            1024,
            NULL,
            1,
            &task_1,
            app_cpu);
  
  xTaskCreatePinnedToCore(startTask2,
                          "Task 2",
                          1024,
                          NULL,
                          2,
                          &task_2,
                          app_cpu);
}

void loop() {
 
}