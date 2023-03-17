// ======================================================================
// \title  FSM.cpp
// \author nate
// \brief  cpp file for FSM component implementation class
// ======================================================================


#include <Util/FSM/FSM.hpp>
#include <FpConfig.hpp>

namespace Util {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  FSM ::
    FSM(
        const char *const compName
    ) : FSMComponentBase(compName)
  {

  }

  void FSM ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    FSMComponentBase::init(instance);
  }

  void FSM::configure(U8[][] transitions, U16 num_transitions, U8 state) {
      FW_ASSERT(transitions);
      FW_ASSERT(num_transitions)

      this->m_transitions = transitions;
      this->m_num_transitions = num_transitions;
      this->m_state = state;
  }

  FSM ::
    ~FSM()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  U8 FSM ::
    getState_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    return this->m_state;
  }

  void FSM ::
    transition_handler(
        const NATIVE_INT_TYPE portNum,
        U16 transitionId
    )
  {
    if (transitionId < num_transitions && transitions[transitionId][0] == this->m_state) {
        this->m_state = transitions[transitionId][1];
        this->onTransition_out(0, transitionId);
        this->log_ACTIVITY_HIGH_Transition(transitionId);
        this->tlmWrite_State(this->m_state);
    }else {
        this->log_WARNING_HIGH_InvalidTransition(transitionId);
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void FSM ::
    Transition_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U16 transitionId
    )
  {
    if (transitionId < num_transitions && transitions[transitionId][0] == this->m_state) {
        this->m_state = transitions[transitionId][1];
        this->onTransition_out(0, transitionId);
        this->log_ACTIVITY_HIGH_Transition(transitionId);
        this->tlmWrite_State(this->m_state);
        this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
    }else {
        this->log_WARNING_HIGH_InvalidTransition(transitionId);
        this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
    }
  }

} // end namespace Util
