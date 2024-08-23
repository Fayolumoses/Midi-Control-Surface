#include "include/MyLib.h"
#include "include/Sev_Seg.h"
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "MIDIUSB.h"
#include <semphr.h>

SemaphoreHandle_t mutex;

Analog_Multiplexer plex(SIG, EN, S_0, S_1, S_2, S_3);
Input_Channel channels[TOTAL_NO_CHANNELS];
Segment seg(SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,SEG_DP);

QueueHandle_t structQueue;

int midi_channel;
int pot_bank[TOTAL_NO_CHANNELS] = {0};
int fader_bank[TOTAL_NO_CHANNELS] = {0};


void setup() {
  // put your setup code here, to run once:
  plex.begin();
  midi_channel = 1;
  Serial.begin(9600);
  seg.begin(COMMON_CATHODE);
  setup_channels(channels, plex);
  structQueue = xQueueCreate(10, sizeof(midiEventPacket_t));

  mutex = xSemaphoreCreateMutex();
  if (mutex == NULL) {
    while(1){delay(1);}
  }

  if (structQueue == NULL) {
    while(1){
      delay(1);
    }
  }
    
    xTaskCreate(midi_transmit, 
                "Midi Transmit",
                128,
                NULL, 
                2, 
                NULL);

    xTaskCreate(bank_selector,
                "LeftnRight",
                128,
                NULL, 
                1,
                NULL);

    xTaskCreate(pots,
                "pots",
                128,
                NULL, 
                1,
                NULL);
    
}

void loop() {
  // put your main code here, to run repeatedly
}

void pots(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {

    for(int i = 0; i < 6; i++){
      int p = channels[midi_channel + i].get_pot();
      int f = channels[midi_channel + i].get_fader();
      if(p <= pot_bank [midi_channel + i] - 2 ||  p >= pot_bank [midi_channel + i] + 2 ){
        midiEventPacket_t midi_pot = {0x0B, 0xB0 | get_channel(), channels[midi_channel + i].get_pot_control(), p};
        xQueueSend(structQueue, &midi_pot, portMAX_DELAY);

        pot_bank [midi_channel + i] = p;
      }

      if(f <= fader_bank [midi_channel + i] - 2 || f >= fader_bank [midi_channel + i] + 2 ){
        midiEventPacket_t midi_fader = {0x0B, 0xB0 | get_channel(), channels[midi_channel + i].get_fader_control(), f}; 
        xQueueSend(structQueue, &midi_fader, portMAX_DELAY);

        fader_bank[midi_channel + i] = f;
      }
    }


    vTaskDelay(1);
  }
}

int get_channel(){
  int ret = 1;
  if (xSemaphoreTake(mutex, 10) == pdTRUE){
    ret = midi_channel;
  }
  xSemaphoreGive(mutex);
  return ret;
}

void set_channel(int toSet){
  if (xSemaphoreTake(mutex, 10) == pdTRUE){
    midi_channel = toSet;
  }
  xSemaphoreGive(mutex);
}

void bank_selector(void *pvParameters)
{
  (void) pvParameters;
  int c;
  for (;;)
  {
    c = get_channel();
    disp_channel(c);
    seg.display(c);

    if (get_button_pressed(plex) == B_PREV){
      (c == 1)? set_channel(16): set_channel(c - 1);
      delay(500);
    }
    else if (get_button_pressed(plex) == B_NEXT){
      (c == 16)? set_channel(1): set_channel(c + 1);
      delay(500);
    }

    vTaskDelay(1);
  }
}




void midi_transmit(void *pvParameters)
{
  (void) pvParameters;
  midiEventPacket_t midi_event;
  for (;;)
  {
    if (xQueueReceive(structQueue, &midi_event, portMAX_DELAY)) {
      MidiUSB.sendMIDI(midi_event); 
      MidiUSB.flush();
    }
  }
}


