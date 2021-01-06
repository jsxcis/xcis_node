void sendMessage(String outgoing, uint8_t from)
{
  //digitalWrite(LORA_SEND, HIGH);
  uint8_t data[32];
  outgoing.toCharArray(data,sizeof(data));
  if (manager->sendtoWait(data, sizeof(data), from) != RH_ROUTER_ERROR_NONE)
  {
    
      Serial.println(F("sendtoWait failed"));
  
  }

  //digitalWrite(LORA_SEND, LOW);
}
