PROGRAM program0
  VAR
    I_PbFill AT %IX100.0 : BOOL := false;
    I_Pb_DisCharge AT %IX100.1 : BOOL := true;
    Q_LightPbFill AT %QX100.0 : BOOL := false;
    Q_LightPbDisCharging AT %QX100.1 : BOOL := false;
    IPotentionMeterFill AT %IW100 : INT := 0;
    IPotentionMeterDisCharge AT %IW101 : INT := 0;
    ITankMeterLevel AT %IW102 : INT := 0;
    ITankMeterFlow AT %IW103 : INT := 0;
    QFillValue AT %QW100 : INT := 0;
    QDisChargeValue AT %QW101 : INT := 0;
    QTankFillValue AT %QW102 : INT := 0;
    QTankDisChargeValue AT %QW103 : INT := 0;
    QLevel AT %QW104 : INT := 0;
    QFlowMeter AT %QW105 : INT := 0;
    PbFill_Pressed AT %QX100.2 : BOOL := false;
    PbDisCharge_Pressed AT %QX100.3 : BOOL := false;
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
