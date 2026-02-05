
void start_up_movement() {

  int pos = 90;
  int speed_temp = 700;

  pan1.startEaseToD(pos, speed_temp);
  tilt1.startEaseToD(pos + Yservo_1_offset, speed_temp);
  updateAndWaitForAllServosToStop();

  pan2.startEaseToD(pos, speed_temp);
  tilt2.startEaseToD(pos + Yservo_2_offset, speed_temp);
  updateAndWaitForAllServosToStop();

  pan3.startEaseToD(pos, speed_temp);
  tilt3.startEaseToD(pos + Yservo_3_offset, speed_temp);
  updateAndWaitForAllServosToStop();

  pan4.startEaseToD(pos, speed_temp);
  tilt4.startEaseToD(pos + Yservo_4_offset, speed_temp);
  updateAndWaitForAllServosToStop();
}

void cross() {

  int pos = 180;

  pan1.startEaseToD(pos, speed);
  pan2.startEaseToD(pos, speed);
  pan3.startEaseToD(pos, speed);
  pan4.startEaseToD(pos, speed);

  tilt1.startEaseToD(pos + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();

  pos = 0;

  pan1.startEaseToD(pos, speed);
  pan2.startEaseToD(pos, speed);
  pan3.startEaseToD(pos, speed);
  pan4.startEaseToD(pos, speed);

  tilt1.startEaseToD(pos + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();
}

void cross2() {

  int pos1 = 180;
  int pos2 = 0;

  pan1.startEaseToD(pos1, speed);
  pan2.startEaseToD(pos1, speed);
  pan3.startEaseToD(pos2, speed);
  pan4.startEaseToD(pos2, speed);

  tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();

  pos1 = 0;
  pos2 = 180;

  pan1.startEaseToD(pos1, speed);
  pan2.startEaseToD(pos1, speed);
  pan3.startEaseToD(pos2, speed);
  pan4.startEaseToD(pos2, speed);

  tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();

  /*

  int pos1 = MINIMUM_PULSE_WIDTH;
  int pos2 = MAXIMUM_PULSE_WIDTH;

  bool bool1 = false;
  bool bool2 = false;

  while(!bool1 && !bool2)
  {
    if(pos1 <= MAXIMUM_PULSE_WIDTH) pos1 += increment;
    else bool1 = true;

    if(pos2 >= MINIMUM_PULSE_WIDTH) pos2 -= increment;
    else bool2 = true;

    pan1.startEaseToD(pos1, speed);
    tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);

    pan2.startEaseToD(pos1, speed);
    tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);

    pan3.startEaseToD(pos2, speed);
    tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);

    pan4.startEaseToD(pos2, speed);
    tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

    updateAndWaitForAllServosToStop();
  }

  bool1 = false;
  bool2 = false;

  while(!bool1 && !bool2)
  {
    if(pos2 <= MAXIMUM_PULSE_WIDTH) pos2 += increment;
    else bool1 = true;

    if(pos1 >= MINIMUM_PULSE_WIDTH) pos1 -= increment;
    else bool2 = true;

    pan1.startEaseToD(pos1, speed);
    tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);

    pan2.startEaseToD(pos1, speed);
    tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);

    pan3.startEaseToD(pos2, speed);
    tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);

    pan4.startEaseToD(pos2, speed);
    tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

    updateAndWaitForAllServosToStop();
  }*/
}

void random_twist() {

  int random_num = random(4);

  int pos1 = 180;
  int pos2 = 0;

  while(random_num == last_random_num)
  {
    random_num = random(4);
  }

  last_random_num = random_num;

  if(random_num == 0)
  {
    pan1.startEaseToD(pos1, speed);
    tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);
    updateAndWaitForAllServosToStop();

    pan1.startEaseToD(pos2, speed);
    tilt1.startEaseToD(pos2 + Yservo_1_offset, speed);
    updateAndWaitForAllServosToStop();
  }
  else if(random_num == 1)
  {
    pan2.startEaseToD(pos1, speed);
    tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);
    updateAndWaitForAllServosToStop();

    pan2.startEaseToD(pos2, speed);
    tilt2.startEaseToD(pos2 + Yservo_2_offset, speed);
    updateAndWaitForAllServosToStop();
  }
  else if(random_num == 2)
  {
    pan3.startEaseToD(pos1, speed);
    tilt3.startEaseToD(pos1 + Yservo_3_offset, speed);
    updateAndWaitForAllServosToStop();

    pan3.startEaseToD(pos2, speed);
    tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);
    updateAndWaitForAllServosToStop();
  }
  else if(random_num == 3)
  {
    pan4.startEaseToD(pos1, speed);
    tilt4.startEaseToD(pos1 + Yservo_4_offset, speed);
    updateAndWaitForAllServosToStop();

    pan4.startEaseToD(pos2, speed);
    tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);
    updateAndWaitForAllServosToStop();
  }
}

void backandfourth() {

  int pos1 = 180;
  int pos2 = 0;

  if(reset)
  {
    pan1.startEaseToD(pos1, speed);
    pan2.startEaseToD(pos1, speed);
    pan3.startEaseToD(pos1, speed);
    pan4.startEaseToD(pos1, speed);

    updateAndWaitForAllServosToStop();

    reset = false;
  }
  
  tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos1 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos1 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();

  tilt1.startEaseToD(pos2 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos2 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();
}

void backandfourth2() {

  if(reversing) 
  {
    x_circle -= 1;
    if(x_circle <= 0) reversing = false;    
  } 
  else 
  {
    x_circle += 1;
    if(x_circle >= 180) reversing = true;
  }

  int y_circle = 180 - x_circle;

  pan1.write(x_circle);
  pan2.write(x_circle);
  pan3.write(x_circle);
  pan4.write(x_circle);

  tilt1.write(y_circle + Yservo_1_offset);
  tilt2.write(y_circle + Yservo_2_offset);
  tilt3.write(y_circle + Yservo_3_offset);
  tilt4.write(y_circle + Yservo_4_offset);

  delay(map(speed_raw, 1, 100, 30, 5));
}
      
void leftandright() {

  int pos1 = 90; //was 90
  int pos2 = 180;
  int pos3 = 0;

  if(reset)
  {
    pan1.startEaseToD(pos1, speed);
    pan2.startEaseToD(pos1, speed);
    pan3.startEaseToD(pos1, speed);
    pan4.startEaseToD(pos1, speed);

    updateAndWaitForAllServosToStop();

    reset = false;
  }

  tilt1.startEaseToD(pos2 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos2 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();

  tilt1.startEaseToD(pos3 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos3 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos3 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos3 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();
}

void leftandright2() {

  int pos1 = 180;
  int pos2 = 0;
  int increment = 1;

  if(reset)
  {
    pan1.startEaseToD(96, speed);
    pan2.startEaseToD(128, speed);
    pan3.startEaseToD(34, speed);
    pan4.startEaseToD(48, speed);

    updateAndWaitForAllServosToStop();

    reset = false;
  }

  while(pos1 > 90)//down to up
  {
    pos1 -= increment;
    pos2 += increment;

    tilt1.write(pos1 + Yservo_1_offset);
    tilt2.write(pos1 + Yservo_2_offset);
    tilt3.write(pos2 + Yservo_3_offset);
    tilt4.write(pos2 + Yservo_4_offset);

    pan1.write(pos1);
    pan2.write(pos1);
    pan3.write(pos2);
    pan4.write(pos2);

    delay(map(speed_raw, 1, 100, 30, 5));
  }

  while(pos1 < 180)//up to down
  {
    pos1 += increment;
    pos2 -= increment;

    tilt1.write(pos1 + Yservo_1_offset);
    tilt2.write(pos1 + Yservo_2_offset);
    tilt3.write(pos2 + Yservo_3_offset);
    tilt4.write(pos2 + Yservo_4_offset);

    pan1.write(pos1);
    pan2.write(pos1);
    pan3.write(pos2);
    pan4.write(pos2);

    delay(map(speed_raw, 1, 100, 30, 5));
  }
}

void leftandright3() {

  int x_1_start = 0;
  int x_4_start = 180;

  int x_1_end = 180;
  int x_4_end = 0;

  int x_2_stay = 180;
  int x_3_stay = 0;

  int y_1_stay = 40;
  int y_4_stay = 135;

  int y_2_start = 110;//110
  int y_3_start = 100;//100

  int y_2_end = 180;//180
  int y_3_end = 30;//30

  if(reset)
  {
    pan2.startEaseToD(x_2_stay, speed);
    pan3.startEaseToD(x_3_stay, speed);

    tilt1.startEaseToD(y_1_stay + Yservo_1_offset, speed);
    tilt4.startEaseToD(y_4_stay + Yservo_4_offset, speed);

    updateAndWaitForAllServosToStop();
    reset = false;
  }

  pan1.startEaseToD(x_1_start, speed);
  pan4.startEaseToD(x_4_start, speed);

  tilt2.startEaseToD(y_2_start, speed);
  tilt3.startEaseToD(y_3_start, speed);

  updateAndWaitForAllServosToStop();

  pan1.startEaseToD(x_1_end, speed);
  pan4.startEaseToD(x_4_end, speed);

  tilt2.startEaseToD(y_2_end, speed);
  tilt3.startEaseToD(y_3_end, speed);

  updateAndWaitForAllServosToStop();
}

void onebyone() {

  //PHASE 1: start of the light goes down slowly
  //int x_start_1 = 0;//stays
  //int y_start_1 = 180;//goes down from here
  int x_end_1 = 0;
  int y_end_1 = 0;

  //PHASE 2: start of the light panning from left to right
  //int x_start_2 = 0;//goes to right from here
  //int y_start_2 = 0;//stays
  int x_end_2 = 90;
  int y_end_2 = 0;

  //PHASE 3: start of the light panning from left to right
  //int x_start_3 = 90;//turns to the right
  //int y_start_3 = 0;//goes back up
  int x_end_3 = 0;
  int y_end_3 = 180;
  //---repeats---

  //check each fixture and its current phase, then based on phase, feed in degrees, afterwards increment all fixtures phases

  //1st fixture
  if(fixture_1_phase == 1)
  {
    pan1.startEaseToD(x_end_1, speed);
    tilt1.startEaseToD(y_end_1 + Yservo_1_offset, speed);
  }
  else if(fixture_1_phase == 2)
  {
    pan1.startEaseToD(x_end_2, speed);
    tilt1.startEaseToD(y_end_2 + Yservo_1_offset, speed);
  }
  else if(fixture_1_phase == 3)
  {
    pan1.startEaseToD(x_end_3, speed);
    tilt1.startEaseToD(y_end_3 + Yservo_1_offset, speed);
  }

  //2nd fixture
  if(fixture_2_phase == 1)
  {
    pan2.startEaseToD(x_end_1, speed);
    tilt2.startEaseToD(y_end_1 + Yservo_2_offset, speed);
  }
  else if(fixture_2_phase == 2)
  {
    pan2.startEaseToD(x_end_2, speed);
    tilt2.startEaseToD(y_end_2 + Yservo_2_offset, speed);
  }
  else if(fixture_2_phase == 3)
  {
    pan2.startEaseToD(x_end_3, speed);
    tilt2.startEaseToD(y_end_3 + Yservo_2_offset, speed);
  }

  //3rd fixture
  if(fixture_3_phase == 1)
  {
    pan3.startEaseToD(x_end_1, speed);
    tilt3.startEaseToD(y_end_1 + Yservo_3_offset, speed);
  }
  else if(fixture_3_phase == 2)
  {
    pan3.startEaseToD(x_end_2, speed);
    tilt3.startEaseToD(y_end_2 + Yservo_3_offset, speed);
  }
  else if(fixture_3_phase == 3)
  {
    pan3.startEaseToD(x_end_3, speed);
    tilt3.startEaseToD(y_end_3 + Yservo_3_offset, speed);
  }

  //4th fixture
  if(fixture_4_phase == 1)
  {
    pan4.startEaseToD(x_end_1, speed);
    tilt4.startEaseToD(y_end_1 + Yservo_4_offset, speed);
  }
  else if(fixture_4_phase == 2)
  {
    pan4.startEaseToD(x_end_2, speed);
    tilt4.startEaseToD(y_end_2 + Yservo_4_offset, speed);
  }
  else if(fixture_4_phase == 3)
  {
    pan4.startEaseToD(x_end_3, speed);
    tilt4.startEaseToD(y_end_3 + Yservo_4_offset, speed);
  }

  fixture_1_phase++;
  fixture_2_phase++;
  fixture_3_phase++;
  fixture_4_phase++;

  if(fixture_1_phase > 3) fixture_1_phase = 1;
  if(fixture_2_phase > 3) fixture_2_phase = 1;
  if(fixture_3_phase > 3) fixture_3_phase = 1;
  if(fixture_4_phase > 3) fixture_4_phase = 1; 

  updateAndWaitForAllServosToStop();
}

void waves() {

  if(reset)
  {
    pan1.startEaseToD(150, speed);
    pan2.startEaseToD(150, speed);
    pan3.startEaseToD(150, speed);
    pan4.startEaseToD(150, speed);

    updateAndWaitForAllServosToStop();

    reset = false;
  }

  int pos1 = 180;
  int pos2 = 0;
  
  tilt1.startEaseToD(pos1 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos1 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos1 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos1 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();
  
  tilt1.startEaseToD(pos2 + Yservo_1_offset, speed);
  tilt2.startEaseToD(pos2 + Yservo_2_offset, speed);
  tilt3.startEaseToD(pos2 + Yservo_3_offset, speed);
  tilt4.startEaseToD(pos2 + Yservo_4_offset, speed);

  updateAndWaitForAllServosToStop();

}

void rotate1() {

  //start
  //x 0, 180, 0, 180
  //y 10, 180, 15, 180

  //end
  //x 30, 150, 30, 140
  //y 10, 160, 15, 180

  int x_1_start = 0;
  int x_2_start = 180;
  int x_3_start = 0;
  int x_4_start = 180;

  int y_1_stay = 10;
  int y_2_stay = 160;
  int y_3_stay = 15;
  int y_4_stay = 170;

  int x_1_end = 50;
  int x_2_end = 130;
  int x_3_end = 50;
  int x_4_end = 130;

  if(reset)
  {
    tilt1.startEaseToD(y_1_stay + Yservo_1_offset, speed);
    tilt2.startEaseToD(y_2_stay + Yservo_2_offset, speed);
    tilt3.startEaseToD(y_3_stay + Yservo_3_offset, speed);
    tilt4.startEaseToD(y_4_stay + Yservo_4_offset, speed);

    updateAndWaitForAllServosToStop();
    reset = false;
  }

  pan1.startEaseToD(x_1_start, speed);
  pan2.startEaseToD(x_2_start, speed);
  pan3.startEaseToD(x_3_start, speed);
  pan4.startEaseToD(x_4_start, speed);

  updateAndWaitForAllServosToStop();

  pan1.startEaseToD(x_1_end, speed);
  pan2.startEaseToD(x_2_end, speed);
  pan3.startEaseToD(x_3_end, speed);
  pan4.startEaseToD(x_4_end, speed);

  updateAndWaitForAllServosToStop();
  
}

void rotate2() {

  //start
  //x 0, 180, 0, 180
  //y 10, 180, 15, 180

  //end
  //x 30, 150, 30, 140
  //y 10, 180, 15, 180

  int x_1_start = 0;
  int x_2_start = 180;
  int x_3_start = 0;
  int x_4_start = 180;

  int y_1_start = 30;
  int y_2_start = 140;
  int y_3_start = 60;
  int y_4_start = 180;

  int x_1_end = 50;
  int x_2_end = 130;
  int x_3_end = 50;
  int x_4_end = 130;

  int y_1_end = 70;
  int y_2_end = 180;
  int y_3_end = 25;
  int y_4_end = 170;

  pan1.startEaseToD(x_1_start, speed);
  pan2.startEaseToD(x_2_start, speed);
  pan3.startEaseToD(x_3_start, speed);
  pan4.startEaseToD(x_4_start, speed);

  tilt1.startEaseToD(y_1_start, speed);
  tilt2.startEaseToD(y_2_start, speed);
  tilt3.startEaseToD(y_3_start, speed);
  tilt4.startEaseToD(y_4_start, speed);

  updateAndWaitForAllServosToStop();

  pan1.startEaseToD(x_1_end, speed);
  pan2.startEaseToD(x_2_end, speed);
  pan3.startEaseToD(x_3_end, speed);
  pan4.startEaseToD(x_4_end, speed);

  tilt1.startEaseToD(y_1_end, speed);
  tilt2.startEaseToD(y_2_end, speed);
  tilt3.startEaseToD(y_3_end, speed);
  tilt4.startEaseToD(y_4_end, speed);

  updateAndWaitForAllServosToStop();
}

void rotate3() {

}

void preset1() {

  /*
    0-12 onebyone at 45
    12-23 backandfourth2 at 50
    23-48 rotate2 at 80
    48-62 cross2 at 80
    62-73 leftandright2 at 80
  */

  if(reset)
  {
    preset_started_at = millis();
    reset = false;
  }

  speed_raw = 45;
  speed = map(speed_raw, 1, 100, 3000, 300);
  while(millis() - preset_started_at < 12000) onebyone();

  speed_raw = 50;
  speed = map(speed_raw, 1, 100, 3000, 300);
  while(millis() - preset_started_at < 23000) backandfourth2();

  speed_raw = 80;
  speed = map(speed_raw, 1, 100, 3000, 300);
  while(millis() - preset_started_at < 48000) rotate2();

  speed_raw = 80;
  speed = map(speed_raw, 1, 100, 3000, 300);
  while(millis() - preset_started_at < 62000) cross2();

  speed_raw = 50;
  speed = map(speed_raw, 1, 100, 3000, 300);
  while(millis() - preset_started_at < 10000) leftandright2();
}


/*
rototate and converage

rotate one by one

draw diamonds

void all(int duration) {

  while(effect_played == 1)
  {
    cross(5);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
     // DEBUG_println(String(effect_played));
    }
  }

  while(effect_played == 2)
  {
    cross2(5);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 3)
  {
    random_twist(5); 

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 4)
  {
    backandfourth(3, 3);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 5)
  {
    backandfourth2(5);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 6)
  {
    leftandright(2, 5);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 7)
  {
    leftandright2(5);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 8)
  {
    leftandright3(8);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 9)
  {
    onebyone(300);

    if(millis() - start_time > duration) 
    {
      effect_played++;
      start_time = millis();
    }
  }

  while(effect_played == 10)
  {
    fast_rotate(1, 5);

    if(millis() - start_time > duration) 
    {
      effect_played = 1;
      start_time = millis();
    }
  }
}*/