//
//    rDUINOScope - Arduino based telescope control system (GOTO).
//    Copyright (C) 2016 Dessislav Gouzgounov (Desso)
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    PROJECT Website: http://rduinoscope.byethost24.com
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// ......................................................................
//  This part of the code take care of:
//  - Handles ALL TOUCH SCREEN Inputs;
//  - Screens are separated like:
//    * CURRENT_SCREEN==0  - drawGPSScreen() Where the GPS coordinates are displayed
//    * CURRENT_SCREEN==1  - drawClockScreen() Captures updates on the time and date
//    * CURRENT_SCREEN==2  -                - not used
//    * CURRENT_SCREEN==3  - Select Alignment method (only have 3 buttons)
//    * CURRENT_SCREEN==4  - drawMainScreen() Captures all clicks on the MAIN Screen of the application
//    * CURRENT_SCREEN==5  - drawCoordinatesScreen() Only have "back" button
//    * CURRENT_SCREEN==6  - drawLoadScreen() Captures input on Load screen (all of them: Messier && Treasurres)
//    * CURRENT_SCREEN==7  - drawOptionsScreen()
//    * CURRENT_SCREEN==8  -  drawMountCalScreen()
//    * CURRENT_SCREEN==9  -                - not used
//    * CURRENT_SCREEN==10  - drawSTATScreen()
//    * CURRENT_SCREEN==11  - drawStarMap()
//    * CURRENT_SCREEN==12  - drawStarSyncScreen() - To Select Alignment Star;
//    * CURRENT_SCREEN==13  - drawConstelationScreen(int indx) - to actually align on Star. Called few times per alignment procedure.
//    * CURRENT_SCREEN==15  - confirm_sun_track()
//
//  - Please note, that Touches are separated in 2 section to capture OnPress && OnRelease!
//    You will notice that "if (lx > 0 && ly > 0 )" this part defines OnPress activities.

void considerTouchInput(int lx, int ly)
{
  //**************************************************************
  //
  //      BUTTON DOWN Events start here
  //
  //      - only executed when the user touches the screen - PRESS
  //**************************************************************
  if (lx > 0 && ly > 0)
  {
    // Make sure you WakeUp the TFT
    // in case the lid is OFF
    if (IS_TFT_ON == false)
    {
      analogWrite(TFTBright, TFT_Brightness);
      IS_TFT_ON = true;
      TFT_Timer = millis();
      delay(200);
      return;
    }
    TFT_Timer = millis();
    if (CURRENT_SCREEN == 0)
    { // captures touches on drawGPSScreen()
      if (lx > 60 && lx < 260 && ly > 400 && ly < 475)
      {
        last_button = 1;
        tft.fillRect2(60, 400, 200, 65, btn_l_border);
      }
    }
    else if (CURRENT_SCREEN == 1)
    { // captures touches on drawClockScreen()
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN <Back pressed
        drawOptionsScreen();
      }

      if (lx > 220 && lx < 320 && ly > 405 && ly < 480)
      {
        // BTN OK pressed
        tft.fillRect2(226, 406, 70, 55, btn_l_border);
        int changes = 0;
        for (int y = 0; y < 12; y++)
        {
          if (w_DateTime[y] != 0)
          {
            changes = 1;
          }
        }
        if (changes == 1)
        {
          // Do the magic as the date and time has been updated... Update the RTC accordingly
          int hh = (w_DateTime[8] * 10) + w_DateTime[9];
          int mm = (w_DateTime[10] * 10) + w_DateTime[11];
          int dd = (w_DateTime[0] * 10) + w_DateTime[1];
          int mo = (w_DateTime[2] * 10) + w_DateTime[3];
          int yy = (w_DateTime[4] * 1000) + (w_DateTime[5] * 100) + (w_DateTime[6] * 10) + w_DateTime[7];
          rtc.setTime(hh, mm, 00);
          rtc.setDate(dd, mo, yy);
        }

        // drawSelectAlignment();
        drawOptionsScreen();
        //drawStarSyncScreen();
        //drawMainScreen();
      }
      else if (lx > 30 && lx < 100 && ly > 170 && ly < 230)
      {
        // BTN 1 pressed
        tft.drawRect(25, 170, 73, 58, btn_l_border);
        last_button = 1;
        removeTime_addXX();
      }
      else if (lx > 125 && lx < 200 && ly > 170 && ly < 230)
      {
        // BTN 2 pressed
        tft.drawRect(125, 170, 73, 58, btn_l_border);
        last_button = 2;
        removeTime_addXX();
      }
      else if (lx > 225 && lx < 290 && ly > 170 && ly < 230)
      {
        // BTN 3 pressed
        tft.drawRect(225, 170, 73, 58, btn_l_border);
        last_button = 3;
        removeTime_addXX();
      }
      else if (lx > 30 && lx < 100 && ly > 250 && ly < 306)
      {
        // BTN 4 pressed
        tft.drawRect(25, 250, 73, 58, btn_l_border);
        last_button = 4;
        removeTime_addXX();
      }
      else if (lx > 125 && lx < 200 && ly > 250 && ly < 306)
      {
        // BTN 5 pressed
        tft.drawRect(125, 250, 73, 58, btn_l_border);
        last_button = 5;
        removeTime_addXX();
      }
      else if (lx > 225 && lx < 290 && ly > 250 && ly < 306)
      {
        // BTN 6 pressed
        tft.drawRect(225, 250, 73, 58, btn_l_border);
        last_button = 6;
        removeTime_addXX();
      }
      else if (lx > 30 && lx < 100 && ly > 330 && ly < 385)
      {
        // BTN 7 pressed
        tft.drawRect(25, 330, 73, 58, btn_l_border);
        last_button = 7;
        removeTime_addXX();
      }
      else if (lx > 125 && lx < 200 && ly > 330 && ly < 385)
      {
        // BTN 8 pressed
        tft.drawRect(125, 330, 73, 58, btn_l_border);
        last_button = 8;
        removeTime_addXX();
      }
      else if (lx > 225 && lx < 290 && ly > 330 && ly < 385)
      {
        // BTN 9 pressed
        tft.drawRect(225, 330, 73, 58, btn_l_border);
        last_button = 9;
        removeTime_addXX();
      }
      else if (lx > 125 && lx < 200 && ly > 405 && ly < 460)
      {
        // BTN 0 pressed
        tft.drawRect(125, 405, 71, 56, btn_l_border);
        last_button = 10;
        removeTime_addXX();
      }
      else if (lx > 30 && lx < 100 && ly > 405 && ly < 460)
      {
        // BTN SummerTime pressed
        last_button = 22;
      }
    }
    else if (CURRENT_SCREEN == 3)
    {
      if (lx > 30 && lx < 250 && ly > 150 && ly < 215)
      {
        // BTN "1 Star Alignment" pressed
        DrawButton(30, 150, 250, 65, "1 Star Alignment", btn_l_border, 0, btn_l_text, 2);
        ALLIGN_TYPE = 1;
        STARS_PAGER = 0;
        STARS_PAGES = int(nr_Stars / 24) + 1;
        drawStarSyncScreen();
      }
      else if (lx > 30 && lx < 250 && ly > 250 && ly < 315)
      {
        // BTN "Iterative Alignment" pressed
        DrawButton(30, 250, 250, 65, "Iterative Align", btn_l_border, 0, btn_l_text, 2);
        ALLIGN_TYPE = 3;

        // I'll take some time to Initialize the Sub ARRAY with suitable stars (only for Northern Hemi)
        tft.setCursor(0, 5);
        int cc = 0;
        for (int t = 0; t < nr_Stars; t++)
        {
          int i1 = Stars[t].indexOf(';');
          int i2 = Stars[t].indexOf(';', i1 + 1);
          int i3 = Stars[t].indexOf(';', i2 + 1);
          OBJECT_NAME = Stars[t].substring(i1 + 1, i2) + " from " + Stars[t].substring(0, i1);
          String OBJ_RA = Stars[t].substring(i2 + 1, i3);
          OBJECT_RA_H = OBJ_RA.substring(0, OBJ_RA.indexOf('h')).toFloat();
          OBJECT_RA_M = OBJ_RA.substring(OBJ_RA.indexOf('h') + 1, OBJ_RA.length() - 1).toFloat();
          float ts_RA = OBJECT_RA_H + OBJECT_RA_M / 100;
          String OBJ_DEC = Stars[t].substring(i3, Stars[t].length());
          String sign = OBJ_DEC.substring(0, 1);
          OBJECT_DEC_D = OBJ_DEC.substring(1, OBJ_DEC.indexOf('°')).toFloat();
          if (sign == "-")
          {
            OBJECT_DEC_D *= (-1);
          }
          OBJECT_DEC_M = 0;
          if (ts_RA > 5.3 && ts_RA < 23.3)
          {
            calculateLST_HA();
            if (AZ > 90 && AZ < 270 && ALT > 20)
            {
              Iter_Stars[cc] = Stars[t];
              cc += 1;
              if (cc > 49)
              {
                break;
              }
            }
          }
          int_star_count = floor(cc / 15) + 1;
          STARS_PAGER = 0;
          STARS_PAGES = int(cc / 24) + 1;
        }
        delay(500);
        drawStarSyncScreen();
      }
      else if (lx > 30 && lx < 250 && ly > 400 && ly < 455)
      {
        // BTN "Skip Alignment" pressed
        DrawButton(30, 400, 250, 55, "Skip Alignment", btn_l_border, 0, btn_l_text, 2);
        IS_IN_OPERATION = true;
        drawMainScreen();
      }
    }
    else if (CURRENT_SCREEN == 4)
    { // captures touches on drawMainScreen()
      if (lx > 0 && lx < 90 && ly > 0 && ly < 100)
      {
        // Left Side Touched
        // Load the GPS screen to capture new data && correct time if needed on the next screen (Time Screen)
        tft.drawRect(0, 0, 90, 90, btn_l_border);
        CURRENT_SCREEN = 0;
        GPS_iterrations = 0;
        IS_IN_OPERATION = false;
        ALLIGN_STEP = 0;
        ALLIGN_TYPE = 0;
#ifdef no_gps
        // drawClockScreen();
        drawSelectAlignment();
#else
        drawGPSScreen();
#endif;
      }

      if (lx > 250 && lx < 320 && ly > 0 && ly < 100)
      {
        tft.drawRect(250, 0, 90, 90, btn_l_border);
        // Right Side Touched
        drawOptionsScreen();
      }
      if (lx > 1 && lx < 100 && ly > 325 && ly < 395 && IS_BT_MODE_ON == false)
      {
        // BTN 1 pressed
        tft.fillRect2(2, 326, 98, 68, btn_l_border);
        if (MAIN_SCREEN_MENU == 0)
        {
          last_button = 1;
        }
        else
        {
          last_button = 7;
        }
      }
      else if (lx > 1 && lx < 100 && ly > 405 && ly < 475 && IS_BT_MODE_ON == false)
      {
        // BTN 4 pressed
        tft.fillRect2(1, 405, 100, 70, btn_l_border);
        if (MAIN_SCREEN_MENU == 0)
        {
          last_button = 4;
        }
        else
        {
          last_button = 10;
        }
      }
      else if (lx > 110 && lx < 210 && ly > 325 && ly < 395 && IS_BT_MODE_ON == false)
      {
        // BTN 2 pressed
        tft.fillRect2(110, 325, 100, 70, btn_l_border);
        if (MAIN_SCREEN_MENU == 0)
        {
          last_button = 2;
        }
        else
        {
          last_button = 8;
        }
      }
      else if (lx > 110 && lx < 210 && ly > 405 && ly < 475)
      {
        // BTN 5 pressed
        tft.fillRect2(110, 405, 100, 70, btn_l_border);
        if (MAIN_SCREEN_MENU == 0)
        {
          last_button = 5;
        }
        else
        {
          last_button = 11;
        }
      }
      else if (lx > 220 && lx < 290 && ly > 325 && ly < 395)
      {
        // BTN 3 pressed
        tft.fillRect2(220, 325, 100, 70, btn_l_border);
        if (MAIN_SCREEN_MENU == 0)
        {
          last_button = 3;
        }
        else
        {
          last_button = 9;
        }
      }
      else if (lx > 220 && lx < 290 && ly > 405 && ly < 475)
      {
        // BTN 6 pressed
        tft.fillRect2(220, 405, 100, 70, btn_l_border);
        if (MAIN_SCREEN_MENU == 0)
        {
          last_button = 6;
        }
        else
        {
          last_button = 12;
        }
      }
    }
    else if (CURRENT_SCREEN == 5)
    { // captures touches on drawCoordinatesScreen()
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN back pressed
        drawMainScreen();
      }
      if (lx > 40 && lx < 280 && ly > 405 && ly < 475)
      {
        // BTN back pressed
        tft.fillRect2(40, 405, 240, 70, btn_l_border);
        last_button = 1;
      }
    }
    else if (CURRENT_SCREEN == 6)
    { // captures touches on drawLoadScreen() .. the one that loads objects from DB
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN Back pressed
        drawMainScreen();
      }
      if (lx > 220 && lx < 320 && ly > 420 && ly < 480)
      {
        // BTN next> pressed  TREAS_PAGER
        if (LOAD_SELECTOR == 1)
        {
          if (MESS_PAGER < MESS_PAGES - 1)
          {
            MESS_PAGER += 1;
          }
          else
          {
            MESS_PAGER = 0;
          }
          drawLoadObjects();
        }
        else if (LOAD_SELECTOR == 2)
        {
          if (TREAS_PAGER < TREAS_PAGES - 1)
          {
            TREAS_PAGER += 1;
          }
          else
          {
            TREAS_PAGER = 0;
          }
          drawLoadObjects();
        }
        else if (LOAD_SELECTOR == 4)
        {
          if (CUSTOM_PAGER < CUSTOM_PAGES - 1)
          {
            CUSTOM_PAGER += 1;
          }
          else
          {
            CUSTOM_PAGER = 0;
          }
          drawLoadObjects();
        }
      }
      if (lx > 0 && lx < 100 && ly > 420 && ly < 480)
      {
        // BTN <prev pressed
        if (LOAD_SELECTOR == 1)
        {
          if (MESS_PAGER > 0)
          {
            MESS_PAGER -= 1;
          }
          else
          {
            MESS_PAGER = MESS_PAGES - 1;
          }
          drawLoadObjects();
        }
        else if (LOAD_SELECTOR == 2)
        {
          if (TREAS_PAGER > 0)
          {
            TREAS_PAGER -= 1;
          }
          else
          {
            TREAS_PAGER = TREAS_PAGES - 1;
          }
          drawLoadObjects();
        }
        else if (LOAD_SELECTOR == 4)
        {
          if (CUSTOM_PAGER > 0)
          {
            CUSTOM_PAGER -= 1;
          }
          else
          {
            CUSTOM_PAGER = CUSTOM_PAGES - 1;
          }
          drawLoadObjects();
        }
      }
      if (lx > 0 && lx < 150 && ly > 60 && ly < 100)
      {
        // BTN Messier pressed
        LOAD_SELECTOR = 1;
        if (LOAD_SELECTOR == 1)
        {
          DrawButton(0, 60, 150, 40, "Messier", btn_d_border, btn_l_border, btn_l_text, 2);
          DrawButton(170, 60, 150, 40, "Treasures", 0, btn_l_border, btn_l_text, 2);
          DrawButton(0, 110, 150, 40, "Solar System", 0, btn_l_border, btn_l_text, 2);
          DrawButton(170, 110, 150, 40, "custom.csv", 0, btn_l_border, btn_l_text, 2);
          drawLoadObjects();
        }
      }
      if (lx > 170 && lx < 320 && ly > 60 && ly < 100)
      {
        // BTN Treasures pressed
        LOAD_SELECTOR = 2;
        DrawButton(0, 60, 150, 40, "Messier", 0, btn_l_border, btn_l_text, 2);
        DrawButton(170, 60, 150, 40, "Treasures", btn_d_border, btn_l_border, btn_l_text, 2);
        DrawButton(0, 110, 150, 40, "Solar System", 0, btn_l_border, btn_l_text, 2);
        DrawButton(170, 110, 150, 40, "custom.csv", 0, btn_l_border, btn_l_text, 2);
        drawLoadObjects();
      }
      if (lx > 0 && lx < 150 && ly > 110 && ly < 150)
      {
        // BTN Solar System pressed
        LOAD_SELECTOR = 3;
        DrawButton(0, 60, 150, 40, "Messier", 0, btn_l_border, btn_l_text, 2);
        DrawButton(170, 60, 150, 40, "Treasures", 0, btn_l_border, btn_l_text, 2);
        DrawButton(0, 110, 150, 40, "Solar System", btn_d_border, btn_l_border, btn_l_text, 2);
        DrawButton(170, 110, 150, 40, "custom.csv", 0, btn_l_border, btn_l_text, 2);
        drawLoadObjects();
      }
      if (lx > 170 && lx < 320 && ly > 110 && ly < 150)
      {
        // BTN custom.csv pressed
        LOAD_SELECTOR = 4;
        DrawButton(0, 60, 150, 40, "Messier", 0, btn_l_border, btn_l_text, 2);
        DrawButton(170, 60, 150, 40, "Treasures", 0, btn_l_border, btn_l_text, 2);
        DrawButton(0, 110, 150, 40, "Solar System", 0, btn_l_border, btn_l_text, 2);
        DrawButton(170, 110, 150, 40, "custom.csv", btn_d_border, btn_l_border, btn_l_text, 2);
        drawLoadObjects();
      }

      if (LOAD_SELECTOR == 1)
      {
        // I'm in MESSIER selector and need to check which Messier object is pressed
        for (int i = 0; i < 5; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (lx > ((j * 75) + 12) && lx < ((j * 75) + 81) && ly > ((i * 50) + 160) && ly < ((i * 50) + 203))
            {
              //75 box width ,12start from left , 50 box hight , 110 start from up

              // found button pressed.... now I need to get his ID and link to the ARRAY;
              int zz = (MESS_PAGER * 20) + (i * 4) + j;

              if (zz < NR_MESS) //(Messier_Array[zz] != ""){
              {
                selectOBJECT_M(zz, 0);
                calculateLST_HA();
                if (ALT > 0)
                {
                  OnScreenMsg(1);
                  if (IS_SOUND_ON)
                  {
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(1000);
                  }
                  // Stop Interrupt procedure for tracking.
                  Timer3.stop(); //
                  IS_TRACKING = false;

                  IS_OBJ_FOUND = false;
                  IS_OBJECT_RA_FOUND = false;
                  IS_OBJECT_DEC_FOUND = false;
                  // Slew_timer = millis();
                  // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
                }
                else
                {
                  IS_TRACKING = false;
                  drawMainScreen();
                }
                UpdateObservedObjects();
                MESS_PAGER == 0;
                sun_confirm = false;
                //drawMainScreen();
              }
            }
          }
        }
        ///////     Treasures Screen /////////////
      }
      else if (LOAD_SELECTOR == 2)
      {
        // I'm in TREASURES selector and need to check which Treasure object is pressed
        for (int i = 0; i < 5; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (lx > ((j * 75) + 12) && lx < ((j * 75) + 81) && ly > ((i * 50) + 160) && ly < ((i * 50) + 203))
            {
              //75 box width ,12start from left , 50 box hight , 110 start from up

              // found button pressed.... now I need to get his ID and link to the ARRAY;
              int zz = (TREAS_PAGER * 20) + (i * 4) + j;
              if (zz < NR_TREAS) //(Treasure_Array[zz] != "")
              {
                selectOBJECT_M(zz, 1);
                calculateLST_HA();
                if (ALT > 0)
                {
                  OnScreenMsg(1);
                  if (IS_SOUND_ON)
                  {
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(1000);
                  }
                  // Stop Interrupt procedure for tracking.
                  Timer3.stop(); //
                  IS_TRACKING = false;

                  IS_OBJ_FOUND = false;
                  IS_OBJECT_RA_FOUND = false;
                  IS_OBJECT_DEC_FOUND = false;
                  // Slew_timer = millis();
                  // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
                }
                else
                {
                  IS_TRACKING = false;
                  drawMainScreen();
                }
                UpdateObservedObjects();
                TREAS_PAGER == 0;
                sun_confirm = false;
                //drawMainScreen();
              }
            }
          }
        }
      }
      else if (LOAD_SELECTOR == 3)
      {
        // I'm in Solar System selector and need to check which Solar System object is pressed
        for (int i = 0; i < 5; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (lx > ((j * 75) + 12) && lx < ((j * 75) + 81) && ly > ((i * 50) + 160) && ly < ((i * 50) + 203))
            {
              // found button pressed.... now I need to get his ID and link to the ARRAY;
              int zz = (i * 4) + j;
#ifdef serial_debug
              Serial.print("zz = ");
              Serial.println(zz);
#endif
              if (zz == 3)
              {
                OnScreenMsg(5);
                delay(2000);
                drawMainScreen();
              }
              else if (zz <= 10)
              {
                if (zz == 0) // Ho scelto il sole
                {
                  drawConfirmSunTrack();
                }
                else
                {
                  planet_pos(zz);
                }
                if (sun_confirm || zz != 0)
                {
                  calculateLST_HA();
                  if (ALT > 0)
                  {
                    OnScreenMsg(1);
                    if (IS_SOUND_ON)
                    {
                      SoundOn(note_C, 32);
                      delay(200);
                      SoundOn(note_C, 32);
                      delay(200);
                      SoundOn(note_C, 32);
                      delay(1000);
                    }
                    // Stop Interrupt procedure for tracking.
                    Timer3.stop(); //
                    IS_TRACKING = false;

                    IS_OBJ_FOUND = false;
                    IS_OBJECT_RA_FOUND = false;
                    IS_OBJECT_DEC_FOUND = false;
                    // Slew_timer = millis();
                    // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
                  }
                  else
                  {
                    IS_TRACKING = false;
                    drawMainScreen();
                  }
                  UpdateObservedObjects();
                  //CUSTOM_PAGER == 0;
                  sun_confirm = false;
                  //drawMainScreen();
                }
              }
            }
          }
        }
      }
      else if (LOAD_SELECTOR == 4)
      {
        // I'm in CUSTOM.CSV selector and need to check which Custom object is pressed
        for (int i = 0; i < 5; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (lx > ((j * 75) + 12) && lx < ((j * 75) + 81) && ly > ((i * 50) + 160) && ly < ((i * 50) + 203))
            {
              //75 box width ,12start from left , 50 box hight , 110 start from up

              // found button pressed.... now I need to get his ID and link to the ARRAY;
              int zz = (CUSTOM_PAGER * 20) + (i * 4) + j;
              if (zz < NR_CUSTOM) //(custom_Array[zz] != "")
              {
                selectOBJECT_M(zz, 4);
                calculateLST_HA();
                if (ALT > 0)
                {
                  OnScreenMsg(1);
                  if (IS_SOUND_ON)
                  {
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(1000);
                  }
                  // Stop Interrupt procedure for tracking.
                  Timer3.stop(); //
                  IS_TRACKING = false;

                  IS_OBJ_FOUND = false;
                  IS_OBJECT_RA_FOUND = false;
                  IS_OBJECT_DEC_FOUND = false;
                  // Slew_timer = millis();
                  // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
                }
                else
                {
                  IS_TRACKING = false;
                  drawMainScreen();
                }
                UpdateObservedObjects();
                CUSTOM_PAGER == 0;
                sun_confirm = false;
                //drawMainScreen();
              }
            }
          }
        }
      }
    }
    else if (CURRENT_SCREEN == 7)
    {
      // captures touches on drawOptionsScreen()
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN <Back pressed
        storeOptions_SD();
        drawMainScreen();
      }
      if (lx > 0 && lx < 100 && ly > 85 && ly < 125)
      {
        // Celestial Tracking Selected
        Tracking_type = 1;
        Tracking_Mode = "Celest";
        updateTrackingMode_opt();
      }
      if (lx > 110 && lx < 210 && ly > 85 && ly < 125)
      {
        // Lunar Tracking Selected
        Tracking_type = 0;
        Tracking_Mode = "Lunar";
        updateTrackingMode_opt();
      }
      if (lx > 220 && lx < 320 && ly > 85 && ly < 125)
      {
        // Solar Tracking Selected
        Tracking_type = 2;
        Tracking_Mode = "Solar";
        updateTrackingMode_opt();
      }

      if (lx > 275 && lx < 400 && ly > 160 && ly < 200)
      {
        // Screen MAX Brightness
        analogWrite(TFTBright, 255);
        TFT_Brightness = 255;
        updateTriangleBrightness_opt();
        //tft.fillTriangle(5, 200, 265, 200, 265, 155, btn_l_border);
      }
      if (lx > 5 && lx < 265 && ly > 155 && ly < 200)
      {
        // Screen REDUCE Brightness   "Triangle"
        // TFT_Brightness = 190 +((lx - 5)*0.25);
        // TFT_Brightness = 125 + ((lx - 5) * 0.5);
        TFT_Brightness = 8 + ((lx - 5) * 0.95);
        analogWrite(TFTBright, TFT_Brightness);
        updateTriangleBrightness_opt();

        //tft.fillTriangle(5, 200, lx, 200, lx, 190, btn_l_border);
      }

      if (lx > 0 && lx < 45 && ly > 230 && ly < 270)
      {
        // ECO Mode - Timeout in seconds  Never
        TFT_timeout = 0;
        TFT_Time = "AL-ON";
        updateScreenTimeout_opt();
      }
      if (lx > 55 && lx < 100 && ly > 230 && ly < 270)
      {
        // ECO Mode - Timeout in seconds  30 Seconds
        TFT_timeout = 30000;
        TFT_Time = "30 s";
        updateScreenTimeout_opt();
      }
      if (lx > 110 && lx < 155 && ly > 230 && ly < 270)
      {
        // ECO Mode - Timeout in seconds   60 Seconds
        TFT_timeout = 60000;
        TFT_Time = "60 s";
        updateScreenTimeout_opt();
      }
      if (lx > 165 && lx < 210 && ly > 230 && ly < 270)
      {
        // ECO Mode - Timeout in seconds   2 Minutes
        TFT_timeout = 120000;
        TFT_Time = "2 min";
        updateScreenTimeout_opt();
      }
      if (lx > 220 && lx < 265 && ly > 230 && ly < 270)
      {
        // ECO Mode - Timeout in seconds  5 Minutes
        TFT_timeout = 300000;
        TFT_Time = "5 min";
        updateScreenTimeout_opt();
      }
      if (lx > 275 && lx < 320 && ly > 230 && ly < 270)
      {
        // ECO Mode - Timeout in seconds  10 Minutes
        TFT_timeout = 600000;
        TFT_Time = "10 min";
        updateScreenTimeout_opt();
      }

      if (lx > 0 && lx < 100 && ly > 300 && ly < 340)
      {
        // ON Meridian Flip
        IS_MERIDIAN_FLIP_AUTOMATIC = true;
        Mer_Flip_State = "AUTO";
        updateMeridianFlip_opt();
      }
      if (lx > 110 && lx < 210 && ly > 300 && ly < 340)
      {
        // OFF Meridian Flip
        IS_MERIDIAN_FLIP_AUTOMATIC = false;
        Mer_Flip_State = "OFF";
        updateMeridianFlip_opt();
      }

      if (lx > 0 && lx < 100 && ly > 370 && ly < 410)
      {
        // ON Sound
        IS_SOUND_ON = true;
        Sound_State = "ON";
        updateSound_opt();
      }
      if (lx > 110 && lx < 210 && ly > 370 && ly < 410)
      {
        // OFF Sound
        IS_SOUND_ON = false;
        Sound_State = "OFF";
        updateSound_opt();
      }

      if (lx > 0 && lx < 100 && ly > 440 && ly < 480)
      {
        // ON Stepper Motors
        IS_STEPPERS_ON = true;
        digitalWrite(DEC_ENABLE, LOW); // enable stepper driver
        digitalWrite(RA_ENABLE, LOW);  // enable stepper driver

        Stepper_State = "ON";
        updateStepper_opt();
      }
      if (lx > 110 && lx < 210 && ly > 440 && ly < 480)
      {
        // OFF Stepper Motors
        IS_STEPPERS_ON = false;
        digitalWrite(DEC_ENABLE, HIGH); // disable stepper driver
        digitalWrite(RA_ENABLE, HIGH);  // disable stepper driver

        Stepper_State = "OFF";
        updateStepper_opt();
      }

      //Touched GPS configuration
      if (lx > 220 && lx < 320 && ly > 300 && ly < 350)
      {
        DrawButton(220, 300, 100, 50, "Time", btn_l_border, 0, btn_l_text, 2);
        // tft.setCursor(252, 320);
        // tft.print("Set");
        // tft.setCursor(252, 340);

#ifdef no_gps
        // tft.print("Clock");
#else
        tft.print("GPS");
        tft.setCursor(242, 360);
        tft.print("Clock");
#endif

        //storeOptions_SD();

#ifdef no_gps
        drawClockScreen();
#else
        drawGPSScreen();
#endif
      }

      //Touched TFT Calibration
      if (lx > 220 && lx < 320 && ly > 365 && ly < 415)
      {
        DrawButton(220, 365, 100, 50, "Time", btn_l_border, 0, btn_l_text, 2);

        // tft.setCursor(252, 430);
        // tft.print("TFT");
        // tft.setCursor(252, 450);
        // tft.print("Cal");

        drawTFTCalibrationScreen();

        CURRENT_SCREEN = 7;
        drawOptionsScreen();
      }

      //Touched Mount Calibration
      if (lx > 220 && lx < 320 && ly > 430 && ly < 480)
      {
        DrawButton(220, 430, 100, 50, "Mount", btn_l_border, 0, btn_l_text, 2);

        // tft.setCursor(252, 430);
        // tft.print("TFT");
        // tft.setCursor(252, 450);
        // tft.print("Cal");

        drawMountCalScreen();
      }
    }
    else if (CURRENT_SCREEN == 8) // captures touches on drawMountCalScreen()
    {
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN <Back pressed
        storeOptions_SD();
        drawOptionsScreen();
      }

      if (lx > 10 && lx < 50 && ly > 120 && ly < 185)
      {
        // RA backlash --
        if (RA_backlash >= 10)
        {
          RA_backlash -= 10;
        }
        else
        {
          RA_backlash = 0;
        }
        update_RA_backlash();
      }
      if (lx > 60 && lx < 100 && ly > 120 && ly < 185)
      {
        // RA backlash -
        if (RA_backlash >= 1)
        {
          RA_backlash -= 1;
        }
        update_RA_backlash();
      }

      if (lx > 220 && lx < 260 && ly > 120 && ly < 185)
      {
        // RA backlash +
        RA_backlash += 1;
        update_RA_backlash();
      }
      if (lx > 270 && lx < 310 && ly > 120 && ly < 185)
      {
        // RA backlash ++
        RA_backlash += 10;
        update_RA_backlash();
      }

      if (lx > 10 && lx < 50 && ly > 300 && ly < 365)
      {
        // RA backlash --
        if (DEC_backlash >= 10)
        {
          DEC_backlash -= 10;
        }
        else
        {
          DEC_backlash = 0;
        }
        update_DEC_backlash();
      }
      if (lx > 60 && lx < 100 && ly > 300 && ly < 365)
      {
        // RA backlash -
        if (DEC_backlash >= 1)
        {
          DEC_backlash -= 1;
        }
        update_DEC_backlash();
      }

      if (lx > 220 && lx < 260 && ly > 300 && ly < 365)
      {
        // RA backlash +
        DEC_backlash += 1;
        update_DEC_backlash();
      }
      if (lx > 270 && lx < 310 && ly > 300 && ly < 365)
      {
        // RA backlash +
        DEC_backlash += 10;
        update_DEC_backlash();
      }

      if (lx > 10 && lx < 310 && ly > 195 && ly < 260)
      {
        // Sweep RA motor
        if (!RA_sweep)
        {
          RA_sweep = true;
          IS_RA_sweep = true;
          setmStepsMode("R", MICROSteps);
          RA_stepper.setSpeedInStepsPerSecond(10000);
          RA_stepper.setAccelerationInStepsPerSecondPerSecond(10000);
          RA_saveCurrentPositionInSteps = RA_stepper.getCurrentPositionInSteps();
          RA_sweep_dir = true;
          RA_stepper.setTargetPositionInSteps(RA_saveCurrentPositionInSteps + RA_backlash);
        }
        else
        {
          RA_sweep = false;
          RA_stepper.setTargetPositionInSteps(RA_saveCurrentPositionInSteps);
        }

        update_RA_sweep();
      }

      if (lx > 10 && lx < 310 && ly > 390 && ly < 455)
      {
        // Sweep DEC motor
        if (!DEC_sweep)
        {
          DEC_sweep = true;
          IS_DEC_sweep = true;
          setmStepsMode("D", MICROSteps);
          DEC_stepper.setSpeedInStepsPerSecond(10000);
          DEC_stepper.setAccelerationInStepsPerSecondPerSecond(10000);
          DEC_saveCurrentPositionInSteps = DEC_stepper.getCurrentPositionInSteps();
          DEC_sweep_dir = true;
          DEC_stepper.setTargetPositionInSteps(DEC_saveCurrentPositionInSteps + DEC_backlash);
        }
        else
        {
          DEC_sweep = false;
          DEC_stepper.setTargetPositionInSteps(DEC_saveCurrentPositionInSteps);
        }

        update_DEC_sweep();
      }
    }
    else if (CURRENT_SCREEN == 10) // captures touches on drawSTATScreen()
    {
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN Cancel pressed
        IS_IN_OPERATION = true;
        drawMainScreen();
      }
    }
    else if (CURRENT_SCREEN == 11) // captures touches on drawStarMap()
    {
      if (lx > 230 && lx < 320 && ly > 0 && ly < 35)
      {
        // BTN Back pressed
        IS_IN_OPERATION = true;
        drawMainScreen();
      }
      // Take care of Map move...
      // When user touches left, right, top and bottom part of the image,
      // the system loads the corresponding Star Map - moving left, right, top and bottom.
      if (lx > 0 && lx < 50 && ly > 90 && ly < 420) // Left side touched... show next StarMap image
      {
        if (map_c < 8)
        {
          map_c += 1;
          IS_CUSTOM_MAP_SELECTED = true;
          drawStarMap();
        }
      }
      if (lx > 190 && lx < 320 && ly > 90 && ly < 420)
      {
        // Right side touched... show next StarMap image
        if (map_c > 1)
        {
          map_c -= 1;
          IS_CUSTOM_MAP_SELECTED = true;
          drawStarMap();
        }
      }
      if (lx > 0 && lx < 320 && ly > 40 && ly < 90)
      {
        // Top side touched... show next StarMap image
        if (map_r > 1)
        {
          map_r -= 1;
          IS_CUSTOM_MAP_SELECTED = true;
          drawStarMap();
        }
      }
      if (lx > 0 && lx < 320 && ly > 440 && ly < 480)
      {
        // Bottom side touched... show next StarMap image
        if (map_r < 3)
        {
          map_r += 1;
          IS_CUSTOM_MAP_SELECTED = true;
          drawStarMap();
        }
      }
    }
    else if (CURRENT_SCREEN == 12) // captures touches on drawStarSyncScreen()
    {
      if (lx > 210 && lx < 320 && ly > 10 && ly < 60)
      {
        // BTN Done pressed
        IS_IN_OPERATION = true;
        drawMainScreen();
      }
      // int do_kolko = 0;
      // if (ALLIGN_TYPE == 3)
      // {
      //   // Chage the 4 to represent the real count of screens.
      //   // They need to be dynamically calculated... not fixed
      //   do_kolko = int_star_count;
      // }
      // else
      // {
      //   do_kolko = 14;
      // }

      if (lx > 220 && lx < 320 && ly > 420 && ly < 480)
      {
        // BTN next> pressed
        if (STARS_PAGER < STARS_PAGES - 1)
        {
          STARS_PAGER += 1;
        }
        else
        {
          STARS_PAGER = 0;
        }

        drawAlignObjects_ali();
      }
      if (lx > 0 && lx < 100 && ly > 420 && ly < 480)
      {
        // BTN <prev pressed
        if (STARS_PAGER > 0)
        {
          STARS_PAGER -= 1;
        }
        else
        {
          STARS_PAGER = STARS_PAGES - 1;
        }
        drawAlignObjects_ali();
      }

      if (ALLIGN_TYPE < 3)
      {
        // I'm in STARS selector and need to check which Star object is pressed
        for (int i = 0; i < 6; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (lx > ((j * 75) + 12) && lx < ((j * 75) + 81) && ly > ((i * 50) + 85) && ly < ((i * 50) + 128))
            {
              // found button pressed.... now I need to get his ID and link to the ARRAY;
              int zz = (STARS_PAGER * 24) + (i * 4) + j;
              if (Stars[zz] != "")
              {
                selectOBJECT_M(zz, 2);
                calculateLST_HA();
                if (ALT < 0)
                {
                  OnScreenMsg(3);
                  if (IS_SOUND_ON)
                  {
                    SoundOn(note_C, 96);
                    delay(2000);
                  }
                  drawStarSyncScreen();
                }
                else
                {
                  OnScreenMsg(1);
                  if (IS_SOUND_ON)
                  {
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(200);
                    SoundOn(note_C, 32);
                    delay(200);
                  }
                  // Stop Interrupt procedure for tracking.
                  Timer3.stop(); //
                  IS_TRACKING = false;

                  IS_OBJ_FOUND = false;
                  IS_OBJECT_RA_FOUND = false;
                  IS_OBJECT_DEC_FOUND = false;
                  // Slew_timer = millis();
                  // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
                  STARS_PAGER == 0;
                  SELECTED_STAR = zz;
                  ALLIGN_STEP += 1;
                  //drawConstelationScreen(zz);
                }
              }
            }
          }
        }
      }
      else
      {
        // I'm in STARS selector and need to check which Star object is pressed
        for (int i = 0; i < 6; i++)
        {
          for (int j = 0; j < 4; j++)
          {
            if (lx > ((j * 75) + 10) && lx < ((j * 75) + 79) && ly > ((i * 50) + 86) && ly < ((i * 50) + 129))
            {
              // found button pressed.... now I need to get his ID and link to the ARRAY;
              int zz = (STARS_PAGER * 24) + (i * 3) + j;
              if (Iter_Stars[zz] != "")
              {
                // selectOBJECT_M(zz,3);
                Iterative_Star_Index = zz;

                // replaced the above with the below row...
                // to make sure each press selects the same star (inital or on Step 2)
                // change made after Test on 17th March.
                selectOBJECT_M(Iterative_Star_Index, 3);
                calculateLST_HA();
                OnScreenMsg(1);
                if (IS_SOUND_ON)
                {
                  SoundOn(note_C, 32);
                  delay(200);
                  SoundOn(note_C, 32);
                  delay(200);
                  SoundOn(note_C, 32);
                  delay(200);
                }
                // Stop Interrupt procedure for tracking.
                Timer3.stop(); //
                IS_TRACKING = false;

                IS_OBJ_FOUND = false;
                IS_OBJECT_RA_FOUND = false;
                IS_OBJECT_DEC_FOUND = false;
                // Slew_timer = millis();
                // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
                STARS_PAGER == 0;
                SELECTED_STAR = zz;
                ALLIGN_STEP += 1;
                // drawConstelationScreen(zz);
              }
            }
          }
        }
      }
    }
    else if (CURRENT_SCREEN == 13)
    { // captures touches on drawConstelationScreen(int indx)
      if (lx > 0 && lx < 100 && ly > 420 && ly < 480)
      {
        // BTN "<Repeat" or "<EXIT" pressed
        if (ALLIGN_TYPE == 3)
        {
          // delta_a_RA = 0;
          // delta_a_DEC = 0;
          STARS_PAGER = 0;
          IS_TRACKING = false;
          IS_IN_OPERATION = true;
          drawMainScreen();
        }
        else
        {
          ALLIGN_STEP -= 1;
          drawStarSyncScreen();
        }
      }
      if (lx > 220 && lx < 320 && ly > 420 && ly < 480)
      {
        // BTN "ALIGN!" pressed
        // Here we need to know which Star is this - 1st, 2nd, 3rd... etc ?
        // In order to use Ralph Pass alignment procedure described on http://rppass.com/
        // http://rppass.com/align.pdf - the actual PDF

        if (ALLIGN_STEP == 1)
        {
          if (ALLIGN_TYPE == 1)
          {
            IS_TRACKING = false;
            IS_IN_OPERATION = true;
            drawMainScreen();
          }
          else if (ALLIGN_TYPE == 3)
          {
            // Select Polaris and SlewTo...
            IS_TRACKING = false; // Select Polaris and SlewTo...
            IS_TRACKING = false;
            //
            //
            // NOW I have to SYNC on that STAR!
            // Assign Values calculated for
            // SLEW_RA_microsteps and SLEW_DEC_microsteps
            //
            selectOBJECT_M(192, 2); // Polaris in on Index 192 in the Stars Array
            calculateLST_HA();
            OnScreenMsg(1);
            if (IS_SOUND_ON)
            {
              SoundOn(note_C, 32);
              delay(200);
              SoundOn(note_C, 32);
              delay(200);
              SoundOn(note_C, 32);
              delay(200);
            }
            // Stop Interrupt procedure for tracking.
            Timer3.stop(); //
            IS_TRACKING = false;

            IS_OBJ_FOUND = false;
            IS_OBJECT_RA_FOUND = false;
            IS_OBJECT_DEC_FOUND = false;
            // Slew_timer = millis();
            // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
            //drawConstelationScreen(0);
            ALLIGN_STEP = 2;
          }
        }
        else if (ALLIGN_STEP == 2)
        {
          if (ALLIGN_TYPE == 3)
          {
            // Select First Star Again and SlewTo...
            IS_TRACKING = false;
            selectOBJECT_M(Iterative_Star_Index, 3); // Load First Star from the Stars Array
            calculateLST_HA();
            OnScreenMsg(1);
            if (IS_SOUND_ON)
            {
              SoundOn(note_C, 32);
              delay(200);
              SoundOn(note_C, 32);
              delay(200);
              SoundOn(note_C, 32);
              delay(200);
            }
            // Stop Interrupt procedure for tracking.
            Timer3.stop(); //
            IS_TRACKING = false;

            IS_OBJ_FOUND = false;
            IS_OBJECT_RA_FOUND = false;
            IS_OBJECT_DEC_FOUND = false;
            // Slew_timer = millis();
            // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
            //drawConstelationScreen(0);
            ALLIGN_STEP = 1;
          }
        }
      }
    }
    else if (CURRENT_SCREEN == 15)
    {
      // Capture touch inputs on drawConfirmSunTrack()
      if (lx > 10 && lx < 150 && ly > 380 && ly < 460) //BTN YES
      {
        //DrawButton(10, 380, 140, 80, "YES", 0, btn_d_border, btn_l_text, 3);
        planet_pos(0);
        sun_confirm = true;
      }
      else //(lx > 170 && lx < 310 && ly > 380 && ly < 460) //BTN NO
      {
        //DrawButton(170, 380, 140, 80, "NO", 0, btn_d_border, btn_l_text, 3);
        drawLoadScreen();
        sun_confirm = false;
      }
    }
  }
  else
  {
    //**************************************************************
    //
    //      BUTTON UP Events start here
    //
    //      - only executed when the user touches the screen - RELEASE
    //**************************************************************

    if (CURRENT_SCREEN == 0)
    {
      if (last_button == 1)
      {
        last_button = 0;
        // Set the earth rotation direction depending on the Hemisphere...
        // HIGH and LOW are substituted
        if (OBSERVATION_LATTITUDE > 0)
        {
          STP_FWD = LOW;
          STP_BACK = HIGH;
        }
        else
        {
          STP_FWD = HIGH;
          STP_BACK = LOW;
        }
#ifdef serial_debug
        Serial.println(OBSERVATION_LATTITUDE);
        Serial.print("STP_FWD = ");
        Serial.println(STP_FWD);
        Serial.print("STP_BACK = ");
        Serial.println(STP_BACK);
#endif
        CURRENT_SCREEN = 1;
        drawClockScreen();
      }
    }
    else if (CURRENT_SCREEN == 1)
    {
      if (last_button == 1)
      {
        last_button = 0;
        tft.drawRect(25, 170, 73, 58, BLACK);
        TimerUpdateDraw(1);
      }
      if (last_button == 2)
      {
        last_button = 0;
        tft.drawRect(125, 170, 73, 58, BLACK);
        TimerUpdateDraw(2);
      }
      if (last_button == 3)
      {
        last_button = 0;
        tft.drawRect(225, 170, 73, 58, BLACK);
        TimerUpdateDraw(3);
      }
      if (last_button == 4)
      {
        last_button = 0;
        tft.drawRect(25, 250, 73, 58, BLACK);
        TimerUpdateDraw(4);
      }
      if (last_button == 5)
      {
        last_button = 0;
        tft.drawRect(125, 250, 73, 58, BLACK);
        TimerUpdateDraw(5);
      }
      if (last_button == 6)
      {
        last_button = 0;
        tft.drawRect(225, 250, 73, 58, BLACK);
        TimerUpdateDraw(6);
      }
      if (last_button == 7)
      {
        last_button = 0;
        tft.drawRect(25, 330, 73, 58, BLACK);
        TimerUpdateDraw(7);
      }
      if (last_button == 8)
      {
        last_button = 0;
        tft.drawRect(125, 330, 73, 58, BLACK);
        TimerUpdateDraw(8);
      }
      if (last_button == 9)
      {
        last_button = 0;
        tft.drawRect(225, 330, 73, 58, BLACK);
        TimerUpdateDraw(9);
      }
      if (last_button == 10)
      {
        last_button = 0;
        tft.drawRect(125, 405, 71, 56, BLACK);
        TimerUpdateDraw(0);
      }
      if (last_button == 22)
      {
        if (Summer_Time == 1)
        {
          Summer_Time = 0;
          tft.fillRect2(30, 405, 71, 56, BLACK);
          DrawButton(30, 405, 71, 56, "SUMMER", 0, btn_l_border, btn_l_text, 1);
        }
        else
        {
          Summer_Time = 1;
          DrawButton(30, 405, 71, 56, "SUMMER", btn_d_border, btn_l_border, btn_l_text, 1);
        }
        tft.setTextColor(btn_l_text);
        tft.setTextSize(3);
        last_button = 0;
      }
    }
    else if (CURRENT_SCREEN == 4)
    {
      tft.setTextColor(btn_l_text);

      if (last_button == 1 && IS_BT_MODE_ON == false)
      {
        last_button = 0;
        DrawButton(1, 325, 100, 70, "LOAD", btn_l_text, 0, btn_d_text, 2);
        drawLoadScreen();
      }
      if (last_button == 4 && IS_BT_MODE_ON == false)
      {
        last_button = 0;
        drawSTATScreen();
      }
      if (last_button == 2 && IS_BT_MODE_ON == false)
      {
        last_button = 0;
        IS_TRACKING = false;
        Timer3.stop();
        DrawButton(111, 325, 100, 70, "HOME", btn_l_text, 0, btn_d_text, 2);
        OBJECT_NAME = "CP";
        OBJECT_DESCR = "Celestial pole";
        OBJECT_RA_H = 12;
        OBJECT_RA_M = 0;
        OBJECT_DEC_D = 90;
        OBJECT_DEC_M = 0;
        IS_OBJ_FOUND = false;
        IS_OBJECT_RA_FOUND = false;
        IS_OBJECT_DEC_FOUND = false;
        // Slew_timer = millis();
        // Slew_RA_timer = Slew_timer + 20000; // Give 20 sec. advance to the DEC. We will revise later.
        OBJECT_DETAILS = "The north and south celestial poles are the two imaginary points in the sky where the Earth's axis of rotation, intersects the celestial sphere";
        deb_println("Homing started..");
      }
      if ((last_button == 5) || (last_button == 11))
      {
        last_button = 0;
        if (MAIN_SCREEN_MENU == 0)
        {
          MAIN_SCREEN_MENU = 1;
        }
        else
        {
          MAIN_SCREEN_MENU = 0;
        }
        drawMainScreen_Menu(1);
      }
      if (last_button == 3)
      {
        last_button = 0;
        if (IS_TRACKING == false)
        {
          IS_TRACKING = true;
          DrawButton(220, 325, 100, 70, "TRACK", btn_d_border, btn_l_border, btn_l_text, 2);
          setmStepsMode("R", MICROSteps);
          RA_stepper.setDirectionBacklash(1);
          if (Tracking_type == 1)
          { // 1: Sidereal, 2: Solar, 0: Lunar;
            Timer3.start(Clock_Sidereal);
          }
          else if (Tracking_type == 2)
          {
            Timer3.start(Clock_Solar);
          }
          else if (Tracking_type == 0)
          {
            Timer3.start(Clock_Lunar);
          }
        }
        else
        {
          IS_TRACKING = false;
          tft.fillRect2(220, 325, 100, 70, BLACK);
          DrawButton(220, 325, 100, 70, "TRACK", 0, btn_l_border, btn_l_text, 2);
          OnScreenMsg(2);
          setmStepsMode("R", 1);
          Timer3.stop(); //
        }
      }
      if (last_button == 6)
      { // BlueTooth Mode
        if (IS_BT_MODE_ON == true)
        {
          IS_BT_MODE_ON = false;
        }
        else
        {
          IS_BT_MODE_ON = true;
          // Initialize Bluetooth communication on PINs: 15 (RX) and 14 (TX)
        }
        last_button = 0;
        drawMainScreen();
      }
      if (last_button == 7 && IS_BT_MODE_ON == false)
      {
        last_button = 0;
        //DrawButton( 1, 325, 100, 70, "LOAD", btn_l_text, 0, btn_d_text, 2);
        if ((IS_TRACKING == true) && (IS_SOUND_ON))
        {
          SoundOn(note_C, 32);
        }
        drawCoordinatesScreen();
      }
      if (last_button == 8 && IS_BT_MODE_ON == false)
      {
        last_button = 0;
        DrawButton(111, 325, 100, 70, "MAP", btn_l_text, 0, btn_d_text, 2);
        drawStarMap();
      }
      if (last_button == 9)
      {
        last_button = 0;
        if (IS_FAN1_ON)
        {
          IS_FAN1_ON = false;
          tft.fillRect2(220, 325, 100, 70, BLACK);
          DrawButton(220, 325, 100, 70, "FAN 1", 0, btn_l_border, btn_l_text, 2);
          digitalWrite(FAN1, LOW);
          Fan1_State = "OFF";
          drawStatusBar();
        }
        else
        {
          IS_FAN1_ON = true;
          tft.fillRect2(220, 325, 100, 70, BLACK);
          DrawButton(220, 325, 100, 70, "FAN 1", btn_d_border, btn_l_border, btn_l_text, 2);
          digitalWrite(FAN1, HIGH);
          //analogWrite(FAN1, 100); //5V PWM over 13V VDD
          //Fan1_State = "39%";
          Fan1_State = "ON";
          drawStatusBar();
        }
        storeOptions_SD();
      }
      if (last_button == 10)
      {
        last_button = 0;
        drawOptionsScreen();
      }
      if (last_button == 12)
      {
        last_button = 0;
        if (IS_FAN2_ON)
        {
          IS_FAN2_ON = false;
          tft.fillRect2(220, 405, 100, 70, BLACK);
          DrawButton(220, 405, 100, 70, "FAN 2", 0, btn_l_border, btn_l_text, 2);
          digitalWrite(FAN2, LOW);
          Fan2_State = "OFF";
          drawStatusBar();
        }
        else
        {
          IS_FAN2_ON = true;
          tft.fillRect2(220, 405, 100, 70, BLACK);
          DrawButton(220, 405, 100, 70, "FAN 2", btn_d_border, btn_l_border, btn_l_text, 2);
          digitalWrite(FAN2, HIGH);
          Fan2_State = "ON";
          drawStatusBar();
        }
        storeOptions_SD();
      }
    }
    else if (CURRENT_SCREEN == 5)
    {
      if (last_button == 1)
      {
        last_button = 0;
        // set microsteps to home position
        // RA_microSteps = RA_90; //  --> point to North Sudereal Pole = -180 deg (-12h)
        // DEC_microSteps = 0;    //  --> Point to North Sudereal Pole = 90 deg

        RA_stepper.setCurrentPositionInSteps(RA_90);
        RA_stepper.setTargetPositionInSteps(RA_90);
        DEC_stepper.setCurrentPositionInSteps(0);
        DEC_stepper.setTargetPositionInSteps(0);

        considerTimeUpdates(); // Update coordinates on the screen
        DrawButton(40, 405, 240, 70, "SET HOME POSITION", 0, btn_l_border, btn_l_text, 2);
      }
    }
  }
}
