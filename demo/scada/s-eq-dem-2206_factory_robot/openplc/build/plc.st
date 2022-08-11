TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK



FUNCTION_BLOCK python_eval
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_poll
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_gear
  VAR_INPUT
    N : UINT;
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    py_eval : python_eval;
    COUNTER : UINT;
    ADD10_OUT : UINT;
    EQ13_OUT : BOOL;
    SEL15_OUT : UINT;
    AND7_OUT : BOOL;
  END_VAR

  ADD10_OUT := ADD(COUNTER, 1);
  EQ13_OUT := EQ(N, ADD10_OUT);
  SEL15_OUT := SEL(EQ13_OUT, ADD10_OUT, 0);
  COUNTER := SEL15_OUT;
  AND7_OUT := AND(EQ13_OUT, TRIG);
  py_eval(TRIG := AND7_OUT, CODE := CODE);
  ACK := py_eval.ACK;
  RESULT := py_eval.RESULT;
END_FUNCTION_BLOCK


PROGRAM Main
  VAR
    I_Item_at_entry : BOOL := false;
    I_Item_at_exit : BOOL := false;
    I_Moving_X : BOOL := false;
    I_Moving_Z : BOOL := false;
    I_Item_detected : BOOL := false;
    I_Start : BOOL := false;
  END_VAR
  VAR
    Start_Pressed : BOOL := false;
    FTrig_Start : F_TRIG;
  END_VAR
  VAR
    I_Reset : BOOL := false;
  END_VAR
  VAR
    Reset_Pressed : BOOL := false;
    FTrig_Reset : F_TRIG;
  END_VAR
  VAR
    I_Stop : BOOL := true;
  END_VAR
  VAR
    Stop_Pressed : BOOL := false;
    RTrig_Stop : R_TRIG;
  END_VAR
  VAR
    I_Emergency_stop : BOOL := true;
    I_Auto : BOOL := false;
    Q_Entry_conveyor : BOOL := false;
    Q_Exit_conveyor : BOOL := false;
    Q_Move_X : BOOL := false;
    Q_Move_Z : BOOL := false;
    Q_Grab : BOOL := false;
    Q_Start_light : BOOL := false;
    Q_Reset_light : BOOL := false;
    Q_Stop_light : BOOL := true;
    Q_Counter : INT := 0;
  END_VAR
  VAR
    FTrig_Moving_X : F_TRIG;
    FTrig_Moving_X1 : F_TRIG;
    FTrig_Moving_Z : F_TRIG;
    FTrig_Moving_Z1 : F_TRIG;
    FTrig_Moving_Z2 : F_TRIG;
    FTrig_Moving_Z3 : F_TRIG;
    Moving_X_Raise_Done : BOOL := false;
    Moving_X_Shrown_Done : BOOL := false;
    Moving_Z_Grab_Done : BOOL := false;
    Moving_Z_Shrown_Done : BOOL := false;
    Moving_Z_Put_Done : BOOL := false;
    Moving_Z_Put_Shrown_Done : BOOL := false;
    Ftrig_Count : F_TRIG;
    ExitSignal : BOOL := false;
    Cycle : BOOL := true;
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
    Cycle := true;
    Q_Counter := 0;
  end_if;

  (*停止*)
  RTrig_Stop(CLK:=I_Stop,Q=>Stop_Pressed);

  if ((Stop_Pressed = true) AND (I_Emergency_Stop = true)) then
    Q_Stop_light := true;
    Q_Start_light := false;
    Stop_Pressed := false;
  end_if;

  (*传送带停止运行*)
  if ((Q_Start_light = false)) then
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
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = false)
  AND (Q_Move_Z = false) AND (I_Moving_Z = false) AND (Cycle = false)
  AND (Q_Grab = false) AND (I_Item_detected = false)) then
    FTrig_Moving_X1(CLK:=I_Moving_X, Q=> Moving_X_Shrown_Done);
  end_if;

  (*循环标记*)
  if (Moving_X_Shrown_Done = true) then
    Cycle := true;
    Moving_X_Shrown_Done := false;
  end_if;


  (*传感器检测机械臂向下运行*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) AND (I_Item_at_entry = true) 
  AND (Q_Entry_Conveyor = false) AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = false) AND (I_Moving_Z = false) AND (Cycle = true)
  AND (Q_Grab = false) AND (I_Item_detected = false)) then
    Q_Move_Z := true;
    Cycle := false;
  end_if;

  (*触发器检测*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) AND (I_Item_at_entry = true) 
  AND (Q_Entry_Conveyor = false) AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = true)) then
    FTrig_Moving_Z(CLK:=I_Moving_Z, Q=> Moving_Z_Grab_Done);
  end_if;


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
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) 
  AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = false)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    FTrig_Moving_Z1(CLK:=I_Moving_Z, Q=> Moving_Z_Shrown_Done);
  end_if;

  (*抓取后向右发送*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true) 
  AND (Q_Move_X = false) AND (I_Moving_X = false) 
  AND (Q_Move_Z = false) AND (I_Moving_Z = false) AND (Moving_Z_Shrown_Done = true)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    Q_Move_X := true;
    Moving_Z_Shrown_Done := false;
  end_if;

  (*触发器检测*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true)
  AND (Q_Move_Z = false) AND (I_Moving_Z = false)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    FTrig_Moving_X(CLK:=I_Moving_X, Q=> Moving_X_Raise_Done);
  end_if;

  (*向下传送*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false) AND (Moving_X_Raise_Done = true)
  AND (Q_Move_Z = false) AND (I_Moving_Z = false)
  AND (Q_Grab = true) AND (I_Item_detected = true)) then
    Q_Move_Z := true;
    Q_Exit_Conveyor := false;
    Moving_X_Raise_Done := false;
  end_if;

  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false)
  AND (Q_Move_Z = true)) then
    FTrig_Moving_Z2(CLK:=I_Moving_Z, Q=> Moving_Z_Put_Done);
  end_if;

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

  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false)
  AND (Q_Move_Z = false)
  AND (Q_Grab = false)) then
    FTrig_Moving_Z3(CLK:=I_Moving_Z, Q=> Moving_Z_Put_Shrown_Done);
  end_if;

  (*返回*)
  if ((Q_Start_light = true) AND (I_Emergency_Stop = true) AND (I_Auto = true)
  AND (Q_Move_X = true) AND (I_Moving_X = false) AND (Moving_Z_Put_Done = false)
  AND (Q_Move_Z = false) AND (I_Moving_Z = false) AND (Moving_Z_Put_Shrown_Done = true)
  AND (Q_Grab = false)) then
    Q_Move_X := false;
    Q_Exit_Conveyor := true;
    Moving_Z_Put_Shrown_done := false;
    Cycle := false;
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
    Cycle := true;
  end_if;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Main;
  END_RESOURCE
END_CONFIGURATION
