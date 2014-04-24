/* robot description: */
/*!res_num: 480 */
/*!res_den: 22 */
/*!radius: 141 */
/*!speed: 50  */
/*!acc_num: 1 */
/*!acc_den: 7 */
/*!rspeed: 100 */
/*!racc_num: 1 */
/*!racc_den: 7 */

#define ODETECT_FRONT_DISTANCE 35
#define ODETECT_REAR_DISTANCE 25
#define ODETECT_TURN_DISTANCE 20

//goto ACTION;

/* place robot at start point */
/* note that robot must be placed at OX direction */
/*!coords: 2778 236 */

odetect_set_single_limit(0, 0); /* reset ODetect */
while (!GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

tmgr_delay(1000);

/* set start position */
chassis_write(-3, -3);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(300);
chassis_write(0, 0);
tmgr_delay(1000);

chassis_move(20, 20, 1, 15, mmToTicks(220));
while (chassis_busy());

servo_write(1, 77);
servo_write(2, 125);
elevator_set_pos(5000);

/* set start angle */
/*!angle: 0.190174 */
chassis_move(100, -100, 1, 7, 585);
while (chassis_busy());

/* go backward 30 mm to fit in start zone */
chassis_move(-20, -20, 1, 15, mmToTicks(30));
while(chassis_busy());

/* wait for shmorgalka to launch */
while (GPIO_READ(CONFIG_ROBOT_SHMORGALKA));
timer_run();

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);

/*
 * Part 1. Collection of fires.
 *
 * Go to the first fire and collect it!
 */

/*!path: 1412.47 */
chassis_move(50 , 50 , 1, 7, 30818);
while (stepper_get_path(1) <= 9600);
elevator_set_pos(2200); /* move elevator up */
servo_write(1, 0); /* arm */
servo_write(2, 20); /* paw */
tmgr_delay(300);
elevator_set_pos(2800);
tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_set_pos(2400);
servo_write(1, 90);
servo_write(2, 125);

//while (stepper_get_path(1) <= 15000);
//odetect_set_single_limit(0, 0);
while (chassis_busy());

/* 
 * First fire is on board now.
 * Turn left and take next one.
 */

odetect_set_single_limit(ODETECT_LEFT, ODETECT_TURN_DISTANCE);
/*!angle: 1.34262 */
chassis_move(100, -100, 1, 7, 4130);
elevator_set_pos(5000);
while (chassis_busy()) {
	/*do something */
}


GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);

odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
/*!path: 789.572 */
chassis_move(50 , 50 , 1, 7, 17227);

while (stepper_get_path(1) <= mmToTicks(130));
elevator_set_pos(100);
servo_write(1, 0);
servo_write(2, 20);
tmgr_delay(200);
elevator_set_pos(1900);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
while (chassis_busy());

/*
 * Second fire is on board!
 *
 * Third fire is on the wall, collect it
 */

/*!speed: 50  */
odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
/*!angle: -1.5328 */
chassis_move(-100, 100, 1, 7, 4715);

elevator_set_pos(1000);
servo_write(1, 87);
servo_write(2, 125);
tmgr_delay(100);
elevator_set_pos(3800);
while (chassis_busy());


/* step 4: go 183 mm */
odetect_set_single_limit(0, 0); /* turn ODetect off for a while */
/*!path: 89.9962 */
chassis_move(50 , 50 , 1, 7, 964);
while (chassis_busy());


GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
chassis_move(10, 10, 1, 10, mmToTicks(6));
while (chassis_busy());

chassis_move(-10, -10, 1, 10, mmToTicks(6));
while (chassis_busy());

/* go away from this side-hell! :D */
odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
chassis_move(-70, -70, 1, 10, 1264);
tmgr_delay(300);
elevator_set_pos(1000);
servo_write(2, 20);

while (chassis_busy());

#if 0
/* rotate to 180.00 degrees (3.141590 radians) */
/*!angle: 3.14159 */
chassis_move(100, -100, 1, 7, 9665);
//chassis_set_interrupt(odetect_front);
chassis_move(100, -100, 1, 7, 9665);
while (chassis_busy()) {
	/*do something */
}

/*!path: 95.9962 */
chassis_move(50 , 50 , 1, 7, 2094);
//chassis_set_interrupt(odetect_front);
chassis_move(50, 50, 1, 7, 4058);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to 90.00 degrees (1.570790 radians) */
/*!angle: -1.60204 */
chassis_move(-100, 100, 1, 7, 4928);
//chassis_set_interrupt(odetect_front);
chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy()) {
	/*do something */
}
#endif
odetect_set_single_limit(ODETECT_LEFT, ODETECT_TURN_DISTANCE);
chassis_move(100, -100, 1, 10, 4932);
elevator_set_pos(400);
servo_write(1, 150);
tmgr_delay(300);
while (chassis_busy());

odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
/*!path: 384.187 */
chassis_move(50 , 50 , 1, 7, 8382);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(100);
elevator_reset();
while (chassis_busy());

/* rotate to 90.00 degrees (1.570800 radians) */
odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
/*!angle: -1.50252 */
chassis_move(-100, 100, 1, 7, 4832);
servo_write(1, 87);
servo_write(2, 125);
elevator_set_pos(3800);
while (chassis_busy());

/*!path: 81.0468 */
chassis_move(50 , 50 , 1, 7, 988);
while (chassis_busy());

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
chassis_move(10, 10, 1, 10, mmToTicks(10));
while (chassis_busy());

chassis_move(-10, -10, 1, 10, mmToTicks(10));
while (chassis_busy());

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
//chassis_set_interrupt(odetect_rear);
chassis_move(-50, -50, 1, 10, 4058);
tmgr_delay(300);
elevator_set_pos(1000);
while (chassis_busy());

#if 0
/* rotate to 180.00 degrees (3.141590 radians) */
/*!angle: 3.10457 */
chassis_move(100, -100, 1, 7, 9551);
//chassis_set_interrupt(odetect_front);
chassis_move(100, -100, 1, 7, 9665);
while (chassis_busy()) {
	/*do something */
}

/*!path: 80.9909 */
chassis_move(50 , 50 , 1, 7, 1767);
//chassis_set_interrupt(odetect_front);
chassis_move(50, 50, 1, 7, 4058);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -90.00 degrees (-1.570790 radians) */
/*!angle: 1.47717 */
chassis_move(100, -100, 1, 7, 4544);
//chassis_set_interrupt(odetect_front);
chassis_move(-100, 100, 1, 7, 4832);
while (chassis_busy()) {
	/*do something */
}
#endif

odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
chassis_move(-100, 100, 1, 10, 4832);
servo_write(2, 20);
elevator_reset();
servo_write(1, 150);
while (chassis_busy());

/*!speed: 50  */

odetect_set_single_limit(ODETECT_FRONT | ODETECT_FLEFT, ODETECT_FRONT_DISTANCE);
/*!path: 1283.62 */
chassis_move(50 , 50 , 1, 7, 28006);
tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(100);
elevator_reset();
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -48.12 degrees (-0.839928 radians) */
odetect_set_single_limit(ODETECT_LEFT, ODETECT_TURN_DISTANCE);
/*!angle: 0.969716 */
chassis_move(100, -100, 1, 7, 2983);
servo_write(1, 0);
servo_write(2, 27);

tmgr_delay(400);
while (chassis_busy());

odetect_set_single_limit(0, 0);
/*!path: 117.158 */
chassis_move(50 , 50 , 1, 7, 2556);
elevator_reset();
elevator_set_pos(2000);
while (chassis_busy());


//chassis_move(40, 40, 1, 7, mmToTicks(30));
//while (chassis_busy());

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(1000);

servo_write(1, 80);
tmgr_delay(300);
servo_write(2, 180);
tmgr_delay(300);


chassis_move(40, 40, 1, 7, mmToTicks(30));
elevator_set_pos(4600);
while (chassis_busy());

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

chassis_move(-20, -20, 1, 15 ,mmToTicks(80));
tmgr_delay(300);
servo_write(2, 27);
elevator_set_pos(1500);
while (chassis_busy());


servo_write(1, 0);
elevator_set_pos(3400);

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(100);

chassis_move(50, 50, 1, 7, mmToTicks(100));
elevator_set_pos(1700);
servo_write(1, 80);
tmgr_delay(100);
while (chassis_busy());

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);

/*chassis_move(-50, -50, 1, 7, mmToTicks(40));
while (chassis_busy());*/

#if 0
/* rotate to 180.00 degrees (3.141590 radians) */
/*!angle: 3.10544 */
chassis_move(100, -100, 1, 7, 9553);
//chassis_set_interrupt(odetect_front);
chassis_move(100, -100, 1, 7, 9665);
while (chassis_busy()) {
	/*do something */
}

/*!path: 122.329 */
chassis_move(50 , 50 , 1, 7, 2669);
//chassis_set_interrupt(odetect_front);
chassis_move(100, 100, 1, 7, 22);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -0.83 degrees (-0.014443 radians) */
/*!angle: 0.415704 */
chassis_move(100, -100, 1, 7, 1279);
//chassis_set_interrupt(odetect_front);
chassis_move(-100, 100, 1, 7, 44);
while (chassis_busy()) {
	/*do something */
}

#endif

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
chassis_move(-50, -50, 1, 10, mmToTicks(100));
while (chassis_busy());

odetect_set_single_limit(0, 0);
chassis_move(100, -100, 1, 7, mmToTicks(280));
while (chassis_busy());

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
chassis_move(-50, -50, 1, 10, mmToTicks(100));
while (chassis_busy());

ACTION:
elevator_set_pos(1700);
odetect_set_single_limit(0, 0);
chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
chassis_write(0, 0);

#if 0
/*!speed: -50  */
odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
/*!path: 992.542 */
chassis_move(-50 , -50 , 1, 7, 21655);
servo_write(1, 0);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -19.43 degrees (-0.339176 radians) */
odetect_set_single_limit(ODETECT_LEFT, ODETECT_TURN_DISTANCE);
/*!angle: 0.312916 */
chassis_move(100, -100, 1, 7, 963);
while (chassis_busy()) {
	/*do something */
}
#endif


odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
chassis_move(50, 50, 1, 7, mmToTicks(520));
while (chassis_busy());

odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
chassis_move(-100, 100, 1, 7, 4862);
while (chassis_busy());

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
chassis_move(-50, -50, 1, 7, mmToTicks(1100));
while (chassis_busy());

odetect_set_single_limit(0, 0);
chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
chassis_write(0, 0);

chassis_write(20, 0);
stepper_reset_path(1);
while (stepper_get_path(1) <= mmToTicks(20));
chassis_write(0, 0);

tmgr_delay(200);
cannon_release(CANNON_RIGHT);
tmgr_delay(200);

chassis_write(-20, -10);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
chassis_write(0, 0);

odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
chassis_move(50, 50, 1, 7, mmToTicks(100));
while (chassis_busy());

odetect_set_single_limit(ODETECT_LEFT, ODETECT_TURN_DISTANCE);
chassis_move(100, -100, 1, 7, 4862);
while (chassis_busy());

odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
chassis_move(50, 50, 1, 7, mmToTicks(350));
while (chassis_busy());

odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
chassis_move(-100, 100, 1, 7, 4862);
while (chassis_busy());

odetect_set_single_limit(0, 0);
chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
chassis_write(0, 0);

tmgr_delay(200);
cannon_release(CANNON_LEFT);
tmgr_delay(200);
while (1);

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
/*!path: 246.018 */
chassis_move(-50 , -50 , 1, 7, 5368);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -21.62 degrees (-0.377253 radians) */
#if 0
/*!angle: 3.1294 */
chassis_move(100, -100, 1, 7, 9627);
chassis_move(-100, 100, 1, 7, 813);
while (1);
while (chassis_busy()) {
	/*do something */
}
#endif

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
/*!path: 105 */
chassis_move(-50 , -50 , 1, 7, 2291);
while (chassis_busy()) { 
	/* do something */
}

/* go back until the wall is detected */
chassis_write(-30, -30);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(200);
chassis_write(0, 0);
tmgr_delay(100);

/* let's reset position */
odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
chassis_move(80, 80, 1, 7, mmToTicks(150));
while (chassis_busy());

odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
chassis_move(-100, 100, 1, 7, 4832);
while (chassis_busy());

//odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
chassis_move(-100, -100, 1, 7, mmToTicks(500));
while (chassis_busy());

chassis_write(-30, -30);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(100);
chassis_write(0, 0);

/* go forward 60 cm */
odetect_set_single_limit(0, 0);
chassis_move(100, 100, 1, 7, mmToTicks(600));
while (chassis_busy());

odetect_set_single_limit(ODETECT_RIGHT, ODETECT_TURN_DISTANCE);
chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy());

odetect_set_single_limit(0, 0);
chassis_move(-70, -70, 1, 7, mmToTicks(75));
while (chassis_busy());

chassis_write(-40, -40);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(50);
chassis_write(0, 0);

tmgr_delay(200); /* establish position */
cannon_release(CANNON_LEFT);
tmgr_delay(300);

#if 0
/* rotate to -179.30 degrees (-3.129400 radians) */
/*!angle: 0.920026 */
chassis_move(100, -100, 1, 7, 2830);
//chassis_set_interrupt(odetect_front);
chassis_move(-100, 100, 1, 7, 9627);
while (chassis_busy()) {
	/*do something */
}
#endif

/*!speed: 50  */

odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
/*!path: 742.82 */
chassis_move(50 , 50 , 1, 7, 16207);
while (chassis_busy()) { 
	/* do something */
}

/* rotate to -52.71 degrees (-0.920026 radians) */
odetect_set_single_limit(ODETECT_LEFT, ODETECT_TURN_DISTANCE);
/*!angle: 0.920026 */
chassis_move(100, -100, 1, 7, 2830);
while (chassis_busy()) {
	/*do something */
}

odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_DISTANCE);
/*!path: 742.82 */
chassis_move(50 , 50 , 1, 7, 16207);
elevator_reset();
servo_write(1, 140);
servo_write(2, 27);
tmgr_delay(1000);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(800);
tmgr_delay(300);
odetect_set_single_limit(0, 0);
elevator_set_pos(20);

servo_write(1, 80);
tmgr_delay(300);
servo_write(2, 180);
tmgr_delay(300);
while (chassis_busy());


elevator_set_pos(4600);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

odetect_set_single_limit(0, 0);
chassis_move(-30, -30, 1, 12, mmToTicks(50));
while (chassis_busy());

chassis_move(30, 30, 1, 12, mmToTicks(50));
elevator_set_pos(1600);
servo_write(1, 140);
servo_write(2, 27);
tmgr_delay(500);
while (chassis_busy());

elevator_set_pos(2100);
tmgr_delay(200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(1600);

servo_write(1, 70);
tmgr_delay(400);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);

odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_DISTANCE);
chassis_move(-80, -80, 1, 7, mmToTicks(470));
servo_write(1, 0);
elevator_reset();
while (chassis_busy());

/********************************************************************
 * Here - go to the fireplace
 */

/* Let's do some magic with candles */

/* First fire is ready */
servo_write(1, 30);
tmgr_delay(500);

servo_write(1, 63);
servo_write(2, 27);
odetect_set_single_limit(0, 0);
chassis_move(-30, -30, 1, 7, mmToTicks(40));
while (chassis_busy());

tmgr_delay(300);

elevator_set_pos(700);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_reset();

tmgr_delay(300);

chassis_move(-10, -10, 1, 10, mmToTicks(40));
for (uint8_t i=27; i!=90; i++) {
        servo_write(2, i);
        tmgr_delay(30);
}
while (chassis_busy());
servo_write(2, 170);

chassis_move(-20, -20, 1, 10, mmToTicks(100));
elevator_set_pos(2000);
while (chassis_busy());

chassis_move(-100, 100, 1, 10, 2500);
elevator_set_pos(5500);
while (chassis_busy());

chassis_move(20, 20, 1, 10, mmToTicks(50));
while (chassis_busy());

tmgr_delay(500);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(500);

chassis_move(-20, -20, 1, 20, mmToTicks(50));
elevator_set_pos(2000);
while (chassis_busy());

chassis_move(100, -100, 1, 10, 2500);
elevator_reset();
while (chassis_busy());

chassis_move(20, 20, 1, 10, mmToTicks(170));
servo_write(1, 63);
servo_write(2, 27);
tmgr_delay(800);
while (chassis_busy());

/* take last */

elevator_set_pos(2000);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_reset();

tmgr_delay(200);


chassis_move(-6, -6, 1, 10, mmToTicks(40));
for (uint8_t i=27; i!=90; i++) {
        servo_write(2, i);
        tmgr_delay(30);
}
while (chassis_busy());
servo_write(2, 170);

chassis_move(-20, -20, 1, 10, mmToTicks(150));
while (chassis_busy());

servo_write(2, 27);

tmgr_delay(500);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(500);

chassis_move(-20, -20, 1, 20, mmToTicks(50));
elevator_reset();
while (chassis_busy());
