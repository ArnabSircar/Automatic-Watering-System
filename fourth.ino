#include<dht.h>

int soilPin=A4,soilVal,rainPin=A1,rainVal,dhtPin=A7,outPin=7;
bool watering;

dht DHT;      // Creates a DHT object

void setup() {
  Serial.begin(9600);
  pinMode(rainPin,INPUT);
  pinMode(soilPin,INPUT);
  pinMode(outPin,OUTPUT);
  digitalWrite(outPin,LOW);
  watering=0;
}

void loop() {
  int readData = DHT.read11(dhtPin);

  int t = DHT.temperature;  // Read temperature
  int h = DHT.humidity;   // Read humidity

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("°C | ");
  Serial.print((t*9.0)/5.0+32.0); // Convert celsius to fahrenheit
  Serial.println("°F ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println("% ");
  Serial.println("");

  rainVal=analogRead(rainPin);
  Serial.print("RainVal = ");
  Serial.println(rainVal);
  Serial.println("");

  soilVal=analogRead(soilPin);
  Serial.print("Soil MoistureVal = ");
  Serial.println(soilVal);
  Serial.println("");

  int soillevel=700,rainlevel=700,tlevel=27,hlevel=40;

  if(rainVal<rainlevel) // raining
  {
    digitalWrite(outPin,HIGH);
    Serial.print("Brishti porche tai ");
    watering=0;
  }
  else
  {
    if(soilVal<soillevel) /// matite pani ase
    {
      digitalWrite(outPin,HIGH);
      Serial.print("Matite pani beshi tai ");
      watering=0;
    }
    else
    {
      if(t>tlevel)
      {
        digitalWrite(outPin,LOW); /// tap beshi
        Serial.print("Abohawa er tap beshi tai ");
        watering=1;
      }
      else if(h<hlevel)
      {
        digitalWrite(outPin,LOW); /// adrota kom
        Serial.print("Abohawa er adrota kom tai ");
        watering=1;
      }
      else
      {
        digitalWrite(outPin,HIGH);
        Serial.print("Abohawa er tap kom ebong adrota beshi tai ");
        watering=0;
      }
    }
  }

  if(watering)
  {
    Serial.println("Pani porche");
  }
  else
  {
    Serial.println("Ber hocche na");
  }
  
  Serial.println("-----------------------------------------");
  Serial.println("");

  delay(500); // wait two seconds
}
