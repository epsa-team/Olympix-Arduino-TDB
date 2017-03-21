// Pour l'écran LCD
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>



                   //--------------------------LCD-----------------------------------//
                   
//Initialisation de l'écran LCD

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, 43, 41, 40, 38); // R0-R2 pour inverser la rotation
// point (x=0,y=0) => en haut à gauche
uint8_t draw_state = 0;
int Pos_pap = 11;
int Temp = 90;
int Rapport = 2;
int RPM = 2500;
//Initialise le LCD
void InitDraw(void){
  u8g2.setFont(u8g2_font_ncenB14_tr); // B08 10 12 14 18 24 ... taille
}

//Choix d'affichage
void draw(void) {
  InitDraw();
  switch(draw_state) {
    case 0: DrawIntro(); break;
    case 1: DrawInterface1(); break;
  
  }
}

void DrawIntro(void){
  u8g2.setFont(u8g2_font_ncenB18_tr);
  u8g2.drawStr(8,36,"Olympix");
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFont(u8g2_font_u8glib_4_tf);
  u8g2.drawStr(45,56,"produit par"); // (20,37) = (x,y)
  u8g2.drawStr(1,62,"Sihsson et Jules et wills haral pierre feuille ciseau");
}






    
//lcd
void DrawInterface1(void){
  u8g2.drawLine(60,0,60,64);
  u8g2.drawLine(0,30,128,30);

  //Partie gauche
  u8g2.setFont(u8g2_font_u8glib_4_tf); // B10 taille minimale
  u8g2.drawStr(20,6,"Rapport");
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(25,26,String(Rapport).c_str());
  u8g2.setFont(u8g2_font_u8glib_4_tf);
  u8g2.drawStr(28,38,"RPM");
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(9,60,String(RPM).c_str());
 

  // Partie droite
  u8g2.setFont(u8g2_font_u8glib_4_tf);
  u8g2.drawStr(72,6,"Temperature");
  u8g2.setFont(u8g2_font_ncenB14_tr); // B10 taille minimale
  u8g2.drawStr(75,24,String(Temp).c_str());
  u8g2.drawStr(110,24,"C");
  u8g2.setFont(u8g2_font_u8glib_4_tf);
  u8g2.drawStr(82,38,"Papillon");
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(78,60,String(Pos_pap).c_str());
  u8g2.drawStr(110,60,"%");
  //u8g2.drawStr(70,64,millis().c_str())

}
                   //--------------------------LCD-----------------------------------//





void setup(void) {
  u8g2.begin(); //LCD
  Serial.begin(9600);
}





void loop(void) {
  Serial.print(draw_state);
                   //--------------------------LCD-----------------------------------//
  // picture loop  
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() ); // on envoie les donnée jusque ce que tout soit arrivé
  
  // utile pour la page d'affichage
  if ( draw_state == 0)
    {
    delay(2000); // 2 sec d'intro
    draw_state = 1;
    }
  // delay between each page
  delay(1000);
                   //--------------------------LCD-----------------------------------//


              
}

