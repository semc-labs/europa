module Util {
  port GetState -> U8
  port Transition(transitionId: U16)

  passive component FSM {
    # ----------------------------------------------------------------------
    # Ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ A port for emitting events
    event port eventOut

    @ A port for emitting text events
    text event port textEventOut

    @ A port for emitting telemetry
    telemetry port tlmOut

    @ A port for getting the time
    time get port timeGetOut

    @ Current state port
    sync input port getState: GetState

    @ Transition signalling port
    output port onTransition: Transition

    @ Transition trigger port
    sync input port transition: Transition

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Transition to new state
    sync command Transition(transitionId: U16)

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Transition event
    event Transition(transitionId: U16) severity activity high format "Transition: {}"

    @ InvalidTransition event
    event InvalidTransition(transitionId: U16) severity warning high format "Invalid transition requested: {}"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ Current state
    telemetry State: U8
  }
}
