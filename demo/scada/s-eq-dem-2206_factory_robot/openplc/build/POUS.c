void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PYTHON_EVAL_init__(PYTHON_EVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->BUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->PREBUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->TRIGM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TRIGGED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_EVAL_body__(PYTHON_EVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // PYTHON_EVAL_body__() 





void PYTHON_POLL_init__(PYTHON_POLL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->BUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->PREBUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->TRIGM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TRIGGED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_POLL_body__(PYTHON_POLL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __IL_DEFVAR_T __IL_DEFVAR;
  __IL_DEFVAR_T __IL_DEFVAR_BACK;
  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // PYTHON_POLL_body__() 





void PYTHON_GEAR_init__(PYTHON_GEAR *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->N,0,retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  PYTHON_EVAL_init__(&data__->PY_EVAL,retain);
  __INIT_VAR(data__->COUNTER,0,retain)
  __INIT_VAR(data__->ADD10_OUT,0,retain)
  __INIT_VAR(data__->EQ13_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEL15_OUT,0,retain)
  __INIT_VAR(data__->AND7_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_GEAR_body__(PYTHON_GEAR *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,ADD10_OUT,,ADD__UINT__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->COUNTER,),
    (UINT)1));
  __SET_VAR(data__->,EQ13_OUT,,EQ__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->N,),
    (UINT)__GET_VAR(data__->ADD10_OUT,)));
  __SET_VAR(data__->,SEL15_OUT,,SEL__UINT__BOOL__UINT__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->EQ13_OUT,),
    (UINT)__GET_VAR(data__->ADD10_OUT,),
    (UINT)0));
  __SET_VAR(data__->,COUNTER,,__GET_VAR(data__->SEL15_OUT,));
  __SET_VAR(data__->,AND7_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->EQ13_OUT,),
    (BOOL)__GET_VAR(data__->TRIG,)));
  __SET_VAR(data__->PY_EVAL.,TRIG,,__GET_VAR(data__->AND7_OUT,));
  __SET_VAR(data__->PY_EVAL.,CODE,,__GET_VAR(data__->CODE,));
  PYTHON_EVAL_body__(&data__->PY_EVAL);
  __SET_VAR(data__->,ACK,,__GET_VAR(data__->PY_EVAL.ACK,));
  __SET_VAR(data__->,RESULT,,__GET_VAR(data__->PY_EVAL.RESULT,));

  goto __end;

__end:
  return;
} // PYTHON_GEAR_body__() 





void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_VAR(data__->I_ITEM_AT_ENTRY,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->I_ITEM_AT_EXIT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->I_MOVING_X,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->I_MOVING_Z,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->I_ITEM_DETECTED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->I_START,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->START_PRESSED,__BOOL_LITERAL(FALSE),retain)
  F_TRIG_init__(&data__->FTRIG_START,retain);
  __INIT_VAR(data__->I_RESET,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESET_PRESSED,__BOOL_LITERAL(FALSE),retain)
  F_TRIG_init__(&data__->FTRIG_RESET,retain);
  __INIT_VAR(data__->I_STOP,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->STOP_PRESSED,__BOOL_LITERAL(FALSE),retain)
  R_TRIG_init__(&data__->RTRIG_STOP,retain);
  __INIT_VAR(data__->I_EMERGENCY_STOP,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->I_AUTO,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_ENTRY_CONVEYOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_EXIT_CONVEYOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_MOVE_X,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_MOVE_Z,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_GRAB,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_START_LIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_RESET_LIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q_STOP_LIGHT,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->Q_COUNTER,0,retain)
  F_TRIG_init__(&data__->FTRIG_MOVING_X,retain);
  F_TRIG_init__(&data__->FTRIG_MOVING_X1,retain);
  F_TRIG_init__(&data__->FTRIG_MOVING_Z,retain);
  F_TRIG_init__(&data__->FTRIG_MOVING_Z1,retain);
  F_TRIG_init__(&data__->FTRIG_MOVING_Z2,retain);
  F_TRIG_init__(&data__->FTRIG_MOVING_Z3,retain);
  __INIT_VAR(data__->MOVING_X_RAISE_DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MOVING_X_SHROWN_DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MOVING_Z_GRAB_DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MOVING_Z_SHROWN_DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MOVING_Z_PUT_DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MOVING_Z_PUT_SHROWN_DONE,__BOOL_LITERAL(FALSE),retain)
  F_TRIG_init__(&data__->FTRIG_COUNT,retain);
  __INIT_VAR(data__->EXITSIGNAL,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CYCLE,__BOOL_LITERAL(TRUE),retain)
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  if ((__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(FALSE))) {
    __SET_VAR(data__->,Q_STOP_LIGHT,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_START_LIGHT,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->FTRIG_START.,CLK,,__GET_VAR(data__->I_START,));
  F_TRIG_body__(&data__->FTRIG_START);
  __SET_VAR(data__->,START_PRESSED,,__GET_VAR(data__->FTRIG_START.Q));
  if (((__GET_VAR(data__->START_PRESSED,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_STOP_LIGHT,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_START_LIGHT,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,START_PRESSED,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->FTRIG_RESET.,CLK,,__GET_VAR(data__->I_RESET,));
  F_TRIG_body__(&data__->FTRIG_RESET);
  __SET_VAR(data__->,RESET_PRESSED,,__GET_VAR(data__->FTRIG_RESET.Q));
  if (((__GET_VAR(data__->RESET_PRESSED,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_STOP_LIGHT,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,Q_START_LIGHT,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,RESET_PRESSED,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_MOVE_X,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_MOVE_Z,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_GRAB,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,CYCLE,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,Q_COUNTER,,0);
  };
  __SET_VAR(data__->RTRIG_STOP.,CLK,,__GET_VAR(data__->I_STOP,));
  R_TRIG_body__(&data__->RTRIG_STOP);
  __SET_VAR(data__->,STOP_PRESSED,,__GET_VAR(data__->RTRIG_STOP.Q));
  if (((__GET_VAR(data__->STOP_PRESSED,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_STOP_LIGHT,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,Q_START_LIGHT,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,STOP_PRESSED,,__BOOL_LITERAL(FALSE));
  };
  if ((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(FALSE))) {
    __SET_VAR(data__->,Q_EXIT_CONVEYOR,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_ENTRY_CONVEYOR,,__BOOL_LITERAL(FALSE));
  };
  if ((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_AT_ENTRY,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->,Q_ENTRY_CONVEYOR,,__BOOL_LITERAL(TRUE));
  };
  if (((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_AT_ENTRY,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_ENTRY_CONVEYOR,,__BOOL_LITERAL(FALSE));
  };
  if ((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->CYCLE,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->FTRIG_MOVING_X1.,CLK,,__GET_VAR(data__->I_MOVING_X,));
    F_TRIG_body__(&data__->FTRIG_MOVING_X1);
    __SET_VAR(data__->,MOVING_X_SHROWN_DONE,,__GET_VAR(data__->FTRIG_MOVING_X1.Q));
  };
  if ((__GET_VAR(data__->MOVING_X_SHROWN_DONE,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,CYCLE,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,MOVING_X_SHROWN_DONE,,__BOOL_LITERAL(FALSE));
  };
  if (((((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_AT_ENTRY,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_ENTRY_CONVEYOR,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->CYCLE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->,Q_MOVE_Z,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,CYCLE,,__BOOL_LITERAL(FALSE));
  };
  if (((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_AT_ENTRY,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_ENTRY_CONVEYOR,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->FTRIG_MOVING_Z.,CLK,,__GET_VAR(data__->I_MOVING_Z,));
    F_TRIG_body__(&data__->FTRIG_MOVING_Z);
    __SET_VAR(data__->,MOVING_Z_GRAB_DONE,,__GET_VAR(data__->FTRIG_MOVING_Z.Q));
  };
  if (((((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_AT_ENTRY,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_ENTRY_CONVEYOR,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_Z_GRAB_DONE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_GRAB,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,MOVING_Z_GRAB_DONE,,__BOOL_LITERAL(FALSE));
  };
  if (((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_ENTRY_CONVEYOR,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_MOVE_Z,,__BOOL_LITERAL(FALSE));
  };
  if (((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->FTRIG_MOVING_Z1.,CLK,,__GET_VAR(data__->I_MOVING_Z,));
    F_TRIG_body__(&data__->FTRIG_MOVING_Z1);
    __SET_VAR(data__->,MOVING_Z_SHROWN_DONE,,__GET_VAR(data__->FTRIG_MOVING_Z1.Q));
  };
  if (((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_Z_SHROWN_DONE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_MOVE_X,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,MOVING_Z_SHROWN_DONE,,__BOOL_LITERAL(FALSE));
  };
  if (((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->FTRIG_MOVING_X.,CLK,,__GET_VAR(data__->I_MOVING_X,));
    F_TRIG_body__(&data__->FTRIG_MOVING_X);
    __SET_VAR(data__->,MOVING_X_RAISE_DONE,,__GET_VAR(data__->FTRIG_MOVING_X.Q));
  };
  if (((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_X_RAISE_DONE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_MOVE_Z,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,Q_EXIT_CONVEYOR,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,MOVING_X_RAISE_DONE,,__BOOL_LITERAL(FALSE));
  };
  if (((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->FTRIG_MOVING_Z2.,CLK,,__GET_VAR(data__->I_MOVING_Z,));
    F_TRIG_body__(&data__->FTRIG_MOVING_Z2);
    __SET_VAR(data__->,MOVING_Z_PUT_DONE,,__GET_VAR(data__->FTRIG_MOVING_Z2.Q));
  };
  if (((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_Z_PUT_DONE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(TRUE)))) {
    __SET_VAR(data__->,Q_GRAB,,__BOOL_LITERAL(FALSE));
  };
  if ((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_Z_PUT_DONE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->,Q_MOVE_Z,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,MOVING_Z_PUT_DONE,,__BOOL_LITERAL(FALSE));
  };
  if ((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->FTRIG_MOVING_Z3.,CLK,,__GET_VAR(data__->I_MOVING_Z,));
    F_TRIG_body__(&data__->FTRIG_MOVING_Z3);
    __SET_VAR(data__->,MOVING_Z_PUT_SHROWN_DONE,,__GET_VAR(data__->FTRIG_MOVING_Z3.Q));
  };
  if (((((((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_MOVE_X,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_MOVING_X,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_Z_PUT_DONE,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->Q_MOVE_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->I_MOVING_Z,) == __BOOL_LITERAL(FALSE))) && (__GET_VAR(data__->MOVING_Z_PUT_SHROWN_DONE,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->,Q_MOVE_X,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_EXIT_CONVEYOR,,__BOOL_LITERAL(TRUE));
    __SET_VAR(data__->,MOVING_Z_PUT_SHROWN_DONE,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,CYCLE,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->FTRIG_COUNT.,CLK,,__GET_VAR(data__->I_ITEM_AT_EXIT,));
  F_TRIG_body__(&data__->FTRIG_COUNT);
  __SET_VAR(data__->,EXITSIGNAL,,__GET_VAR(data__->FTRIG_COUNT.Q));
  if ((__GET_VAR(data__->EXITSIGNAL,) == __BOOL_LITERAL(TRUE))) {
    __SET_VAR(data__->,Q_COUNTER,,(__GET_VAR(data__->Q_COUNTER,) + 1));
    __SET_VAR(data__->,EXITSIGNAL,,__BOOL_LITERAL(FALSE));
  };
  if ((((((__GET_VAR(data__->Q_START_LIGHT,) == __BOOL_LITERAL(TRUE)) && (__GET_VAR(data__->I_EMERGENCY_STOP,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_AUTO,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->Q_GRAB,) == __BOOL_LITERAL(TRUE))) && (__GET_VAR(data__->I_ITEM_DETECTED,) == __BOOL_LITERAL(FALSE)))) {
    __SET_VAR(data__->,Q_MOVE_Z,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_MOVE_X,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,Q_GRAB,,__BOOL_LITERAL(FALSE));
    __SET_VAR(data__->,CYCLE,,__BOOL_LITERAL(TRUE));
  };

  goto __end;

__end:
  return;
} // MAIN_body__() 





