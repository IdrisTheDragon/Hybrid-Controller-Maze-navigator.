CC= ./xc16
BH="C:\Program Files (x86)\Microchip\xc16\v1.33\bin\xc16-bin2hex.exe" 

OBJ= robo.o input/Location.o input/ObstacleDetection.o control/WallFollow.o control/LightReaction.o RobotState.o control/RobotCalibrate.o input/dataCollect.o input/Light.o input/Encoders.o Cell.o output/bluetooth.o control/master.o control/movingInstructions.o output/setMotors.o
LIB="\lib\allcode_api.o"

SRC=src
OUT=out
$(OUT)/%.o: $(src)/%.c
	 $(CC) -c $< -o $@ 

out/robot.bin : $(OBJ) $(LIB)
	$(CC) -o $@ $(OBJ) $(LIB)

robot.hex : out/robot.bin
	$(BH) -a $<
