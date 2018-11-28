void readColor() // Renk okuma algoritması
{
  tcs.getRawData(&red, &green, &blue, &clearr); // renk sensöründen gelen değerleri al

  avarage = (red + green + blue) / 3; // renk değerlerini topla ve ortalamasını al
  r = red / avarage; // kırmızı renk değeri oranı
  g = green / avarage; // yeşil renk değeri oranı
  b = blue / avarage; // mavi renk değeri oranı
}

void printColor() // Renk gösterme algoritması
{
  Serial.print("red  :  ");
  Serial.println(r);

  Serial.print("blue  :  ");
  Serial.println(b);

  Serial.print("green  :  ");
  Serial.println(g);

  if ((r > 1) && (g < 1.15) && (b < 1.1)) { // kırmızı renk olma durumu
    Serial.println("RED");
  }
  else if ((r < 0.82) && (g > 1.2) && (b < 1.08)) {  // yeşil renk olma durumu
    Serial.println("GREEN");
  }
  else if ((r < 0.78) && (g < 1.25) && (b > 1)) { // mavi renk olma durumu
    Serial.println("BLUE");
  }
  else if ((r < 1.30) && (g < 1.25) && (b < 0.85)) { // mavi renk olma durumu
    Serial.println("YELLOW");
  }
  else { // tanımlı renkler değilse
    Serial.println("NO COLOR DETECTED");
  }
}

int findColor(){
  for (int i = 0; i < 7; i++) {
        if ((r_[i] - 0.04 < r) && (r < r_[i] + 0.04) && (g_[i] - 0.04 < g) && (g < g_[i] + 0.04) && (b_[i] - 0.04 < b) && (b < b_[i] + 0.04)) {
          controlColor=true;
          r_[i]=0;
          g_[i]=0;
          b_[i]=0;

         return i;
        }
      }
}


