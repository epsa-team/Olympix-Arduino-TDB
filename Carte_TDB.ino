// Pour l'écran LCD
#include <Arduino.h>


#include <D:\Cours\epsa\arduino\global\Carte TDB\_2emetest\U8g2lib.h>
#include <SPI.h>
#include <Wire.h>



                    ///// LCD /////
//Initialisation de l'écran LCD

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, 13, 11, 10, 8); // R0-R2 pour inverser la rotation
// point (x=0,y=0) => en haut à gauche
uint8_t draw_state = 0;
int Pos_pap = 11;
int Temp = 99;
int Rapport = 2;
int RPM = 2500;
static unsigned char logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x28, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xCC, 0x40, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x7E, 0x60, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7C, 0xE3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x70, 0x06, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x12, 0x00, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x7D, 0x00, 0x1C, 
  0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
  0x80, 0xFF, 0x00, 0x38, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1F, 0x00, 0x00, 0x00, 0x00, 0xCE, 0x19, 0xB8, 0x0D, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x77, 0x00, 0x00, 0x00, 0x00, 0x67, 0x0B, 0x38, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xE0, 0x00, 0x00, 0x40, 
  0xC0, 0x61, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 
  0x60, 0x00, 0x00, 0x40, 0x60, 0x70, 0x03, 0x21, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0xE0, 0x00, 0x00, 0x06, 0x00, 0xF0, 0x00, 0xE3, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x70, 0x00, 0x61, 0x1C, 
  0x02, 0x90, 0xD9, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x30, 0x00, 0xA3, 0x05, 0x00, 0x00, 0x10, 0x80, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x30, 0x00, 0xD0, 0x05, 0x08, 0x00, 0xCE, 0x98, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0C, 0x00, 0xC0, 0x18, 
  0x08, 0x00, 0xD8, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x13, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x32, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x40, 0x18, 
  0x03, 0x02, 0x20, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xC8, 0xC0, 0x19, 0x01, 0x00, 0x80, 0x6F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1E, 0x78, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x23, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x7C, 0x00, 0x20, 
  0x08, 0x00, 0xC0, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xF8, 0x24, 0x00, 0x3C, 0x18, 0x18, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x0E, 0x79, 0x08, 0xF0, 0x0E, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x23, 
  0x33, 0x08, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x99, 0xC0, 0x61, 0x02, 0x3B, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x1D, 0xE3, 0x11, 0x08, 0x1C, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x08, 0x81, 0x39, 
  0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0xB0, 0x11, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x01, 0x20, 0xF0, 0x00, 0x00, 0x18, 0x04, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x70, 0xF0, 0x00, 
  0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 
  0x04, 0x10, 0x30, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x0C, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x08, 0x03, 
  0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCE, 0x00, 0x80, 0x03, 
  0x00, 0x30, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x00, 0x00, 0x0E, 0x0E, 0x7C, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x34, 0x06, 0xF0, 0x79, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x20, 
  0x00, 0x80, 0xE7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x10, 0x20, 0x40, 0x0A, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x40, 0xCE, 0x00, 0x39, 0x00, 0x00, 0x9E, 0x20, 
  0xC0, 0x0F, 0x87, 0x08, 0xE0, 0x81, 0x81, 0x1F, 0x60, 0x06, 0x04, 0x18, 
  0x00, 0x03, 0x8E, 0x78, 0x00, 0x0C, 0xC3, 0xCC, 0xE0, 0x00, 0x03, 0x0F, 
  0x60, 0x86, 0x0F, 0x1B, 0x70, 0xE0, 0x8F, 0x49, 0x10, 0x08, 0xE3, 0x8C, 
  0xB8, 0x61, 0x06, 0x07, 0xFC, 0x80, 0x0B, 0x01, 0xF0, 0x6C, 0x83, 0x18, 
  0xE0, 0x0C, 0x03, 0x1C, 0x98, 0x00, 0x87, 0x07, 0x1C, 0x80, 0x3B, 0x63, 
  0xC0, 0x1F, 0x83, 0x30, 0x60, 0x1C, 0x18, 0x00, 0x88, 0x01, 0xC7, 0x01, 
  0x1C, 0x00, 0x13, 0x3B, 0xC0, 0x4D, 0x80, 0xC7, 0x63, 0x08, 0x7C, 0xC0, 
  0xD8, 0x01, 0x06, 0x00, 0x04, 0x00, 0x30, 0x3B, 0x00, 0x60, 0x80, 0xCF, 
  0x07, 0x18, 0xEF, 0xF0, 0xE8, 0x00, 0x18, 0x00, 0x40, 0x00, 0x10, 0x33, 
  0x00, 0x00, 0x80, 0x1D, 0x03, 0x18, 0x00, 0x78, 0xF8, 0x01, 0x70, 0x00, 
  0x40, 0x80, 0x30, 0x33, 0x00, 0x06, 0x00, 0x0E, 0x07, 0x09, 0x01, 0x27, 
  0xC8, 0x01, 0x70, 0x00, 0x20, 0xE0, 0x00, 0x78, 0x00, 0x3A, 0x00, 0x98, 
  0x9E, 0x01, 0x0E, 0x02, 0x18, 0xC0, 0xE0, 0x01, 0x40, 0x72, 0x0C, 0xB8, 
  0x65, 0x66, 0x80, 0x09, 0x80, 0x0B, 0x01, 0x00, 0x88, 0xE0, 0x83, 0x01, 
  0xD0, 0x71, 0x0C, 0xCF, 0x27, 0x7C, 0x80, 0x03, 0x00, 0x09, 0x23, 0x00, 
  0xD8, 0x31, 0x83, 0x0D, 0x60, 0x32, 0x00, 0x8F, 0x63, 0x3C, 0x80, 0x07, 
  0x80, 0x0D, 0x3F, 0x00, 0xC8, 0x00, 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, };

 
//Initialise le LCD
void InitDraw(void){
  u8g2.setFont(u8g2_font_ncenB14_tr); // B08 10 12 14 18 24 ... taille
}

//Choix d'affichage
void draw(void) {
  InitDraw();
  switch(draw_state) {
    case 0: DrawIntro(); break;
    case 1: DrawIntro2(); break;
    case 2: DrawInterface1(); break;
  
  }
}
// lcd
void DrawIntro(void){
    u8g2.setColorIndex(1);
    u8g2.drawXBM( 0, 0, 128, 64, logo); //x,y, largeur,hauteur, bitmap
}
//lcd
void DrawIntro2(void){
  u8g2.setFont(u8g2_font_ncenB18_tr);
  u8g2.drawStr(8,36,"Olympix");
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFont(u8g2_font_u8glib_4_tf);
  u8g2.drawStr(45,56,"produit par"); // (20,37) = (x,y)
  u8g2.drawStr(35,62,"Sihsson et Jules et wills haral pierre feuille ciseau");
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
               ///// LCD /////






void setup(void) {
  u8g2.begin(); //LCD
}

void loop(void) {

                ///// LCD /////
  // picture loop  
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  
  // increase the state
  if ( draw_state == 0)
    {delay(2000);
    draw_state = 1;
    }
   else
   if (draw_state == 1)
   {delay(2000);
    draw_state = 2;
    }
  // delay between each page
  delay(1000);
              ///// LCD /////


              
}


