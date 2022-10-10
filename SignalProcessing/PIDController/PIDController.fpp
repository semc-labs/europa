module SignalProcessing {
  @ PID Controller Gain Struct
  struct PIDGains {
    Kp: F32, @< Proportional gain
    Ki: F32, @< Integral gain
    Kd: F32  @< Derivative gain
  }

  port F32Port(value: F32)
  port PIDInPort(setpoint: F32, measurement: F32)

  passive component PIDController {
    # ----------------------------------------------------------------------
    # Ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ Parameter get port
    param get port prmGetOut

    @ Parameter set port
    param set port prmSetOut

    sync input port dataIn: PIDInPort
    output port out: F32Port

    # ----------------------------------------------------------------------
    # Parameters
    # ----------------------------------------------------------------------

    param Gains: PIDGains
  }
}
