#include "set.h"

void setup() {
  //--------------------------------------------------------------
  File_system_init();
  Serial.println("SPIFFS_init");
  //--------------------------------------------------------------
  CMD_init();
  Serial.println("[V] CMD_init");
  //--------------------------------------------------------------
  All_init();
  Serial.println("[V] All_init");
  //--------------------------------------------------------------
  WIFI_init();
  Serial.println("[V] WIFI_init");
  //--------------------------------------------------------------
  statistics_init();
  Serial.println("[V] statistics_init");
  //--------------------------------------------------------------
  initUpgrade();
  Serial.println("[V] initUpgrade");
  //--------------------------------------------------------------
  Web_server_init();
  Serial.println("[V] Web_server_init");
  //--------------------------------------------------------------
  MQTT_init();
  Serial.println("[V] MQTT_init");
  //--------------------------------------------------------------
  Time_Init();
  Serial.println("[V] Time_Init");
  //--------------------------------------------------------------
  Push_init();
  Serial.println("[V] Push_init");
  //--------------------------------------------------------------
  SSDP_init();
  Serial.println("[V] SSDP_init");
  //--------------------------------------------------------------

  ts.add(TEST, 10000, [&](void*) {
    getMemoryLoad("[i] periodic check of");
  }, nullptr, true);

  just_load = false;
}


void loop() {

#ifdef OTA_enable
  ArduinoOTA.handle();
#endif

#ifdef WS_enable
  ws.cleanupClients();
#endif

  handleMQTT();

  handle_connection();
  handle_get_url();

  handleCMD_loop();
  handleButton();
  handleScenario();

  ts.update();
  handle_upgrade();
}
