void readDataStream()
{

  Serial.println(F("readDataStream()"));
  digitalWrite(A1,1);
  unsigned char data[4]={};
  unsigned char incomingByte = 0;
  int byteCount = 0;
  bool foundPacket = false;
  while (usonic.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = usonic.read();
    if (incomingByte == 0xFF)
    {
      //Serial.println("Found start");
      data[0] = incomingByte;
      byteCount++;
      while (usonic.available() > 0) {
        data[byteCount] = usonic.read();
        byteCount++;
        if (byteCount > 3)
        {
          foundPacket = true;
          break;
        }
      }
    }
    if (foundPacket)
        break;
  }
  usonic.flush();

  if(data[0]==0xff)
  {
    int sum;
    sum=(data[0]+data[1]+data[2])&0x00FF;
    if(sum==data[3])
    {
        distance=(data[1]<<8)+data[2];
    }
    else 
    {
      Serial.println(F("ERROR"));
    }
  }
  digitalWrite(A1,0);

}
