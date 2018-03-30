# MPLAB IDE generated this makefile for use with GNU make.
# Project: robot.mcp
# Date: Fri Mar 30 19:56:46 2018

AS = xc16-as.exe
CC = xc16-gcc.exe
LD = xc16-ld.exe
AR = xc16-ar.exe
HX = xc16-bin2hex.exe
RM = del

out/robot.hex : out/robot.cof
	$(HX) "out\robot.cof" -omf=coff

out/robot.cof : out/robo.o out/Location.o out/ObstacleDetection.o out/WallFollow.o out/LightReaction.o out/RobotState.o out/RobotCalibrate.o out/dataCollect.o out/Light.o out/Encoders.o out/Cell.o out/bluetooth.o out/master.o out/movingInstructions.o out/setMotors.o
	$(CC) -omf=coff -mcpu=33EP256MU810 "out\robo.o" "out\Location.o" "out\ObstacleDetection.o" "out\WallFollow.o" "out\LightReaction.o" "out\RobotState.o" "out\RobotCalibrate.o" "out\dataCollect.o" "out\Light.o" "out\Encoders.o" "out\Cell.o" "out\bluetooth.o" "out\master.o" "out\movingInstructions.o" "out\setMotors.o" "C:\Users\Nathan\Documents\Git Hub\robotCode\src\lib\allcode_api.o" -o"out\robot.cof" -Wl,-Tp33EP256MU810.gld,--defsym=__MPLAB_BUILD=1,--heap=10000,-Map="out\robot.map",--report-mem

out/robo.o : ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/yvals.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdlib.h src/Cell.h src/RobotState.h src/RobotState.h src/output/bluetooth.h src/Cell.h src/input/Location.h src/RobotState.h src/input/Location.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/robo.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\robo.c" -o"out\robo.o" -g -Wall -mno-eds-warn

out/Location.o : src/input/Light.h src/Cell.h src/input/Location.h src/RobotState.h src/input/Location.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/math.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/input/Location.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\input\Location.c" -o"out\Location.o" -g -Wall -mno-eds-warn

out/ObstacleDetection.o : src/control/RobotCalibrate.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/control/ObstacleDetection.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\control\ObstacleDetection.c" -o"out\ObstacleDetection.o" -g -Wall -mno-eds-warn

out/WallFollow.o : src/control/WallFollow.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\control\WallFollow.c" -o"out\WallFollow.o" -g -Wall -mno-eds-warn

out/LightReaction.o : src/control/LightReaction.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\control\LightReaction.c" -o"out\LightReaction.o" -g -Wall -mno-eds-warn

out/RobotState.o : src/RobotState.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\RobotState.c" -o"out\RobotState.o" -g -Wall -mno-eds-warn

out/RobotCalibrate.o : src/input/Location.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/control/RobotCalibrate.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\control\RobotCalibrate.c" -o"out\RobotCalibrate.o" -g -Wall -mno-eds-warn

out/dataCollect.o : ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/input/dataCollect.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\input\dataCollect.c" -o"out\dataCollect.o" -g -Wall -mno-eds-warn

out/Light.o : src/input/Encoders.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h src/input/Light.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/input/Light.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\input\Light.c" -o"out\Light.o" -g -Wall -mno-eds-warn

out/Encoders.o : src/RobotState.h src/output/bluetooth.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h src/input/Encoders.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/input/Encoders.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\input\Encoders.c" -o"out\Encoders.o" -g -Wall -mno-eds-warn

out/Cell.o : src/Cell.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\Cell.c" -o"out\Cell.o" -g -Wall -mno-eds-warn

out/bluetooth.o : ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/yvals.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdio.h src/RobotState.h src/control/master.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h src/output/bluetooth.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\output\bluetooth.c" -o"out\bluetooth.o" -g -Wall -mno-eds-warn

out/master.o : ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/yvals.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdlib.h src/control/movingInstructions.h src/RobotState.h src/control/master.h src/RobotState.h src/output/bluetooth.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h src/control/master.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\control\master.c" -o"out\master.o" -g -Wall -mno-eds-warn

out/movingInstructions.o : ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/RobotState.h src/output/setMotors.h src/RobotState.h src/control/movingInstructions.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h src/control/movingInstructions.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\control\movingInstructions.c" -o"out\movingInstructions.o" -g -Wall -mno-eds-warn

out/setMotors.o : src/input/Location.h ../../../../../program\ files\ (x86)/microchip/xc16/v1.33/include/lega-c/stdbool.h src/lib/allcode_api.h src/Cell.h src/RobotState.h src/input/Location.h src/RobotState.h src/output/setMotors.c
	$(CC) -omf=coff -mcpu=33EP256MU810 -x c -c "src\output\setMotors.c" -o"out\setMotors.o" -g -Wall -mno-eds-warn

clean : 
	$(RM) "out\robo.o" "out\Location.o" "out\ObstacleDetection.o" "out\WallFollow.o" "out\LightReaction.o" "out\RobotState.o" "out\RobotCalibrate.o" "out\dataCollect.o" "out\Light.o" "out\Encoders.o" "out\Cell.o" "out\bluetooth.o" "out\master.o" "out\movingInstructions.o" "out\setMotors.o" "out\robot.cof" "out\robot.hex"

