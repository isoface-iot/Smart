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


PROGRAM program0
  VAR
    I_PbFill : BOOL := false;
    I_Pb_DisCharge : BOOL := true;
    Q_LightPbFill : BOOL := false;
    Q_LightPbDisCharging : BOOL := false;
    IPotentionMeterFill : INT := 0;
    IPotentionMeterDisCharge : INT := 0;
    ITankMeterLevel : INT := 0;
    ITankMeterFlow : INT := 0;
    QFillValue : INT := 0;
    QDisChargeValue : INT := 0;
    QTankFillValue : INT := 0;
    QTankDisChargeValue : INT := 0;
    QLevel : INT := 0;
    QFlowMeter : INT := 0;
    PbFill_Pressed : BOOL := false;
    PbDisCharge_Pressed : BOOL := false;
  END_VAR
  VAR
    PbFill_Trig : F_TRIG;
    PbDisCharge_Trig : R_TRIG;
    Old_PotentionMeterFill : INT := 0;
    Old_PotentionMeterDisCharge : INT := 0;
  END_VAR

  PbFill_Trig(CLK:= I_PbFill,Q=>PbFill_Pressed); 

  if (PbFill_Pressed = true) AND (Q_LightPbFill = false) then
    Q_LightPbFill := true;
    PbFill_Pressed := false;
  end_if;

  if (PbFill_Pressed = true) AND (Q_LightPbFill = true) then
    Q_LightPbFill := false;
    PbFill_Pressed := false;
  end_if;

  PbDisCharge_Trig(CLK:= I_Pb_DisCharge,Q => PbDisCharge_Pressed);

  if (PbDisCharge_Pressed = true) AND (Q_LightPbDisCharging = false) then
    Q_LightPbDisCharging := true;
    PbDisCharge_Pressed := false;
  end_if;

  if (PbDisCharge_Pressed = true) AND (Q_LightPbDisCharging = true) then
    Q_LightPbDisCharging := false;
    PbDisCharge_Pressed := false;
  end_if;

  if (IPotentionMeterFill <> Old_PotentionMeterFill) then
    QFillValue := IPotentionMeterFill;
    Old_PotentionMeterFill := IPotentionMeterFill;
  end_if;

  if (IPotentionMeterDisCharge <> Old_PotentionMeterDisCharge) then
    QDisChargeValue := IPotentionMeterDisCHarge;
    Old_PotentionMeterDisCharge := IPotentionMeterDisCharge;
  end_if;

  if (Q_LightPbFill = true) then
    QTankFillValue := QFillValue;
  else
    QTankFillValue := 0;
  end_if;

  if (Q_LightPbDisCharging = true) then
    QTankDisChargeValue := QDisChargeValue;
  else
    QTankDisChargeValue := 0;
  end_if;

  QLevel := ITankMeterLevel;
  QFlowMeter := ITankMeterFlow;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
