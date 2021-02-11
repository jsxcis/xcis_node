bool onReceive()
{
  uint8_t buf[32];
  uint8_t len = sizeof(buf);
  uint8_t from;
  if (manager->recvfromAck(buf, &len, &from))
  {
    //Serial.println((char*)buf);
    // Assume message is for me.
    digitalWrite(A2,0); 
    String response = "ID=04,Name=Rosedale4,Value=" + String(distance) + ",";
    Serial.println(response);
    sendMessage(response, from);
    digitalWrite(A2,1);
  }
  return true;
}
