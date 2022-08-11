PROGRAM Main
  VAR
    I_Item_at_entry AT %IX100.0 : BOOL := false;
    I_Item_at_exit AT %IX100.1 : BOOL := false;
    I_Moving_X AT %IX100.2 : BOOL := false;
    I_Moving_Z AT %IX100.3 : BOOL := false;
    I_Item_detected AT %IX100.4 : BOOL := false;
    I_Start AT %IX100.5 : BOOL := false;
  END_VAR
  VAR
    Start_Pressed : BOOL := false;
    FTrig_Start : F_TRIG;
  END_VAR
  VAR
    I_Reset AT %IX100.6 : BOOL := false;
  END_VAR
  VAR
    Reset_Pressed : BOOL := false;
    FTrig_Reset : F_TRIG;
  END_VAR
  VAR
    I_Stop AT %IX100.7 : BOOL := true;
  END_VAR
  VAR
    Stop_Pressed : BOOL := false;
    RTrig_Stop : R_TRIG;
  END_VAR
  VAR
    I_Emergency_stop AT %IX101.0 : BOOL := true;
    I_Auto AT %IX101.1 : BOOL := false;
    Q_Entry_conveyor AT %QX100.0 : BOOL := false;
    Q_Exit_conveyor AT %QX100.1 : BOOL := false;
    Q_Move_X AT %QX100.2 : BOOL := false;
    Q_Move_Z AT %QX100.3 : BOOL := false;
    Q_Grab AT %QX100.4 : BOOL := false;
    Q_Start_light AT %QX100.5 : BOOL := false;
    Q_Reset_light AT %QX100.6 : BOOL := false;
    Q_Stop_light AT %QX100.7 : BOOL := true;
    Q_Counter AT %QW100 : INT := 0;
  END_VAR
  VAR
    RTrig_Moving_X : R_TRIG;
    RTrig_Moving_Z : R_TRIG;
    FTrig_Moving_Z1 : F_TRIG;
    RTrig_Moving_Z2 : R_TRIG;
    FTrig_Moving_Z3 : F_TRIG;
    Moving_X_Raise_Done : BOOL := false;
    Moving_X_Shrown_Done : BOOL := false;
    Moving_Z_Grab_Done : BOOL := false;
    Moving_Z_Shrown_Done : BOOL := false;
    Moving_Z_Put_Done : BOOL := false;
    Moving_Z_Put_Shrown_Done : BOOL := false;
    Ftrig_Count : F_TRIG;
    ExitSignal : BOOL := false;
  END_VAR

  (*急停*)
  if (I_Emergency_Stop = false) then
    Q_Stop_light := false;
    Q_Start_light := false;
  end_if;

  (*开始*)
  FTrig_Start(CLK:=I_Start, Q => Start_Pressed);

  if ((Start_Pressed = true) AND (I_Emergency_Stop = true)) then
    Q_Stop_light := false;
    Q_Start_light := true;
    Start_Pressed := false;
  end_if;

  (*重置*)
  FTrig_Reset(CLK:= I_Reset, Q => Reset_Pressed);

  if ((Reset_Pressed = true) AND (I_Emergency_Stop = true)) then
    Q_Stop_light := true;
    Q_Start_light := false; 
    Reset_Pressed := false;
    Q_Move_X := false;
    Q_Move_Z := false;
    Q_Grab := false;
  end_if;

  (*停止*)
  RTrig_Stop(CLK:=I_Stop,Q=>Stop_Pressed);

  if ((Stop_Pressed = true) AND (I_Emergency_Stop = true)) then
    Q_Stop_light := true;
    Q_Start_light := false;
    Stop_Pressed := false;
  end_if;

  (*传送带停止运行*)
  if ((Q_Start_light = false) AND (I_Emergency_Stop = true)) then
    Q_Exit_Conveyor := false;
    Q_Entry_Conveyor := false;
  end_if;

  (*物体运输开启传送带*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) AND (I_Item_at_entry = false) AND (Q_Move_Z = false)) then
    Q_Entry_Conveyor := true;
  end_if;

  (*传送带停止*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) AND (I_Item_at_entry = true)) then
    Q_Entry_Conveyor := false;
  end_if;


  (*运行流程*)

  (*传感器检测机械臂向下运行*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) AND (I_Item_at_entry = true) 
  AND (Q_Entry_Conveyor = false) AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = false) AND (I_Moving_Z = false)
  AND (Q_Grab = false) AND (I_Item_detected = false)) then
    Q_Move_Z := true;
  end_if;

  (*触发器检测*)
  RTrig_Moving_Z(CLK:=((I_Moving_Z)XOR(Q_Move_Z)), Q=> Moving_Z_Grab_Done);


  (*机械臂向下运行，检测到物体后抓取并提升*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) AND (I_Item_at_entry = true) 
  AND (Q_Entry_Conveyor = false) AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = true) AND (I_Moving_Z = false) AND (Moving_Z_Grab_Done = true)
  AND (Q_Grab = false) AND (I_Item_detected = true)) then
    Q_Grab := true;
    Moving_Z_Grab_Done := false;
  end_if;

  (*抓取后升起机械臂*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Entry_Conveyor = false) AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = true) AND (I_Moving_Z = false)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    Q_Move_Z := false;  
  end_if;

  (*触发器检测*)
  FTrig_Moving_Z1(CLK:=((I_Moving_Z)XOR(Q_Move_Z)), Q=> Moving_Z_Shrown_Done);


  (*抓取后向右发送*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) 
  AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = false) AND (I_Moving_Z = false) AND (Moving_Z_Shrown_Done = true)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    Q_Move_X := true;
    Moving_Z_Shrown_Done := false;
  end_if;

  (*触发器检测*)
  RTrig_Moving_X(CLK:=((I_Moving_X)XOR(Q_Move_X)), Q=> Moving_X_Raise_Done);

  (*向下传送*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false) AND (Moving_X_Raise_Done = true)
  AND (Q_Move_Z = false) AND (I_Moving_Z = false)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    Q_Move_Z := true;
    Q_Exit_Conveyor := false;
    Moving_X_Raise_Done := false;
  end_if;

  RTrig_Moving_Z2(CLK:=((I_Moving_Z)XOR(Q_Move_Z)), Q=> Moving_Z_Put_Done);

  (*松开*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false)
  AND (Q_Move_Z = true) AND (I_Moving_Z = false) AND (Moving_Z_Put_Done = true)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    Q_Grab := false;
  end_if;

  (*回升*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false)
  AND (Q_Move_Z = true) AND (I_Moving_Z = false) AND (Moving_Z_Put_Done = true) 
  AND (Q_Grab = false)) then
    Q_Move_Z := false;
    Moving_Z_Put_Done := false;
  end_if;

  FTrig_Moving_Z3(CLK:=((I_Moving_Z)XOR(Q_Move_Z)), Q=> Moving_Z_Put_Shrown_Done);

  (*返回*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false) AND (Moving_Z_Put_Done = false)
  AND (Q_Move_Z = false) AND (I_Moving_Z = false) AND (Moving_Z_Put_Shrown_Done = true)
  AND (Q_Grab = false)) then
    Q_Move_X := false;
    Q_Exit_Conveyor := true;
    Moving_Z_Put_Shrown_done := false;
  end_if;

  (*计数*)
  FTrig_Count(CLK:=I_Item_at_exit,Q=>ExitSignal);

  if (ExitSignal = true) then
    Q_Counter := Q_Counter + 1;
    ExitSignal := False;
  end_if;

  (*异常复位*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Grab = true) AND (I_Item_detected = false))  then
    Q_Move_Z := false;
    Q_Move_X := false;
    Q_Grab := false;
  end_if;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Main;
  END_RESOURCE
END_CONFIGURATION
