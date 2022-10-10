// ======================================================================
// \title  PIDController.hpp
// \author codeflight1
// \brief  hpp file for PIDController component implementation class
// ======================================================================

#ifndef PIDController_HPP
#define PIDController_HPP

#include "SignalProcessing/PIDController/PIDControllerComponentAc.hpp"

namespace SignalProcessing {

  class PIDController :
    public PIDControllerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PIDController
      //!
      PIDController(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object PIDController
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Configure PIDController component
      //!
      void configure(
          F32 tau, //!< Derivative low-pass filter time constant
          F32 limMin, //!< Output limit lower bound
          F32 limMax, //!< Output limit upper bound
          F32 T //!< Sample time (seconds)
      );

      //! Start PIDController component
      //! The component must be configured with configure() before starting
      //!
      void preamble();

      //! Destroy object PIDController
      //!
      ~PIDController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for dataIn
      //!
      void dataIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          F32 setpoint, //!< Control setpoint
          F32 measurement //!< Measured input
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Member variables
      // ----------------------------------------------------------------------

      //! Whether the configuration function has been called.
      bool configured;

      //! Derivative low-pass filter time constant
      F32 tau;

      //! Output limit lower bound
      F32 limMin;

      //! Output limit upper bound
      F32 limMax;

      //! Sample time (seconds)
      F32 T;

      //! Previous measurement
      F32 prevMeasurement;

      //! Previous error
      F32 prevError;

      //! Running integrator value
      F32 integral;

      //! Running derivative value
      F32 derivative;

      //! Output value
      F32 out;
  };

} // end namespace SignalProcessing

#endif
