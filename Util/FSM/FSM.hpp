// ======================================================================
// \title  FSM.hpp
// \author nate
// \brief  hpp file for FSM component implementation class
// ======================================================================

#ifndef FSM_HPP
#define FSM_HPP

#include "Util/FSM/FSMComponentAc.hpp"

namespace Util {

  class FSM :
    public FSMComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object FSM
      //!
      FSM(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object FSM
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      void configure(U8[][] transitions, U8 state);

      //! Destroy object FSM
      //!
      ~FSM();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for getState
      //!
      U8 getState_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for transition
      //!
      void transition_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U16 transitionId 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for Transition command handler
      //! Transition to new state
      void Transition_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U16 transitionId 
      );

    PRIVATE:
      U8 m_state;
      U8[][] m_transitions;
      U16 m_num_transition;
    };

} // end namespace Util

#endif
